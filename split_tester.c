/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:13:46 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/31 21:59:50 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_split(char** split)
{
    char** temp = split;
    while (*temp != NULL) {
        free(*temp);
        temp++;
    }
    free(split);
}

int main() {
	char* str = "Hello 'world of programming'";
	char** split = p_split(str);

	if (split != NULL)
	{
		int i = 0;
		while (split[i] != NULL)
		{
			printf("%s\n", split[i]);
			i++;
		}
		free_split(split);
	}
	return 0;
}
