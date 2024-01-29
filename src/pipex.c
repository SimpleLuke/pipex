/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:21:59 by llai              #+#    #+#             */
/*   Updated: 2024/01/29 11:22:58 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>

void	redirect_stream(int input, int output, t_data *data);

void	run_child(t_data *data)
{
	if (data->child == 0)
		redirect_stream(data->fd_in, data->pipes[1], data);
	else if (data->child == data->cmd_count - 1)
		redirect_stream(data->pipes[data->child * 2 - 2], data->fd_out, data);
	else
		redirect_stream(data->pipes[data->child * 2 - 2],
			data->pipes[data->child * 2 + 1], data);
	close_fds(data);
	if (data->cmd_args == NULL || data->cmd == NULL)
		err_exit(1, data);
	if (execve(data->cmd, data->cmd_args, data->env) == -1)
		err_exit(print_err(data->cmd_args[0], strerror(errno), 1), data);
}

void	redirect_stream(int input, int output, t_data *data)
{
	if (dup2(input, STDIN_FILENO) == -1)
		err_exit(1, data);
	if (dup2(output, STDOUT_FILENO) == -1)
		err_exit(1, data);
}

int	run_parent(t_data *data)
{
	int	wpid;
	int	status;
	int	exit_code;

	close_fds(data);
	data->child--;
	exit_code = 1;
	while (data->child >= 0)
	{
		wpid = waitpid(data->pids[data->child], &status, 0);
		if (wpid == data->pids[data->cmd_count - 1])
			if ((data->child == (data->cmd_count - 1)) && WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		data->child--;
	}
	ft_free((void **)&data->pipes);
	ft_free((void **)&data->pids);
	return (exit_code);
}

int	pipex(t_data *data)
{
	int	exit_code;

	while (data->child < data->cmd_count)
	{
		data->cmd_args = ft_split(data->argv[data->child
				+ 2 + data->here_doc], ' ');
		data->cmd = get_cmd(data->cmd_args[0], data);
		if (!data->cmd)
			print_err(data->cmd_args[0], "command not found", 1);
		data->pids[data->child] = fork();
		if (data->pids[data->child] == -1)
			err_exit(print_err("Fork error", NULL, 1), data);
		if (data->pids[data->child] == 0)
			run_child(data);
		ft_free((void **)&data->cmd);
		ft_free_strarr(data->cmd_args);
		data->child++;
	}
	exit_code = run_parent(data);
	if (data->here_doc)
		unlink(".temp_heredoc");
	return (exit_code);
}
