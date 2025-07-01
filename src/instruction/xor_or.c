/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** instruction3
*/

#include "../../include/op.h"
#include "../../include/corewar.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

uint8_t get_argument_type(uint8_t *memory, process_t *proc, int arg_index)
{
    uint8_t ocp = memory[(proc->pc + 1) % MEM_SIZE];

    return (ocp >> (6 - 2 * (arg_index - 1))) & 0x03;
}

void store_result(process_t *proc, uint8_t reg_dest, int result)
{
    if (reg_dest >= 1 && reg_dest <= 16)
        proc->reg[reg_dest - 1] = result;
}

void exec_xor(process_t *proc, uint8_t *memory)
{
    uint8_t arg1_type = get_argument_type(memory, proc, 1);
    uint8_t arg2_type = get_argument_type(memory, proc, 2);
    uint8_t reg_dest = memory[proc->pc + 4];
    int octet_temp = 2;
    int value1 = define_value_for_4oct(proc, memory, &octet_temp, arg1_type);
    int value2 = define_value_for_4oct(proc, memory, &octet_temp, arg2_type);
    int result = value1 ^ value2;

    store_result(proc, reg_dest, result);
    proc->carry = (result == 0) ? 1 : 0;
    proc->pc = (proc->pc + 5) % MEM_SIZE;
}

void exec_or(process_t *proc, uint8_t *memory)
{
    uint8_t arg1_type = get_argument_type(memory, proc, 1);
    uint8_t arg2_type = get_argument_type(memory, proc, 2);
    uint8_t reg_dest = memory[proc->pc + 4];
    int octet_temp = 2;
    int value1 = define_value_for_4oct(proc, memory, &octet_temp, arg1_type);
    int value2 = define_value_for_4oct(proc, memory, &octet_temp, arg2_type);
    int result = value1 | value2;

    store_result(proc, reg_dest, result);
    proc->carry = (result == 0) ? 1 : 0;
    proc->pc = (proc->pc + 5) % MEM_SIZE;
}
