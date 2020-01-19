//C application which encode/decode passwords
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Include/GDCrypto.h"

#define optionEncode "--encode"
#define optionDecode "--decode"

uint8_t* cipherWrapper(
	void* cipher,
	char const* s,
	size_t const len,
	size_t* buffer_size)
{
	uint8_t* buffer = NULL;

	if (!cipher)
	{
		printf("Cipher isn't initialized!\n");
		return NULL;
	}

	RobTopCipher_insert(cipher, s, len);
	//buffer_size can be NULL, if not needed
	buffer = RobTopCipher_digest(cipher, buffer_size);

	if (!buffer || 
		(buffer_size && !*buffer_size))
	{
		printf("Failed to digest the buffer!\n");
		return NULL;
	}

	return buffer;
}

int encode(char const* s, size_t const len)
{
	size_t buffer_size = 0;
	void* encoder = RobTopCipher_createEncoder(GJP_KEY, sizeof(GJP_KEY));

	uint8_t* buffer = cipherWrapper(encoder, s, len, &buffer_size);

	if (buffer && buffer_size)
	{
		printf("Encoded password: %s\n", buffer);
		printf("Encoded password size: %i\n", buffer_size);
		free(buffer);
	}

	RobTopCipher_destroy(encoder);
	return 0;
}

int decode(char const* s, size_t const len)
{
	size_t buffer_size = 0;
	void* decoder = RobTopCipher_createDecoder(GJP_KEY, sizeof(GJP_KEY));

	uint8_t* buffer = cipherWrapper(decoder, s, len, &buffer_size);

	if (buffer && buffer_size)
	{
		printf("Decoded password: %s\n", buffer);
		printf("Decoded password size: %i\n", buffer_size);
		free(buffer);
	}

	RobTopCipher_destroy(decoder);
	return 0;
}

int main(int argc, char** argv)
{
	printf("GD password encoder/decoder\n");

	if (argc > 2)
	{
		if (strcmp(argv[1], optionEncode) == 0)
			return encode(argv[2], strlen(argv[2]));
		else if (strcmp(argv[1], optionDecode) == 0)
			return decode(argv[2], strlen(argv[2]));
	}

	printf("Usage: %s [--encode|--decode] [password|gjp]\n", argv[0]);
	return 0;
}