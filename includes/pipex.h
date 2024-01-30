/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:47:30 by llai              #+#    #+#             */
/*   Updated: 2024/01/30 15:38:50 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>

# define FILE_PERMISSION 0666

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**env;
	int		infile_fd;
	int		outfile_fd;
	int		*pipes;
	int		*pids;
	int		child_idx;
	int		here_doc;
	int		cmd_count;
	char	**cmd_args;
	char	*cmd;
	int		exit_code;
}	t_data;

// init.c
void	init_data(int argc, char **argv, char **env, t_data *data);

// pipex.c
void	pipex(t_data *data);

// cmd.c
// char	*get_cmd(t_data *data, int child_no);
char	*get_cmd(char *cmd, t_data *data);

// error.c
int		print_err(char *msg1, char *msg2, int errstate);
void	err_exit(int errstate, t_data *data);

// file_utils.c
void	set_infile_fd(t_data *data);
void	set_outfile_fd(t_data *data);

// close.c
void	close_fds(t_data *data);

#endif // !PIPEX_H
