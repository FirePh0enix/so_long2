/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:29:25 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:30:12 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTILE_H
# define PROJECTILE_H

# include "../entity.h"
# include "../physics/physics.h"
# include "../render/light.h"

typedef struct s_projectile_ext
{
	t_vec2	direction;
	float	speed;
	t_light	*light;
	int		mask;
	int		damage;
	int		knockback;
}	t_projectile_ext;

void	projectile_spawn(t_game *game, t_entity *e, t_projectile_ext *ext);
void	projectile_update(t_game *game, t_entity *e, t_projectile_ext *ext);

#endif
