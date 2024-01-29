/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:50:27 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/29 16:48:56 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	paths(t_pipex *p, char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH", 4))
		{
			paths = ft_split(*envp + 5, ':');
			while (paths[i])
			{
				paths[i] = ft_strjoin(paths[i], "/");
				i++;
			}
			p->paths = paths;
			return ;
		}
		envp++;
	}
	handle_perror(p, ERROR_PATH, 1, 1);
}

void	commands(t_pipex *p, char **argv)
{
	p->cmd1 = ft_split(argv[2], ' ');
	if (p->cmd1 == NULL)
		handle_perror(p, ERROR_MALLOC, 1, 1);
	if (p->cmd1[0] == NULL)
		handle_perror(p, ERROR_CMD, 1, 1);
	p->cmd2 = ft_split(argv[3], ' ');
	if (p->cmd2 == NULL)
		handle_perror(p, ERROR_MALLOC, 1, 1);
	if (p->cmd2[0] == NULL)
		handle_perror(p, ERROR_CMD, 1, 1);
}
