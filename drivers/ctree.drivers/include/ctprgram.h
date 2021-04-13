#ifndef ctFeatDYNPARTRUL
typedef union {
	LONG    	yInt;
	pTEXT   	yText;
	CTPRTYPE 	yRule;
	CTPRCALEND	yCal;
} YYSTYPE;
#define STRCONST	257
#define INTCONST	258
#define HEXCONST	259
#define BCDCONST	260
#define FLOATCONST	261
#define DATECONST	262
#define IDENTIFIER	263
#define SDK	264
#define INTEGER	265
#define FLOAT	266
#define DATE	267
#define BCD	268
#define INTERVAL	269
#define FORMAT	270
#define ARRAY	271
#define FIXED	272
#define STRING	273
#define BINARY	274
#define YEAR	275
#define QUARTER	276
#define MONTH	277
#define WEEK	278
#define DAY	279
#define SYSTIME	280
#define CTPR_TIME	281
#define YYYYMMDD	282
#define YYMMDD	283
#define YYYY_MM_DD	284
#define YY_MM_DD	285
#define EXISTING	286
#define FIRST	287
#define BEG_RAWNO	288
extern YYSTYPE yylval;
#endif /*~ ctFeatDYNPARTRUL */
/* end of ctprgram.h */
