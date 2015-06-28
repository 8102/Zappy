/*
** utils.c for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Sat Jun 27 20:56:34 2015 TommyStarK
** Last update Sun Jun 28 00:17:25 2015 TommyStarK
*/

#include "client.h"

void		error(char *error)
{
  perror(error);
  exit(EXIT_FAILURE);
}

void		ssend(int fd, char *data)
{
  int		len;

  len = strlen(data);
  snd(data, &len, fd);
}

void		snd(char *buf, int *len, int sock)
{
  int		tot;
  int		l;
  int		r;

  l = *len;
  tot = 0;
  while (tot < *len)
    {
      r = send(sock, buf + tot, l, 0);
      if (r == -1)
	{
	  perror("recv");
	  break ;
	}
      tot += r;
      l -= r;
    }
  *len = tot;
}
