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

typedef struct s_piplist
{
	char				*path;
	char				**cmd;
	struct s_piplist	*next;
}						t_piplist;

t_piplist	*parser(int ac, char **av, char **envp, int i);
void		dbarr_free(char **arr);
void		closer(int count, ...);
t_piplist	*pip_lstnew(char *path, char **cmd);
int			pip_lstsize(t_piplist *lst);
t_piplist	*pip_lstlast(t_piplist *lst);
void		pip_lstadd_back(t_piplist **lst, t_piplist *new);
void		pip_lstclear(t_piplist **lst, void (*del)(char **));

#endif
