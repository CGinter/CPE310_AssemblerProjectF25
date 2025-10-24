/**
 * @file mach_to_assm.c
 * @brief
 * @author Chase Sprigle
 * @date 10/23/2025
 */
#include "include.h"

static size_t find_instruction_by_code(uint32_t op_code, uint32_t funct_code, char **error);

struct assm_parse_result convert_to_assembly(uint32_t inst, char **error)
{
	// Set error to NULL initially
	*error = NULL;

	// Find all instruction parts regarless of validity
	uint32_t rd = (inst >> 11) & MAX_5_BIT;
	uint32_t rs = (inst >> 21) & MAX_5_BIT;
	uint32_t rt = (inst >> 16) & MAX_5_BIT;
	uint32_t sa = (inst >> 6) & MAX_5_BIT;
	uint32_t imm = inst & MAX_16_BIT;
	uint32_t tar = inst & MAX_26_BIT;

	uint32_t op_code = (inst >> 26) & MAX_6_BIT;
	uint32_t funct_code = inst & MAX_6_BIT;

	// Make struct
	struct assm_parse_result assembly;

	// Find the instruction
	size_t ins = find_instruction_by_code(op_code, funct_code, error);
	if (*error != NULL)
		return assembly;

	// Build the parse result
	assembly.op_name = instruction_definitions[ins].op_name;
	for (size_t i = 0; i < 4; i++) {
		switch (instruction_definitions[ins].parts[i]) {
		case RD:
			assembly.types[i] = REGISTER;
			assembly.vals[i] = rd;
			break;
		case RS:
			assembly.types[i] = REGISTER;
			assembly.vals[i] = rs;
			break;
		case RT:
			assembly.types[i] = REGISTER;
			assembly.vals[i] = rt;
			break;
		case SA:
			assembly.types[i] = REGISTER;
			assembly.vals[i] = sa;
			break;
		case IMM:
			assembly.types[i] = IMMEDIATE;
			assembly.vals[i] = imm;
			break;
		case TAR:
			assembly.types[i] = TARGET;
			assembly.vals[i] = tar;
			break;
		case EMPTY:
			assembly.types[i] = NONE;
			assembly.vals[i] = UNDEFINED;
			break;
		}
	}

	return assembly;
}

static size_t find_instruction_by_code(uint32_t op_code, uint32_t funct_code, char **error)
{
	size_t ins;
	bool found = false;

	for (ins = 0; ins < sizeof(instruction_definitions)
			/ sizeof(struct instruction_definition); ins++) {
		if (bin_to_num(instruction_definitions[ins].op_code) != op_code)
			continue;

		if (instruction_definitions[ins].type == R_TYPE) {
			if (bin_to_num(instruction_definitions[ins].funct_code) != funct_code)
				continue;
		}

		found = true;
		break;
	}

	if (found == false)
		*error = "No instruction of given op code or funct code.";

	return ins;
}
