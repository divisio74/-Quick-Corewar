/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** instruction
*/

#include "../../include/op.h"
#include "../../include/corewar.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

void exec_ld(process_t *proc, uint8_t *memory)
{
    int value = 0;
    int reg = 0;

    value |= memory[(proc->pc + 2) % MEM_SIZE] << 24;
    value |= memory[(proc->pc + 3) % MEM_SIZE] << 16;
    value |= memory[(proc->pc + 4) % MEM_SIZE] << 8;
    value |= memory[(proc->pc + 5) % MEM_SIZE];
    reg = memory[(proc->pc + 6) % MEM_SIZE];
    if (reg >= 1 && reg <= 16) {
        proc->reg[reg - 1] = value;
        proc->carry = (value == 0) ? 1 : 0;
    }
    proc->pc = (proc->pc + 7) % MEM_SIZE;
}

static int32_t read_big_endian_int32(uint8_t *memory, int addr)
{
    return (int32_t)((memory[addr % MEM_SIZE] << 24) |
        (memory[(addr + 1) % MEM_SIZE] << 16) |
        (memory[(addr + 2) % MEM_SIZE] << 8) |
        (memory[(addr + 3) % MEM_SIZE]));
}

void exec_live(process_t *proc, uint8_t *memory, game_ctx_t *ctx)
{
    int32_t id = read_big_endian_int32(memory, proc->pc + 1);

    proc->alive = 1;
    ctx->live_count++;
    my_putstr("Processus ");
    my_put_nbr(proc->id);
    my_putstr(" ping la vie du champion ");
    my_put_nbr(id);
    my_putstr("\n");
    for (int i = 0; i < ctx->champion_count; i++) {
        if (ctx->champions[i].number == - id) {
            ctx->champions[i].last_live_cycle = ctx->current_cycle;
            my_putstr("\nping life for Champion ");
            my_put_nbr(id);
            break;
        }
    }
    proc->pc = (proc->pc + 5) % MEM_SIZE;
}

void exec_add(process_t *proc, uint8_t *memory)
{
    uint8_t reg1 = memory[(proc->pc + 2) % MEM_SIZE];
    uint8_t reg2 = memory[(proc->pc + 3) % MEM_SIZE];
    uint8_t reg3 = memory[(proc->pc + 4) % MEM_SIZE];
    int result = 0;

    if (reg1 < 1 || reg1 > 16 || reg2 < 1 || reg2 > 16 || reg3 < 1 ||
        reg3 > 16) {
        my_putstr("Erreur : Registres invalides pour ADD\n");
        proc->pc = (proc->pc + 5) % MEM_SIZE;
        return;
    }
    result = proc->reg[reg1 - 1] + proc->reg[reg2 - 1];
    proc->reg[reg3 - 1] = result;
    proc->carry = (result == 0) ? 1 : 0;
    proc->pc = (proc->pc + 5) % MEM_SIZE;
}
