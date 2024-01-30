/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:46:34 by llai              #+#    #+#             */
/*   Updated: 2024/01/30 15:38:36 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void		close_fds(t_data *data);
static void	close_pipes(t_data *data);

void	close_fds(t_data *data)
{
	if (data->infile_fd != -1)
		close(data->infile_fd);
	if (data->outfile_fd != -1)
		close(data->outfile_fd);
	close_pipes(data);
}

static void	close_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < (data->cmd_count - 1) * 2)
		close(data->pipes[i]);
}
