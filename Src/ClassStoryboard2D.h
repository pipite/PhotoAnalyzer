#ifndef CLASSSTORYBOARD2DH
#define CLASSSTORYBOARD2DH

#include <FMX.Controls.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Types.hpp>

#include <FMX.ExtCtrls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Layers3D.hpp>
#include <System.Rtti.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Colors.hpp>
#include <FMX.Filter.Effects.hpp>
#include <FMX.Effects.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Ani.hpp>
#include <stdlib.h>
#include <vector>

using namespace std;

class TStoryImage2D;
class TStoryBoard2D;
class TStoryGroup2D;

#include "ClassPhoto.h"
#include "ClassScandisk.h"
#include "UtilCommon.h"

#pragma region TStoryImage2D

// -----------------------------------------------------
// CLASS TStoryImage2D
// -----------------------------------------------------
class TStoryImage2D : public TImage {
	TStoryBoard2D *StoryBoard2D;

	void __fastcall ImageDblClick(TObject *Sender);
public:
	TThumbPanel* ThumbPanel;

	__fastcall TStoryImage2D(TFmxObject* Owner, TThumbPanel* thumbpanel, const TPointF &Point, TStoryBoard2D *storyboard2D);
	__fastcall ~TStoryImage2D(void);

};

#pragma end_region

#pragma region TStoryGroup2D

// -----------------------------------------------------
// CLASS TStoryGroup2D
// -----------------------------------------------------
class TStoryGroup2D : public TPanel {
	TStoryBoard2D *StoryBoard2D;
	int PIndex;

	//int __fastcall GetCount(void);
	void __fastcall SetIndex(int AIndex);
	void __fastcall AddInListImage2D(TStoryImage2D *storyimage2D);
	void __fastcall RemoveFromListImage2D(TStoryImage2D *storyimage2D);

public:
	vector<TStoryImage2D*>VSGListImage2D;

	__fastcall TStoryGroup2D(TFmxObject* Owner, TPointF *point, TStoryBoard2D *storyboard2D);
	__fastcall ~TStoryGroup2D(void);

	int __fastcall Add(TStoryImage2D* storyimage2D);
	void __fastcall SGMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, bool &Handled);

	//__declspec(property(get = GetCount))int Count;
	__property int Index = {read = PIndex, write = SetIndex};
};

#pragma end_region

#pragma region TStoryBoard2D

// -----------------------------------------------------
// CLASS TStoryBoard2D
// -----------------------------------------------------
class TStoryBoard2D : public TPanel {
	TObject  *DragObject;
	TControl *MoveObject;
	TPointF  MovePoint;
	bool     MoveFlag;

	TObject* __fastcall ImageIntersect(TStoryImage2D *source);

	void     __fastcall AddInListImage2D(TStoryImage2D *storyimage2D);
	void     __fastcall AddInListGroup2D(TStoryGroup2D *storygroup2D);
	void     __fastcall RemoveFromListImage2D(TStoryImage2D *storyimage2D);
	void     __fastcall RemoveFromListGroup2D(TStoryGroup2D *storygroup2D);
	void     __fastcall SetGridVisible(bool visible);
	bool     __fastcall GetGridVisible(void);
	void     __fastcall SetGridSnap(bool visible);
	bool     __fastcall GetGridSnap(void);

public:
	double ScaleMax;
	double ScaleMin;
	std::vector<TStoryGroup2D*>VSBListGroup2D;
	std::vector<TStoryImage2D*>VSBListImage2D;

			 __fastcall TStoryBoard2D(TFmxObject* Owner);
			 __fastcall ~TStoryBoard2D(void);

	void     __fastcall ImageMoveStart(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
	void     __fastcall ImageMoveStop(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
	void     __fastcall ImageMove(TObject *Sender, TShiftState Shift, float X, float Y);
	void     __fastcall SBDragDropBegin(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);

	void     __fastcall SBDragOver(TObject *Sender, const TDragObject &Data, const TPointF &Point, TDragOperation &Accept);
	void     __fastcall SBDragDrop(TObject *Sender, const TDragObject &Data, const TPointF &Point);
	void     __fastcall SBMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, bool &Handled);

	__property bool GridVisible = {read = GetGridVisible, write = SetGridVisible};
	__property bool GridSnap    = {read = GetGridSnap, write = SetGridSnap};
};

#pragma end_region

#endif
