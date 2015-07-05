/*
** broadcast.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Wed Jun 24 15:26:13 2015 David Tran
*/

#include "zappy.h"

int	horizontalVerticalOrient(int c1, int c2, int type)
{
  if (type == 0)
    return ((c1 < c2) ? 5 : 1);
  return ((c1 < c2) ? 3 : 7);
}

int	checkBasicCase(t_client *src, t_client *client, t_master *all)
{
  int	x;
  int	y;
  int	cx;
  int	cy;
  float	distance;
  int	lastOrient;

  x = src->pos[0];
  y = src->pos[1];
  cx = client->pos[0];
  cy = client->pos[1];
  if (client->pos[0] == src->pos[0] && client->pos[1] == src->pos[1])
    return (0);
  if (client->pos[0] == src->pos[0])
    {
      distance = calculateDistance(x, y, cx, cy);
      translateMapUp(&y, &cy, all);
      lastOrient = (distance > calculateDistance(x, y, cx, cy)) ?
	horizontalVerticalOrient(y, cy, 0) :
	horizontalVerticalOrient(src->pos[1], client->pos[1], 0);
      if (client->orient == NORTH)
	return (lastOrient);
      return (lastOrient + ((int)client->orient - 1) * 2 == 8 ? 8 :
	      ((lastOrient + ((int)client->orient - 1) * 2) % 8));
    }
  return (checkBasicYAxis(src, client, all));
}

int	checkBasicYAxis(t_client *src, t_client *client, t_master *all)
{
  int	x;
  int	y;
  int	cx;
  int	cy;
  float	distance;
  int	lastOrient;

  x = src->pos[0];
  y = src->pos[1];
  cx = client->pos[0];
  cy = client->pos[1];
  if (client->pos[1] == src->pos[1])
    {
      distance = calculateDistance(x, y, cx, cy);
      translateMapRight(&x, &cx, all);
      lastOrient = (distance > calculateDistance(x, y, cx, cy)) ?
	horizontalVerticalOrient(x, cx, 1) :
	horizontalVerticalOrient(src->pos[0], client->pos[0], 1);
      if (client->orient == NORTH)
	return (lastOrient);
      return (lastOrient + ((int)client->orient - 1) * 2 == 8 ? 8 :
	      ((lastOrient + ((int)client->orient - 1) * 2) % 8));
    }
  return (multipleCases(src, client, all));
}

int	multipleFinalOpe(t_client *src, t_client *client, t_master *all)
{
  int	y;
  int	cy;
  int	lastOrient;

  y = src->pos[1];
  cy = client->pos[1];
  translateMapUp(&y, &cy, all);
  lastOrient = (calculateDistance(src->pos[0], y, client->pos[0], cy) <
		calculateDistance(src->pos[0], src->pos[1], client->pos[0],
				  client->pos[1])) ?
    calculateOrientation(src->pos[0], y, client->pos[0], cy) :
    calculateOrientation(src->pos[0], src->pos[1], client->pos[0],
			 client->pos[1]);
  if (client->orient == NORTH)
    return (lastOrient);
  return (lastOrient + ((int)client->orient - 1) * 2 == 8 ? 8 :
	  ((lastOrient + ((int)client->orient - 1) * 2) % 8));
}

int	multipleCases(t_client *src, t_client *client, t_master *all)
{
  int	x;
  int	y;
  int	cx;
  int	cy;
  float	distance;
  int	lastOrient;

  x = src->pos[0];
  y = src->pos[1];
  cx = client->pos[0];
  cy = client->pos[1];
  distance = calculateDistance(x, y, cx, cy);
  translateMapUp(&y, &cy, all);
  if (distance > calculateDistance(x, y, cx, cy))
    distance = calculateDistance(x, y, cx, cy);
  translateMapRight(&x, &cx, all);
  if (distance > calculateDistance(x, y, cx, cy))
    {
      lastOrient = calculateOrientation(x, y, cx, cy);
      if (client->orient == NORTH)
	return (lastOrient);
      return (lastOrient + ((int)client->orient - 1) * 2 == 8 ? 8 :
	      ((lastOrient + ((int)client->orient - 1) * 2) % 8));
    }
  return (multipleFinalOpe(src, client, all));
}
