/*
** client.h for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Sat Jun 27 20:42:45 2015 TommyStarK
** Last update Sat Jul  4 22:30:11 2015 Emmanuel Chambon
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

# include <time.h>
# include <errno.h>
# include <stdio.h>
# include <netdb.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <signal.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>

# define BUFF_SIZE 		512
# define LOCALHOST		"127.0.0.1"
# define USAGE			"[USAGE] ./client -n teamName -p port -h machine (set by default to localhost)."
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
  int				size;
  int				status;
  int				*fdmax;
  char 				*team;
  char                          **ia;
  fd_set			*rfds;
  t_socket			*client;
}				t_client;

/*
** init.c
*/
t_socket			*init_client(t_client *, char **);
char				**init_ia();
void				init_time_handler();

/*
** client.c
*/
void				ia(t_client *);
void 				run_client(t_client *);
int 				make_coffe(t_client *);

/*
** network.c
*/
void				*ipvx(struct sockaddr *);
int				co_serv(t_socket *, const char *, const char *);
void 				disconnect(t_client *);

/*
** utils.c
*/
void				error(char *);
void				snd(char *, int *, int);
void 				ssend(int, char *);
int				get_array_size(char **);

#endif /* end of include guard: _CLIENT_H_ */
