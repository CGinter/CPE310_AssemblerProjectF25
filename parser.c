/**
 * @file parser.c
 * @brief
 * @author Rachel Ogbonna
 * @date 10/26/2025
 */

#include "include.h"

/**
 * @brief Takes the string and turns each character to uppercase
 * @param operand String to convert to uppercase
 */
static void uppercase(char *operand);

/**
 * @brief Takes the string compares it with each register type to find a match
 * @param operand String to lookup
 */
static uint32_t reg_lookup(char *str, char** error);

/**
 * @brief Removes whitespace from a string
 * @param str String to remove whitespace from
 */
static void remove_space(char* str);

/**
 * @brief Removes pound symbol from string
 * @param str String to remove pound symbol from
 */
static void remove_pound(char* str);



uint32_t parse_assembly(char *line, char **error)
{
    struct assm_parse_result result;
    *error = NULL;
    size_t length;
    char* opp_name;

    //Returns length of the part of string that does not contain " "
    length = strcspn(line, " ");

    //Allocate mem for opp name 
    opp_name = (char*)malloc(sizeof(char) * (length + 1));

    //look for operand, and store into struct capitalized
    if (opp_name == NULL)
    {
        *error = "Memory not allocated.";
        return UNDEFINED;
    }

    //Copies opp name from line
    strncpy(opp_name, line, length);

    //Adds null terminator 
    opp_name[length] = '\0';
            
    // Turns opp name to uppercase
    uppercase(opp_name);

    //Assigns opp_name in struct
    result.op_name = opp_name;

    //look for registers
    line += length;

    char* token = strtok(line, ",");
    size_t arg;
    for (arg = 0; token != NULL; arg++)
    {
        //Removes space from token
        remove_space(token);

        if (token[0] == '#')
        {
            result.types[arg] = IMMEDIATE;
            remove_pound(token);
            char* end_ptr;
            result.vals[arg] = strtol(token, &end_ptr, 10);

            if(end_ptr == token || *end_ptr != '\0')
            {
                *error = "Improperly formatted immediate.";
                free(opp_name);
                opp_name = NULL;
                return UNDEFINED;
            }
        }
        else if (token[0] == '$')
        {
            result.types[arg] = REGISTER;
            // Set result.vals[arg] to the register internal number for the register after the $
            result.vals[arg] = reg_lookup(token, error);
            if (*error != NULL) {
                free(opp_name);
                opp_name = NULL;
                return UNDEFINED;
            }
        }
        else
        {
            *error = "Argument isn't register or immediate (targets not yet supported).";
            free(opp_name);
            opp_name = NULL;
            return UNDEFINED; 
        }

        // convert to val
        //val is undefined whrn corresponding type is NONE
        // add val to result

        token = strtok(NULL, ",");
    }

    for (;arg < 4; arg++) {
        // add none to remaining fields
        result.types[arg] = NONE;
        result.vals[arg] = UNDEFINED;
    }

    // Call convert_to_machine_code here
    uint32_t new_val = convert_to_machine_code(result, error);
    
    free(opp_name);
    opp_name = NULL;

    return new_val;
}

static void uppercase(char *operand)
{
    size_t length = strlen(operand);
    for (size_t i = 0; i < length; i++)
    {
        operand[i] = toupper((unsigned char) operand[i]);
    }
}

static void remove_pound(char* str)
{
    int count = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != '#')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

static void remove_space(char* str)
{
    int count = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ')
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0';
}

static uint32_t reg_lookup(char *str, char** error)
{
    for (uint32_t i = 0; i < sizeof(registers) / sizeof(char *); i++)
    {
        if (strcmp(registers[i],str) == 0)
        {
            return i;
        }
    }

    *error = "Register not found.";
    return UNDEFINED;
}
