/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** and_st.c
*/

#include "../../include/op.h"
#include "../../include/corewar.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

void exec_and(process_t *proc, uint8_t *memory)
{
    uint32_t value1 = 0;
    uint32_t value2 = 0;
    uint8_t dest_reg = 0;

    value1 |= memory[(proc->pc + 2) % MEM_SIZE] << 24;
    value1 |= memory[(proc->pc + 3) % MEM_SIZE] << 16;
    value1 |= memory[(proc->pc + 4) % MEM_SIZE] << 8;
    value1 |= memory[(proc->pc + 5) % MEM_SIZE];
    value2 |= memory[(proc->pc + 6) % MEM_SIZE] << 24;
    value2 |= memory[(proc->pc + 7) % MEM_SIZE] << 16;
    value2 |= memory[(proc->pc + 8) % MEM_SIZE] << 8;
    value2 |= memory[(proc->pc + 9) % MEM_SIZE];
    dest_reg = memory[(proc->pc + 10) % MEM_SIZE];
    if (dest_reg >= 1 && dest_reg <= 16) {
        proc->reg[dest_reg - 1] = value1 & value2;
        proc->carry = (proc->reg[dest_reg - 1] == 0) ? 1 : 0;
    }
    proc->pc = (proc->pc + 10) % MEM_SIZE;
}

void exec_st(process_t *proc, uint8_t *memory)
{
    uint8_t src_reg = memory[(proc->pc + 2) % MEM_SIZE];
    uint8_t type2 = get_argument_type(memory, proc, 2);
    uint32_t addr = 0;
    uint32_t value;
    int oct_temp = 2;

    addr = define_value_for_2oct(proc, memory, &oct_temp, type2);
    if (src_reg >= 1 && src_reg <= 16) {
        value = proc->reg[src_reg - 1];
        memory[(addr + 0) % MEM_SIZE] = (value >> 24) & 0xFF;
        memory[(addr + 1) % MEM_SIZE] = (value >> 16) & 0xFF;
        memory[(addr + 2) % MEM_SIZE] = (value >> 8) & 0xFF;
        memory[(addr + 3) % MEM_SIZE] = value & 0xFF;
        proc->carry = (value == 0) ? 1 : 0;
    }
    proc->pc = (proc->pc + 6) % MEM_SIZE;
}
