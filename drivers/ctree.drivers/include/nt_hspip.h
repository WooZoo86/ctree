/* #define ONLY_GEN */
#define USE_SENTINEL_MESSAGE_CONTROL_HEADER

#include <stdlib.h>
#include <stdio.h>
#include "ntreestd.h"

/*minimum record len (must be greater than 27)*/
#define MIN_LEN 3000
/*maximum record len*/
#define MAX_LEN 5000
/*minimum records per day*/
#define MIN_RECPERDAY 200
/*maximum records per day*/
#define MAX_RECPERDAY 500

/* random seed */
/*#define RAND_SEED time(NULL)*/
#define RAND_SEED 4321



/* do not modify under this line */
#define DATE_LEN 7
#define DESC_LEN 20


#ifdef  USE_SENTINEL_MESSAGE_CONTROL_HEADER
#define SDK_SENTINEL_DATA	"InRq"		/* Signiture text		*/
#define SDK_SENTINEL_LEN	4		/* Signiture Length		*/
#else
#define SDK_SENTINEL_LEN	0
#endif
#define SDK_DATA_LEN		4 		/* Message data Length		*/
#define SDK_HEADER_LEN 		SDK_SENTINEL_LEN + SDK_DATA_LEN		/* SDK_SENTINEL_LEN + SDK_DATA_LEN*/

/* nt_hspip.h */

