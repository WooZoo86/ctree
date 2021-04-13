/*~****************************************/
#ifdef FAIRJOB_HELPER
/* 
The following section defined the Job Helper Function. This function is 
strategically called from key locations in the engine in order to facilitate an 
easy centralized place by which debugger breakpoints can be added.
*/

/* Location codes form the FairJobHelper function */


/*^****************************************/
/*  
fcJOBHELPER_LOC_EMAIL_PARSE: ..\sdk\Xtras\ctree.samples\jobmgmt\fcgen\src\FcGenLLS_ctdb.c
You are now inside of SDKWriteDataBase() function which is reading entry's from a memory Q and 
processing them for entry into the JOBQ data file.
*/
#define fcJOBHELPER_LOC_EMAIL_PARSE	1	

/*^****************************************/
/*  
fcJOBHELPER_LOC_CTSRVR_LAUNCH: ..\ctreeAPI\ctree\source\ctsrvr.c
You are now inside of main(). Here is the location where the job management 
system is checked by the server's mainline.
*/
#define fcJOBHELPER_LOC_CTSRVR_LAUNCH	2
/*~****************************************/


/*^****************************************/
/*  
fcJOBHELPER_LOC_CTJOB_MAIN_LAUNCH_EACH_THREAD: ..\ctreeAPI\ctree\source\ctjobs.c

Here we are in ctjob_main(), looping thru all the defined jobs we have found in 
the ctsjobsf[] array. We are about the launch a thread for a job definition. If 
there are multiple JOB_QUEUE_INFO keywords in ctsrvr.cfg, then we will see this 
spot for each one.

*/
#define fcJOBHELPER_LOC_CTJOB_MAIN_LAUNCH_EACH_THREAD	3
/*~****************************************/


/*^****************************************/
/*  
fcJOBHELPER_LOC_CTJOBS_TOP_OF_THREAD: ..\ctreeAPI\ctree\source\ctjobs.c
Here we are at the top ctjobs() Thread. This function will parse out the token names and the call CTUSER().
*/
#define fcJOBHELPER_LOC_CTJOBS_TOP_OF_THREAD	4
/*~****************************************/

/*^****************************************/
/*  
fcJOBHELPER_LOC_CTUSER_BEFORE_LOAD_LIB: ..\ctreeAPI\ctree\source\ctsctu_a.c	
Here, we are in CTUSER() and are about to load the dynamic library.
*/
#define fcJOBHELPER_LOC_CTUSER_BEFORE_LOAD_LIB	5
/*~****************************************/

/*^****************************************/
/*  
fcJOBHELPER_LOC_CTUSER_BEFORE_PROC_ADDRESSES: ..\ctreeAPI\ctree\source\ctsctu_a.c	
Here, we are in CTUSER() and are about to GetProcAddress.
*/
#define fcJOBHELPER_LOC_CTUSER_BEFORE_PROC_ADDRESSES	6
/*~****************************************/

/*^****************************************/
/*  
fcJOBHELPER_LOC_CTUSER_CALL_DLL_ENTRYPOINT: ..\ctreeAPI\ctree\source\ctsctu_a.c	
Here, we have just loaded the JOB DLL and are about to call its DLL entry point function
*/
#define fcJOBHELPER_LOC_CTUSER_CALL_DLL_ENTRYPOINT	7
/*~****************************************/


/*^****************************************/
/*  
fcJOBHELPER_LOC_CTUSER_CALL_DLL_ENTRYRETURN: ..\ctreeAPI\ctree\source\ctsctu_a.c	
Here, we just returned from the DLL entry point function.
*/
#define fcJOBHELPER_LOC_CTUSER_CALL_DLL_ENTRYRETURN	8
/*~****************************************/

#endif /* FAIRJOB_HELPER */
/*~**************************************************/



/*^**************************************************/
#if (defined( __JOBDBASE_H__ ) || defined(__MTLOG_C__))

/* Here our naming convensions are based on the IP address of the machine */

#define HOST_MACHINE_000_LOCALHOST		"localhost"
#define HOST_MACHINE_021_RAYSDELLV9		"rays21"	/* Rays Primary Develoment Machine */
#define HOST_MACHINE_217_LEON			"leo"		/* Windows Gen Machine */
#define HOST_MACHINE_086_AIX_4_3		"aix43"		/* AIX aix43 3 4 001557214C00 */
#define HOST_MACHINE_000_AIX_5_1		"aix51"		/* unknown */
#define HOST_MACHINE_088_AIX_5_2		"aix52"		/* AIX aix52 2 5 004247DC4C00 */
#define HOST_MACHINE_072_AIX_5_3		"aix53"		/* AIX AIX53 3 5 0003520F4C00 */
#define HOST_MACHINE_182_AIX_6_1		"p5aix61"	/* AIX p5aix61 1 6 00040D8AD300 */

#define HOST_MACHINE_212_HPUX_IA		"hpuxitan"	/* HP-UX itanium2 B.11.31 U ia64 2460296906 unlimited-user license */	
#define HOST_MACHINE_081_HPUX_RISC		"hp92"		/* HP-UX hp92 B.11.11 U 9000/800 518706507 unlimited-user license */

#define HOST_MACHINE_212_LINUX_IA		"linuxitan"	/* */
#define HOST_MACHINE_227_LINUX_2_4_X86		"iln7"		/* Linux iln7 2.4.2-2 #1 Sun Apr 8 20:41:30 EDT 2001 i686 unknown */
#define HOST_MACHINE_117_LINUX_2_6__X64		"centos4x64"	/* Linux centos4x64.faircom.com 2.6.9-78.0.5.ELsmp #1 SMP Wed Oct 8 07:06:30 EDT 2008 x86_64 x86_64 x86_64 GNU/Linux */
#define HOST_MACHINE_112_LINUX_2_6__X86		"centos4x86"	/* Linux centos4x86.faircom.com 2.6.9-67.0.22.EL #1 Wed Jul 23 17:17:45 EDT 2008 i686 i686 i386 GNU/Linux */
#define HOST_MACHINE_183_LINUX_P5_64		"p5rhel4"	/* Linux p5rhel4 2.6.9-89.0.7.EL #1 SMP Wed Aug 5 14:05:23 EDT 2009 ppc64 ppc64 ppc64 GNU/Linux*/

#define HOST_MACHINE_141_OSX_10_3		"mike-g4mac"	/* Darwin mike-g4mac.faircom.com 7.9.0 Darwin Kernel Version 7.9.0: Wed Mar 30 20:11:17 PST 2005; root:xnu/xnu-517.12.7.obj~1/RELEASE_PPC  Power Macintosh powerpc */
#define HOST_MACHINE_144_OSX_10_4		"g4dual800"	/* Darwin g4dual800.faircom.com 8.11.0 Darwin Kernel Version 8.11.0: Wed Oct 10 18:26:00 PDT 2007; root:xnu-792.24.17~1/RELEASE_PPC Power Macintosh powerpc */
#define HOST_MACHINE_046_OSX_10_5		"osxsrv"	/* Darwin osxsrv.faircom.com 9.5.0 Darwin Kernel Version 10.5.0: Wed Sep  3 11:31:44 PDT 2008; root:xnu-1228.7.58~1/RELEASE_PPC Power Macintosh */
#define HOST_MACHINE_169_OSX_10_6		"rayssnowmac"	/* Darwin rayssnowmac.faircom.com 10.3.0 Darwin Kernel Version 10.3.0: Fri Feb 26 11:58:09 PST 2010; root:xnu-1504.3.12~1/RELEASE_I386 i386 */


#define HOST_MACHINE_116_SOLARIS10_X64		"sol10x64"	/* SunOS sol10x64 5.10 Generic_127128-11 i86pc i386 i86pc */

#define OLD_ONES
#ifdef  OLD_ONES
#define HOST_MACHINE_097_SOLARIS8_SPARC		"sol7"		/* SunOS solaris 5.8 Generic_117350-08 sun4u sparc SUNW,Ultra-4 */
#define HOST_MACHINE_099_SOLARIS10_SPARC	"sol10"		/* SunOS sol10 5.10 Generic_127127-11 sun4u sparc SUNW,Ultra-4 */
#endif 

#define HOST_MACHINE_140_SOLARIS8_SPARC		"sol8-v240"	/* SunOS sol8-v240 5.8 Generic_117000-05 sun4u sparc SUNW,Sun-Fire-V240 */
#define HOST_MACHINE_149_SOLARIS10_SPARC	"sol10-v240"	/* SunOS sol10-v240 5.10 Generic_141444-09 sun4u sparc SUNW,Sun-Fire-V240 */
#define HOST_MACHINE_204_SOLARIS9_X86		"sol9x86"	/* SunOS sol9x86 5.9 Generic_117172-07 i86pc i386 i86pc */

#define HOST_MACHINE_084_SCO_6_X86		"unixware"	/* SCO_SV sco6 5 6.0.0 i386 */
#define HOST_MACHINE_106_QNXRTP_6		"qnxrtp6"	/* QNX qnxrtp 6.4.0 2008/10/21-11:10:39EDT x86pc x86 */

/* AIX p5aix61 1 6 00040D8AD300 */


#ifdef mtPortGEN_w32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_217_LEON
#endif
  
#ifdef mtPortGEN_x64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_217_LEON
#endif
 
#ifdef mtPortGEN_ia64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_217_LEON
#endif
 
#ifdef mtPortGEN_aix6164
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_182_AIX_6_1
#endif

#ifdef mtPortGEN_aix6132
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_182_AIX_6_1
#endif
 
 
#ifdef mtPortGEN_aix5332
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_072_AIX_5_3
#endif
 
#ifdef mtPortGEN_aix5364
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_072_AIX_5_3
#endif
 
#ifdef mtPortGEN_aix5232
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_088_AIX_5_2
#endif
 
#ifdef mtPortGEN_aix5264
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_088_AIX_5_2
#endif
 
#ifdef mtPortGEN_aix5132
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_000_AIX_5_1
#endif
 
#ifdef mtPortGEN_aix5164
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_000_AIX_5_1
#endif
 
#ifdef mtPortGEN_aix4332
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_086_AIX_4_3
#endif
 
#ifdef mtPortGEN_hp911risc32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_081_HPUX_RISC
#endif
 
#ifdef mtPortGEN_hp911risc64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_081_HPUX_RISC
#endif
 
#ifdef mtPortGEN_hp911itan32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_212_HPUX_IA
#endif
 
#ifdef mtPortGEN_hp911itan64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_212_HPUX_IA
#endif

#ifdef mtPortGEN_linux24_32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_227_LINUX_X86
#endif

#ifdef mtPortGEN_linux24_64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_227_LINUX_2_4_X86
#endif

#ifdef mtPortGEN_linux26_32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_112_LINUX_2_6__X86
#endif
 
#ifdef mtPortGEN_linux26_64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_117_LINUX_2_6__X64
#endif
 
#ifdef mtPortGEN_linux26_ia64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_212_LINUX_IA
#endif

#ifdef mtPortGEN_linux26_p564
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_183_LINUX_P5_64
#endif
 
#ifdef mtPortGEN_osx10_3_32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_141_OSX_10_3
#endif
 
#ifdef mtPortGEN_osx10_4_u32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_144_OSX_10_4
#endif

#ifdef mtPortGEN_osx10_4_32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_144_OSX_10_4
#endif

#ifdef mtPortGEN_osx10_4_64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_144_OSX_10_4
#endif
 
#ifdef mtPortGEN_osx10_5_u32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_046_OSX_10_5
#endif

#ifdef mtPortGEN_osx10_5_32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_046_OSX_10_5
#endif
 
#ifdef mtPortGEN_osx10_4_64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_144_OSX_10_4
#endif
 
#ifdef mtPortGEN_osx10_5_64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_046_OSX_10_5
#endif
 
#ifdef mtPortGEN_osx10_6_32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_169_OSX_10_6
#endif

#ifdef mtPortGEN_osx10_6_u32
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_169_OSX_10_6
#endif

#ifdef mtPortGEN_osx10_6_64
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_169_OSX_10_6
#endif
 
#ifdef mtPortGEN_sco632  
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_084_SCO_6_X86
#endif
 
#ifdef mtPortGEN_sol832
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_140_SOLARIS8_SPARC
#endif
 
#ifdef mtPortGEN_sol864
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_140_SOLARIS8_SPARC
#endif
 
#ifdef mtPortGEN_sol932
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_140_SOLARIS8_SPARC
#endif
 
#ifdef mtPortGEN_sol964
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_140_SOLARIS8_SPARC
#endif
 
#ifdef mtPortGEN_sol1032
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_149_SOLARIS10_SPARC
#endif
 
#ifdef mtPortGEN_sol1064
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_149_SOLARIS10_SPARC
#endif
 
#ifdef mtPortGEN_solx1032
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_116_SOLARIS10_X64
#endif
 
#ifdef mtPortGEN_solx1064
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_116_SOLARIS10_X64
#endif

#ifdef mtPortGEN_solx932
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_204_SOLARIS9_X86
#endif

#ifdef mtPortGEN_qnxrtp6
#define CURRENT_HOST_MACHINE 			 HOST_MACHINE_106_QNXRTP_6
#endif

#endif /* __JOBDBASE_H__ */
/*~**************************************************/
 
/****************************************************/

/* end of ctjobs2.h */
