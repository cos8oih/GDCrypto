//GJP encoder/decoder
#include "Include/GDCrypto/RobTopCipher.hpp"

using namespace gdcrypto;

static std::string const OPTION_ENCODE("--encode");
static std::string const OPTION_DECODE("--decode");

int encode(
	RobTopCipher& cipher,
	std::string const& s)
{
	auto encoded = cipher.encode(s);

	std::cout
		<< "Encoded password: "
		<< encoded
		<< std::endl;

	return 0;
}

int decode(
	RobTopCipher& cipher,
	std::string const& s)
{
	auto buf = cipher.decode(s);
	std::string decoded(buf.begin(), buf.end());

	std::cout
		<< "Decoded password: "
		<< decoded
		<< std::endl;

	return 0;
}

int main(
	int const argc,
	char const* const* argv)
{
	RobTopCipher gjpCipher(gdcrypto::vecFromArray(keys::GJP_KEY));

	if (argc == 3)
	{
		if (argv[1] == OPTION_ENCODE)
			return encode(gjpCipher, argv[2]);
		else if (argv[1] == OPTION_DECODE)
			return decode(gjpCipher, argv[2]);
	}

	std::cout
		<< "\nUsage: "
		<< argv[0]
		<< " [--encode|--decode] [password]"
		<< std::endl;

	return 0;
}