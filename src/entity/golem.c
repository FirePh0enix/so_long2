/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golem.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:34:27 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:13:05 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "golem.h"
#include "../so_long.h"

void	golem_spawn(t_game *game, t_entity *entity, t_golem_ext *ext)
{
	entity->state = 1;
	entity->health = 20;
	entity->collision_mask = MASK_ENEMY;
	entity->hitbox = (t_box){{8 * PIXEL_SCALE, 0},
	{24 * PIXEL_SCALE, 32 * PIXEL_SCALE}};
}

void	golem_update(t_game *game, t_entity *entity, t_golem_ext *ext)
{
	if (entity->health <= 0)
		entity->state = 0;
	if (entity->current_blink_time > 0)
		entity->current_blink_time -= 16;
}
