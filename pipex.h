/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:04:56 by agamay            #+#    #+#             */
/*   Updated: 2024/12/02 16:41:15 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <libft.h>

typedef struct s_piplist
{
	char				*path;
	char				**cmd;
	struct s_piplist	*next;
	struct s_piplist	*prev;
}						t_piplist;

t_piplist	*parser(int ac, char **av, char **envp);
void		secured_pipe(int pdf[0][2], t_piplist *cmdlst,
				int ffd[2], int prev);
pid_t		secured_fork(t_piplist *cmdlst, int pfd[2], int ffd[2], int prev);
void		waiter(int len, t_piplist *cmdlst);
void		dbarr_free(char **arr);
void		ft_error(int errtype);
void		closer(int count, ...);
t_piplist	*pip_lstnew(char *path, char **cmd);
t_piplist	*pip_lstlast(t_piplist *lst);
void		pip_lstadd_back(t_piplist **lst, t_piplist *new);
void		pip_lstclear(t_piplist **lst, void (*del)(char **));

#endif
