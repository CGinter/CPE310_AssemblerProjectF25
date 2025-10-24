/**
 * @file util.c
 * @brief
 * @author Chase Sprigle
 * @date 10/23/2025
 */
#include "include.h"

uint32_t bin_to_num(char *binary)
{
	uint32_t num = 0;

	while (*binary != '\0') {
		num <<= 1;
		if (*binary == '1')
			num |= 1;
		binary++;
	}

	return num;
}
