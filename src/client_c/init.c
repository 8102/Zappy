/*
** init.c for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Tue Jun 30 23:34:42 2015 TommyStarK
** Last update Tue Jun 30 23:43:54 2015 TommyStarK
*/

#include "client.h"

t_socket	*init_client(t_client *it, char **arg)
{
  t_socket	*sock;

  !(sock = malloc(sizeof(t_socket))) ? error("malloc") : 0;
  !(it->team = malloc(strlen(arg[2]))) ? error("malloc")
    		      : bzero(it->team, strlen(arg[2]));
  !(it->team = strdup(arg[2])) ? error("strdup") : 0;
  !(it->ia = init_ia()) ? error("initializion ia") : 0;
  it->size = get_array_size(it->ia);
  it->fdmax = NULL;
  it->rfds = NULL;
  return (sock);
}

void 		init_time_handler()
{
  int		i;

  i = time(NULL);
  srand(i);
}

char            **init_ia()
{
  int           i;
  char          **ret;

  if (!(ret = malloc(sizeof(char *) * 10)))
     return (NULL);
  for (i = 0; i < 10; i++)
  {
    if (!(ret[i] = malloc(sizeof(BUFF_SIZE / 8))))
      return (NULL);
    if (!(memset(ret[i], 0, BUFF_SIZE / 8)))
      error("memset");
  }
  ret[i] = NULL;
  !(ret[0] = strdup("avance")) ? error("strdup") : 0;
  !(ret[1] = strdup("droite")) ? error("strdup") : 0;
  !(ret[2] = strdup("gauche")) ? error("strdup") : 0;
  !(ret[3] = strdup("voir")) ? error("strdup") : 0;
  !(ret[4] = strdup("inventaire")) ? error("strdup") : 0;
  !(ret[5] = strdup("prend objet")) ? error("strdup") : 0;
  !(ret[6] = strdup("pose objet")) ? error("strdup") : 0;
  !(ret[7] = strdup("expulse")) ? error("strdup") : 0;
  !(ret[8] = strdup("incantation")) ? error("strdup") : 0;
  return (ret);
}
