/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:37 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/07 22:47:10 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//  env -i ./pipex in "cat" "cat" outfile
// close fd in check_path if error occurs
static void	ft_exe_cmd2(t_data *pipex, char **envp, int *pipefd)
{
	close(pipefd[1]);
	pipex->path_cmd_two = ft_check_path(pipex, pipex->av2, envp, \
		&(pipex->acs2));
	if (dup2(pipefd[0], 0) == -1)
		return ;
	close(pipefd[0]);
	if (dup2(pipex->fd_outfile, 1) == -1)
		return ;
	close(pipex->fd_outfile);
	pipex->fd_outfile = -1;
	execve(pipex->path_cmd_two, pipex->cmd_two, envp);
	ft_exit_failure("Second cmd execution issue in ft_pipex.c", pipex);
}

static void	ft_exe_cmd1(t_data *pipex, char **envp, int *pipefd)
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
	close(fd_infile);
	if (dup2(pipefd[1], 1) == -1)
		return ;
	close(pipefd[1]);
	close(pipex->fd_outfile);
	pipex->fd_outfile = -1;
	execve(pipex->path_cmd_one, pipex->cmd_one, envp);
	ft_exit_failure("First command execution issue in ft_pipex.c", pipex);
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
	pid_t	pid;
	pid_t	pid2;

	if (pipe(pipex->pipefd) == -1)
		ft_exit_failure("Pipe function issue in ft_pipex.c", pipex);
	pid = fork();
	if (pid == -1)
		ft_exit_failure("Fork function n1 issue in ft_pipex.c", pipex);
	if (pid == 0)
		ft_exe_cmd1(pipex, envp, pipex->pipefd);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_exit_failure("Fork function n2 issue in ft_pipex.c", pipex);
		if (pid2 == 0)
			ft_exe_cmd2(pipex, envp, pipex->pipefd);
	}
	ft_end_parent(pipex->pipefd);
}
