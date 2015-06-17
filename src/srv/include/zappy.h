/*
** zappy.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:35:49 2015 Emmanuel Chambon
** Last update Tue Jun 16 20:18:10 2015 Emmanuel Chambon
*/

#ifndef _ZAPPY_H_
# define _ZAPPY_H_

#include "misc.h"
#include "server.h"

bool	g_run;

typedef struct	s_all
{
  t_server	server;
}		t_all;

/*
**	zappy.c
*/
void		init_zappy(t_all *);
void		release_zappy(t_all *);

#endif /* !_ZAPPY_H_ */
