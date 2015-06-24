/*
** server.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:27:54 2015 Emmanuel Chambon
** Last update Fri Jun 19 16:57:35 2015 Emmanuel Chambon
*/

#ifndef _SERVER_H_
# define _SERVER_H_

#include "misc.h"
#include "network.h"

typedef struct	s_server	t_server;

# define	MAX_CMD		22 + 1
# define	BACKLOG		5
# define	RECV_SIZE	4096

struct		s_server
{
  char		*port;
  int		socket;
  fd_set	master;
  char		*cmd[MAX_CMD];
  void		(*cmd_handler[MAX_CMD])(char *,
					t_client *,
					t_master *);
};

/*
**      socketutils.c
*/
void		ssend(int, char *, ...);
void		*ipvx(struct sockaddr *);
int		bind_local(struct addrinfo *, int *);
int		bind_port(char *);
/*
**      server_init.c
*/
void		set_handler(t_server *);
/*
**      server_idle.c
*/
void		handle_new_connection(int *, t_master *);
void		watch_sockets(int *, int *, fd_set *, t_master *);
void		idle_server(t_master *);
/*
**	server.c
*/
void		close_handler(int);
void		release_server(t_server *);
void		set_server(t_server *, char *);
void		init_server(t_server *, char *);
/*
**	check_params.c
*/
char		*default_check(char *);
char		*check_params(char *);
/*
**	commands.c
*/
void		avance(char *, t_client *, t_master *);
void		droite(char *, t_client *, t_master *);
void		gauche(char *, t_client *, t_master *);
void		voir(char *, t_client *, t_master *);
void		inventaire(char *, t_client *, t_master *);
void		prend(char *, t_client *, t_master *);
void		pose(char *, t_client *, t_master *);
void		expulse(char *, t_client *, t_master *);
void		broadcast(char *, t_client *, t_master *);
void		incantation(char *, t_client *, t_master *);
void		_fork(char *, t_client *, t_master *);
void		connect_nbr(char *, t_client *, t_master *);
void		msz(char *, t_client *, t_master *);
void		bct(char *, t_client *, t_master *);
void		mct(char *, t_client *, t_master *);
void		tna(char *, t_client *, t_master *);
void		ppo(char *, t_client *, t_master *);
void		plv(char *, t_client *, t_master *);
void		pin(char *, t_client *, t_master *);
void		sgt(char *, t_client *, t_master *);
void		sst(char *, t_client *, t_master *);
/*
**	graphic.h
*/
void		graphic(char *, t_client *, t_master *);

#endif /* !_SERVER_H_ */
