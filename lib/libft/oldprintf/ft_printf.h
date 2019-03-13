/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 14:57:24 by sklepper          #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <inttypes.h>

# define SHARP 0
# define ZERO 1
# define MINUS 2
# define PLUS 3
# define SPACE 4
# define H 0
# define L 1
# define J 2
# define Z 3

# define BASE_O "01234567"
# define BASE_HC "0123456789ABCDEF"
# define BASE_H "0123456789abcdef"
# define BUFF_SIZE 3000

typedef struct	s_data
{
	char		buff[BUFF_SIZE];
	int			flags[5];
	int			length[5];
	intmax_t	precision;
	int			width;
	int			zero;
	int			ret_val;
	intmax_t	len;
	int			idx;
	int			sign;
}				t_data;

int				path(char *ptr, va_list param, t_data *data);
int				conversion(const char *ptr, va_list param, t_data *data);
int				int_param(va_list param);
int				string_param(t_data *data, va_list param);
int				pick_f_p(va_list param, t_data *data, const char *ptr);
int				unsignedint_param_oct(va_list param);
int				unsignedint_param(va_list param);
int				unsignedint_param_hex(const char *ptr, va_list param);
int				unsignedint_param_hexc(const char *ptr, va_list param);
int				flags(const char *ptr, t_data *data);
int				flag_sharp(t_data *data);
int				flag_zero(t_data *data);
int				flag_minus(t_data *data);
int				flag_plus(t_data *data);
int				flag_space(t_data *data);
int				length(const char *ptr, t_data *data);
int				length_h(const char *ptr, t_data *data);
int				length_l(const char *ptr, t_data *data);
int				length_j(t_data *data);
int				length_z(t_data *data);
int				width(char *ptr, t_data *data);
int				precision(const char *ptr, t_data *data);
int				print_str(char *str, t_data *data, const char *ptr);
int				width_min(const char *ptr, t_data *data);
char			*to_base(uintmax_t nb, char *base);
int				pick_f_u(va_list param, t_data *data);
int				pick_f_base(va_list param, t_data *data, const char *ptr);
int				pick_f_c(va_list param, t_data *data, char ptr);
int				pick_f_w(t_data *data, va_list param);
int				pick_f_percent(t_data *data);
int				pick_f_bigs(va_list param, t_data *data);
int				pick_f_s(va_list param, t_data *data);
int				pick_f_d(va_list param, t_data *data, const char *ptr);
int				f_precision(t_data *data);
int				f_zero(t_data *data);
int				f_zero_s(t_data *data);
int				f_width(t_data *data);
int				f_width_s(t_data *data);
void			init_struct(t_data *data);
int				check(const char *ptr);
int				path_check(char *ptr, t_data *data);
int				check_s(t_data *data);
int				check_s_c_p(t_data *data);
int				check_di(t_data *data);
int				check_ox(t_data *data);
int				check_u(t_data *data);
int				fill_buff_c(t_data *data, char c);
int				ft_printf(const char *str, ...);
int				write_str(t_data *data, char *str);
int				write_w(t_data *data, wchar_t unicode);
void			determine_w_len(t_data *data, wchar_t unicode);
int				f_width_p(t_data *data, uintptr_t nb);
int				exception_zero_x(t_data *data, const char *ptr);
int				exception_bigs(t_data *data, char *ptr);
int				exception_zero_u(t_data *data);

#endif
