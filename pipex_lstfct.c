/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_lstfct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:07:15 by agamay            #+#    #+#             */
/*   Updated: 2024/12/02 16:37:45 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

t_piplist	*pip_lstnew(char *path, char **cmd)
{
	t_piplist	*new_node;

	new_node = malloc(sizeof(t_piplist));
	if (!new_node)
		return (NULL);
	new_node->path = path;
	new_node->cmd = cmd;
	new_node->next = NULL;
	return (new_node);
}

int	pip_lstsize(t_piplist *lst)
{
	int		len;

	if (!lst)
		return (0);
	len = 1;
	while (lst->next)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

t_piplist	*pip_lstlast(t_piplist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	pip_lstadd_back(t_piplist **lst, t_piplist *new)
{
	t_piplist	*temp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = pip_lstlast(*lst);
	temp->next = new;
}

void	pip_lstclear(t_piplist **lst, void (*del)(char **))
{
	void	*temp;

	if (!(lst && *lst && del))
		return ;
	temp = *lst;
	while (*lst)
	{
		if ((*lst)->path && (*lst)->cmd)
		{
			free((*lst)->path);
			del((*lst)->cmd);
		}
		*lst = (*lst)->next;
		free(temp);
		temp = *lst;
	}
}
