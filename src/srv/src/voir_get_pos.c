/*
** voir_get_pos.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Sun Jul  5 01:20:53 2015 Hugo Prenat
** Last update Sun Jul  5 01:31:01 2015 Hugo Prenat
*/

#include "zappy.h"

size_t	get_y_pos(t_master *content, size_t y, int level)
{
  int	i;

  i = 0;
  while (i != level)
    {
      y = voir_gauche(content, y);
      i++;
    }
  return (y);
}
