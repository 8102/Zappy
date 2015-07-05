/*
** init.c for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Tue Jun 30 23:34:42 2015 TommyStarK
** Last update Sun Jul  5 02:58:11 2015 Emmanuel Chambon
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
  srand(time(NULL));
}

char            **init_ia()
{
  char          **ret;

  if (!(ret = malloc(sizeof(char *) * 10)))
     return (NULL);
  ret[0] = "avance\n";
  ret[1] = "droite\n";
  ret[2] = "gauche\n";
  ret[3] = "voir\n";
  ret[4] = "inventaire\n";
  ret[5] = "prend objet\n";
  ret[6] = "pose objet\n";
  ret[7] = "expulse\n";
  ret[8] = "incantation\n";
  ret[9] = NULL;
  return (ret);
}
