/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 12:51:37 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/25 12:58:27 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	debug(t_pipex *p)
{
	int	i;

	i = 0;
	printf("PATHS\n");
	while (p->paths[i])
	{
		printf("paths[%d]: %s\n", i, p->paths[i]);
		i++;
	}
	printf("\nCOMMANDS\n");
	i = 0;
	while (p->cmd1[i])
	{
		printf("cmd1[%d]: %s\n", i, p->cmd1[i]);
		i++;
	}
	i = 0;
	while (p->cmd2[i])
	{
		printf("cmd2[%d]: %s\n", i, p->cmd2[i]);
		i++;
	}
}