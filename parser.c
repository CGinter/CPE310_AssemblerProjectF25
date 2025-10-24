/**
 * @file parser.c
 * @brief
 * @author Rachel Ogbonna
 * @date 10/23/2025
 */

#include "include.h"
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

//parsing text like add $t0, $t1, $t0; assembly to machine
//get string, pack into struct in types.h, then call convert_to_machine_code func (pass error straight into it)
//set char**error to null immediately, when i get an error return to cadens function 
//dont do error messages
//Pointer to string, when i need to twll caden there is an error set it something other than null
//make sure private functions are static 

uint32_t parse_assembly(char *line, char **error)
{

    puts("Please enter an instruction: \n");

}




