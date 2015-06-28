/*
** client.h for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Sat Jun 27 20:42:45 2015 TommyStarK
** Last update Sun Jun 28 00:17:41 2015 TommyStarK
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

# include <errno.h>
# include <stdio.h>
# include <netdb.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <signal.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>

# define BUFF_SIZE 		512
# define LOCALHOST		"127.0.0.1"
# define USAGE			"[USAGE] ./client -m teamName -p port -h machine (set by default to localhost)."
# define ERR_CONNECT		"00PS: Cannot connect specified IP/PORT."
# define BYEBYE			"You have been disconnected from specified server. Goodbye :)"

typedef struct addrinfo		addinf;
typedef struct sockaddr_storage	stor;

typedef struct			s_socket
{
  int				fd;
  stor				addr;
  socklen_t			len;
}				t_socket;

typedef struct			s_client
{
  int				status;
  int				*fdmax;
  char 				*team;
  char 				*machine;
  fd_set			*rfds;
  t_socket			*client;
}				t_client;

/*
** client.c
*/
t_socket			*init_client(t_client *, char **);
void 				run_client(t_client *);
int 				make_coffe(t_client *);
void 				disconnect(t_client *);

/*
** network.c
*/
void				*ipvx(struct sockaddr *);
int				co_serv(t_socket *, const char *, const char *);

/*
** utils.c
*/
void				error(char *);
void				snd(char *, int *, int);
void 				ssend(int, char *);

#endif /* end of include guard: _CLIENT_H_ */
