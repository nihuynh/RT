/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 04:18:50 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/19 04:22:06 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parse.h"
# include "libft.h"

void	check_opening_bracket(t_parse_txt *scene_file)
{
	if (ft_strchr(scene_file->get_curr_line(scene_file), '{') != NULL)
		scene_file->line_idx++;
	else
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_P_BRACKET_OPEN, scene_file);
	}
}

void	check_closing_bracket(t_parse_txt *scene_file)
{
	if (ft_strchr(scene_file->get_curr_line(scene_file), '}') != NULL)
		scene_file->line_idx++;
	else
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_P_BRACKET_CLSE, scene_file);
	}
}
