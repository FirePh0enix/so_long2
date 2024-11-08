/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:01:56 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:20:15 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "../entity.h"
# include "../render/graph.h"
# include "../render/light.h"

# define PLAYER_SPEED 8
# define JUMP_FORCE 20
# define DASH_FORCE 15

typedef struct s_game	t_game;

typedef struct s_afterimage
{
	t_vec2		position;
	int			disabled;
	t_sprite	*sprite;
}	t_afterimage;

typedef struct s_player_ext
{
	t_light			*light;
	int				already_jump;

	long			cooldown_q;
	long			last_q;
	long			cooldown_w;
	long			last_w;

	int				already_dash;
	long			dash_end;
	long			dash_cooldown;
	long			last_dash;
	t_afterimage	afterimages[10];
	int				afterimage_index;
}	t_player_ext;

void	player_spawn(t_game *game, t_entity *entity, t_player_ext *ext);
void	player_update(t_game *game, t_entity *entity, t_player_ext *ext);

void	player_dash(t_game *game, t_entity *entity, t_player_ext *ext);

#endif
