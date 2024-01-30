/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:47:04 by llai              #+#    #+#             */
/*   Updated: 2024/01/30 14:36:39 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdlib.h>

int		print_err(char *msg1, char *msg2, int errstate);
void	err_exit(int errstate, t_data *data);

int	print_err(char *msg1, char *msg2, int errstate)
{
	ft_putstr_fd(msg1, 2);
	if (msg2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg2, 2);
	}
	ft_putstr_fd("\n", 2);
	return (errstate);
}

void	err_exit(int errstate, t_data *data)
{
	if (data)
	{
		close_fds(data);
		if (data->pipes)
			ft_free((void **)&data->pipes);
		if (data->pids)
			ft_free((void **)&data->pids);
	}
	exit(errstate);
}
