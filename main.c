#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum assm_parse_result_type {
	REGISTER,
	IMMEDIATE,
	TARGET,
	NONE
};

struct assm_parse_result {
	char *op_name;
	enum assm_parse_result_type types[4];
	uint32_t vals[4];
};

enum instruction_type {
	R_TYPE,
	I_TYPE,
	J_TYPE
};

enum instruction_part {
	RD,
	RS,
	RT,
	SA,
	IMM,
	TAR,
	EMPTY
};

struct instruction_definition {
	char *op_name;
	enum instruction_type type;
	char *op_code;
	char *funct_code;
	enum instruction_part parts[4];
};

struct instruction_definition instruction_definitions[] = {
	{
		"ADD",
		R_TYPE,
		"000000",
		"100000",
		{ RD, RS, RT, EMPTY }
	}
};

uint32_t bin_to_num(char *binary);
uint32_t convert_to_machine_code(struct assm_parse_result parsed, char **error);

int main(int argc, char *argv[])
{
	struct assm_parse_result test = {
		"ADD",
		{ REGISTER, REGISTER, REGISTER, EMPTY },
		{ 8, 9, 10, 0 }
	};
	char *error = NULL;

	uint32_t machine_code = convert_to_machine_code(test, &error);

	if (error != NULL)
		puts(error);
	else
		printf("%b\n", machine_code);

	return EXIT_SUCCESS;
}

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

uint32_t convert_to_machine_code(struct assm_parse_result parsed, char **error)
{
	// Handle abscense of BREAK
	if (strcmp(parsed.op_name, "BREAK") == 0) {
		*error = "The BREAK instruction is not supported.";
		return 0;
	}

	size_t ins;
	bool found = false;

	// Find index of instruction
	for (ins = 0; ins < sizeof(instruction_definitions) / sizeof(struct instruction_definition); ins++) {
		if (strcmp(parsed.op_name, instruction_definitions[ins].op_name) == 0) {
			found = true;
			break;
		}
	}

	// Error out if instruction not found
	if (found == false) {
		*error = "No instruction of given name.";
		return 0;
	}

	uint32_t result = 0;

	// Add op code to result
	result |= bin_to_num(instruction_definitions[ins].op_code) << 26;

	// Add funct code to result
	if (instruction_definitions[ins].type == R_TYPE)
		result |= bin_to_num(instruction_definitions[ins].funct_code);

	for (size_t i = 0; i < 4; i++) {
		// Error checking
		switch (instruction_definitions[ins].parts[i]) {
		case RD:
		case RS:
		case RT:
		case SA:
			if (parsed.types[i] != REGISTER) {
				*error = "Missing register.";
				return 0;
			}
			if (parsed.vals[i] > 31) { // 6-bit max
				*error = "Invalid register.";
				return 0;
			}
			break;
		case IMM:
			if (parsed.types[i] != IMMEDIATE) {
				*error = "Missing immediate.";
				return 0;
			}
			if (parsed.vals[i] > 65535) { // 16-bit max
				*error = "Invalid immediate.";
				return 0;
			}
			break;
		case TAR:
			if (parsed.types[i] != TARGET) {
				*error = "Missing target.";
				return 0;
			}
			if (parsed.vals[i] > 67108863) { // 26-bit max
				*error = "Invalid target.";
				return 0;
			}
			break;
		}

		// Put parsed value into result
		switch (instruction_definitions[ins].parts[i]) {
		case RD:
			result |= parsed.vals[i] << 11;
			break;
		case RS:
			result |= parsed.vals[i] << 21;
			break;
		case RT:
			result |= parsed.vals[i] << 16;
			break;
		case SA:
			result |= parsed.vals[i] << 6;
			break;
		case IMM:
		case TAR:
			result |= parsed.vals[i];
			break;
		}
	}

	return result;
}
