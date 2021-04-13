
/*
** local cancel of ctDBGSEMCNT redefines
*/

#undef ctsemrqs
#undef ctsemwat

#ifdef ctMUTZRO
#undef ctmutrqs
#endif

#ifdef ctSEMBLK
#undef ctblkrqs
#undef ctblkwat
#endif

#ifdef ctSEMTIM
#undef cttimrqs
#undef cttimwat
#endif

/* end of ctdsem.h */
