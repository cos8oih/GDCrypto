#include "External/Zlib.hpp"
#include "External/Base64.hpp"
#include "External/Sha1.hpp"
#include "Include/GDCrypto.hpp"
#include "Include/GDCrypto.h"
#include <algorithm>

using namespace GDCrypto;

static std::vector<uint8_t> const NEW_LEVEL_HEADER = 
{ 
	0x48, 0x34, 0x73, 0x49, 0x41, 
	0x41, 0x41, 0x41, 0x41, 0x41
};
static auto const CHUNK_SIZE = 16384;

//Helpers

inline void appendBuffer(
	std::vector<uint8_t>& dst,
	std::vector<uint8_t> const& src)
{
	dst.reserve(dst.size() + src.size());
	dst.insert(dst.end(), src.begin(), src.end());
}

inline std::vector<uint8_t> streamToBuffer(std::istream& in)
{
	return std::vector<uint8_t>(std::istreambuf_iterator<char>(in), {});
}

inline void writeToStream(
	std::ostream& out,
	std::vector<uint8_t> const& buffer)
{
	out.write(reinterpret_cast<const char*>(
		buffer.data()), buffer.size());
}

inline std::vector<uint8_t> dataToBuffer(
	uint8_t const* p,
	size_t const size)
{
	return std::vector<uint8_t>(p, p + size);
}

uint8_t* bufferToData(std::vector<uint8_t> const& src)
{
	auto p = reinterpret_cast<uint8_t*>(std::malloc(src.size() + 1));

	if (p)
	{
		std::memcpy(p, src.data(), src.size());
		p[src.size()] = '\0';
	}

	return p;
}

void inflateBuffer(std::vector<uint8_t>& buf, bool newLevelData)
{
	z_stream stream = {};
	std::vector<uint8_t> out;

	auto buffer = new uint8_t[CHUNK_SIZE];
	size_t dataLeft = buf.size();

	stream.next_in = buf.data();

	auto state = inflateInit2(&stream,
		newLevelData ? -MAX_WBITS : MAX_WBITS);

	if (state != Z_OK)
		return;

	while (state != Z_STREAM_END)
	{
		stream.next_in += stream.avail_in;
		stream.avail_in = CHUNK_SIZE < dataLeft ? CHUNK_SIZE : dataLeft;

		if (stream.avail_in <= 0)
			return;

		dataLeft -= stream.avail_in;

		do
		{
			stream.avail_out = CHUNK_SIZE;
			stream.next_out = buffer;

			state = inflate(&stream, Z_NO_FLUSH);

			if (state != Z_OK &&
				state != Z_STREAM_END)
				break;

			auto bufferSize = CHUNK_SIZE - stream.avail_out;

			if (bufferSize)
				appendBuffer(out, dataToBuffer(buffer, bufferSize));

		} while (!stream.avail_out);
	};

	inflateEnd(&stream);
	delete[] buffer;
	buf = out;
}

void deflateBuffer(std::vector<uint8_t>& buf)
{
	z_stream stream = {};
	std::vector<uint8_t> out;

	auto buffer = new uint8_t[CHUNK_SIZE];
	size_t dataLeft = buf.size();

	stream.next_in = buf.data();

	auto state = deflateInit2(
		&stream,
		Z_DEFAULT_COMPRESSION,
		Z_DEFLATED,
		31,
		8,
		Z_DEFAULT_STRATEGY);

	if (state != Z_OK)
		return;

	while (state != Z_STREAM_END)
	{
		stream.next_in += stream.avail_in;
		stream.avail_in = CHUNK_SIZE < dataLeft ? CHUNK_SIZE : dataLeft;

		if (stream.avail_in <= 0)
			return;

		dataLeft -= stream.avail_in;

		do
		{
			stream.avail_out = CHUNK_SIZE;
			stream.next_out = buffer;

			if (dataLeft)
				state = deflate(&stream, Z_NO_FLUSH);
			else
				state = deflate(&stream, Z_FINISH);

			if (state != Z_OK &&
				state != Z_STREAM_END)
				break;

			auto bufferSize = CHUNK_SIZE - stream.avail_out;

			if (bufferSize)
				appendBuffer(out, dataToBuffer(buffer, bufferSize));

		} while (!stream.avail_out);
	}

	deflateEnd(&stream);
	delete[] buffer;
	buf = out;
}

//RobTopCipher

RobTopCipher& RobTopCipher::insert(std::vector<uint8_t> const& buffer)
{
	appendBuffer(m_vBuffer, buffer);
	return *this;
}

RobTopCipher& RobTopCipher::insert(std::string const& s)
{
	appendBuffer(m_vBuffer, Utility::stringToBuffer(s));
	return *this;
}

RobTopCipher& RobTopCipher::insert(std::istream& in)
{
	appendBuffer(m_vBuffer, streamToBuffer(in));
	return *this;
}

RobTopCipher& RobTopCipher::digest(std::vector<uint8_t>& buffer)
{
	buffer.clear();
	buffer = m_vBuffer;

	if (m_eType == RobTopCipher::ENCODE)
	{
		Utility::xorWithKey(buffer, m_vKey);
		buffer = Base64::encode(buffer);
	}
	else if (m_eType == RobTopCipher::DECODE)
	{
		buffer = Base64::decode(buffer);
		Utility::xorWithKey(buffer, m_vKey);
	}

	return *this;
}

RobTopCipher& RobTopCipher::digest(std::string& s)
{
	std::vector<uint8_t> buffer;

	digest(buffer);
	s = Utility::bufferToString(buffer);

	return *this;
}

RobTopCipher& RobTopCipher::digest(std::ostream& out)
{
	std::vector<uint8_t> buffer;

	digest(buffer);
	writeToStream(out, buffer);

	return *this;
}

//RobTopCipher (C bindings)

void* RobTopCipher_create(
	uint8_t const* key,
	size_t const size,
	RobTopCipher::CipherType type)
{
	if (key && size)
		return reinterpret_cast<void*>(
			new RobTopCipher(
				std::vector<uint8_t>(key, key + size), type));

	return NULL;
}

void* RobTopCipher_createEncoder(uint8_t const* key, size_t const size)
{
	return RobTopCipher_create(key, size, RobTopCipher::ENCODE);
}

void* RobTopCipher_createDecoder(uint8_t const* key, size_t const size)
{
	return RobTopCipher_create(key, size, RobTopCipher::DECODE);
}

void RobTopCipher_destroy(void* cipher)
{ 
	if (cipher)
		delete reinterpret_cast<RobTopCipher*>(cipher);
}

void RobTopCipher_insert(void* pcipher, uint8_t const* buffer, size_t const size)
{
	if (pcipher && buffer && size)
	{
		auto cipher = reinterpret_cast<RobTopCipher*>(pcipher);
		std::vector<uint8_t> buf(buffer, buffer + size);

		cipher->insert(buf);
	}
}

uint8_t const* RobTopCipher_digest(void* pcipher, size_t* size)
{
	if (pcipher)
	{
		auto cipher = reinterpret_cast<RobTopCipher*>(pcipher);
		std::vector<uint8_t> buf;

		cipher->digest(buf);

		auto p = bufferToData(buf);
		
		if (p)
		{
			if (size) *size = buf.size();
			return p;
		}
	}

	return NULL;
}

//DataCipher

DataCipher& DataCipher::insert(std::vector<uint8_t> const& buffer)
{
	appendBuffer(m_vBuffer, buffer);
	return *this;
}

DataCipher& DataCipher::insert(std::string const& s)
{
	appendBuffer(m_vBuffer, Utility::stringToBuffer(s));
	return *this;
}

DataCipher& DataCipher::insert(std::istream& in)
{
	appendBuffer(m_vBuffer, streamToBuffer(in));
	return *this;
}

DataCipher& DataCipher::digest(std::vector<uint8_t>& buffer)
{
	buffer.clear();
	buffer = m_vBuffer;

	if (m_eType == ENCODE)
	{
		deflateBuffer(buffer);
		buffer = Base64::encode(buffer);

		if (!m_vKey.empty())
			Utility::xorWithKey(buffer, m_vKey);
	}
	else if (m_eType == DECODE)
	{
		if (!m_vKey.empty())
			Utility::xorWithKey(buffer, m_vKey);

		//Check if new encoding
		if (std::search(
			buffer.begin(),
			buffer.end(),
			NEW_LEVEL_HEADER.begin(),
			NEW_LEVEL_HEADER.end())
			== buffer.begin())
		{
			buffer = Base64::decode(buffer);
			buffer.erase(buffer.begin(), buffer.begin() + 10);
			inflateBuffer(buffer, true);
		}
		else
		{
			buffer = Base64::decode(buffer);
			inflateBuffer(buffer, false);
		}
	}

	return *this;
}

DataCipher& DataCipher::digest(std::string& s)
{
	std::vector<uint8_t> buffer;

	this->digest(buffer);

	s = Utility::bufferToString(buffer);
	return *this;
}

DataCipher& DataCipher::digest(std::ostream& out)
{
	std::vector<uint8_t> buffer;

	this->digest(buffer);

	writeToStream(out, buffer);
	return *this;
}

//DataCipher (C bindings)

//CheckGenerator

CheckGenerator& CheckGenerator::insert(std::vector<std::uint8_t> const& buffer)
{
	if (!m_vLast.empty())
		appendBuffer(m_vBuffer, m_vLast);

	m_vLast = buffer;
	return *this;
}

CheckGenerator& CheckGenerator::insert(std::string const& s)
{
	if (!m_vLast.empty())
		appendBuffer(m_vBuffer, m_vLast);

	m_vLast = Utility::stringToBuffer(s);
	return *this;
}

CheckGenerator& CheckGenerator::insert(std::istream& in)
{
	if (!m_vLast.empty())
		appendBuffer(m_vBuffer, m_vLast);

	m_vLast = streamToBuffer(in);
	return *this;
}

CheckGenerator& CheckGenerator::digest(std::vector<std::uint8_t>& buffer)
{
	SHA1 sha;
	RobTopEncoder encoder(m_vKey);

	buffer.clear();

	//Special case
	if (m_vKey == Keys::LEVELSCORE_KEY &&
		m_sSalt == Salts::LEVELSCORE_SALT)
	{
		appendBuffer(m_vBuffer, Utility::stringToBuffer(m_sSalt));
		appendBuffer(m_vBuffer, m_vLast);
	}
	else
	{
		appendBuffer(m_vBuffer, m_vLast);
		appendBuffer(m_vBuffer, Utility::stringToBuffer(m_sSalt));
	}

	sha.update(std::string(m_vBuffer.begin(), m_vBuffer.end()));
	encoder.insert(sha.final()).digest(buffer);

	return *this;
}

CheckGenerator& CheckGenerator::digest(std::string& s)
{
	std::vector<uint8_t> buffer;

	this->digest(buffer);

	s = Utility::bufferToString(buffer);
	return *this;
}

CheckGenerator& CheckGenerator::digest(std::ostream& out)
{
	std::vector<uint8_t> buffer;

	this->digest(buffer);

	writeToStream(out, buffer);
	return *this;
}

//CheckGenerator (C bindings)

void* CheckGenerator_create(
	uint8_t const* key, size_t const key_size,
	char const* salt, size_t const salt_size)
{
	if (key && key_size && salt)
		return reinterpret_cast<void*>(
			new CheckGenerator(
				dataToBuffer(key, key_size),
				std::string(salt, salt_size)));

	return NULL;
}

void CheckGenerator_destroy(void* chkgen)
{
	if (chkgen)
		delete reinterpret_cast<CheckGenerator*>(chkgen);
}

void CheckGenerator_insert(void* chkgen, uint8_t const* buffer, size_t const size)
{
	if (chkgen && buffer && size)
	{
		auto generator = reinterpret_cast<CheckGenerator*>(chkgen);
		std::vector<uint8_t> buf(buffer, buffer + size);

		generator->insert(buf);
	}
}

uint8_t const* CheckGenerator_digest(void* chkgen, size_t* size)
{
	if (chkgen)
	{
		auto generator = reinterpret_cast<CheckGenerator*>(chkgen);
		std::vector<uint8_t> buf;

		generator->digest(buf);

		auto p = bufferToData(buf);

		if (p)
		{
			if (size) *size = buf.size();
			return p;
		}
	}

	return NULL;
}