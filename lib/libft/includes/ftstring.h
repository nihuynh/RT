/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftstring.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:09:51 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/08 15:43:43 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSTRING_H
# define FTSTRING_H

# include <stddef.h>

size_t	ft_strlen(char const *str);
char	*ft_strdup(char const *src);
char	*ft_strcpy(char *dst, char const *src);
char	*ft_strncpy(char *dst, char const *src, size_t n);
size_t	ft_strlcpy(char *dst, char const *src, size_t n);
char	*ft_strcat(char *dst, char const *src);
char	*ft_strncat(char *dst, char const *src, size_t n);
size_t	ft_strlcat(char *dst, char const *src, size_t size);
char	*ft_strchr (char const *str, int c);
char	*ft_strrchr (char const *str, int c);
char	*ft_strstr(char const *haystack, char const *needle);
char	*ft_strnstr(char const *haystack, char const *needle, size_t len);
int		ft_strcmp(char const *s1, const char *s2);
int		ft_strncmp(char const *s1, const char *s2, size_t n);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *str);
void	ft_striter(char *str, void (*f)(char*));
void	ft_striteri(char *str, void (*f)(unsigned int, char*));
char	*ft_strmap(char const *str, char (*f)(char));
char	*ft_strmapi(char const *str, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
char	*ft_strsub(char const *s1, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strsubfree(char const *s1, unsigned int start, size_t len);
char	*ft_strjoinfree(char const *s1, char const *s2);
char	*ft_strtrim(char const *str);
char	**ft_strsplit(char const *str, char c);
size_t	ft_strclen(char const *s, char c);
int		ft_strcasecmp(char const *s1, char const *s2);
int		ft_strncasecmp(char const *s1, char const *s2, size_t n);
char	*ft_strndup(char const *src, size_t n);
int		ft_str_is_alpha(char *str);
int		ft_str_is_lowercase(char *str);
int		ft_str_is_numeric(char *str);
int		ft_str_is_printable(char *str);
int		ft_str_is_uppercase(char *str);
char	*ft_strlowcase(char *str);
char	*ft_strupcase(char *str);
char	*ft_strcapitalize(char *str);
char	*ft_strcasestr(char const *str, char const *needle);
char	*ft_strpbrk(char const *s1, char const *s2);
char	*ft_strnchr(char const *str, int c, int size);
size_t	ft_wordcount(char const *str, char c);

#endif
