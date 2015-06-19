/*
** rb.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Wed Jun 17 09:51:15 2015 Emmanuel Chambon
** Last update Fri Jun 19 16:55:16 2015 Emmanuel Chambon
*/

#pragma once
#ifndef _RB_H_
# define _RB_H_

# define        CB_SIZE			10
# define        RB_SIZE			4096

typedef struct  s_cmd_buffer		t_cmd_buffer;
typedef struct  s_ring_buffer		t_ring_buffer;

struct          s_cmd_buffer
{
  char          *data[RB_SIZE];
  unsigned int  index_r;
  unsigned int  index_w;
  unsigned int  slot;
};

struct		s_ring_buffer
{
  char		rb[RB_SIZE];
  char		*rrb;
  char		*wrb;
};

/*
**	cbinit.c
*/
t_cmd_buffer	*cb_init();
void		cb_free(t_cmd_buffer *);
unsigned int	cb_available(t_cmd_buffer *);
void		cb_write(t_cmd_buffer *, char *, bool);
char		*cb_read(t_cmd_buffer *);
/*
**	rbinit.c
*/
t_ring_buffer	*rb_init();
void		rb_free(t_ring_buffer *);
unsigned int	rb_available(t_ring_buffer *);
void		rb_write(t_ring_buffer *, char *);
char		*rb_read(t_ring_buffer *);
/*
**
*/
char		rb_at(t_ring_buffer *, int);
void		rb_set_at(t_ring_buffer *, int idx, char);
void		rb_delete_last(t_ring_buffer *);
void		rb_write_c(t_ring_buffer *, char c);
void		rb_reset(t_ring_buffer *);

#endif /* !_RB_H_ */
