/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Sun Jul  5 02:53:13 2015 Hugo Prenat
*/

#include "zappy.h"

char	*voir_nord(t_master *content, t_client *client, int level, char *str)
{
  size_t	x;
  size_t	y;
  int		i;
  int		j;

  x = voir_haut(content, client->pos[X]);
  y = voir_gauche(content, client->pos[Y]);
  i = 1;
  while (i <= level)
    {
      j = level * -1;
      while (j <= level)
	{
	  str = add_content_case(getCaseFromCoord(x, y, content->cases), str);
	  y = voir_droite(content, y);
	  j++;
	  if (j <= level)
	    str = add_coma(str);
	}
      x = voir_haut(content, x);
      i++;
      if (i <= level)
	str = add_coma(str);
    }
  return (str);
}

char	*voir_est(t_master *content, t_client *client, int level, char *str)
{
  size_t	x;
  size_t	y;
  int		i;
  int		j;

  x = voir_haut(content, client->pos[X]);
  y = voir_droite(content, client->pos[Y]);
  i = 1;
  while (i <= level)
    {
      j = level * -1;
      while (j <= level)
	{
	  str = add_content_case(getCaseFromCoord(x, y, content->cases), str);
	  x = voir_bas(content, x);
	  j++;
	  if (j <= level)
	    str = add_coma(str);
	}
      y = voir_droite(content, y);
      i++;
      if (i <= level)
	str = add_coma(str);
    }
  return (str);
}

char	*voir_sud(t_master *content, t_client *client, int level, char *str)
{
  size_t	x;
  size_t	y;
  int		i;
  int		j;

  x = voir_bas(content, client->pos[X]);
  y = voir_droite(content, client->pos[Y]);
  i = 1;
  while (i <= level)
    {
      j = level * -1;
      while (j <= level)
	{
	  str = add_content_case(getCaseFromCoord(x, y, content->cases), str);
	  y = voir_gauche(content, y);
	  j++;
	  if (j <= level)
	    str = add_coma(str);
	}
      x = voir_bas(content, x);
      i++;
      if (i <= level)
	str = add_coma(str);
    }
  return (str);
}

char	*voir_ouest(t_master *content, t_client *client, int level, char *str)
{
  size_t	x;
  size_t	y;
  int		i;
  int		j;

  x = voir_bas(content, client->pos[X]);
  y = voir_gauche(content, client->pos[Y]);
  i = 1;
  while (i <= level)
    {
      j = level * -1;
      while (j <= level)
	{
	  str = add_content_case(getCaseFromCoord(x, y, content->cases), str);
	  x = voir_haut(content, x);
	  j++;
	  if (j <= level)
	    str = add_coma(str);
	}
      y = voir_gauche(content, y);
      i++;
      if (i <= level)
	str = add_coma(str);
    }
  return (str);
}

void	voir(char UNUSED*params,
	     t_client *client,
	     t_master *content)
{
  char	*ret;
  char	*str;
  int	level;

  level = 1;
  timespec_add(client->clock, content->time.delays[VOIR], true);
  str = first_case(content, client);
  while (level <= client->level)
    {
      str = voir_ligne(content, client, level, str);
      level++;
    }
  if (!(ret = malloc(sizeof(*str) * (strlen(str) + 3))))
    return ;
  strcpy(ret, str);
  strcat(ret, "}\n");
  ssend(client->socket, ret);
  free(str);
  free(ret);
}
