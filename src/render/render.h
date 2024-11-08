/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:37:07 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:34:11 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "graph.h"
# include "../sprite.h"
# include <mlx.h>
# include <mlx_int.h>

typedef struct s_game	t_game;
typedef struct s_sprite t_sprite;
typedef struct s_entity t_entity;
typedef struct s_box	t_box;

typedef struct s_draw_opts
{
	int			flipped;
	t_effect	effect;
}	t_draw_opts;

t_vec2			camera_offset(t_game *game);

void			draw_sprite(t_game *game, t_sprite *sprite, t_vec2i pos, t_draw_opts ops);
void			draw_ui(t_game *game, t_sprite *sprite, t_vec2 pos, t_effect effect);
void			draw_debug_box(t_game *game, t_box *box, int color);

/*
  Draw the backbuffer to the screen.
*/
void			present(t_game *game);
void			clear_screen(t_game *game);

/*
  Calculate the light level for each pixels of the window.
*/
void			apply_lighting(t_game *game);

unsigned int	blend_colors(unsigned int a, unsigned int b, float ratio);

#endif
