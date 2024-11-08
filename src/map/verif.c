/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:20:30 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:50:17 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	verify_boundaries(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map_get_tile(map, i, 0)->type != GROUND
			|| map_get_tile(map, i, map->height - 1)->type != GROUND)
			return (0);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map_get_tile(map, 0, i)->type != GROUND
			|| map_get_tile(map, map->width - 1, i)->type != GROUND)
			return (0);
		i++;
	}
	return (1);
}

int	map_verify(t_game *game, t_map *map)
{
	return (verify_boundaries(map) && game->player_start_present
		&& game->exit_present && game->total_collectibles > 0);
}
