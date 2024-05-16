/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:03:53 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/07 23:23:00 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// return 0 = malloc error
// if fail during the process the new_array / 
	//beginning of the new array is free
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

static char	**ft_get_env_paths(t_data *pipex, char **envp)
{
	char	**env_paths;
	char	**save_env_paths;

	while (envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			break ;
		envp++;
	}
	if (*envp == NULL)
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
	char	**save_path_list;
	char	**path_list;

	pipex->cutcmd = ft_strcut(full_cmd, ' ');
	if (pipex->cutcmd == NULL)
		ft_exit_failure("Malloc issue during path creation", pipex);
	if (pipex->cutcmd != full_cmd)
		pipex->chk_cutcmd = 1;
	path_list = ft_get_env_paths(pipex, envp);
	save_path_list = path_list;
	path_list = ft_modify_full_array(path_list, pipex->cutcmd);
	ft_free_str_array(save_path_list);
	if (path_list == NULL)
		ft_exit_failure ("Malloc issue during path creation", pipex);
	return (path_list);
}

static char	*ft_is_already_path(char *full_cmd, int *acs)
{
	char	*al_path;

	al_path = ft_strcut(full_cmd, ' ');
	if (access(al_path, R_OK) == 0)
	{
		if (al_path == full_cmd)
			*acs += 1;
		return (al_path);
	}
	if (al_path != full_cmd)
		free(al_path);
	return (NULL);
}

char	*ft_check_path(t_data *pipex, char *full_cmd, char **envp, int *acs)
{
	char	**paths;
	char	**save_paths;
	char	*store;
	char	*al_path;

	al_path = ft_is_already_path(full_cmd, acs);
	if (al_path != NULL)
		return (al_path);
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
