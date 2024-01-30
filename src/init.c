/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:46:22 by llai              #+#    #+#             */
/*   Updated: 2024/01/30 15:40:43 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void		init_data(int argc, char **argv, char **env, t_data *data);
static void	default_data(t_data *data);
static void	init_pipes(t_data *data);

void	init_data(int argc, char **argv, char **env, t_data *data)
{
	default_data(data);
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	if (!ft_strncmp("here_doc", argv[1], 9))
		data->here_doc = 1;
	data->cmd_count = data->argc - 3 - data->here_doc;
	data->pids = malloc(sizeof(int) * data->cmd_count);
	if (!data->pids)
		err_exit(print_err("Malloc error", "data->pids", EXIT_FAILURE), data);
	set_infile_fd(data);
	set_outfile_fd(data);
	init_pipes(data);
}

static void	default_data(t_data *data)
{
	data->argc = 0;
	data->argv = NULL;
	data->env = NULL;
	data->infile_fd = -1;
	data->outfile_fd = -1;
	data->pipes = NULL;
	data->pids = NULL;
	data->child_idx = 0;
	data->here_doc = 0;
	data->cmd_count = 0;
	data->cmd = NULL;
	data->cmd_args = NULL;
	data->exit_code = 0;
}

static void	init_pipes(t_data *data)
{
	int	i;

	data->pipes = malloc(sizeof(int) * 2 * (data->cmd_count - 1));
	if (!data->pipes)
		err_exit(print_err("Malloc error", "data->pipes", EXIT_FAILURE), data);
	i = -1;
	while (++i < data->cmd_count - 1)
		if (pipe(data->pipes + 2 * i) == -1)
			err_exit(print_err("Pipe error", NULL, EXIT_FAILURE), data);
}
