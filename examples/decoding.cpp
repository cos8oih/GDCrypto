#include "include/gdcrypto.hpp"

using namespace std;

int main()
{
	string encPwd("fk5lU0VAQFpAUgIFBg==");
	vector<unsigned char> decPwd = RobtopCipher_Decode(encPwd, GJP_KEY);
	string decPwdS(decPwd.begin(), decPwd.end());
  
	cout << "Encoded Password: " << encPwd << endl;
	cout << "Decoded Password: " << decPwdS << endl;
  
  	cin.get();
  	return 0;
}
