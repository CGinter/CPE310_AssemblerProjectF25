/**
 * @file mach_to_assm.h
 * @brief
 * @author Chase Sprigle
 * @date 10/23/2025
 */

/**
 * @brief Converts a machine instruction into assembly.
 * @param inst The provided machine instruction.
 * @param error Pointer to string to hold error message if an error occurs.
 * @return An assm_parse_result containing the instruction given when error is not set.
 * Undefined when error is set.
 */
struct assm_parse_result convert_to_assembly(uint32_t inst, char **error);
