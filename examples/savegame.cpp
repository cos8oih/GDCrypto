#include "include/gdcrypto.hpp"
#include <fstream>

using namespace std;

//Messy
int main()
{
	char * EncodedData;
	string DecodedData;
	size_t EncodedDataSize = 0;
	ifstream GMRead("path\\to\\CCGameManager.dat", std::ifstream::ate, std::ifstream::binary);
	ofstream GMWrite("Output.xml", std::ofstream::binary);
	if (GMRead.is_open() && GMWrite.is_open())
	{
		EncodedDataSize = GMRead.tellg();
		GMRead.seekg(0, SEEK_SET);
		EncodedData = new char[EncodedDataSize];
		GMRead.read(EncodedData, EncodedDataSize);
		vector<unsigned char> EncodedDataVec(EncodedData, EncodedData + EncodedDataSize);
		DecodedData = DecodeSavegame(EncodedDataVec);
		if (!DecodedData.empty())
			GMWrite.write(DecodedData.data(), DecodedData.size());
		else
			cout << "Something went wrong when trying to decode the savegame." << std::endl;
		delete[] EncodedData;
	}
	else
		cout << "Something went wrong when trying to open the savegame.";

	GMRead.close();
	GMWrite.close();
	cout << "Procedure complete." << endl;
	cin.get();
	return 0;
}
