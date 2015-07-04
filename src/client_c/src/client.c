/*
** client.c for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Sat Jun 27 20:40:47 2015 TommyStarK
** Last update Sat Jul  4 21:01:00 2015 TommyStarK
*/

#include "client.h"

void		ia(t_client *it)
{
  int 		random;

  usleep(rand() % 1000 + 400000);
  if (it->size > 0)
  {
    random = rand() % it->size;
    ssend(it->client->fd, it->ia[random]);
  }
}

int             make_coffe(t_client *it)
{
  int           ret;
  char          tmp[BUFF_SIZE] = {0};
  static int 	flag = 0;

  ret = 1;
  memset(tmp, 0, BUFF_SIZE);
  if (!flag)
  {
    ret = recv(it->client->fd, tmp, BUFF_SIZE, 0);
    ssend(it->client->fd, it->team);
    !ret ? printf("00PS: connection closed by server.\n")
    : ret > 0 ? printf("%s\n", tmp) : 0;
    flag = 1;
  }
  else
  {
    ret = recv(it->client->fd, tmp, BUFF_SIZE, 0);
    if (ret >= 0)
      printf("%s\n", tmp);
  }
  return (!ret ? 0 : ret > 0 ? 1 : -1);
}

void            run_client(t_client *it)
{
  int          i;
  int          ret;
  int          fdmax;
  fd_set       read_fds;
  struct timeval	t;

  t.tv_usec = 500;
  fdmax = it->client->fd + 1;
  FD_ZERO(&read_fds);
  it->fdmax = &fdmax;
  it->rfds = &read_fds;
  while (42)
  {
    FD_ZERO(it->rfds);
    FD_SET(it->client->fd, it->rfds);
    if (select(fdmax, it->rfds, NULL, NULL, &t) == -1)
      error("select");
    for (i = 0; i < *it->fdmax; i++)
    {
      if (FD_ISSET(i, &read_fds))
	(ret = make_coffe(it)) < 0 ? disconnect(it) : 0;
    }
    ia(it);
  }
}

int 		main(int ac, char **av)
{
  t_client 	this;

  if (ac < 5)
    return (fprintf(stderr, "%s\n", USAGE));
  this.client = init_client(&this, av);
  this.client->fd = -1;
  this.status = co_serv(this.client, ac == 7 ? av[6] : LOCALHOST, av[4]);
  init_time_handler();
  if (!this.status)
  {
    fprintf(stderr, "%s\n", ERR_CONNECT);
    return (EXIT_FAILURE);
  }
  printf("(.)(.) Connection succeed: you are connected @ %s:%s\n",
	 ac == 7 ? av[6] : LOCALHOST, av[4]);
  run_client(&this);
  return (EXIT_SUCCESS);
}
