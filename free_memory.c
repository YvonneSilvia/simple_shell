#include "shell.h"
/**
*buffer_free - frees a pointer to a pointer to ptr
*@ptr: a pointer to a pointer param
*Return: - returns 1 success or 0 if pointer is NULL
*/
int buffer_free(void **ptr)
{
	if (!ptr || !*ptr)
		return (0);
	free(*ptr); /*free the pointer*/
	*ptr = NULL; /*set it to null*/
	return (1);
}
