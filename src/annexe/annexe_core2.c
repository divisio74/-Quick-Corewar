/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-pierre.baud
** File description:
** annexe_maze2
*/
#include "../../include/op.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int my_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n > 0 && *s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
        n--;
    }
    return n == (size_t)-1 ? 0 : (unsigned char)(*s1) - (unsigned char)(*s2);
}

size_t my_strlen(const char *str)
{
    size_t len = 0;

    while (str[len])
        len++;
    return len;
}

void *my_memcpy(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;

    for (size_t i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr = malloc(new_size);

    if (!new_ptr)
        return NULL;
    if (ptr)
        my_memcpy(new_ptr, ptr, old_size);
    free(ptr);
    return new_ptr;
}

int my_atoi(const char *str)
{
    int i = 0;
    int sign = 1;
    int result = 0;

    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}
