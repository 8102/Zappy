/*
** client.c for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Sat Jun 27 20:40:47 2015 TommyStarK
** Last update Sun Jul  5 21:08:09 2015 Emmanuel Chambon
*/

#include "client.h"

void			ia(t_client *it)
{
  int			random;

  usleep(rand() % 1000 + 400000);
  if (it->size > 0)
  {
    random = rand() % it->size;
    ssend(it->client->fd, it->ia[random]);
  }
}

int			make_coffe(t_client *it)
{
  int			ret;
  char			tmp[BUFF_SIZE] = {0};
  static int		flag = 0;

  ret = 1;
  memset(tmp, 0, BUFF_SIZE);
  if (!flag)
  {
    ret = recv(it->client->fd, tmp, BUFF_SIZE, 0);
    ssend(it->client->fd, "%s\n", it->team);
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

void			run_client(t_client *it)
{
  int			i;
  int			ret;
  int			fdmax;
  fd_set		read_fds;
  struct timeval	t;

  t.tv_sec = 0;
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

bool			check_params(int ac, char **av, t_client *this)
{
  int			opt;

  while ((opt = getopt(ac, av, "p:h:n:")) != -1) {
    if (opt == 'p')
      this->port = optarg;
    else if (opt == 'h')
      this->host = optarg;
    else if (opt == 'n')
      this->team = optarg;
    else
      return (false);
  }
  if (!this->team || !this->port)
    return (false);
  return (true);
}

int			main(int ac, char **av)
{
  t_client		this;

  srand(time(NULL));
  this.client = init_client(&this);
  this.client->fd = -1;
  if (!check_params(ac, av, &this))
    return (fprintf(stderr, "%s\n", USAGE));
  if (!(this.status = co_serv(this.client, this.host, this.port)))
    {
      fprintf(stderr, "%s\n", ERR_CONNECT);
      return (EXIT_FAILURE);
    }
  printf("(.)(.) Connection succeed: you are connected @ %s:%s\n",
	 this.host, this.port);
  run_client(&this);
  return (EXIT_SUCCESS);
}
