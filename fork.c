/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:49:00 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/30 15:38:37 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_one(t_pipex *p, char **argv, char **envp)
{
	int		i;
	char	*cmd_path;
	char	*cmd_one;

	p->infile = open(argv[1], O_RDONLY);
	if (p->infile < 0)
		handle_perror(p, ERROR_INFILE, 1, 1);
	i = 0;
	dup2(p->infile, STDIN_FILENO);
	dup2(p->pipe[1], STDOUT_FILENO);
	close_pipes(p, 2);
	cmd_one = ft_strjoin("//", p->cmd1[0]);
	if (cmd_one == NULL)
		handle_perror(p, ERROR_MALLOC, 1, 1);
	while (p->paths[i])
	{
		cmd_path = ft_strjoin(p->paths[i], cmd_one);
		execve(cmd_path, p->cmd1, envp);
		free(cmd_path);
		i++;
	}
	execve(p->cmd1[0], p->cmd1, envp);
	free(cmd_one);
	handle_perror(p, ERROR_CMD, 127, 1);
}

static void	child_two(t_pipex *p, char **argv, char **envp)
{
	int		i;
	char	*cmd_path;
	char	*cmd_two;

	p->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->outfile < 0)
		handle_perror(p, ERROR_OUTFILE, 1, 1);
	i = 0;
	dup2(p->pipe[0], STDIN_FILENO);
	dup2(p->outfile, STDOUT_FILENO);
	close_pipes(p, 2);
	cmd_two = ft_strjoin("//", p->cmd2[0]);
	if (cmd_two == NULL)
		handle_perror(p, ERROR_MALLOC, 1, 1);
	while (p->paths[i])
	{
		cmd_path = ft_strjoin(p->paths[i], cmd_two);
		execve(cmd_path, p->cmd2, envp);
		free(cmd_path);
		i++;
	}
	execve(p->cmd2[0], p->cmd2, envp);
	free(cmd_two);
	handle_perror(p, ERROR_CMD, 127, 1);
}

void	do_fork(t_pipex *p, char **argv, char **envp)
{
	p->pid_one = fork();
	if (p->pid_one == -1)
		handle_perror(p, ERROR_FORK, 1, 1);
	if (p->pid_one == 0)
		child_one(p, argv, envp);
	p->pid_two = fork();
	if (p->pid_two == -1)
	{
		waitpid(p->pid_one, &p->status, 0);
		handle_perror(p, ERROR_FORK, 1, 1);
	}
	if (p->pid_two == 0)
		child_two(p, argv, envp);
}

/* int execve(const char *path, char *const argv[], char *envp[]);
# path: the path to our command
        type `which ls` and `which wc` in your terminal
        you'll see the exact path to the commands' binaries
# argv[]: the args the command needs, for ex. `ls -la`
          you can use your ft_split to obtain a char **
          like this { "ls", "-la", NULL }
          it must be null terminated
# envp: the environmental variable
        you can simply retrieve it in your main (see below)
        and pass it onto execve, no need to do anything here
        in envp you'll see a line PATH which contains all possible
        paths to the commands' binaries */