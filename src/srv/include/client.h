/*
** zappy.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:35:49 2015 Emmanuel Chambon
** Last update Fri Jun 19 17:01:14 2015 Emmanuel Chambon
*/

#pragma once
#ifndef _CLIENT_H_
# define _CLIENT_H_

enum            Orientation {
  NORTH,
  EAST,
  SOUTH,
  WEST
};

struct          s_client
{
  int           socket;
  char          *ip;
  bool		auth;
  bool		graphic;
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

#endif /* !_CLIENT_H_ */
