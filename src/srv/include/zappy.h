/*
** zappy.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:35:49 2015 Emmanuel Chambon
** Last update Thu Jun 18 18:09:00 2015 Hugo Prenat
*/

#ifndef _ZAPPY_H_
# define _ZAPPY_H_

typedef struct	s_client	t_client;
typedef struct	s_team		t_team;
typedef struct	s_case		t_case;
typedef struct	s_all		t_all;
typedef enum	Orientation	e_Orientation;

# include "misc.h"
# include "server.h"
# include "rb.h"
# include "client.h"

bool		g_run;

enum		Orientation {
  NORTH,
  WEST,
  SOUTH,
  EAST
};

struct		s_client
{
  int		socket;
  size_t	x;
  size_t	y;
  char		*ip;
  t_ring_buffer	*buffer;
  e_Orientation	orient;
  t_client	*prev;
  t_client	*next;
};

struct		s_case
{
  size_t	x;
  size_t	y;
  t_case	*prev;
  t_case	*next;
}

struct		s_team
{
  char		*name;
  int		slot;
  t_team	*next;
};

struct		s_master
{
  int		max_clients;
  int		width;
  int		height;
  int		delay;
  char		*port;
  t_server	server;
  t_team	*teams;
  t_client	*clients;
};

/*
**	zappy.c
*/
int		init_zappy(t_master *, int, char **);
void		release_zappy(t_master *);
int		check_param(int, char **, t_master *);

#endif /* !_ZAPPY_H_ */
