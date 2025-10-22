#include "include.h"

const uint32_t UNDEFINED;

const struct instruction_definition instruction_definitions[] = {
	{
		"ADD",
		R_TYPE,
		"000000",
		"100000",
		{ RD, RS, RT, EMPTY }
	}
};
