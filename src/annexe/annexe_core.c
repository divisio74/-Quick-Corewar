/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-amazed-pierre.baud
** File description:
** annexe_maze
*/

#include "../../include/op.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *my_strchr(const char *s, int c)
{
    while (*s) {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    return NULL;
}

char *my_strcpy(char *dest, const char *src)
{
    char *ptr = dest;

    while (*src != '\0') {
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';
    return dest;
}

char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}
