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

int	checkOtherSend(t_case *position, char *param,
		       t_client *client, int possible)
{
  if (strstr(param, "sibur") && client->resources[SIBUR] > 0)
    {
      position->sibur++;
      client->resources[SIBUR]--;
      possible = 1;
    }
  if (strstr(param, "mendiane") && client->resources[MENDIANE] > 0)
    {
      position->mendiane++;
      client->resources[MENDIANE]--;
      possible = 1;
    }
  if (strstr(param, "phiras") && client->resources[PHIRAS] > 0)
    {
      client->resources[PHIRAS]--;
      position->phiras++;
      possible = 1;
    }
  if (strstr(param, "thystame") && client->resources[THYSTAME] > 0)
    {
      position->thystame++;
      client->resources[THYSTAME]--;
      possible = 1;
    }
  return (possible);
}

int	checkPossibleSend(t_case *position, char *param, t_client *client)
{
  int	possible;

  possible = 0;
  if (strstr(param, "nourriture") && client->resources[MEAL] > 0)
    {
      position->meal++;
      client->resources[MEAL]--;
      possible = 1;
    }
  if (strstr(param, "linemate") && client->resources[LINEMATE] > 0)
    {
      position->linemate++;
      client->resources[LINEMATE]--;
      possible = 1;
    }
  if (strstr(param, "deraumere") && client->resources[DERAUMERE] > 0)
    {
      position->deraumere++;
      client->resources[DERAUMERE]--;
      possible = 1;
    }
  return (checkOtherSend(position, param, client, possible));
}
