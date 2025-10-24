/**
 * @file gen_assm.h
 * @brief Code to generate assembly from a parse result.
 * @author Chase Sprigle
 * @date 10/23/2025
 */

/**
 * @brief Function to generate assembly as text from a parse result.
 * @param parsed The assembly parse result.
 * @param error Pointer to string to hold error message if an error occurs.
 * @return A line of assembly as text if error is not set. Undefined otherwise.
 */
char *generate_assembly(struct assm_parse_result parsed, char **error);
