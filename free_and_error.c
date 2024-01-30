/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:45:47 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/30 14:47:59 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_paths(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->paths[i])
	{
		free(p->paths[i]);
		i++;
	}
	free(p->paths);
}

void	free_strs(t_pipex *p)
{
	int	i;

	i = 0;
	if (p->paths)
		free_paths(p);
	if (p->cmd1)
	{
		while (p->cmd1[i])
		{
			free(p->cmd1[i]);
			i++;
		}
		free(p->cmd1);
	}
	i = 0;
	if (p->cmd2)
	{
		while (p->cmd2[i])
		{
			free(p->cmd2[i]);
			i++;
		}
		free(p->cmd2);
	}
}

void	handle_perror(t_pipex *p, char *error, int errcode, int do_exit)
{
	perror(error);
	if (do_exit)
	{
		free_strs(p);
		close(p->infile);
		close(p->outfile);
		exit(errcode);
	}
}
