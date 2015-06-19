/*
** cbutils.c for  in /home/chambo_e/epitech/PSU_2014_zappy
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Apr  9 14:11:57 2015 Emmanuel Chambon
** Last update Fri Jun 19 16:18:06 2015 Emmanuel Chambon
*/

#include "zappy.h"

t_cmd_buffer		*cb_init()
{
  t_cmd_buffer		*buffer;

  if (!(buffer = malloc(sizeof(t_cmd_buffer))))
    error("malloc");
  buffer->index_r = 0;
  buffer->index_w = 0;
  buffer->slot = CB_SIZE;
  return (buffer);
}

void			cb_free(t_cmd_buffer *ring)
{
  if (ring)
    free(ring);
}

unsigned int		cb_available(t_cmd_buffer *ring)
{
  return (ring->slot);
}

void			cb_write(t_cmd_buffer *ring, char *str, bool dup)
{
  if (ring->slot == 0)
    return ;
  if (dup)
    {
      if (!(ring->data[ring->index_w] = strdup(str)))
	error("strdup");
    }
  else
    ring->data[ring->index_w] = str;
  ring->index_w = (ring->index_w + 1 == CB_SIZE)
    ? 0 : ring->index_w + 1;
  ring->slot--;
}

char			*cb_read(t_cmd_buffer *ring)
{
  char			*ret;

  if (ring->slot == CB_SIZE)
    return (NULL);
  if (!(ret = strdup(ring->data[ring->index_r])))
    error("strdup");
  free(ring->data[ring->index_r]);
  ring->index_r = (ring->index_r + 1 == CB_SIZE)
    ? 0 : ring->index_r + 1;
  ring->slot++;
  return (ret);
}
