/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Wed Jun 24 15:26:13 2015 David Tran
*/

#include "zappy.h"

int	checkOthers(t_case *position, char *param, t_client *client, int possible)
{
  if (strstr(param, "sibur") && position->sibur > 0)
    {
      position->sibur--;
      client->resources[SIBUR]++;
      possible = 1;
    }
  if (strstr(param, "mendiane") && position->mendiane > 0)
    {
      position->mendiane--;
      client->resources[MENDIANE]++;
      possible = 1;
    }
  if (strstr(param, "phiras") && position->phiras > 0)
    {
      client->resources[PHIRAS]++;
      position->phiras--;
      possible = 1;
    }
  if (strstr(param, "thystame") && position->thystame > 0)
    {
      position->thystame--;
      client->resources[THYSTAME]++;
      possible = 1;
    }
  return (possible);
}

int	checkPossibleTake(t_case *position, char *param, t_client *client)
{
  int	possible;

  possible = 0;
  if (strstr(param, "nourriture") && position->meal > 0)
    {
      position->meal--;
      client->resources[MEAL]++;
      possible = 1;
    }
  if (strstr(param, "linemate") && position->linemate > 0)
    {
      position->linemate--;
      client->resources[LINEMATE]++;
      possible = 1;
    }
  if (strstr(param, "deraumere") && position->deraumere > 0)
    {
      position->deraumere--;
      client->resources[DERAUMERE]++;
      possible = 1;
    }
  return (checkOthers(position, param, client, possible));
}
