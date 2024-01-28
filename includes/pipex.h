#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**env;
}	t_data;

int		print_err(char *msg1, char *msg2, int errstate);
void	err_exit(int errstate, t_data *data);

#endif // !PIPEX_H
