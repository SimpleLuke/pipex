/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:14:11 by llai              #+#    #+#             */
/*   Updated: 2024/01/29 11:14:35 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->cmd_count - 1) * 2)
	{
		close(data->pipes[i]);
		i++;
	}
}

void	close_fds(t_data *data)
{
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	close_pipes(data);
}

void	ft_free_strarr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_free((void **)&arr[i]);
		i++;
	}
	ft_free((void **)&arr);
}
