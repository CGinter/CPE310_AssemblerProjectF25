/**
 * @file main.c
 * @brief
 * @author Chase Sprigle
 * @date 10/23/2025
 */
#include "include.h"

int main(int argc, char *argv[])
{
	struct assm_parse_result test = {
		"ADD",
		{ REGISTER, REGISTER, REGISTER, NONE },
		{ 8, 9, 10, 0 }
	};
	char *error = NULL;

	uint32_t machine_code = convert_to_machine_code(test, &error);

	if (error != NULL)
		puts(error);
	else
		printf("%b\n", machine_code);

	struct assm_parse_result assembly = convert_to_assembly(machine_code, &error);

	if (error != NULL)
		puts(error);
	else
		printf("Name:\t%s\nTypes:\t%d\t%d\t%d\t%d\nVals:\t%d\t%d\t%d\t%d\n",
				assembly.op_name, assembly.types[0], assembly.types[1],
				assembly.types[2], assembly.types[3], assembly.vals[0],
				assembly.vals[1], assembly.vals[2], assembly.vals[3]);

	char buf[1024];
	generate_assembly(buf, 1024, assembly, &error);

	if (error != NULL)
		puts(error);
	else
		puts(buf);

	return EXIT_SUCCESS;
}
