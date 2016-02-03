#include "simpleTOTP.h"

#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <string.h>

#define T0 0
#define TI 30
#define TOK_LEN 6

int32_t hotp(const uint8_t* K, const size_t Klen, uint64_t C, const int digits)
{
	uint8_t counter[8];
	for (int i = 8; i --> 0;)
	{
			counter[i] = C;
			C >>= 8;
	}

	uint8_t hash[SHA_DIGEST_LENGTH];
	HMAC(EVP_sha1(), K, Klen, counter, 8, hash, NULL);

	int offset = hash[SHA_DIGEST_LENGTH - 1] & 0x0F;

	uint32_t value = 0;
	for (int i = 0; i < 4; ++i)
	{
		value <<= 8;
		value |= hash[offset + i];
	}
	value &= 0x7FFFFFFF;

	static uint32_t pow10[10] =
	{
		1, 10, 100, 1000, 10000, 100000,
		1000000, 10000000, 100000000, 1000000000
	};

	return value % pow10[digits];
}

int32_t totp(const uint8_t* K, const size_t Klen, const time_t T, const int digits)
{
	uint64_t C = (T - T0) / TI;
	return hotp(K, Klen, C, digits);
}

bool verify_token(const uint8_t* K, const size_t Klen, const int32_t token, const int sync)
{
	time_t t = time(NULL);
	time_t now = mktime(gmtime(&t));

	if (totp(K, Klen, now, TOK_LEN) == token)
		return true;

	for (int i = 1; i <= sync; ++i)
		if (totp(K, Klen, now - (sync * TI), TOK_LEN) == token ||
			  totp(K, Klen, now + (sync * TI), TOK_LEN) == token)
			return true;
	return false;
}
