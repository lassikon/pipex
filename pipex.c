/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:41:39 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/30 12:51:58 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *p, int end)
{
	if (end < 2)
	{
		if (close(p->pipe[end]) < 0)
			handle_perror(p, ERROR_PIPE, 1, 1);
	}
	if (close(p->pipe[0]) < 0 || close(p->pipe[1]) < 0)
		handle_perror(p, ERROR_PIPE, 1, 1);
}

void	init_struct(t_pipex *p, char **argv, char **envp)
{
	p->infile = 0;
	p->outfile = 0;
	p->paths = NULL;
	p->cmd1 = NULL;
	p->cmd2 = NULL;
	p->pid_one = 0;
	p->pid_two = 0;
	p->status = 0;
	p->argv = argv;
	p->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc != 5)
		return (1);
	init_struct(&p, argv, envp);
	if (pipe(p.pipe) < 0)
		handle_perror(&p, ERROR_PIPE, 1, 1);
	paths(&p, envp);
	commands(&p, argv);
	do_fork(&p, argv, envp);
	close_pipes(&p, 2);
	waitpid(p.pid_one, &p.status, 0);
	waitpid(p.pid_two, &p.status, 0);
	close(p.infile);
	close(p.outfile);
	free_strs(&p);
	return (WEXITSTATUS(p.status));
}
