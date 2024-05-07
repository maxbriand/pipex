/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:37 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/07 18:17:46 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exe_snd_cmd(t_data *pipex, char **envp, int *pipefd)
{
	close(pipefd[1]);
	pipex->path_cmd_two = ft_check_path(pipex, pipex->av2, envp, \
		&(pipex->acs2));
	if (dup2(pipefd[0], 0) == -1)
		return ;
	if (dup2(pipex->fd_outfile, 1) == -1)
		return ;
	execve(pipex->path_cmd_two, pipex->cmd_two, envp);
	close(pipefd[0]);
	ft_exit_failure("Second cmd execution issue in ft_pipex.c", pipex);
}

static void	ft_exe_fst_cmd(t_data *pipex, char **envp, int *pipefd)
{
	int	fd_infile;

	close(pipefd[0]);
	pipex->path_cmd_one = ft_check_path(pipex, pipex->av1, envp, \
		&(pipex->acs1));
	fd_infile = open(pipex->infile, O_RDONLY);
	if (fd_infile == -1)
		return ;
	if (dup2(fd_infile, 0) == -1)
		return ;
	if (dup2(pipefd[1], 1) == -1)
		return ;
	execve(pipex->path_cmd_one, pipex->cmd_one, envp);
	close(fd_infile);
	close(pipefd[1]);
}

static void	ft_end_parent(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
}

void	ft_pipex(t_data *pipex, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		ft_exit_failure("Pipe function issue in ft_pipex.c", pipex);
	pid = fork();
	if (pid == -1)
		ft_exit_failure("Fork function n1 issue in ft_pipex.c", pipex);
	if (pid == 0)
	{
		ft_exe_fst_cmd(pipex, envp, pipefd);
		ft_exit_failure("First command execution issue in ft_pipex.c", pipex);
	}
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_exit_failure("Fork function n2 issue in ft_pipex.c", pipex);
		if (pid2 == 0)
			ft_exe_snd_cmd(pipex, envp, pipefd);
	}
	ft_end_parent(pipefd);
}
