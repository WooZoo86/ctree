/* c-tree Plus Application Header File */

#ifndef CTREEPH
#define CTREEPH

#include "ctstdr.h"
		/* All programs that use c-tree must have
		 * this include statement. it automatically
		 * includes several necessary
		 * header files (including the compiler's
		 * "stdio.h")
		 */
#include "ctoptn.h"
		/* This is your configuration header. There are a number of 
		 * features that are enabled or disabled by settings in this 
		 * header. It should always be included.
		 */
#include "ctaerr.h"
		/* This contains declarations for a number of global variables,
		 * including the error code variables, that you will need 
		 * access to.
		 */				 
#include "ctdecl.h"
		/* This include contains the c-tree Plus function prototypes.
		 * It is important that you include this.
		 */
#include "cterrc.h"
		/* By including this we can use the c-tree
		 * error code mnemonics in our error handling
		 */

		/* We always prefer to use symbolic names
		 * whenever we can, for constants. This
		 * allows us to easily change the constant
		 * throughout the program by just changing
		 * the definition in one place. Here we are
		 * defining the file numbers that we will
		 * use for both the data and the index file.*/

#include "ctv6v7.h" /* c-tree Plus V6 to V7 Compatibility File */

#ifdef ctNOGLOBALS
#ifndef ctPortWINKE_CLIENT

#define MYctWNGV 	((pCTGVAR)(GETCTREE((pTEXT)WCHCTREE())))

#ifdef	uerr_cod
#undef	uerr_cod
#define uerr_cod	((CTERR)(!MYctWNGV ? (CTERR)-1 : MYctWNGV->suerr_cod))
#endif

#ifdef	sysiocod
#undef	sysiocod
#define sysiocod	((CTERR)(!MYctWNGV ? (CTERR)-1 : MYctWNGV->ssysiocod))
#endif

#ifdef	isam_err
#undef	isam_err
#define isam_err	((CTERR)(!MYctWNGV ? (CTERR)-1 : MYctWNGV->sisam_err))
#endif

#ifdef	isam_fil
#undef	isam_fil
#define isam_fil	((FILNO)(!MYctWNGV ? (FILNO)-1 : MYctWNGV->sisam_fil))
#endif

#endif /* ~ctPortWINKE_CLIENT */
#endif /* ctNOGLOBALS */

#endif /* CTREEPH */
/* end of ctree.h */

