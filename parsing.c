/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:50:27 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/01 11:38:01 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	paths(t_pipex *p, char **envp)
{
	char	**paths;

	if (envp != NULL)
	{
		while (*envp)
		{
			if (!ft_strncmp(*envp, "PATH", 4))
			{
				paths = ft_split(*envp + 5, ':');
				if (paths == NULL)
					handle_perror(p, ERROR_MALLOC, 1, 1);
				p->paths = paths;
				return ;
			}
			envp++;
		}
	}
}

void	commands(t_pipex *p, char **argv)
{
	p->cmd1 = p_split(argv[2]);
	if (p->cmd1 == NULL)
		handle_perror(p, ERROR_MALLOC, 1, 1);
	if (p->cmd1[0] == NULL)
		handle_perror(p, ERROR_CMD, 1, 1);
	p->cmd2 = p_split(argv[3]);
	if (p->cmd2 == NULL)
		handle_perror(p, ERROR_MALLOC, 1, 1);
	if (p->cmd2[0] == NULL)
		handle_perror(p, ERROR_CMD, 1, 1);
}
