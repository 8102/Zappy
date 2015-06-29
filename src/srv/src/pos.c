/*
** pos.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Mon Jun 29 17:29:07 2015 Hugo Prenat
** Last update Mon Jun 29 17:56:14 2015 Hugo Prenat
*/

#include "zappy.h"

void 	set_pos(t_master *content, t_client *client, size_t x, size_t y)
{
  t_case	*tmp;

  tmp = content->cases;
  while (tmp->x != client->pos[0] && tmp->y != client->pos[1])
    tmp = tmp->next;
  if (tmp->nbr_player != 0)
    tmp->nbr_player--;
  tmp = content->cases;
  while (tmp->x != x && tmp->y != y)
    tmp = tmp->next;
  tmp->nbr_player++;
}
