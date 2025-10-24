/**
 * @file parser.h
 * @brief 
 * @author Rachel Ogbonna
 * @date 10/23/2025
 */

#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>

/**
 * @brief Uses sys_free_mem() to free all memory associated with the pcb
 * @param line String of assembly instruction to translate
 * @param error Pointer to string that will contain error message 
 * @return Instruction in binary
 */
uint32_t parse_assembly(char *line, char **error);

/**
 * @brief Takes the string and turns each character to uppercase
 * @param operand String to convert to uppercase
 */
void uppercase(char *operand);


/**
 * @brief Takes the string compares it with each register type to find a match
 * @param operand String to lookup
 */
u_int32_t reg_lookup(char *str);

#endif