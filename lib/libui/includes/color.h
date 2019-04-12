/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 09:14:13 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/12 15:45:28 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

# define MASK_RED	0xFF
# define MASK_GREEN	0xFF00
# define MASK_BLUE	0xFF0000

typedef struct		s_color
{
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
}					t_color;

#endif
