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
static void	ft_exec(t_piplist *cmdlst, int pfd[2], int ffd[2], int jump_cmd)
{
	if (cmdlst->next)
		dup2(pfd[1], 1);
	else
		dup2(ffd[1], 1);
	closer(3, pfd[0], pfd[1], ffd[1]);
	if (!cmdlst->cmd || jump_cmd == 1)
	{
		pip_lstclear(&cmdlst, &dbarr_free);
		exit(EXIT_SUCCESS);
	}
	execve(cmdlst->path, cmdlst->cmd, NULL);
	perror("execve failed");
	pip_lstclear(&cmdlst, &dbarr_free);
	exit(EXIT_FAILURE);
}

//creates forks until there are no more cmds to execute
static void	apply_cmds(int ffd[2], t_piplist *cmdlst, int len, int jump_cmd)
{
	int		pfd[2];
	int		prev;
	pid_t	pid;

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
			ft_exec(cmdlst, pfd, ffd, jump_cmd);
		}
		jump_cmd = 0;
		close(prev);
		prev = dup(pfd[0]);
		closer(2, pfd[0], pfd[1]);
		cmdlst = cmdlst->next;
	}
	while (len--)
		waitpid(0, NULL, 0);
}

int	main(int ac, char **av, char **envp)
{
	int			ffd[2];
	int			jump_cmd;
	t_piplist	*cmdlst;

	if (ac < 4)
		ft_error(0);
	if (!envp)
		ft_error(1);
	jump_cmd = 0;
	ffd[0] = open(av[1], O_RDONLY);
	if (ffd[0] == -1)
	{
		perror("infile failed");
		jump_cmd++;
	}
	ffd[1] = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ffd[1] == -1)
	{
		perror("outfile failed");
		exit (EXIT_FAILURE);
	}
	cmdlst = parser(ac, av, envp);
	apply_cmds(ffd, cmdlst, ac - 3, jump_cmd);
	close(ffd[1]);
	pip_lstclear(&cmdlst, &dbarr_free);
}
