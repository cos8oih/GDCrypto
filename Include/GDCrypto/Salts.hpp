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
#ifndef _GDCRYPTO_SALTS_HPP
#define _GDCRYPTO_SALTS_HPP

#include <string>

namespace gdcrypto
{
	namespace salts
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
}

#endif /* _GDCRYPTO_SALTS_HPP */