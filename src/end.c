/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:01:54 by ledelbec          #+#    #+#             */
/*   Updated: 2024/02/26 13:21:38 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anim/anim.h"
#include "gui.h"
#include "mlx.h"
#include "render/render.h"
#include "so_long.h"
#include <stdlib.h>

static void	exit_click(t_game *game)
{
	mlx_loop_end(game->mlx);
}

void	init_end(t_game *game)
{
	int	i;

	i = -1;
	while (++i < EXPLOSION_COUNT)
		game->end.explosions[i].anim = anim_new(game->explosion, 9, 100, false);
	game->end.next_spawn = 0;
	game->end.exit = btn_new_label((t_vec2i){630, 240}, 3, "Quit", exit_click);
}

static void	_draw_time(t_game *game)
{
	suseconds_t	e;
	int			mins;
	int			secs;
	int			ms;

	e = game->end_time - game->start_time;
	ms = e % 1000;
	secs = (e - ms) % 60000;
	mins = (e - ms - secs);
	sprintf(game->buffer, "in %d'%d.%d", mins / 1000000, secs / 1000, ms);
	rdr_add_text(game->rdr, game->buffer, (t_vec2){
		text_center_x(game->small_font, game->buffer, 0, WIN_WIDTH), 150},
		(t_add_text){10, 5, game->small_font, 0x0});
	sprintf(game->buffer, "with %d moves", game->moves);
	rdr_add_text(game->rdr, game->buffer, (t_vec2){
		text_center_x(game->small_font, game->buffer, 0, WIN_WIDTH), 180},
		(t_add_text){10, 5, game->small_font, 0x0});
}

static bool	_set_explosion(t_game *game, int i)
{
	game->end.explosions[i].pos = (t_vec2){rand() % (WIN_WIDTH - 192),
		rand() % (WIN_HEIGHT - 192)};
	game->end.explosions[i].anim->current_frame = 0;
	if (!game->end.explosions[i].spawned)
	{
		game->end.explosions[i].spawned = true;
		game->end.next_spawn = getms() + 50;
		return (false);
	}
	return (true);
}

void	draw_end(t_game *game)
{
	int	i;

	i = -1;
	while (++i < EXPLOSION_COUNT)
	{
		rdr_add_sprite(game->rdr, anim_get_sprite(game->end.explosions[i].anim),
			game->end.explosions[i].pos, (t_add_sprite){10, 4, false});
		if ((!game->end.explosions[i].spawned
				|| game->end.explosions[i
				].anim->current_frame == game->end.explosions[i].anim->size - 1)
			&& game->end.next_spawn < getms())
		{
			if (!_set_explosion(game, i))
				break ;
		}
		anim_update(game->end.explosions[i].anim);
	}
	draw_banner_v(game, (t_vec2i){WIN_WIDTH / 2 - 224, 0}, (t_vec2i){7, 7});
	rdr_add_text(game->rdr, "You win !", (t_vec2){620, 100},
		(t_add_text){10, 5, game->font, 0x0});
	_draw_time(game);
	btn_update(game, &game->end.exit);
}