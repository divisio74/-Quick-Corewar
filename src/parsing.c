/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** parsing
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/op.h"
#include "../include/corewar.h"

static void handle_n(char **argv, champion_t *champions,
    parsing_args_t *p_args)
{
    p_args->i++;
    champions[p_args->champ_n].number = my_atoi(argv[p_args->i]);
    champions[p_args->champ_n].flag_address = -1;
    if (my_strcmp(argv[p_args->i + 1], "-a") == 0) {
        p_args->i += 2;
        champions[p_args->champ_n].flag_address = my_atoi(argv[p_args->i]);
    }
    p_args->i++;
    load_champion_to_parse(argv[p_args->i], &champions[p_args->champ_n]);
    p_args->champ_n++;
}

static void handle_champ(char **argv, champion_t *champions,
    parsing_args_t *p_args)
{
    champions[p_args->champ_n].number = p_args->champ_n + 1;
    champions[p_args->champ_n].flag_address = -1;
    load_champion_to_parse(argv[p_args->i], &champions[p_args->champ_n]);
    p_args->champ_n++;
}

int parsing_args(int argc, char **argv, champion_t *champions, int *dump_cycle)
{
    parsing_args_t p_args = {0};

    for (p_args.i = 1; p_args.i < argc && p_args.champ_n < MAX_CHAMPIONS;
        p_args.i++) {
        if (my_strcmp(argv[p_args.i], "-dump") == 0 && p_args.i + 1 < argc) {
            p_args.i++;
            *dump_cycle = my_atoi(argv[p_args.i]);
            continue;
        }
        if (my_strcmp(argv[p_args.i], "-n") == 0 && p_args.i + 2 < argc) {
            handle_n(argv, champions, &p_args);
            continue;
        }
        handle_champ(argv, champions, &p_args);
    }
    return p_args.champ_n;
}
