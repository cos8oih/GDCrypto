#include "../include/base64.hpp"

static const unsigned char base64_table[65] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

static const int B64index[256] = { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62, 63, 62, 62, 63, 52, 53, 54, 55,
56, 57, 58, 59, 60, 61,  0,  0,  0,  0,  0,  0,  0,  0,  1,  2,  3,  4,  5,  6,
7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,  0,
0,  0,  0, 63,  0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 };

std::string Base64_Encode(const std::vector<unsigned char>& Src)
{
	std::string Result;
	auto In = Src.begin();

	while (Src.end() - In >= 3) 
	{
		Result += base64_table[In[0] >> 2];
		Result += base64_table[((In[0] & 0x03) << 4) | (In[1] >> 4)];
		Result += base64_table[((In[1] & 0x0f) << 2) | (In[2] >> 6)];
		Result += base64_table[In[2] & 0x3f];
		In += 3;
	}

	if (Src.end() - In) 
	{
		Result += base64_table[In[0] >> 2];
		if (Src.end() - In == 1) {
			Result += base64_table[(In[0] & 0x03) << 4];
			Result += '=';
		}
		else 
		{
			Result += base64_table[((In[0] & 0x03) << 4) |
				(In[1] >> 4)];
			Result += base64_table[(In[1] & 0x0f) << 2];
		}
		Result += '=';
	}

	return Result;
}

std::vector<unsigned char> Base64_Decode(const std::string& Src)
{
	int Pad = Src.length() > 0 && (Src.length() % 4 || Src[Src.length() - 1] == '=');
	const size_t L = ((Src.length() + 3) / 4 - Pad) * 4;
	std::vector<unsigned char> Result;

	for (size_t i = 0; i < L; i += 4)
	{
		int n = B64index[Src[i]] << 18 | B64index[Src[i + 1]] << 12 | B64index[Src[i + 2]] << 6 | B64index[Src[i + 3]];
		Result.push_back(n >> 16);
		Result.push_back(n >> 8 & 0xFF);
		Result.push_back(n & 0xFF);
	}
	if (Pad)
	{
		int n = B64index[Src[L]] << 18 | B64index[Src[L + 1]] << 12;
		Result.push_back(n >> 16);

		if (Src.length() > L + 2 && Src[L + 2] != '=')
		{
			n |= B64index[Src[L + 2]] << 6;
			Result.push_back(n >> 8 & 0xFF);
		}
	}

	return Result;
}
