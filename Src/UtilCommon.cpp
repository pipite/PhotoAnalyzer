#ifndef UTILCOMMON
#define UTILCOMMON

#include "UtilCommon.h"
#include "stdlib.h"

#ifdef __cplusplus
//   int max(int value1, int value2){
//	  return ( (value1 > value2) ? value1 : value2);
//   }
//   int min(int value1, int value2){
//	  return ( (value1 < value2) ? value1 : value2);
//   }
	double dmax(double value1, double value2){
		return ( (value1 > value2) ? value1 : value2);
	}
	double dmin(double value1, double value2){
		return ( (value1 < value2) ? value1 : value2);
	}
#endif

EDragSelect VDragSelect;

UnicodeString PConfigFileName;
bool ForceDump;
unsigned Verbose;
UnicodeString RootPath;


TAlphaColor __fastcall QueryVisualColor(double mini, double maxi, double value, TColor cmini, TColor cmaxi) {
	unsigned red = 0x00;
	unsigned green = 0x00;
	unsigned blue = 0x00;
	double p;
	int rmini, gmini, bmini;
	int rmaxi, gmaxi, bmaxi;

	bmini = (cmini >> 16) & 0xFF;
	gmini = (cmini >> 8) & 0xFF;
	rmini = cmini & 0xFF;

	bmaxi = (cmaxi >> 16) & 0xFF;
	gmaxi = (cmaxi >> 8) & 0xFF;
	rmaxi = cmaxi & 0xFF;

	if (value >= maxi) {
		return cmaxi;
	} else if (value <= mini) {
		return cmini;
	} else {
		p = (value - mini) / (maxi - mini);
		blue = (unsigned)((double)bmini + p * ((double)bmaxi - (double)bmini));
		green = (unsigned)((double)gmini + p * ((double)gmaxi - (double)gmini));
		red = (unsigned)((double)rmini + p * ((double)rmaxi - (double)rmini));
	}
	return (TAlphaColor) 0xff000000 | RGB(red, green, blue);
}

TAlphaColor __fastcall QueryIndiceColor(double value) {
	return QueryVisualColor(1500.0, 2100.0, value, TColor(255), TColor(65280));
}

UnicodeString __fastcall ExposureTimeFormat(double exposuretime) {
	if (exposuretime > 0.0 && exposuretime < 1.0)
		return Uprintf(L"1/%.0f", 1 / exposuretime);
	else if (exposuretime >= 1)
		return Uprintf(L"%0.1f", exposuretime);
	else
		return L"n/a";
}

UnicodeString __fastcall ApertureFormat(double aperture) {
	if (aperture > 0)
		return Uprintf(L"f%.1f", aperture);
	else
		return L"n/a";
}

UnicodeString __fastcall FocaleFormat(double focale) {
	if (focale > 0)
		return Uprintf(L"%.0fmm", focale);
	else
		return L"n/a";
}

UnicodeString __fastcall FocusDistanceFormat(double focusdistance, bool bracket) {
	if (bracket) {
		if (focusdistance == INFINI) {
			return L"(inf)";
		} else {
			if (focusdistance > MACROLIMIT) {
				if (focusdistance < 10) {
					return Uprintf(L"(%.3fm)", focusdistance);
				} else if (focusdistance < 100) {
					return Uprintf(L"(%.2fm)", focusdistance);
				} else if (focusdistance < 1000) {
					return Uprintf(L"(%.1fm)", focusdistance);
				} else if (focusdistance >= 1000) {
					return Uprintf(L"(%.0fm)", focusdistance);
				}
			} else {
				return L"(Macro)";
			}
		}
	} else {
		if (focusdistance == INFINI) {
			return L"inf";
		} else {
			if (focusdistance > MACROLIMIT) {
				if (focusdistance < 10) {
					return Uprintf(L"%.3fm", focusdistance);
				} else if (focusdistance < 100) {
					return Uprintf(L"%.2fm", focusdistance);
				} else if (focusdistance < 1000) {
					return Uprintf(L"%.1fm", focusdistance);
				} else if (focusdistance >= 1000) {
					return Uprintf(L"%.0fm", focusdistance);
				}
			} else {
				return L"Macro";
			}
		}
	}
	return L"";
}

UnicodeString __fastcall ExposureFormat(double exposure, TLgs *lgs) {
	return Uprintf(L"%+.2f %s", exposure, lgs->QueryKey(L"Exposure.EV").w_str());
}

UnicodeString __fastcall IsoFormat(double iso) {
	if (iso > 0)
		return Uprintf(L"%.0f ISO", iso);
	else
		return L"n/a";
}

UnicodeString __fastcall RemoveStr(UnicodeString str, UnicodeString toremove) {
	unsigned i;

	i=1;
	while (i!=0) {
		i = str.Pos(toremove);
		if (i!=0) str.Delete(i,1);
	}
	return str.Trim();
}
UnicodeString __fastcall RemoveEol(UnicodeString str) {
	unsigned i;

	str = RemoveStr(str, "\n");
	i=1;
	while (i!=0) {
		i = str.Pos("; ");
		if (i!=0) str.Delete(i+1,1);
	}
	return str;
}

unsigned __fastcall PointCount(UnicodeString str) {
	unsigned i, j;

	i=1; j=0;
	while (i!=0) {
		i = str.Pos(".");
		if (i!=0) {
			str.Delete(i,1);
			j++;
		}
	}
	return j;
}

// Conversion UnicodeString en char*
char* __fastcall U2c(UnicodeString U) {
	return AnsiString(U).c_str();
}

// Conversion char * en UnicodeString
UnicodeString __fastcall C2u(char *C) {
	return UnicodeString(C);
}

// Conversion const char * en UnicodeString
UnicodeString __fastcall Cc2u(const char *Cc) {
	return UnicodeString(Cc);
}

UnicodeString __fastcall SpecialTrim(UnicodeString s) {
	s = s.Trim();
	if ( s.SubString(s.Length(),1) == L"." ) {
		s.Delete(s.Length(),1);
	}
	return s;
}

void __fastcall SetConfigFileName(UnicodeString *configfilename) {
	PConfigFileName = *configfilename;
}

unsigned __fastcall FFCount(FILE *cfp, const char *tomatch, const char *stop1, const char *stop2, char *str1, char *str2) {
	unsigned ftmp;
	unsigned count = 0;
	ftmp = ftell(cfp);

	strcpy(str2, "");
	while (1) {
		if (fgets(str1, 1999, cfp) == NULL)
			break;
		sscanf(str1, "%s", str2);
		if (!strcmp(str2, stop1))
			break;
		if (!strcmp(str2, stop2))
			break;
		if (!strcmp(str2, tomatch))
			count++;
	}
	fseek(cfp, ftmp, SEEK_SET);
	return count;
}

unsigned __fastcall FFUnsigned(FILE *cfp, unsigned jump, char *str1) {
	unsigned i;
	for (i = 0; i < jump; i++)
		fscanf(cfp, "%s", str1);
	return(unsigned)atoi(str1);
};

int __fastcall FFInt(FILE *cfp, unsigned jump, char *str1) {
	unsigned i;
	for (i = 0; i < jump; i++)
		fscanf(cfp, "%s", str1);
	return(int)atoi(str1);
};

double __fastcall FFDouble(FILE *cfp, unsigned jump, char *str1) {
	unsigned i;
	for (i = 0; i < jump; i++)
		fscanf(cfp, "%s", str1);
	return(double)atof(str1);
};

unsigned short __fastcall FFUnsignedShortHexa(FILE *cfp, unsigned jump, char *str1) {
	unsigned i;
	for (i = 0; i < jump; i++)
		fscanf(cfp, "%s", str1);
	return(unsigned short)strtol(str1, NULL, 0);
};

unsigned __fastcall FFUnsignedHexa(FILE *cfp, unsigned jump, char *str1) {
	unsigned i;
	for (i = 0; i < jump; i++)
		fscanf(cfp, "%s", str1);
	return(unsigned)strtol(str1, NULL, 0); ;
};

bool __fastcall FFBool(FILE *cfp, unsigned jump, char *str1) {
	unsigned i;
	for (i = 0; i < jump; i++)
		fscanf(cfp, "%s", str1);
	return(bool)atoi(str1);
};

UnicodeString __fastcall FFQuoteString(FILE *cfp, unsigned jump, char *str1) {
	unsigned i;
	char c;
	for (i = 0; i < jump - 1; i++)
		fscanf(cfp, "%s", str1);
	i = 0;
	fscanf(cfp, "%c", &c);
	while (c != '"')
		fscanf(cfp, "%c", &c);
	fscanf(cfp, "%c", &c);
	while (c != '"') {
		str1[i++] = c;
		fscanf(cfp, "%c", &c);
	}
	str1[i] = '\0';
	return SpecialTrim(C2u(str1));
}

UnicodeString __fastcall FFBracketString(FILE *cfp, unsigned jump, char *str1) {
	unsigned i;
	char c;
	for (i = 0; i < jump - 1; i++)
		fscanf(cfp, "%s", str1);
	i = 0;
	fscanf(cfp, "%c", &c);
	while (c != '{')
		fscanf(cfp, "%c", &c);
	fscanf(cfp, "%c", &c);
	while (c != '}') {
		str1[i++] = c;
		fscanf(cfp, "%c", &c);
	}
	str1[i] = '\0';
	return SpecialTrim(C2u(str1));
}

UnicodeString __fastcall FFString(FILE *cfp, unsigned jump, char *str1) {
	unsigned i;
	for (i = 0; i < jump; i++)
		fscanf(cfp, "%s", str1);
	return SpecialTrim(C2u(str1));
}

UnicodeString __fastcall FFNextString(FILE *cfp, unsigned jump, char *str1) {
	unsigned ftmp;
	unsigned i;
	ftmp = ftell(cfp);
	for (i = 0; i < jump; i++)
		fscanf(cfp, "%s", str1);
	fseek(cfp, ftmp, SEEK_SET);
	return SpecialTrim(C2u(str1));
}

UnicodeString __fastcall FFStringUntilEqual(FILE *cfp, char *str1) {
	unsigned i;
	char c;
	i = 0;
	fscanf(cfp, "%c", &c);
	while (c != '=') {
		str1[i++] = c;
		fscanf(cfp, "%c", &c);
	}
	str1[i] = '\0';
	return SpecialTrim(C2u(str1));
}

UnicodeString __fastcall FFStringUntilPoint(FILE *cfp, char *str1) {
	unsigned i;
	char c;
	i = 0;
	fscanf(cfp, "%c", &c);
	while (c != '.') {
		str1[i++] = c;
		fscanf(cfp, "%c", &c);
	}
	str1[i] = '\0';
	return SpecialTrim(C2u(str1));
}

bool __fastcall FFGotoSection(FILE *cfp, const char *section, char *str1) {
	strcpy(str1, "");
	while (1) {
		if (strstr(str1, section))
			return true;
		if (fgets(str1, MAXLEN, cfp) == 0)
			return false;
	}
}

bool __fastcall FFWriteTmpUntilSection(FILE *cfp, FILE *cfptmp, char *section, char *str1) {
	strcpy(str1, "");
	while (1) {
		if (strstr(str1, section))
			return true;
		if (fgets(str1, MAXLEN, cfp) == 0)
			return false;
		fputs(str1, cfptmp);
	}
}

bool __fastcall FFWriteTmpEnd(FILE *cfp, FILE *cfptmp, char *str1) {
	if (fgets(str1, MAXLEN, cfp) == 0)
		return false;
	while (!strchr(str1, '[')) {
		if (fgets(str1, MAXLEN, cfp) == 0)
			return false;
	}
	fputs(str1, cfptmp);
	while (fgets(str1, MAXLEN, cfp) != 0)
		fputs(str1, cfptmp);
	return true;
}

unsigned short __fastcall Sget2(unsigned char *c, unsigned pos, int *ByteOrder) {
	if (*ByteOrder == 0x4949)
		return c[pos + 0] | c[pos + 1] << 8;
	else
		return (unsigned short) (c[pos + 0] << 8 | c[pos + 1]);
}

unsigned __fastcall Sget4(unsigned char *c, unsigned pos, int *ByteOrder) {
	if (*ByteOrder == 0x4949)
		return c[pos] | c[pos + 1] << 8 | c[pos + 2] << 16 | c[pos + 3] << 24;
	else
		return c[pos] << 24 | c[pos + 1] << 16 | c[pos + 2] << 8 | c[pos + 3];
}

unsigned char __fastcall Get1(FILE *ifp) {
	unsigned char c[1];

	fread(c, 1, 1, ifp);
	return c[0];
}

unsigned short __fastcall Get2(FILE *ifp, int *ByteOrder) {
	unsigned char str[2] = {
		0xff, 0xff
	};
	fread(str, 1, 2, ifp);
	return Sget2(str, 0, ByteOrder);
}

unsigned __fastcall Get4(FILE *ifp, int *ByteOrder) {
	unsigned char str[4] = {
		0xff, 0xff, 0xff, 0xff
	};
	fread(str, 1, 4, ifp);
	return Sget4(str, 0, ByteOrder);
}

float __fastcall int_to_float(int i) {
	union {
		int i;
		float f;
	}u;
	u.i = i;
	return u.f;
}

double __fastcall GetURational(FILE *ifp, SURational *rational, int *ByteOrder) {
	(*rational).Numerator = Get4(ifp, ByteOrder);
	(*rational).Denominator = Get4(ifp, ByteOrder);
	if ((*rational).Denominator != 0)
		return(double)(*rational).Numerator / (double)(*rational).Denominator;
	return 0xFFFFFFFF;
}

double __fastcall GetSRational(FILE *ifp, SSRational *rational, int *ByteOrder) {
	(*rational).Numerator = (signed int)(signed int)Get4(ifp, ByteOrder);
	(*rational).Denominator = (signed int)Get4(ifp, ByteOrder);
	if ((*rational).Denominator != 0)
		return(double)(*rational).Numerator / (double)(*rational).Denominator;
	return 0xFFFFFFFF;
}

unsigned __fastcall GetStringLenZeroTerminal(FILE *ifp) {
	unsigned sv2, count;
	char c;

	sv2 = ftell(ifp);
	count = 0;
	while (1) {
		count++;
		c = (char) fgetc(ifp);
		if (c == EOF || c == '\0')
			break;
	}
	fseek(ifp, sv2, SEEK_SET);
	count--;
	return count;
}

double __fastcall GetReal(FILE *ifp, int type, int *ByteOrder) {
	union {
		char c[8];
		double d;
	}u;
	unsigned int d, n;
	signed int h;
	int i, rev;

	switch(type) {
	case 1:
		return(unsigned char)Get1(ifp);
	case 6:
		return(signed char)Get1(ifp);
	case 3:
		return(unsigned short)Get2(ifp, ByteOrder);
	case 4:
		return(unsigned int)Get4(ifp, ByteOrder);
	case 5:
		d = (unsigned int)Get4(ifp, ByteOrder);
		n = (unsigned int)Get4(ifp, ByteOrder);
		if (n == 0)
			return(unsigned int)0;
		return(double)d / (double)n;
	case 7:
	case 8:
		return(signed short)Get2(ifp, ByteOrder);
	case 9:
		return(signed int)Get4(ifp, ByteOrder);
	case 10:
		u.d = (signed int)Get4(ifp, ByteOrder);
		h = (signed int)Get4(ifp, ByteOrder);
		if (h == 0)
			return(signed int)0;
		return u.d / h;
	case 11:
		return int_to_float(Get4(ifp, ByteOrder));
	case 12:
		rev = 7 * ((*ByteOrder == 0x4949) == (ntohs(0x1234) == 0x1234));
		for (i = 0; i < 8; i++)
			u.c[i ^ rev] = (char) fgetc(ifp);
		return u.d;
	default:
		return fgetc(ifp);
	}
}

unsigned short __fastcall GetSizeOf(unsigned short *type) {
	switch(*type) {
	case 1: // .....1      unsigned char (0 à 255)
	case 2: // ...???      ASCII a zero terminal (longueur variable)
	case 6: // .....1      char (-128 à 127)
	case 7: // ...???      indéfini (longueur variable)
		return 1;
	case 3: // .....2      unsigned short (0 à 65535)
	case 8: // .....2      signed short (-32768 à 32767)
		return 2;
	case 4: // .....4      int (0 à 4294967295)
	case 9: // .....4      unsigned int (-2147483648 à 2147483647)
	case 11: // ....4      float (-3.4*10-38 à 3.4*10+38)
		return 4;
	case 5: // ...2x4      fraction non signée (unsigned int=numérateur; unsigned int=denominateur)
	case 10: // ..2x4      fraction signée (int=numérateur; int=denominateur)
	case 12: // ....8      double (-1.7*10-308 à 1.7*10+308)
	case 13: // ....8      offset d'un sous repertoire
		return 8;
	default:
		*type = 0;
		return 1;
	}
}

#endif



