/*
** pos.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Mon Jun 29 17:29:07 2015 Hugo Prenat
** Last update Thu Jul  2 19:25:46 2015 Hugo Prenat
*/

#include "zappy.h"

void		set_pos(t_master *content, t_client *client, size_t x, size_t y)
{
  t_case	*tmp;

  tmp = content->cases;
  if (client->placed)
    {
      while (tmp)
	{
	  if (tmp->x == client->pos[X] && tmp->y == client->pos[Y])
	    break ;
	  tmp = tmp->next;
	}
      tmp->nbr_player--;
    }
  tmp = content->cases;
  x = ((int)x >= content->width) ? 0 : x;
  y = ((int)y >= content->height) ? 0 : y;
  while (tmp)
    {
      if (tmp->x == x && tmp->y == y)
	break ;
      tmp = tmp->next;
    }
  tmp->nbr_player++;
  client->pos[X] = x;
  client->pos[Y] = y;
}
