/*
** init.c for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Tue Jun 30 23:34:42 2015 TommyStarK
** Last update Sun Jul  5 21:08:55 2015 Emmanuel Chambon
*/

#include "client.h"

t_socket	*init_client(t_client *it)
{
  t_socket	*sock;

  !(sock = malloc(sizeof(t_socket))) ? error("malloc") : 0;
  it->team = NULL;
  it->host = LOCALHOST;
  it->port = 0;
  it->ia = init_ia();
  it->size = get_array_size(it->ia);
  it->fdmax = NULL;
  it->rfds = NULL;
  return (sock);
}

char		**init_ia()
{
  char		**ret;

  if (!(ret = malloc(sizeof(char *) * 10)))
    error("malloc");
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
