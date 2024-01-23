/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:41:35 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/23 14:54:55 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft/include/libft.h"

typedef struct s_pip
{
	int		fd[2];
	int		infile;
	int		outfile;
	int		pid_one;
	int		pid_two;
	int		status;
	char	**paths;
}	t_pip;

#endif