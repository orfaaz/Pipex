/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:03:44 by agamay            #+#    #+#             */
/*   Updated: 2024/11/14 22:47:49 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "pipex.h"
/*
int	main()
{
	int		fdout;
	int		fdin;
	char	*cmd1[] = {"grep", "ret", NULL};

	fdout = open("outtest.txt", O_RDWR | O_CREAT, 0777);
	fdin = open("intest.txt", O_RDONLY);
	char	*envp[] = {NULL};

	dup2(fdin, 0);
	dup2(fdout, 1);
	close(fdin);
	close(fdout);
	execve("/bin/grep", cmd1, envp);
}*/
/*
int	main()
{
	int		fdout;
	int		fdin;
	int		pfd[2];
	pid_t	pid;
	char	*cmd1[] = {"pwd", "-L", NULL};
	char	*cmd2[] = {"wc", "-c", NULL};
	char	*envp[] = {NULL};

	fdout = open("outtest.txt", O_WRONLY | O_CREAT, 0777);
	fdin = open("intest.txt", O_RDONLY);

	pipe(pfd);
	pid = fork();
	if (!pid)
	{
		close(fdout);
		close(pfd[0]);
		
		dup2(fdin, 0);
		dup2(pfd[1], 1);
		close(fdin);
		close(pfd[1]);
		execve("/bin/pwd", cmd1, envp);
	}
	wait(NULL);
	close(pfd[1]);
	close(fdin);

	dup2(pfd[0], 0);
	dup2(fdout, 1);
	close(pfd[0]);
	close(fdout);

	execve("/bin/wc", cmd2, envp);
}*/
/*
int	main(int ac, char **av)
{
	int	fdin;
	int	fdout;
	int	pfd[2];
	int	pid1;
	int	i;
	// av[1]=infile av[2..n]=cmds av[ac - 1]=outfile

	fdin = open(av[1], O_RDONLY);
		if (fdin == -1)
			perror("invalid infile");
	fdout = open(av[ac - 1], O_WRONLY | O_CREAT, 0744);
		if (fdout == -1)
			perror("outfile failed");
	if (pipe(pfd) == -1)
		perror("pipe failed");
	i = 0;	
	pid1 = fork();
	if (!pid1)
	{
		write(pfd[1], "5", 1);
		printf("%d 1 is done writing\n", getpid());
		close(pfd[0]);
		close(pfd[1]);
		exit(3);	
	}
	int pid2 = fork();
	if(!pid2)
	{
		char *str = ft_calloc(2, 1);
		read(pfd[0], str, 1);
		printf("%d 2 is done reading\n", getpid());
		printf("should print 5: %s\n", str);
		char *join = ft_strjoin(str, "6");
		free(str);
		printf("should print 56: %s\n", join);
		write(pfd[1], join, 2);
		printf("%d 2 is done writing\n", getpid());
		free(join);
		close(pfd[0]);
		close(pfd[1]);
		exit(2);
	}
	waitpid(pid1, NULL, 0);
	char *str2 = ft_calloc(3, 1);
	read(pfd[0], str2, 2);
	printf("parent should print 56: %s\n", str2);
	free(str2);
	close(pfd[0]);
	close(pfd[1]);
}*/
/*
int	main()
{//test de dups
	int fd1 = open("txt_in", O_WRONLY);
	int fd2 = open("txt_out", O_WRONLY);
	dup2(fd2, fd1);
	write(fd1, "987654321\n", 10);
	dup2(fd1, 1);
	write(1, "123456789\n", 10);
	close(fd1);
	close(fd2);
}*/
/*
int	main()
{
	int	pid;
	pid = fork();
	if (!pid)
		return (0);
	printf("%d\n", pid);
	pid = fork();
	if (!pid)
		return (0);
	printf("%d\n", pid);
	pid = fork();
	if (!pid)
		return (0);
	printf("%d\n", pid);
	printf("%d\n", getpid());
}*/

int	main()
{
	int	fd1 = open("intest.txt", O_WRONLY);
	int	fd2 = dup(fd1);
	write(fd2, "111", 3);
	close(fd1);
	write(fd2, "222", 3);
	close(fd2);
}