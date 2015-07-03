/*
** rbinit.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Fri Jun 19 14:38:38 2015 Emmanuel Chambon
** Last update Fri Jul  3 03:30:47 2015 Emmanuel Chambon
*/

#include "zappy.h"

t_ring_buffer		*rb_init()
{
  t_ring_buffer		*buffer;

  if (!(buffer = malloc(sizeof(t_ring_buffer))))
    error("malloc");
  memset(buffer->rb, 0, RB_SIZE);
  buffer->rrb = buffer->rb;
  buffer->wrb = buffer->rb;
  return (buffer);
}

void			rb_free(t_ring_buffer *ring)
{
  if (ring)
    free(ring);
}

unsigned int		rb_available(t_ring_buffer *ring)
{
  return ((ring->wrb >= ring->rrb)
	  ? (RB_SIZE - (int)(ring->wrb - ring->rrb))
	  : (int)(ring->rrb - ring->wrb));
}

void			rb_write(t_ring_buffer *ring, char *str)
{
  ring->wrb = (ring->wrb) ? ring->wrb : ring->rb;
  for (int i = 0; str[i]; i++)
    {
      *ring->wrb = str[i];
      ring->wrb = &ring->rb[(((size_t)ring->wrb + 1)
			     - (size_t)ring->rb) % RB_SIZE];
    }
}

char			*rb_read(t_ring_buffer *ring)
{
  char			*str;
  int			size;

  size = ((ring->wrb >= ring->rrb)
	  ? (int)(ring->wrb - ring->rrb)
	  : (RB_SIZE - (int)(ring->rrb - ring->wrb)));
  if (!(str = malloc(size + 1)))
    error("malloc");
  memset(str, 0, size + 1);
  for (int i = 0; i < size; i++)
    {
      str[i] = *ring->rrb;
      ring->rrb = &ring->rb[(((size_t)ring->rrb + 1)
			     - (size_t)ring->rb) % RB_SIZE];
    }
  return (str);
}
