/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:46:54 by llai              #+#    #+#             */
/*   Updated: 2024/01/30 15:35:12 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void		set_infile_fd(t_data *data);
void		set_outfile_fd(t_data *data);
static void	create_heredoc(t_data *data);

void	set_infile_fd(t_data *data)
{
	if (!data->here_doc)
	{
		data->infile_fd = open(data->argv[1], O_RDONLY, FILE_PERMISSION);
		if (data->infile_fd == -1)
			print_err(data->argv[1], strerror(errno), EXIT_FAILURE);
	}
	else
	{
		create_heredoc(data);
		data->infile_fd = open(".temp_heredoc", O_RDONLY, FILE_PERMISSION);
		if (data->infile_fd == -1)
			print_err("here_doc", strerror(errno), EXIT_FAILURE);
	}
}

void	set_outfile_fd(t_data *data)
{
	if (!data->here_doc)
		data->outfile_fd = open(data->argv[data->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		data->outfile_fd = open(data->argv[data->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (data->outfile_fd == -1)
		print_err(data->argv[data->argc - 1], strerror(errno), EXIT_FAILURE);
}

static void	create_heredoc(t_data *data)
{
	int		fd;
	int		stdin_dup;
	int		is_open;
	char	*line;

	fd = open(".temp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, FILE_PERMISSION);
	if (fd == -1)
		print_err("here_doc", strerror(errno), EXIT_FAILURE);
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
