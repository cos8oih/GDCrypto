//C++ application that generates a pseudo check
#include "Include/GDCrypto.hpp"
#include <random>

using namespace GDCrypto;

std::string randomString()
{
	static std::string const dict("abcdefghijklmnopqrstuvwxyz123456789");
	std::string s;
	std::random_device r;

	for (auto i = 0u; i < 5u; ++i)
		s += dict[r() % dict.size()];

	return s;
}

unsigned int randomNumber()
{
	return std::random_device()();
}

int main()
{
	CheckGenerator gen(Keys::REWARDS_KEY, Salts::REWARDS_SALT);
	RobTopDecoder decoder(Keys::REWARDS_KEY);

	auto randString = randomString();
	auto randNum = randomNumber();

	gen << randString << std::to_string(randNum);
	decoder << gen.digestAsString();

	std::cout << "String: " << randString << '\n';
	std::cout << "Number: " << randNum << '\n';
	std::cout << "Raw data: " << randString << randNum << Salts::REWARDS_SALT << '\n';
	std::cout << "SHA1: " << decoder.digestAsString() << '\n';
	std::cout << "Final check: " << gen.digestAsString() << std::endl;

	return 0;
}