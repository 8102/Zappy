/*
** voir_get_pos.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Sun Jul  5 01:20:53 2015 Hugo Prenat
** Last update Sun Jul  5 21:40:22 2015 Hugo Prenat
*/

#include "zappy.h"

size_t	get_real_pos(t_master *content, size_t pos,
		     int level, size_t (*func)(t_master *, size_t))
{
  int	i;

  i = 1;
  while (i <= level)
    {
      pos = func(content, pos);
      i++;
    }
  return (pos);
}
