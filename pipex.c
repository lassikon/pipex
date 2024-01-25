/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:41:39 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/25 12:58:13 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	free_and_exit(t_pipex *p, int error)
{
	if (p->paths)
	{
		while (*p->paths)
		{
			free(*p->paths);
			p->paths++;
		}
		// free(p->paths);
	}
	if (p->cmd1)
	{
		while (*p->cmd1)
		{
			free(*p->cmd1);
			p->cmd1++;
		}
		// free(p->cmd1);
	}
	if (p->cmd2)
	{
		while (*p->cmd2)
		{
			free(*p->cmd2);
			p->cmd2++;
		}
		// free(p->cmd2);
	}
	if (error)
	{
		write(2, "Error\n", 7);
		exit(1);
	}
	exit(0);
}

void	child_one(t_pipex p, char **envp)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (dup2(p.infile, STDIN_FILENO) < 0)
		exit(1);
	if (dup2(p.pipe[1], STDOUT_FILENO) < 0)
		exit(1);
	close(p.pipe[0]);
	close(p.pipe[1]);
	while (p.paths[i])
	{
		cmd_path = ft_strjoin(p.paths[i], p.cmd1[0]);
		execve(cmd_path, p.cmd1, envp);
		free(cmd_path);
		i++;
	}
	exit(1);
}

void	child_two(t_pipex p, char **envp)
{
	int		i;
	char	*cmd_path;

	i = 0;
	if (dup2(p.pipe[0], STDIN_FILENO) < 0)
		exit(1);
	if (dup2(p.outfile, STDOUT_FILENO) < 0)
		exit(1);
	close(p.pipe[1]);
	close(p.pipe[0]);
	while (p.paths[i])
	{
		cmd_path = ft_strjoin(p.paths[i], p.cmd2[0]);
		execve(cmd_path, p.cmd2, envp);
		free(cmd_path);
		i++;
	}
	exit(1);
}


int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc != 5)
		return (1);
	p.infile = open(argv[1], O_RDONLY);
	p.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	pipe(p.pipe);
	paths(&p, envp);
	commands(&p, argv);
	p.pid_one = fork();
	if (p.pid_one == -1)
		return (1);
	if (p.pid_one == 0)
		child_one(p, envp);
	p.pid_two = fork();
	if (p.pid_two == -1)
		return (1);
	if (p.pid_two == 0)
		child_two(p, envp);
	close(p.pipe[0]);
	close(p.pipe[1]);
	waitpid(p.pid_one, &p.status, 0);
	waitpid(p.pid_two, &p.status, 0);
	free_and_exit(&p, 0);
	return (0);
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