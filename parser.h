/**
 * @file parser.h
 * @brief 
 * @author Rachel Ogbonna
 * @date 10/23/2025
 */


/**
 * @brief Uses sys_free_mem() to free all memory associated with the pcb
 * @param line String of assembly instruction to translate
 * @param error Pointer to string that will contain error message 
 * @return Instruction in binary
 */
uint32_t parse_assembly(char *line, char **error);