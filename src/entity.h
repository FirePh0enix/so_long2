/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:45:18 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 21:45:42 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include "physics/box.h"
# include "physics/physics.h"
# include "physics/vec2.h"
# include "sprite.h"

typedef void (*t_spawn)(t_game *game, void *entity, void *ext);
typedef void (*t_update)(t_game *game, void *entity, void *ext);
typedef void (*t_mouse_event)(t_game *game, void *entity, void *ext,
							  int button);

typedef struct s_entity_type
{
	t_sprite		*sprite;
	int				extension_size;
	t_spawn			spawn_hook;
	t_update		update_hook;
	t_mouse_event	mouse_event_hook;
	int				render_order;
}	t_entity_type;

# define STATE_DEAD 0
# define STATE_ALIVE 1
# define STATE_PROP 2

# define MASK_ENEMY (1 << 0)
# define MASK_PLAYER (1 << 1)
# define MASK_SOLID (1 << 2)

# define GROUND_FRICTION 0.1
# define AIR_FRICTION 0.05

// Everything not in the tilemap like collectibles, enemies, etc...
//
// state - Can be dead (0), alive (1), prop (2)
typedef struct s_entity
{
	t_entity_type	*type;
	t_game			*game;
	t_sprite		*sprite;
	int				x;
	int				y;
	t_vec2			velocity;
	void			*extension;
	int				state;
	int				flipped;
	int				health;
	int				max_health;
	int				collision_mask;
	t_box			hitbox;

	int				blink_time;
	int				current_blink_time;
}	t_entity;

t_entity	*new_entity(t_game *game, int x, int y, t_entity_type *type);
t_vec2		entity_size(t_entity *entity);

int			entity_effect(int color, int x, int y, t_entity *entity);

#endif
