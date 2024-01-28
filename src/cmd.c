#include "../includes/pipex.h"
#include <sys/unistd.h>
#include <unistd.h>

void	format_list(char **env_list)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (env_list[i])
	{
		tmp = env_list[i];
		env_list[i] = ft_strjoin(env_list[i], "/");
		ft_free((void **)&tmp);
		i++;
	}
}

char	**get_env_list(t_data *data)
{
	int		i;
	char	*path;
	char	**env_list;

	i = 0;
	path = NULL;
	while (data->env[i])
	{
		if(!ft_strncmp("PATH=", data->env[i], 5))
		{
			path = data->env[i] + 5;
			break;
		}
		i++;
	}
	env_list = ft_split(path, ':');
	format_list(env_list);
	return (env_list);
}

char	*get_cmd(char *cmd, t_data *data)
{
	char	**env_list;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	env_list = get_env_list(data);
	while (env_list[i])
	{
		cmd_path = ft_strjoin(env_list[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		ft_free((void **)&cmd_path);
		i++;
	}
	ft_free_strarr(env_list);
	return (cmd_path);
}
