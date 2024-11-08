/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:05:03 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:05:06 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

typedef struct s_light
{
	int		x;
	int		y;
	int		color;
	int		range;
	int		disabled;
	float	intensity;
}	t_light;

/*
 * Check if a given position is in the range of the light.
 */
float	light_intensity(t_light *light, int x, int y);

#endif
