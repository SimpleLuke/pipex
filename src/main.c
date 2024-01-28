#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		if (argc > 1 && !ft_strncmp("here_doc", argv[1], 9))
			err_exit(print_err("Invalid arguments",
					  "./pipex here_doc LIMITER cmd cmd1 file", 1), NULL);
		else
			err_exit(print_err("Invalid arguments",
					  "./pipex infile cmd ... cmdn outfile", 1), NULL);
	}
	else if (argc < 6 && !ft_strncmp("here_doc", argv[1], 9))
			err_exit(print_err("Invalid arguments",
					  "./pipex here_doc LIMITER cmd cmd1 file", 1), NULL);
	(void)env;
	return (0);
}
