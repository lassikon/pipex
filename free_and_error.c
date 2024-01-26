/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:45:47 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/26 15:33:26 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_strs(t_pipex *p)
{
	if (p->paths)
	{
		while (*p->paths)
		{
			free(*p->paths);
			p->paths++;
		}
	}
	if (p->cmd1)
	{
		while (*p->cmd1)
		{
			free(*p->cmd1);
			p->cmd1++;
		}
	}
	if (p->cmd2)
	{
		while (*p->cmd2)
		{
			free(*p->cmd2);
			p->cmd2++;
		}
	}
}

void	handle_perror(char *error, int errcode)
{
	perror(error);
	exit(errcode);
}
