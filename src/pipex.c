#include "../includes/pipex.h"

int	pipex(t_data *data)
{
	while (data->child < data->cmd_count)
	{
		// data->cmd = get_cmd(data, data->child);
		data->cmd_args = ft_split(data->argv[data->child + 2 + data->here_doc], ' ');
		data->cmd = get_cmd(data->cmd_args[0], data);
		if (!data->cmd)
			print_err("command not found", data->cmd_args[0], 1);
		printf("%s\n", data->cmd);
		// int i = 0;
		// while (data->cmd_args[i])
		// {
		// 	printf("%s\n", data->cmd_args[i]);
		// 	i++;
		// }
		data->child++;
	}
	return (1);
}
