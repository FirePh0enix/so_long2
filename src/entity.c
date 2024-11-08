/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:53:25 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 21:54:04 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "entity.h"
#include "libft.h"
#include "physics/physics.h"
#include "render/render.h"
#include "so_long.h"
#include <stdlib.h>

t_entity	*new_entity(t_game *game, int x, int y, t_entity_type *type)
{
	t_entity	*entity;

	entity = malloc(sizeof(t_entity));
	entity->game = game;
	entity->x = x;
	entity->y = y;
	entity->state = 0;
	entity->type = type;
	entity->sprite = type->sprite;
	entity->extension = malloc(type->extension_size);
	entity->current_blink_time = 0;
	entity->blink_time = 50;
	return (entity);
}

t_vec2	entity_size(t_entity *entity)
{
	return ((t_vec2){entity->hitbox.max.x - entity->hitbox.min.x,
		entity->hitbox.max.y - entity->hitbox.min.y});
}

int	entity_effect(int color, int x, int y, t_entity *entity)
{
	if (entity->current_blink_time > 0 && color != (int)0xff000000)
		return (blend_colors(color, 0xff0000, 0.5));
	return (color);
}
