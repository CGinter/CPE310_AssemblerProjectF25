/**
 * @file util.c
 * @brief Utility functions.
 * @author Chase Sprigle, Caden Ginter
 * @date 10/23/2025
 */

// Chase Sprigle start
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
// Chase Sprigle end
// Caden Ginter start
const uint32_t ARG_AUTO 	= 1;
const uint32_t ARG_REVERSE	= 2;

const uint32_t LINE_BUFF_SIZE = 4096;

uint32_t command_line_args(int argc, char *argv[], char** in_filename, char** out_filename)
{
	uint32_t result = 0;
	for (int i = 1; i < argc; i++) {
		// Check for each possible command argument, then default to file names
		if (!strcmp(argv[i], "-a"))
			result = result | ARG_AUTO;
		else if (!strcmp(argv[i], "-r"))
			result = result | ARG_REVERSE;
		else if (*in_filename == NULL)
			*in_filename = argv[i];
		else if (*out_filename == NULL)
			*out_filename = argv[i];
	}
	return result;
}

void get_next_input(char* line, enum InteractiveState* int_state, uint32_t flags, char* in_filename, FILE** file)
{
	// Pluck out flags
	uint32_t auto_mode = flags & ARG_AUTO > 0;
	uint32_t reverse_mode = flags & ARG_REVERSE > 0;
	
	// Empty box for file read status
	char* str;

	// Input from filename
	if (auto_mode && in_filename != NULL) {
		// Open the file if it isn't already
		if (*file == NULL)
			*file = fopen(in_filename, "r");
		// Read line from file, checking for and cleaning up newlines
		str = fgets(line, LINE_BUFF_SIZE, *file);
		if (str == NULL && feof(*file)) {
			if (*file != NULL)
				fclose(*file);
			exit(0);
		}
		else if (str == NULL && ferror(*file)) {
			printf("Invalid line");
			if (*file != NULL)
				fclose(*file);
			exit(1);
		}
		else if (*line == '\n') {
			get_next_input(line, int_state, flags, in_filename, file);
		}
		line[strcspn(line, "\n")] = 0;
		return;
	}
	// Input from stdin
	else if (auto_mode && in_filename == NULL) {
		str = fgets(line, LINE_BUFF_SIZE, stdin);
		if (str == NULL && feof(stdin)) {
			if (stdin != NULL)
				fclose(stdin);
			exit(0);
		}
		else if (str == NULL && ferror(stdin)) {
			printf("Invalid line");
			if (stdin != NULL)
				fclose(stdin);
			exit(1);
		}
		else if (*line == '\n') {
			get_next_input(line, int_state, flags, in_filename, file);
		}

		// Read line from stdin, checking for and cleaning up newlines
		if (strchr(line, '\n') == NULL || str == NULL) {
			printf("Invalid line");
			if (*file != NULL)
				fclose(*file);
			exit(1);
		}
		line[strcspn(line, "\n")] = 0;
		return;
	}
	// Interactive mode
	else if (!auto_mode) {
		// Keep navigating menu until user enters a line
		while (1) {
			char choice[10];
			switch (*int_state) {
				// Root menu
				case ROOT:
					printf("\nPlease enter an option:\n\t(1) Assembly to Machine Code\n\t(2) Machine Code to Assembly\n\t(3) Quit\n\t(4) Corrupted Code Inspector\n");
					printf("\n> ");
					choice[0] = 0;
					str = fgets(choice, sizeof(choice), stdin);
					if (strchr(choice, '\n') == NULL || str == NULL) {
						printf("Invalid input");
						*int_state = ROOT;
						continue;
					}
					choice[strcspn(choice, "\n")] = 0;
					if (!strcmp(choice, "1")) {
						*int_state = ASM_TO_MACH;
					}
					else if (!strcmp(choice, "2")) {
						*int_state = MACH_TO_ASM;
					}
					else if (!strcmp(choice, "3")) {
						if (*file != NULL)
							fclose(*file);
						exit(0);
					}
					else if (!strcmp(choice, "4")) {
						*int_state = DEBUG;
					}
					else {
						printf("Invalid input");
						*int_state = ROOT;
					}
					break;
			
				// Submenu for Hex vs. Binary entry
				case MACH_TO_ASM:
					printf("\nPlease select an option:\n\t(1) Hexadecimal to Assembly\n\t(2) Binary to Assembly\n\t[3] Main Menu\n");
					printf("\n> ");
					choice[0] = 0;
					str = fgets(choice, sizeof(choice), stdin);
					if (strchr(choice, '\n') == NULL || str == NULL) {
						printf("Invalid input");
						*int_state = MACH_TO_ASM;
						continue;
					}
					choice[strcspn(choice, "\n")] = 0;
					if (!strcmp(choice, "1")) {
						*int_state = HEX_TO_ASM;
					}
					else if (!strcmp(choice, "2")) {
						*int_state = BIN_TO_ASM;
					}
					else if (!strcmp(choice, "3")) {
						*int_state = ROOT;
					}
					else {
						printf("Invalid input");
						*int_state = MACH_TO_ASM;
					}
					break;
				
				// ASM entry, stay stuck until valid entry or blank
				case ASM_TO_MACH:
					printf("\n Enter a line of assembly:\n> ");
					str = fgets(line, LINE_BUFF_SIZE, stdin);
					if (strchr(line, '\n') == NULL || str == NULL) {
						printf("Invalid input");
						continue;
					}
					line[strcspn(line, "\n")] = 0;
					if (line[0] == 0) { // If empty, jump back to root
						*int_state = ROOT;
					}
					return;
				
				// Hex entry, stay stuck until valid entry or blank
				case HEX_TO_ASM:
					printf("\n Enter Hex:\n> ");
					str = fgets(line, LINE_BUFF_SIZE, stdin);
					if (strchr(line, '\n') == NULL || str == NULL) {
						printf("Invalid input");
						continue;
					}
					line[strcspn(line, "\n")] = 0;
					if (line[0] == 0) { // If empty, jump back to machine submenu
						*int_state = MACH_TO_ASM;
					}
					return;
				
				// Binary entry, stay stuck until valid entry or blank
				case BIN_TO_ASM:
					printf("\n Enter Binary:\n> ");
					str = fgets(line, LINE_BUFF_SIZE, stdin);
					if (strchr(line, '\n') == NULL || str == NULL) {
						printf("Invalid input");
						continue;
					}
					line[strcspn(line, "\n")] = 0;
					if (line[0] == 0) { // If empty, jump back to machine submenu
						*int_state = MACH_TO_ASM;
					}
					return;
				case DEBUG:
					printf("\n Enter Broken Binary:\n> ");
					str = fgets(line, LINE_BUFF_SIZE, stdin);
					if (strchr(line, '\n') == NULL || str == NULL) {
						printf("Invalid input");
						continue;
					}
					line[strcspn(line, "\n")] = 0;
					if (line[0] == 0) { // If empty, jump back to machine submenu
						*int_state = ROOT;
					}
					return;

			}
		}
	}
	// Invalid mode
	else {
		return;
	}
}

// Caden Ginter end
