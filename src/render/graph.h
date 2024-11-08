#ifndef GRAPH_H
#define GRAPH_H

#include "../physics/box.h"
#include "../sprite.h"

enum
{
	NODE_SPRITE,
	NODE_DEBUG_BOX,
	NODE_UI,
	NODE_PARTICLES,
};

typedef struct s_effect
{
	int	  (*apply)(int, int, int, void *);
	void *user_data;
} t_effect;

typedef struct s_node
{
	struct s_node *next;
	int			   type;
	int			   order;
	union
	{
		struct
		{
			t_sprite *sprite;
			t_vec2	  position;
		} sprite;
		struct
		{
			t_sprite *sprite;
			t_vec2	  position;
		} ui;
		struct
		{
			t_box box;
			int	  color;
		} debug_box;
	};
	t_effect effect;
} t_node;

typedef struct s_render_graph
{
	t_node *root;
} t_render_graph;

t_render_graph *new_graph();
void			graph_reset(t_render_graph *graph);

void graph_add_sprite(t_render_graph *graph, t_sprite *sprite, t_vec2 pos,
					  int order, t_effect effect);
void graph_add_ui(t_render_graph *graph, t_sprite *sprite, t_vec2 pos,
				  int order, t_effect effect);
void graph_add_debug_box(t_render_graph *graph, t_box box, int color);

void graph_draw(t_render_graph *graph, t_game *game);

#endif
