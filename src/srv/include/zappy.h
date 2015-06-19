/*
** zappy.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:35:49 2015 Emmanuel Chambon
** Last update Fri Jun 19 16:57:56 2015 Emmanuel Chambon
*/

#ifndef _ZAPPY_H_
# define _ZAPPY_H_

typedef struct  s_client        t_client;
typedef struct  s_team		t_team;
typedef struct  s_master	t_master;
typedef struct	s_case		t_case;
typedef enum    Orientation     e_Orientation;

# include "misc.h"
# include "server.h"
# include "rb.h"
# include "client.h"

bool            g_run;

struct		s_case
{
  size_t	x;
  size_t	y;
  int		meal;
  int		linemate;
  int		deraumere;
  int		sibur;
  int		mendiane;
  int		phiras;
  int		thystame;
  t_case	*prev;
  t_case	*next;
};

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
  t_case	*cases;
};

/*
**	zappy.c
*/
int		init_zappy(t_master *, int, char **);
void		release_zappy(t_master *);
int		check_param(int, char **, t_master *);
int		create_map(t_master *content);

#endif /* !_ZAPPY_H_ */
