#include "pipex.h"

	// // test
	// char *buffer;
	// buffer = malloc(sizeof(char)*42);
	// buffer = get_next_line(pipefd[0]);
	// ft_printf("that's crazy %s end \n", buffer);

static void	ft_exe_snd_cmd(t_data *pipex, char **envp, int *pipefd)
{
	int fd_outfile;
	
	close(pipefd[1]);
	fd_outfile = open(pipex->outfile, O_RDWR | O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd_outfile == -1)
		return ;
	if (dup2(pipefd[0], 0) == -1)
		return ;
	if (dup2(fd_outfile, 1) == -1)
		return ;
	execve(pipex->path_cmd_two, pipex->cmd_two, envp);
}

static void	ft_exe_fst_cmd(t_data *pipex, char **envp, int *pipefd)
{
	int	fd_infile;
	
	close(pipefd[0]);
	fd_infile = open(pipex->infile, O_RDONLY);
	if (fd_infile == -1)
		return ;
	if (dup2(fd_infile, 0) == -1)
		return ;
	if (dup2(pipefd[1], 1) == -1)
		return ;
	execve(pipex->path_cmd_one, pipex->cmd_one, envp);	
}

void	ft_pipex(t_data *pipex, char **envp)
{
	int		pipefd[2];
	pid_t 	pid;

	if (pipe(pipefd) == -1)
		ft_exit_failure("Pipe function issue in ft_pipex.c", pipex);
	pid = fork();
	if (pid == -1)
		ft_exit_failure("Fork function issue in ft_pipex.c", pipex);
	if (pid == 0)
	{
		ft_exe_fst_cmd(pipex, envp, pipefd);
		close(pipefd[1]);
		ft_exit_failure("First command execution issue in ft_pipex.c", pipex);
	}
	else
	{
		waitpid(0, NULL, 0);
		ft_exe_snd_cmd(pipex, envp, pipefd);
		close(pipefd[0]);
		ft_exit_failure("Second command execution issue in ft_pipex.c", pipex);
	}
}