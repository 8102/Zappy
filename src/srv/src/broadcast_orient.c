/*
** broadcast_orient.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Wed Jun 24 15:26:13 2015 David Tran
*/

#include "zappy.h"

int		returnOrientation(float angle, int type)
{
  if (type == 0 && angle <= 22.5f)
    return (7);
  else if (type == 0 && angle >= 67.5f)
    return (1);
  else if (type == 0)
    return (8);
  if (type == 1 && angle <= 22.5f)
    return (3);
  else if (type == 1 && angle >= 67.5f)
    return (1);
  else if (type == 1)
    return (2);
  if (type == 2 && angle <= 22.5f)
    return (7);
  else if (type == 2 && angle >= 67.5f)
    return (5);
  else if (type == 2)
    return (6);
  if (type == 3 && angle <= 22.5f)
    return (3);
  else if (type == 3 && angle >= 67.5f)
    return (5);
  return (2);
}

int		calculateOrientation(int x, int y, int xc, int yc)
{
  int		tx;
  int		ty;
  float		angle;

  ty = (y < yc) ? y : yc;
  tx = (y < yc) ? x : xc;
  if (y < yc)
    {
      angle = 90 - atanf(calculateDistance(x, y, tx, ty) /
			 calculateDistance(x, y, xc, yc));
      return ((x > xc) ? (returnOrientation(angle, 0)) : (returnOrientation(angle, 1)));
    }
  angle = 90 - atanf(calculateDistance(x, y, tx, ty) /
		     calculateDistance(x, y, xc, yc));
  return ((x > xc) ? (returnOrientation(angle, 2)) : (returnOrientation(angle, 3)));
}

void	translateMapUp(int *y, int *yc, t_master *all)
{
  *y -= (*y - all->height / 2) < 0 ? 0 + all->height / 2 : all->height / 2;
  *yc -= (*yc - all->height / 2) < 0 ? 0 + all->height / 2 : all->height / 2;
}

void	translateMapRight(int *x, int *xc, t_master *all)
{
  *x -= (*x - all->width / 2) < 0 ? 0 + all->width / 2 : all->width / 2;
  *xc -= (*xc - all->width / 2) < 0 ? 0 + all->width / 2 : all->width / 2;
}

float	calculateDistance(int x, int y, int xc, int yc)
{
  int	powx;
  int	powy;

  powx = pow(x - xc, 2);
  powy = pow(y - yc, 2);
  return (sqrt(powx + powy));
}
