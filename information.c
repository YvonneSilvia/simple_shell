#include "shell.h"
/**
*_set_info - function to set struct info
*@argv: - argument array
*@info: - struct type param
*Return: - returns nothing
*/
void _set_info(info_t *info, char **argv)
{
	int k = 0;

	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = _strwd1(info->arg, "\t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (k = 0; info->argv && info->argv[k]; k++)
			;
		info->argc = k;
		_replace_alias(info);
		replace_variables(info);
	}
}
/**
*_flush_info - clears information struct
*@info: - struct type param
*Return: - returns nothing
*/
void _flush_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
*_free_info - frees struct info
*@info: - struct type param
*@everything: - everything
*Return: - return nothing
*/
void _free_info(info_t *info, int everything)
{
	_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (everything)
	{
		if (!info->command_buffer)
			free(info->arg);
		if (info->env)
			_free_list(&(info->env));
		if (info->history)
			_free_list(&(info->history));
		if (info->alias)
			_free_list(&(info->alias));
		_ffree(info->environ);
		info->environ = NULL;
		buffer_free((void **)info->command_buffer);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
