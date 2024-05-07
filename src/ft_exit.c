/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:06 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/07 17:58:07 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free_pipex(t_data *pipex)
{
	if (pipex->path_cmd_one != NULL && pipex->acs1 == 0)
		free(pipex->path_cmd_one);
	if (pipex->path_cmd_two != NULL && pipex->acs2 == 0)
		free(pipex->path_cmd_two);
	if (pipex->cmd_one != NULL)
		ft_free_str_array(pipex->cmd_one);
	if (pipex->cmd_two != NULL)
		ft_free_str_array(pipex->cmd_two);
	if (pipex->fd_outfile != -1)
		close(pipex->fd_outfile);
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
}
