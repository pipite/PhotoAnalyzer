#ifndef CLASSSTORYBOARDH
#define CLASSSTORYBOARDH

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


enum class EMode2D3D : int {flNone, fl2D, fl3D};

class TStoryBoard;

#include "ClassPhoto.h"
#include "ClassScandisk.h"
#include "UtilCommon.h"
#include "ClassStoryboard2D.h"
#include "ClassStoryboard3D.h"

#pragma region TStoryBoard

// -----------------------------------------------------
// CLASS TStoryBoard
// -----------------------------------------------------
class TStoryBoard {
	EMode2D3D PMode;

	double __fastcall GetScaleMax(void);
	void   __fastcall SetScaleMax(double scalemax);
	void   __fastcall SetMode(EMode2D3D mode);
	void   __fastcall SetGridVisible(bool visible);
	bool   __fastcall GetGridVisible(void);
	void   __fastcall SetGridSnap(bool visible);
	bool   __fastcall GetGridSnap(void);
	bool   __fastcall GetGPUReady(void);

public:
	TStoryBoard2D *D2;
	TStoryBoard3D *D3;

		   TStoryBoard(TFmxObject* Owner, EMode2D3D mode);
		   ~TStoryBoard(void);

	void   __fastcall SBDragDropBegin(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
	void   __fastcall Expand(bool expcol);

	__property double    ScaleMax    = {read = GetScaleMax, write = SetScaleMax};
	__property EMode2D3D Mode        = {read = PMode, write = SetMode};
	__property bool      GPUReady    = {read = GetGPUReady};
	__property bool      GridVisible = {read = GetGridVisible, write = SetGridVisible};
	__property bool      GridSnap    = {read = GetGridSnap, write = SetGridSnap};
};

#pragma end_region

#endif
