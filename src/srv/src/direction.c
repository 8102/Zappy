/*
** direction.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Wed Jun 24 19:02:16 2015 Hugo Prenat
** Last update Thu Jun 25 00:24:22 2015 Hugo Prenat
*/

#include "zappy.h"

void	go_east_west(t_master *content, t_client *client)
{
  if (client->orient == SOUTH)
    {
      if (client->pos[1] == (size_t)content->height)
	client->pos[1] = 0;
      else
	client->pos[1] += 1;
    }
  else
    {
      if (client->pos[0] == 0)
	client->pos[0] = content->width;
      else
	client->pos[0] -= 1;
    }
}

void	change_pos(t_master *content, t_client *client)
{
  if (client->orient == NORTH)
    {
      if (client->pos[1] == 0)
	client->pos[1] = content->height;
      else
	client->pos[1] -= 1;
    }
  else if (client->orient == EAST)
    {
      if (client->pos[0] == (size_t)content->width)
	client->pos[0] = 0;
      else
	client->pos[0] += 1;
    }
  else
    go_east_west(content, client);
}

void	avance(char UNUSED*params,
	       t_client *client,
	       t_master *content)
{
  if (client->trigger[GRAPHIC] == true)
    {
      change_pos(content, client);
      ssend(client->socket, "ppo %d %d %d %d\n", client->id, client->pos[0],
	    client->pos[1], client->orient);
    }
  else
    ssend(client->socket, "ok\n");
}

void	droite(char UNUSED*params,
	       t_client *client,
	       UNUSED t_master *content)
{
  if (client->trigger[GRAPHIC] == true)
    {
      if (client->orient != WEST)
	client->orient++;
      else
	client->orient = NORTH;
      ssend(client->socket, "ppo %d %d %d %d\n", client->id, client->pos[0],
	    client->pos[1], client->orient);
    }
  else
  ssend(client->socket, "ok\n");

}

void	gauche(char UNUSED*params,
	       t_client *client,
	       UNUSED t_master *content)
{
  if (client->trigger[GRAPHIC] == true)
    {
      if (client->orient != NORTH)
	client->orient--;
      else
	client->orient = WEST;
      ssend(client->socket, "ppo %d %d %d %d\n", client->id, client->pos[0],
	    client->pos[1], client->orient);
    }
  else
  ssend(client->socket, "ok\n");
}
