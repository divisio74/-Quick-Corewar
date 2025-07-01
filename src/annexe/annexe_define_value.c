/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** annexe_define_value
*/

#include "../../include/op.h"
#include "../../include/corewar.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int extract_value_from_ind(process_t *proc, uint8_t *memory,
    int *oct_temp)
{
    int value = 0;
    int addr = 0;

    addr = (short)((memory[(proc->pc + *oct_temp) % MEM_SIZE] << 8) |
        memory[(proc->pc + *oct_temp + 1) % MEM_SIZE]);
    addr = (proc->pc + (addr % IDX_MOD)) % MEM_SIZE;
    value = (memory[addr % MEM_SIZE] << 24) |
        (memory[(addr + 1) % MEM_SIZE] << 16) |
        (memory[(addr + 2) % MEM_SIZE] << 8) |
        memory[(addr + 3) % MEM_SIZE];
    *oct_temp += 2;
    return value;
}

int extract_value_from_reg(process_t *proc, uint8_t *memory,
    int *oct_temp)
{
    uint8_t reg = memory[(proc->pc + *oct_temp) % MEM_SIZE];
    int value = 0;

    if (reg >= 1 && reg <= 16)
        value = proc->reg[reg - 1];
    *oct_temp += 1;
    return value;
}
