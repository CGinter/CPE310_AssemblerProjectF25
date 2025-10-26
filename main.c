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
		printf("%s\n", line);
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
