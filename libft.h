/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agamay <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:18:58 by agamay            #+#    #+#             */
/*   Updated: 2024/11/16 13:31:44 by agamay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

int		ft_atoi(const char *nbr);
void	ft_bzero(void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int nbr);
void	*ft_memchr(const void *haystack, int needl, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *dest, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int nbr, int fd);
void	ft_putstr_fd(char *str, int fd);
char	**ft_split(const char *str, char c);
char	*ft_strchr(const char *src, int needl);
char	*ft_strdup(const char *src);
void	ft_striteri(char *str, void (*f)(unsigned int, char*));
char	*ft_strjoin(const char *str1, const char *str2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy( char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(const char *str, char (*f)(unsigned int, char));
int		ft_strncmp(const char *dest, const char *src, size_t size);
char	*ft_strnstr(const char *haystack, const char *needl, size_t size);
char	*ft_strrchr(const char *src, int needl);
char	*ft_strtrim(const char *str, const char *needl);
char	*ft_substr(const char *str, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*get_next_line(int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
