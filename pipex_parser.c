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
#include "libft.h"

void    dbarr_free(char **arr)
{
    int size;

    size = 0;
    while (*arr)
    {
        free(*arr);
        arr++;
        size++;
    }
    free(arr - size);
}

//Creates an **arr of all pathes in envp PATH.
//So we can look for shell cmds in these later
char    **pathsplit(char **envp)
{
    char    **ret;
    char    *tmp;
    int     stop;

    stop = 1;
    while (*envp && stop)
    {
        if (!ft_strncmp(*envp, "PATH=", 5))
        {
            tmp = ft_substr(*envp, 5, ft_strlen(*envp));
            ret = ft_split(tmp, ':');
            free(tmp);
            stop = 0;
        }
        envp++;
    }
    return (ret);
}

//If the cmd exists in the given path, this will create a node
//w the infos we'll need for the execve().
int check_access(char *path, char *avi, p_list **cmdlst)
{
    char    *path_cmd;
    char    **cmd;

    if (!*avi)
        return (0);
    cmd = ft_split(avi, ' ');
    if (!cmd)
    {
        perror("slit failed");
        exit (2);
    }
    if (!access(cmd[0], X_OK))
    {
        pip_lstadd_back(cmdlst, pip_lstnew(path, cmd));
        return (1);
    }
    path_cmd = ft_vastrjoin(3, path, "/", cmd[0]);
    if (!access(path_cmd, X_OK))
    {
        pip_lstadd_back(cmdlst, pip_lstnew(path_cmd, cmd));
        return (1);
    }
    free(path_cmd);
    dbarr_free(cmd);
    return (0);
}

//check X_OK of each cmd. 
//return a lst containing each path and **cmd
p_list  *parser(int ac, char **av, char **envp)
{
    p_list  *cmdlst;
    char    **envpath;
    int     i;
    int     j;

    envpath = pathsplit(envp);
    cmdlst = NULL;
    i = 1;
    j = 0;
    while (++i < ac - 1)
    {
        while (envpath[j] && !check_access(envpath[j], av[i], &cmdlst))
        {
            j++;
            if (!envpath[j])
            {
                ft_printf("cmd not found: %s\n", av[i]);
                exit(2);
            }
        }
        j = 0;
    }
    dbarr_free(envpath);
    return (cmdlst);
}
