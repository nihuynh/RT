/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 09:14:13 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/12 18:25:23 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

# define MASK_RED	0xFF0000
# define MASK_GREEN	0xFF00
# define MASK_BLUE	0xFF

typedef struct		s_color
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
}					t_color;

#endif
