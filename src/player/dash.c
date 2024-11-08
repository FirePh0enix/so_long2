/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 20:49:18 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:46:43 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render/render.h"
#include "../so_long.h"
#include "player.h"

static int	afterimage_effect(int color, int x, int y, t_entity *entity)
{
	const float	ratio = 0.0
		+ ((t_player_ext *)entity->extension)->afterimage_index * 0.1;

	(void) x;
	(void) y;
	if (color == (int)0xff000000)
		return (color);
	return (blend_colors(color, 0x707070, ratio));
}

void	player_dash(t_game *game, t_entity *entity, t_player_ext *ext)
{
	t_afterimage	image;
	int				i;

	ext->afterimages[(getms() - ext->last_dash) / 16] = (t_afterimage){
		.disabled = 0,
		.position = (t_vec2){entity->x, entity->y}, .sprite = entity->sprite};
	i = 0;
	while (i < 10)
	{
		image = ext->afterimages[i];
		ext->afterimage_index = i;
		if (image.sprite)
			graph_add_sprite(game->graph, image.sprite, image.position, -1,
				(t_effect){(void *)afterimage_effect, entity});
		i++;
	}
}
