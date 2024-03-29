/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:49:00 by lkonttin          #+#    #+#             */
/*   Updated: 2024/02/10 11:31:57 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execve_with_path(t_pipex *p, char **cmd, char **envp)
{
	int		i;
	char	*cmd_path;
	char	*cmd_one;

	i = 0;
	cmd_one = ft_strjoin("/", cmd[0]);
	if (cmd_one == NULL)
		handle_perror(p, ERROR_MALLOC, 1, 1);
	while (p->paths[i])
	{
		cmd_path = ft_strjoin(p->paths[i], cmd_one);
		execve(cmd_path, cmd, envp);
		free(cmd_path);
		i++;
	}
	free(cmd_one);
}

static void	child_one(t_pipex *p, char **argv, char **envp)
{
	p->infile = open(argv[1], O_RDONLY);
	if (p->infile < 0)
		handle_perror(p, ERROR_INFILE, 0, 1);
	dup2(p->infile, STDIN_FILENO);
	dup2(p->pipe[1], STDOUT_FILENO);
	close_pipes(p, 2);
	close(p->infile);
	remove_backslash(p->cmd1);
	if (ft_strchr(p->cmd1[0], '/') || p->cmd1[0][0] == '.')
	{
		if (access(p->cmd1[0], X_OK) == -1)
			handle_perror(p, ERROR_CMD, 126, 1);
		execve(p->cmd1[0], p->cmd1, envp);
	}
	else if (p->paths != NULL)
		execve_with_path(p, p->cmd1, envp);
	handle_perror(p, ERROR_CMD, 127, 1);
}

static void	child_two(t_pipex *p, char **argv, char **envp)
{
	p->outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->outfile < 0)
		handle_perror(p, ERROR_OUTFILE, 1, 1);
	dup2(p->pipe[0], STDIN_FILENO);
	dup2(p->outfile, STDOUT_FILENO);
	close_pipes(p, 2);
	close(p->outfile);
	remove_backslash(p->cmd2);
	if (ft_strchr(p->cmd2[0], '/') || p->cmd2[0][0] == '.')
	{
		if (access(p->cmd2[0], X_OK) == -1)
			handle_perror(p, ERROR_CMD, 126, 1);
		execve(p->cmd2[0], p->cmd2, envp);
	}
	else if (p->paths != NULL)
		execve_with_path(p, p->cmd2, envp);
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
