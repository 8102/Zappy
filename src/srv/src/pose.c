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
      possible = SIBUR;
    }
  if (strstr(param, "mendiane") && client->resources[MENDIANE] > 0)
    {
      position->mendiane++;
      client->resources[MENDIANE]--;
      possible = MENDIANE;
    }
  if (strstr(param, "phiras") && client->resources[PHIRAS] > 0)
    {
      client->resources[PHIRAS]--;
      position->phiras++;
      possible = PHIRAS;
    }
  if (strstr(param, "thystame") && client->resources[THYSTAME] > 0)
    {
      position->thystame++;
      client->resources[THYSTAME]--;
      possible = THYSTAME;
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
      possible = MEAL;
    }
  if (strstr(param, "linemate") && client->resources[LINEMATE] > 0)
    {
      position->linemate++;
      client->resources[LINEMATE]--;
      possible = LINEMATE;
    }
  if (strstr(param, "deraumere") && client->resources[DERAUMERE] > 0)
    {
      position->deraumere++;
      client->resources[DERAUMERE]--;
      possible = DERAUMERE;
    }
  return (checkOtherSend(position, param, client, possible));
}

void	pose_graphic(t_client *client, t_master *content, int resource)
{
  char		*transform;

  if (client->trigger[GRAPHIC])
    {
      transform = transform_int(client->id);
      ssend(client->socket, "pdr %d %d\n", client->id, resource);
      pin(transform, client, content);
      free(transform);
      transform = transformCoord(client);
      bct(transform, client, content);
      free(transform);
    }
}
