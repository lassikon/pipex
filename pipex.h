/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:41:35 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/08 12:07:52 by lkonttin         ###   ########.fr       */
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

# define ERROR_INFILE "Infile"
# define ERROR_OUTFILE "Outfile"
# define ERROR_INPUT "Invalid number of arguments.\n"
# define ERROR_PIPE "Pipe"
# define ERROR_CMD "Command not found.\n"
# define ERROR_FORK "Fork"
# define ERROR_CLOSE "Close"
# define ERROR_PATH "Path"
# define ERROR_MALLOC "Malloc"
# define ERROR_EXECVE "Execve() Failed"

typedef struct s_pipex
{
	int		pipe[2];
	int		infile;
	int		outfile;
	int		pid_one;
	int		pid_two;
	int		status;
	char	**paths;
	char	**cmd1;
	char	**cmd2;
	char	**argv;
}	t_pipex;

typedef struct s_quotes
{
	char	quote;
	int		quotes_exist;
	int		start;
	int		end;
	int		substr_count;
	int		quote_len;
	int		index;
}	t_quotes;

void	paths(t_pipex *p, char **envp);
void	commands(t_pipex *p);
void	handle_perror(t_pipex *p, char *error, int errcode, int do_exit);
void	error_message(char *error);
void	do_fork(t_pipex *p, char **argv, char **envp);
void	close_pipes(t_pipex *p, int end);
void	free_strs(t_pipex *p);
char	**p_split(char *s);
void	init_struct(t_pipex *p, char **argv);
int		array_creator(t_quotes *q, char *s, char **str_array);
void	remove_backslash(char **cmd);

#endif