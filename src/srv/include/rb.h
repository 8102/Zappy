/*
** rb.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Wed Jun 17 09:51:15 2015 Emmanuel Chambon
** Last update Wed Jun 17 09:55:42 2015 Emmanuel Chambon
*/

#ifndef _RB_H_
# define _RB_H_

# define        RB_SIZE         10

typedef struct  s_ring_buffer   t_ring_buffer;

struct          s_ring_buffer
{
  char          *data[RB_SIZE];
  unsigned int  index_r;
  unsigned int  index_w;
  unsigned int  slot;
};

/*
**	rbinit.c
*/
t_ring_buffer	*rb_init();
void		rb_free(t_ring_buffer *);
unsigned int	rb_available(t_ring_buffer *);
void		rb_write(t_ring_buffer *, char *);
char		*rb_read(t_ring_buffer *);

#endif /* !_RB_H_ */
