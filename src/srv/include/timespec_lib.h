/*
** timelib.h for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Jul  2 21:53:17 2015 Emmanuel Chambon
** Last update Fri Jul  3 06:18:21 2015 Emmanuel Chambon
*/

#pragma once
#ifndef TIMESPEC_LIB_H_
# define TIMESPEC_LIB_H_

# include <time.h>
# include <assert.h>

/*
**	timespec_add.c
*/
void					timespec_add_usec(struct timespec *,
							  unsigned long long int, bool);
void					timespec_add_timespec(struct timespec *,
							      struct timespec *, bool);

# define timespec_add(X, Y, Z)		_Generic((X),						\
						 unsigned long long int: timespec_add_usec,	\
						 struct timespec *: timespec_add_timespec)(X, Y, Z)
/*
**	timespec_sub.c
*/
void					timespec_sub_usec(struct timespec *,
							  unsigned long long int, bool);
void					timespec_sub_timespec(struct timespec *,
							      struct timespec *, bool);

# define timespec_sub(X, Y, Z)		_Generic((X),						\
						 unsigned long long int: timespec_sub_usec,	\
						 struct timespec *: timespec_sub_timespec)(X, Y, Z)
/*
**	timespec_cmp.c
*/
bool					timespec_is_lower(struct timespec *,
							  struct timespec *);
bool					timespec_is_greater(struct timespec *,
							    struct timespec *);
bool					timespec_is_equal(struct timespec *,
							  struct timespec *);
/*
**	timespec_utils.c
*/
struct timespec				*timespec_now();
struct timespec				*timespec_init(struct timespec *);
void					timespec_update(struct timespec *);
void					timespec_release(struct timespec *);
/*
**	timsepec_lib.c
*/
struct timespec				*timespec_usec_to_timespec(unsigned long long int);
struct timespec				*timespec_time_to_timespec_ptr(time_t *);
struct timespec				*timespec_time_to_timespec_cp(time_t);
struct timespec				*timespec_tm_to_timespec_cp(struct tm);
struct timespec				*timespec_tm_to_timespec_ptr(struct tm *);

# define timespec_convert(X)		_Generic((X),						\
						 time_t *: timespec_time_to_timespec_ptr,	\
						 time_t: timespec_time_to_timespec_cp,		\
						 struct tm *: timespec_tm_to_timespec_ptr,	\
						 struct tm: timespec_tm_to_timespec_cp,		\
						 unsigned long long int: timespec_usec_to_timespec)(X)

#endif /* !TIMESPEC_LIB_H_ */
