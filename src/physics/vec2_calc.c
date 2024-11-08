/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:22:41 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:22:58 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec2.h"
#include <math.h>

float	vec2_length(t_vec2 vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2)));
}

t_vec2	vec2_normalize(t_vec2 vec)
{
	const float	length = vec2_length(vec);

	return ((t_vec2){vec.x / length, vec.y / length});
}
