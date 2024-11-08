/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:22:34 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:21:44 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

# include "box.h"

typedef struct s_entity	t_entity;
typedef struct s_map	t_map;

void		physx_move_entity(t_entity *entity);
int			physx_is_on_ground(t_entity *entity);
int			physx_collide_with_terrain(t_box box, t_map *map);
int			physx_box_collision(t_box a, t_box b);
t_entity	*physx_collide_with_entities(t_box box, t_map *map, int mask);

#endif
