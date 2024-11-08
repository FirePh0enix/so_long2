/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:43:09 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 21:43:23 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../so_long.h"

t_tile		*map_get_tile(t_map *map, int x, int y);
int			map_verify(t_game *game, t_map *map);

t_sprite	*map_get_ground_sprite(t_game *game, t_map *map, int x, int y);

#endif
