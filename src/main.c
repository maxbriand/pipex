/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:57:45 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/07 17:57:58 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_fill_cmd(t_data *pipex, char **av)
{
	pipex->cmd_one = ft_split(av[1], ' ');
	if (pipex->cmd_one == NULL)
		ft_exit_failure("issue command creation in main.c", pipex);
	pipex->cmd_two = ft_split(av[2], ' ');
	if (pipex->cmd_two == NULL)
		ft_exit_failure("issue command creation in main.c", pipex);
}

static void	ft_init_pipex(t_data *pipex, char **av, int ac)
{
	if (ac >= 2)
		pipex->av1 = av[1];
	if (ac >= 3)
		pipex->av2 = av[2];
	pipex->cmd_one = NULL;
	pipex->cmd_two = NULL;
	pipex->path_cmd_one = NULL;
	pipex->path_cmd_two = NULL;
	if (ac >= 1)
		pipex->infile = av[0];
	if (ac >= 4)
		pipex->outfile = av[3];
	pipex->acs1 = 0;
	pipex->acs2 = 0;
	pipex->fd_outfile = -1;
}

int	main(int ac, char **av, char **envp)
{
	t_data	*pipex;

	ac -= 1;
	av++;
	pipex = malloc(sizeof(t_data));
	if (pipex == NULL)
		ft_exit_failure("malloc issue on pipex variable", pipex);
	ft_init_pipex(pipex, av, ac);
	ft_parsing(pipex, ac, av);
	ft_fill_cmd(pipex, av);
	ft_pipex(pipex, envp);
	ft_exit_success(pipex);
	return (0);
}
