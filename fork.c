/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:49:00 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/26 15:36:14 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_one(t_pipex *p, char **envp)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (dup2(p->infile, STDIN_FILENO) < 0)
		handle_perror(ERROR_DUP, 1);
	if (dup2(p->pipe[1], STDOUT_FILENO) < 0)
		handle_perror(ERROR_DUP, 1);
	close_pipes(p, 2);
	while (p->paths[i])
	{
		cmd_path = ft_strjoin(p->paths[i], p->cmd1[0]);
		free(p->paths[i]);
		execve(cmd_path, p->cmd1, envp);
		free(cmd_path);
		i++;
	}
	execve(p->cmd1[0], p->cmd1, envp);
	free(p->paths);
	handle_perror(ERROR_CMD, 127);
}

static void	child_two(t_pipex *p, char **envp)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (dup2(p->pipe[0], STDIN_FILENO) < 0)
		handle_perror(ERROR_DUP, 1);
	if (dup2(p->outfile, STDOUT_FILENO) < 0)
		handle_perror(ERROR_DUP, 1);
	close_pipes(p, 2);
	while (p->paths[i])
	{
		cmd_path = ft_strjoin(p->paths[i], p->cmd2[0]);
		free(p->paths[i]);
		execve(cmd_path, p->cmd2, envp);
		free(cmd_path);
		i++;
	}
	execve(p->cmd2[0], p->cmd2, envp);
	free(p->paths);
	handle_perror(ERROR_CMD, 127);
}

void	do_fork(t_pipex *p, char **envp)
{
	p->pid_one = fork();
	if (p->pid_one == -1)
		handle_perror(ERROR_FORK, 1);
	if (p->pid_one == 0)
		child_one(p, envp);
	else
	{
		p->pid_two = fork();
		if (p->pid_two == -1)
		{
			waitpid(p->pid_one, &p->status, 0);
			handle_perror(ERROR_FORK, 1);
		}
		if (p->pid_two == 0)
			child_two(p, envp);
	}
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