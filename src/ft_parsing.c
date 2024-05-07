/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:37:03 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/07 18:08:38 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_sc(char **str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_wrong_infile(t_data *pipex, char *infile)
{
	if (access(infile, F_OK) == -1)
		ft_exit_failure("The infile doesn't exist", pipex);
	if (access(infile, R_OK) == -1)
		ft_exit_failure("The infile is not readable", pipex);
}

static void	ft_open_outfile(t_data *pipex)
{
	pipex->fd_outfile = open(pipex->outfile, O_WRONLY | O_TRUNC | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (pipex->fd_outfile == -1)
		ft_exit_failure("open outfile issue in main.c", pipex);
}

static void	ft_wrong_arg_number(t_data *pipex, int ac)
{
	if (ac < 4)
		ft_exit_failure("Too few arguments", pipex);
	if (ac > 4)
		ft_exit_failure("Too many arguments", pipex);
}

void	ft_parsing(t_data *pipex, int ac, char **av)
{
	ft_wrong_arg_number(pipex, ac);
	ft_open_outfile(pipex);
	ft_wrong_infile(pipex, *av);
}
