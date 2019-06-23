/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:34:56 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/23 14:48:25 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*name_obj(int type, int *nb)
{
	char		*tmp;
	char		*name;
	const char*	name_objs[] = {
		"Plane", "Sphere", "Cone", "Cylinder", "Cube", "Tore"
	};

	if (!(tmp = ft_itoa(*nb)))
		ft_error(__func__, __LINE__);
	if (ft_btw(type, 0, sizeof(name_objs) / sizeof(char*)))
	{
		if (!(name = ft_strjoin(name_objs[type], tmp)))
			ft_error(__func__, __LINE__);
	}
	else
	{
		if (!(name = ft_strjoin("Light ", tmp)))
			ft_error(__func__, __LINE__);
	}
	free(tmp);
	*nb += 1;
	return (name);
}
