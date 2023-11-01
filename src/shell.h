/***************************************************************/
/*                                                             */
/*   ARM Instruction Level Simulator                       */
/*                                                             */
/*   CMSC-22200 Computer Architecture                                            */
/*   University of Chicago                                */
/*                                                             */
/***************************************************************/

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/*          DO NOT MODIFY THIS FILE!                            */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#ifndef _SIM_SHELL_H_
#define _SIM_SHELL_H_

#include <stdint.h>

#define FALSE 0
#define TRUE  1
#define ARM_REGS 32

typedef enum instruction {
    NO_INSTRUCTION,//0
    //R type
    ADD,
    ADDS,
    AND,
    ANDS,
    BR,
    EOR,
    MUL,
    ORR,
    SDIV,
    SUB,
    SUBS,
    CMP,
    UDIV,
    //CB-type
    CBNZ,
    CBZ,
    BEQ,
    BNE,
    BGT,
    BLT,
    BGE,
    BLE,
    // D-type
    LDUR,
    LDURB,
    LDURH,
    STUR,
    STURB,
    STURH,
    STURW,
    // I-type
    ADDI,
    ADDIS,
    SUBI,
    SUBIS,
    // Shift-Type
    LSL, 
    LSLI,
    LSRI,
    LSR,
    // B-type
    B,
    BL,
    // IW-type
    MOVZ,
    // HLT
    HLT
} instruction;

typedef struct Pipe_Reg_IFtoID {
    int64_t PC_d;
    uint32_t IR_d;
    uint32_t flag_n;
    uint32_t flag_z;
    uint32_t flag_v;
    uint32_t flag_c;
} Pipe_Reg_IFtoID;

typedef struct Pipe_Reg_IDtoEX {
    int64_t PC_e;
    int64_t A_e;
    int64_t B_e;
    uint32_t Imm_e;
    uint32_t write_register_number;
    uint32_t flag_n;
    uint32_t flag_z;
    uint32_t flag_v;
    uint32_t flag_c;
    uint32_t register_Rn1;
    uint32_t register_Rm2;
    uint32_t machine_code;
    instruction i;
} Pipe_Reg_IDtoEX;

typedef struct Pipe_Reg_EXtoMEM {
    int64_t nPC_m;
    int64_t Aout_m;
    int64_t B_m;
    uint32_t write_register_number;
    uint32_t flag_n;
    uint32_t flag_z;
    uint32_t flag_v;
    uint32_t flag_c;
    uint32_t will_write;
    uint32_t machine_code;
    instruction i;
} Pipe_Reg_EXtoMEM;

typedef struct Pipe_Reg_MEMtoWB {
    int64_t MDR_w;
    int64_t Aout_w;
    uint32_t write_register_number;
    uint32_t flag_n;
    uint32_t flag_z;
    uint32_t flag_v;
    uint32_t flag_c;
    uint32_t will_write;
    uint32_t machine_code;
    instruction i;
} Pipe_Reg_MEMtoWB;

typedef struct CPU_State {
    /* register file state */
    int64_t REGS[ARM_REGS];
    int FLAG_N;        /* flag N */
    int FLAG_Z;        /* flag Z */
    int FLAG_V;        /* flag V */
    int FLAG_C;        /* flag C */
    /* program counter in fetch stage */
    uint64_t PC;
} CPU_State;

typedef struct global_vars {
    uint32_t dcache_num_to_stall;
    uint32_t icache_num_to_squash;
    uint32_t machine_code;
    bool is_unconditional;
    bool should_squash_fetch;
    bool detected_load_hazard;
    bool detected_halt;
    bool did_forward_flags;
    bool should_squash_decode;
    bool should_update_i_cache;
    bool should_update_d_cache;
} global_vars;

/* only the cache touches these functions */
uint32_t mem_read_32(uint64_t address);
void     mem_write_32(uint64_t address, uint32_t value);

/* statistics */
extern uint32_t stat_cycles, stat_inst_retire, stat_inst_fetch, stat_squash;

#endif
