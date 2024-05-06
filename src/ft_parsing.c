/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:37:03 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/07 01:14:06 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_sc(char	**str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

// valgrind on if in while loop
// return 0 = malloc error
// if fail during the process the new_array / 
	//beginning of the new array is free

// have to test the malloc issue in the loop
static char	**ft_modify_full_array(char **array, char *str)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = malloc(sizeof(char *) * (ft_sc(array) + 1));
	if (new_array == NULL)
		return (0);
	while (array[i])
	{
		new_array[i] = ft_strjoin(array[i], str);
		if (new_array[i] == NULL)
		{
			ft_free_str_array(new_array);
			return (0);
		}
		i++;
	}
	new_array[i] = array[i];
	return (new_array);
}

static char **ft_get_env_paths(t_data *pipex, char **envp)
{
	char	**env_paths;
	char	**save_env_paths;

	while (envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			break ;
		envp++;
	}
	if (envp == NULL)
		ft_exit_failure("Command file not found", pipex);
	env_paths = ft_split(*envp + 5, ':');
	if (env_paths == NULL)
		ft_exit_failure("Malloc issue during path searching", pipex);	
	save_env_paths = env_paths;
	env_paths = ft_modify_full_array(env_paths, "/");
	ft_free_str_array(save_env_paths);
	if (env_paths == NULL)
		ft_exit_failure("Malloc issue during path searching", pipex);
	return (env_paths);
}

static char	**ft_get_path_list(t_data *pipex, char *full_cmd, char **envp)
{
	char	*cmd;
	char	**save_path_list;
	char	**path_list;

	path_list = ft_get_env_paths(pipex, envp);
	cmd = ft_strcut(full_cmd, ' ');
	if (cmd == NULL)
	{
		ft_free_str_array(path_list);
		ft_exit_failure("Malloc issue during path creation", pipex);
	}
	save_path_list = path_list;
	path_list = ft_modify_full_array(path_list, cmd);	
	if (cmd != full_cmd)
		free(cmd);
	ft_free_str_array(save_path_list);
	if (path_list == NULL)
		ft_exit_failure ("Malloc issue during path creation", pipex);
	return (path_list);
}

// continue to add t_data
	// begin testing the cmd without
char	*ft_check_path(t_data *pipex, char *full_cmd, char **envp, int *acs)
{
	char	**paths;
	char	**save_paths;
	char	*store;

	if (access(full_cmd, R_OK) == 0)
	{
		*acs += 1;
		return (full_cmd);
	}
	paths = ft_get_path_list(pipex, full_cmd, envp);
	save_paths = paths;
	while (*paths)
	{
		if (access(*paths, R_OK) == 0)
		{
			store = ft_strdup(*paths);
			ft_free_str_array(save_paths);
			if (store == NULL)
				ft_exit_failure("strdup malloc issue", pipex);
			return (store);
		}
		paths++;
	}
	ft_free_str_array(save_paths);
	ft_exit_failure("Not existing path for a command", pipex);
	return (NULL);
}

static void	ft_wrong_infile(t_data *pipex, char *infile)
{
	if (access(infile, F_OK) == -1)
		ft_exit_failure("The infile doesn't exist", pipex);
	if (access(infile, R_OK) == -1)
		ft_exit_failure("The infile is not readable", pipex);
}

static void	ft_wrong_arg_number(t_data *pipex, int ac)
{
	if (ac < 4)
		ft_exit_failure("Too few arguments", pipex);
	if (ac > 4)
		ft_exit_failure("Too many arguments", pipex);
}

void	ft_parsing(t_data *pipex, int ac, char **av, char **envp)
{
	ft_wrong_arg_number(pipex, ac);
	ft_wrong_infile(pipex, *av);
	pipex->path_cmd_one = ft_check_path(pipex, av[1], envp, &(pipex->acs1));
	pipex->path_cmd_two = ft_check_path(pipex, av[2], envp, &(pipex->acs2));
}
