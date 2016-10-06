
/* some useful utilities */


#include "utilities.h"

#include <sys/time.h>

/* internal variables and functions for timer */
static double _last_time = -1.0;
static double _get_time(void)
{
  struct timeval tv;
  struct timezone tz;

  gettimeofday(&tv,&tz);
  double systime = tv.tv_sec;
  systime += ((double) tv.tv_usec)/1000000.0;
  return systime;
}

/* internal variables and functions for pseudo random numbers */

static const int _RNG_IA = 16807;
static const int _RNG_IM = 2147483647;
static const int _RNG_IQ = 127773;
static const int _RNG_IR = 2836;
static const double _RNG_AM = 1.0/2147483647.0;
static int _RNG_seed = -1;

/* exported API */

/* start the stopwatch */
void start_timer(void)
{
  _last_time = _get_time();
}

/* fortran versions */
void start_timer_(void)
{
  start_timer();
}

void start_timer__(void)
{
  start_timer();
}

/* return time in seconds since start */
double get_timer(void)
{
  if (_last_time > 0.0) {
    double _this_time = _get_time();
    return _this_time - _last_time;
  } else return 0.0;
}

/* fortran versions */
void get_timer_(double *retval)
{
  if (retval)
    *retval = get_timer();
}

void get_timer__(double *retval)
{
  get_timer_(retval);
}

/************************************************/

/* Park/Miller pseudo random number generator */

void init_random(int seed)
{
  if (seed > 0) {
    _RNG_seed = seed;
  } else {
    _RNG_seed = (int) (_get_time() * 100.0);
  }
}

/* uniformly distributed random number */

double get_random(void)
{
  int k;

  if (_RNG_seed < 0)
    init_random(0);

  k = _RNG_seed / _RNG_IQ;
  _RNG_seed = _RNG_IA * (_RNG_seed - k*_RNG_IQ) - _RNG_IR*k;
  
  if (_RNG_seed < 0)
    _RNG_seed += _RNG_IM;

  return _RNG_AM * (double) _RNG_seed;
}

/* fortran versions */

void init_random_(int *seed)
{
  if (seed)
    init_random(*seed);
  else
    init_random(0);
}

void init_random__(int *seed)
{
  init_random_(seed);
}


void get_random_(double *retval)
{
  if (retval)
    *retval = get_random();
}
void get_random__(double *retval)
{
  get_random_(retval);
}
