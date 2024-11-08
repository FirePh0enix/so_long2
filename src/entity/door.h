/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:11:26 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:24:39 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# include "../entity.h"
# include "../render/light.h"

typedef struct s_game	t_game;

typedef struct s_door_ext
{
	t_anim	*anim;
	t_light	*light;
}	t_door_ext;

void	door_spawn(t_game *game, t_entity *entity, t_door_ext *ext);
void	door_update(t_game *game, t_entity *entity, t_door_ext *ext);

#endif
