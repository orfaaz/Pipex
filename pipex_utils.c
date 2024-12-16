/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:08:17 by agamay            #+#    #+#             */
/*   Updated: 2024/12/15 18:08:19 by agamay           ###   ########.fr       */
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

//frees **char
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
