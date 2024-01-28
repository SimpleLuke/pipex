#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		exit_code;

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
	if (!env)
		err_exit(print_err("Invalid environment variables", NULL, 1), NULL);
	init_data(argc, argv, env, &data);
	exit_code = pipex(&data);
	// printf("Enter to continue...\n");
	// getchar();
	// err_exit(1, &data);
	return (exit_code);
}
