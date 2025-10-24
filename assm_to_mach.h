/**
 * @file assm_to_mach.h
 * @brief 
 * @author Chase Sprigle
 * @date 10/23/2025
 */

/**
 * @brief Converts an assembly instruction into a machine instruction.
 * @param parsed A struct containing the assembly instruction to convert.
 * @param error Pointer to string to hold error message if an error occurs.
 * @return A uint32_t containing the machine instruction when error is not set. Undefined when
 * error is set.
 */
uint32_t convert_to_machine_code(struct assm_parse_result parsed, char **error);
