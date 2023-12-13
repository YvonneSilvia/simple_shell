#include "shell.h"
/**
*main - the main entry point
*@argc: - argument count
*@argv: - array of arguments
*Return: - always returns 0
*/
int main(int argc, char **argv)
{
	int fd = 2 + 3;
	info_t info[] = { INFO_INIT };

	if (argc == 2 && (fd = open(argv[1], O_RDONLY)) != -1)
		info->readfd = fd;
	else if (errno == EACCES)
		exit(126);
	else if (errno == ENOENT)
	{
		_eputs(argv[0]);
		_eputs(": 0 Can't open file ");
		_eputs(argv[1]);
		_eputchar('\n');
		_eputchar(BUF_FLUSH);
		exit(127);
	}
	populate_env_list(info);
	read_history(info);
	loop_shell(info, argv);
	return (EXIT_SUCCESS);
}
