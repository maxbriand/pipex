/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:23:24 by mbriand           #+#    #+#             */
/*   Updated: 2024/05/07 18:19:50 by mbriand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_data
{
	char	**cmd_one;
	char	**cmd_two;
	char	*path_cmd_one;
	char	*path_cmd_two;
	char	*infile;
	char	*outfile;
	int		acs1;
	int		acs2;
	int		fd_outfile;
	char	*av1;
	char	*av2;
}	t_data;

// Handle error
void	ft_exit_failure(char *msg, t_data *pipex);
void	ft_exit_success(t_data *pipex);

// Parsing
void	ft_parsing(t_data *pipex, int ac, char **av);
char	*ft_check_path(t_data *pipex, char *full_cmd, char **envp, int *acs);
int		ft_sc(char	**str);

// Exe cmd
void	ft_pipex(t_data *pipex, char **envp);

#endif
