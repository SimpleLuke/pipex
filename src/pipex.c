/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:46:43 by llai              #+#    #+#             */
/*   Updated: 2024/01/30 15:33:11 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>

void		pipex(t_data *data);
static void	run_child(t_data *data);
static void	run_parent(t_data *data);
static void	replace_stream(int input, int output, t_data *data);

void	pipex(t_data *data)
{
	while (data->child_idx < data->cmd_count)
	{
		data->cmd_args = ft_split(data->argv[data->child_idx
				+ 2 + data->here_doc], ' ');
		data->cmd = get_cmd(data->cmd_args[0], data);
		if (!data->cmd)
			print_err(data->cmd_args[0], "command not found", EXIT_FAILURE);
		data->pids[data->child_idx] = fork();
		if (data->pids[data->child_idx] == -1)
			err_exit(print_err("Fork error", NULL, EXIT_FAILURE), data);
		if (data->pids[data->child_idx] == 0)
			run_child(data);
		ft_free((void **)&data->cmd);
		ft_free_strarr(data->cmd_args);
		data->child_idx++;
	}
	run_parent(data);
}

static void	run_child(t_data *data)
{
	if (data->child_idx == 0)
		replace_stream(data->infile_fd, data->pipes[1], data);
	else if (data->child_idx == data->cmd_count - 1)
		replace_stream(data->pipes[data->child_idx * 2 - 2],
			data->outfile_fd, data);
	else
		replace_stream(data->pipes[data->child_idx * 2 - 2],
			data->pipes[data->child_idx * 2 + 1], data);
	close_fds(data);
	if (data->cmd_args == NULL || data->cmd == NULL)
		err_exit(EXIT_FAILURE, data);
	if (execve(data->cmd, data->cmd_args, data->env) == -1)
		err_exit(print_err(data->cmd_args[0],
				strerror(errno), EXIT_FAILURE), data);
}

static void	replace_stream(int input, int output, t_data *data)
{
	if (dup2(input, STDIN_FILENO) == -1)
		err_exit(1, data);
	if (dup2(output, STDOUT_FILENO) == -1)
		err_exit(1, data);
}

static void	run_parent(t_data *data)
{
	int	wpid;
	int	status;

	close_fds(data);
	while (--data->child_idx >= 0)
	{
		wpid = waitpid(data->pids[data->child_idx], &status, 0);
		if (wpid == data->pids[data->cmd_count - 1])
			if ((data->child_idx == (data->cmd_count - 1)) && WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
	}
	ft_free((void **)&data->pipes);
	ft_free((void **)&data->pids);
	if (data->here_doc)
		unlink(".temp_heredoc");
}
