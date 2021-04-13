#ifndef ctSTDRH
#define ctSTDRH		

#ifndef ct_V90_GENERATION	
#define ct_V90_GENERATION 	/* Ray activated as of v8.27.0 Build(050831) */
#endif

#ifndef ctOPT2H		/* Special ctoptn.h & ctopt2.h include controls */
#define ctOPT2H 	/* Prevent ctopt2.h header in initial ctoptn.h */
#include "ctoptn.h"	/* Compiler Options Header */
#undef	ctOPT2H    	/* Allow ctopt2.h for traditianal ctoptn.h inclusion */
#endif
#include "ctopt1.h" /* OEM & Special Feature definitions		*/
#include "ctcmpl.h" /* Compiler-Operating System Specific definitions 	*/
#include "ctport.h" /* System independent type definitions		*/

#ifdef ctPortNLM
EXTERN int _threadid;
#endif

#ifdef ctPortFAIRCOM_THREADS	/* FairCom's Proprietary Thread Manager */
#include "ctthrd.h"
#endif

#endif /* ctSTDRH */
