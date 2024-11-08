/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:40:34 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:41:11 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_game t_game;

typedef struct s_sprite
{
	int		width;
	int		height;
	void	*img;
	int		flipped;
}	t_sprite;

typedef struct s_anim
{
	int			frames;
	int			current;
	t_sprite	**sprites;
	int			loop;
	long		frame_time;
	long		last_frame;
}	t_anim;

t_sprite	*new_sprite(t_game *game, char *file);

t_anim		*new_anim(int frames, t_sprite *sprites[], int loop, long frame_time);
void		anim_step(t_anim *anim);

typedef struct s_img t_img;

int			get_pixel_color(t_img *image, int x, int y);
void		set_pixel_color(t_img *image, int x, int y, int color);

#endif
