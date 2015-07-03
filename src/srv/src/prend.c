/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Fri Jul  3 22:38:51 2015 Hugo Prenat
*/

#include "zappy.h"

int	checkOthers(t_case *position, char *param, t_client *client,
		    int possible)
{
  if (strstr(param, "sibur") && position->sibur > 0)
    {
      position->sibur--;
      client->resources[SIBUR]++;
      possible = SIBUR;
    }
  if (strstr(param, "mendiane") && position->mendiane > 0)
    {
      position->mendiane--;
      client->resources[MENDIANE]++;
      possible = MENDIANE;
    }
  if (strstr(param, "phiras") && position->phiras > 0)
    {
      client->resources[PHIRAS]++;
      position->phiras--;
      possible = PHIRAS;
    }
  if (strstr(param, "thystame") && position->thystame > 0)
    {
      position->thystame--;
      client->resources[THYSTAME]++;
      possible = THYSTAME;
    }
  return (possible);
}

int	checkPossibleTake(t_case *position, char *param, t_client *client)
{
  int	possible;

  possible = -1;
  if (strstr(param, "nourriture") && position->meal > 0)
    {
      position->meal--;
      client->resources[MEAL]++;
      possible = MEAL;
    }
  if (strstr(param, "linemate") && position->linemate > 0)
    {
      position->linemate--;
      client->resources[LINEMATE]++;
      possible = LINEMATE;
    }
  if (strstr(param, "deraumere") && position->deraumere > 0)
    {
      position->deraumere--;
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

  x = transform_int(client->pos[0]);
  y = transform_int(client->pos[1]);
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
  t_client	*client_tmp;

  client_tmp = content->clients;
  while(client_tmp)
    {
      if (client_tmp->trigger[GRAPHIC])
	ssend(client_tmp->socket, "pgt %d %d\n", client->id, resource);
      client_tmp = client_tmp->next;
    }
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
