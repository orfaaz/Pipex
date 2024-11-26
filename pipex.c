/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:04:00 by agamay            #+#    #+#             */
/*   Updated: 2024/11/14 17:13:31 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

// 	while (read_size)//reads and puts successive reads in a list
// 	{
// 		lstadd_back(*read_lst);
// 		read_size = read(fd, *read_lst->content, BUFFER_SIZE);
// 	}
// 	strin = malloc(nb of reads * read size + 1);
// 	while (*read_lst)//cats lst->contents in str
// 	{
// 		strin++ = *read_lst->content;
// 		*read_lst = read_lst=>next;
// 	}
// //	close(fd); ?
// 	return (strin);
// }

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
void	ft_exec(p_list *cmdlst, int pfd[2], int ffd[2])
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
void	apply_cmds(int ffd[2], p_list *cmdlst)
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
		closer(2, pfd[0], pfd[1]);//verifier les closes (pfd[0]?)
		cmdlst = cmdlst->next;
	}
	waitpid(0, NULL, 0);
	close(ffd[1]);
}

// av[1]=infile av[2..n]=cmds av[ac - 1]=outfile
int main(int ac, char **av, char **envp)
{
	int		ffd[2];
	p_list	*cmdlst;

	cmdlst = parser(ac, av, envp);
	ffd[0] = open(av[1], O_RDONLY);
		if (ffd[0] == -1)
			perror("invalid infile");
	ffd[1] = open(av[ac - 1], O_WRONLY | O_CREAT, 0744);
		if (ffd[1] == -1)
			perror("outfile failed");
	apply_cmds(ffd, cmdlst);
	pip_lstclear(&cmdlst, &dbarr_free);
}
