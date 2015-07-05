/*
** voir_poss.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Sat Jul  4 23:11:05 2015 Hugo Prenat
** Last update Sun Jul  5 01:20:34 2015 Hugo Prenat
*/

#include "zappy.h"

size_t	voir_gauche(t_master *content, size_t y)
{
  if (y == 0)
    return (content->height - 1);
  return (y - 1);
}

size_t	voir_droite(t_master *content, size_t y)
{
  if (y == content->height - 1)
    return (0);
  return (y + 1);
}

size_t	voir_haut(t_master *content, size_t x)
{
  if (x == 0)
    return (content->width - 1);
  return (x - 1);
}

size_t	voir_bas(t_master *content, size_t x)
{
  if (x == content->width - 1)
    return (0);
  return (x + 1);
}
