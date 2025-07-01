/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** annexe_game
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../include/op.h"
#include "../../include/corewar.h"

static void remove_process(process_t **proc_list, process_t *prev,
    process_t *current)
{
    process_t *to_free = current;

    if (prev)
        prev->next = current->next;
    else
        *proc_list = current->next;
    current = current->next;
    my_putstr("Processus ");
    my_put_nbr(to_free->id);
    my_putstr(" est mort.\n");
    free(to_free);
}

void remove_dead_processes(process_t **proc_list)
{
    process_t *prev = NULL;
    process_t *to_remove = NULL;
    process_t *current = *proc_list;

    while (current != NULL) {
        if (!current->alive) {
            to_remove = current;
            current = current->next;
            remove_process(proc_list, prev, to_remove);
        } else {
            my_putstr("Processus : ");
            my_put_nbr(current->id);
            my_putstr(" est vivant\n");
            prev = current;
            current = current->next;
        }
    }
}

int count_living_processes(process_t *proc_list)
{
    int count = 0;

    while (proc_list != NULL) {
        if (proc_list->alive)
            count++;
        proc_list = proc_list->next;
    }
    return count;
}

void announce_winner(process_t *proc_list)
{
    if (proc_list != NULL) {
        my_putstr("Le gagnant est le champion : ");
        my_put_nbr(proc_list->id);
        my_putchar('\n');
    } else {
        my_putstr("Aucun survivant !\n");
    }
}

void free_all_processes(process_t *proc_list)
{
    process_t *current = proc_list;
    process_t *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
