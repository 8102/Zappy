/*
** server.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:27:54 2015 Emmanuel Chambon
** Last update Fri Jul  3 05:51:39 2015 Emmanuel Chambon
*/

#ifndef _SERVER_H_
# define _SERVER_H_

#include "misc.h"
#include "network.h"

typedef struct	s_server	t_server;

# define	MAX_CMD		22 + 1
# define	BACKLOG		5
# define	RECV_SIZE	4096
# define	UNUSED		__attribute__((unused))
# define	AVANCE		0
# define	DROITE		1
# define	GAUCHE		2
# define	VOIR		3
# define	INVENTAIRE	4
# define	PREND		5
# define	POSE		6
# define	EXPULSE		7
# define	BROADCAST	8
# define	INCANTATION	9
# define	FORK		10

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
void		inventaire(char *, t_client *, t_master *);
void		broadcast(char *, t_client *, t_master *);
void		connect_nbr(char *, t_client *, t_master *);
void		tna(char *, t_client *, t_master *);
/*
**	fork.c
*/
void		_fork(char *, t_client *, t_master *);
/*
**	map_misc.c
*/
void		msz(char *, t_client *, t_master *);
void		bct(char *, t_client *, t_master *);
void		mct(char *, t_client *, t_master *);
void		prend(char *, t_client *, t_master *);
void		pose(char *, t_client *, t_master *);
/*
**	time.c
*/
void		sgt(char *, t_client *, t_master *);
void		sst(char *, t_client *, t_master *);
/*
**	graphic.c
*/
void		graphic(char *, t_client *, t_master *);
void		send_map(t_client *, t_master *);
/*
**	direction.c
*/
void		avance(char *, t_client *, t_master *);
void		droite(char *, t_client *, t_master *);
void		gauche(char *, t_client *, t_master *);
void		change_pos(t_master *, t_client *, e_Orientation);
/*
**	expulse.c
*/
void		expulse(char *, t_client *, t_master *);
/*
**	player_misc.c
*/
void		ppo(char *, t_client *, t_master *);
void		plv(char *, t_client *, t_master *);
void		pin(char *, t_client *, t_master *);
/*
**	voir.c
*/
void		voir(char *, t_client *, t_master *);
t_case		*getCaseInMap(t_client *, int, int, t_master *);
char		*fillStringCase(t_case *, char *);
char		*fillFirstTime();
t_case		*getNextCase(t_case *, t_master *, int);
/*
**	prend.c
*/
int	checkPossibleTake(t_case *, char *, t_client *);
void	prend_graphic(t_client *, t_master *, int);
char	*transformCoord(t_client *);
/*
**	pose.c
*/
int	checkPossibleSend(t_case *, char *, t_client *);
void	pose_graphic(t_client *, t_master *, int);
/*
**	broadcast.c
*/
float		calculateDistance(int, int, int, int);
void		translateMapUp(int *, int *, t_master *);
void		translateMapRight(int *, int *, t_master *);
int		checkBasicYAxis(t_client *, t_client *, t_master *);
int		multipleCases(t_client *, t_client *, t_master *);
int		calculateOrientation(int, int, int, int);
void		select_position_watch(t_client *client, t_master *all);
int		checkBasicCase(t_client *, t_client *, t_master *);
/*
**	incantation.c
*/
void	do_incantation(t_client *, t_master *);
int	check_stones(t_client *, t_case *, t_client *);
void	incantation(char *, t_client *, t_master *);
void	incantation_graphic(t_client *, t_master *, char *);

#endif /* !_SERVER_H_ */
