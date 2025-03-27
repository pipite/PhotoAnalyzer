#ifndef CLASSTRAITEMENTH
#define CLASSTRAITEMENTH

#include <FMX.Types.hpp>

class TBrightness;

#include "utilcommon.h"
#include "main.h"

class TBrightness {
	TBitmap *PBitmap;

	public:

	TBrightness(void);
	~TBrightness(void);

	void __fastcall Modify(TBitmap *bmsrc, TBitmap *bmdest, int value);
};


#endif

