/**
 * @file consts.c
 * @authors Chase Sprigle and Victoria Marston
 * @date 10/23/25
 */
#include "include.h"

//Chase Sprigle Start
const uint32_t UNDEFINED;

const uint32_t MAX_5_BIT = 31;
const uint32_t MAX_6_BIT = 63;
const uint32_t MAX_16_BIT = 65535;
const uint32_t MAX_26_BIT = 67108863;

const struct instruction_definition instruction_definitions[] = {
	{
		"ADD",
		R_TYPE,
		"000000",
		"100000",
		{ RD, RS, RT, EMPTY }
	},
	{
		"DIV",
		R_TYPE,
		"000000",
		"011010",
		{ RS, RT, EMPTY, EMPTY }
	}
	//Chase Sprigle End
	//Victoria Marston Start
	{
		"ADDU",
		R_Type,
		"000000",
		"100001",
		{ RD, RS, RT, EMPTY }
	},
	{
		"AND",
		R_Type,
		"000000",
		"100100",
		{ RD, RS, RT, EMPTY }
	},
	{
		"DIVU",
		R_Type,
		"000000",
		"011011",
		{ EMPTY, RS, RT, EMPTY }
	},
	{
		"JALR",
		R_Type,
		"000000",
		"001001",
		{ RD, RS, EMPTY, EMPTY }
	},
	{
		"JR",
		R_Type,
		"000000",
		"001000",
		{ EMPTY, RS, EMPTY, EMPTY }
	},
	{
		"MFHI",
		R_Type,
		"000000".
		"010000",
		{ RD, EMPTY, EMPTY, EMPTY }
	},
	{
		"MFLO",
		R_Type,
		"000000",
		"010010",
		{RD, EMPTY, EMPTY, EMPTY }
	},
	{
		"MTHI",
		R_Type,
		"000000",
		"010001",
		{ EMPTY, RS, EMPTY, EMPTY }
	},
	{
		"MTLO",
		R_Type,
		"000000",
		"010011",
		{ EMPTY, RS, EMPTY, EMPTY }
	},
	{
		"MULT",
		R_Type,
		"000000",
		"011000",
		{ EMPTY, RS, RT, EMPTY}
	},
	{
		"MULTU",
		R_Type,
		"000000",
		"011001",
		{ EMPTY, RS, RT, EMPTY }
	},
	{
		"NOR",
		R_Type,
		"000000",
		"100111",
		{ RD, RS, RT, EMPTY }
	},
	{
		"OR",
		R_Type,
		"000000",
		"100101",
		{ RD, RS, RT, EMPTY }
	},
	{
		"SLL",
		R_Type,
		"000000",
		"000000",
		{ RD, EMPTY, RT, SA }
	},
	{
		"SLLV",
		R_Type,
		"000000",
		"000100",
		{ RD, EMPTY, RT, RS }
	},
	{
		"SLT",
		R_Type,
		"000000",
		"101010",
		{ RD, RS, RT, EMPTY }
	},
	{
		
	}
};
