/*
** zappy.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:35:49 2015 Emmanuel Chambon
** Last update Wed Jun 17 21:13:38 2015 Hugo Prenat
*/

#ifndef _ZAPPY_H_
# define _ZAPPY_H_

#include "misc.h"
#include "server.h"

bool	g_run;

typedef struct	s_team
{
  char		*name;
  int		slot;
}		t_team;

typedef struct	s_all
{
  int		max_clients;
  int		width;
  int		height;
  int		delay;
  char		*port;
  t_server	server;
  t_team	*teams;
  t_client	*clients;
}		t_all;

/*
**	zappy.c
*/
int		init_zappy(t_all *content, int ac, char **av);
void		release_zappy(t_all *);
int		check_param(int ac, char **av, t_all *content);

#endif /* !_ZAPPY_H_ */
