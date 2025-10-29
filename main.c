/**
 * @file main.c
 * @brief
 * @author Caden Ginter
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
		char* error = NULL;
		char* end;
		struct assm_parse_result parse_result;
		uint32_t inst_in;
		uint32_t result;
		char decompile_result[LINE_BUFF_SIZE];
		switch (int_state) {
			case ASM_TO_MACH:
				// Call conversion from assembly to binary
				result = parse_assembly(line, &error);
				// Check for errors in parsing and assembling
				if (error != NULL) {
					printf("%s\n", error);
					continue;
				}
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
				if (error != NULL) {
					printf("%s\n", error);
					continue;
				}
				generate_assembly(decompile_result, LINE_BUFF_SIZE, parse_result, &error);
				if (error != NULL) {
					printf("%s\n", error);
					continue;
				}
				printf("%s\n\n", decompile_result);
				break;
			case BIN_TO_ASM:
				// First convert string hexadecimal to string binary
				inst_in = strtol(line, &end, 2);
				// Call binary to assembly conversion and print out, print input in binary for now
				parse_result = convert_to_assembly(inst_in, &error);
				if (error != NULL) {
					printf("%s\n", error);
					continue;
				}
				generate_assembly(decompile_result, LINE_BUFF_SIZE, parse_result, &error);
				if (error != NULL) {
					printf("%s\n", error);
					continue;
				}
				printf("%s\n\n", decompile_result);
				break;
			case INACTIVE:
				if (flags & ARG_REVERSE) {
					// First convert string hexadecimal to string binary
					inst_in = strtol(line, &end, 2);
					// Call conversion from binary to assembly
					parse_result = convert_to_assembly(inst_in, &error);
					if (error != NULL) {
						printf("%s\n", error);
						continue;
					}
					generate_assembly(decompile_result, LINE_BUFF_SIZE, parse_result, &error);
					if (error != NULL) {
						printf("%s\n", error);
						continue;
					}
					printf("%s\n", decompile_result);
				}
				else {
					// Call conversion from assembly to binary
					result = parse_assembly(line, &error);
					// Check for errors in parsing and assembling
					if (error != NULL) {
						printf("%s\n", error);
						continue;
					}
					// Print the result in binary
					for (int i = 0; i < 32; i++) {
						printf("%d", result / 0b010000000000000000000000000000000);
						result *= 2;
					}
					printf("\n");
				}
				break;

		}
		
	}
}
