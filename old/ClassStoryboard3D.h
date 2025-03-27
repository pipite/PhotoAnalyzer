#ifndef CLASSSTORYBOARD3DH
#define CLASSSTORYBOARD3DH

#include <FMX.Controls.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Types.hpp>

#include <FMX.ExtCtrls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Objects3D.hpp>
#include <FMX.Viewport3D.hpp>
#include <FMX.Types.hpp>
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

class TArcBall3D;
class TStoryImage3D;
class TStoryBoard3D;
class TStoryGroup3D;

#include "ClassPhoto.h"
#include "ClassScandisk.h"
#include "UtilCommon.h"

enum class EExpandMode {ExpX, ExpY, ExpZ};

#pragma region TStoryImage3D

// -----------------------------------------------------
// CLASS TStoryImage3D
// -----------------------------------------------------
class TStoryImage3D : public TImage3D {
	TStoryBoard3D *StoryBoard3D;

	void __fastcall SIMouseMove(TObject *Sender, TShiftState Shift, float X, float Y);
	void __fastcall SIMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall SIMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir);
	void __fastcall SIDblClick(TObject *Sender);

	bool __fastcall GetIsInGroup(void);
	void __fastcall SnapToGrid(void);


public:
	TFloatAnimation *AnimX;
	TFloatAnimation *AnimY;
	TFloatAnimation *AnimZ;
	TThumbPanel* ThumbPanel;
	TStoryGroup3D *StoryGroup3D;

	__fastcall TStoryImage3D(TFmxObject* Owner, TThumbPanel* thumbpanel, const TVector3D &vector, TStoryBoard3D *storyboard3D);
	__fastcall ~TStoryImage3D(void);

	bool __fastcall IsHit(TPointF xy);
	void __fastcall Move(void);
	void __fastcall DoClick(void);
	void __fastcall DoClickAndMove(void);
	void __fastcall DoDblClick(void);
	void __fastcall DoMove(TShiftState Shift, float X, float Y);
	void __fastcall DoMouseUpAfterMove(void);
	void __fastcall DoDragEnd(void);

	__declspec(property(get = GetIsInGroup))bool IsInGroup;
};

#pragma end_region

#pragma region TStoryGroup3D

// -----------------------------------------------------
// CLASS TStoryGroup3D
// -----------------------------------------------------
class TStoryGroup3D : public TImage3D {
	TStoryBoard3D *StoryBoard3D;
	TBitmapAnimation *AnimB;
	TFloatAnimation *AnimH;
	TFloatAnimation *AnimW;
	TFloatAnimation *AnimX;
	TFloatAnimation *AnimY;
	TSphere *Sphere;
	TCone *ConeR;

	int PIndex;
	float SphereSize;
	double StepZCollapse;
	double StepZExpand;
	double Step;
	double Duration;
	bool PIsExpanded;
	EExpandMode ExpandMode;


	int __fastcall GetCount(void);
	void __fastcall SetIsExpanded(bool expanded);
	void __fastcall Anime(int i, int j);
	void __fastcall AnimeFirst(int i);
	void __fastcall SGMouseMove(TObject *Sender, TShiftState Shift, float X, float Y);
	void __fastcall SGMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall SGMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir);
	void __fastcall SGDblClick(TObject *Sender);
	void __fastcall AddInListImage3D(TStoryImage3D *storyimage3D);
	void __fastcall RemoveFromListImage3D(TStoryImage3D *storyimage3D);
	void __fastcall SGTimer(TObject *Sender);

public:
	std::vector<TStoryImage3D*>VSGListImage3D;

	__fastcall TStoryGroup3D(TFmxObject* Owner, TThumbPanel* thumbpanel, const TVector3D &vector, TStoryBoard3D *storyboard3D);
	__fastcall ~TStoryGroup3D(void);

	void __fastcall Move();
	void __fastcall Last(void);
	void __fastcall Add(TStoryImage3D* storyimage3D);
	void __fastcall Remove(TStoryImage3D* storyimage3D);
	void __fastcall SetIndex(int AIndex);
	void __fastcall SnapToGrid(void);
	void __fastcall DoClick(void);
	void __fastcall DoClickAndMove(void);
	void __fastcall DoDblClick(void);
	void __fastcall DoMove(TShiftState Shift, float X, float Y);
	void __fastcall DoMouseUpAfterMove(void);

	__declspec(property(get = GetCount))int Count;
	__declspec(property(get = PIsExpanded, put = SetIsExpanded))bool IsExpanded;
	__declspec(property(get = PIndex, put = SetIndex))int Index;
};

#pragma end_region

#pragma region TStoryBoard3D

// -----------------------------------------------------
// CLASS TStoryBoard3D
// -----------------------------------------------------
class TStoryBoard3D : public  TViewport3D {
	TFloatAnimation *AnimRY;
	TFloatAnimation *AnimPX;
	TFloatAnimation *AnimPY;
	TFloatAnimation *AnimPZ;
	TLight *Light;

	bool PGridVisible;
	bool PGridSnap;
	TVector3D SphereGrip;
	float PCameraSaveZPos;
	TPointF Down;

	void __fastcall RemoveFromListGroup3D(TStoryGroup3D *storygroup3D);
	TObject* __fastcall ImageIntersect(TStoryImage3D *source);
	void __fastcall SetGridVisible(bool visible);
	bool __fastcall GetGridVisible(void);
	void __fastcall SetGridSnap(bool visible);
	bool __fastcall GetGridSnap(void);
	void __fastcall DoG3DClick(void);
	void __fastcall DoG3DClickAndMove(TShiftState Shift, float X, float Y);
	void __fastcall DoG3DDblClick(void);
	void __fastcall DoG3DMove(TShiftState Shift, float X, float Y);
	void __fastcall DoG3DMouseUpAfterMove(void);
	void __fastcall DoG3DDragEnd(void);

public:
	TArcBall3D *ArcBall3D;

	bool IsCameraMove;
	bool FlagMouseClick;
	bool FlagMouseDblClick;
	bool FlagMouseDown;
	bool FlagMouseMove;

	bool IsObjectMove;
	TControl *ObjectInMove;

	bool IsStoryImage3DDrag;
	TStoryImage3D *StoryImage3DInDrag;

	TGrid3D *Grid3D;
	TDummy *Boom;
	TVector3D MovePoint;
	TVector3D MoveBoomProj3D;
	TPointF MoveBoomOld2D;

	double ScaleMax;
	double ScaleMin;
	double AnimDuration;
	double GridSize;
	double GridFrequency;

	std::vector<TStoryGroup3D*>VSBListGroup3D;
	std::vector<TStoryImage3D*>VSBListImage3D;

	__fastcall TStoryBoard3D(TFmxObject* Owner);
	__fastcall ~TStoryBoard3D(void);

	void __fastcall Debug(void);
	TPointF __fastcall MousePos(void);
	TPointF __fastcall XyzToXy(TVector3D vector);
	TVector3D __fastcall MouseToXyz(TFmxObject *target3D);
	TVector3D __fastcall XyToXyz(float X, float Y, TFmxObject *target3D);
	TPointF __fastcall QuerySnapPoint(TPointF point);
	void __fastcall BoomMoveStart(TShiftState Shift, float X, float Y);
	void __fastcall BoomMove(TShiftState Shift, float X, float Y);
	void __fastcall CameraWheel(TShiftState Shift, int WheelDelta);
	void __fastcall AddInListImage3D(TStoryImage3D *storyimage3D);
	void __fastcall RemoveFromListImage3D(TStoryImage3D *storyimage3D);
	void __fastcall AddInListGroup3D(TStoryGroup3D *storygroup3D);
	void __fastcall Grid3DMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, TVector3D &RayPos, TVector3D &RayDir);
	void __fastcall SBMouseMove(TObject *Sender, TShiftState Shift, float X, float Y);
	void __fastcall SBDragDropBegin(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall G3DMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir);
	void __fastcall G3DMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir);
	void __fastcall G3DMouseMove(TObject *Sender, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir);
	void __fastcall G3DDblClick(TObject *Sender);
	void __fastcall G3DDragOver(TObject *Sender, const TDragObject &Data, const TPointF &Point, TDragOperation &Accept);
	void __fastcall SBMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall SBMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, bool &Handled);
	void __fastcall AddToGroup(TStoryImage3D *storyimage3D);
	void __fastcall RemoveFromGroup(TStoryGroup3D *storygroup3D, TStoryImage3D *storyimage3D);
	void __fastcall Expand(bool expcol);
	void __fastcall ResetClick(void);
	void __fastcall SetAnim(TFloatAnimation *anim, float val);

	__declspec(property(get = GetGridVisible, put = SetGridVisible))bool GridVisible;
	__declspec(property(get = GetGridSnap, put = SetGridSnap))bool GridSnap;
};

#pragma end_region

#pragma region ArcBall3D

class TArcBall3D : public  TSphere {
	TStoryBoard3D *StoryBoard3D;
	float PRadius;
	float PCoefZoom;
	TVector3D OldGripPos;

	void __fastcall SetRadius(float radius);
	void __fastcall SetIsVisible(bool visible);
	void __fastcall ArcBall3DMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir);
	void __fastcall ArcBall3DMouseMove(TObject *Sender, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir);
	TVector3D __fastcall EyesPos(void);
	TVector3D __fastcall EyesDir(void);
	TVector3D __fastcall BallPos(void);

public:
	__fastcall TArcBall3D(TFmxObject* Owner);
	__fastcall ~TArcBall3D(void);

	TVector3D __fastcall MouseProj3DPlane(void);

	__declspec(property(get = PRadius, put = SetRadius))float Radius;
	__declspec(property(get = Visible, put = SetIsVisible))bool IsVisible;
};

#pragma end_region

#endif
