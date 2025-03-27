#ifndef CLASSSTORYBOARD
#define CLASSSTORYBOARD

#include "ClassStoryboard.h"

#pragma region TStoryBoard

// -----------------------------------------------------
// CLASS TStoryBoard
// -----------------------------------------------------
TStoryBoard::TStoryBoard(TFmxObject* Owner, EMode2D3D mode) {
	if (mode == EMode2D3D::fl2D) {
		D2 = new TStoryBoard2D(Owner);
		D3 = NULL;
		PMode = mode;
	} else
	if (mode == EMode2D3D::fl3D) {
		D3 = new TStoryBoard3D(Owner);
		D2 = NULL;
		PMode = mode;
	} else
		PMode = EMode2D3D::flNone;
}

TStoryBoard::~TStoryBoard(void) {
	if (PMode == EMode2D3D::fl2D) {
		delete D2;
	} else
	if (PMode == EMode2D3D::fl3D) {
		delete D3;
	}
}

void __fastcall TStoryBoard::SBDragDropBegin(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y) {
	if (PMode == EMode2D3D::fl2D)
		D2->SBDragDropBegin(Sender, Button, Shift, X, Y);
	if (PMode == EMode2D3D::fl3D)
		D3->SBDragDropBegin(Sender, Button, Shift, X, Y);
}

void __fastcall TStoryBoard::Expand(bool expcol) {
//	if (PMode == EMode2D3D::fl2D)
//		D2->Expand(expcol);
	if (PMode == EMode2D3D::fl3D)
		D3->Expand(expcol);
}

void __fastcall TStoryBoard::SetMode(EMode2D3D mode) {
	// Set mode, or Swap 2D <> 3D
	if (PMode != mode) {
		if ( (mode == EMode2D3D::fl3D) && GPUReady ) {
			if (PMode == EMode2D3D::fl2D) {
				// Bascule 2D vers 3D
			}
			// Ok pour 3D
			PMode = mode;
		} else {
			// Mode 2D
			if (PMode == EMode2D3D::fl2D) {
				// Bascule 3D vers 2D
			}
			PMode = EMode2D3D::fl2D;
		}
	}
}

bool __fastcall TStoryBoard::GetGPUReady(void) {
	return true;
}

double __fastcall TStoryBoard::GetScaleMax(void) {
	if (PMode == EMode2D3D::fl2D)
		return D2->ScaleMax;
	else
		return D3->ScaleMax;
}

void __fastcall TStoryBoard::SetScaleMax(double scalemax) {
	if (PMode == EMode2D3D::fl2D)
		D2->ScaleMax = scalemax;
	if (PMode == EMode2D3D::fl3D)
		D3->ScaleMax = scalemax;
}

bool __fastcall TStoryBoard::GetGridVisible(void) {
	if (PMode == EMode2D3D::fl2D)
		return D2->GridVisible;
	else
		return D3->GridVisible;
}

void __fastcall TStoryBoard::SetGridVisible(bool visible) {
	if (PMode == EMode2D3D::fl2D)
		D2->GridVisible = visible;
	if (PMode == EMode2D3D::fl3D)
		D3->GridVisible = visible;
}

bool __fastcall TStoryBoard::GetGridSnap(void) {
	if (PMode == EMode2D3D::fl2D)
		return D2->GridSnap;
	else
		return D3->GridSnap;
}

void __fastcall TStoryBoard::SetGridSnap(bool snap) {
	if (PMode == EMode2D3D::fl2D)
		D2->GridSnap = snap;
	if (PMode == EMode2D3D::fl3D)
		D3->GridSnap = snap;
}

#pragma end_region

#endif
