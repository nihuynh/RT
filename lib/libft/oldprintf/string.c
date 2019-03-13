/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 15:22:18 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ftstring.h"
#include <unistd.h>
#include <stdlib.h>

int		fill_buff_c(t_data *data, char c)
{
	if (data->ret_val == -1)
		return (0);
	if (data->idx + 1 <= BUFF_SIZE)
	{
		data->buff[++data->idx] = c;
		++data->ret_val;
	}
	else if (1 + data->idx > BUFF_SIZE)
	{
		write(1, &data->buff, BUFF_SIZE);
		data->idx = 0;
		fill_buff_c(data, c);
	}
	return (0);
}

int		print_str(char *str, t_data *data, const char *ptr)
{
	int	i;

	i = -1;
	if (*ptr == 's' || *ptr == 'S')
		while (str[++i] && i < (int)data->len)
			fill_buff_c(data, str[i]);
	else
		while (str[++i])
			fill_buff_c(data, str[i]);
	return (data->ret_val);
}

void	determine_w_len(t_data *data, wchar_t unicode)
{
	if (unicode < 129 || (MB_CUR_MAX == 1 && unicode <= 255))
		data->len += 1;
	else if (unicode < 2049)
		data->len += 2;
	else if (unicode < 65536)
		data->len += 3;
	else if (unicode < 2097152)
		data->len += 4;
}
