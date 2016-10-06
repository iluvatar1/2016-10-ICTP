
/* some helpful utilities */

#ifdef __cplusplus
extern "C" {
#endif

/* stopwatch prototypes */
void start_timer(void);
double get_timer(void);

/* random number generator */
void init_random(int seed);
double get_random(void);

#ifdef __cplusplus
}
#endif


