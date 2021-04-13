#ifdef DH_JAVA_SP
#include "os_java.hxx"
#endif

#include "rds_env.hxx"
#include "rsstypes.hxx"
#include "hm.hxx"
#include "rdsprocs.hxx"
#include "rss_hdl.hxx"
#include "sql_da.hxx"
#include "rss_env.hxx"
#include "ssm.hxx"
#include "auth.hxx"
#include "dt_misc.hxx"

#include "sqlucode.h"

#ifdef DH_ODBC_INT
#include "odbci.hxx"
#endif

#ifdef DH_JAVA_SP
#include "xec_spro.hxx"
#endif 

/* DC560 Begin - Changes for viewing the query execution plan */
#include "qep_proc.hxx"
/* DC560 End - Changes for viewing the query execution plan */

#include "i18n_env.hxx"  // DC427
#include        "mbcs_wcs.hxx"  // DC587

#include "ctdbsdk.hpp"
#include "stub_std.hxx"

typedef status_t (*ctstp) (fldl_val_t *, fc_result_set_t**, sql_proccolinfolist_t *, rds_env_t *);

#ifdef ctSQL_BUILTIN_PROC
extern dh_char_t *GetStaticProcEntry (dh_u16_t entry);
extern void *RegisterStaticProc(dh_char_t *name, BOOL has_result_set, BOOL has_return_value, ctstp fncexe, ctstp fncopn = NULL, ctstp fncfetch = NULL, ctstp fnccls=NULL);
extern CTDBRET RegisterProcParams (void *list, dh_char_t *column, typeid_t datatype, sql_proccoltype_t argtype, dh_i32_t width, dh_i16_t scale, dh_boolean nullflag);
#endif
