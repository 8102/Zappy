/*
** zappy.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:35:49 2015 Emmanuel Chambon
** Last update Wed Jun 24 13:32:24 2015 Emmanuel Chambon
*/

#pragma once
#ifndef _CLIENT_H_
# define _CLIENT_H_

# define	LINEMATE	0
# define	DERAUMERE	1
# define	SIBUR		2
# define	MENDIANE	3
# define	PHIRAS		4
# define	THYSTAME	5
# define	MEAL		6
# define	AUTH		0
# define	GRAPHIC		1
# define	X		0
# define	Y		1

enum		Orientation {
  NORTH = 1,
  EAST,
  SOUTH,
  WEST
};

struct          s_client
{
  size_t	pos[2];
  bool		trigger[2];
  int		resources[7];
  int		level;
  int		id;

  char          *ip;
  int           socket;
  t_cmd_buffer	*buffer;
  t_ring_buffer *recv;
  e_Orientation orient;
  t_team	*team;
  t_client      *prev;
  t_client      *next;
};

/*
**	client.c
*/
void		push_client(t_client **, t_client *);
void		pop_client(t_client **, t_client *);
void		delete_client(t_client *);
void		release_clients(t_client **);
void		init_client(t_client *, t_master *);
/*
**	client_handler.c
*/
void		handle_new_connection(int *, t_master *);
t_client	*get_client(int, t_client **);
void		remove_connection(t_client *, t_master *, int);
void		input_interpret(t_client *client, t_master *);
void		handle_io_connection(t_client *, t_master *);
/*
**	auth.c
*/
t_team		*find_team(char *, t_master *);
void		select_team(char *, t_client *, t_master *);
void		place_player(t_master *, t_client *, t_team *);

#endif /* !_CLIENT_H_ */
