/*
** rbutils.c for  in /home/chambo_e/epitech/PSU_2014_zappy
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Apr  9 14:11:57 2015 Emmanuel Chambon
** Last update Wed Jun 17 09:55:49 2015 Emmanuel Chambon
*/

#include "zappy.h"

t_ring_buffer		*rb_init()
{
  t_ring_buffer		*buffer;

  if (!(buffer = malloc(sizeof(t_ring_buffer))))
    error("malloc");
  buffer->index_r = 0;
  buffer->index_w = 0;
  buffer->slot = RB_SIZE;
  return (buffer);
}

void			rb_free(t_ring_buffer *ring)
{
  if (ring)
    free(ring);
}

unsigned int		rb_available(t_ring_buffer *ring)
{
  return (ring->slot);
}

void			rb_write(t_ring_buffer *ring, char *str)
{
  if (ring->slot == 0)
    return ;
  if (!(ring->data[ring->index_w] = strdup(str)))
    error("strdup");
  ring->index_w = (ring->index_w + 1 == RB_SIZE)
    ? 0 : ring->index_w + 1;
  ring->slot--;
}

char			*rb_read(t_ring_buffer *ring)
{
  char			*ret;

  if (ring->slot == RB_SIZE)
    return (NULL);
  if (!(ret = strdup(ring->data[ring->index_r])))
    error("strdup");
  free(ring->data[ring->index_r]);
  ring->index_r = (ring->index_r + 1 == RB_SIZE)
    ? 0 : ring->index_r + 1;
  ring->slot++;
  return (ret);
}
