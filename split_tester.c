/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:13:46 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/01 11:35:26 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	char	**temp;

	temp = split;
	while (*temp != NULL)
	{
		free(*temp);
		temp++;
	}
	free(split);
}

int	main(int argc, char **argv)
{
	char	**split;
	int		i;

	split = p_split(argv[1]);
	if (split != NULL)
	{
		i = 0;
		while (split[i] != NULL)
		{
			printf("%s\n", split[i]);
			i++;
		}
		free_split(split);
	}
	return (0);
}
