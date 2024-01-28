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
	data->cmds = NULL;
	data->cmd_args = NULL;
}

void	init_data(int argc, char **argv, char **env, t_data *data)
{
	default_data(data);
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	if (!ft_strncmp("here_doc", argv[0], 9))
		data->here_doc = 1;
	data->cmd_count = data->argc - 3 - data->here_doc;
	setup_file_input(data);
	setup_file_output(data);
	// printf("IN:%d, OUT:%d\n", data->fd_in, data->fd_out);
}
