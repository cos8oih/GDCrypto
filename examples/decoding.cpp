include "include/gdcrypto.hpp"
#include <cassert>

using namespace std;

int main()
{
	vector<unsigned char> pass = RobtopCipher_Decode("fk5lU0VAQFpAUgIFBg==", GJP_KEY);
	assert(string(pass.begin(), pass.end()) == "MyPassword123");
	return 0;
}
