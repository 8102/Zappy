/*
** rbutils.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Fri Jun 19 14:38:22 2015 Emmanuel Chambon
** Last update Fri Jun 19 17:01:51 2015 Emmanuel Chambon
*/

#include "zappy.h"

char			rb_at(t_ring_buffer *ring, int idx)
{
  return ((idx >= 0)
	  ? (ring->rb[(((size_t)ring->rrb + idx)
				 - (size_t)ring->rb) % RB_SIZE])
	  : (ring->rb[(((size_t)ring->wrb + idx)
		       - (size_t)ring->rb) % RB_SIZE]));
}

void			rb_set_at(t_ring_buffer *ring, int idx, char c)
{
  ((idx >= 0)
   ? (ring->rb[(((size_t)ring->rrb + idx)
		- (size_t)ring->rb) % RB_SIZE] = c)
   : (ring->rb[(((size_t)ring->wrb + idx)
		- (size_t)ring->rb) % RB_SIZE] = c));
}

void			rb_delete_last(t_ring_buffer *ring)
{
  ring->wrb = (ring->wrb == ring->rrb)
    ? ring->wrb
    : &ring->rb[(((size_t)ring->wrb - 1)
		 - (size_t)ring->rb) % RB_SIZE];
}

void			rb_write_c(t_ring_buffer *ring, char c)
{
  ring->wrb = (ring->wrb) ? ring->wrb : ring->rb;
  *ring->wrb = c;
  ring->wrb = &ring->rb[(((size_t)ring->wrb + 1)
			 - (size_t)ring->rb) % RB_SIZE];
}

void			rb_reset(t_ring_buffer *ring)
{
  ring->rrb = ring->wrb;
}
