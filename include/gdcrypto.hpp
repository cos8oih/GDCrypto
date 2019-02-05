#ifndef _gdcrypto_hpp
#define _gdcrypto_hpp

#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "base64.hpp"
#include "sha1.hpp"
#include "zlib/zlib.h"

//General XOR keys, used for various reasons

/*
	Use this key to encode/decode passwords
*/
const auto GJP_KEY = "37526";
/*
	Use this key to encode/decode the body of your messages
*/
const auto MESSAGE_KEY = "14251";
/*
	CHK values (download): LevelID, Inc, RS, AccountID, UDID, UUID
	CHK values (upload): Seed
	generate it using the function "GenerateLevelUploadSeed()"
*/
const auto LEVEL_KEY = "41274";
/*
	CHK values: Username, Comment, LevelID, Percentage, Comment Type (0 = Level, 1 = User)
*/
const auto COMMENT_KEY = "29481";
/*
	CHK values: Random[5], Random Number
*/
const auto CHALLENGES_KEY = "19847";
/*
	CHK values: Random[5], Random Number
*/
const auto REWARDS_KEY = "59182";
/*
	CHK values (like): Special, ItemID, Like, Type, RS, AccountID, UDID, UUID
	CHK values (rate): LevelID, Stars, RS, AccountID, UDID, UUID
*/
const auto LIKERATE_KEY = "58281";
/*
	CHK values: AccountID, UserCoins, Demons, Stars, Coins, IconType, Icon, Diamonds, AccIcon, AccShip, AccBall, AccBird, AccDart, AccRobot, AccGlow, AccSpider, AccExplosion
*/
const auto USERSCORE_KEY = "85271";
/*
	CHK values: AccountID, LevelID, Percentage, Seconds, Jumps, Attempts, Seed, Bests Differences, UNKNOWN (always 1), UserCoins, DailyID, Seed7 ("s7" from packet)
	Seconds = seconds taken to reach the best
	Jumps = jumps taken to reach the best
	Bests Differences = differences between bests, ex: 0% - 65% - 100% -> (65 - 0), (100 - 65) -> 65,35
	Generate Seed using the function "GenerateLevelLeaderboardSeed()"
*/
const auto LEVELSCORE_KEY = "39673";

//CHKs salts

const auto LEVEL_SALT = "xI25fpAapCQg";
const auto COMMENT_SALT = "xPT6iUrtws0J";
const auto CHALLENGES_SALT = "";
const auto REWARDS_SALT = "";
const auto LIKERATE_SALT = "ysg6pUrtjn0J";
const auto USERSCORE_SALT = "xI35fsAapCRg";
const auto LEVELSCORE_SALT = "yPg6pUrtWn0J";

/*  
	Function: RobtopCipher_Encode()

	@Buffer: the data to be encoded
	@Key: seed used by the algorithm

	Returns: the encoded data on success,
	an empty string on failure.
*/
std::string RobtopCipher_Encode(
	const std::vector<unsigned char>& Buffer,
	const std::string& Key);

/*
	Function: RobtopCipher_Decode()

	@Buffer: the data to be decoded
	@Key: seed used by the algorithm

	Returns: the decoded data on success,
	an empty string on failure.
*/
std::vector<unsigned char> RobtopCipher_Decode(
	const std::string& Buffer, 
	const std::string& Key);

/*
	Function: GenerateLevelUploadSeed()

	@Buffer: the level string

	Returns: the seed generated from the level string.
*/
std::string GenerateLevelUploadSeed(
	const std::string& LevelString);

/*
	Function: GenerateLevelLeaderboardSeed()

	@Jumps: jumps taken to reach the best
	@Percentage: your best 
	@Seconds: seconds taken to reach the best

	Returns: seed used by the level leaderboard CHK.
*/
long GenerateLevelLeaderboardSeed(
	unsigned long Jumps,
	unsigned long Percentage,
	unsigned long Seconds);

/*
	About CHKs
	CHKs are encoded strings that contains data used by the server to validate requests.
	Every CHK is encoded in this way:
	Raw data -> SHA1 string -> xor (every CHK has a different key) -> base64
	The raw data is a combination of various values and a salt, which also differ between CHKs.
*/

/*
	Function: GenerateCHK()

	@Key: seed used by the algorithm
	@Values: Values needed for the CHK to be built
	@Salt: salt used by the algorithm

	Returns: the CHK on success,
	random corrupted data on failure.
*/
std::string GenerateCHK(
	const std::string& Key,
	const std::vector<std::string>& Values,
	const std::string& Salt);

/*
	Function: DecodeSavegame()

	@Src: the savegame data to be decoded

	Returns: the decoded data on success,
	an empty string on failure.
*/
std::string DecodeSavegame(
	const std::vector<unsigned char>& Src);

#endif
