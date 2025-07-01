/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** main
*/
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "../include/op.h"
#include "../include/corewar.h"

int main(int argc, char **argv)
{
    champion_t champions[MAX_CHAMPIONS];
    int flag_dump = -1;
    uint8_t memory[MEM_SIZE] = {0};
    int champion_count;

    champion_count = parsing_args(argc, argv, champions, &flag_dump);
    load_champions_into_memory(champions, champion_count, memory);
    run_game(champions, champion_count, memory, flag_dump);
    return 0;
}
