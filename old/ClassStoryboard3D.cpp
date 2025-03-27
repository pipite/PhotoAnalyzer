#ifndef CLASSSTORYBOARD3D
#define CLASSSTORYBOARD3D

#include "ClassStoryboard3D.h"
#include "main.h"

#pragma region TArcBall

// -----------------------------------------------------
// CLASS TArcBall
// -----------------------------------------------------
__fastcall TArcBall3D::TArcBall3D(TFmxObject* Owner) : TSphere(Owner) {
//	TBitmap *bm;
	StoryBoard3D = (TStoryBoard3D*) Owner;
	Visible = true;
	PRadius = 3.0;
	PCoefZoom = 1.66;
	RotationAngle->X = 180;
	Parent = Owner;
	SetSize(PRadius*2, PRadius*2, PRadius*2);
	OldGripPos = Vector3D(0, 0, 0, 1);
	Position->Empty();
//	bm = new TBitmap(0, 0);
//	bm->LoadFromFile("G:/Perso/Photo analyzer/sphere2.jpg");
//	Material->Texture->Assign(bm);
//	delete bm;
	Opacity = 0.7;

	OnMouseDown = ArcBall3DMouseDown;
	OnMouseMove = ArcBall3DMouseMove;
}

__fastcall TArcBall3D::~TArcBall3D(void) {
}

void __fastcall TArcBall3D::SetIsVisible(bool visible) {
	Visible = visible;
	if (visible) {
		Position->Vector = StoryBoard3D->Boom->Position->Vector;
		RecalcAbsolute();
	}
}

void __fastcall TArcBall3D::SetRadius(float radius) {
	PRadius = radius;
	SetSize(PRadius*2, PRadius*2, PRadius*2);
}

TVector3D __fastcall TArcBall3D::MouseProj3DPlane(void) {
	TPointF xyscreen;
	TVector3D xyplane;

	xyscreen = StoryBoard3D->AbsoluteToLocal(Application->MainForm->ScreenToClient(Screen->MousePos()));  // XE3: Screen->GetMousePos()
	xyscreen.X = StoryBoard3D->Width / 2 - xyscreen.X;
	xyscreen.Y = StoryBoard3D->Height / 2 - xyscreen.Y;
	xyplane.X = -xyscreen.X * (1 / (-PCoefZoom * StoryBoard3D->Camera->Position->Z));
	xyplane.Y = -xyscreen.Y * (1 / (-PCoefZoom * StoryBoard3D->Camera->Position->Z));
	xyplane.Z = 0.0;

	Form1->Label18->Text = Uprintf(L"Mouse pos  %8.2f,%8.2f", xyscreen.X, xyscreen.Y);
	Form1->Label13->Text = Uprintf(L"Plane pos %8.2f,%8.2f,%8.2f,%8.2f", xyplane.X, xyplane.Y, xyplane.Z, xyplane.W);
	return xyplane;
}

TVector3D __fastcall TArcBall3D::EyesPos(void) {
	return Vector3D(0, 0, StoryBoard3D->Camera->Position->Z, 1);
}

TVector3D __fastcall TArcBall3D::BallPos(void) {
	return Vector3D(0, 0, 0, 1);
}

TVector3D __fastcall TArcBall3D::EyesDir(void) {
	TVector3D v;

	v._op_Subtraction(MouseProj3DPlane(),EyesPos());
	return v.Normalize();
}

void __fastcall TArcBall3D::ArcBall3DMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir) {
	TVector3D tmp;

//	StoryBoard3D->ResetClick();
//	if (Shift.Contains(ssLeft))
//		RayCastSphereIntersect(EyesPos(), EyesDir(), BallPos(), Radius, OldGripPos, tmp);
}

void __fastcall TArcBall3D::ArcBall3DMouseMove(TObject *Sender, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir) {
	TVector3D rot, xrot, yrot, zrot, oldgrippos, newgrippos, v1, v2;
	TQuaternion3D quat;
	float yaw, pitch, roll;

//	if (Shift.Contains(ssLeft)) {
//		RayCastSphereIntersect(EyesPos(), EyesDir(), BallPos(), Radius, newgrippos, v1);
//		Form1->Label16->Text = Uprintf(L"Int Sphere %8.2f,%8.2f,%8.2f,%8.2f,%8.2f", newgrippos.X, newgrippos.Y, newgrippos.Z, newgrippos.W);
//		v1 = Vector3DNormalize(OldGripPos);
//		v2 = Vector3DNormalize(newgrippos);
//		rot = Vector3DNormalize(Vector3DCrossProduct(v1, v2));
//		rot.W = Vector3DAngleCosine(v1, v2);
//		if ((fabs(rot.W) > 0.01) && (Vector3DLength(rot) == 1.0)) {
//			quat = QuaternionFromAngleAxis(rot.W, rot);
//			rot = quat.ImagPart;
//			rot.W = quat.RealPart;
//			pitch = atan2(2 * (rot.Y * rot.Z + rot.W * rot.X), rot.W * rot.W - rot.X * rot.X - rot.Y * rot.Y + rot.Z * rot.Z) * 57.2958;
//			yaw = asin(-2 * (rot.X * rot.Z - rot.W * rot.Y)) * 57.2958;
//			roll = atan2(2 * (rot.X * rot.Y + rot.W * rot.Z), rot.W * rot.W + rot.X * rot.X - rot.Y * rot.Y - rot.Z * rot.Z) * 57.2958;
//			StoryBoard3D->Boom->RotationAngle->X -= pitch;
//			StoryBoard3D->Boom->RotationAngle->Y -= yaw;
//			StoryBoard3D->Boom->RotationAngle->Z -= roll;
//			OldGripPos = newgrippos;
//		}
//	}
}

#pragma end_region

#pragma region TStoryBoard3D

// -----------------------------------------------------
// CLASS TStoryBoard3D
// -----------------------------------------------------
__fastcall TStoryBoard3D::TStoryBoard3D(TFmxObject* Owner) : TViewport3D(Owner) {
	ScaleMax = 4.0;
	ScaleMin = 0.2;
	AnimDuration = 0.3;
	PCameraSaveZPos = -20;
	GridSize = 1000.0;
	GridFrequency = 5.0;
	PGridVisible = true;
	PGridSnap = true;

	ObjectInMove = NULL;
	IsObjectMove = false;
	StoryImage3DInDrag = NULL;
	IsStoryImage3DDrag = false;

	Grid3D = new TGrid3D(NULL);
	Grid3D->Parent = this;
	Grid3D->LineColor = unsigned(0xff303030);
	Grid3D->Width = GridSize;
	Grid3D->Height = GridSize;
	Grid3D->HitTest = true;
	Grid3D->Frequency = GridFrequency;
	//Grid3D->OnDragOver = G3DDragOver;
	Grid3D->OnMouseMove = G3DMouseMove;
	Grid3D->OnMouseDown = G3DMouseDown;
	Grid3D->OnMouseUp = G3DMouseUp;
	Grid3D->OnDblClick = G3DDblClick;

	Align = TAlignLayout::Client;
	Color = TAlphaColors::Black;
	Parent = Owner;

	Boom = new TDummy(NULL);
	Boom->Parent = this;
	Boom->Position->Point = Point3D(0, 0, 0);
	Boom->RotationAngle->Empty();

	Camera = new TCamera(NULL);
	Camera->Parent = Boom;
	Camera->Projection = TProjection::pjCamera;
	UsingDesignCamera = false;
	Camera->ZWrite = false;
	Camera->Position->Point = Point3D(0, 0, PCameraSaveZPos);
	Camera->RotationAngle->Empty();

	Light = new TLight(NULL);
	Light->Parent = Camera;

	AnimPX = new TFloatAnimation(NULL);
	AnimPX->Parent = Boom;
	AnimPX->PropertyName = L"Position.Point.X";
	AnimPX->Enabled = false;
	AnimPX->Duration = AnimDuration;
	AnimPX->StartFromCurrent = true;

	AnimPY = new TFloatAnimation(NULL);
	AnimPY->Parent = Boom;
	AnimPY->PropertyName = L"Position.Point.Y";
	AnimPY->Enabled = false;
	AnimPY->Duration = AnimDuration;
	AnimPY->StartFromCurrent = true;

	AnimPZ = new TFloatAnimation(NULL);
	AnimPZ->Parent = Camera;
	AnimPZ->PropertyName = L"Position.Point.Z";
	AnimPZ->Enabled = false;
	AnimPZ->Duration = AnimDuration;
	AnimPZ->StartFromCurrent = true;

	ArcBall3D = new TArcBall3D(this);

	OnMouseWheel = SBMouseWheel;

	ResetClick();
}

__fastcall TStoryBoard3D::~TStoryBoard3D(void) {
	unsigned int i, j;
	// detruire les images isolées
	// Detruire les groupes
//	if (StoryImage3DInDrag != NULL) {
//		StoryImage3DInDrag->Bitmap = NULL;
//	}
	for (i = 0; i < VSBListGroup3D.size(); i++) {
//		VSBListGroup3D.at(i)->Bitmap = NULL;
		VSBListGroup3D.at(i)->Parent = NULL;
		for (j = 0; j < VSBListGroup3D.at(i)->VSGListImage3D.size(); j++) {
//			VSBListGroup3D.at(i)->VSGListImage3D.at(j)->Bitmap = NULL;
			VSBListGroup3D.at(i)->VSGListImage3D.at(j)->Parent = NULL;
		}
		delete VSBListGroup3D.at(i);
	}
	for (i = 0; i < VSBListImage3D.size(); i++) {
//		VSBListImage3D.at(i)->Bitmap = NULL;
		VSBListImage3D.at(i)->Parent = NULL;
		delete VSBListImage3D.at(i);
	}
	VSBListImage3D.empty();
	VSBListGroup3D.empty();

	delete ArcBall3D;
	delete AnimPX;
	delete AnimPY;
	delete AnimPZ;
	delete Light;
	delete Camera;
	delete Boom;
	delete Grid3D;
}

void __fastcall TStoryBoard3D::Debug(void) {
	// Form1->Label13->Text = Uprintf(L"ImageList = %d", VSBListImage3D.size());
	// Form1->Label14->Text = Uprintf(L"GroupList = %d", VSBListGroup3D.size());
}

void __fastcall TStoryBoard3D::SetAnim(TFloatAnimation *anim, float val) {
	anim->StopAtCurrent();
	anim->StopValue = val;
	anim->Start();
}

bool __fastcall TStoryBoard3D::GetGridVisible(void) {
	return PGridVisible;
}

void __fastcall TStoryBoard3D::SetGridVisible(bool visible) {
	PGridVisible = visible;
	if (visible)
		Grid3D->Frequency = GridFrequency;
	else
		Grid3D->Frequency = GridSize / 2;
}

bool __fastcall TStoryBoard3D::GetGridSnap(void) {
	return PGridSnap;
}

void __fastcall TStoryBoard3D::SetGridSnap(bool snap) {
	PGridSnap = snap;
}

void __fastcall TStoryBoard3D::BoomMoveStart(TShiftState Shift, float X, float Y) {
	MoveBoomOld2D = TPointF(X, Y);
	MoveBoomProj3D = MouseToXyz(Grid3D);
	BoomMove(Shift, X, Y);
}

void __fastcall TStoryBoard3D::BoomMove(TShiftState Shift, float X, float Y) {
	TVector3D v1,v2;
	IsCameraMove = true;
	if (Shift.Contains(ssLeft)) {
		// Pan XY
		ArcBall3D->IsVisible = false;
		MoveBoomProj3D = XyToXyz(MoveBoomOld2D.X, MoveBoomOld2D.Y, Grid3D);
		v1._op_Addition( v2._op_Subtraction(MoveBoomProj3D, MouseToXyz(Grid3D)),Boom->Position->Vector);
		Boom->Position->X = v1.X;
		Boom->Position->Y = v1.Y;
		Boom->Position->Z = v1.Z;
		//Boom->RecalcAbsolute();
		MoveBoomOld2D = MousePos();
	}
	else {
		IsCameraMove = false;
	}
}

TPointF __fastcall TStoryBoard3D::MousePos(void) {
	TPointF xyscreen;

	xyscreen = Screen->MousePos();
	return AbsoluteToLocal(Application->MainForm->ScreenToClient(xyscreen));
}

TVector3D __fastcall TStoryBoard3D::MouseToXyz(TFmxObject *target3D) {
	TPointF xyviewport;

	xyviewport = MousePos();
	return XyToXyz(xyviewport.X, xyviewport.Y, target3D);
}

TVector3D __fastcall TStoryBoard3D::XyToXyz(float X, float Y, TFmxObject *target3D) {
	TPointF xyviewport;
	TVector3D RayDir, RayPos, r;
	TPoint3D HitPos;
	//TVector3D RayDir, RayPos, HitPos;

	xyviewport = TPointF(X, Y);
	if (target3D->ClassNameIs(L"TGrid3D")) {
		((TGrid3D*)(target3D))->Context->Pick(xyviewport.X, xyviewport.Y, TProjection::pjCamera, RayPos, RayDir);
		((TGrid3D*)(target3D))->RayCastIntersect(RayPos, RayDir, HitPos);
		r = HitPos;
	}
	return r;
}

TPointF __fastcall TStoryBoard3D::XyzToXy(TVector3D v) {
	TPoint3D p;

	p = Grid3D->Context->WorldToScreen(TProjection::pjCamera , (TPoint3D)v);
	return TPointF(p.X, p.Y);
}

TPointF __fastcall TStoryBoard3D::QuerySnapPoint(TPointF point) {
	TPointF r;
	if (point.X >= 0)
		r.X = GridFrequency / 2 + (int)(point.X / GridFrequency) * GridFrequency;
	else
		r.X = -GridFrequency / 2 + (int)(point.X / GridFrequency) * GridFrequency;
	if (point.Y >= 0)
		r.Y = GridFrequency / 2 + (int)(point.Y / GridFrequency) * GridFrequency;
	else
		r.Y = -GridFrequency / 2 + (int)(point.Y / GridFrequency) * GridFrequency;
	return r;
}

void __fastcall TStoryBoard3D::Expand(bool expcol) {
	unsigned int i;

	for (i = 0; i < VSBListGroup3D.size(); i++)
		VSBListGroup3D[i]->IsExpanded = expcol;
}

// gestion des listes groupes et images
void __fastcall TStoryBoard3D::AddInListImage3D(TStoryImage3D *storyimage3D) {
	VSBListImage3D.push_back(storyimage3D);
	IsStoryImage3DDrag = false;
	IsObjectMove = false;
}

void __fastcall TStoryBoard3D::AddInListGroup3D(TStoryGroup3D *storygroup3D) {
	VSBListGroup3D.push_back(storygroup3D);
}

void __fastcall TStoryBoard3D::RemoveFromListImage3D(TStoryImage3D *storyimage3D) {
	unsigned int i;
	bool flag;

	flag = false;
	for (i = 0; i < VSBListImage3D.size(); i++) {
		if (flag)
			VSBListImage3D.at(i - 1) = VSBListImage3D.at(i);
		if (VSBListImage3D.at(i) == storyimage3D) {
			flag = true;
		}
	}
	if (flag)
		VSBListImage3D.pop_back();
}

void __fastcall TStoryBoard3D::RemoveFromListGroup3D(TStoryGroup3D *storygroup3D) {
	unsigned int i;
	bool flag;

	flag = false;
	for (i = 0; i < VSBListGroup3D.size(); i++) {
		if (flag)
			VSBListGroup3D.at(i - 1) = VSBListGroup3D.at(i);
		if (VSBListGroup3D.at(i) == storygroup3D) {
//			VSBListGroup3D[i]->Bitmap = NULL;
			delete VSBListGroup3D[i];
			flag = true;
		}
	}
	if (flag)
		VSBListGroup3D.pop_back();
}

void __fastcall TStoryBoard3D::AddToGroup(TStoryImage3D *storyimage3D) {
	unsigned int i;
	TRectF i1, i2;

	if (storyimage3D->Parent->ClassNameIs(L"TGrid3D")) {
		// Intersection avec un groupe
		for (i = 0; i < VSBListGroup3D.size(); i++) {
			i1.left = VSBListGroup3D[i]->Position->X;
			i1.top = VSBListGroup3D[i]->Position->Y;
			i1.bottom = i1.top + VSBListGroup3D[i]->Height;
			i1.right = i1.left + VSBListGroup3D[i]->Width;
			i2.left = storyimage3D->Position->X;
			i2.top = storyimage3D->Position->Y;
			i2.bottom = i2.top + storyimage3D->Height;
			i2.right = i2.left + storyimage3D->Width;
			if (i1.IntersectsWith(i2)) {
				// Ajout dans un groupe existant
				VSBListGroup3D[i]->Add(storyimage3D);
				RemoveFromListImage3D(storyimage3D);
				VSBListGroup3D[i]->Last();
				return;
			}
		}
		// Intersection avec image isolée
		for (i = 0; i < VSBListImage3D.size(); i++) {
			if (VSBListImage3D[i] != storyimage3D) {
				i1.left = VSBListImage3D[i]->Position->X;
				i2.left = storyimage3D->Position->X;
				i1.top = VSBListImage3D[i]->Position->Y;
				i2.top = storyimage3D->Position->Y;
				i1.bottom = i1.top + VSBListImage3D[i]->Height;
				i2.bottom = i2.top + storyimage3D->Height;
				i1.right = i1.left + VSBListImage3D[i]->Width;
				i2.right = i2.left + storyimage3D->Width;
				if (i1.IntersectsWith(i2)) {
					// Création d'un nouveau groupe
					AddInListGroup3D(new TStoryGroup3D(NULL, VSBListImage3D[i]->ThumbPanel, VSBListImage3D[i]->Position->Vector, this));
					VSBListGroup3D[VSBListGroup3D.size() - 1]->Add(VSBListImage3D[i]);
					RemoveFromListImage3D(VSBListImage3D[i]);
					VSBListGroup3D[VSBListGroup3D.size() - 1]->Add(storyimage3D);
					RemoveFromListImage3D(storyimage3D);
					VSBListGroup3D[VSBListGroup3D.size() - 1]->Last();
					return;
				}
			}
		}
	}
}

void __fastcall TStoryBoard3D::RemoveFromGroup(TStoryGroup3D *storygroup3D, TStoryImage3D *storyimage3D) {
	// Separrer l'image du groupe
	AddInListImage3D(storyimage3D);
	storygroup3D->Remove(storyimage3D);
	storyimage3D->Parent = Grid3D;
	storyimage3D->Position->Vector = MouseToXyz(Grid3D);

	storyimage3D->StoryGroup3D = NULL;
	storyimage3D->HitTest = true;
	if (storygroup3D->Count == 1) {
		// Isoler la derniere image du groupe
		AddInListImage3D(storygroup3D->VSGListImage3D[0]);
		storygroup3D->VSGListImage3D[0]->Parent = Grid3D;
		storygroup3D->VSGListImage3D[0]->Position->X = storygroup3D->Position->X;
		storygroup3D->VSGListImage3D[0]->Position->Y = storygroup3D->Position->Y;
		storygroup3D->VSGListImage3D[0]->Position->Z = 0.0;
		storygroup3D->VSGListImage3D[0]->StoryGroup3D = NULL;
		storygroup3D->VSGListImage3D[0]->HitTest = true;
		storygroup3D->Remove(storygroup3D->VSGListImage3D[0]);
		// Detruire le groupe
		RemoveFromListGroup3D(storygroup3D);
	}
}

// -----------------------------------------------------

void __fastcall TStoryBoard3D::CameraWheel(TShiftState Shift, int wheeldelta) {
	PCameraSaveZPos -= wheeldelta / 60;
	SetAnim(AnimPZ, PCameraSaveZPos);
}

void __fastcall TStoryBoard3D::SBMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, bool &Handled) {
	TVector3D normal;
	TObject *obj;
	UnicodeString s;

	obj = ObjectAtPoint(Screen->MousePos())->GetObjectW();
	s = obj->ClassName();
	if (obj->ClassNameIs(L"TStoryImage3D")) {
		if (((TStoryImage3D*)(obj))->IsInGroup) {
			((TStoryImage3D*)(obj))->StoryGroup3D->SetIndex(((TStoryImage3D*)(obj))->StoryGroup3D->Index - (int)(WheelDelta / 120.0));
		}
	}
	else if (obj->ClassNameIs(L"TStoryGroup3D")) {
		((TStoryGroup3D*)(obj))->SetIndex(((TStoryGroup3D*)(obj))->Index - (int)(WheelDelta / 120.0));
	}
	else {
		CameraWheel(Shift, WheelDelta);
	}
}

void __fastcall TStoryBoard3D::SBDragDropBegin(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y) {
	TThumbPanel *tp1;
	// Emeteur DragDrop Capté par un MouseDown sur une TThumbPanel->Image

	ArcBall3D->IsVisible = false;
	if (Button == TMouseButton::mbLeft)
		VDragSelect = EDragSelect::flSingle;
	else if (Button == TMouseButton::mbRight)
		VDragSelect = EDragSelect::flAllSelected;

	if (Sender->ClassName() == L"TImage") {
		// Simuler un Click pour analys
		//((TImage*)(Sender))->DoClick(Sender);
		// Creer TStoryImage3D pour fantome en 3D
		if (((TImage*)(Sender))->Parent->ClassName() == L"TThumbPanel") {
			tp1 = (TThumbPanel*)((TImage*)(Sender))->Parent;
			tp1->DoClick(tp1);
			if (StoryImage3DInDrag != NULL) {
				if (IsStoryImage3DDrag) {
//					StoryImage3DInDrag->Bitmap = NULL;
					delete StoryImage3DInDrag;
				}
			}
			StoryImage3DInDrag = new TStoryImage3D(this, tp1, MouseToXyz(Grid3D), this);
			IsStoryImage3DDrag = true;
		}
	}
}

void __fastcall TStoryBoard3D::G3DDragOver(TObject *Sender, const TDragObject &Data, const TPointF &Point, TDragOperation &Accept) {
	// Passe ici pendant le dragdrop
	Accept = true;
	if (StoryImage3DInDrag != NULL) {
		// XY souris -> repère grille
		StoryImage3DInDrag->Position->Vector = MouseToXyz(Grid3D);
	}
}

void __fastcall TStoryBoard3D::G3DDblClick(TObject *Sender) {
	FlagMouseDblClick = true;
	DoG3DDblClick();
}

void __fastcall TStoryBoard3D::G3DMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir) {
	FlagMouseDown = true;
}

void __fastcall TStoryBoard3D::G3DMouseMove(TObject *Sender, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir) {
	Debug();
	// Passage à la fin d'un dragdrop, et a chaque mouvement dans une image si pas dragdrop
	if (IsStoryImage3DDrag) {
		DoG3DDragEnd();
	}
	else if (IsCameraMove) {
		BoomMove(Shift, X, Y);
	}
	else {
		if (Shift.Contains(ssLeft)) {
			if (FlagMouseDown) {
				if (!FlagMouseClick && !FlagMouseDblClick) {
					FlagMouseClick = true;
					DoG3DClickAndMove(Shift, X, Y);
				}
				else if (FlagMouseClick && !FlagMouseDblClick) {
					FlagMouseMove = true;
					DoG3DMove(Shift, X, Y);
				}
			}
		}
		else
			ResetClick();
	}
}

void __fastcall TStoryBoard3D::G3DMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir) {
	// Passage ici quand fin de move(image), ne passe pas ici a la fin d'un dragdrop
	if (!IsCameraMove) {
		if (!FlagMouseMove && !FlagMouseDblClick)
			DoG3DClick();
		if (FlagMouseMove)
			DoG3DMouseUpAfterMove();
	}
	ResetClick();
}

void __fastcall TStoryBoard3D::ResetClick(void) {
	FlagMouseClick = false;
	FlagMouseDblClick = false;
	FlagMouseDown = false;
	FlagMouseMove = false;
	IsCameraMove = false;
}

void __fastcall TStoryBoard3D::DoG3DClick(void) {
	ArcBall3D->IsVisible = false;
	IsCameraMove = false;
}

void __fastcall TStoryBoard3D::DoG3DClickAndMove(TShiftState Shift, float X, float Y) {
	BoomMoveStart(Shift, X, Y);
}

void __fastcall TStoryBoard3D::DoG3DDblClick(void) {
	ArcBall3D->IsVisible = true;
}

void __fastcall TStoryBoard3D::DoG3DMove(TShiftState Shift, float X, float Y) {
	ArcBall3D->IsVisible = false;
	if (IsObjectMove) {
		if (ObjectInMove->ClassNameIs(L"TStoryImage3D")) {
			((TStoryImage3D*)ObjectInMove)->DoMove(Shift, X, Y);
		}
		else if (ObjectInMove->ClassNameIs(L"TStoryGroup3D")) {
			((TStoryGroup3D*)ObjectInMove)->DoMove(Shift, X, Y);
		}
	}
	else {
		BoomMove(Shift, X, Y);
	}
}

void __fastcall TStoryBoard3D::DoG3DMouseUpAfterMove(void) {
	IsCameraMove = false;
}

void __fastcall TStoryBoard3D::DoG3DDragEnd(void) {
}

#pragma end_region

#pragma region TStoryImage3D

// -----------------------------------------------------
// CLASS TStoryImage3D
// -----------------------------------------------------
__fastcall TStoryImage3D::TStoryImage3D(TFmxObject* Owner, TThumbPanel* thumbpanel, const TVector3D &vector, TStoryBoard3D *storyboard3D) : TImage3D(Owner) {
	AnimX = new TFloatAnimation(NULL);
	AnimX->Parent = this;
	AnimX->PropertyName = L"Position.X";
	AnimX->Enabled = false;
	AnimX->Duration = 0.48;
	AnimX->StartFromCurrent = true;

	AnimY = new TFloatAnimation(NULL);
	AnimY->Parent = this;
	AnimY->PropertyName = L"Position.Y";
	AnimY->Enabled = false;
	AnimY->Duration = 0.48;
	AnimY->StartFromCurrent = true;

	AnimZ = new TFloatAnimation(NULL);
	AnimZ->Parent = this;
	AnimZ->PropertyName = L"Position.Z";
	AnimZ->Enabled = false;
	AnimZ->Duration = 0.48;
	AnimZ->StartFromCurrent = true;

	ThumbPanel = thumbpanel;
	StoryBoard3D = storyboard3D;
	Parent = StoryBoard3D->Grid3D;
	Projection = TProjection::pjCamera;
	Width = ThumbPanel->Bitmap->Width / 100;
	Height = ThumbPanel->Bitmap->Height / 100;
	Bitmap = ThumbPanel->Bitmap;
	Position->Vector = vector;
	RotationAngle->X = 0.0;
	RotationAngle->Y = 0.0;
	RotationAngle->Z = 0.0;

	StoryGroup3D = NULL;

	//OnDragOver = StoryBoard3D->G3DDragOver; // Permet mouvement image pendant dragdrop si souris sur image
	OnMouseDown = SIMouseDown;
	OnLayerMouseMove = SIMouseMove;
	OnLayerMouseUp = SIMouseUp;
	OnDblClick = SIDblClick;
}

__fastcall TStoryImage3D::~TStoryImage3D(void) {
	delete AnimX;
	delete AnimY;
	delete AnimZ;
}

bool __fastcall TStoryImage3D::GetIsInGroup(void) {
	if (StoryGroup3D == NULL)
		return false;
	return true;
}

bool __fastcall TStoryImage3D::IsHit(TPointF xy) {
	TVector3D raydir, raypos;
	TPoint3D p;

	Context->Pick(xy.X, xy.Y, TProjection::pjCamera, raypos, raydir);
	if (RayCastPlaneIntersect(raypos.ToPoint3D(false) , raydir.ToPoint3D(false), AbsolutePosition, AbsoluteDirection, p)) {
		if (!IsInGroup) {
			p.X -= Position->X;
			p.Y -= Position->Y;
		}
		else {
			p.X -= StoryGroup3D->Position->X;
			p.Y -= StoryGroup3D->Position->Y;
		}
		Form1->Label13->Text = Uprintf(L"Position xy = %8.2f, %8.2f, %8.2f", p.X, p.Y, p.Z);
		if ((abs(p.X) <= Width / 2) && (abs(p.Y) <= Height / 2))
			return true;
		else
			return false;
	}
	return false;
}

void __fastcall TStoryImage3D::SnapToGrid(void) {
	TPointF p;
	p = StoryBoard3D->QuerySnapPoint(TPointF(Position->X, Position->Y));
	StoryBoard3D->SetAnim(AnimX, p.X);
	StoryBoard3D->SetAnim(AnimY, p.Y);
}

void __fastcall TStoryImage3D::Move() {
	if (StoryBoard3D->IsObjectMove) {
		((TStoryImage3D*)(StoryBoard3D->ObjectInMove))->Position->Vector = StoryBoard3D->MouseToXyz(StoryBoard3D->Grid3D);
	}
	if (StoryBoard3D->IsStoryImage3DDrag) {
		StoryBoard3D->AddInListImage3D(StoryBoard3D->StoryImage3DInDrag);
		StoryBoard3D->AddToGroup(StoryBoard3D->StoryImage3DInDrag);
	}
}

// -----------------------------------------------------------------

void __fastcall TStoryImage3D::SIDblClick(TObject *Sender) {
	StoryBoard3D->FlagMouseDblClick = true;
	DoDblClick();
}

void __fastcall TStoryImage3D::SIMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir) {
	StoryBoard3D->FlagMouseDown = true;
}

void __fastcall TStoryImage3D::SIMouseMove(TObject *Sender, TShiftState Shift, float X, float Y) {
	// Passage à la fin d'un dragdrop, et a chaque mouvement dans une image si pas dragdrop
	if (StoryBoard3D->IsStoryImage3DDrag) {
		// Fin d'un DragDrop
		DoDragEnd();
	}
	else if (StoryBoard3D->IsCameraMove) {
		StoryBoard3D->BoomMove(Shift, X, Y);
	}
	else {
		if (Shift.Contains(ssLeft)) {
			if (StoryBoard3D->FlagMouseDown) {
				if (!StoryBoard3D->FlagMouseClick && !StoryBoard3D->FlagMouseDblClick) {
					StoryBoard3D->FlagMouseClick = true;
					DoClickAndMove();
				}
			}
			if (StoryBoard3D->FlagMouseClick && !StoryBoard3D->FlagMouseDblClick) {
				StoryBoard3D->FlagMouseMove = true;
				DoMove(Shift, X, Y);
			}
		}
		else
			StoryBoard3D->ResetClick();
	}
}

void __fastcall TStoryImage3D::SIMouseUp(TObject * Sender, TMouseButton Button, TShiftState Shift, float X, float Y) {
	// Passage ici quand fin de move(image), ne passe pas ici a la fin d'un dragdrop
	if (!StoryBoard3D->IsCameraMove) {
		if (!StoryBoard3D->FlagMouseMove && !StoryBoard3D->FlagMouseDblClick)
			DoClick();
		if (StoryBoard3D->FlagMouseMove)
			DoMouseUpAfterMove();
	}
	StoryBoard3D->ResetClick();
}

void __fastcall TStoryImage3D::DoClick(void) {
	StoryBoard3D->ArcBall3D->IsVisible = false;
}

void __fastcall TStoryImage3D::DoClickAndMove(void) {
	StoryBoard3D->ArcBall3D->IsVisible = false;
	if (!IsInGroup) {
		StoryBoard3D->ObjectInMove = (TControl*) this;
		StoryBoard3D->IsObjectMove = true;
	}
	else {
		if (StoryGroup3D->IsExpanded) {
			StoryBoard3D->RemoveFromGroup(StoryGroup3D, this);
			StoryBoard3D->ObjectInMove = (TControl*) this;
			StoryBoard3D->IsObjectMove = true;
		}
		else {
			StoryBoard3D->ObjectInMove = (TControl*) StoryGroup3D;
			StoryBoard3D->IsObjectMove = true;
		}
	}
}

void __fastcall TStoryImage3D::DoDblClick(void) {
	if (IsInGroup)
		StoryGroup3D->IsExpanded = !StoryGroup3D->IsExpanded;
}

void __fastcall TStoryImage3D::DoMove(TShiftState Shift, float X, float Y) {
	// StoryBoard3D->Sphere->Visible = false;
	if (StoryBoard3D->IsObjectMove) {
		if (StoryBoard3D->ObjectInMove->ClassNameIs(L"TStoryImage3D")) {
			Move();
		}
		else if (StoryBoard3D->ObjectInMove->ClassNameIs(L"TStoryGroup3D")) {
			((TStoryGroup3D*)StoryBoard3D->ObjectInMove)->Move();
		}
	}
	else {
		StoryBoard3D->BoomMove(Shift, X, Y);
	}
}

void __fastcall TStoryImage3D::DoMouseUpAfterMove(void) {
	StoryBoard3D->IsObjectMove = false;
	StoryBoard3D->AddToGroup(this);
	if (StoryBoard3D->GridSnap) {
		if (!IsInGroup)
			SnapToGrid();
		else
			StoryGroup3D->SnapToGrid();
	}
}

void __fastcall TStoryImage3D::DoDragEnd(void) {
	Move();
	StoryBoard3D->ResetClick();
	if (!IsInGroup && StoryBoard3D->GridSnap)
		SnapToGrid();
}

#pragma end_region

#pragma region TStoryGroup3D

// -----------------------------------------------------
// CLASS TStoryGroup3D
// -----------------------------------------------------
__fastcall TStoryGroup3D::TStoryGroup3D(TFmxObject * Owner, TThumbPanel * thumbpanel, const TVector3D & vector, TStoryBoard3D * storyboard3D) : TImage3D(Owner) {
	PIndex = 0;
	PIsExpanded = false;
	SphereSize = 0.5;
	StepZCollapse = 0.06;
	StepZExpand = 3.0;
	Step = StepZExpand;
	Duration = 0.4;

	AnimH = new TFloatAnimation(this);
	AnimH->Parent = this;
	AnimH->PropertyName = L"Height";
	AnimH->Enabled = true;
	AnimH->Duration = Duration;
	AnimH->StartFromCurrent = true;

	AnimW = new TFloatAnimation(this);
	AnimW->Parent = this;
	AnimW->PropertyName = L"Width";
	AnimW->Enabled = true;
	AnimW->Duration = Duration;
	AnimW->StartFromCurrent = true;

	AnimX = new TFloatAnimation(NULL);
	AnimX->Parent = this;
	AnimX->PropertyName = L"Position.X";
	AnimX->Enabled = false;
	AnimX->Duration = Duration;
	AnimX->StartFromCurrent = true;

	AnimY = new TFloatAnimation(NULL);
	AnimY->Parent = this;
	AnimY->PropertyName = L"Position.Y";
	AnimY->Enabled = false;
	AnimY->Duration = Duration;
	AnimY->StartFromCurrent = true;

	AnimB = new TBitmapAnimation(this);
	AnimB->Parent = this;
	AnimB->PropertyName = L"Bitmap";
	AnimB->Duration = Duration;

	Sphere = new TSphere(NULL);
	Sphere->Parent = this;
	ConeR = new TCone(NULL);
	ConeR->Parent = Sphere;

	StoryBoard3D = storyboard3D;
	Projection = TProjection::pjCamera;

	Position->Vector = vector;
	Position->Z = -StepZCollapse;
	RotationAngle->X = 0.0;
	RotationAngle->Y = 0.0;
	RotationAngle->Z = 0.0;
	Width = thumbpanel->Bitmap->Width / 100;
	Height = thumbpanel->Bitmap->Height / 100;
	Bitmap = new TBitmap(0, 0);
	Bitmap->Assign(thumbpanel->Bitmap);
	Parent = StoryBoard3D->Grid3D;

	Sphere->Width = SphereSize;
	Sphere->Height = SphereSize;
	Sphere->Depth = SphereSize;
	Sphere->Position->X = (float)(StoryBoard3D->GridFrequency / 2.0) - SphereSize;
	Sphere->Position->Y = (float)(-StoryBoard3D->GridFrequency / 2.0) + SphereSize;
	Sphere->Position->Z = -SphereSize + SphereSize / 5;

	ConeR->Width = SphereSize / 2;
	ConeR->Height = SphereSize / 2;
	ConeR->Depth = SphereSize / 2;
	ConeR->Position->X = SphereSize;
	ConeR->Position->Y = 0;
	ConeR->Position->Z = 0;
	ConeR->RotationAngle->Z = 90.0;

	ExpandMode = EExpandMode::ExpZ;

	VSGListImage3D.empty();

	//OnDragOver = StoryBoard3D->G3DDragOver; // Permet mouvement image pendant dragdrop si souris sur image
	OnMouseDown = SGMouseDown;
	OnLayerMouseMove = SGMouseMove;
	OnLayerMouseUp = SGMouseUp;
	OnDblClick = SGDblClick;
}

__fastcall TStoryGroup3D::~TStoryGroup3D(void) {
	unsigned int i;

	delete ConeR;
	delete Sphere;
	delete AnimH;
	delete AnimW;
	delete AnimX;
	delete AnimY;
	delete AnimB;
	for (i = 0; i < VSGListImage3D.size(); i++) {
		delete VSGListImage3D.at(i);
	}
}

void __fastcall TStoryGroup3D::SnapToGrid(void) {
	TPointF p;
	p = StoryBoard3D->QuerySnapPoint(TPointF(Position->X, Position->Y));
	StoryBoard3D->SetAnim(AnimX, p.X);
	StoryBoard3D->SetAnim(AnimY, p.Y);
}

// gestion de la liste des images
void __fastcall TStoryGroup3D::AddInListImage3D(TStoryImage3D * storyimage3D) {
	VSGListImage3D.push_back(storyimage3D);
}

void __fastcall TStoryGroup3D::RemoveFromListImage3D(TStoryImage3D * storyimage3D) {
	unsigned int i;
	bool flag;

	flag = false;
	for (i = 0; i < VSGListImage3D.size(); i++) {
		if (flag)
			VSGListImage3D.at(i - 1) = VSGListImage3D.at(i);
		if (VSGListImage3D.at(i) == storyimage3D) {
			flag = true;
		}
	}
	if (flag)
		VSGListImage3D.pop_back();
}

void __fastcall TStoryGroup3D::Last(void) {
	Index = Count - 1;
}

void __fastcall TStoryGroup3D::Move(void) {
	if (!IsExpanded)
		Position->Vector = StoryBoard3D->MouseToXyz(StoryBoard3D->Grid3D);
}

void __fastcall TStoryGroup3D::SetIsExpanded(bool expanded) {
	if (PIsExpanded != expanded) {
		PIsExpanded = expanded;
		if (!PIsExpanded)
			Step = StepZCollapse;
		else
			Step = StepZExpand;
		SetIndex(-99);
	}
}

int __fastcall TStoryGroup3D::GetCount(void) {
	return (int) VSGListImage3D.size();
}

void __fastcall TStoryGroup3D::Add(TStoryImage3D * storyimage3D) {
	storyimage3D->Parent = this;
	if (ExpandMode == EExpandMode::ExpZ) {
		StoryBoard3D->SetAnim(storyimage3D->AnimX, 0.0);
		StoryBoard3D->SetAnim(storyimage3D->AnimY, 0.0);
		StoryBoard3D->SetAnim(storyimage3D->AnimZ, VSGListImage3D.size() * Step + StepZCollapse);
	}
	else if (ExpandMode == EExpandMode::ExpX) {
		StoryBoard3D->SetAnim(storyimage3D->AnimX, VSGListImage3D.size() * StoryBoard3D->GridFrequency);
		StoryBoard3D->SetAnim(storyimage3D->AnimY, 0.0);
		StoryBoard3D->SetAnim(storyimage3D->AnimZ, 0.0);
	}
	storyimage3D->StoryGroup3D = this;
	AddInListImage3D(storyimage3D);
}

void __fastcall TStoryGroup3D::Remove(TStoryImage3D * storyimage3D) {
	RemoveFromListImage3D(storyimage3D);
	Index = PIndex;
}

void __fastcall TStoryGroup3D::Anime(int i, int j) {
	if (ExpandMode == EExpandMode::ExpZ) {
		StoryBoard3D->SetAnim(VSGListImage3D[i]->AnimX, 0.0);
		StoryBoard3D->SetAnim(VSGListImage3D[i]->AnimY, 0.0);
		if ((VSGListImage3D[i]->Position->Z < 0.01) && j > 0) {
			VSGListImage3D[i]->AnimZ->StopAtCurrent();
			VSGListImage3D[i]->Position->Z = Step * (j + 2) + StepZCollapse;
			StoryBoard3D->SetAnim(VSGListImage3D[i]->AnimZ, Step * (j + 1) + StepZCollapse);
		}
		else {
			StoryBoard3D->SetAnim(VSGListImage3D[i]->AnimZ, Step * (j + 1) + StepZCollapse);
		}
	}
	else if (ExpandMode == EExpandMode::ExpX) {

	}
}

void __fastcall TStoryGroup3D::AnimeFirst(int i) {
	if (ExpandMode == EExpandMode::ExpZ) {
		StoryBoard3D->SetAnim(VSGListImage3D[i]->AnimX, 0.0);
		StoryBoard3D->SetAnim(VSGListImage3D[i]->AnimY, 0.0);
		if (VSGListImage3D[i]->Position->Z > 2 * Step) {
			VSGListImage3D[i]->Position->Z = StepZCollapse;
		}
		else {
			VSGListImage3D[i]->AnimZ->StopAtCurrent();
			VSGListImage3D[i]->Position->Z = VSGListImage3D[i]->Position->Z;
			StoryBoard3D->SetAnim(VSGListImage3D[i]->AnimZ, StepZCollapse);
		}
	}

	AnimH->Stop();
	AnimH->StopValue = VSGListImage3D[i]->Height;
	AnimW->Stop();
	AnimW->StopValue = VSGListImage3D[i]->Width;
	if ((Bitmap->Width == VSGListImage3D[i]->Bitmap->Width) && (Bitmap->Height == VSGListImage3D[i]->Bitmap->Height)) {
		AnimB->StartValue = Bitmap;
		AnimB->StopValue = VSGListImage3D[i]->Bitmap;
		AnimB->Start();
	}
	else {
		Bitmap->Assign(VSGListImage3D[i]->Bitmap);
		AnimH->Start();
		AnimW->Start();
	}
}

void __fastcall TStoryGroup3D::SetIndex(int index) {
	int i, j;
	int c;
	bool flag;
	double decX;

	c = VSGListImage3D.size();

	if (index != -99) {
		flag = true;
		if (index < 0)
			index = c - 1;
		if (index >= c)
			index = 0;
	}
	else {
		flag = false;
		index = PIndex;
	}
	j = 0;
	if (ExpandMode == EExpandMode::ExpZ) {
		for (i = 0; i < c; i++)
			VSGListImage3D[i]->AnimZ->Stop();
		for (i = index + 1; i < c; i++)
			Anime(i, j++);
		for (i = 0; i < index; i++)
			Anime(i, j++);
		if (VSGListImage3D[i]->Position->Z > Step && flag) {
			AnimeFirst(i);
		}
	}
	PIndex = index;
}

void __fastcall TStoryGroup3D::SGTimer(TObject * Sender) {
	IsExpanded = false;
}

// ---------------------------------------------------------

void __fastcall TStoryGroup3D::SGDblClick(TObject *Sender) {
	StoryBoard3D->FlagMouseDblClick = true;
	DoDblClick();
}

void __fastcall TStoryGroup3D::SGMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y, const TVector3D &RayPos, const TVector3D &RayDir) {
	StoryBoard3D->FlagMouseDown = true;
}

void __fastcall TStoryGroup3D::SGMouseMove(TObject *Sender, TShiftState Shift, float X, float Y) {
	// StoryBoard3D->Sphere->Visible = false;
	// Passage à chaque mouvement dans un groupe si pas dragdrop
	// if (StoryBoard3D->DragFlag) {
	// Move();
	// ResetClick();
	// } else
	if (StoryBoard3D->IsCameraMove) {
		StoryBoard3D->BoomMove(Shift, X, Y);
	}
	else {
		if (Shift.Contains(ssLeft)) {
			if (StoryBoard3D->FlagMouseDown) {
				if (!StoryBoard3D->FlagMouseClick && !StoryBoard3D->FlagMouseDblClick) {
					StoryBoard3D->FlagMouseClick = true;
					DoClickAndMove();
				}
			}
			if (StoryBoard3D->FlagMouseClick && !StoryBoard3D->FlagMouseDblClick) {
				StoryBoard3D->FlagMouseMove = true;
				DoMove(Shift, X, Y);
			}
		}
		else
			StoryBoard3D->ResetClick();
	}
}

void __fastcall TStoryGroup3D::SGMouseUp(TObject * Sender, TMouseButton Button, TShiftState Shift, float X, float Y) {
	// Passage ici quand fin de move(group), ne passe pas ici a la fin d'un dragdrop
	if (!StoryBoard3D->IsCameraMove) {
		if (!StoryBoard3D->FlagMouseMove && !StoryBoard3D->FlagMouseDblClick)
			DoClick();
		if (StoryBoard3D->FlagMouseMove)
			DoMouseUpAfterMove();
	}
	StoryBoard3D->ResetClick();
}

void __fastcall TStoryGroup3D::DoClick(void) {
}

void __fastcall TStoryGroup3D::DoClickAndMove(void) {
	StoryBoard3D->ArcBall3D->IsVisible = false;
	if (!IsExpanded) {
		StoryBoard3D->ObjectInMove = (TControl*) this;
		StoryBoard3D->IsObjectMove = true;
	}
}

void __fastcall TStoryGroup3D::DoDblClick(void) {
	IsExpanded = !IsExpanded;
}

void __fastcall TStoryGroup3D::DoMove(TShiftState Shift, float X, float Y) {
	if (StoryBoard3D->IsObjectMove) {
		if (StoryBoard3D->ObjectInMove->ClassNameIs(L"TStoryImage3D")) {
			((TStoryImage3D*)StoryBoard3D->ObjectInMove)->DoMove(Shift, X, Y);
		}
		else if (StoryBoard3D->ObjectInMove->ClassNameIs(L"TStoryGroup3D")) {
			Move();
		}
	}
	else {
		StoryBoard3D->BoomMove(Shift, X, Y);
	}
}

void __fastcall TStoryGroup3D::DoMouseUpAfterMove(void) {
	StoryBoard3D->IsObjectMove = false;
	SnapToGrid();
}

#pragma end_region

#endif
