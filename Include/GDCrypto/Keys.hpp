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
#ifndef _GDCRYPTO_KEYS_HPP
#define _GDCRYPTO_KEYS_HPP

#include <array>

namespace gdcrypto
{
	namespace keys
	{
		/*
			Null key
			Does not affect the data
		*/
		static std::array<std::uint8_t, 1> const NULL_KEY = { 0x00 };

		/*
			Savegame key
			Used to encode/decode savegames
		*/
		static std::array<std::uint8_t, 1> const SAVEGAME_KEY = { 0x0B };

		/*
			GJP key
			Used to encode/decode passwords
		*/
		static std::array<std::uint8_t, 5> const GJP_KEY = { 0x33, 0x37, 0x35, 0x32, 0x36 };

		/*
			Message key
			Used to encode/decode messages
		*/
		static std::array<std::uint8_t, 5> const MESSAGE_KEY = { 0x31, 0x34, 0x32, 0x35, 0x31 };

		/*
			Level key
			Used when generating level checks in requests

			Level downloading check (chk): LevelID + Inc + RS + AccountID + UDID + UUID
			Level uploading check (seed2): levelSeed
			Generate "levelSeed" using the utility function
		*/
		static std::array<std::uint8_t, 5> const LEVEL_KEY = { 0x34, 0x31, 0x32, 0x37, 0x34 };

		/*
			Comment key
			Used when generating comment checks in requests

			Comment check (chk): Username + Comment + LevelID + Percentage +
			Comment Type (0 = Level, 1 = User)
		*/
		static std::array<std::uint8_t, 5> const COMMENT_KEY = { 0x32, 0x39, 0x34, 0x38, 0x31 };

		/*
			Challenges key
			Used when generating challenges checks in requests

			Challenges check (chk): 5 random chars + Random number
		*/
		static std::array<std::uint8_t, 5> const CHALLENGES_KEY = { 0x31, 0x39, 0x38, 0x34, 0x37 };

		/*
			Rewards key
			Used when generating rewards checks in requests

			Rewards check (chk): 5 random chars + Random number
		*/
		static std::array<std::uint8_t, 5> const REWARDS_KEY = { 0x35, 0x39, 0x31, 0x38, 0x32 };

		/*
			Like key
			Used when generating like checks in requests

			Like check (chk): Special + ItemID + Like + Type + RS + AccountID +
			UDID + UUID
		*/
		static std::array<std::uint8_t, 5> const LIKE_KEY = { 0x35, 0x38, 0x32, 0x38, 0x31 };

		/*
			Rate key
			Used when generating rate checks in requests

			Rate check (chk): LevelID + Stars + RS + AccountID + UDID + UUID
		*/
		static std::array<std::uint8_t, 5> const RATE_KEY = { 0x35, 0x38, 0x32, 0x38, 0x31 };

		/*
			Userscore key
			Used when generating userscore checks in requests

			Userscore check (seed2): AccountID + UserCoins + Demons + Stars +
			Coins + IconType + Icon + Diamonds + AccIcon + AccShip + AccBall +
			AccBird + AccDart + AccRobot + AccGlow + AccSpider + AccExplosion
		*/
		static std::array<std::uint8_t, 5> const USERSCORE_KEY = { 0x38, 0x35, 0x32, 0x37, 0x31 };

		/*
			Levelscore key
			Used when generating checks for the level leaderboards

			Userscore check (chk): AccountID + LevelID + Percentage + Seconds +
			Jumps + Attempts + levelscoreSeed + Bests Differences + UNKNOWN (always 1)
			+ UserCoins + DailyID + Seed7 ("s7" from packet)
			Seconds = seconds taken to reach the best
			Jumps = jumps taken to reach the best
			Bests Differences = differences between bests, ex: 0% - 65% - 100% -> (65 - 0), (100 - 65) -> 65,35
			Generate "levelscoreSeed" using the utility function
		*/
		static std::array<std::uint8_t, 5> const LEVELSCORE_KEY = { 0x33, 0x39, 0x36, 0x37, 0x33 };
	}
}

#endif /* _GDCRYPTO_KEYS_HPP */