/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** dump_memory
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../include/op.h"
#include "../include/corewar.h"

void my_putnbr_base(unsigned int nbr, const char *base)
{
    int len = 0;

    while (base[len])
        len++;
    if (nbr >= (unsigned int)len)
        my_putnbr_base(nbr / len, base);
    my_putchar(base[nbr % len]);
}

void print_hex_byte(uint8_t byte)
{
    if (byte < 16)
        my_putchar('0');
    my_putnbr_base(byte, "0123456789abcdef");
}

void dump_memory(uint8_t *memory, size_t size)
{
    for (size_t i = 0; i < size; i += 16) {
        my_putstr("0x");
        if (i < 0x1000)
            my_putchar('0');
        my_putnbr_base(i, "0123456789abcdef");
        my_putstr(": ");
        for (size_t j = 0; j < 16 && (i + j) < size; j++) {
            print_hex_byte(memory[i + j]);
            my_putchar(' ');
        }
        my_putchar('\n');
    }
}
