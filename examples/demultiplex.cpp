#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "Fastq.hpp"
#include "string_utils.hpp"

using namespace std;

std::map<std::string,std::vector<std::string>> parse_barcodes(std::string filename);
int main(int argc, char** argv)
{
    if(argc < 2) cout << "Usage : "<< argv[0] << " <fasta file> <barcode.txt> " << endl;
    else {
        ifstream file(argv[1]);
        while(file){
            string head,seq,opt,qual;
            getline(file,head);
            getline(file,seq);
            getline(file,opt);
            getline(file,qual);
            Fastq record = Fastq(head,seq,opt,qual);
	    auto barcodes = parse_barcodes(string(argv[2]));
            for( auto code : barcodes )
	    {
		bool a = record.search_in_seq(code.second[0]);
		bool b = record.search_in_seq(code.second[1]);
		bool c = record.search_in_seq(code.second[2]);
		bool d = record.search_in_seq(code.second[3]); 
                if (a||b||c||d)
		{
                    ofstream fastq(code.first+".txt", std::ios::out|std::ios_base::app);
                    fastq << record.to_string() << endl;
                    fastq.close();
		}
	     }
            //string pattern = argv[2];
            //if (record.search_in_seq(pattern))
               // cout << record.to_string() << endl;
                  }
        file.close();
        }
}

std::map<std::string,std::vector<std::string>> parse_barcodes(std::string filename)
{
    std::map<std::string,std::vector<std::string>> barcodes;
    std::ifstream file(filename.c_str());
    while(file) {
       std::string line;
       getline(file,line);
       if(!line.empty()) {
           StringUtils colstr(line);
           auto col = colstr.split_by('\t');
           auto frc = StringUtils(col[1]).reverse_complement();
           auto rrc = StringUtils(col[2]).reverse_complement();
           barcodes[col[0]] = { col[1],col[2], frc, rrc };
	}
    }
    file.close();
    return barcodes;
}
