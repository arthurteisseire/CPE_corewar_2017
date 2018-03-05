/*
** EPITECH PROJECT, 2017
** File Name : asm.h
** File description:
** by Arthur Teisseire
*/

#ifndef ASM_H
#define ASM_H

typedef struct label {
	char *label;
	int line;
} label_t;

typedef struct token {
	char *str;
	int type;
	int cbyte;
} token_t;

typedef struct line {
	int label;
	int nb_bytes;	
	int nb_tokens;
	token_t *tokens;
} line_t;

typedef struct buffer {
	line_t *line;
	label_t *label;
	int curr_byte;
} buffer_t;

int my_asm(buffer_t *buffer, char *pathname);

#endif
