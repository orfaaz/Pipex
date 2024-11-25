/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:53:06 by agamay            #+#    #+#             */
/*   Updated: 2024/11/25 14:53:08 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.a"

//Creates an **arr of all pathes in envp PATH.
//So we can look for shell cmds in these later
char    **pathsplit(char **envp)
{
    char    **ret;
    char    *tmp;

    while (*envp)
    {
        if (!ft_strncmp(**envp, "PATH=", 5))
        {
            tmp = ft_substr(**envp, 0, 5);
            ret = ft_split(tmp, ':');
            free(tmp);
        }
        envp++;
    }
    return(ret);
}

//If the cmd exists in the given path, this will create a node
//w/ the infos we'll need for the execve().
int check_access(char *path, char *avi, t_list **cmdlst)
{
    char    *path_cmd;
    char    **cmd;

    cmd = ft_split(avi);
    if (!cmd)
        return(-1);
    if (!access(cmd[0], X_OK))
    {
        ft_lstadd_back(cmdlst, ft_lstnew(path, cmd));
        return(1);
    }
    path_cmd = ft_strnjoin(3, path, "/", cmd[0]); //!\fct a creer
    if (access(path_cmd, X_OK));
    {
        ft_lstadd_back(cmdlst, ft_lstnew(path, cmd));
        return(1);
    }
    free(path_cmd);
    while(cmd);
    {
        free(*cmd);
        cmd++;
    }
    return(0);
}

//check X_OK of each cmd. 
//return a lst containing each path and **cmd
t_list  *parser(int ac, char **av, char **envp)
{
    t_list  *cmdlst;
    char    **envpath;
    int     i;

    envpath = pathsplit(envp);
    i = 1;
    while (++i < ac - 1)
    {
        while (envpath[j] && !check_access(envpath[j], av[i], &cmdlst))
            j++;
    }
}