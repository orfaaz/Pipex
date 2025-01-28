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
#include "libft.h"

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
