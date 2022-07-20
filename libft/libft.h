/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahrach <slahrach@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:29:10 by slahrach          #+#    #+#             */
/*   Updated: 2022/07/20 06:19:26 by slahrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_fds
{
	int				fd;
	struct s_fds	*next;
}	t_fds;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				flag;
	int				flag_unset_path;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	int				id;
	char			*content;
	struct s_redir	*next;
}	t_redir;

typedef struct s_list
{
	int				fd_in;
	int				fd_out;
	int				err;
	int				id;
	int				exit_status;
	struct s_list	*inside;
	char			*content;
	char			**arr;
	int				pipe_after;
	int				pipe_before;
	t_redir			*redirect;
	struct s_list	*next;
}	t_list;

typedef struct s_tools
{
	int		p[2];
	char	*path;
}	t_tools;

int			ft_isalpha(int c);
int			ft_isdigit(int arg);
int			ft_isalnum(int arg);
int			ft_isascii(int arg);
int			ft_isprint(int arg);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *ptr, int x, size_t count);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy( char *dst, const char *src, size_t sizedst);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strchr1(const char *s, int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *origin, const char *find, size_t len);
long long	ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin1(char *s1, char *s2);
char		*ft_strjoin2(char *s1, char *s2);
char		*ft_strtrim(char *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int nbr);
char		*ft_strmapi(char const *s, int (*f)(int));
void		ft_striteri(char *s, void (*f) (unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst);
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_redir		*redir_new(char	*content, int id);
t_redir		*redir_last(t_redir *lst);
void		redir_add_front(t_redir **lst, t_redir *new);
void		redir_add_back(t_redir **lst, t_redir *new);
void		ft_lstclear1(t_list **lst);
void		clear_env(t_env **env);
void		ft_clear(t_redir **lst);
char		*ft_strjoin0(char *s1, char *s2);
char		**ft_split1(char const *s, char c);
void		ft_lstadd_back_fds(t_fds **lst, t_fds *new);
void		ft_lstadd_front_fds(t_fds **lst, t_fds *new);
t_fds		*ft_lstlast_fds(t_fds *lst);
t_fds		*new_fds(int fd);
void		clear_fds(t_fds **head);

#endif
