/*
	MIT License

	Copyright (c) 2020 Cos8o

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
#ifndef _GDCrypto_h
#define _GDCrypto_h

#include <stdint.h>

//Xor keys

#define GJP_KEY			"37526"
#define MESSAGE_KEY		"14251"
#define LEVEL_KEY		"41274"
#define COMMENT_KEY		"29481"
#define CHALLENGES_KEY	"19847"
#define REWARDS_KEY		"59182"
#define LIKE_KEY		"58281"
#define RATE_KEY		"58281"
#define USERSCORE_KEY	"85271"
#define LEVELSCORE_KEY	"39673"

//Salts

#define LEVEL_SALT		"xI25fpAapCQg"
#define COMMENT_SALT	"xPT6iUrtws0J"
#define CHALLENGES_SALT	""
#define REWARDS_SALT	""
#define LIKERATE_SALT	"ysg6pUrtjn0J"
#define USERSCORE_SALT	"xI35fsAapCRg"
#define LEVELSCORE_SALT	"yPg6pUrtWn0J"

//RobTopCipher

void* RobTopCipher_createEncoder(char const* key, size_t const key_size);
void* RobTopCipher_createDecoder(char const* key, size_t const key_size);
void RobTopCipher_destroy(void* cipher);

void RobTopCipher_insert(void* cipher, uint8_t const* buffer, size_t const size);
uint8_t const* RobTopCipher_digest(void* cipher, size_t* size);

//DataCipher



//CheckGenerator

void* CheckGenerator_create(
	char const* key, size_t const key_size,
	char const* salt, size_t const salt_size);
void CheckGenerator_destroy(void* chkgen);

void CheckGenerator_insert(void* chkgen, uint8_t const* buffer, size_t const size);
uint8_t const* CheckGenerator_digest(void* chkgen, size_t* size);

#endif /* _GDCrypto_h */
