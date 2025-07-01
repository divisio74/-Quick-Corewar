/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard1
** File description:
** instruction5
*/

#include "../../include/op.h"
#include "../../include/corewar.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

void exec_sti(process_t *proc, uint8_t *memory)
{
    int oct_temp = 2;
    uint8_t reg = memory[(proc->pc + oct_temp) % MEM_SIZE];
    uint8_t type2 = get_argument_type(memory, proc, 2);
    uint8_t type3 = get_argument_type(memory, proc, 3);
    int value = proc->reg[reg - 1];
    int val2 = 0;
    int val3 = 0;
    int addr = 0;

    oct_temp++;
    val2 = define_value_for_2oct(proc, memory, &oct_temp, type2);
    val3 = define_value_for_2oct(proc, memory, &oct_temp, type3);
    addr = (proc->pc + ((val2 + val3) % IDX_MOD)) % MEM_SIZE;
    memory[addr % MEM_SIZE] = (value >> 24) & 0xFF;
    memory[(addr + 1) % MEM_SIZE] = (value >> 16) & 0xFF;
    memory[(addr + 2) % MEM_SIZE] = (value >> 8) & 0xFF;
    memory[(addr + 3) % MEM_SIZE] = value & 0xFF;
    proc->pc = (proc->pc + oct_temp) % MEM_SIZE;
}

void exec_fork(process_t *proc, uint8_t *memory, process_t **proc_list)
{
    int offset;
    int addr;
    process_t *new_proc;

    offset = (short)((memory[(proc->pc + 1) % MEM_SIZE] << 8) |
        memory[(proc->pc + 2) % MEM_SIZE]);
    addr = (proc->pc + (offset % IDX_MOD)) % MEM_SIZE;
    if (addr < 0)
        addr += MEM_SIZE;
    new_proc = malloc(sizeof(process_t));
    if (!new_proc)
        return;
    my_memcpy(new_proc, proc, sizeof(process_t));
    new_proc->pc = addr;
    new_proc->next = *proc_list;
    new_proc->id = proc->id;
    *proc_list = new_proc;
    proc->pc = (proc->pc + 3) % MEM_SIZE;
    my_putstr("Fork executé !\n");
}

int extract_value_from_ind_no_mod(process_t *proc, uint8_t *memory,
    int *oct_temp)
{
    int addr = (short)((memory[(proc->pc + *oct_temp) % MEM_SIZE] << 8) |
        memory[(proc->pc + *oct_temp + 1) % MEM_SIZE]);
    int value = 0;

    addr = (proc->pc + addr) % MEM_SIZE;
    value = (memory[addr % MEM_SIZE] << 24) |
        (memory[(addr + 1) % MEM_SIZE] << 16) |
        (memory[(addr + 2) % MEM_SIZE] << 8) |
        memory[(addr + 3) % MEM_SIZE];
    *oct_temp += 2;
    return value;
}

void exec_lld(process_t *proc, uint8_t *memory)
{
    int oct_temp = 2;
    uint8_t type = get_argument_type(memory, proc, 1);
    int value;
    uint8_t reg;

    if (type == 0x02)
        value = extract_value_from_dir4(proc, memory, &oct_temp);
    else if (type == 0x03)
        value = extract_value_from_ind_no_mod(proc, memory, &oct_temp);
    else {
        proc->pc = (proc->pc + oct_temp) % MEM_SIZE;
        return;
    }
    reg = memory[(proc->pc + oct_temp) % MEM_SIZE];
    if (reg >= 1 && reg <= 16)
        proc->reg[reg - 1] = value;
    proc->carry = (value == 0) ? 1 : 0;
    proc->pc = (proc->pc + oct_temp + 1) % MEM_SIZE;
}
