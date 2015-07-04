/*
** creation.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Fri Jul  3 18:10:08 2015 Hugo Prenat
** Last update Fri Jul  3 21:13:25 2015 Hugo Prenat
*/

#include "zappy.h"

void		print_creation(t_master *content)
{
  printf("%sListening on port %s%s\n"
	 "%sWidth = %s%lu %sHeight = %s%lu %sMax player = %s%d %sT = %s%d\n%s",
	 BOLDWHITE, BOLDBLUE, content->port, BOLDWHITE, BOLDBLUE,
	 content->width, BOLDWHITE, BOLDBLUE, content->height,
	 BOLDWHITE, BOLDBLUE, content->max_clients,
   BOLDWHITE, BOLDBLUE, content->delay, RESET);
}
