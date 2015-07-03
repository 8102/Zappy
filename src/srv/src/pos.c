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

void		reset_previous(t_client *client, t_master *content)
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
}

void		set_pos(t_master *content, t_client *client, int x, int y)
{
  t_case	*tmp;

  reset_previous(client, content);
  tmp = content->cases;
  x = (x >= content->width) ? 0 : x;
  y = (y >= content->height) ? 0 : y;
  x = (x < 0) ? content->width : x;
  y = (y < 0) ? content->height : y;
  while (tmp)
    {
      if ((int)tmp->x == x && (int)tmp->y == y)
	break ;
      tmp = tmp->next;
    }
  tmp->nbr_player++;
  client->pos[X] = x;
  client->pos[Y] = y;
}
