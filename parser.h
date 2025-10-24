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
 * @brief Array of strings to represent available registers
 */
extern const char* registers[] = {
    "$zero",
    "$v0",
    "$v1",
    "$a0",
    "$a1",
    "$a2",
    "$a3",
    "$t0",
    "$t1",
    "$t2",
    "$t3",
    "$t4",
    "$t5",
    "$t6",
    "$t7",
    "$s1",
    "$s2",
    "$s3",
    "$s4",
    "$s5",
    "$s6",
    "$s7",
    "$t8",
    "$t9",
    "$t8",
    "$gp",
    "$sp",
    "$fp",
    "$ra"
};

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