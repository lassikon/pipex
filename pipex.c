/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonttin <lkonttin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:41:39 by lkonttin          #+#    #+#             */
/*   Updated: 2024/01/26 15:36:29 by lkonttin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *p, int end)
{
	if (end < 2)
	{
		if (close(p->pipe[end]) < 0)
			handle_perror(ERROR_PIPE, 1);
	}
	if (close(p->pipe[0]) < 0 || close(p->pipe[1]) < 0)
		handle_perror(ERROR_PIPE, 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc != 5)
		return (1);
	p.infile = open(argv[1], O_RDONLY);
	/* if (p.infile < 0)
		handle_perror(ERROR_INFILE); */
	p.outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p.outfile < 0)
		handle_perror(ERROR_OUTFILE, 1);
	if (pipe(p.pipe) < 0)
		handle_perror(ERROR_PIPE, 1);
	paths(&p, envp);
	commands(&p, argv);
	do_fork(&p, envp);
	close_pipes(&p, 2);
	waitpid(p.pid_one, &p.status, 0);
	waitpid(p.pid_two, &p.status, 0);
	free_strs(&p);
	return (WEXITSTATUS(p.status));
}
