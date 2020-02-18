#include <string>
#include <vector>
#include <fstream>
#include "fasta.hpp"
#include "fastq.hpp"


template <typename T>
std::vector<T> parse_seq_file(std::string filename, std::string format)
{
	std::cout << typeid(T).name() << std::endl;
	std::vector<T> records;
        std::ifstream file(filename);
        if (format == "fasta")
        {
                while(file)
                {
                        std::string head,seq;
                        std::getline(file,head);
                        std::getline(file,seq);
                        Fasta f = Fasta(head,seq);
                        records.push_back(f);
                }
        } else if (format == "fastq")
        {
                while(file)
                {
                        std::string head,seq,opt,qual;
                        std::getline(file,head);
                        std::getline(file,seq);
                        std::getline(file,opt);
                        std::getline(file,qual);
                        Fastq f = Fastq(head,seq,opt,qual);
                        //records.push_back(f);
                }
        }
        return records;
}

