/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** read_header
*/

#include "../include/op.h"
#include "../include/corewar.h"
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

static uint32_t read_u32(int fd)
{
    uint8_t bytes[4];

    if (read(fd, bytes, 4) != 4)
        return 0;
    return ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) |
        ((uint32_t)bytes[2] << 8) | ((uint32_t)bytes[3]);
}

int read_header(int fd, header_t *header)
{
    if (!header)
        return -1;
    header->magic = read_u32(fd);
    if (header->magic != COREWAR_EXEC_MAGIC)
        return -1;
    if (read(fd, header->prog_name, 128) != 128)
        return -1;
    if (lseek(fd, 4, SEEK_CUR) == (off_t)-1)
        return -1;
    header->prog_size = read_u32(fd);
    if (read(fd, header->comment, 2048) != 2048)
        return -1;
    if (lseek(fd, 4, SEEK_CUR) == (off_t)-1)
        return -1;
    return 0;
}
