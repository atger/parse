#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/progress.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

std::string reverse_complement(std::string text)
{
        std::reverse(text.begin(),text.end());
        std::map<char,char> comp = {{'A','T'},{'T','A'},{'C','G'},{'G','C'}};
        std::string rc = "";
        for(auto c : text)
            rc += comp[c];
        return rc;
}

std::map<std::string,std::vector<std::string>> parse_barcodes(std::string filename)
{
    std::map<std::string,std::vector<std::string>> barcodes;
    std::ifstream file(filename.c_str());
    int ln = 0;
    while(file)
    {
       std::string line;
       getline(file,line);
       ++ln;
       if(!line.empty())
       {
           int spaces = std::count(line.begin(),line.end(),' ');
           if(spaces == 0)
           {
               std::vector<std::string> col;
               split(col,line,boost::is_any_of("\t"));
               if (col.size() == 3)
               {
                   auto frc = reverse_complement(col[1]);
                   auto rrc = reverse_complement(col[2]);
                   barcodes[col[0]] = { col[1],col[2], frc, rrc };
               } else if (col.size() == 2)
               {
                   auto frc = reverse_complement(col[1]);
                   barcodes[col[0]] = { col[1], frc };
               }
           } else {
               throw invalid_argument("Error in Line "+to_string(ln)+": "+filename+" not in proper tab separated format");
           }
       }
    }
    file.close();
    return barcodes;
}

int match_count(std::string text, std::string pattern)
{
    std::vector<int> matches;
    for (int i = 0; i < text.length()-pattern.length()+1; ++i) {
        if (text[i] == pattern[0]) 
         {
            int count = 0;
            for(int j = 0; j < pattern.length(); ++j)
            {
                if (text[i+j] == pattern[j])
                    count += 1;
            }
            matches.push_back(count);
         }
    }
    return !matches.empty() ? *std::max_element(matches.begin(),matches.end()): true;
}

std::vector<bool> is_combination_exists(std::string seq, std::map<std::string,std::vector<std::string>> barcodes, int mismatch)
{
    std::vector<bool> bc_exists;
    for (auto code : barcodes)
    {
        if (code.second.size() == 4)
        {
            bool forward = match_count(seq,code.second[0]) >= (code.second[0].length() - mismatch);
            bool reverse_comp = match_count(seq,code.second[3]) >= (code.second[3].length() - mismatch);
            bool reverse = match_count(seq,code.second[1]) >= (code.second[1].length() - mismatch);
            bool forward_comp = match_count(seq,code.second[2]) >= (code.second[2].length() - mismatch);
            bool exist = forward && reverse_comp || reverse && forward_comp;
            bc_exists.push_back(exist);
        } else if (code.second.size() == 2)
        {
            bool forward = match_count(seq,code.second[0]) >= (code.second[0].length() - mismatch);
            bool forward_comp = match_count(seq,code.second[1]) >= (code.second[1].length() - mismatch);
            bool exist = forward || forward_comp;
            bc_exists.push_back(exist);
        }
    }
    return bc_exists;

}

int main(int argc, char** argv)
{
    if (argc < 4)
        cout << "Usage : " << argv[0] << " <sample_sheet> <fastq file> <allowed mismatch>" << endl;
    else
    {
        auto barcodes = parse_barcodes(string(argv[1]));
        vector<string> keys;

        for(auto code : barcodes)
        {
            ofstream f(code.first+".fastq", std::ios::out);
            keys.push_back(code.first);
        }
        ofstream multiclass_file("multiclass.fastq", std::ios::out);
        ofstream unclassified_file("unclassified.fastq", std::ios::out);

	ifstream file(argv[2]);
        ifstream f(argv[2],std::ios::binary|std::ios::ate); 
        boost::progress_display show_progress(f.tellg());
        stringstream ss(argv[3]);
        int mismatch;
        ss >> mismatch;
        int count = 0;
        while(file)
	{
            //cout << file.tellg() << endl;
	    string head,seq,opt,qual;
	    getline(file,head);
	    getline(file,seq);
            getline(file,opt);
            getline(file,qual);
            count += 4;
            if (!head.empty() || !seq.empty())
            {
                 std::vector<bool> bc_exists = is_combination_exists(seq,barcodes,mismatch);
                 int present_in = std::count(bc_exists.begin(),bc_exists.end(),true);
                 if (present_in == 1)
                 {
                     auto iter = find(bc_exists.begin(),bc_exists.end(),true);
                     int ix = std::distance(bc_exists.begin(),iter);
		     ofstream fastq(keys[ix]+".fastq", std::ios_base::app);
		     fastq << head << endl;
		     fastq << seq << endl;
                     fastq << opt << endl;
                     fastq << qual << endl;
		     fastq.close();
                 } else if (present_in > 1) {
		     multiclass_file << head << endl;
		     multiclass_file << seq << endl;
                     multiclass_file << opt << endl;
                     multiclass_file << qual << endl;
                 } else {
		     unclassified_file << head << endl;
                     unclassified_file << seq << endl;
                     unclassified_file << opt << endl;
                     unclassified_file << qual << endl;
                 }
             }
             show_progress += (head.length()+seq.length()+opt.length()+qual.length());

	}
    }
    cout << endl;
}
