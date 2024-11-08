/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:11:15 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:12:03 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"
#include "../so_long.h"
#include "libft.h"

void	door_spawn(t_game *game, t_entity *entity, t_door_ext *ext)
{
	entity->state = 2;
	entity->hitbox = (t_box){{0, 0}, {32, 32}};
	ext->anim = new_anim(6, game->tiles.door, 0, 200);
	ext->light = malloc(sizeof(t_light));
	ext->light->x = entity->x + entity->sprite->width / 2;
	ext->light->y = entity->y;
	ext->light->color = 0xffffff;
	ext->light->range = 150;
	ext->light->intensity = 1.0;
	ext->light->disabled = 0;
	add_light(game, ext->light);
}

void	door_update(t_game *game, t_entity *entity, t_door_ext *ext)
{
	entity->sprite = ext->anim->sprites[ext->anim->current];
	if (game->collectibles == game->total_collectibles)
		anim_step(ext->anim);
	if (ext->anim->current >= 4 && physx_box_collision(box_from_entity(entity),
			box_from_entity(game->map->player)))
		ft_printf("YOU WIN!\n");
}
