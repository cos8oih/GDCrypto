//C++ application which encode/decode savegames
#include "Include/GDCrypto.hpp"
#include <fstream> //For reading/writing files

using namespace GDCrypto;

static std::string const optionEncode("--encode");
static std::string const optionDecode("--decode");

void encode(std::string const& path)
{
	SavegameEncoder encoder;
	std::ifstream in(path);
	std::ofstream out(path + ".dat");

	if (in.is_open() && out.is_open())
	{
		encoder << in >> out;
		std::cout << "Encoded file written to: \""
			<< path + ".dat\"" << std::endl;
	}
	else
	{
		std::cout 
			<< "Couldn't open input/output files!"
			<< std::endl;
	}
}

void decode(std::string const& path)
{
	SavegameDecoder decoder;
	std::ifstream in(path);
	std::ofstream out(path + ".out");

	if (in.is_open() && out.is_open())
	{
		decoder << in >> out;
		std::cout << "Decoded file written to: \""
			<< path + ".out\"" << std::endl;
	}
	else
	{
		std::cout
			<< "Couldn't open input/output files!"
			<< std::endl;
	}
}

int main(int argc, char** argv)
{
	std::cout << "GD savegame encoder/decoder\n";

	if (argc > 2)
	{
		if (argv[1] == optionEncode)
			encode(argv[2]);
		else if (argv[1] == optionDecode)
			decode(argv[2]);

		return 0;
	}

	std::cout << "Usage: " << argv[0]
		<< " [--encode|--decode] [filepath]"
		<< std::endl;

	return 0;
}