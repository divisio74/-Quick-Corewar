/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** starg_game
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/op.h"
#include "../include/corewar.h"

void execute_for_all(game_ctx_t *ctx)
{
    process_t *current = ctx->proc_list;
    process_t *next;

    while (current) {
        next = current->next;
        if (current->alive)
            execute_process(current, ctx);
        current = next;
    }
}

process_t *init_processes(champion_t *champions, int count)
{
    process_t *head = NULL;
    process_t *new_proc;

    for (int i = 0; i < count; ++i) {
        new_proc = malloc(sizeof(process_t));
        new_proc->pc = champions[i].flag_address;
        new_proc->id = champions[i].number;
        new_proc->alive = 1;
        new_proc->next = head;
        for (int r = 0; r < 16; ++r)
            new_proc->reg[r] = 0;
        new_proc->reg[0] = champions[i].number;
        head = new_proc;
    }
    return head;
}

void execute_process(process_t *proc, game_ctx_t *ctx)
{
    uint8_t opcode = ctx->memory[proc->pc];

    if (opcode < 1 || opcode > 16) {
        proc->pc = (proc->pc + 1) % MEM_SIZE;
        my_putstr("Instruction inconnue, PC + 1\n");
        return;
    }
    my_putstr("\nprocess ");
    my_put_nbr(proc->id);
    my_putstr(" execute opcode : ");
    my_put_nbr(opcode);
    my_putchar('\n');
    execute_instruction(proc, opcode, ctx);
}

static void execute_arithmetic(process_t *proc, uint8_t opcode,
    game_ctx_t *ctx)
{
    switch (opcode) {
        case 4:
            exec_add(proc, ctx->memory);
            break;
        case 5:
            exec_sub(proc, ctx->memory);
            break;
        default:
            break;
    }
}

static void execute_logical(process_t *proc, uint8_t opcode, game_ctx_t *ctx)
{
    switch (opcode) {
        case 6:
            exec_and(proc, ctx->memory);
            break;
        case 7:
            exec_or(proc, ctx->memory);
            break;
        case 8:
            exec_xor(proc, ctx->memory);
            break;
        default:
            break;
    }
}

static void execute_memory(process_t *proc, uint8_t opcode, game_ctx_t *ctx)
{
    switch (opcode) {
        case 2:
            exec_ld(proc, ctx->memory);
            break;
        case 3:
            exec_st(proc, ctx->memory);
            break;
        case 10:
            exec_ldi(proc, ctx->memory);
            break;
        case 11:
            exec_sti(proc, ctx->memory);
            break;
        case 13:
            exec_lld(proc, ctx->memory);
            break;
        default:
            break;
    }
}

static void execute_control(process_t *proc, uint8_t opcode, game_ctx_t *ctx)
{
    switch (opcode) {
        case 9:
            exec_zjmp(proc, ctx->memory);
            break;
        case 12:
            exec_fork(proc, ctx->memory, &ctx->proc_list);
            break;
        case 15:
            exec_lfork(proc, ctx->memory, &ctx->proc_list);
            break;
        default:
            break;
    }
}

static void execute_special(process_t *proc, uint8_t opcode, game_ctx_t *ctx)
{
    switch (opcode) {
        case 1:
            exec_live(proc, ctx->memory, ctx);
            break;
        case 16:
            exec_aff(proc, ctx->memory);
            break;
        case 14:
            exec_lldi(proc, ctx->memory);
            break;
        default:
            break;
    }
}

void execute_instruction(process_t *proc, uint8_t opcode, game_ctx_t *ctx)
{
    execute_arithmetic(proc, opcode, ctx);
    execute_logical(proc, opcode, ctx);
    execute_memory(proc, opcode, ctx);
    execute_control(proc, opcode, ctx);
    execute_special(proc, opcode, ctx);
}
