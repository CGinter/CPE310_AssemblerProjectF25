/**
 * @file main.c
 * @brief
 * @author Chase Sprigle
 * @date 10/23/2025
 */
#include "include.h"

int main(int argc, char *argv[])
{
	// Call the command line argument parser
	char* in_filename = NULL;
	char* out_filename = NULL;
	uint32_t flags;
	flags = command_line_args(argc, argv, &in_filename, &out_filename);

	enum InteractiveState int_state;

	if (flags & ARG_AUTO) {
		int_state = INACTIVE;
	}
	else {
		printf("Welcome to the MIPS-Translatron 3000 Tool\n");
		printf("ByteForge Systems ©2012\n");
		int_state = ROOT;
	}
	
	// Create empty file pointer for reading in
	FILE* in_file = NULL;

	while (1) {
		char line[LINE_BUFF_SIZE];
		get_next_input(line, &int_state, flags, in_filename, &in_file);
		// printf("%s\n", line);
		char* error;
		char* end;
		struct assm_parse_result parse_result;
		uint32_t inst_in;
		char decompile_result[LINE_BUFF_SIZE];
		switch (int_state) {
			case ASM_TO_MACH:
				// Call conversion from assembly to binary
				uint32_t result = parse_assembly(line, &error);
				// Print the result in binary and hexadecimal
				printf("Hex: 0x%08X Binary:", result);
				for (int i = 0; i < 32; i++) {
					if (i % 4 == 0 && i != 0)
						printf(" ");
					printf("%d", result / 0b010000000000000000000000000000000);
					result *= 2;
				}
				printf("\n");
				break;
			case HEX_TO_ASM:
				// First convert string hexadecimal to string binary
				inst_in = strtol(line, &end, 16);
				// Call binary to assembly conversion and print out, print input in binary for now
				parse_result = convert_to_assembly(inst_in, &error);
				generate_assembly(decompile_result, LINE_BUFF_SIZE, parse_result, &error);
				printf("%s\n\n", decompile_result);
				break;
			case BIN_TO_ASM:
				// First convert string hexadecimal to string binary
				inst_in = strtol(line, &end, 2);
				// Call binary to assembly conversion and print out, print input in binary for now
				parse_result = convert_to_assembly(inst_in, &error);
				generate_assembly(decompile_result, LINE_BUFF_SIZE, parse_result, &error);
				printf("%s\n\n", decompile_result);
				break;
		}
	}
	// if (result & ARG_AUTO)
	// 	printf("Auto mode\n");
	// else
	// 	printf("Interactive mode\n");

	// if (result & ARG_REVERSE)
	// 	printf("Machine to Assembly\n");
	// else
	// 	printf("Assembly to Machine\n");

	// if (in_filename != NULL)
	// 	printf("Input:\t%s\n", in_filename);
	// if (out_filename != NULL)
	// 	printf("Output:\t%s\n", out_filename);
}
