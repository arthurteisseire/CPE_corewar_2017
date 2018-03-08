/*
** EPITECH PROJECT, 2017
** File Name : init_buffer.c
** File description:
** by Arthur Teisseire
*/

#include <stdlib.h>
#include "asm.h"
#include "buffer.h"
#include "line.h"

void init_buffer(buffer_t *buffer)
{
	buffer->lines = NULL;
	buffer->labels = NULL;
	buffer->nb_lines = 0;
	buffer->curr_byte = 0;
	buffer->nb_labels = 0;
}