/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:15:01 by llai              #+#    #+#             */
/*   Updated: 2024/01/29 11:20:24 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <unistd.h>

void	create_heredoc(t_data *data)
{
	int		fd;
	int		stdin_dup;
	int		is_open;
	char	*line;

	fd = open(".temp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_err("here_doc", strerror(errno), 1);
	stdin_dup = dup(STDIN_FILENO);
	is_open = 1;
	while (true)
	{
		if (is_open)
			ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(stdin_dup);
		if (line == NULL)
			break ;
		if (ft_strlen(line) == ft_strlen(data->argv[2]) + 1
			&& !ft_strncmp(line, data->argv[2], ft_strlen(data->argv[2])))
			is_open = close(stdin_dup);
		else
			ft_putstr_fd(line, fd);
		ft_free((void **)&line);
	}
	close(fd);
}

void	setup_file_input(t_data *data)
{
	if (!data->here_doc)
	{
		data->fd_in = open(data->argv[1], O_RDONLY, 0644);
		if (data->fd_in == -1)
			print_err(data->argv[1], strerror(errno), 1);
	}
	else
	{
		create_heredoc(data);
		data->fd_in = open(".temp_heredoc", O_RDONLY, 0644);
		if (data->fd_in == -1)
			print_err("here_doc", strerror(errno), 1);
	}
}

void	setup_file_output(t_data *data)
{
	if (!data->here_doc)
		data->fd_out = open(data->argv[data->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		data->fd_out = open(data->argv[data->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd_out == -1)
		print_err(data->argv[data->argc - 1], strerror(errno), 1);
}
