/*
** server.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:27:54 2015 Emmanuel Chambon
** Last update Wed Jun 17 22:05:20 2015 Emmanuel Chambon
*/

#ifndef _SERVER_H_
# define _SERVER_H_

#include "misc.h"
#include "network.h"

typedef struct s_server         t_server;

# define MAX_CMD		12 + 1
# define BACKLOG		5
# define RECV_SIZE		4096

struct                          s_server
{
  char                          *port;
  int                           socket;
  fd_set                        master;
  char                          *cmd[MAX_CMD];
  void                          (*cmd_handler[MAX_CMD])(bool (*)(char *),
							char *, t_client *,
							t_all *);
  void                          (*param_checker[MAX_CMD])(char *);
};

/*
**      socketutils.c
*/
void                    *ipvx(struct sockaddr *);
int                     bind_local(struct addrinfo *, int *);
int                     bind_port(char *);
/*
**      server_init.c
*/
void                    set_handler(t_server *);
/*
**      server_idle.c
*/
void                    handle_new_connection(int *, t_all *);
void                    watch_sockets(int *, int *, fd_set *, t_all *);
void                    idle_server(t_all *);
/*
**	server.c
*/
void			close_handler(int);
void			release_server(t_server *);
void			set_server(t_server *, char *);
void			init_server(t_server *, char *);
/*
**	commands.c
*/
void                    avance(bool (*)(char*), char *, t_client *, t_all *);
void                    droite(bool (*)(char*), char *, t_client *, t_all *);
void                    gauche(bool (*)(char*), char *, t_client *, t_all *);
void                    voir(bool (*)(char*), char *, t_client *, t_all *);
void                    inventaire(bool (*)(char*), char *, t_client *, t_all *);
void                    prend(bool (*)(char*), char *, t_client *, t_all *);
void                    pose(bool (*)(char*), char *, t_client *, t_all *);
void                    expulse(bool (*)(char*), char *, t_client *, t_all *);
void                    broadcast(bool (*)(char*), char *, t_client *, t_all *);
void                    incantation(bool (*)(char*), char *, t_client *, t_all *);
void                    _fork(bool (*)(char*), char *, t_client *, t_all *);
void                    connect_nbr(bool (*)(char*), char *, t_client *, t_all *);

#endif /* !_SERVER_H_ */
