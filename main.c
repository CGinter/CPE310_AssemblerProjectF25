#include "include.h"

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
