/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:42:23 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:22:55 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"
#include <math.h>

t_vec2	vec2_add(t_vec2 l, t_vec2 r)
{
	return ((t_vec2){l.x + r.x, l.y + r.y});
}

t_vec2	vec2_sub(t_vec2 l, t_vec2 r)
{
	return ((t_vec2){l.x - r.x, l.y - r.y});
}

t_vec2	vec2_scale(t_vec2 vec, float scale)
{
	return ((t_vec2){vec.x * scale, vec.y * scale});
}

int	vec2_is_zero(t_vec2 vec)
{
	const float	e = 0.00001;

	return (vec.x > -e && vec.x < e && vec.y > -e && vec.y < e);
}
