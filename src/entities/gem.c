/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:46:40 by ledelbec          #+#    #+#             */
/*   Updated: 2024/01/26 15:09:43 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../entity.h"
#include <stdio.h>

t_entity	*gem_new(t_game *game, t_vec2 pos)
{
	t_entity	*gem;

	gem = malloc(sizeof(t_entity));
	gem->game = game;
	gem->type = ETYPE_GEM;
	gem->state = STATE_NOT_ALIVE;
	gem->pos = pos;
	gem->box = (t_box){{0, 0}, {32 * SCALE, 32 * SCALE}};
	gem->update = gem_update;
	gem->sprite = game->gem;
	gem->z_index = 1;
	return (gem);
}

void	gem_update(t_game *game, t_entity *entity)
{
	if (box_collide_with_box(box_for_position(entity->box, entity->pos),
			box_for_position(game->player->box, game->player->pos)))
	{
		entity->state = STATE_DEAD;
		game->collectibles++;
		printf("Collectibles: %d/%d\n",
			game->collectibles,
			game->collectibles_count);
	}
}