#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>

int32_t hotp(const uint8_t* K, const size_t Klen, const uint64_t C, const int digits);
int32_t totp(const uint8_t* K, const size_t Klen, const time_t T, const int digits);
bool verify_token(const uint8_t* key, const size_t Klen, const int32_t offset, const int digits);
