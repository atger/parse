#include <string>

class Fastq
{
    std::string header;
    std::string sequence;
    std::string optional;
    std::string quality;
    public:
    Fastq(std::string h, std::string s, std::string o, std::string q) : header(h),sequence(s), optional(o), quality(q) {}
    std::string to_string();
    bool search_in_seq(std::string pattern);
    bool is_match(std::string pattern,int mismatch);
};
    
