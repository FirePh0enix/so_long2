/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:06:29 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:07:09 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particles.h"
#include "../vector.h"

void	particles_step(t_particles *particles)
{
	unsigned int	i;

	i = 0;
	while (i < vector_size(particles->particles))
	{
		particles->particles[i].position = vec2_add(
				particles->particles[i].position,
				vec2_scale(particles->particles[i].direction,
					particles->particles[i].speed));
		i++;
	}
}
