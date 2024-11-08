/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledelbec <ledelbec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:01:45 by ledelbec          #+#    #+#             */
/*   Updated: 2023/12/27 13:34:33 by ledelbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "libft.h"
#include "render.h"
#include <stdlib.h>

t_render_graph	*new_graph(void)
{
	t_render_graph	*graph;

	graph = malloc(sizeof(t_render_graph));
	graph->root = NULL;
	return (graph);
}

void	graph_reset(t_render_graph *graph)
{
	t_node	*cur_node;
	t_node	*next;

	cur_node = graph->root;
	while (cur_node)
	{
		next = cur_node->next;
		free(cur_node);
		cur_node = next;
	}
	graph->root = NULL;
}

static void	add_node(t_render_graph *graph, t_node *node)
{
	t_node	*cur_node;

	if (!graph->root || graph->root->order >= node->order)
	{
		node->next = graph->root;
		graph->root = node;
		return ;
	}
	cur_node = graph->root;
	while (cur_node->next && cur_node->next->order < node->order)
		cur_node = cur_node->next;
	node->next = cur_node->next;
	cur_node->next = node;
}

void	graph_add_sprite(
	t_render_graph *graph,
	t_sprite *sprite,
	t_vec2 pos,
	int order,
	t_effect effect)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = NODE_SPRITE;
	node->order = order;
	node->next = NULL;
	node->sprite.sprite = sprite;
	node->sprite.position = pos;
	node->effect = effect;
	add_node(graph, node);
}

void	graph_add_ui(
	t_render_graph *graph,
	t_sprite *sprite,
	t_vec2 pos,
	int order,
	t_effect effect)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = NODE_UI;
	node->order = order;
	node->next = NULL;
	node->effect = effect;
	node->sprite.sprite = sprite;
	node->sprite.position = pos;
	add_node(graph, node);
}

void	graph_add_debug_box(t_render_graph *graph, t_box box, int color)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = NODE_DEBUG_BOX;
	node->order = 100;
	node->next = NULL;
	node->debug_box.box = box;
	node->debug_box.color = color;
	node->effect.apply = NULL;
	add_node(graph, node);
}

void	graph_draw(t_render_graph *graph, t_game *game)
{
	t_node	*node;

	node = graph->root;
	while (node)
	{
		// FIXME: `flipped` should be located in entity
		if (node->type == NODE_SPRITE)
			draw_sprite(game, node->sprite.sprite,
				vec2i_from_vec2(node->sprite.position),
				(t_draw_opts){node->sprite.sprite->flipped, node->effect});
		else if (node->type == NODE_DEBUG_BOX)
			draw_debug_box(game, &node->debug_box.box, node->debug_box.color);
		else if (node->type == NODE_UI)
			draw_ui(game, node->ui.sprite, node->ui.position, node->effect);
		node = node->next;
	}
}
