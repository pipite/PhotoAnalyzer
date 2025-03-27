#ifndef CLASSTIFF
#define CLASSTIFF

#include "ClassTiff.h"

#pragma region TTiff
// -----------------------------------------------------
// CLASS TTiff
// -----------------------------------------------------
void __fastcall TTiff::TiffSet(unsigned short *ntag, unsigned short tag, unsigned short type, int count, int val) {
	STiffTag *tt;
	int c;

	tt = (STiffTag*)(ntag + 1) + (*ntag)++;
	tt->tag = tag;
	tt->type = type;
	tt->count = count;
	if ( (type < 3) && (count <= 4) )
		for (c = 0; c < 4; c++)
			tt->val.c[c] = char (val >> (c << 3));
	else if ( (type == 3) && (count <= 2) )
		for (c = 0; c < 2; c++)
			tt->val.s[c] = short (val >> (c << 4));
	else
		tt->val.i = val;
}

void __fastcall TTiff::TiffHead(STiffHdr *th) {
	int c; //psize = 0;
	struct tm *t;
	time_t timestamp;

	memset(th, 0, sizeof*th);
	th->order = htonl(0x4d4d4949) >> 16;
	th->magic = 42;
	th->ifd = 10;

	TiffSet(&th->ntag, 270,   2, 512, TOFF(th->desc));
	TiffSet(&th->ntag, 271,   2,  64, TOFF(th->make));
	TiffSet(&th->ntag, 272,   2,  64, TOFF(th->model));

	TiffSet(&th->ntag, 274,   3,   1, 1);

	TiffSet(&th->ntag, 282,   5,   1, TOFF(th->rat[0]));
	TiffSet(&th->ntag, 283,   5,   1, TOFF(th->rat[2]));
	TiffSet(&th->ntag, 284,   3,   1, 1);
	TiffSet(&th->ntag, 296,   3,   1, 2);
	TiffSet(&th->ntag, 305,   2,  32, TOFF(th->soft));
	TiffSet(&th->ntag, 306,   2,  20, TOFF(th->date));
	TiffSet(&th->ntag, 315,   2,  64, TOFF(th->artist));
	TiffSet(&th->ntag, 34665, 4,   1, TOFF(th->nexif));
//	if (psize)
//		TiffSet(&th->ntag, 34675, 7, psize, sizeof *th);
	TiffSet(&th->nexif, 33434, 5,  1, TOFF(th->rat[4]));
	TiffSet(&th->nexif, 33437, 5,  1, TOFF(th->rat[6]));
	TiffSet(&th->nexif, 34855, 3,  1, 0); // Iso;
	TiffSet(&th->nexif, 37386, 5,  1, TOFF(th->rat[8]));

	th->rat[0] = th->rat[2] = 300;
	th->rat[1] = th->rat[3] = 1;
	for (c = 0; c < 6; c++)
		th->rat[4 + c] = 1000000;
	th->rat[4] *= 0; // ExposureTime;
	th->rat[6] *= 0; // Aperture;
	th->rat[8] *= 0; // Focale;
	strncpy(th->desc, "", 512);
	strncpy(th->make, /* Maker */ "", 64);
	strncpy(th->model, /* Model */ "", 64);
	strncpy(th->soft, /* "Photo Analizer" */ "",32);
	t = localtime(&timestamp);
	sprintf(th->date, "%04d:%02d:%02d %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	strncpy(th->artist, "", 64);
}

void __fastcall TTiff::LoadBitmapOffset(TBitmap * bitmap, TPhoto *photo, int taille) {
	unsigned short exif[5];
	STiffHdr th;
	unsigned char header[2] = {0xff, 0xd8};
	int to, tl;

	TFileStream* f = new TFileStream(photo->Path, fmOpenRead);
	if (f != NULL) {
		if (taille == 0) {
			to = photo->ThumbOffset;
			tl = photo->ThumbLength;
		} else if (taille == 1) {
			to = photo->PreviewOffset;
			tl = photo->PreviewLength;
		}
		TMemoryStream* m = new TMemoryStream;

		m->Write(header, 2);
		memcpy(exif, "\xff\xe1  Exif\0\0", 10);
		exif[1] = htons(8+sizeof th);
		m->Write(exif, sizeof exif);

		TiffHead(&th);
		m->Write(&th, sizeof th);
		f->Seek(to + 2, 0);
		m->CopyFrom(f, tl - 2);

		m->Position = 0;
		bitmap->LoadFromStream(m);

		if (photo->Rotate == 6)
			bitmap->Rotate(90);
		if (photo->Rotate == 8)
			bitmap->Rotate(270);

		delete m;
		delete f;
	}
}

void __fastcall TTiff::LoadThumbnail(TBitmap *bitmap, TPhoto *photo, TStoryBoard *storyboard) {
	if (FileExists(photo->Path)) {
		if ((photo->ThumbOffset != 0) && (photo->ThumbLength != 0) && (photo->Format == ".cr2"))
			LoadBitmapOffset(bitmap, photo, 0);
		else
			bitmap->LoadThumbnailFromFile(photo->Path, float(storyboard->ScaleMax*IMAGESIZE), float(storyboard->ScaleMax*IMAGESIZE), false);
	}
}

void __fastcall TTiff::LoadPreview(TBitmap *bitmap, TPhoto *photo) {
	if (FileExists(photo->Path)) {
		if ((photo->PreviewOffset != 0) && (photo->PreviewLength != 0) && (photo->Format == ".cr2"))
			LoadBitmapOffset(bitmap, photo, 1);
		else
			bitmap->LoadFromFile(photo->Path);
	}
}

#pragma end_region

#endif
