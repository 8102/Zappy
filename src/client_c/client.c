/*
** client.c for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Sat Jun 27 20:40:47 2015 TommyStarK
** Last update Sun Jun 28 00:23:33 2015 TommyStarK
*/

#include "client.h"

void             disconnect(t_client *it)
{
   if (it->status)
     close(it->client->fd);
   write(1, BYEBYE, strlen(BYEBYE)) == -1 ? error("write") : 0;
   exit(EXIT_SUCCESS);
}

int             make_coffe(t_client *it)
{
  int           ret;
  char          tmp[BUFF_SIZE] = {0};

  memset(tmp, 0, BUFF_SIZE);
  ret = recv(it->client->fd, tmp, BUFF_SIZE, 0);
  !ret ? printf("00PS: connection closed by server.\n")
        : ret > 0 ? printf("%s\n", tmp) : 0;
  return (!ret ? 0 : ret > 0 ? 1 : -1);
}

void            run_client(t_client *it)
{
   int          i;
   int          ret;
   int          fdmax;
   fd_set       read_fds;

   fdmax = it->client->fd + 1;
   FD_ZERO(&read_fds);
   it->fdmax = &fdmax;
   it->rfds = &read_fds;
   while (42)
   {
     FD_ZERO(it->rfds);
     it->client->fd < 0 ? 0 : FD_SET(it->client->fd, it->rfds);
     if (select(fdmax, it->rfds, NULL, NULL, NULL) == -1)
        error("select");
     for (i = 0; i < *it->fdmax; i++)
     {
        if (FD_ISSET(i, &read_fds))
          (ret = make_coffe(it)) < 0 ? disconnect(it) : 0;
     }
   }
}

t_socket	*init_client(t_client *it, char **arg)
{
  t_socket	*sock;

  !(sock = malloc(sizeof(t_socket))) ? error("malloc") : 0;
  !(it->team = malloc(strlen(arg[2]))) ? error("malloc")
    		      : bzero(it->team, strlen(arg[2]));
  !(it->machine = malloc(BUFF_SIZE)) ? error("malloc") : bzero(it->machine, BUFF_SIZE);
  !(it->team= strdup(arg[2])) ? error("strdup") : 0;
  it->fdmax = NULL;
  it->rfds = NULL;
  return (sock);
}

int 		main(int ac, char **av)
{
  t_client 	this;

  if (ac < 5)
    return (fprintf(stderr, "%s\n", USAGE));
  this.client = init_client(&this, av);
  this.client->fd = -1;
  this.status = co_serv(this.client, ac == 7 ? av[6] : LOCALHOST, av[4]);
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
