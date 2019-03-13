/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 08:09:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/11/26 02:16:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

inline static int	ft_max(int x, int y)
{
	return (x > y) ? x : y;
}

inline static int	ft_min(int x, int y)
{
	return (x > y) ? y : x;
}

int					ft_btw(int value, int limit1, int limit2)
{
	return (value >= ft_min(limit1, limit2) && value <= ft_max(limit1, limit2));
}
