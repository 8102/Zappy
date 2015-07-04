/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Sat Jul  4 22:17:27 2015 Hugo Prenat
*/

#include "zappy.h"

t_case		*getNextCase(t_case *tmp, t_master *all, int type)
{
  if (type == 0)
    {
      if (tmp->x + 1 >= all->width)
	return (getCaseFromCoord(0, tmp->y, all->cases));
      return (getCaseFromCoord(tmp->x + 1, tmp->y, all->cases));
    }
  if (tmp->y + 1 >= all->height)
    return (getCaseFromCoord(tmp->x, 0, all->cases));
  return (getCaseFromCoord(tmp->x, tmp->y + 1, all->cases));
}

t_case		*getCaseInMap(t_client *client, int tmp, int lvl, t_master *all)
{
  t_case	*parse;
  lli		x;
  lli		y;

  printf(BOLDMAGENTA"======{On fait un tour}======\n"RESET);
  printf("BOUM = %lld\n", (lli)client->pos[X] + tmp);
  if ((x = (lli)client->pos[X] + tmp) < 0)
    {
      x = all->width + tmp;
      while (x < 0)
	x = all->width + (tmp - x);
    }
  printf("X == %lld\n"RESET, x);
  if ((size_t)x >= all->width)
    x -= all->width;
  printf(RED"After X == %lld\n"RESET, x);
  if ((y = (lli)client->pos[Y] + lvl) < 0)
    {
      y = all->height + lvl;
      while (y < 0)
	y = all->height + (lvl - y);
    }
  printf(RED"Y == %lld\n"RESET, y);
  if ((size_t)y >= all->height)
    y-= all->height;
  printf(RED"After Y == %lld\n"RESET, y);
  parse = all->cases;
  while (parse)
    {
      if (parse->x == (size_t)x && parse->y == (size_t)y)
	break ;
      parse = parse->next;
    }
  return (parse);
}

int		countHowMany(t_case *tmp)
{
  int		count;
  static int	value[] = {8, 11, 10, 10, 6, 9, 7, 10};

  count = 0;
  for (int i = 0; i <= 7; i++)
    {
      if (tmp->content[i] > 0)
	count += (value[i] * tmp->content[i]);
    }
  return (count);
}

char		*add_content_case(t_case *cur, char *str)
{
  int		i;
  char		*ret;
  static char	*content[] = {" joueur", " nourriture", " linemate",
			      " deraumere", " sibur", " mendiane"
			      " phiras", " thystame", NULL};

  i = 0;
  if (!(ret = malloc(sizeof(*str) * (strlen(str) + countHowMany(cur) + 1))))
    return (NULL);
  strcpy(ret, str);
  while (content[i])
    {
      for (int num = 0; num != cur->content[i]; num++)
	strcat(ret, content[i]);
      i++;
    }
  free(str);
  return (ret);
}

char	*first_case(t_master *content, t_client *client)
{
  char	*str;
  char	*ret;

  str = strdup("{");
  str = add_content_case(getCaseFromCoord(client->pos[X],
					  client->pos[Y], content->cases), str);
  if (!(ret = malloc(sizeof(*str) * (strlen(str) + 2))))
    return (NULL);
  strcpy(ret, str);
  strcat(ret, ",");
  free(str);
  return (ret);
}
