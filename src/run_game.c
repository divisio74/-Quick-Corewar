/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** run_game
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/op.h"
#include "../include/corewar.h"

static game_ctx_t init_game_context(champion_t *champions, int champion_count,
    uint8_t *memory)
{
    return (game_ctx_t){
        .champions = champions,
        .champion_count = champion_count,
        .current_cycle = 0,
        .live_count = 0,
        .cycle_to_die = CYCLE_TO_DIE,
        .proc_list = init_processes(champions, champion_count),
        .memory = memory
    };
}

static int limit_continue(game_ctx_t *ctx)
{
    if (ctx->proc_list == NULL)
        return 0;
    if (ctx->current_cycle > 10000)
        return 0;
    if (count_living_processes(ctx->proc_list) <= 0)
        return 0;
    return 1;
}

static void reset_alive_flags(process_t *proc_list)
{
    while (proc_list != NULL) {
        proc_list->alive = 0;
        proc_list = proc_list->next;
    }
}

static void perform_cycle_check(game_ctx_t *ctx, int *last_check)
{
    remove_dead_processes(&ctx->proc_list);
    *last_check = ctx->current_cycle;
    if (ctx->live_count >= NBR_LIVE) {
        ctx->cycle_to_die -= CYCLE_DELTA;
        if (ctx->cycle_to_die < 0)
            ctx->cycle_to_die = 0;
    }
    ctx->live_count = 0;
    reset_alive_flags(ctx->proc_list);
}

void run_game(champion_t *champions, int champion_count, uint8_t *memory,
    int flag_dump)
{
    game_ctx_t ctx = init_game_context(champions, champion_count, memory);
    int last_check = 0;

    while (limit_continue(&ctx)) {
        if (flag_dump != -1 && ctx.current_cycle == flag_dump) {
            my_putstr("\nDernier cycle ");
            my_put_nbr(ctx.current_cycle);
            my_putstr("\n");
            dump_memory(ctx.memory, MEM_SIZE);
            break;
        }
        execute_for_all(&ctx);
        ctx.current_cycle++;
        if ((ctx.current_cycle - last_check) >= ctx.cycle_to_die)
            perform_cycle_check(&ctx, &last_check);
    }
    announce_winner(ctx.proc_list);
    free_all_processes(ctx.proc_list);
}
