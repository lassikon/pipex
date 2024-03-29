/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:50:27 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/08 12:09:40 by lkonttin         ###   ########.fr       */
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

void	commands(t_pipex *p)
{
	p->cmd1 = p_split(p->argv[2]);
	if (p->cmd1 == NULL)
		handle_perror(p, ERROR_MALLOC, 1, 1);
	if (p->cmd1[0] == NULL)
		handle_perror(p, ERROR_CMD, 1, 1);
	p->cmd2 = p_split(p->argv[3]);
	if (p->cmd2 == NULL)
		handle_perror(p, ERROR_MALLOC, 1, 1);
	if (p->cmd2[0] == NULL)
		handle_perror(p, ERROR_CMD, 1, 1);
}

void	remove_backslash(char **cmd)
{
	int		i;
	int		j;
	int		k;

	k = 0;
	while (cmd[k])
	{
		i = 0;
		j = 0;
		while (cmd[k][i])
		{
			if (cmd[k][i] == '\\')
				i++;
			cmd[k][j] = cmd[k][i];
			i++;
			j++;
		}
		while (cmd[k][j])
		{
			cmd[k][j] = '\0';
			j++;
		}
		k++;
	}
}
