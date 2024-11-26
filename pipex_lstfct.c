/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_lstfct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:07:15 by agamay            #+#    #+#             */
/*   Updated: 2024/11/26 14:07:17 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

p_list  *pip_lstnew(char *path, char **cmd)
{
    p_list	*new_node;

	new_node = malloc(sizeof(p_list));
	if (!new_node)
		return (NULL);
	new_node->path = path;
    new_node->cmd = cmd;
	new_node->next = NULL;
	return (new_node);
}

p_list	*pip_lstlast(p_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	pip_lstadd_back(p_list **lst, p_list *new)
{
	p_list	*temp;

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

void	pip_lstclear(p_list **lst, void (*del)(char **))
{
	void	*temp;

	if (!(lst && *lst && del))
		return ;
	temp = *lst;
	while (*lst)
	{
        free((*lst)->path);
		del((*lst)->cmd);
		*lst = (*lst)->next;
		free(temp);
		temp = *lst;
	}
}
