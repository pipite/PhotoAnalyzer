#ifndef CLASSPHOTOH
#define CLASSPHOTOH

#include <FMX.TreeView.hpp>

class TPhoto;

#include "ClassAnalys.h"
#include "ClassIfds.h"
#include "ClassTagMap.h"
#include "ClassDiagnostic.h"

class TPhoto {
	void          __fastcall DisplayIfdsExpert(TTreeView *TreeView);
	void          __fastcall DisplayIfdsShort(TTreeView *TreeView);
	void          __fastcall DisplayIfdsUser(TTreeView *TreeView);
	UnicodeString __fastcall GetInfo(void);

public:
	TTagMap       *TagMap;
	TIfds         *Ifds;
	TAnalys       *Analys;
	DDiagnostic   *Diagnostic;
	TLgs          *Lgs;
	unsigned      Width;
	unsigned      Heigth;
	unsigned      ThumbOffset;
	unsigned      ThumbLength;
	unsigned      PreviewOffset;
	unsigned      PreviewLength;
	unsigned      Rotate;
	UnicodeString Path;
	UnicodeString Format;

				  TPhoto(TTagMap *tagmap, TLgs *lgs);
				  ~TPhoto(void);

	void          __fastcall DisplayIfds(TTreeView *TreeView);
	void          __fastcall AssignAnalysData(void);
	void          __fastcall Compute(UnicodeString *fullname);

	// Interface avec Ifds / MapData
	double        __fastcall QueryDataValue(UnicodeString MapDataCaption);
	double        __fastcall QueryDataCalcValue(UnicodeString MapDataCaption);
	bool          __fastcall QueryDataValid(UnicodeString MapDataCaption);
	UnicodeString __fastcall QueryDataCaption(UnicodeString MapDataCaption);

	__property UnicodeString Info = {read = GetInfo};
};

#endif

