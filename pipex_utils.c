/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:45:03 by agamay            #+#    #+#             */
/*   Updated: 2025/01/28 15:45:06 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dbarr_free(char **arr)
{
	int	size;

	size = 0;
	while (*arr)
	{
		free(*arr);
		arr++;
		size++;
	}
	free(arr - size);
}

void	ft_error(int errtype)
{
	if (errtype == 0)
	{
		perror("Too few arguments");
		exit(EXIT_FAILURE);
	}
	if (errtype == 1)
	{
		perror("envp not found");
		exit(EXIT_FAILURE);
	}
	if (errtype == 2)
	{
		perror("PATH in envp not found");
		exit(EXIT_FAILURE);
	}
}

void	secured_pipe(int pfd[0][2], t_piplist *cmdlst, int ffd[2], int prev)
{
	if (pipe(*pfd) == -1)
	{
		perror("pipe creation failed");
		pip_lstclear(&cmdlst, &dbarr_free);
		closer(2, ffd[1], prev);
		exit(EXIT_FAILURE);
	}
}

pid_t	secured_fork(t_piplist *cmdlst, int pfd[2], int ffd[2], int prev)
{
	pid_t	ret;

	ret = fork();
	if (ret == -1)
	{
		perror("fork failed");
		pip_lstclear(&cmdlst, &dbarr_free);
		closer(4, pfd[0], pfd[1], ffd[1], prev);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

void	waiter(int len, t_piplist *cmdlst)
{
	int		status;
	pid_t	pid;

	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == -1)
		{
			perror("waitpid failed");
			pip_lstclear(&cmdlst, &dbarr_free);
			exit(EXIT_FAILURE);
		}
	}
}
