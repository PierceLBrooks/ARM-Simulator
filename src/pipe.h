/*
 * CMSC 22200, Fall 2016
 *
 * ARM pipeline timing simulator
 *
 * Reza Jokar, Gushu Li, 2016
 */


#ifndef _PIPE_H_
#define _PIPE_H_

#include "shell.h"
#include "stdbool.h"
#include <limits.h>

//typedef int bool;
#define TRUE 1
#define FALSE 0

extern int RUN_BIT;

extern Pipe_Reg_IFtoID PREGISTER_IF_ID;
extern Pipe_Reg_IDtoEX PREGISTER_ID_EX;
extern Pipe_Reg_EXtoMEM PREGISTER_EX_MEM;
extern Pipe_Reg_MEMtoWB PREGISTER_MEM_WB;

extern global_vars globals;
/* global variable -- pipeline state */
extern CPU_State CURRENT_STATE;

/* called during simulator startup */
void pipe_init();

/* this function calls the others */
void pipe_cycle();

/* each of these functions implements one stage of the pipeline */
void pipe_stage_fetch();
void pipe_stage_decode();
void pipe_stage_execute();
void pipe_stage_mem();
void pipe_stage_wb();

#endif
