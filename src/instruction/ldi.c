/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** instruction4
*/

#include "../../include/op.h"
#include "../../include/corewar.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int extract_value_from_dir2(process_t *proc, uint8_t *memory,
    int *oct_temp)
{
    int value = (short)((memory[(proc->pc + *oct_temp) % MEM_SIZE] << 8) |
        memory[(proc->pc + *oct_temp + 1) % MEM_SIZE]);

    *oct_temp += 2;
    return value;
}

int extract_value_from_dir4(process_t *proc, uint8_t *memory,
    int *oct_temp)
{
    int value = (memory[(proc->pc + *oct_temp) % MEM_SIZE] << 24) |
        (memory[(proc->pc + *oct_temp + 1) % MEM_SIZE] << 16) |
        (memory[(proc->pc + *oct_temp + 2) % MEM_SIZE] << 8) |
        memory[(proc->pc + *oct_temp + 3) % MEM_SIZE];

    *oct_temp += 4;
    return value;
}

int define_value_for_2oct(process_t *proc, uint8_t *memory, int *oct_temp,
    uint8_t type)
{
    int value = 0;

    if (type == 0x01)
        value = extract_value_from_reg(proc, memory, oct_temp);
    if (type == 0x02)
        value = extract_value_from_dir2(proc, memory, oct_temp);
    if (type == 0x03)
        value = extract_value_from_ind(proc, memory, oct_temp);
    return value;
}

int define_value_for_4oct(process_t *proc, uint8_t *memory, int *oct_temp,
    uint8_t type)
{
    int value = 0;

    if (type == 0x01)
        value = extract_value_from_reg(proc, memory, oct_temp);
    if (type == 0x02)
        value = extract_value_from_dir4(proc, memory, oct_temp);
    if (type == 0x03)
        value = extract_value_from_ind(proc, memory, oct_temp);
    return value;
}

void exec_ldi(process_t *proc, uint8_t *memory)
{
    int oct_temp = 2;
    int value = 0;
    int final_addr = 0;
    uint8_t reg;
    uint8_t type1 = get_argument_type(memory, proc, 1);
    uint8_t type2 = get_argument_type(memory, proc, 2);
    int val1 = define_value_for_2oct(proc, memory, &oct_temp, type1);
    int val2 = define_value_for_2oct(proc, memory, &oct_temp, type2);

    final_addr = (proc->pc + ((val1 + val2) % IDX_MOD)) % MEM_SIZE;
    value = (memory[final_addr % MEM_SIZE] << 24) |
        (memory[(final_addr + 1) % MEM_SIZE] << 16) |
        (memory[(final_addr + 2) % MEM_SIZE] << 8) |
        memory[(final_addr + 3) % MEM_SIZE];
    reg = memory[(proc->pc + oct_temp) % MEM_SIZE];
    store_result(proc, reg, value);
    proc->pc = (proc->pc + oct_temp + 1) % MEM_SIZE;
}
