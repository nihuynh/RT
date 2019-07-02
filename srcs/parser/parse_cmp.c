/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 23:14:44 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/02 23:15:20 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "ftstring.h"

int
	matcmp(void *content, void *key)
{
	t_material	*mat;
	char		*ckey;

	mat = content;
	ckey = key;
	return (!ft_strncasecmp(mat->name, ckey, ft_strlen(mat->name)));
}

int
	texcmp(void *content, void *key)
{
	t_texture	*tex;
	char		*ckey;

	tex = content;
	ckey = key;
	return (!ft_strncasecmp(tex->name, ckey, ft_strlen(tex->name)));
}

int
	obj_cmp_key(void *content, void *key)
{
	t_obj	*obj;
	char	*ckey;

	obj = content;
	ckey = key;
	return (!ft_strncmp(obj->name, ckey, ft_strlen(obj->name)));
}

int
	light_cmp_key(void *content, void *key)
{
	t_light	*light;
	char	*ckey;

	light = content;
	ckey = key;
	return (!ft_strncmp(light->name, ckey, ft_strlen(light->name)));
}
