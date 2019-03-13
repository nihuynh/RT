/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftio.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:09:10 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/10 14:04:41 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTIO_H
# define FTIO_H

void	ft_putchar(char c);
void	ft_putstr(char const *str);
void	ft_putendl(char const *str);
void	ft_putnbr(int n);
void	ft_putnbr_base(int nb, unsigned int base);
void	ft_putnbr_base_low(int nb, unsigned int base);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *str, int fd);
void	ft_putendl_fd(char const *str, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_puttab(char **tab);
void	ft_putctab(char **tab, char c);
void	ft_print_value(char *name, int value);
void	ft_error(const char function[], int line);
int		ft_fopen_read(char *file_name);
int		ft_gnl(int const fd, char **line, char *endlsep);
int		ft_printf(const char *str, ...);

#endif
