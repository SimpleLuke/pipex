#include "../includes/pipex.h"

static void	default_data(t_data *data)
{
	data->argc = 0;
	data->argv = NULL;
	data->env = NULL;
	data->fd_in = -1;
	data->fd_out = -1;
	data->pipes = NULL;
	data->pids = NULL;
	data->child = 0;
	data->here_doc = 0;
	data->cmd_count = 0;
	data->cmd = NULL;
	data->cmd_args = NULL;
}

static void	init_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count - 1)
	{
		if (pipe(data->pipes + 2 * i) == -1)
			err_exit(print_err("Pipe error", NULL, 1), data);
		i++;
	}
}

void	init_data(int argc, char **argv, char **env, t_data *data)
{
	default_data(data);
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	if (!ft_strncmp("here_doc", argv[1], 9))
		data->here_doc = 1;
	data->cmd_count = data->argc - 3 - data->here_doc;
	setup_file_input(data);
	setup_file_output(data);
	data->pipes = malloc(sizeof(int) * 2 * (data->cmd_count - 1));
	if (!data->pipes)
		err_exit(print_err("Malloc error", "data->pipes", 1), data);
	data->pids = malloc(sizeof(int) * data->cmd_count);
	if (!data->pids)
		err_exit(print_err("Malloc error", "data->pids", 1), data);
	init_pipes(data);
	// printf("IN:%d, OUT:%d\n", data->fd_in, data->fd_out);
}
