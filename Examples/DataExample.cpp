//Savefile decoding
#include "Include/GDCrypto/DataCipher.hpp"
#include "Include/GDCrypto/RobTopCipher.hpp"
#include "Source/ZlibHelper.hpp"
#include <fstream>

using namespace gdcrypto;

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

int main()
{
	/*
	Base64Cipher b64;
	LevelDataCipher lvl;

	std::ifstream data("C:\\Users\\Nicolas\\Desktop\\gd saves\\broken.dat", std::ios::binary);

	if (data.is_open())
	{
		auto buffer = b64.decode(data);
		writeToFile("C:\\Users\\Nicolas\\Desktop\\gd saves\\broken.gzip", buffer);

		buffer = lvl.decode(data);
		writeToFile("C:\\Users\\Nicolas\\Desktop\\gd saves\\broken.xml", buffer);
	}

	return 0;
	*/

	std::ifstream data("C:\\Users\\Nicolas\\Desktop\\gd saves\\mac_saves\\macsave1.dat", std::ios::binary);

	if (data.is_open())
	{
		std::vector<uint8_t> buffer(std::istreambuf_iterator(data), {});
		auto decoded = zlib::inflateBuffer(buffer);
		std::cout << "All g\n";
	}

	return 0;
}