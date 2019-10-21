#include <iostream>
#include "Fastq.hpp"

using namespace std;

int main() 
{

  auto record = Fastq(">hesd","ATAAGGC","+","F24s241#$@#$");
  cout << record.to_string() << endl;
  //cout << record.search_in_seq("AA") << endl;
  cout << record.is_match("ATG",0) << endl;

}
