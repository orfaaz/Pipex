/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:04:56 by agamay            #+#    #+#             */
/*   Updated: 2024/11/14 15:36:59 by agamay           ###   ########.fr       */
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

typedef	struct	q_list
{
	char			*path;
	char			**cmd;
	struct q_list	*next;
}					p_list;

p_list	*parser(int ac, char **av, char **envp);
void    dbarr_free(char **arr);
void	closer(int count, ...);
p_list  *pip_lstnew(char *path, char **cmd);
p_list	*pip_lstlast(p_list *lst);
void	pip_lstadd_back(p_list **lst, p_list *new);
void	pip_lstclear(p_list **lst, void (*del)(char **));

#endif
