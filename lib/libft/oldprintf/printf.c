/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:59:43 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ftstring.h"
#include <unistd.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <limits.h>

static int	printuntil(const char *str, const char *ptr, t_data *data)
{
	int i;

	i = -1;
	while (str[++i] && str + i != ptr && str[i] != '\0' && str[i] != '%')
	{
		fill_buff_c(data, str[i]);
	}
	return (i);
}

void		init_struct(t_data *data)
{
	int i;

	data->precision = 0;
	data->width = 0;
	data->len = 0;
	data->sign = 0;
	i = -1;
	while (++i <= 4)
		data->flags[i] = 0;
	i = -1;
	while (++i <= 4)
		data->length[i] = 0;
}

int			init_printf(t_data *data, const char *str)
{
	init_struct(data);
	data->ret_val = 0;
	data->idx = -1;
	if (!ft_strcmp((char *)str, "%") && ft_strlen(str) == 1)
		return (0);
	return (1);
}

char		*f_while(t_data *data, const char *str, char *ptr, va_list ptr_lst)
{
	int i;

	init_struct(data);
	printuntil(str, ptr, data);
	ptr += 1;
	while (ptr && (i = path(ptr, ptr_lst, data)) > 0)
		ptr += i;
	if (data->ret_val > 0)
		write(1, &data->buff, ++data->idx);
	data->idx = -1;
	return (ptr);
}

int			ft_printf(const char *str, ...)
{
	va_list	pointerlst;
	char	*ptr;
	t_data	data;

	if (!str)
		return (0);
	va_start(pointerlst, str);
	if (init_printf(&data, str) == 0)
		return (0);
	while ((ptr = ft_strchr(str, '%')) != NULL)
	{
		ptr = f_while(&data, str, ptr, pointerlst);
		if (*ptr)
			ptr += 1;
		str = ptr;
	}
	printuntil(str, ptr, &data);
	if (data.ret_val > -1)
		write(1, &data.buff, ++data.idx);
	va_end(pointerlst);
	return (data.ret_val);
}
