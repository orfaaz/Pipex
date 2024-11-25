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

# ifndef
#  define BUFFER_SIZE 50
# endif

t_list	*parser(int ac, char **av, char **envp);

typedef	struct	s_list
{
	char			*path;
	char			**cmd;
	struct s_list	*next;
}					t_list;

#endif
