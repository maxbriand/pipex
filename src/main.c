#include "pipex.h"

// handle ./bin/ls ? what's the behavior when I unset path in env var?
	// if I use the path as command the command is run?

static void	ft_init_pipex(t_data *pipex, char **av)
{
	pipex->cmd_one = NULL;
	pipex->cmd_two = NULL;
	pipex->path_cmd_one = NULL;
	pipex->path_cmd_two = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_data	*pipex;

	ac -= 1;
	av++;
	pipex = malloc(sizeof(t_data));
	if (pipex == NULL)
		ft_exit_failure("malloc issue on pipex variable", pipex);
	ft_init_pipex(pipex, av);
	ft_parsing(pipex, ac, av, envp);
	pipex->cmd_one = ft_split(av[1], ' ');
	// if ()
		// protection
	pipex->cmd_two = ft_split(av[2], ' ');
	// if ()
		// protection
	pipex->infile = av[0];
	pipex->outfile = av[3];
	ft_pipex(pipex, envp);
	ft_exit_success(pipex);
	return (0);
}
