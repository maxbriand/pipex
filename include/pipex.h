/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:23:24 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/04 17:40:41 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_data
{
	char	**cmd_one;
	char	**cmd_two;
	char 	*path_cmd_one;
	char	*path_cmd_two;
	char	*infile;
	char	*outfile;
}	t_data;

// Handle error
void	ft_exit_failure(char *msg, t_data *pipex);
void	ft_exit_success(t_data *pipex);

// Parsing
void	ft_parsing(t_data *pipex, int ac, char **av, char **envp);

// Exe cmd
void	ft_pipex(t_data *pipex, char **envp);

#endif
