/*
** direction.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Wed Jun 24 19:02:16 2015 Hugo Prenat
** Last update Thu Jul  2 15:54:28 2015 Hugo Prenat
*/

#include "zappy.h"

void	go_south_west(t_master *content, t_client *client,
		      e_Orientation orient)
{
  if (orient == SOUTH)
    {
      if (client->pos[1] == (size_t)content->height - 1)
	set_pos(content, client, client->pos[X], 0);
      else
	set_pos(content, client, client->pos[X], client->pos[Y] + 1);
    }
  else
    {
      if (client->pos[0] == 0)
	set_pos(content, client, content->width, client->pos[Y]);
      else
	set_pos(content, client, client->pos[X] - 1, client->pos[Y]);
    }
}

void	change_pos(t_master *content, t_client *client, e_Orientation orient)
{
  if (orient == NORTH)
    {
      if (client->pos[1] == 0)
	set_pos(content, client, client->pos[X], content->height);
      else
	set_pos(content, client, client->pos[X], client->pos[Y] - 1);
    }
  else if (orient == EAST)
    {
      if (client->pos[0] == (size_t)content->width - 1)
	set_pos(content, client, 0, client->pos[Y]);
      else
	set_pos(content, client, client->pos[X] + 1, client->pos[Y]);
    }
  else
    go_south_west(content, client, orient);
}

void		avance(char UNUSED*params,
		       t_client *client,
		       t_master *content)
{
  t_client	*tmp;

  tmp = content->clients;
  change_pos(content, client, client->orient);
  while (tmp)
    {
      if (tmp->trigger[GRAPHIC] == true)
	{
	  ssend(tmp->socket, "ppo %d %d %d %d\n", tmp->id, tmp->pos[0],
		tmp->pos[1], tmp->orient);
	}
      tmp = tmp->next;
    }
  ssend(client->socket, "ok\n");
}

void		droite(char UNUSED*params,
		       t_client *client,
		       UNUSED t_master *content)
{
  t_client	*tmp;

  tmp = content->clients;
  if (client->orient != WEST)
    client->orient++;
  else
    client->orient = NORTH;
  while (tmp)
    {
      if (tmp->trigger[GRAPHIC] == true)
	{
	  ssend(tmp->socket, "ppo %d %d %d %d\n", tmp->id, tmp->pos[0],
		tmp->pos[1], tmp->orient);
	}
      tmp = tmp->next;
    }
  ssend(client->socket, "ok\n");
}

void		gauche(char UNUSED*params,
		       t_client *client,
		       UNUSED t_master *content)
{
  t_client	*tmp;

  tmp = content->clients;
  if (client->orient != NORTH)
    client->orient--;
  else
    client->orient = WEST;
  while (tmp)
    {
      if (tmp->trigger[GRAPHIC] == true)
	{
	  ssend(tmp->socket, "ppo %d %d %d %d\n", tmp->id, tmp->pos[0],
		tmp->pos[1], tmp->orient);
	}
      tmp = tmp->next;
    }
  ssend(client->socket, "ok\n");
}
