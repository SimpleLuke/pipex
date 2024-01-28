#include "../includes/pipex.h"

void	setup_file_input(t_data *data)
{
	if (!data->here_doc)
	{
		data->fd_in = open(data->argv[1], O_RDONLY, 0644);
		if (data->fd_in == -1)
			print_err(data->argv[1], strerror(errno), 1);
			// print_err(strerror(errno), data->argv[1], 1);
	}
}

void	setup_file_output(t_data *data)
{
	if (!data->here_doc)
	{
		data->fd_out = open(data->argv[data->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (data->fd_out == -1)
			print_err(data->argv[data->argc - 1], strerror(errno), 1);
			// print_err(strerror(errno), data->argv[data->argc - 1], 1);
	}
}
