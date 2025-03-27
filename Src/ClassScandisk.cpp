#ifndef CLASSSCANDISK
#define CLASSSCANDISK

// ---------------------------------------------------------------------------
// Module ScanDisk Unicode pour TTreeView FireMonkey
#pragma hdrstop

#include "ClassScandisk.h"
#include "main.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma region ExternalProc

void __fastcall CalcAllHeight(TFmxObject *Object) {
	TFolderItem *fi;
	int i;

	for (i = 0; i < Object->ComponentCount; i++) {
		if (((TFolderItem*)(Object->Components[i]))->ClassNameIs("TFolderItem")) {
			fi = ((TFolderItem*)(Object->Components[i]));
			if (fi->IsChecked && fi->IsExpanded) {
				CalcFolderItemHeight(fi);
			}
			CalcAllHeight(fi);
		}
	}
}

void __fastcall CalcFolderItemHeight(TFolderItem *FolderItem) {
	float c, h;
	float p;
	TGroupPanel *gp;

	if (FolderItem != NULL) {
		if (FolderItem->GroupPanel != NULL) {
			gp = FolderItem->GroupPanel;
			c = (int)(gp->GridLayout->Width / gp->GridLayout->ItemWidth);
			if (c == 0)
				c = 1;
			h = gp->GridLayout->ItemHeight;
			p = ((float) gp->Count / (float) c) - (int)(gp->Count / c);
			if (p > 0.0)
				p = 1;
			gp->GridLayout->Height = (int)((int)((gp->Count / c) + p) * h);
			gp->Height = gp->GridLayout->Height + gp->Panel->Height + 10;
		}
	}
}

TThumbPanel* GetThumbPanel(TObject *Sender) {
	if (Sender->ClassNameIs("TImage")) {
		return (TThumbPanel *)((TThumbPanel *)Sender)->Parent;
	}
	else {
		return ((TThumbPanel*)Sender);
	}
}

#pragma end_region

#pragma region TGroupPanel

// -----------------------------------------------------
// CLASS TGroupPanel
// -----------------------------------------------------
TGroupPanel::TGroupPanel(TFolderItem* Owner, TLgs *lgs) : TFolderItem(Owner) {
	Lgs                         = lgs;
	Count                       = Owner->ImagesLevel1Count;
	ListModel                   = new TStringList();
	ListLens                    = new TStringList();

	GridLayout                  = new TGridLayout(this);
	GridLayout->Name            = "GridLayout";
	Panel                       = new TPanel(this);
	Panel->Name                 = "Panel";
	Label                       = new TLabel(Panel);
	Label->Name                 = "Label";

	Panel->Parent               = this;
	Panel->Height               = 46;
	Panel->Align                = TAlignLayout::Top;
	Panel->Padding->Left        = 1;
	Panel->Padding->Bottom      = 2;
	Panel->Padding->Right       = 1;

	OpenProgressBar(Owner->ImagesLevel1Count);

	Label->StyledSettings       = Label->StyledSettings >> TStyledSetting::Size;
	Label->Align                = TAlignLayout::Client;
	Label->Font->Size           = 18;
	Label->Parent               = Panel;
	Label->TextAlign            = TTextAlign::Center;
	Label->VertTextAlign        = TTextAlign::Center;
	Label->Text                 = Lgs->QueryKey(L"INTF.Loading");

	GridLayout->ItemHeight      = float(IMAGESIZE + 16 + 4);
	GridLayout->ItemWidth       = float(IMAGESIZE + 4);
	GridLayout->Padding->Bottom = 2;
	GridLayout->Align           = TAlignLayout::Top;
	GridLayout->Parent          = this;
	Parent                      = Owner;
	Name                        = "GroupPanel";

	GBModel                     = new TGroupBox(Panel);
	GBLens                      = new TGroupBox(Panel);
}

TGroupPanel::~TGroupPanel(void) {
	if (GBModel != NULL)
		delete GBModel;
	if (GBLens != NULL)
		delete GBLens;
	if (Label != NULL)
		delete Label;
	if (Panel != NULL)
		delete Panel;
	if (GridLayout != NULL)
		delete GridLayout;
	if (ListModel != NULL)
		delete ListModel;
	if (ListLens != NULL)
		delete ListLens;
}

void __fastcall TGroupPanel::OpenProgressBar(int max) {
	ProgressBar                  = new TProgressBar(Panel);
	ProgressBar->Value           = 0;
	ProgressBar->Max             = max;
	ProgressBar->Align           = TAlignLayout::Top;
	ProgressBar->Padding->Left   = 2;
	ProgressBar->Padding->Bottom = 2;
	ProgressBar->Padding->Right  = 2;
	ProgressBar->Height          = 9;
	ProgressBar->Align           = TAlignLayout::Bottom;
	ProgressBar->Parent          = Panel;
}

void __fastcall TGroupPanel::CloseProgressBar(void) {
	if (ProgressBar != NULL)
		delete ProgressBar;
	ProgressBar = NULL;
	if (Label != NULL)
		delete Label;
	Label = NULL;
}

void __fastcall TGroupPanel::AddInfo(TAnalys *analys) {
	bool flag;
	int i;
	UnicodeString s;

	s = analys->MapCamera->MakerModelCaption;

	flag = true;
	for (i = 0; i < ListModel->Count; i++) {
		if (ListModel->Strings[i] == s) {
			flag = false;
			break;
		}
	}
	if (flag)
		ListModel->Add(s);

	s = analys->Lens->Caption.Trim();
	if ((s != L"") && (s != "n/a")) {
		flag = true;
		for (i = 0; i < ListLens->Count; i++) {
			if (ListLens->Strings[i] == s) {
				flag = false;
				break;
			}
		}
		if (flag)
			ListLens->Add(s);
	}
}

void __fastcall TGroupPanel::CBChange(TObject *Sender) {
	/* TODO : Appel Filter */
	//Apply(Form1->QueryFilterData());
}

void __fastcall TGroupPanel::UpdateInfo(void) {
	TCheckBox *CB;
	int i, h1, h2;

	CloseProgressBar();

	h1 = 22 + 19 * ListModel->Count;
	h2 = 22 + 19 * ListLens->Count;
	this->Height += (h1 - Panel->Height) + h2;
	Panel->Height = h1 + h2 + 5;

	GBModel->Parent = Panel;
	GBModel->Height = h1;
	GBModel->Align = TAlignLayout::Top;
	GBModel->Padding->Top = 19;
	GBModel->Padding->Left = 1;
	GBModel->Padding->Bottom = 2;
	GBModel->Padding->Right = 1;
	GBModel->Text = L" " + Lgs->QueryKey(L"INTF.CameraModel") + L" ";

	for (i = 0; i < ListModel->Count; i++) {
		CB = new TCheckBox(GBModel);
		CB->BeginUpdate();
		CB->Parent = GBModel;
		CB->Height = 16;
		CB->Padding->Top = 0;
		CB->Align = TAlignLayout::Top;
		CB->Padding->Left = 8;
		CB->Padding->Right = 1;
		CB->Text = ListModel->Strings[i];
		CB->IsChecked = true;
		CB->OnChange = CBChange;
		CB->EndUpdate();
	}

	GBLens->Parent = Panel;
	GBLens->Height = h2;
	GBLens->Align = TAlignLayout::Top;
	GBLens->Padding->Top = 16;
	GBLens->Padding->Left = 1;
	GBLens->Padding->Bottom = 2;
	GBLens->Padding->Right = 1;
	GBLens->Text = L" " + Lgs->QueryKey(L"INTF.Lens") + L" ";

	for (i = 0; i < ListLens->Count; i++) {
		CB = new TCheckBox(GBLens);
		CB->BeginUpdate();
		CB->Parent = GBLens;
		CB->Height = 19;
		CB->Padding->Top = 0;
		CB->Align = TAlignLayout::Top;
		CB->Padding->Left = 8;
		CB->Padding->Right = 1;
		CB->Text = ListLens->Strings[i];
		CB->IsChecked = true;
		CB->OnChange = CBChange;
		CB->EndUpdate();
	}
}


#pragma end_region

#pragma region TThumbPanel

// -----------------------------------------------------
// CLASS TThumbPanel
// -----------------------------------------------------
TThumbPanel::TThumbPanel(TGridLayout* Owner, TTagMap *tagmap, UnicodeString path, TLgs *lgs, TStoryBoard *storyboard) : TPanel(Owner) {
	TBitmap *Bitmap;
	TTiff *Tiff;

	StoryBoard             = storyboard;
	Lgs                    = lgs;
	Photo                  = new TPhoto(tagmap, lgs);
	PPath                  = path;
	Height                 = float(IMAGESIZE + 4 + 16);
	Width                  = float(IMAGESIZE + 6);
	Parent                 = Owner;
	HitTest                = true;
	OnClick                = DoClick;
	Padding->Left          = IMAGESEPARATOR;
	Padding->Bottom        = IMAGESEPARATOR;
	Padding->Right         = IMAGESEPARATOR;

	Label                  = new TLabel(this);
	Label->Name            = "Label";
	Image                  = new TImage(this);
	Image->Name            = "Image";

	Label->StyledSettings  = Label->StyledSettings >> TStyledSetting::Size;
	Label->Font->Size      = 9;
	Label->Parent          = this;
	Label->Align           = TAlignLayout::Bottom;
	Label->Padding->Left   = 1;
	Label->Padding->Bottom = 1;
	Label->Padding->Right  = 1;
	Label->TextAlign       = TTextAlign::Center;
	Label->Text            = "55-250/125mm f3.5 1/2000";

	Bitmap                 = new TBitmap(0, 0);
	Tiff                   = new TTiff();
	Photo->Compute(&PPath);
	Tiff->LoadThumbnail(Bitmap, Photo, StoryBoard);
	Image->Bitmap->Assign(Bitmap);

	Image->Parent          = this;
	Image->HitTest         = true;
	Image->OnClick         = DoClick;
	Image->Align           = TAlignLayout::Client;
	Image->Padding->Left   = 3;
	Image->Padding->Bottom = 1;
	Image->Padding->Right  = 3;
	Image->Padding->Top    = 3;
	Image->WrapMode        = TImageWrapMode::Fit;
	Image->DragMode        = TDragMode::dmAutomatic;
	Image->OnMouseDown     = DoMouseDown;

	Ratio = (double) Bitmap->Width / (double) Bitmap->Height;
	if (Bitmap->Height > Bitmap->Width) {
		Rotate = ERotate::flPortrait;
		OffsetX = (IMAGESIZE - Image->Width) / 2.0;
	} else {
		Rotate = ERotate::flLandscape;
		OffsetX = 0.0;
	}
	delete Bitmap;
	delete Tiff;

	PSelected = false;
}

TThumbPanel::~TThumbPanel(void) {
	if (Image != NULL)
		delete Image;
	if (Label != NULL)
		delete Label;
	if (Photo != NULL)
		delete Photo;
	PPath = L"";
}

void __fastcall TThumbPanel::DoClick(TObject *Sender)
{
	Form1->ImageViewer1->Bitmap->LoadFromFile(Path);
	Form1->ImageViewer1->BestFit();

	Form1->LbExposureTime->Text = Photo->Analys->ExposureTime->Caption;
	Form1->LbAperture->Text = Photo->Analys->Aperture->Caption;
	Form1->LbIso->Text = Photo->Analys->Iso->Caption;

	Form1->LbLens->Text = Photo->Analys->Lens->Caption;
	Form1->TbEv->Enabled = false;
	Form1->TbEv->Value = float(Photo->Analys->Exposure->Relative->Value);
	Form1->TbEv->Enabled = true;

	Form1->PbLensQuality->Min = 0;
	Form1->PbLensQuality->Max = 1;
	Form1->PbLensQuality->Value = float(Photo->Analys->Lens->QueryIndice(Photo->Analys->Focale->Value, Photo->Analys->Aperture->Value));
	Form1->LbFocale->Text = Photo->Analys->Focale->Caption;

	Photo->Analys->Histogram->Compute(Bitmap, Form1->ImHistogram);
	Form1->UpdateLangVar();
	Photo->DisplayIfds(Form1->TreeViewExif);
	Photo->Diagnostic->Compute(Form1->TreeView2);
	Selected = true;
}

void __fastcall TThumbPanel::DoMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y)
{
	StoryBoard->SBDragDropBegin(Sender,Button,Shift,X,Y);
}

void __fastcall TThumbPanel::SetSelected(bool selected) {
	PSelected = selected;
}

TBitmap* __fastcall TThumbPanel::GetBitmap(void) {
	return Image->Bitmap;
}

void __fastcall TThumbPanel::UpdateInfo(void) {
	UnicodeString Focale, ExposureTime, Aperture, Iso;

	Focale = Photo->Analys->Focale->Caption + L" ";
	ExposureTime = Photo->Analys->ExposureTime->Caption + L" ";
	Aperture = Photo->Analys->Aperture->Caption + L" ";
	Iso = Photo->Analys->Iso->Caption;
	Label->Text = Focale + ExposureTime + Aperture + Iso;
}

#pragma end_region

#pragma region TFolderItem

// -----------------------------------------------------
// CLASS TFolderItem
// -----------------------------------------------------
TFolderItem::TFolderItem(TFmxObject* Owner) : TTreeViewItem(Owner) {
	if (Owner->ClassNameIs("TFolderItem")) {
		Parent = ((TFolderItem*)(Owner));
		// Width = ((TFolderItem*)(Owner))->Width ;             // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< !!!!!!!!!!!
	}
	else {
		Parent = ((TTreeViewItem*)(Owner));
	}
	Font->Size = 16;
	//HitTest = true;
	//DragMode = TDragMode::dmAutomatic;
	//OnMouseDown = FIMouseDown;
	//OnClick = FIClick;
}

TFolderItem::~TFolderItem(void) {
}

void __fastcall TFolderItem::FIClick(TObject *Sender) {
	IsExpanded = !IsExpanded;
}

void __fastcall TFolderItem::FIMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y) {
	IsExpanded = !IsExpanded;
}

#pragma end_region

#pragma region TScanDisk

// -----------------------------------------------------
// CLASS TScanDisk
// -----------------------------------------------------
TScanDisk::TScanDisk(TTreeView *Tv, TTreeView *Tv3, UnicodeString tagmapfile, TLgs *lgs, TStoryBoard *storyboard) {
	StoryBoard = storyboard;
	TreeView   = Tv;
	TagMapFile = tagmapfile;
	Lgs        = lgs;
	TagMap     = new TTagMap(Tv3);
	TagMap->LoadFromFile(TagMapFile);
	Count      = 0;
}

TScanDisk::~TScanDisk(void) {
	delete TagMap;
}

int __fastcall TScanDisk::ScanFolder(TFmxObject *Owner, UnicodeString *path) {
	int validres;
	TSearchRec SearchRec;
	UnicodeString FullName;
	TFolderItem *TviRecursif;
	int MatchAllCount = 0;
	int MatchCount = 0;
	int MatchFolder = 0;
	int tmpcount;
	UnicodeString s;

	if (!DirectoryExists(*path))
		return 0;

	validres = FindFirst(*path + L"\\*.*", faAnyFile, SearchRec);
	while (validres == 0) {
		if (SearchRec.Name[1] != '.') {
			FullName = *path + L"\\" + LowerCase(SearchRec.Name);
			s = LowerCase(ExtractFileExt(SearchRec.Name));
			if (((s == ".jpg") || (s == ".cr2")) || (SearchRec.Attr == 16)) {
				if (SearchRec.Attr != 16) {
					MatchAllCount++;
					MatchCount++;
				}
				else {
					TviRecursif = new TFolderItem(Owner);
					TviRecursif->Text = SearchRec.Name;
					TviRecursif->Path = FullName;
					TviRecursif->StyleLookup = L"treeviewitemstyle";
				}
			}
			if (SearchRec.Attr == 16) {
				if ((tmpcount = ScanFolder(TviRecursif, &FullName)) > 0) {
					MatchFolder++;
					MatchAllCount += tmpcount;
				}
			}
		}
		validres = FindNext(SearchRec);
	}
	FindClose(SearchRec);

	if (MatchAllCount == 0) {
//		delete Owner;
//		Owner = NULL;
	}
	else {
		if (Owner->ClassNameIs("TFolderItem")) {
			((TFolderItem*)(Owner))->ImagesLevel1Count = MatchCount;
			((TFolderItem*)(Owner))->ImagesAllLevelCount = MatchAllCount;
			((TFolderItem*)(Owner))->SubFoldersCount = MatchFolder;
			if (MatchCount != MatchAllCount) {
				((TFolderItem*)(Owner))->Text = ((TFolderItem*)(Owner))->Text + L" (" + UnicodeString(MatchCount) + L"/" + UnicodeString(MatchAllCount) + L")";
			}
			else {
				((TFolderItem*)(Owner))->Text = ((TFolderItem*)(Owner))->Text + L" (" + UnicodeString(MatchCount) + L")";
			}
		}
	}
	return MatchAllCount;
}

void __fastcall TScanDisk::ScanFile(void) {
	TFolderItem *fi;

	if (TreeView->Selected != NULL) {
		if (TreeView->Selected->ClassNameIs("TFolderItem")) {
			fi = ((TFolderItem*)(TreeView->Selected));
			if (!fi->IsChecked) {
				if (DirectoryExists(fi->Path) && (fi->ImagesLevel1Count > 0)) {
					fi->GroupPanel = new TGroupPanel(fi, Lgs);
					new TThreadScanFile(false, fi, TagMap, Lgs, StoryBoard);
					fi->IsChecked = true;
				}
			}
		}
	}
}
#pragma end_region

#pragma region TThreadScanFile

// -----------------------------------------------------
// CLASS TThreadScanFile
// -----------------------------------------------------
TThreadScanFile::TThreadScanFile(bool CreateSuspended, TFolderItem *tfi, TTagMap *tagmap, TLgs *lgs, TStoryBoard *storyboard) : TThread(CreateSuspended) {
	FreeOnTerminate = true;
	StoryBoard = storyboard;
	TagMap = tagmap;
	Lgs = lgs;
	Tfi = tfi;
	GridLayout = tfi->GroupPanel->GridLayout;
}

void __fastcall TThreadScanFile::Execute(void) {
	int validres;
	TSearchRec SearchRec;
	TPointF p;
	UnicodeString s;

	validres = FindFirst(Tfi->Path + L"\\*.*", faAnyFile, SearchRec);
	while (validres == 0) {
		if (SearchRec.Name[1] != '.') {
			FullName = Tfi->Path + L"\\" + LowerCase(SearchRec.Name);
			s = LowerCase(ExtractFileExt(SearchRec.Name));
			if (((s == ".jpg") || (s == ".cr2")) || (SearchRec.Attr == 16)) {
				if (SearchRec.Attr != 16) {
					Synchronize(ThumbLoad);
					Tfi->GroupPanel->AddInfo(ThumbPanel->Photo->Analys);
					Synchronize(UpdateThumbPanelInfo);
				}
			}
		}
		validres = FindNext(SearchRec);
	}
	Synchronize(UpdateGroupPanelInfo);
}

void __fastcall TThreadScanFile::ThumbLoad(void) {
	ThumbPanel = new TThumbPanel(GridLayout, TagMap, FullName, Lgs, StoryBoard);
	Tfi->GroupPanel->ProgressBar->Value++;
}

void __fastcall TThreadScanFile::UpdateGroupPanelInfo(void) {
	Tfi->GroupPanel->UpdateInfo();
	Tfi->IsExpanded = !Tfi->IsExpanded;
	Tfi->IsExpanded = !Tfi->IsExpanded;
}

void __fastcall TThreadScanFile::UpdateThumbPanelInfo(void) {
	ThumbPanel->UpdateInfo();
}

#pragma end_region

#endif
