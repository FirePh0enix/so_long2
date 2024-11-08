/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 20:49:00 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 21:53:04 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "sprite.h"
#include <stdlib.h>

t_anim	*new_anim(int frames, t_sprite *sprites[], int loop, long frame_time)
{
	t_anim	*anim;
	int		i;

	anim = malloc(sizeof(t_anim));
	anim->frames = frames;
	anim->current = 0;
	anim->sprites = malloc(frames * sizeof(t_sprite *));
	anim->loop = loop;
	anim->last_frame = 0;
	anim->frame_time = frame_time;
	i = 0;
	while (i < frames)
	{
		anim->sprites[i] = sprites[i];
		i++;
	}
	return (anim);
}

void	anim_step(t_anim *anim)
{
	long	time;

	if (anim->current == anim->frames - 1 && !anim->loop)
		return ;
	time = getms();
	if (time - anim->last_frame < anim->frame_time)
		return ;
	anim->last_frame = time;
	anim->current++;
	if (anim->current == anim->frames)
		anim->current = 0;
}
