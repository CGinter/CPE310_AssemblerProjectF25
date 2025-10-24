/**
 * @file parser.c
 * @brief
 * @author Rachel Ogbonna
 * @date 10/23/2025
 */

#include "include.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include <stdlib.h>

//parsing text like add $t0, $t1, $t0; assembly to machine
//get string, pack into struct in types.h, then call convert_to_machine_code func (pass error straight into it)
//set char**error to null immediately, when i get an error return to cadens function 
//dont do error messages
//Pointer to string, when i need to twll caden there is an error set it something other than null
//make sure private functions are static 

uint32_t parse_assembly(char *line, char **error)
{
    struct assm_parse_result result;
    *error = NULL;

    //look for operand, and store into struct capitalized
    char *operand = strstr(line, " ");
    if (operand == NULL)
    {
        *error = "Operand not found";
        return UNDEFINED;
    }
            
    uppercase(operand);
    result.op_name = operand;

    //look for registers
    char* inst_registers;
    strcat(inst_registers, operand + 1);
    
    // char* reg1, reg2, reg3, reg4;

    char* token = strtok(inst_registers, ",");
    size_t arg;
    for (arg = 1; token != NULL; arg++)
    {
        // parse the token

        // determine the type
        // add type to result

        // convert to val
        //val is undefined whrn corresponding type is NONE
        // add val to result

        token = strtok(NULL, ",");
    }

    for (;arg < 4; arg++) {
        // add none to remaining fields
    }
}

void uppercase(char *operand)
{
    size_t length = strlen(operand);
    for(size_t i = 0; i < length; i++)
    {
        operand[i] = toupper((unsigned char) operand[i]);
    }
}

u_int32_t reg_lookup(char *str)
{
    for (u_int32_t i = 0; i < sizeof(registers) / sizeof(registers[0]); i++)
    {
        if(strcmp(registers[i],str) == 0)
        {
            return i;
        }
    } 
}






