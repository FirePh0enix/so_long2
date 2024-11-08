#!/bin/bash

new-tile()
{
  TILE_SIZE=16
  X=$(($3*$TILE_SIZE))
  Y=$(($4*$TILE_SIZE))
  convert -crop ${TILE_SIZE}x${TILE_SIZE}+$X+$Y $1 $2
}

new-wide-tile()
{
  TILE_SIZE=16
  X=$(($3*$TILE_SIZE))
  Y=$(($4*$TILE_SIZE))
  convert -crop 16x32+$X+$Y $1 $2
}

NAME="textures/so_long_sheet.png"

mkdir -p textures/gen

#
# Ground tiles
#
new-tile $NAME "textures/gen/mid.png" 1 1

new-tile $NAME "textures/gen/lt_side.png" 0 0
new-tile $NAME "textures/gen/lb_side.png" 0 2
new-tile $NAME "textures/gen/rt_side.png" 2 0
new-tile $NAME "textures/gen/rb_side.png" 2 2

new-tile $NAME "textures/gen/top.png" 1 0
new-tile $NAME "textures/gen/bottom.png" 1 2
new-tile $NAME "textures/gen/left.png" 0 1
new-tile $NAME "textures/gen/right.png" 2 1

new-tile $NAME "textures/gen/rb_corner.png" 3 0
new-tile $NAME "textures/gen/lb_corner.png" 5 0
new-tile $NAME "textures/gen/rt_corner.png" 3 2
new-tile $NAME "textures/gen/lt_corner.png" 5 2

new-tile $NAME "textures/gen/all_corners.png" 6 0
new-tile $NAME "textures/gen/all_sides.png" 7 0

new-tile $NAME "textures/gen/ltb_side.png" 6 2
new-tile $NAME "textures/gen/tb_side.png" 7 2
new-tile $NAME "textures/gen/rtb_side.png" 8 2

new-tile $NAME "textures/gen/lrt_side.png" 9 0
new-tile $NAME "textures/gen/lr_side.png" 9 1
new-tile $NAME "textures/gen/lrb_side.png" 9 2

new-tile $NAME "textures/gen/lrt_cor_b_side.png" 7 4
new-tile $NAME "textures/gen/lrb_cor_t_side.png" 9 4
new-tile $NAME "textures/gen/rtb_cor_l_side.png" 11 4
new-tile $NAME "textures/gen/ltb_cor_r_side.png" 13 4

new-tile $NAME "textures/gen/rb_cor_lt_side.png" 11 0
new-tile $NAME "textures/gen/lb_cor_rt_side.png" 12 0
new-tile $NAME "textures/gen/rt_cor_lb_side.png" 11 1
new-tile $NAME "textures/gen/lt_cor_rb_side.png" 12 1

new-tile $NAME "textures/gen/lrt_corner.png" 7 6
new-tile $NAME "textures/gen/lrb_corner.png" 9 6
new-tile $NAME "textures/gen/rtb_corner.png" 11 6
new-tile $NAME "textures/gen/ltb_corner.png" 13 6

new-tile $NAME "textures/gen/lt_cor_b_side.png" 7 8
new-tile $NAME "textures/gen/lb_cor_t_side.png" 9 8
new-tile $NAME "textures/gen/rt_cor_l_side.png" 11 8
new-tile $NAME "textures/gen/lt_cor_r_side.png" 13 8

new-tile $NAME "textures/gen/rt_cor_b_side.png" 7 10
new-tile $NAME "textures/gen/rb_cor_t_side.png" 9 10
new-tile $NAME "textures/gen/rb_cor_l_side.png" 11 10
new-tile $NAME "textures/gen/lb_cor_r_side.png" 13 10

#
# Grass
#

new-tile $NAME "textures/gen/grass.png" 0 3
new-tile $NAME "textures/gen/red_flower.png" 1 3
new-tile $NAME "textures/gen/yellow_flower.png" 2 3

#
# Misc
#

new-wide-tile $NAME "textures/gen/glowing_tree.png" 0 4

