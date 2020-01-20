//C++ application which encode/decode passwords
#include "Include/GDCrypto.hpp"
#include <chrono>

using namespace GDCrypto;

static std::string const optionEncode("--encode");
static std::string const optionDecode("--decode");

void encode(std::string const& s)
{
	RobTopEncoder encoder(Keys::GJP_KEY);

	std::cout << "Encoded password: "
		<< (encoder << s).digestAsString()
		<< std::endl;
}

void decode(std::string const& s)
{
	RobTopDecoder decoder(Keys::GJP_KEY);

	std::cout << "Decoded password: "
		<< (decoder << s).digestAsString()
		<< std::endl;
}

int main(int argc, char** argv)
{
	std::cout << "GD password encoder/decoder\n";

	if (argc > 2)
	{
		if (argv[1] == optionEncode)
			encode(argv[2]);
		else if (argv[1] == optionDecode)
			decode(argv[2]);

		return 0;
	}

	std::cout << "Usage: " << argv[0]
		<< " [--encode|--decode] [password|gjp]"
		<< std::endl;

	return 0;
}