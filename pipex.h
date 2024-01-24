/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:41:35 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/24 11:13:19 by lkonttin         ###   ########.fr       */
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
	char	**cmd1;
	char	**cmd2;
}	t_pip;

#endif