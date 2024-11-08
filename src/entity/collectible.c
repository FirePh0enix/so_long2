/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:34:32 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:10:53 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collectible.h"
#include "../entity.h"
#include "../so_long.h"

void	collectible_spawn(t_game *g, t_entity *entity, t_collectible_ext *ext)
{
	entity->state = 2;
	entity->hitbox = (t_box){{0, 0}, {32, 32}};
	entity->collision_mask = 0;
	ext->light = malloc(sizeof(t_light));
	ext->light->range = 90;
	ext->light->intensity = 1.0;
	ext->light->x = entity->x + entity->type->sprite->width / 2;
	ext->light->y = entity->y;
	ext->light->color = 0xffffff;
	ext->light->disabled = 0;
	ext->anim = new_anim(6, g->tiles.gem, 1, 200);
	add_light(g, ext->light);
}

void	collectible_update(t_game *g, t_entity *entity, t_collectible_ext *ext)
{
	if (physx_box_collision(box_from_entity(entity),
			box_from_entity(g->map->player)))
	{
		entity->state = 0;
		ext->light->disabled = 1;
		g->collectibles++;
	}
	entity->sprite = ext->anim->sprites[ext->anim->current];
	anim_step(ext->anim);
}
