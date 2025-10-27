/**
 * @file consts.c
 * @brief Constants used throughout codebase.
 * @authors Chase Sprigle, Rachel Ogbonna, and Victoria Marston
 * @date 10/23/25
 */
#include "include.h"

//Chase Sprigle Start
const uint32_t UNDEFINED;

const uint32_t MAX_5_BIT = 31;
const uint32_t MAX_6_BIT = 63;
const uint32_t MAX_16_BIT = 65535;
const uint32_t MAX_26_BIT = 67108863;

//Rachel Ogbonna Start
const char* registers[] = {
    "$zero",
    "$at",
    "$v0",
    "$v1",
    "$a0",
    "$a1",
    "$a2",
    "$a3",
    "$t0",
    "$t1",
    "$t2",
    "$t3",
    "$t4",
    "$t5",
    "$t6",
    "$t7",
    "$s0",
    "$s1",
    "$s2",
    "$s3",
    "$s4",
    "$s5",
    "$s6",
    "$s7",
    "$t8",
    "$t9",
    "$k0",
    "$k1",
    "$gp",
    "$sp",
    "$fp",
    "$ra"
};
//Rachel Ogbonna End

const struct instruction_definition instruction_definitions[] = {
	{
		"ADD",
		R_TYPE,
		"000000",
		"100000",
		{ RD, RS, RT, EMPTY }
	},
	//Chase Sprigle End
	//Victoria Marston Start
	{
		"ADDU",
		R_TYPE,
		"000000",
		"100001",
		{ RD, RS, RT, EMPTY }
	},
	{
		"AND",
		R_TYPE,
		"000000",
		"100100",
		{ RD, RS, RT, EMPTY }
	},
	{
		"DIV",
		R_TYPE,
		"000000",
		"011010",
		{ RS, RT, EMPTY, EMPTY }
	},
	{
		"DIVU",
		R_TYPE,
		"000000",
		"011011",
		{ EMPTY, RS, RT, EMPTY }
	},
	{
		"JALR",
		R_TYPE,
		"000000",
		"001001",
		{ RD, RS, EMPTY, EMPTY }
	},
	{
		"JR",
		R_TYPE,
		"000000",
		"001000",
		{ EMPTY, RS, EMPTY, EMPTY }
	},
	{
		"MFHI",
		R_TYPE,
		"000000",
		"010000",
		{ RD, EMPTY, EMPTY, EMPTY }
	},
	{
		"MFLO",
		R_TYPE,
		"000000",
		"010010",
		{RD, EMPTY, EMPTY, EMPTY }
	},
	{
		"MTHI",
		R_TYPE,
		"000000",
		"010001",
		{ EMPTY, RS, EMPTY, EMPTY }
	},
	{
		"MTLO",
		R_TYPE,
		"000000",
		"010011",
		{ EMPTY, RS, EMPTY, EMPTY }
	},
	{
		"MULT",
		R_TYPE,
		"000000",
		"011000",
		{ EMPTY, RS, RT, EMPTY}
	},
	{
		"MULTU",
		R_TYPE,
		"000000",
		"011001",
		{ EMPTY, RS, RT, EMPTY }
	},
	{
		"NOR",
		R_TYPE,
		"000000",
		"100111",
		{ RD, RS, RT, EMPTY }
	},
	{
		"OR",
		R_TYPE,
		"000000",
		"100101",
		{ RD, RS, RT, EMPTY }
	},
	{
		"SLL",
		R_TYPE,
		"000000",
		"000000",
		{ RD, EMPTY, RT, SA }
	},
	{
		"SLLV",
		R_TYPE,
		"000000",
		"000100",
		{ RD, EMPTY, RT, RS }
	},
	{
		"SLT",
		R_TYPE,
		"000000",
		"101010",
		{ RD, RS, RT, EMPTY }
	},
	{
		"STLU",
		R_TYPE,
		"000000",
		"101011",
		{ RD, RS, RT, EMPTY }
	},
	{
		"SRA",
		R_TYPE,
		"000000",
		"000011",
		{ RD, EMPTY, RT, SA }
	},
	{
		"SRAV",
		R_TYPE,
		"000000",
		"000111",
		{ RD, EMPTY, RT, RS }
	},
	{
		"SRL",
		R_TYPE,
		"000000",
		"000010",
		{ RD, EMPTY, RT, SA }
	},
	{
		"SRLV",
		R_TYPE,
		"000000",
		"000110",
		{RD, EMPTY, RT, RS }
	},
	{
		"SUB",
		R_TYPE,
		"000000",
		"100010",
		{ RD, RS, RT, EMPTY }
	},
	{
		"SUBU",
		R_TYPE,
		"000000",
		"100011",
		{ RD, RS, RT, EMPTY }
	},
	{
		"SYSCALL",
		R_TYPE,
		"000000",
		"001100",
		{ EMPTY, EMPTY, EMPTY, EMPTY }
	},
	{
		"XOR",
		R_TYPE,
		"000000",
		"100110",
		{ RD, RS, RT, EMPTY }
	},
	// Start of the I-TYPEs
	{
		"ADDI",
		I_TYPE,
		"001000",
		NULL,
		{ RT, RS, IMM, EMPTY}
	},
	{
		"ADDIU",
		I_TYPE,
		"001001",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"ANDI",
		I_TYPE,
		"001100",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"BEQ",
		I_TYPE,
		"000100",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"BGEZ",
		I_TYPE,
		"000001",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"BGTZ",
		I_TYPE,
		"000111",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"BLEZ",
		I_TYPE,
		"000110",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"BLTZ",
		I_TYPE,
		"000001",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"BNE",
		I_TYPE,
		"000101",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"LB",
		I_TYPE,
		"100000",
		NULL,
		{ RT, EMPTY, IMM, EMPTY }
	},
	{
		"LBU",
		I_TYPE,
		"100100",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"LH",
		I_TYPE,
		"100001",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"LHU",
		I_TYPE,
		"100101",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"LUI",
		I_TYPE,
		"001111",
		NULL,
		{ RT, EMPTY, IMM, EMPTY }
	},
	{
		"LW",
		I_TYPE,
		"100011",
		NULL,
		{ RT, EMPTY, IMM, EMPTY}
	},
	{
		"LWCL",
		I_TYPE,
		"110001",
		NULL,
		{ RT, EMPTY, IMM, EMPTY }
	},
	{
		"ORI",
		I_TYPE,
		"001101",
		NULL,
		{ RT, RS, IMM, EMPTY}
	},
	{
		"SB",
		I_TYPE,
		"101000",
		NULL,
		{ RT, EMPTY, IMM, EMPTY }
	},
	{
		"SLTI",
		I_TYPE,
		"001010",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"SLTIU",
		I_TYPE,
		"001011",
		NULL,
		{ RT, RS, IMM, EMPTY }
	},
	{
		"SH",
		I_TYPE,
		"101001",
		NULL,
		{ RT, EMPTY, IMM, EMPTY}
	},
	{
		"SW",
		I_TYPE,
		"101011",
		NULL,
		{ RT, RS, IMM, EMPTY}
	},
	{
		"SWCL",
		I_TYPE,
		"111001",
		NULL,
		{ RT, EMPTY, IMM, EMPTY}
	},
	{
		"XORI",
		I_TYPE,
		"001110",
		NULL,
		{ RT, RS, IMM, EMPTY}
	},
	// Start of the J-TYPEs
	{
		"J",
		J_TYPE,
		"000010",
		NULL,
		{ TAR, EMPTY, EMPTY, EMPTY }
	},
	{
		"JAL",
		J_TYPE,
		"000011",
		NULL,
		{ TAR, EMPTY, EMPTY, EMPTY }
	}
	// Victoria Marston End
};
