/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:41:39 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/23 14:58:14 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	paths(t_pip *pip, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			pip->paths = ft_split(envp[i] + 5, ':');
			return ;
		}
		i++;
	}
	exit(1);
}

void	child_one(t_pip *pip, char *argv, char **envp)
{
	int		i;

	i = 0;
	if (dup2(pip->infile, STDIN_FILENO) < 0)
		exit(1);
	if (dup2(pip->fd[1], STDOUT_FILENO) < 0)
		exit(1);
	close(pip->fd[0]);
	while (pip->paths[i])
	{
		execve(pip->paths[i], &argv, envp);
		i++;
	}
	exit(1);
}

void	child_two(t_pip *pip, char *argv, char **envp)
{
	int	i;

	i = 0;
	if (dup2(pip->fd[0], STDIN_FILENO) < 0)
		exit(1);
	if (dup2(STDOUT_FILENO, pip->outfile) < 0)
		exit(1);
	close(pip->fd[1]);
	while (pip->paths[i])
	{
		execve(pip->paths[i], &argv, envp);
		i++;
	}
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pip	pip;

	if (argc != 5)
		return (1);
	pip.infile = open(argv[1], O_RDONLY);
	pip.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	pipe(pip.fd);
	paths(&pip, envp);
	pip.pid_one = fork();
	if (pip.pid_one == -1)
		return (1);
	if (pip.pid_one == 0)
		child_one(&pip, argv[2], envp);
	pip.pid_two = fork();
	if (pip.pid_two == -1)
		return (1);
	if (pip.pid_two == 0)
		child_two(&pip, argv[3], envp);
	close(pip.fd[0]);
	close(pip.fd[1]);
	waitpid(pip.pid_one, &pip.status, 0);
	waitpid(pip.pid_two, &pip.status, 0);
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