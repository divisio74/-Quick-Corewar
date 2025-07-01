/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** instruction6
*/

#include "../../include/op.h"
#include "../../include/corewar.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int define_value_for_2oct_nomod(process_t *proc, uint8_t *memory,
    int *oct_temp, uint8_t type)
{
    int value = 0;

    if (type == 0x01)
        value = extract_value_from_reg(proc, memory, oct_temp);
    if (type == 0x02)
        value = extract_value_from_dir2(proc, memory, oct_temp);
    if (type == 0x03)
        value = extract_value_from_ind_no_mod(proc, memory, oct_temp);
    return value;
}

void exec_lldi(process_t *proc, uint8_t *memory)
{
    int oct_temp = 2;
    int value = 0;
    int addr = 0;
    uint8_t reg;
    uint8_t type1 = get_argument_type(memory, proc, 1);
    uint8_t type2 = get_argument_type(memory, proc, 2);
    int val1 = define_value_for_2oct_nomod(proc, memory, &oct_temp, type1);
    int val2 = define_value_for_2oct_nomod(proc, memory, &oct_temp, type2);

    addr = (proc->pc + val1 + val2) % MEM_SIZE;
    value = (memory[addr % MEM_SIZE] << 24) |
        (memory[(addr + 1) % MEM_SIZE] << 16) |
        (memory[(addr + 2) % MEM_SIZE] << 8) |
        memory[(addr + 3) % MEM_SIZE];
    reg = memory[(proc->pc + oct_temp) % MEM_SIZE];
    if (reg >= 1 && reg <= 16)
        proc->reg[reg - 1] = value;
    proc->carry = (value == 0) ? 1 : 0;
    proc->pc = (proc->pc + oct_temp + 1) % MEM_SIZE;
}

void exec_lfork(process_t *proc, uint8_t *memory, process_t **proc_list)
{
    int offset;
    int addr;
    process_t *new_proc;

    offset = (short)((memory[(proc->pc + 1) % MEM_SIZE] << 8) |
        memory[(proc->pc + 2) % MEM_SIZE]);
    addr = (proc->pc + offset) % MEM_SIZE;
    if (addr < 0)
        addr += MEM_SIZE;
    new_proc = malloc(sizeof(process_t));
    if (!new_proc)
        return;
    my_memcpy(new_proc, proc, sizeof(process_t));
    new_proc->pc = addr;
    new_proc->next = *proc_list;
    *proc_list = new_proc;
    proc->pc = (proc->pc + 3) % MEM_SIZE;
}

void exec_aff(process_t *proc, uint8_t *memory)
{
    int oct_temp = 2;
    uint8_t reg_index = memory[(proc->pc + 2) % MEM_SIZE];
    char c;

    if (reg_index >= 1 && reg_index <= 16) {
        c = (char)(proc->reg[reg_index - 1] % 256);
        write(1, &c, 1);
    }
    proc->pc = (proc->pc + oct_temp) % MEM_SIZE;
}
