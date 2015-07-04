/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Sat Jul  4 20:46:40 2015 Hugo Prenat
*/

#include "zappy.h"

int	checkOtherSend(t_case *position, char *param,
		       t_client *client, int possible)
{
  if (strstr(param, "sibur") && client->resources[SIBUR] > 0)
    {
      position->content[4]++;
      client->resources[SIBUR]--;
      possible = SIBUR;
    }
  if (strstr(param, "mendiane") && client->resources[MENDIANE] > 0)
    {
      position->content[5]++;
      client->resources[MENDIANE]--;
      possible = MENDIANE;
    }
  if (strstr(param, "phiras") && client->resources[PHIRAS] > 0)
    {
      client->resources[PHIRAS]--;
      position->content[6]++;
      possible = PHIRAS;
    }
  if (strstr(param, "thystame") && client->resources[THYSTAME] > 0)
    {
      position->content[7]++;
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
      position->content[1]++;
      client->resources[MEAL]--;
      possible = MEAL;
    }
  if (strstr(param, "linemate") && client->resources[LINEMATE] > 0)
    {
      position->content[2]++;
      client->resources[LINEMATE]--;
      possible = LINEMATE;
    }
  if (strstr(param, "deraumere") && client->resources[DERAUMERE] > 0)
    {
      position->content[3]++;
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
