/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** load_champions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/op.h"
#include "../include/corewar.h"

unsigned char *read_code(int fd, int size)
{
    unsigned char *code = malloc(size);

    if (!code)
        return NULL;
    if (read(fd, code, size) != size) {
        free(code);
        return NULL;
    }
    return code;
}

int load_champion_to_parse(const char *filename, champion_t *champion)
{
    int fd = open(filename, O_RDONLY);
    int size;

    if (fd < 0)
        return -1;
    if (read_header(fd, &champion->header) == -1) {
        close(fd);
        return -1;
    }
    size = champion->header.prog_size;
    champion->code = read_code(fd, size);
    if (!champion->code) {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

static void copy_champion_to_memory(champion_t *champion, uint8_t *memory,
    int *addr, int gap)
{
    if (champion->flag_address != -1) {
        my_memcpy(memory + champion->flag_address, champion->code,
            champion->header.prog_size);
        my_putstr("Champion ");
        my_put_nbr(champion->number);
        my_putstr(" -> adresse ");
        my_put_nbr(champion->flag_address);
        *addr += champion->header.prog_size;
    } else {
        my_memcpy(memory + *addr, champion->code, champion->header.prog_size);
        champion->flag_address = *addr;
        my_putstr("Champion ");
        my_put_nbr(champion->number);
        my_putstr(" -> adresse ");
        my_put_nbr(*addr);
        my_putchar('\n');
        *addr += gap;
    }
    if (*addr > MEM_SIZE)
        *addr %= MEM_SIZE;
}

void load_champions_into_memory(champion_t *champions, int champion_count,
    uint8_t *memory)
{
    int addr = 0;
    int gap = MEM_SIZE / champion_count;

    for (int i = 0; i < champion_count; i++) {
        if (champions[i].header.prog_size + addr > MEM_SIZE)
            return;
        copy_champion_to_memory(&champions[i], memory, &addr, gap);
    }
}
