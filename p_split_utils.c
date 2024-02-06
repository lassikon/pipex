/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:07:23 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/06 17:52:06 by lkonttin         ###   ########.fr       */
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

static int	substr_quotes(t_quotes *q, char **array, char *src, int k)
{
	array[k] = ft_substr(src, q->start + 1, q->quote_len);
	if (!array[k])
	{
		free_array(array, k);
		return (0);
	}
	q->index = q->end + 1;
	return (1);
}

static int	substr_spaces(t_quotes *q, char **array, char *src, int k)
{
	int	len;

	len = substr_len(&src[q->index], ' ', q->quote);
	array[k] = ft_substr(src, q->index, len);
	if (!array[k])
	{
		free_array(array, k);
		return (0);
	}
	q->index += len;
	return (1);
}

int	array_creator(t_quotes *q, char *s, char **str_array)
{
	int	k;

	k = 0;
	while (s[q->index] != '\0' && k < q->substr_count)
	{
		while (s[q->index] == ' ')
			q->index++;
		if (q->quotes_exist && q->index == q->start)
		{
			if (!substr_quotes(q, str_array, s, k))
				return (0);
		}
		else if (s[q->index] != ' ' && s[q->index] != '\0')
		{
			if (!substr_spaces(q, str_array, s, k))
				return (0);
		}
		k++;
	}
	str_array[k] = NULL;
	return (1);
}
