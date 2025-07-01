/*
** EPITECH PROJECT, 2025
** B-CPE-200-LYN-2-1-corewar-mathieu.girard
** File description:
** my_op
*/

#ifndef INCLUDED_OP_H
    #define INCLUDED_OP_H
    #include <stdint.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <fcntl.h>
    #define MEM_SIZE (6 * 1024)
    #define IDX_MOD 512 /* modulo of the index < */
    #define MAX_ARGS_NUMBER 4 /* this may not be changed 2^*IND_SIZE */
    #define COMMENT_CHAR '#'
    #define LABEL_CHAR ':'
    #define DIRECT_CHAR '%'
    #define SEPARATOR_CHAR ','
    #define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"
    #define NAME_CMD_STRING ".name"
    #define COMMENT_CMD_STRING ".comment"
    #define REG_NUMBER 16 /* r1 <--> rx */

typedef char args_type_t;

    #define T_REG 1 /* register */
    #define T_DIR 2 /* direct  (ld  #1,r1  put 1 into r1) */
    #define T_IND 4
    #define T_LAB 8 /* LABEL */

    #define IND_SIZE 2
    #define DIR_SIZE 4
    #define REG_SIZE DIR_SIZE

    #define PROG_NAME_LENGTH 128
    #define COMMENT_LENGTH 2048
    #define COREWAR_EXEC_MAGIC 0xea83f3

    #define CYCLE_TO_DIE 1536 /* number of cycle before beig declared dead */
    #define CYCLE_DELTA 5
    #define NBR_LIVE 40
    #define MAX_CHAMPIONS 4

typedef struct op_s {
    char *mnemonique;
    char nbr_args;
    args_type_t type[MAX_ARGS_NUMBER];
    char code;
    int nbr_cycles;
    char *comment;
} op_t;

typedef struct header_s {
    uint32_t magic;
    char prog_name[128];
    uint32_t prog_size;
    char comment[2048];
} header_t;

typedef struct champion_s {
    int number;
    int flag_address;
    header_t header;
    unsigned char *code;
    int last_live_cycle;

} champion_t;

typedef struct parsing_args_s {
    int champ_n;
    int i;
} parsing_args_t;

typedef struct process_s {
    int pc;
    int reg[16];
    int carry;
    int alive;
    int id;
    struct process_s *next;
} process_t;

typedef struct game_ctx_s {
    champion_t *champions;
    int champion_count;
    int current_cycle;
    int live_count;
    int cycle_to_die;
    process_t *proc_list;
    uint8_t *memory;
} game_ctx_t;

#endif
