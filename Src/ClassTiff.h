#ifndef CLASSTIFFH
#define CLASSTIFFH

#include <FMX.Layouts.hpp>

#include <stdio.h>
#include <time.h>
#include "UtilCommon.h"
#include "ClassPhoto.h"
#include "ClassStoryboard.h"

struct STiffIfd {
	int width, height, bps, comp, phint, offset, flip, samples, bytes;
};

struct STiffTag {
	unsigned short tag, type;
	int count;

	union {
		char c[4];
		short s[2];
		int i;
	} val;
};

struct STiffHdr {
	unsigned short order, magic;
	int ifd;
	unsigned short pad, ntag;
	STiffTag tag[23];
	int nextifd;
	unsigned short pad2, nexif;
	STiffTag exif[4];
	unsigned short pad3, ngps;
	STiffTag gpst[10];
	short bps[4];
	int rat[10];
	unsigned gps[26];
	char desc[512], make[64], model[64], soft[32], date[20], artist[64];
};

class TTiff {
	STiffIfd tiff_ifd[10];
	void __fastcall TiffSet(unsigned short *ntag, unsigned short tag, unsigned short type, int count, int val);
	void __fastcall TiffHead(STiffHdr *th);
	void __fastcall LoadBitmapOffset(TBitmap* bitmap, TPhoto *photo, int taille);

public:
	void __fastcall LoadPreview(TBitmap *bitmap, TPhoto *photo);
	void __fastcall LoadThumbnail(TBitmap *bitmap, TPhoto *photo, TStoryBoard *storyboard);
};
#endif
