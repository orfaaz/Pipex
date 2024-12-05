/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:04:00 by agamay            #+#    #+#             */
/*   Updated: 2024/12/02 15:33:32 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

//close multiple fds
void	closer(int count, ...)
{
	va_list	arg;

	va_start(arg, count);
	while (count--)
		close(va_arg(arg, int));
	va_end(arg);
}

//executes shell cmd in child process and return result through pipe
static void	ft_exec(t_piplist *cmdlst, int pfd[2], int ffd[2])
{
	if (cmdlst->next)
		dup2(pfd[1], 1);
	else
		dup2(ffd[1], 1);
	closer(3, pfd[0], pfd[1], ffd[1]);
	execve(cmdlst->path, cmdlst->cmd, NULL);
	perror("execve failed");
	pip_lstclear(&cmdlst, &dbarr_free);
	exit(2);
}

//creates forks until there are no more cmds to execute
static void	apply_cmds(int ffd[2], t_piplist *cmdlst)
{
	int		i;
	int		pfd[2];
	int		prev;
	pid_t	pid;

	i = 1;
	prev = dup(ffd[0]);
	close(ffd[0]);
	while (cmdlst)
	{
		if (pipe(pfd) == -1)
			perror("pipe creation failed");
		pid = fork();
		if (!pid)
		{
			dup2(prev, 0);
			close(prev);
			ft_exec(cmdlst, pfd, ffd);
		}
		close(prev);
		prev = dup(pfd[0]);
		closer(2, pfd[0], pfd[1]);
		cmdlst = cmdlst->next;
	}
	waitpid(0, NULL, 0); //get pid from last fork, wait in while cmds
}

// pour imiter bash: if cmd not fount -> prog continue;
// if invalid infile(rights or not found) -> skip cmd01, continue;
// if invalid outfile -> ex cmds;
// av[1]=infile av[2..n]=cmds av[ac - 1]=outfile
int	main(int ac, char **av, char **envp)
{
	int			ffd[2];
	t_piplist	*cmdlst;

	ffd[0] = open(av[1], O_RDONLY);
	if (ffd[0] == -1)
	{
		perror("invalid infile");
		exit(2);
	}
	ffd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ffd[1] == -1)
	{
		perror("outfile failed");
		exit(2);
	}
	cmdlst = parser(ac, av, envp);
	apply_cmds(ffd, cmdlst);
	close(ffd[1]);
	pip_lstclear(&cmdlst, &dbarr_free);
}
