/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Sun Jul  5 02:55:29 2015 Hugo Prenat
*/

#include "zappy.h"

char	*voir_ligne(t_master *content, t_client *client,
		    int level, char *str)
{
  if (client->orient == NORTH)
    str = voir_nord(content, client, level, str);
  else if (client->orient == EAST)
    str = voir_est(content, client, level, str);
  else if (client->orient == WEST)
    str = voir_ouest(content, client, level, str);
  else
    str = voir_sud(content, client, level, str);
  return (str);
}

char	*add_coma(char *str)
{
  char	*tmp;

  if (!(tmp = malloc(sizeof(*str) * (strlen(str) + 2))))
    return (NULL);
  strcpy(tmp, str);
  strcat(tmp, ",");
  free(str);
  return (tmp);
}

int		countHowMany(t_case *tmp)
{
  int		count;
  int		i;
  static int	value[] = {7, 11, 9, 10, 6, 9, 7, 9};

  count = 0;
  i = 0;
  while (i <= 7)
    {
      if (tmp->content[i] > 0)
	count += (value[i] * tmp->content[i]);
      i++;
    }
  return (count);
}

char		*add_content_case(t_case *cur, char *str)
{
  int		i;
  char		*tmp;
  static char	*content[] = {" joueur", " nourriture", " linemate",
			      " deraumere", " sibur", " mendiane",
			      " phiras", " thystame", NULL};

  i = 0;
  if (!(tmp = malloc(sizeof(*str) * (strlen(str) + countHowMany(cur) + 2))))
    return (NULL);
  strcpy(tmp, str);
  while (content[i])
    {
      for (int num = 0; num != cur->content[i]; num++)
	strcat(tmp, content[i]);
      i++;
    }
  free(str);
  return (tmp);
}

char	*first_case(t_master *content, t_client *client)
{
  char	*str;

  str = strdup("{");
  str = add_content_case(getCaseFromCoord(client->pos[X],
					  client->pos[Y], content->cases), str);
  str = add_coma(str);
  return (str);
}
