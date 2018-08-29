#include "../include/gdcrypto.hpp"

std::string RobtopCipher_Encode(const char * Buffer, size_t Size, const std::string& Key)
{
	std::string tmp;

	for (unsigned int i = 0; i < Size; ++i)
		tmp += (Buffer[i] ^ Key[i % Key.length()]);

	return base64_encode(reinterpret_cast<const unsigned char*>(tmp.c_str()), tmp.length());
}

std::string RobtopCipher_Decode(const std::string& Buffer, const std::string& Key)
{
	size_t Size = 0;
	std::string Result = base64_decode(Buffer.c_str(), Buffer.length(), &Size);

	for (unsigned int i = 0; i < Size; ++i)
		Result[i] ^= Key[i % Key.length()];

	return Result;
}

//Add more chks dumbass
std::string GenerateCHK(ServerChecks Type, const std::vector<std::string>& Args)
{
	SHA1 sha;
	std::stringstream ss;
	std::string key;

	for (const auto & s : Args) 
		ss << s;

	switch (Type)
	{
	case LIKE_CHK:
	case RATE_LEVEL_CHK:
		key = std::string(LIKERATE_KEY);
		ss << "ysg6pUrtjn0J";
		break;
	case UPLOAD_COMMENT_CHK:
		key = std::string(COMMENT_KEY);
		ss << "xPT6iUrtws0J";
		break;
	case DOWNLOAD_LEVEL_CHK:
		key = std::string(LEVEL_KEY);
		ss << "xI25fpAapCQg";
		break;
	default:
		return std::string();
	}

	sha.update(ss.str());
	return RobtopCipher_Encode(sha.final().c_str(), sha.final().length(), key);
}

//Need tweaks
std::string DecodeSavegame(char * Src, size_t SizeIn)
{
	z_stream strm;
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	int have = 0;
	int input_data_left = 0;
	int chunk_size = 0;
	char buf[CHUNK];

	int state;
	std::string Decoded, Output;
	char * Buffer;
	std::size_t DecodedSize;

	for (unsigned int i = 0; i < SizeIn; ++i)
		Src[i] ^= 11;
	Decoded = base64_decode(Src, SizeIn, &DecodedSize);

	Buffer = (char*)calloc(1, DecodedSize);
	memcpy(Buffer, Decoded.data(), DecodedSize);
	Buffer += 10;
	DecodedSize -= 10;

	state = inflateInit2(&strm, -MAX_WBITS);

	//add state check

	input_data_left = DecodedSize;

	do 
	{
		chunk_size = CHUNK < input_data_left ? CHUNK : input_data_left;

		if (chunk_size <= 0)
			break;

		strm.next_in = (unsigned char*)Buffer;
		strm.avail_in = chunk_size;
		Buffer += chunk_size;
		input_data_left -= chunk_size;

		do {
			strm.next_out = (unsigned char*)buf;
			strm.avail_out = CHUNK;

			state = inflate(&strm, Z_NO_FLUSH);

			switch (state) 
			{
			case Z_NEED_DICT:
				state = Z_DATA_ERROR;
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
			case Z_STREAM_ERROR:
				inflateEnd(&strm);
				free(Buffer);
				return std::string();
			}

			have = (CHUNK - strm.avail_out);

			if (have > 0)
				Output.append((char*)buf, have);

		} while (strm.avail_out == 0);

	} while (state != Z_STREAM_END);

	inflateEnd(&strm);
	free(Buffer);
	return Output;
}
