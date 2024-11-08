/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:13:47 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:28:53 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "projectile.h"
#include "../so_long.h"
#include <stdlib.h>

void	projectile_spawn(t_game *game, t_entity *entity, t_projectile_ext *ext)
{
	entity->state = 2;
	entity->hitbox = (t_box){{8, 8}, {8, 8}};
	ext->direction.y = 0;
	ext->speed = 20;
	ext->light = malloc(sizeof(t_light));
	ext->light->disabled = 0;
	ext->light->intensity = 0.8;
	ext->light->range = 20;
	ext->light->color = 0xffffff;
	ext->knockback = 100;
}

void	projectile_update(t_game *game, t_entity *entity, t_projectile_ext *ext)
{
	t_box		box;
	t_entity	*collided_entity;

	entity->x += ext->direction.x * ext->speed;
	entity->y += ext->direction.y * ext->speed;
	box = box_from_entity(entity);
	if (physx_collide_with_terrain(box, game->map))
	{
		entity->state = 0;
		ext->light->disabled = 1;
	}
	collided_entity = physx_collide_with_entities(box, game->map, ext->mask);
	if (collided_entity)
	{
		collided_entity->health -= ext->damage;
		collided_entity->velocity = vec2_add(collided_entity->velocity,
				vec2_scale(ext->direction, ext->knockback));
		collided_entity->current_blink_time = collided_entity->blink_time;
		entity->state = 0;
		ext->light->disabled = 1;
	}
	box.max.x += entity->velocity.x;
	if (physx_collide_with_entities(box, game->map, MASK_SOLID))
		entity->state = 0;
}
