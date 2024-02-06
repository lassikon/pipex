/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:29:29 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/06 14:42:50 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_quotes(t_quotes *q)
{
	q->quote = 0;
	q->quotes_exist = 0;
	q->start = -1;
	q->end = -1;
	q->substr_count = 0;
	q->quote_len = 0;
	q->index = 0;
}

static void	find_quote_indexes(t_quotes *q, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == q->quote && s[i - 1] != '\\')
		{
			if (q->start == -1)
				q->start = i;
			else
			{
				q->end = i;
				q->quotes_exist = 1;
			}
		}
		i++;
	}
	q->quote_len = q->end - q->start - 1;
}

static void	find_quotes(t_quotes *q, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && s[i - 1] != '\\')
		{
			q->quote = '\'';
			return ;
		}
		else if (s[i] == '\"' && s[i - 1] != '\\')
		{
			q->quote = '\"';
			return ;
		}
		i++;
	}
}

static void	substr_count_with_quotes(t_quotes *q, char *s)
{
	int	i;
	int	in_substr;

	i = 0;
	in_substr = 0;
	while (s[i] != '\0')
	{
		if (q->quotes_exist)
		{
			if (i == q->start)
			{
				in_substr = 0;
				i = q->end;
				q->substr_count++;
			}
		}
		if (s[i] == ' ')
			in_substr = 0;
		else if (in_substr == 0)
		{
			in_substr = 1;
			q->substr_count++;
		}
		i++;
	}
}

char	**p_split(char *s)
{
	char		**str_array;
	t_quotes	q;

	str_array = NULL;
	init_quotes(&q);
	find_quotes(&q, s);
	if (q.quote)
		find_quote_indexes(&q, s);
	substr_count_with_quotes(&q, s);
	if (s == NULL)
		return (NULL);
	str_array = (char **)malloc(sizeof(char *) * (q.substr_count + 1));
	if (!str_array)
		return (NULL);
	if (!array_creator(&q, s, str_array))
		return (NULL);
	return (str_array);
}
