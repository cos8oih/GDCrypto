//C++ application which encode/decode savegames
#include "Include/GDCrypto.hpp"
#include <chrono>
#include <fstream>

using namespace GDCrypto;

static std::string const optionEncode("--encode");
static std::string const optionDecode("--decode");

class Benchmark
{
public:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	Benchmark() { start = std::chrono::steady_clock::now(); }
	~Benchmark()
	{
		end = std::chrono::steady_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Code ran in " << diff.count() << "ms" << std::endl;
	}
};

void encode(std::string const& path)
{
	SavegameEncoder encoder;
	std::ifstream in(path);
	std::ofstream out(path + ".dat");

	if (in.is_open() && out.is_open())
	{
		Benchmark b;
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
		Benchmark b;
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