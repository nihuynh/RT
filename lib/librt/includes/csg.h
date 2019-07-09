/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 19:02:52 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/09 13:23:35 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSG_H
# define CSG_H

# include "rtstruct.h"

typedef struct	s_csg_op
{
	int			type;
}				t_csg_op;

typedef struct s_inter_csg	t_inter_csg;

struct			s_inter_csg
{
	t_inter		inter;
	t_inter_csg	*next;
};

#endif
