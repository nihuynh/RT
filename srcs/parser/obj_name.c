/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 14:34:56 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/28 15:17:40 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*name_obj(int type, int *nb)
{
	char		*tmp;
	char		*name;
	const char	**name_objs;

	name_objs = (const char*[]){"Plane ", "Sphere ", "Cone ", "Cylinder ", 
			"Csg "};
	if (!(tmp = ft_itoa(*nb)))
		ft_error(__func__, __LINE__);
	if (type == 5)
	{
		if (!(name = ft_strjoin("Light ", tmp)))
			ft_error(__func__, __LINE__);
	}
	else
	{
		if (!(name = ft_strjoin(name_objs[type], tmp)))
			ft_error(__func__, __LINE__);
	}
	free(tmp);
	*nb += 1;
	return (name);
}
