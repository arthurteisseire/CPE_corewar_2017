/*
** EPITECH PROJECT, 2018
** Corewar
** File description:
** manage header
*/

#include <stdlib.h>
#include "parse.h"
#include "buffer.h"
#include "my.h"
#include "op.h"
#include "line.h"
#include "asm.h"
#include "errors.h"
#include "token.h"

static char **split_header(char *str, char const *sep)
{
	char **arr = split(str, "\"");

	arr[0] = get_next_word(&str, sep);

	int i = 0;
	while (arr[i] != NULL) {
		printf("arr[%d] = %s\n", i, arr[i]);
		i++;
	}
	printf("\n\n");
	return(arr);
}

static int check_header(char *name, char *comment, int index_name, int index_comment)
{
	char **name_arr = split_header(name, separators);
	char **comment_arr;

	comment_arr = split_header(comment, separators);
	if (((my_strcmp(name_arr[0], NAME_CMD_STRING) != 0 && my_strcmp(name_arr[0], COMMENT_CMD_STRING) != 0) && get_id_cmd(name_arr[0]) == -1)) {
		true_index(-1);
		true_index(index_name);
		put_err_asm(INVALID_INSTRUCTION);
		return (-1);
	}
	if (((my_strcmp(comment_arr[0], COMMENT_CMD_STRING) != 0 && my_strcmp(comment_arr[0], NAME_CMD_STRING) != 0) && get_id_cmd(comment_arr[0]) == -1)) {
		put_err_asm(INVALID_INSTRUCTION);
		return (-1);
	}
	if (my_strcmp(name_arr[0], NAME_CMD_STRING) != 0 && my_strcmp(comment_arr[0], COMMENT_CMD_STRING) == 0) {
		true_index(-1);
		true_index(index_name);
		put_err_asm(MISPLACED_NAME);
		return (-1);
	}
	if (my_strcmp(name_arr[0], NAME_CMD_STRING) == 0 && my_strcmp(comment_arr[0], COMMENT_CMD_STRING) != 0) {
		true_index(-1);
		true_index(index_name);
		put_err_asm(NO_COMMENT_W);
		return (-1);
	}
	if (my_strcmp(name_arr[0], COMMENT_CMD_STRING) == 0 && my_strcmp(comment_arr[0], NAME_CMD_STRING) == 0) {
		true_index(-1);
		true_index(index_name);
		put_err_asm(MISPLACED_COMMENT);
		return (-1);
	}
	if (my_arrlen(name_arr) > 2 || (nb_char_in_str('\"', name) != 2 && my_arrlen(name_arr) == 2)) {
		true_index(-1);
		true_index(index_name);
		put_err_asm(SYNTAX_ERROR);
		return (-1);
	}
	if (my_arrlen(comment_arr) > 2  || (nb_char_in_str('\"', comment) != 2 && my_arrlen(comment_arr) == 2)) {
		put_err_asm(SYNTAX_ERROR);
		return (-1);
	}
	if (my_arrlen(name_arr) == 1) {
		true_index(-1);
		true_index(index_name);
		put_err_asm(NO_NAME);
		return (-1);
	}
	if (my_arrlen(comment_arr) == 1) {
		put_err_asm(EMPTY_COMMENT);
		return (-1);
	}
	return (0);
}

static int set_comment_and_name(char *name, char *comment, header_t *header)
{
	char **name_cpy = split_header(name, separators);
	char **comment_cpy = split_header(comment, separators);

	my_strcpy(header->prog_name, name_cpy[1]);
	my_strcpy(header->comment, comment_cpy[1]);
	header->magic = COREWAR_EXEC_MAGIC;
	free_array(name_cpy);
	free_array(comment_cpy);
	return (0);
}

int set_header(header_t *header, int fd)
{
	char *name = get_next_line(fd);
	char *comment;
	int index_name = 0;
	int index_comment = 0;

	skip_comments(fd, &name, separators);
	index_name = true_index(0);
	comment = get_next_line(fd);
	if (comment == NULL) {
		put_err_asm(SYNTAX_ERROR);
		return (-1);
	}
	skip_comments(fd, &comment, separators);
	index_comment = true_index(0);

	if (name == NULL) {
		put_or_init_err(NULL, 0);
		my_puterror(" :");
		my_puterror(EMPTY_FILE);
		my_puterror("\n");
		free(name);
		free(comment);
		return (-1);
	}
	name = my_clean_str(name, '\t');
	name = my_clean_str(name, ' ');
	if (comment != NULL) {
		comment = my_clean_str(comment, ' ');
		comment = my_clean_str(comment, '\t');
	}
	if (check_header(name, comment, index_name, index_comment) == -1) {
		free(name);
		free(comment);	
		return (-1);
	}
	set_comment_and_name(name, comment, header);
	free(name);
	free(comment);
	return (0);
}
