/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:03:46 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:04:43 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include <math.h>

float	light_intensity(t_light *light, int x, int y)
{
	const float	distance = (x - light->x) * (x - light->x)
		+ (y - light->y) * (y - light->y);
	const float	range_squared = light->range * light->range;

	if (distance > range_squared)
		return (0.0);
	return (light->intensity * ((range_squared - distance) / range_squared));
}
