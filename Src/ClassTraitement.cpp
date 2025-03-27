#ifndef CLASSTRAITEMENT
#define CLASSTRAITEMENT

#include "ClassTraitement.h"

TBrightness::TBrightness(void) {
}
TBrightness::~TBrightness(void) {
}

void __fastcall TBrightness::Modify(TBitmap *bmsrc, TBitmap *bmdest, int value) {
//	unsigned x, y, c, r, g, b;
//	TBitmapData bds, bdd;

//	Form1->WorkStart();
//	if (PBitmap != NULL)
//		delete PBitmap;
//	PBitmap = new TBitmap(bmsrc->Width, bmsrc->Height);
//	bmsrc->Map(TMapAccess::ReadWrite,bds);
//	PBitmap->Map(TMapAccess::ReadWrite,bdd);
//
//	for (x = 0; x < (unsigned) bmsrc->Width; x++) {
//		for (y = 0; y < (unsigned) bmsrc->Height; y++) {
//			if (value>0) {
//				c = bds.GetPixel(x,y) & 0xffffff;
//				r = min(255,value + ((c & 0xff0000) >> 16));
//				g = min(255,value + ((c & 0x00ff00) >> 8));
//				b = min(255,value + (c & 0x0000ff));
//			} else {
//				c = bds.GetPixel(x,y) & 0xffffff;
//				r = max(0,value + ((c & 0xff0000) >> 16));
//				g = max(0,value + ((c & 0x00ff00) >> 8));
//				b = max(0,value + (c & 0x0000ff));
//			}
//			bdd.SetPixel(x,y,0xff000000 + (r << 16) + (g << 8) + b);
//		}
//	}
//
//	bmdest->Assign(PBitmap);
//	PBitmap->Unmap(bdd);
//	delete PBitmap;
//	bmsrc->Unmap(bds);
//	Application->HandleMessage();
//	Form1->WorkStop();
}

#endif
