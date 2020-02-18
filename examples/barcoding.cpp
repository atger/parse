#include <seqan/seq_io.h>

using namespace seqan;

int main(int argc, char const ** argv)
{
	CharString seqFileName = argv[1];
	CharString id;
	Dna5String seq;

	SeqFileIn seqFileIn(toCString(seqFileName));
	readRecords(id,seq,seqFileIn);
	std::cout << id << "\t" << seq << "\n";
	return 0;
}
