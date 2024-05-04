#include "pipex.h"

static void	ft_free_pipex(t_data *pipex)
{
	if (pipex->path_cmd_one != NULL)
		free(pipex->path_cmd_one);
	if (pipex->path_cmd_two != NULL)
		free(pipex->path_cmd_two);
	free(pipex);
}

void	ft_exit_failure(char *msg, t_data *pipex)
{
	if (pipex != NULL)
		ft_free_pipex(pipex);
	write(2, "Error:\n", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	ft_exit_success(t_data *pipex)
{
	if (pipex != NULL)
		ft_free_pipex(pipex);
	exit(EXIT_SUCCESS);
}
