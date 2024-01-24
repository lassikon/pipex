/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:41:39 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/24 15:39:21 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	free_and_exit(t_pip *pip, int error)
{
	if (pip->paths)
	{
		while (*pip->paths)
		{
			free(*pip->paths);
			pip->paths++;
		}
		// free(pip->paths);
	}
	if (pip->cmd1)
	{
		while (*pip->cmd1)
		{
			free(*pip->cmd1);
			pip->cmd1++;
		}
		// free(pip->cmd1);
	}
	if (pip->cmd2)
	{
		while (*pip->cmd2)
		{
			free(*pip->cmd2);
			pip->cmd2++;
		}
		// free(pip->cmd2);
	}
	if (error)
	{
		write(2, "Error\n", 7);
		exit(1);
	}
	exit(0);
}

void	paths(t_pip *pip, char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH", 4))
		{
			paths = ft_split(*envp + 5, ':');
			while (paths[i])
			{
				paths[i] = ft_strjoin(paths[i], "/");
				i++;
			}
			pip->paths = paths;
			// free(paths);
			return ;
		}
		envp++;
	}
	exit(1);
}

void	commands(t_pip *pip, char **argv)
{
	pip->cmd1 = ft_split(argv[2], ' ');
	pip->cmd2 = ft_split(argv[3], ' ');
}

void	child_one(t_pip pip, char **envp)
{
	int		i;

	i = 0;
	if (dup2(pip.infile, STDIN_FILENO) < 0)
		exit(1);
	if (dup2(pip.fd[1], STDOUT_FILENO) < 0)
		exit(1);
	close(pip.fd[0]);
	// close(pip.fd[1]);
	while (pip.paths[i])
	{
		execve(pip.paths[i], pip.cmd1, envp);
		i++;
	}
	exit(1);
}

void	child_two(t_pip pip, char **envp)
{
	int	i;

	i = 0;
	if (dup2(pip.fd[0], STDIN_FILENO) < 0)
		exit(1);
	if (dup2(STDOUT_FILENO, pip.outfile) < 0)
		exit(1);
	close(pip.fd[1]);
	// close(pip.fd[0]);
	while (pip.paths[i])
	{
		execve(pip.paths[i], pip.cmd2, envp);
		i++;
	}
	exit(1);
}

void	debug(t_pip *pip)
{
	int	i;

	i = 0;
	printf("PATHS\n");
	while (pip->paths[i])
	{
		printf("paths[%d]: %s\n", i, pip->paths[i]);
		i++;
	}
	printf("\nCOMMANDS\n");
	i = 0;
	while (pip->cmd1[i])
	{
		printf("cmd1[%d]: %s\n", i, pip->cmd1[i]);
		i++;
	}
	i = 0;
	while (pip->cmd2[i])
	{
		printf("cmd2[%d]: %s\n", i, pip->cmd2[i]);
		i++;
	}
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
	commands(&pip, argv);
	debug(&pip);
	pip.pid_one = fork();
	if (pip.pid_one == -1)
		return (1);
	if (pip.pid_one == 0)
		child_one(pip, envp);
	pip.pid_two = fork();
	if (pip.pid_two == -1)
		return (1);
	if (pip.pid_two == 0)
		child_two(pip, envp);
	close(pip.fd[0]);
	close(pip.fd[1]);
	waitpid(pip.pid_one, &pip.status, 0);
	waitpid(pip.pid_two, &pip.status, 0);
	free_and_exit(&pip, 0);
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