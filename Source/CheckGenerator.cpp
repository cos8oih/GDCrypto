#include "External/Sha1.hpp"

#include "GDCrypto/CheckGenerator.hpp"
#include "GDCrypto/RobTopCipher.hpp"

using namespace gdcrypto;

//CheckGenerator

void CheckGenerator::insert(std::vector<uint8_t> const& buffer)
{
	if (!m_Last.empty())
	{
		m_Buffer.insert(
			m_Buffer.end(),
			m_Last.begin(),
			m_Last.end());
	}

	m_Last = buffer;
}

void CheckGenerator::insert(std::string const& s)
{
	insert(std::vector<uint8_t>(s.begin(), s.end()));
}

void CheckGenerator::insert(std::istream& in)
{
	insert(std::vector<uint8_t>(std::istreambuf_iterator(in), {}));
}

void CheckGenerator::digest(std::vector<uint8_t>& buffer)
{
	SHA1 sha;
	RobTopCipher cipher(m_Key);

	buffer.clear();

	//Special case
	if (m_Key == gdcrypto::vecFromArray(keys::LEVELSCORE_KEY) &&
		m_Salt == salts::LEVELSCORE_SALT)
	{
		m_Buffer.insert(
			m_Buffer.end(),
			m_Salt.begin(),
			m_Salt.end());

		m_Buffer.insert(
			m_Buffer.end(),
			m_Last.begin(),
			m_Last.end());
	}
	else
	{
		m_Buffer.insert(
			m_Buffer.end(),
			m_Last.begin(),
			m_Last.end());

		m_Buffer.insert(
			m_Buffer.end(),
			m_Salt.begin(),
			m_Salt.end());
	}

	sha.update(gdcrypto::toString(m_Buffer));
	
	auto s = cipher.encode(sha.final());
	buffer.insert(buffer.begin(), s.begin(), s.end());

	m_Buffer.clear();
	m_Last.clear();
}

void CheckGenerator::digest(std::string& s)
{
	std::vector<uint8_t> buf;

	digest(buf);

	s = gdcrypto::toString(buf);
}

void CheckGenerator::digest(std::ostream& out)
{
	std::vector<uint8_t> buf;

	digest(buf);

	out.write(
		reinterpret_cast<char*>(buf.data()),
		buf.size());
}

std::string CheckGenerator::generate(
	std::vector<std::vector<uint8_t>> const& buffers)
{
	std::string s;

	for (auto const& buf : buffers)
		insert(buf);

	digest(s);
	return s;
}

std::string CheckGenerator::generate(
	std::vector<std::string> const& buffers)
{
	std::string s;

	for (auto const& buf : buffers)
		insert(buf);

	digest(s);
	return s;
}

//Operators

CheckGenerator& gdcrypto::operator<<(CheckGenerator& g, std::vector<uint8_t> const& buffer)
{
	g.insert(buffer);
	return g;
}

CheckGenerator& gdcrypto::operator<<(CheckGenerator& g, std::string const& s)
{
	g.insert(s);
	return g;
}

CheckGenerator& gdcrypto::operator<<(CheckGenerator& g, std::istream& in)
{
	g.insert(in);
	return g;
}

CheckGenerator& gdcrypto::operator>>(CheckGenerator& g, std::vector<uint8_t>& buffer)
{
	g.digest(buffer);
	return g;
}

CheckGenerator& gdcrypto::operator>>(CheckGenerator& g, std::string& s)
{
	g.digest(s);
	return g;
}

CheckGenerator& gdcrypto::operator>>(CheckGenerator& g, std::ostream& in)
{
	g.digest(in);
	return g;
}