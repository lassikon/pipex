/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:07:23 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/06 11:33:00 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_array(char **str_array, int index)
{
	while (index > 0)
	{
		free(str_array[index -1]);
		index--;
	}
	free(str_array);
}

static int	substr_len(char *s, char c, char q)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != q && s[i] != '\0')
		i++;
	return (i);
}

int	array_creator(t_quotes *q, char *s, char **str_array)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0' && k < q->substr_count)
	{
		while (s[i] == ' ')
			i++;
		if (q->quotes_exist && i == q->start)
		{
			str_array[k] = ft_substr(s, i + 1, q->quote_len);
			if (!str_array[k])
			{
				free_array(str_array, k);
				return (0);
			}
			i = q->end + 1;
		}
		else if (s[i] != ' ' && s[i] != '\0')
		{
			str_array[k] = ft_substr(s, i, substr_len(&s[i], ' ', q->quote));
			if (!str_array[k])
			{
				free_array(str_array, k);
				return (0);
			}
			i = i + substr_len(&s[i], ' ', q->quote);
		}
		k++;
	}
	str_array[k] = NULL;
	return (1);
}
// if '\' is found, remove it from the string