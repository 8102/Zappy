/*
** zappy.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:35:49 2015 Emmanuel Chambon
** Last update Wed Jun 24 13:33:44 2015 Emmanuel Chambon
*/

#ifndef _ZAPPY_H_
# define _ZAPPY_H_

typedef struct  s_client        t_client;
typedef struct  s_team		t_team;
typedef struct  s_master	t_master;
typedef struct	s_case		t_case;
typedef struct	s_egg		t_egg;
typedef enum    Orientation     e_Orientation;

# include "misc.h"
# include "server.h"
# include "rb.h"
# include "client.h"

bool            g_run;

struct		s_egg
{
  size_t	pos[2];
  size_t	nbr;
  int	id;
  t_egg		*next;
  t_egg		*prev;
};

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
  int		nbr_player;
  t_case	*prev;
  t_case	*next;
};

struct		s_team
{
  char		*name;
  int		slot;
  t_egg	*eggs;
  t_team	*next;
};

struct		s_master
{
  int		max_clients;
  int		width;
  int		height;
  int		delay;
  size_t	nbr_player;
  size_t	nbr_egg;
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
/*
**	pos.c
*/
void		set_pos(t_master *, t_client *, size_t , size_t);
/*
**	egg.c
*/
void		add_egg(t_team *team, t_master *content, size_t pos[2], int id);
void		pop_egg(t_egg **, t_egg *);
/*
**	voir.c
*/
t_case		*getCaseInMap(int, int, t_case *, t_master *);
char		*fillStringCase(t_case *, char *);
void	select_position_watch(t_client *client, t_master *all);

#endif /* !_ZAPPY_H_ */
