/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** annexe_print
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "../../include/op.h"
#include "../../include/corewar.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_put_nbr(int nb)
{
    long nbr = nb;
    int count = 0;

    if (nbr < 0) {
        my_putchar(45);
        nbr = nbr * - 1;
        count++;
    }
    if (nbr >= 10) {
        count += my_put_nbr(nb / 10);
    }
    my_putchar(nbr % 10 + 48);
    return count + 1;
}

int my_putstr(char *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++) {
        my_putchar(str[i]);
    }
    return i;
}
