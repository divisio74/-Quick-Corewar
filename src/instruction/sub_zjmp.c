/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** instruction2
*/

#include "../../include/op.h"
#include "../../include/corewar.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

void exec_sub(process_t *proc, uint8_t *memory)
{
    uint8_t reg1 = memory[(proc->pc + 2) % MEM_SIZE];
    uint8_t reg2 = memory[(proc->pc + 3) % MEM_SIZE];
    uint8_t reg3 = memory[(proc->pc + 4) % MEM_SIZE];
    int result = 0;

    if (reg1 < 1 || reg1 > 16 || reg2 < 1 || reg2 > 16 || reg3 < 1 ||
        reg3 > 16)
        return;
    result = proc->reg[reg1 - 1] - proc->reg[reg2 - 1];
    proc->reg[reg3 - 1] = result;
    proc->carry = (result == 0) ? 1 : 0;
    proc->pc = (proc->pc + 5) % MEM_SIZE;
}

void exec_zjmp(process_t *proc, uint8_t *memory)
{
    int oct_temp = 1;
    int offset = extract_value_from_dir2(proc, memory, &oct_temp);

    if (proc->carry == 1) {
        proc->pc = (proc->pc + (offset % IDX_MOD)) % MEM_SIZE;
        my_putstr("\nJumped !\n");
    } else
        proc->pc = (proc->pc + oct_temp) % MEM_SIZE;
}
