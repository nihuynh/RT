/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 02:37:54 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 19:07:16 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "ftio.h"

void	vec3_print(t_vec3 data)
{
	ft_printf("x = %f y = %f z = %f\n", data.x, data.y, data.z);
}

void	vec3_print_(char *msg, t_vec3 data)
{
	ft_printf("%s x = %f y = %f z = %f\n", msg, data.x, data.y, data.z);
}
