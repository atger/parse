#include <iostream>
#include <vector>
#include <algorithm>
#include "Fastq.hpp"

std::string Fastq::to_string()
{
    return header+"\n"+sequence+"\n"+optional+"\n"+quality;
}

bool Fastq::search_in_seq(std::string pattern)
{
    return sequence.find(pattern) != std::string::npos ? true : false;
}

bool Fastq::is_match(std::string pattern,int mismatch)
{
    std::vector<int> matches;
    for (int i = 0; i < sequence.length()-pattern.length(); i++) {
        if (sequence[i] == pattern[0]) {
            int count = 0;
            for(int j = 0; j < pattern.length(); j++)
            {
                if (sequence[i+j] == pattern[j])
                    count += 1;
            }
            matches.push_back(count);
         }
    }
    return (*std::max_element(matches.begin(),matches.end()) >= pattern.length()-mismatch) ? true : false ;
}
