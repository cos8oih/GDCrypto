//Savefile encoding/decoding
#include "Include/GDCrypto/DataCipher.hpp"

#include <fstream>

using namespace gdcrypto;

static std::string_view constexpr OPTION_ENCODE("--encode");
static std::string_view constexpr OPTION_DECODE("--decode");

static std::string_view constexpr OPTION_IOS("--ios");

std::vector<uint8_t> readFromFile(std::string const& path)
{
	std::vector<uint8_t> buffer;
	std::ifstream file(path, std::ios::ate, std::ios::binary);

	if (file.is_open())
	{
		auto size = file.tellg();
		file.seekg(0, std::ios::beg);

		buffer.resize(size);

		file.read(
			reinterpret_cast<char*>(buffer.data()),
			size);
	}

	return buffer;
}

bool writeToFile(
	std::string const& path,
	std::vector<uint8_t> const& data)
{
	std::ofstream file(path, std::ios::binary);

	if (file.is_open())
	{
		file.write(
			reinterpret_cast<char*>(
				const_cast<uint8_t*>(data.data())),
			data.size());

		return true;
	}

	return false;
}

bool writeToFile(
	std::string const& path,
	std::string_view const s)
{
	return writeToFile(
		path,
		std::vector<uint8_t>(s.begin(), s.end()));
}

int encode(std::string const& path)
{
	SavegameCipher cipher;

	auto buffer = readFromFile(path);
	auto s = cipher.encode(buffer);
	writeToFile(path + ".encoded", s);

	return 0;
}

int decode(std::string const& path)
{
	SavegameCipher cipher;

	auto buffer = readFromFile(path);
	buffer = cipher.decode(buffer);
	writeToFile(path + ".decoded", buffer);

	return 0;
}

int encodeIOS(std::string const& path)
{
	IOSSavegameCipher cipher;

	auto buffer = readFromFile(path);
	auto s = cipher.encode(buffer);
	writeToFile(path + ".encoded", s);

	return 0;
}

int decodeIOS(std::string const& path)
{
	IOSSavegameCipher cipher;

	auto buffer = readFromFile(path);
	buffer = cipher.decode(buffer);
	writeToFile(path + ".decoded", buffer);

	return 0;
}

int main(int argc, char** argv)
{
	if (argc == 3)
	{
		if (argv[1] == OPTION_ENCODE)
			return encode(argv[2]);
		else if (argv[1] == OPTION_DECODE)
			return decode(argv[2]);
	}
	else if (argc == 4 &&
	argv[2] == OPTION_IOS)
	{
		if (argv[1] == OPTION_ENCODE)
			return encodeIOS(argv[3]);
		else if (argv[1] == OPTION_DECODE)
			return decodeIOS(argv[3]);
	}

	std::cout
		<< "\nUsage: "
		<< argv[0]
		<< " [--encode|--decode] [--ios] [savefile path]"
		<< std::endl;

	return 0;
}