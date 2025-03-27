#ifndef UTILCOMMONH
#define UTILCOMMONH

#include <stdlib.h>
#include <stdio.h>

#include <FMX.Layouts.hpp>

#include "ClassLgs.h"

#define Uprintf UnicodeString().sprintf
#define TOFF(ptr) ((char *)(&(ptr)) - (char *)th)

#define VERSION "2017 01 16"
#define MAXSTR          2000
#define MAXLEN          256
#define ISOLIMIT        800
#define MACROLIMIT	   	0.02
#define INFINI          987654321.0
#define NGINCREMENT     1.3
#define NGHSYNC         0.70
#define NGHSYNCCORRECT  32  // 32 fois moins de lumière entre 1/250 et 1/8000
#define NGLIMIT         500
#define MAXPOINTSFOCUS  25

#define IMAGESIZE       120.0
#define IMAGESEPARATOR  2;
#define CNEPER 2.71828182845904523536

#ifdef __cplusplus
   int max (int a, int b);
   int min (int a, int b);
   double dmax (double a, double b);
   double dmin (double a, double b);
#endif


typedef struct {
	unsigned Numerator;
	unsigned Denominator;
}SURational;

typedef struct {
	signed int Numerator;
	signed int Denominator;
}SSRational;

enum class EDragSelect {flSingle, flAllSelected};

extern EDragSelect VDragSelect;

extern UnicodeString  PConfigFileName;
extern bool           ForceDump;
extern unsigned		  Verbose;
extern UnicodeString  RootPath;

TAlphaColor    __fastcall QueryVisualColor(double mini, double maxi, double value, TColor cmini, TColor cmaxi);
TAlphaColor    __fastcall QueryIndiceColor(double value);
UnicodeString  __fastcall ExposureTimeFormat(double exposuretime);
UnicodeString  __fastcall ApertureFormat(double aperture);
UnicodeString  __fastcall FocaleFormat(double focale);
UnicodeString  __fastcall FocusDistanceFormat(double focusdistance, bool bracket);
UnicodeString  __fastcall ExposureFormat(double exposure, TLgs *lgs);
UnicodeString  __fastcall IsoFormat(double iso);

UnicodeString __fastcall  RemoveStr(UnicodeString str, UnicodeString toremove);
UnicodeString  __fastcall RemoveEol(UnicodeString str);
unsigned 	   __fastcall PointCount(UnicodeString str);
char*          __fastcall U2c(UnicodeString U);
UnicodeString  __fastcall C2u(char *C);
UnicodeString  __fastcall Cc2u(const char *Cc);
UnicodeString  __fastcall SpecialTrim(UnicodeString s);
float          __fastcall int_to_float(int i);

void           __fastcall SetConfigFileName(UnicodeString *configfilename);

unsigned       __fastcall FFCount(FILE *cfp, const char *tomatch, const char *stop1, const char *stop2, char *str1, char *str2);
unsigned       __fastcall FFUnsigned(FILE *cfp, unsigned jump, char *str1);
int            __fastcall FFInt(FILE *cfp, unsigned jump, char *str1);
double         __fastcall FFDouble(FILE *cfp, unsigned jump, char *str1);
unsigned short __fastcall FFUnsignedShortHexa(FILE *cfp, unsigned jump, char *str1);
unsigned       __fastcall FFUnsignedHexa(FILE *cfp, unsigned jump, char *str1);
bool           __fastcall FFBool(FILE *cfp, unsigned jump, char *str1);
UnicodeString  __fastcall FFQuoteString(FILE *cfp, unsigned jump, char *str1);
UnicodeString  __fastcall FFBracketString(FILE *cfp, unsigned jump, char *str1);
UnicodeString  __fastcall FFString(FILE *cfp, unsigned jump, char *str1);
UnicodeString  __fastcall FFNextString(FILE *cfp, unsigned jump, char *str1);
UnicodeString  __fastcall FFStringUntilEqual(FILE *cfp, char *str1);
UnicodeString  __fastcall FFStringUntilPoint(FILE *cfp, char *str1);
bool           __fastcall FFGotoSection(FILE *cfp, const char *section, char *str1);
bool           __fastcall FFWriteTmpUntilSection(FILE *cfp, FILE *cfptmp, char *section, char *str1);
bool           __fastcall FFWriteTmpEnd(FILE *cfp, FILE *cfptmp, char *str1);

unsigned short __fastcall Sget2(unsigned char *c, unsigned pos, int *ByteOrder);
unsigned       __fastcall Sget4(unsigned char *c, unsigned pos, int *ByteOrder);
unsigned char  __fastcall Get1(FILE *ifp);
unsigned short __fastcall Get2(FILE *ifp, int *ByteOrder);
unsigned       __fastcall Get4(FILE *ifp, int *ByteOrder);

double         __fastcall GetURational(FILE *ifp, SURational *rational, int *ByteOrder);
double         __fastcall GetSRational(FILE *ifp, SSRational *rational, int *ByteOrder);
unsigned       __fastcall GetStringLenZeroTerminal(FILE *ifp);
double         __fastcall GetReal(FILE *ifp, int type, int *ByteOrder);
unsigned short __fastcall GetSizeOf(unsigned short *type);

#endif

