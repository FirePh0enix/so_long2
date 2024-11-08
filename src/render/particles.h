/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particles.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:05:53 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:06:02 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLES_H
# define PARTICLES_H

# include "../physics/physics.h"
# include "../sprite.h"

typedef struct s_particle_instance
{
	t_vec2	position;
	t_vec2	direction;
	float	speed;
}	t_particle_instance;

// speed_variation - The actual speed of each particles will be +/- the value
typedef struct s_particles
{
	t_sprite			*sprite;
	t_vec2				dir;
	float				dir_variation;
	float				origin_variation;
	float				speed;
	float				speed_variation;
	t_particle_instance	*particles;
}	t_particles;

t_particles	*particles_new(int max);
void		particles_step(t_particles *particles);

#endif
