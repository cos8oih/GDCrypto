#include "../include/gdcrypto.hpp"

std::string RobtopCipher_Encode(
	const std::vector<unsigned char>& Buffer,
	const std::string& Key)
{
	std::vector<unsigned char> tmp;

	for (auto i = 0; i < Buffer.size(); ++i)
		tmp.push_back(Buffer[i] ^ Key[i % Key.length()]);

	return Base64_Encode(tmp);
}

std::vector<unsigned char> RobtopCipher_Decode(
	const std::string& Buffer,
	const std::string& Key)
{
	std::vector<unsigned char> Result = Base64_Decode(Buffer);

	for (auto i = 0; i < Result.size(); ++i)
		Result[i] ^= Key[i % Key.length()];

	return Result;
}

//Add more chks
std::string GenerateCHK(ServerChecks Type, const std::vector<std::string>& Args)
{
	SHA1 sha;
	std::stringstream ss;
	std::string key, final;

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
	final = sha.final();
	return RobtopCipher_Encode(std::vector<unsigned char>(final.begin(), final.end()), key);
}

std::string DecodeSavegame(
	const std::vector<unsigned char>& Src)
{
	z_stream Strm;
	Strm.zalloc = Z_NULL;
	Strm.zfree = Z_NULL;
	Strm.opaque = Z_NULL;
	Strm.avail_in = 0;
	Strm.next_in = Z_NULL;
	int State = 0, Have = 0, DataLeft = 0, ChunkSize = 0;
	char Buf[CHUNK];
	unsigned char * P;
	std::vector<unsigned char> Buffer(Src);
	std::string Output;

	for (auto i = 0; i < Buffer.size(); ++i)
		Buffer[i] ^= 11;
	Buffer = Base64_Decode(std::string(Buffer.begin(), Buffer.end()));
	Buffer.erase(Buffer.begin(), Buffer.begin() + 10);
	P = Buffer.data();
	DataLeft = Buffer.size();

	State = inflateInit2(&Strm, -MAX_WBITS);
	if (State != Z_OK) return std::string();

	do 
	{
		ChunkSize = CHUNK < DataLeft ? CHUNK : DataLeft;
		if (ChunkSize <= 0) break;
		Strm.next_in = P;
		P += ChunkSize;
		Strm.avail_in = ChunkSize;
		DataLeft -= ChunkSize;

		do {
			Strm.next_out = reinterpret_cast<unsigned char*>(Buf);
			Strm.avail_out = CHUNK;

			State = inflate(&Strm, Z_NO_FLUSH);

			switch (State) 
			{
			case Z_NEED_DICT:
				State = Z_DATA_ERROR;
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
			case Z_STREAM_ERROR:
				inflateEnd(&Strm);
				return std::string();
			}

			Have = (CHUNK - Strm.avail_out);
			if (Have > 0) Output.append(Buf, Have);

		} while (Strm.avail_out == 0);

	} while (State != Z_STREAM_END);

	inflateEnd(&Strm);
	return Output;
}
