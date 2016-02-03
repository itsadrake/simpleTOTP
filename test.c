#include "simpleTOTP.h"

#include <stdio.h>
#include <string.h>

int main()
{
	uint8_t* keys[] = {"12345678901234567890"};
	uint64_t times[] =
	{
		59, 1111111109, 1111111111,
		1234567890, 2000000000,
		20000000000
	};
	uint32_t solutions[][sizeof(keys) / sizeof(keys[0])] =
	{
		{94287082},
		{ 7081804},
		{14050471},
		{89005924},
		{69279037},
		{65353130}
	};
	for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); ++i)
	{
		for (int j = 0; j < sizeof(times) / sizeof(times[0]); ++j)
		{
			int32_t token = totp(keys[i], strlen(keys[i]), times[j], 8);
			printf("%20s %11lu %8d %8d => ", keys[i], times[j], solutions[j][i], token);
			if (token == solutions[j][i])
				printf("pass\n");
			else
				printf("fail\n");
		}
	}
}
