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
void	ft_exec(char *avcmd, int pfd[2], int state)
{
	char	*path;
	char	**cmd;

	if (state)
		dup2(pfd[0], 0);
	if (state != 2)
		dup2(pfd[1], 1);
	closer(2, pfd[0], pfd[1]);
	cmd = ft_split(avcmd, ' ');
	path = ft_strjoin("/usr/bin/", cmd[0]);
	execve(path, cmd, NULL);
	perror("execve failed");
	exit(2);
}

// [ 5 | 6 ] 4
// [ 4 | 6 ] 5
// [ 5 | 6 ] 4 

//creates forks until there are no more cmds to execute
void	apply_cmds(int ffd[2], int ac, char **av)
{
	int		i;
	int		pfd[2];
	int		prev;
	pid_t	pid;

	i = 1;
	prev = dup(STDIN_FILENO);
	while (++i < ac - 1)
	{
		if (pipe(pfd) == -1)
			perror("pipe creation failed");
		pid = fork();
		if (!pid)
		{
			if (i == 2)
			{
				dup2(ffd[0], 0);
				closer(2, ffd[0], ffd[1]);
				ft_exec(av[i], pfd, 0);
			}
			if (i == ac -2)
			{
				dup2(ffd[1], 1);
				closer(2, ffd[0], ffd[1]);
				ft_exec(av[i], pfd, 2);
			}
			closer(2, ffd[0], ffd[1]);
			ft_exec(av[i], pfd, 1);
		}
		closer(2, pfd[1], prev);//verifier les closes (pfd[0]?)
		prev = pfd[0];
	}
	waitpid(0, NULL, 0);
	closer(3, ffd[0], ffd[1], pfd[0]);
}

int main(int ac, char **av, char **envp)//add **envp? -> tableau de variables ->>>> PATH
{
	int		ffd[2];
	t_list	*cmdlst;
// av[1]=infile av[2..n]=cmds av[ac - 1]=outfile

	cmdlst = parser(ac, av, envp);
	ffd[0] = open(av[1], O_RDONLY);
		if (ffd[0] == -1)
			perror("invalid infile");
	ffd[1] = open(av[ac - 1], O_WRONLY | O_CREAT, 0744);
		if (ffd[1] == -1)
			perror("outfile failed");
	apply_cmds(ffd, ac, av);
}
