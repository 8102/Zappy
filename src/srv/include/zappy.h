/*
** zappy.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:35:49 2015 Emmanuel Chambon
** Last update Thu Jun 18 01:57:08 2015 Emmanuel Chambon
*/

#ifndef _ZAPPY_H_
# define _ZAPPY_H_

typedef struct  s_client        t_client;
typedef struct  s_team		t_team;
typedef struct  s_all           t_all;
typedef enum    Orientation     e_Orientation;

# include "misc.h"
# include "server.h"
# include "rb.h"

bool            g_run;

enum            Orientation {
  NORTH,
  WEST,
  SOUTH,
  EAST
};

struct          s_client
{
  int           socket;
  char          *ip;
  t_ring_buffer *buffer;
  e_Orientation orient;
  t_client      *prev;
  t_client      *next;
};

struct		s_team
{
  char		*name;
  int		slot;
  t_team	*next;
};

struct		s_all
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
int		init_zappy(t_all *content, int ac, char **av);
void		release_zappy(t_all *);
int		check_param(int ac, char **av, t_all *content);
/*
**	client.c
*/
void		push_client(t_client **, t_client *);
void		pop_client(t_client **, t_client *);
void		handle_new_connection(int *, t_all *);
t_client	*get_client(int, t_all *);
void		remove_connection(t_client *, t_all *);
#endif /* !_ZAPPY_H_ */
