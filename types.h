/**
 * @file types.h
 * @brief
 * @author Chase Sprigle, Caden Ginter
 * @date 10/23/2025
 */
// Chase Sprigle Start
enum assm_parse_result_type {
	REGISTER,
	IMMEDIATE,
	TARGET,
	NONE
};

struct assm_parse_result {
	char *op_name;
	enum assm_parse_result_type types[4];
	uint32_t vals[4];
};

enum instruction_type {
	R_TYPE,
	I_TYPE,
	J_TYPE
};

enum instruction_part {
	RD,
	RS,
	RT,
	SA,
	IMM,
	TAR,
	EMPTY
};

struct instruction_definition {
	char *op_name;
	enum instruction_type type;
	char *op_code;
	char *funct_code;
	enum instruction_part parts[4];
};
// Chase Sprigle End

// Caden Ginter Start
/**
 * @brief Enum for the state of the interactive assembler mode
 */
enum InteractiveState {
    ROOT,

    ASM_TO_MACH,

    MACH_TO_ASM,
    HEX_TO_ASM,
    BIN_TO_ASM,

    INACTIVE
};
// Caden Ginter End