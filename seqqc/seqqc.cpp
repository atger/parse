#include <iostream>
#include <string>
#include "boost/program_options.hpp"

using namespace std;

void info()
{
	std::cout << "This is SeqQC program" << std::endl;
}

int main(int argc, char** argv)
{
	namespace po = boost::program_options;
	po::options_description desc("Options");
	desc.add_options()
	("help","Print help messages");
	po::variables_map vm;

}

