#ifndef CLASSSTORYBOARD2D
#define CLASSSTORYBOARD2D

#include "ClassStoryboard2D.h"

#pragma region TStoryBoard2D

// -----------------------------------------------------
// CLASS TStoryBoard2D
// -----------------------------------------------------
__fastcall TStoryBoard2D::TStoryBoard2D(TFmxObject* Owner) : TPanel(Owner) {
	MoveFlag = false;
	MoveObject = NULL;
	DragObject = NULL;
	MovePoint = TPointF(float(0.0), float(0.0));
	ScaleMax = 4.0;
	ScaleMin = 0.2;
	Parent = Owner;
	StyleLookup = L"thumbpanelstyle";
	ApplyStyle();
	Width = float(100000.0);
	Height = float(100000.0);
	Position->X = float(-50000.0);
	Position->Y = float(-50000.0);

	//OnDragDrop = SBDragDrop;
	//OnDragOver = SBDragOver;
	OnMouseMove = ImageMove;
	OnMouseUp = ImageMoveStop;
	OnMouseWheel = SBMouseWheel;

	VSBListImage2D.empty();
	VSBListGroup2D.empty();
}

__fastcall TStoryBoard2D::~TStoryBoard2D(void) {
	unsigned int i;
	// detruire les images isolées
	for (i = 0; i < VSBListImage2D.size(); i++) {
		delete VSBListImage2D.at(i);
	}
	// Detruire les groupes
	for (i = 0; i < VSBListGroup2D.size(); i++) {
		delete VSBListGroup2D.at(i);
	}
	VSBListImage2D.empty();
	VSBListGroup2D.empty();
}

bool __fastcall TStoryBoard2D::GetGridVisible(void) {
	return true;
}

void __fastcall TStoryBoard2D::SetGridVisible(bool visible) {
}

bool __fastcall TStoryBoard2D::GetGridSnap(void) {
	return true;
}

void __fastcall TStoryBoard2D::SetGridSnap(bool visible) {
}

// gestion des listes groupes et images
void __fastcall TStoryBoard2D::AddInListImage2D(TStoryImage2D *storyimage2D) {
	VSBListImage2D.push_back(storyimage2D);
}

void __fastcall TStoryBoard2D::AddInListGroup2D(TStoryGroup2D *storygroup2D) {
	VSBListGroup2D.push_back(storygroup2D);
}

void __fastcall TStoryBoard2D::RemoveFromListImage2D(TStoryImage2D *storyimage2D) {
	unsigned int i;
	bool flag;

	flag = false;
	for (i = 0; i < VSBListImage2D.size(); i++) {
		if (flag)
			VSBListImage2D.at(i-1) = VSBListImage2D.at(i);
		if (VSBListImage2D.at(i) == storyimage2D)
			flag = true;
	}
	if (flag)
		VSBListImage2D.pop_back();
}

void __fastcall TStoryBoard2D::RemoveFromListGroup2D(TStoryGroup2D *storygroup2D) {
	unsigned int i;
	bool flag;

	flag = false;
	for (i = 0; i < VSBListGroup2D.size(); i++) {
		if (flag)
			VSBListGroup2D.at(i-1) = VSBListGroup2D.at(i);
		if (VSBListGroup2D.at(i) == storygroup2D)
			flag = true;
	}
	if (flag)
		VSBListGroup2D.pop_back();
}

// dragdrop
void __fastcall TStoryBoard2D::SBDragDropBegin(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y) {
	// Emeteur DragDrop
	// Capté par un MouseDown sur une TThumbPanel->Image
	UnicodeString s;

	s = Sender->ClassName();
	DragObject = Sender;
	if (Button == TMouseButton::mbLeft) {
		VDragSelect = EDragSelect::flSingle;
	}
	else if (Button == TMouseButton::mbRight) {
		VDragSelect = EDragSelect::flAllSelected;
	}

	// Simuler un Click
	if (DragObject->ClassName() == L"TImage")
		((TImage*)(Sender))->OnClick(Sender);
}

void __fastcall TStoryBoard2D::SBDragDrop(TObject *Sender, const TDragObject &Data, const TPointF &Point) {
	TStoryImage2D *storyimage2D;
	TStoryGroup2D *storygroup2D;
	TObject *dropon;
	TGroupPanel *grouppanel;
	TThumbPanel *tp1, *tp2;
	UnicodeString s;
	int i;
	TPointF pt;

	// Recepteur DragDrop (StoryBoard en 2D)
	storygroup2D = NULL;
	if (DragObject->ClassName() == L"TImage") {
		grouppanel = (TGroupPanel*)((TThumbPanel*)((TImage*)(DragObject))->Parent)->Parent;
		if (((TImage*)(DragObject))->Parent->ClassName() == L"TThumbPanel") {
			tp1 = (TThumbPanel*)((TImage*)(DragObject))->Parent;
			storyimage2D = new TStoryImage2D((TFmxObject*)Sender, tp1, Point, this);
			if (Sender->ClassName() == L"TStoryBoard2D") {
				// Drop sur StoryBoard
				//storyimage2D = new TStoryImage2D(this, tp1, Point, this);
				storyimage2D->Position->X -= float(storyimage2D->Width / 2.0);
				storyimage2D->Position->Y -= float(storyimage2D->Height / 2.0);
				AddInListImage2D(storyimage2D);

				// Verif si intersection avec image ou groupe pour groupement eventuel
				dropon = ImageIntersect(storyimage2D);
				if (dropon != NULL) {
					if (dropon->ClassNameIs(L"TStoryImage2D")) {
						// Drop sur une image isolé
						pt.X = ((TStoryImage2D*)(dropon))->Position->X;
						pt.Y = ((TStoryImage2D*)(dropon))->Position->Y + ((TStoryImage2D*)(dropon))->Height + 4.0;
						storygroup2D = new TStoryGroup2D(this, &pt, this);
						AddInListGroup2D(storygroup2D);
						storygroup2D->Add((TStoryImage2D*)dropon);
						RemoveFromListImage2D((TStoryImage2D*)dropon);
						i = storygroup2D->Add(storyimage2D);
						storygroup2D->Index = i;
					}
					else if (dropon->ClassNameIs(L"TStoryGroup2D")) {
						// drop sur un groupe existant
						i = ((TStoryGroup2D*)(dropon))->Add(storyimage2D);
						((TStoryGroup2D*)(dropon))->Index = i;
					}
				}

				if (VDragSelect == EDragSelect::flAllSelected) {
					// Multiselect actif: Copier le reste des images selectionnées
					for (i = 0; i < grouppanel->ChildrenCount; i++) {
						if (grouppanel->Children[i].ClassNameIs(L"TThumbPanel")) {
							tp2 = (TThumbPanel*) grouppanel->Children->Items[i];
							if ((tp1 != tp2) && tp2->Selected) {
								if (storygroup2D != NULL) {
									// Groupe déjà existant
									storyimage2D = new TStoryImage2D((TFmxObject*)Sender, tp2, Point, this);
									i = storygroup2D->Add(storyimage2D);
									storygroup2D->Index = i;
								}
								else {
									// Création d'un groupe sur la première image de la selection, puis ajout de la suivante
									pt.X = storyimage2D->Position->X;
									pt.Y = storyimage2D->Position->Y + storyimage2D->Height + 4.0;
									storygroup2D = new TStoryGroup2D(this, &pt, this);
									storygroup2D->Add(storyimage2D);
									AddInListGroup2D(storygroup2D);
									storyimage2D = new TStoryImage2D((TFmxObject*)Sender, tp2, Point, this);
									i = storygroup2D->Add(storyimage2D);
									storygroup2D->Index = i;
								}
							}
						}
					}
				}
			}
			else if (Sender->ClassName() == L"TStoryGroup2D") {
				storygroup2D = (TStoryGroup2D*)Sender;
				i = storygroup2D->Add(storyimage2D);
				storygroup2D->Index = i;
			}
			else if (Sender->ClassName() == L"TStoryImage2D") {
				if (((TStoryImage2D*)(Sender))->Parent->ClassNameIs(L"TStoryGroup2D")) {
					storygroup2D = (TStoryGroup2D*)((TStoryImage2D*)(Sender))->Parent;
					i = storygroup2D->Add(storyimage2D);
					storygroup2D->Index = i;
				}
				else {
					pt.X = ((TStoryImage2D*)(Sender))->Position->X;
					pt.Y = ((TStoryImage2D*)(Sender))->Position->Y + ((TStoryImage2D*)(Sender))->Height + 4.0;
					storygroup2D = new TStoryGroup2D(this, &pt, this);
					AddInListGroup2D(storygroup2D);
					storygroup2D->Add((TStoryImage2D*)Sender);
					i = storygroup2D->Add(storyimage2D);
					storygroup2D->Index = i;
				}
			}
		}
	}
}

void __fastcall TStoryBoard2D::SBDragOver(TObject *Sender, const TDragObject &Data, const TPointF &Point, TDragOperation &Accept) {
	Accept = TDragOperation::Move;
}

void __fastcall TStoryBoard2D::ImageMoveStart(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y) {
	if (Sender->ClassNameIs(L"TStoryImage2D")) {
		if (((TStoryImage2D*)(Sender))->Parent->ClassNameIs(L"TStoryBoard2D")) {
			// Image isolé
			MoveObject = (TControl*) Sender;
			MovePoint = ((TImage*)(Sender))->AbsoluteToLocal(Application->MainForm->ScreenToClient(Screen->MousePos()));
		}
		else if (((TStoryImage2D*)(Sender))->Parent->ClassNameIs(L"TStoryGroup2D")) {
			// Image appartenant à un groupe
			MoveObject = (TControl*)((TControl*)(Sender))->Parent;
			MovePoint = ((TPanel*)(MoveObject))->AbsoluteToLocal(Application->MainForm->ScreenToClient(Screen->MousePos()));
		}
	}
	else {
		// Groupe
		MoveObject = (TControl*) Sender;
		MovePoint = ((TPanel*)(Sender))->AbsoluteToLocal(Application->MainForm->ScreenToClient(Screen->MousePos()));
	}
	MoveObject->BringToFront();
	MoveFlag = true;
}

void __fastcall TStoryBoard2D::ImageMove(TObject *Sender, TShiftState Shift, float X, float Y) {
	TPointF p;

	if (MoveFlag) {
		p = this->AbsoluteToLocal(Application->MainForm->ScreenToClient(Screen->MousePos()));
		MoveObject->Position->X = p.X - MovePoint.X;
		MoveObject->Position->Y = p.Y - MovePoint.Y;
	}
}

void __fastcall TStoryBoard2D::ImageMoveStop(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y) {
	TStoryImage2D *storyimage2D;
	TStoryGroup2D *storygroup2D;
	TObject *dropon;
	TPointF pt;
	int i;

	MoveFlag = false;
	if (Sender->ClassNameIs(L"TStoryImage2D")) {
		storyimage2D = (TStoryImage2D*)Sender;
		dropon = ImageIntersect(storyimage2D);
		if (dropon != NULL) {
			if (dropon->ClassNameIs(L"TStoryImage2D")) {
				// Move sur une image isolé
				pt.X = ((TStoryImage2D*)(dropon))->Position->X;
				pt.Y = ((TStoryImage2D*)(dropon))->Position->Y + ((TStoryImage2D*)(dropon))->Height + 4.0;
				storygroup2D = new TStoryGroup2D(this, &pt, this);
				AddInListGroup2D(storygroup2D);
				storygroup2D->Add((TStoryImage2D*)dropon);
				i = storygroup2D->Add(storyimage2D);
				storygroup2D->Index = i;
			}
			else if (dropon->ClassNameIs(L"TStoryGroup2D")) {
				// Move sur un groupe existant si storyimage2D n'appartient pas a un groupe
				if (!storyimage2D->Parent->ClassNameIs(L"TStoryGroup2D")) {
					i = ((TStoryGroup2D*)(dropon))->Add(storyimage2D);
					((TStoryGroup2D*)(dropon))->Index = i;
				}
			}
		}
	}
}

void __fastcall TStoryBoard2D::SBMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, bool &Handled) {
	TPointF pscreen, pwindow, pbefore, pafter;

	// Position souris sur client de la fenetre
	pscreen = Application->MainForm->ScreenToClient(Screen->MousePos());
	pwindow.X = pscreen.X;
	pwindow.Y = pscreen.Y;

	// Position souris dans storyboard avant Zoom
	pbefore = AbsoluteToLocal(pwindow);

	if (WheelDelta > 0) {
		Scale->X = dmin(Scale->X + 0.2, ScaleMax);
		Scale->Y = dmin(Scale->Y + 0.2, ScaleMax);
	}
	else {
		Scale->X = dmax(Scale->X - 0.2, ScaleMin);
		Scale->Y = dmax(Scale->Y - 0.2, ScaleMin);
	}
	pafter = LocalToAbsolute(pbefore);

	Position->X += (pwindow.X - pafter.X);
	Position->Y += (pwindow.Y - pafter.Y);
}

TObject* __fastcall TStoryBoard2D::ImageIntersect(TStoryImage2D *source) {
	unsigned i, j;
	TStoryImage2D *cible;
	TStoryGroup2D *storygroup2D;

	for (i = 0; i < (unsigned) ChildrenCount; i++) {
		if (Children->Items[i]->ClassNameIs(L"TStoryImage2D")) {
			cible = (TStoryImage2D*)Children->Items[i];
			if (cible->AbsoluteRect.IntersectsWith(source->AbsoluteRect) && (source != cible)) {
				// Drop sur une image isolé
				return cible;
			}
		}
		if (Children->Items[i]->ClassNameIs(L"TStoryGroup2D")) {
			storygroup2D = (TStoryGroup2D*)Children->Items[i];
			if (storygroup2D->AbsoluteRect.IntersectsWith(source->AbsoluteRect)) {
				// Drop sur le container d'un groupe
				return storygroup2D;
			}
			else {
				for (j = 0; j < (unsigned) storygroup2D->ChildrenCount; j++) {
					if (storygroup2D->Children->Items[j]->ClassNameIs(L"TStoryImage2D")) {
						cible = (TStoryImage2D*)storygroup2D->Children->Items[j];
						if (cible->AbsoluteRect.IntersectsWith(source->AbsoluteRect) && (source != cible)) {
							// Drop sur une image d'un groupe
							return storygroup2D;
						}
					}
				}
			}
		}
	}
	return NULL;
}

#pragma end_region

#pragma region TStoryImage2D

// -----------------------------------------------------
// CLASS TStoryImage2D
// ...Owner: TStoryBoard ou TStoryGroup
// ...thumbpanel: Image et informations
// ...point: Position d'insertion dans StoryBoard
// ...storyBoard: viewport d'affichage
// -----------------------------------------------------
__fastcall TStoryImage2D::TStoryImage2D(TFmxObject* Owner, TThumbPanel* thumbpanel, const TPointF &Point, TStoryBoard2D *storyboard2D) : TImage(Owner) {
	double decX;

	StoryBoard2D = storyboard2D;
	ThumbPanel = thumbpanel;
	Parent = Owner;

	Bitmap = ThumbPanel->Bitmap;
	WrapMode = TImageWrapMode::Fit;

	if (ThumbPanel->Rotate == ERotate::flPortrait) {
		Width = IMAGESIZE * ThumbPanel->Ratio;
		Height = IMAGESIZE;
		decX = (IMAGESIZE - Width) / 2.0;
	} else {
		Width = IMAGESIZE;
		Height = IMAGESIZE / ThumbPanel->Ratio;
		decX = 0.0;
	}
	Position->X = Point.X + decX;
	Position->Y = Point.Y;

	OnMouseDown = StoryBoard2D->ImageMoveStart;
	OnMouseMove = StoryBoard2D->ImageMove;
	OnMouseUp  = StoryBoard2D->ImageMoveStop;
	//OnDragOver = StoryBoard2D->SBDragOver;
	//OnDragDrop = StoryBoard2D->SBDragDrop;
	OnDblClick = ImageDblClick;
}

__fastcall TStoryImage2D::~TStoryImage2D(void) {
}

void __fastcall TStoryImage2D::ImageDblClick(TObject *Sender) {
}

#pragma end_region

#pragma region TStoryGroup2D

// -----------------------------------------------------
// CLASS TStoryGroup2D
// -----------------------------------------------------
__fastcall TStoryGroup2D::TStoryGroup2D(TFmxObject* Owner, TPointF *point, TStoryBoard2D *storyboard2D) : TPanel(Owner) {
	StoryBoard2D = storyboard2D;
	Parent = Owner;
	PIndex = 0;

	Width = IMAGESIZE;
	Height = 20.0;
	StyleLookup = L"panelstyle";
	ClipChildren = false;

	Position->X = point->X;
	Position->Y = point->Y;

	OnMouseDown = StoryBoard2D->ImageMoveStart;
	OnMouseMove = StoryBoard2D->ImageMove;
	OnMouseUp = StoryBoard2D->ImageMoveStop;
	//OnDragOver = StoryBoard2D->SBDragOver;
	//OnDragDrop = StoryBoard2D->SBDragDrop;
	OnMouseWheel = SGMouseWheel;

	VSGListImage2D.empty();
}

__fastcall TStoryGroup2D::~TStoryGroup2D(void) {
	VSGListImage2D.empty();
}

void __fastcall TStoryGroup2D::AddInListImage2D(TStoryImage2D *storyimage2D) {
	VSGListImage2D.push_back(storyimage2D);
}

void __fastcall TStoryGroup2D::RemoveFromListImage2D(TStoryImage2D *storyimage2D) {
	unsigned int i;
	bool flag;

	flag = false;
	for (i = 0; i < VSGListImage2D.size(); i++) {
		if (flag)
			VSGListImage2D.at(i-1) = VSGListImage2D.at(i);
		if (VSGListImage2D.at(i) == storyimage2D)
			flag = true;
	}
	if (flag)
		VSGListImage2D.pop_back();
}

void __fastcall TStoryGroup2D::SGMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta, bool &Handled) {
	SetIndex(PIndex - (int)(WheelDelta / 120.0));
	Handled = true;
}

//int __fastcall TStoryGroup2D::GetCount(void) {
//	return (int) VSGListImage2D.size();
//}

int __fastcall TStoryGroup2D::Add(TStoryImage2D* storyimage2D) {
	storyimage2D->Parent = this;
	AddInListImage2D(storyimage2D);
	//SetIndex(VSGListImage2D.size());
	return VSGListImage2D.size();
}

void __fastcall TStoryGroup2D::SetIndex(int AIndex) {
	int i, j;
	int c;

	c = VSGListImage2D.size();
	if (AIndex < 0)
		AIndex = 0;
	if (AIndex >= c)
		AIndex = c-1;

	j = 0;
	for (i = AIndex + 1; i < c; i++) {
		VSGListImage2D[i]->Position->X = VSGListImage2D[i]->ThumbPanel->OffsetX - (double)(c - j) * 0.5;
		VSGListImage2D[i]->Position->Y = -4.0 - VSGListImage2D[i]->Height - (double)(c - j) * 0.5;
		VSGListImage2D[i]->BringToFront();
		j++;
	}
	for (i = 0; i < AIndex; i++) {
		VSGListImage2D[i]->Position->X = VSGListImage2D[i]->ThumbPanel->OffsetX - (double)(c - j) * 0.5;
		VSGListImage2D[i]->Position->Y = -4.0 - VSGListImage2D[i]->Height - (double)(c - j) * 0.5;
		VSGListImage2D[i]->BringToFront();
		j++;
	}
	VSGListImage2D[AIndex]->Position->X = VSGListImage2D[AIndex]->ThumbPanel->OffsetX;
	VSGListImage2D[AIndex]->Position->Y = -4.0 - VSGListImage2D[AIndex]->Height;
	VSGListImage2D[AIndex]->BringToFront();
	PIndex = AIndex;
}

#pragma end_region

#endif
