/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:42:27 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:33:10 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

t_vec2	vec2_add(t_vec2 l, t_vec2 r);
t_vec2	vec2_sub(t_vec2 l, t_vec2 r);
t_vec2	vec2_scale(t_vec2 vec, float scale);
float	vec2_length(t_vec2 vec);
t_vec2	vec2_normalize(t_vec2 vec);
int		vec2_is_zero(t_vec2 vec);

typedef struct s_vec2i
{
	int	x;
	int	y;
}	t_vec2i;

t_vec2i vec2i_from_vec2(t_vec2 v);

#endif
