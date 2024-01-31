/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:29:29 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/31 22:06:19 by lkonttin         ###   ########.fr       */
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

static void	init_quotes(t_quotes *q)
{
	q->quote = 0;
	q->quotes_exist = 0;
	q->first = -1;
	q->last = -1;
	q->substr_count = 0;
	q->quote_len = 0;
}

static void	find_quote_indexes(t_quotes *q, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == q->quote && s[i - 1] != '\\')
		{
			if (q->first == -1)
				q->first = i;
			else
			{
				q->last = i;
				q->quotes_exist = 1;
			}
		}
		i++;
	}
	q->quote_len = q->last - q->first - 1;
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
		if (i == q->first)
		{
			while (i <= q->last)
				i++;
			q->substr_count++;
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

static void	substr_count_with_spaces(t_quotes *q, char *s)
{
	int	i;
	int	in_substr;

	i = 0;
	while (s[i] != '\0')
	{
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

static int	substr_len(char *s, char c, char q)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != q && s[i] != '\0')
		i++;
	return (i);
}

static int	array_creator(t_quotes *q, char *s, char **str_array)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0' && k < q->substr_count)
	{
		while (s[i] == ' ')
			i++;
		if (i == q->first)
		{
			str_array[k] = ft_substr(s, i + 1, q->quote_len);
			if (!str_array[k])
			{
				free_array(str_array, k);
				return (0);
			}
			i = q->last + 1;
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

char	**p_split(char *s)
{
	char		**str_array;
	t_quotes	q;

	str_array = NULL;
	init_quotes(&q);
	find_quotes(&q, s);
	find_quote_indexes(&q, s);
	if (q.quote == 0)
		substr_count_with_spaces(&q, s);
	else
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
