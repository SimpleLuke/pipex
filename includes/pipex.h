#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**env;
	int		fd_in;
	int		fd_out;
	int		*pipes;
	int		*pids;
	int		child;
	int		here_doc;
	int		cmd_count;
	char	**cmd_args;
	char	*cmd;
}	t_data;

// init.c
void	init_data(int argc, char **argv, char **env, t_data *data);

// pipex.c
int		pipex(t_data *data);

// cmd.c
// char	*get_cmd(t_data *data, int child_no);
char	*get_cmd(char *cmd, t_data *data);
// utils.c
int		print_err(char *msg1, char *msg2, int errstate);
void	err_exit(int errstate, t_data *data);

// file_utils.c
void	setup_file_input(t_data *data);
void	setup_file_output(t_data *data);

// close.c
void	close_fds(t_data *data);
#endif // !PIPEX_H
