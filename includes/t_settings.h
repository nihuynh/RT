/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_settings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 00:13:33 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/03 00:18:55 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SETTINGS_H
# define T_SETTINGS_H

# include "color.h"
# include <stdbool.h>

typedef struct	s_settings
{
	t_color		back_color;
	t_color		amb_light;
	t_color		filter;
	bool		light;
	bool		facing;
	bool		i_light;
	bool		shine;
	bool		shadow;
	bool		deflect;
	bool		absorb;
	bool		anti_a;
	bool		debug_normal;
	bool		normal_mapping;
	int			depth_max;
	float		fov;
}				t_settings;

#endif
