/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Sat Jul  4 22:33:03 2015 Emmanuel Chambon
*/

#include "zappy.h"

int	checkOthers(t_case *position, char *param, t_client *client,
		    int possible)
{
  if (strstr(param, "sibur") && position->content[4] > 0)
    {
      position->content[4]--;
      client->resources[SIBUR]++;
      possible = SIBUR;
    }
  if (strstr(param, "mendiane") && position->content[5] > 0)
    {
      position->content[5]--;
      client->resources[MENDIANE]++;
      possible = MENDIANE;
    }
  if (strstr(param, "phiras") && position->content[6] > 0)
    {
      client->resources[PHIRAS]++;
      position->content[6]--;
      possible = PHIRAS;
    }
  if (strstr(param, "thystame") && position->content[6] > 0)
    {
      position->content[7]--;
      client->resources[THYSTAME]++;
      possible = THYSTAME;
    }
  return (possible);
}

int	checkPossibleTake(t_case *position, char *param, t_client *client)
{
  int	possible;

  possible = -1;
  if (strstr(param, "nourriture") && position->content[1] > 0)
    {
      position->content[1]--;
      client->resources[MEAL]++;
      possible = MEAL;
    }
  if (strstr(param, "linemate") && position->content[2] > 0)
    {
      position->content[2]--;
      client->resources[LINEMATE]++;
      possible = LINEMATE;
    }
  if (strstr(param, "deraumere") && position->content[3] > 0)
    {
      position->content[3]--;
      client->resources[DERAUMERE]++;
      possible = DERAUMERE;
    }
  return (checkOthers(position, param, client, possible));
}

char	*transformCoord(t_client *client)
{
  char	*send;
  char	*x;
  char	*y;

  x = transform_int(client->pos[X]);
  y = transform_int(client->pos[Y]);
  if (!(send = malloc(10 + strlen(x) + strlen(y))))
    return (NULL);
  send[0] = 0;
  strcat(send, x);
  strcat(send, " ");
  strcat(send, y);
  free(x);
  free(y);
  return (send);
}

void		prend_graphic(t_client *client, t_master *content, int resource)
{
  char		*transform;

  ssend_graphics(content, "pgt %d %d\n", client->id, resource);
  if (client->trigger[GRAPHIC])
    {
      transform = transform_int(client->id);
      pin(transform, client, content);
      free(transform);
      transform = transformCoord(client);
      bct(transform, client, content);
      free(transform);
    }
}
