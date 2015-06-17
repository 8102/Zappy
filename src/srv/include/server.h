/*
** server.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:27:54 2015 Emmanuel Chambon
** Last update Tue Jun 16 12:12:03 2015 Emmanuel Chambon
*/

#ifndef _SERVER_H_
# define _SERVER_H_

#include "misc.h"
#include "network.h"

typedef struct s_server         t_server;

# define MAX_CMD		10
# define BACKLOG		5

struct                          s_server
{
  char                          *port;
  int                           socket;
  fd_set                        master;
  char                          *cmd[MAX_CMD];
  void                          (*cmd_handler[MAX_CMD])(bool (*)(char *),
							char *, int,
							t_server *);
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
void                    handle_new_connection(int *, t_server *);
void                    watch_sockets(int *, int *, fd_set *, t_server *);
void                    idle_server(t_server *);
/*
**	server.c
*/
void			close_handler(int);
void			release_server(t_server *);
void			set_server(t_server *, char *);
void			init_server(t_server *, char *);

#endif /* !_SERVER_H_ */
