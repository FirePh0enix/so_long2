/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 20:48:56 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:15:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"
#include "../so_long.h"

void	wall_spawn(t_game *game, t_entity *entity, t_wall_ext *ext)
{
	entity->state = 2;
	entity->hitbox = (t_box){{15 * PIXEL_SCALE, 3 * PIXEL_SCALE},
	{15 * PIXEL_SCALE, 29 * PIXEL_SCALE}};
	entity->collision_mask = MASK_SOLID;
	ext->death_time = getms() + 5000;
}

void	wall_update(t_game *game, t_entity *entity, t_wall_ext *ext)
{
	if (getms() > ext->death_time)
		entity->state = 0;
}
