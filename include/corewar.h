/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** corewar
*/

#ifndef INCLUDED_COREWAR_H
    #define INCLUDED_COREWAR_H
    #include <stdint.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <fcntl.h>
    #include "../include/op.h"

char *my_strchr(const char *s, int c);
size_t my_strlen(const char *str);
void *my_memcpy(void *dest, const void *src, size_t n);
int my_atoi(const char *str);
void *my_realloc(void *ptr, size_t old_size, size_t new_size);
char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, const char *src, size_t n);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, size_t n);
size_t my_strlen(const char *str);
int parsing_args(int argc, char **argv, champion_t *champions,
    int *dump_cycle);
void load_without_flags(char **argv, champion_t *champions,
    int *champion_count, int i);
int load_champion_to_parse(const char *filename, champion_t *champion);
void load_champions_into_memory(champion_t *champions, int count,
    uint8_t *memory);
unsigned char *read_code(int fd, int size);
int read_header(int fd, header_t *header);
void run_game(champion_t *champions, int champion_count, uint8_t *memory,
    int flag_dump);
process_t *init_processes(champion_t *champions, int count);
void execute_process(process_t *proc, game_ctx_t *ctx);
void execute_for_all(game_ctx_t *ctx);
void execute_instruction(process_t *proc, uint8_t opcode, game_ctx_t *ctx);
uint8_t get_argument_type(uint8_t *memory, process_t *proc, int arg_index);
int define_value_for_4oct(process_t *proc, uint8_t *memory, int *oct_temp,
    uint8_t arg_type);
int define_value_for_2oct(process_t *proc, uint8_t *memory, int *oct_temp,
    uint8_t type);
int extract_value_from_ind_no_mod(process_t *proc, uint8_t *memory,
    int *oct_temp);
int define_value_for_2oct_nomod(process_t *proc, uint8_t *memory,
    int *oct_temp,
    uint8_t type);
int extract_value_from_dir2(process_t *proc, uint8_t *memory,
    int *oct_temp);
int extract_value_from_dir4(process_t *proc, uint8_t *memory,
    int *oct_temp);
int extract_value_from_ind(process_t *proc, uint8_t *memory,
    int *oct_temp);
int extract_value_from_reg(process_t *proc, uint8_t *memory,
    int *oct_temp);
void store_result(process_t *proc, uint8_t reg_dest, int result);
void exec_ld(process_t *proc, uint8_t *memory);
void exec_live(process_t *proc, uint8_t *memory, game_ctx_t *ctx);
void exec_add(process_t *proc, uint8_t *memory);
void exec_and(process_t *proc, uint8_t *memory);
void exec_st(process_t *proc, uint8_t *memory);
void exec_sub(process_t *proc, uint8_t *memory);
void exec_or(process_t *proc, uint8_t *memory);
void exec_xor(process_t *proc, uint8_t *memory);
void exec_zjmp(process_t *proc, uint8_t *memory);
void exec_ldi(process_t *proc, uint8_t *memory);
void exec_sti(process_t *proc, uint8_t *memory);
void exec_fork(process_t *proc, uint8_t *memory, process_t **proc_list);
void exec_lld(process_t *proc, uint8_t *memory);
void exec_lldi(process_t *proc, uint8_t *memory);
void exec_lfork(process_t *proc, uint8_t *memory, process_t **proc_list);
void exec_aff(process_t *proc, uint8_t *memory);
void remove_dead_processes(process_t **proc_list);
int count_living_processes(process_t *proc_list);
void announce_winner(process_t *proc_list);
void free_all_processes(process_t *proc_list);
void my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char *str);
void my_putnbr_base(unsigned int nbr, const char *base);
void print_hex_byte(uint8_t byte);
void dump_memory(uint8_t *memory, size_t size);

#endif
