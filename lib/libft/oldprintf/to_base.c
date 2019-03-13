/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 11:46:34 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/04 13:56:08 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftstring.h"
#include "ft_printf.h"

static char	*ft_swap_chars(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++j])
		str[++i] = str[j];
	str[--j] = '\0';
	return (str);
}

static char	*base_exception(uintmax_t nb, char *base)
{
	if (!base)
		return (NULL);
	if (nb == 0)
		return (ft_strdup("0"));
	return (NULL);
}

char		*to_base(uintmax_t nb, char *base)
{
	intmax_t	i;
	uintmax_t	prod;
	uintmax_t	tmp;
	char		*result;

	if (!base || nb == 0)
		return (base_exception(nb, base));
	prod = (ft_strcmp(base, BASE_O) == 0) ? 8 : 16;
	i = (nb < prod) ? 1 : 0;
	tmp = nb;
	while (tmp > 0)
	{
		tmp = tmp / prod;
		i++;
	}
	if (!(result = ft_strnew(i)))
		return (NULL);
	result[i] = '\0';
	tmp = nb;
	while (--i >= 0)
	{
		result[i] = base[nb % prod];
		nb = nb / prod;
	}
	return ((result[++i] == '0' && tmp != 0) ? ft_swap_chars(result) : result);
}
