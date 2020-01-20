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
#ifndef _GDCrypto_hpp
#define _GDCrypto_hpp

#include <cmath>
#include <vector>
#include <string>
#include <iostream>

namespace GDCrypto
{
	namespace Keys
	{
		/*
			GJP key
			Used to encode/decode GD passwords
		*/
		static std::vector<uint8_t> const GJP_KEY = { 0x33, 0x37, 0x35, 0x32, 0x36 };

		/*
			Message key
			Used to encode/decode messages
		*/
		static std::vector<uint8_t> const MESSAGE_KEY = { 0x31, 0x34, 0x32, 0x35, 0x31 };

		/*
			Level key
			Used when generating level checks in requests

			Level downloading check (chk): LevelID + Inc + RS + AccountID + UDID + UUID
			Level uploading check (seed2): levelSeed
			Generate "levelSeed" using the utility function
		*/
		static std::vector<uint8_t> const LEVEL_KEY = { 0x34, 0x31, 0x32, 0x37, 0x34 };

		/*
			Comment key
			Used when generating comment checks in requests

			Comment check (chk): Username + Comment + LevelID + Percentage +
			Comment Type (0 = Level, 1 = User)
		*/
		static std::vector<uint8_t> const COMMENT_KEY = { 0x32, 0x39, 0x34, 0x38, 0x31 };

		/*
			Challenges key
			Used when generating challenges checks in requests

			Challenges check (chk): 5 random chars + Random number
		*/
		static std::vector<uint8_t> const CHALLENGES_KEY = { 0x31, 0x39, 0x38, 0x34, 0x37 };

		/*
			Rewards key
			Used when generating rewards checks in requests

			Rewards check (chk): 5 random chars + Random number
		*/
		static std::vector<uint8_t> const REWARDS_KEY = { 0x35, 0x39, 0x31, 0x38, 0x32 };

		/*
			Like key
			Used when generating like checks in requests

			Like check (chk): Special + ItemID + Like + Type + RS + AccountID +
			UDID + UUID
		*/
		static std::vector<uint8_t> const LIKE_KEY = { 0x35, 0x38, 0x32, 0x38, 0x31 };

		/*
			Rate key
			Used when generating rate checks in requests

			Rate check (chk): LevelID + Stars + RS + AccountID + UDID + UUID
		*/
		static std::vector<uint8_t> const RATE_KEY = { 0x35, 0x38, 0x32, 0x38, 0x31 };

		/*
			Userscore key
			Used when generating userscore checks in requests

			Userscore check (seed2): AccountID + UserCoins + Demons + Stars +
			Coins + IconType + Icon + Diamonds + AccIcon + AccShip + AccBall +
			AccBird + AccDart + AccRobot + AccGlow + AccSpider + AccExplosion
		*/
		static std::vector<uint8_t> const USERSCORE_KEY = { 0x38, 0x35, 0x32, 0x37, 0x31 };

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
		static std::vector<uint8_t> const LEVELSCORE_KEY = { 0x33, 0x39, 0x36, 0x37, 0x33 };
	}

	namespace Salts
	{
		/*
			Level salt
			Used when generating level checks in requests
		*/
		static std::string const LEVEL_SALT("xI25fpAapCQg");

		/*
			Comment salt
			Used when generating comment checks in requests
		*/
		static std::string const COMMENT_SALT("xPT6iUrtws0J");

		/*
			Challenges salt
			Used when generating challenges checks in requests
		*/
		static std::string const CHALLENGES_SALT("");

		/*
			Rewards salt
			Used when generating rewards checks in requests
		*/
		static std::string const REWARDS_SALT("");

		/*
			Like salt
			Used when generating like checks in requests
		*/
		static std::string const LIKE_SALT("ysg6pUrtjn0J");

		/*
			Rate salt
			Used when generating rate checks in requests
		*/
		static std::string const RATE_SALT("ysg6pUrtjn0J");

		/*
			Userscore salt
			Used when generating userscore checks in requests
		*/
		static std::string const USERSCORE_SALT("xI35fsAapCRg");

		/*
			Levelscore salt
			Used when generating level leaderboard checks in requests
		*/
		static std::string const LEVELSCORE_SALT("yPg6pUrtWn0J");
	}

	namespace Utility
	{
		inline std::vector<uint8_t> stringToBuffer(std::string const& s)
		{
			return std::vector<uint8_t>(s.begin(), s.end());
		}

		inline std::string bufferToString(std::vector<uint8_t> const& buffer)
		{
			return std::string(buffer.begin(), buffer.end());
		}

		inline void xorWithKey(
			std::vector<uint8_t>& buffer,
			std::vector<uint8_t> const& key)
		{
			for (auto i = 0u; i < buffer.size(); ++i)
				buffer[i] ^= key[i % key.size()];
		}

		inline std::string levelSeed(const std::string& s)
		{
			std::string ret;

			if (s.size() < 49)
				return s;

			for (auto i = 0u; i < 50; ++i)
				ret += s[(s.size() / 50) * i];

			return ret;
		}

		inline long levelscoreSeed(
			unsigned long Jumps,
			unsigned long Percentage,
			unsigned long Seconds)
		{
			return 1482 +
				(Jumps + 3991) * (Percentage + 8354)
				+ std::pow(Seconds + 4085, 2) - 50028039;
		}
	}

	/*
		RobTopCipher

		The RobTop Cipher is a cipher widely used in Geometry Dash. It's the
		combination of the base64 (url safe) algorithm and the bitwise XOR
		operation, where every char of the result string is XORed with a
		character of the key (also a string).
	*/
	class RobTopCipher
	{
	public:
		typedef enum
		{
			ENCODE,
			DECODE,
		} CipherType;
	protected:
		std::vector<uint8_t> m_vBuffer;
		std::vector<uint8_t> m_vKey;
		CipherType m_eType;
	public:
		RobTopCipher(
			std::vector<uint8_t> const& key,
			CipherType const type)
			: m_vKey(key),
			m_eType(type) {}

		RobTopCipher& insert(std::vector<uint8_t> const& buffer);
		RobTopCipher& insert(std::string const& s);
		RobTopCipher& insert(std::istream& in);

		RobTopCipher& digest(std::vector<uint8_t>& buffer);
		RobTopCipher& digest(std::string& s);
		RobTopCipher& digest(std::ostream& out);

		std::string digestAsString()
		{
			std::string s;
			this->digest(s);
			return s;
		}

		RobTopCipher& operator<<(std::vector<uint8_t> const& obj) { return this->insert(obj); }
		RobTopCipher& operator<<(std::string const& s) { return this->insert(s); }
		RobTopCipher& operator<<(std::istream& in) { return this->insert(in); }

		RobTopCipher& operator>>(std::vector<uint8_t>& obj) { return this->digest(obj); }
		RobTopCipher& operator>>(std::string& s) { return this->digest(s); }
		RobTopCipher& operator>>(std::ostream& out) { return this->digest(out); }
	};

	class RobTopEncoder
		: public RobTopCipher
	{
	public:
		RobTopEncoder(std::vector<uint8_t> const& key)
			: RobTopCipher(key, RobTopCipher::ENCODE) {}
	};

	class RobTopDecoder
		: public RobTopCipher
	{
	public:
		RobTopDecoder(std::vector<uint8_t> const& key)
			: RobTopCipher(key, RobTopCipher::DECODE) {}
	};

	/*
		DataCipher

		This class is used to encode/decode data, like savegames or level strings.
		The algorithm used is deflate + base64 (url safe) for encoding, base64 +
		inflate for decoding. A XOR operation can be applied before of the algorithm.
	*/
	class DataCipher
	{
	public:
		typedef enum
		{
			ENCODE,
			DECODE
		} ManagerType;
	protected:
		std::vector<uint8_t> m_vBuffer;
		std::vector<uint8_t> m_vKey;
		ManagerType m_eType;
	public:
		DataCipher(ManagerType const type)
			: m_eType(type) {}
		DataCipher(
			std::vector<uint8_t> const& key,
			ManagerType const type)
			: m_vKey(key),
			m_eType(type) {}
		
		void enableXorWithKey(std::vector<uint8_t> const& key) { m_vKey = key; }
		void disableXor() { m_vKey.clear(); }

		DataCipher& insert(std::vector<uint8_t> const& buffer);
		DataCipher& insert(std::string const& s);
		DataCipher& insert(std::istream& in);

		DataCipher& digest(std::vector<uint8_t>& buffer);
		DataCipher& digest(std::string& s);
		DataCipher& digest(std::ostream& out);

		std::string digestAsString()
		{
			std::string s;
			this->digest(s);
			return s;
		}

		DataCipher& operator<<(std::vector<uint8_t> const& obj) { return this->insert(obj); }
		DataCipher& operator<<(std::string const& s) { return this->insert(s); }
		DataCipher& operator<<(std::istream& in) { return this->insert(in); }

		DataCipher& operator>>(std::vector<uint8_t>& obj) { return this->digest(obj); }
		DataCipher& operator>>(std::string& s) { return this->digest(s); }
		DataCipher& operator>>(std::ostream& out) { return this->digest(out); }
	};

	class LevelEncoder
		: public DataCipher
	{
	public:
		LevelEncoder()
			: DataCipher(DataCipher::ENCODE) {}

		void enableXorWithKey(std::vector<uint8_t> const& key) = delete;
		void disableXor() = delete;
	};

	class LevelDecoder
		: public DataCipher
	{
	public:
		LevelDecoder()
			: DataCipher(DataCipher::DECODE) {}

		void enableXorWithKey(std::vector<uint8_t> const& key) = delete;
		void disableXor() = delete;
	};

	class SavegameEncoder
		: public DataCipher
	{
	public:
		SavegameEncoder()
			: DataCipher({ 11 }, DataCipher::ENCODE) {}

		void enableXorWithKey(std::vector<uint8_t> const& key) = delete;
		void disableXor() = delete;
	};

	class SavegameDecoder
		: public DataCipher
	{
	public:
		SavegameDecoder()
			: DataCipher({ 11 }, DataCipher::DECODE) {}
		
		void enableXorWithKey(std::vector<uint8_t> const& key) = delete;
		void disableXor() = delete;
	};

	/*
		CheckGenerator
		
		Checks (chk, sometimes seed2) are encoded strings that contains data
		used by the server to validate requests. Every check is encoded in this way:
		Raw data -> SHA1 string -> RobTop Cipher (every check has a different key).
		The raw data is a combination of various values and a salt, which
		also differs between checks.
	*/
	class CheckGenerator
	{
	protected:
		std::vector<uint8_t> m_vBuffer;
		std::vector<uint8_t> m_vKey;
		std::string m_sSalt;
		std::vector<uint8_t> m_vLast;
	public:
		CheckGenerator(
			std::vector<uint8_t> const& key,
			std::string const& salt)
			: m_vKey(key),
			m_sSalt(salt) {}

		CheckGenerator& insert(std::vector<uint8_t> const& buffer);
		CheckGenerator& insert(std::string const& s);
		CheckGenerator& insert(std::istream& in);

		CheckGenerator& digest(std::vector<uint8_t>& buffer);
		CheckGenerator& digest(std::string& s);
		CheckGenerator& digest(std::ostream& out);

		std::string digestAsString()
		{
			std::string s;
			this->digest(s);
			return s;
		}

		CheckGenerator& operator<<(std::vector<uint8_t> const& obj) { return this->insert(obj); }
		CheckGenerator& operator<<(std::string const& s) { return this->insert(s); }
		CheckGenerator& operator<<(std::istream& in) { return this->insert(in); }

		CheckGenerator& operator>>(std::vector<uint8_t>& obj) { return this->digest(obj); }
		CheckGenerator& operator>>(std::string& s) { return this->digest(s); }
		CheckGenerator& operator>>(std::ostream& out) { return this->digest(out); }
	};
}

#endif /* _GDCrypto_hpp */