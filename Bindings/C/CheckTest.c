//C application that generates a pseudo check
#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Include/GDCrypto.h"

char* randomString(char* s)
{
	char const dict[] = "abcdefghijklmnopqrstuvwxyz123456789";

	srand(time(NULL));

	for (size_t i = 0; i < 5; i++)
		s[i] = dict[rand() % (sizeof(dict) - 1)];

	s[5] = '\0';
}

int randomNumber() { return rand(); }

int main()
{
	uint8_t* check_buffer;
	uint8_t* sha_buffer;
	size_t check_buffer_size;
	char itoaString[10];
	char randString[6];
	int randNum;

	void* generator = CheckGenerator_create(
		REWARDS_KEY, strlen(REWARDS_KEY),
		REWARDS_SALT, strlen(REWARDS_SALT));
	void* decoder = RobTopCipher_createDecoder(REWARDS_KEY, strlen(REWARDS_KEY));

	randomString(randString);
	randNum = randomNumber();

	sprintf(itoaString, "%d", randNum);

	CheckGenerator_insert(generator, (uint8_t*)randString, strlen(randString));
	CheckGenerator_insert(generator, (uint8_t*)(itoaString), strlen(itoaString));

	check_buffer = CheckGenerator_digest(generator, &check_buffer_size);

	RobTopCipher_insert(decoder, check_buffer, check_buffer_size);
	sha_buffer = RobTopCipher_digest(decoder, NULL);

	printf("String: %s\n", randString);
	printf("Number: %s\n", itoaString);
	printf("Raw data: %s%s%s\n", randString, itoaString, REWARDS_SALT);
	printf("SHA1: %s\n", sha_buffer);
	printf("Final check: %s\n", check_buffer);

	free(check_buffer);
	free(sha_buffer);
	RobTopCipher_destroy(decoder);
	CheckGenerator_destroy(generator);
	return 0;
}