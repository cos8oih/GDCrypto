#include "include/gdcrypto.hpp"

using namespace std;

int main()
{

	vector<unsigned char> Password = { 'H', 'e', 'l', 'l', 'o' };

	cout << "Encoded data: " << RobtopCipher_Encode(Password, GJP_KEY) << endl;

	cin.get();
	return 0;
}
