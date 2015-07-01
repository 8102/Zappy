/*
** incantation_stone.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Wed Jun 24 15:26:13 2015 David Tran
*/

#include "zappy.h"


int	playerLevelUp(t_client *client, t_client *all)
{
  int	lvl;

  lvl = client->level;
  while (all)
    {
      if (all->pos[0] == client->pos[0] && all->pos[1] == client->pos[1] &&
	  all->level == lvl)
	all->level++;
      all = all->next;
    }
  return (1);
}

int	check_stones_hard(t_client *client, t_case *tmp, t_client *all)
{
  if (client->level == 6 && tmp->linemate > 0 && tmp->deraumere > 1 &&
      tmp->sibur > 2 && tmp->phiras > 0)
    {
      tmp->linemate--;
      tmp->deraumere -= 2;
      tmp->sibur -= 3;
      tmp->phiras--;
      return (playerLevelUp(client, all));
    }
  if (client->level == 7 && tmp->linemate > 1 && tmp->deraumere > 1 &&
      tmp->sibur > 1 && tmp->mendiane > 1 && tmp->phiras > 1 &&
      tmp->thystame > 0)
    {
      tmp->linemate -= 2;
      tmp->deraumere -= 2;
      tmp->sibur -= 2;
      tmp->mendiane -= 2;
      tmp->phiras -= 2;
      tmp->thystame--;
      return (playerLevelUp(client, all));
    }
  return (0);
}

int	check_stones_medium(t_client *client, t_case *tmp, t_client *all)
{
  if (client->level == 4 && tmp->linemate > 0 && tmp->deraumere > 0 &&
      tmp->sibur > 1 && tmp->phiras > 0)
    {
      tmp->linemate--;
      tmp->deraumere--;
      tmp->sibur -= 2;
      tmp->phiras--;
      return (playerLevelUp(client, all));
    }
  if (client->level == 5 && tmp->linemate > 0 && tmp->deraumere > 1 &&
      tmp->sibur > 0 && tmp->mendiane > 2)
    {
      tmp->linemate--;
      tmp->deraumere -= 2;
      tmp->sibur--;
      tmp->mendiane -= 3;
      return (playerLevelUp(client, all));
    }
  return (check_stones_hard(client, tmp, all));
}

int	check_stones(t_client *client, t_case *tmp, t_client *all)
{
  if (client->level == 1 && tmp->linemate > 0)
    {
      tmp->linemate--;
      return (playerLevelUp(client, all));
    }
  if (client->level == 2 && tmp->linemate > 0 && tmp->deraumere > 0 &&
      tmp->sibur > 0)
    {
      tmp->linemate--;
      tmp->deraumere--;
      tmp->sibur--;
      return (playerLevelUp(client, all));
    }
  if (client->level == 3 && tmp->linemate > 1 && tmp->sibur > 0 &&
      tmp->phiras > 1)
    {
      tmp->linemate -= 2;
      tmp->sibur--;
      tmp->phiras -= 2;
      return (playerLevelUp(client, all));
    }
  return (check_stones_medium(client, tmp, all));
}
