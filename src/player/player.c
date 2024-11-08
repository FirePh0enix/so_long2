/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 20:48:50 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/26 22:44:13 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "../entity/projectile.h"
#include "../physics/physics.h"
#include "../so_long.h"
#include <stdio.h>
#include <stdlib.h>

void	player_spawn(t_game *game, t_entity *entity, t_player_ext *ext)
{
	entity->health = 1000;
	entity->max_health = 1000;
	entity->state = 1;
	entity->velocity = (t_vec2){0, 0};
	entity->hitbox = (t_box){{0, 0},
	{16 * PIXEL_SCALE, 28 * PIXEL_SCALE}};
	ext->light = malloc(sizeof(t_light));
	ext->light->range = 90;
	ext->light->intensity = 1.0;
	ext->light->x = entity->x + entity->type->sprite->width / 2;
	ext->light->y = entity->y;
	ext->light->color = 0xffff99;
	ext->light->disabled = 0;
	ext->already_jump = 0;
	ext->already_dash = 0;
	ext->dash_end = 0;
	ext->cooldown_q = 300;
	ext->cooldown_w = 1000;
	ext->dash_cooldown = 400;
	ext->last_dash = 0;
	ext->afterimage_index = 0;
	ft_bzero(ext->afterimages, sizeof(t_afterimage) * 10);
}

static void	player_movement(t_game *game, t_entity *entity, t_player_ext *ext)
{
	float	vel_x;

	vel_x = 0;
	if (game->key_right)
	{
		vel_x = PLAYER_SPEED;
		entity->sprite->flipped = 0;
	}
	if (game->key_left)
	{
		vel_x = -PLAYER_SPEED;
		entity->sprite->flipped = 1;
	}
	if (game->key_up && physx_is_on_ground(entity) && !ext->already_jump)
	{
		entity->velocity.y -= JUMP_FORCE;
		ext->already_jump = 1;
	}
	else if (!game->key_up)
		ext->already_jump = 0;
	if (game->key_space && !ext->already_dash
		&& getms() - ext->last_dash > ext->dash_cooldown)
	{
		ext->last_dash = getms();
		ext->already_dash = 1;
		ext->dash_end = getms() + 16 * 10;
	}
	else if (!game->key_space)
		ext->already_dash = 0;
	if (getms() < ext->dash_end)
	{
		if (entity->velocity.y > 0)
			entity->velocity.y = 0;
		player_dash(game, entity, ext);
		if (entity->sprite->flipped)
			vel_x = -DASH_FORCE;
		else
			vel_x = DASH_FORCE;
	}
	else
	{
		ft_bzero(ext->afterimages, sizeof(t_afterimage) * 10);
	}
	entity->velocity.x += vel_x;
}

static void	cast_wall_spell(t_game *game, t_entity *entity, t_player_ext *ext)
{
	t_entity	*wall;

	wall = new_entity(game, 0, entity->y, game->wall_type);
	if (entity->sprite->flipped)
		wall->x = entity->x + 16 * 3 * PIXEL_SCALE * -1;
	else
		wall->x = entity->x + 16 * 3 * PIXEL_SCALE;
	if (!physx_is_on_ground(wall)
		|| physx_collide_with_terrain(box_from_entity(wall), game->map))
	{
		free(wall);
		return ;
	}
	add_entity(game, wall);
}

static void	cast_spell(t_game *game, t_entity *entity, t_player_ext *ext)
{
	long		time;
	t_entity	*spell;

	time = getms();
	if (game->key_q && time - ext->last_q > ext->cooldown_q)
	{
		ext->last_q = time;
		spell = new_entity(game, entity->x,
				entity->y - 10, game->projectile_type);
		((t_projectile_ext *)spell->extension)->mask = MASK_ENEMY;
		((t_projectile_ext *)spell->extension)->damage = 5;
		if (entity->sprite->flipped)
			((t_projectile_ext *)spell->extension)->direction.x = -1;
		else
			((t_projectile_ext *)spell->extension)->direction.x = 1;
		add_entity(game, spell);
	}
	else if (game->key_w && time - ext->last_w > ext->cooldown_w)
	{
		ext->last_w = time;
		cast_wall_spell(game, entity, ext);
	}
}

void	player_update(t_game *game, t_entity *entity, t_player_ext *ext)
{
	if (!physx_is_on_ground(entity))
		entity->velocity.y += 1.2;
	player_movement(game, entity, ext);
	physx_move_entity(entity);
	ext->light->x = entity->x + entity->type->sprite->width / 2;
	ext->light->y = entity->y;
	game->camera_x = entity->x;
	game->camera_y = entity->y;
	entity->velocity.x = 0;
	cast_spell(game, entity, ext);
	entity->health -= 1;
}
