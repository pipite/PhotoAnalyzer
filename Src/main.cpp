// #include <fmx.h>
#pragma hdrstop

#include "main.h"

#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;

#pragma region ConstructeurDestructeur

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	UnicodeString configpath, path;
	unsigned i;

	Caption = APPNAME;
	RootPath = ".\\PhotoAnalyser"; //ExtractFileDir(ParamStr(0));
	configpath = RootPath + L"..\\Config\\" + EditFileConfig->Text;
	Lgs = new TLgs();
	StoryBoard = new TStoryBoard(StoryBoardContainer, EMode2D3D::fl3D);
	ScanDisk = new TScanDisk(TreeView1, TreeView3, configpath, Lgs, StoryBoard);
	ImageFilter = new TImageFilter();
	Lgs->LoadXML("..\\Config\\Lang.xml");

	for (i = 0; i < Lgs->CountLang; i++) {
		ComboBoxLang->Items->Add(Lgs->Lang->Strings[i]);
	}

	XPanel = Panel1->Width;
	path = Edit2->Text;
	TreeView1->BeginUpdate();
	ScanDisk->ScanFolder(TreeView1, &path);
	TreeView1->EndUpdate();
	RadioButtonUserList->IsChecked = true;
	ThumbPanel = NULL;
	Verbose = 0;
	WorkCount = 0;
	LbPhotoInfo->TextAlign = TTextAlign::Center;
	LbPhotoInfo->VertTextAlign = TTextAlign::Center;

	Brightness = new TBrightness;

	FlagLast1 = 0;
	FlagLast2 = 0;
	FlagLast3 = 0;
	FlagLast4 = 0;

	FilterChangeCheck(NULL);
}

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action) {
	delete ScanDisk;
	delete StoryBoard;
	delete Lgs;
	delete Brightness;
	delete ImageFilter;
}

#pragma end_region

#pragma region InfoPanel

void __fastcall TForm1::UpdateLangVar(void) {
	if (ThumbPanel != NULL) {
		ThumbPanel->Photo->DisplayIfds(TreeViewExif);
		LbPhotoInfo->Text = ThumbPanel->Photo->Info;
		LbExposureTimeEv->Text = ThumbPanel->Photo->Analys->ExposureTime->ExposureCompens->Caption;
		LbApertureEv->Text = ThumbPanel->Photo->Analys->Aperture->ExposureCompens->Caption;
		LbIsoEv->Text = ThumbPanel->Photo->Analys->Iso->ExposureCompens->Caption;
		LbExposureProgram->Text = ThumbPanel->Photo->QueryDataCaption(L"ExposureProgram");
		LbFocusMode->Text = ThumbPanel->Photo->QueryDataCaption(L"FocusMode");
		LbFocusAreaMode->Text = ThumbPanel->Photo->QueryDataCaption(L"FocusAreaMode");
		LbMeteringMode->Text = ThumbPanel->Photo->QueryDataCaption(L"MeteringMode");
		LbMesuredEv->Text = ThumbPanel->Photo->Analys->Exposure->Caption;
		ThumbPanel->Photo->Diagnostic->Compute(TreeView2);
	}
}

void __fastcall TForm1::UpdateLangConst(void) {
	int i;

	LabelFileConfig->Text = Lgs->QueryKey(L"INTF.LabelFileConfig");
	LabelDefaultSearchPath->Text = Lgs->QueryKey(L"INTF.LabelDefaultSearchPath");
	ButtonBrowse->Text = Lgs->QueryKey(L"INTF.ButtonBrowse");
	TabControlMain->Tabs[0]->Text = Lgs->QueryKey(L"INTF.TabItemViewer");
	TabControlMain->Tabs[1]->Text = Lgs->QueryKey(L"INTF.TabItemExifData");
	TabControlMain->Tabs[2]->Text = Lgs->QueryKey(L"INTF.TabItemConfig");
	RadioButtonUserList->Text = Lgs->QueryKey(L"INTF.RadioButtonUserList");
	RadioButtonFullList->Text = Lgs->QueryKey(L"INTF.RadioButtonFullList");
	RadioButtonFullListExpert->Text = Lgs->QueryKey(L"INTF.RadioButtonFullListExpert");
	for (i = 0; i < TreeView1->Count; i++) {
		RecurseTvi(TreeView1->Items[i]);
	}
}

void __fastcall TForm1::RecurseTvi(TTreeViewItem *tvi) {
	int i;

	if (tvi->ClassNameIs(L"TFolderItem")) {
		for (i = 0; i < tvi->Count; i++) {
			if (tvi->Items[i]->ClassNameIs(L"TFolderItem"))
				RecurseTvi(tvi->Items[i]);
			else if (tvi->Items[i]->ClassNameIs(L"TGroupPanel")) {
				((TGroupPanel*)(tvi->Items[i]))->GBModel->Text = L" " + Lgs->QueryKey(L"INTF.CameraModel") + L" ";
				((TGroupPanel*)(tvi->Items[i]))->GBLens->Text = L" " + Lgs->QueryKey(L"INTF.Lens") + L" ";
			}
		}
	}
}

#pragma end_region

#pragma region WorkIndicator

void __fastcall TForm1::WorkStart(void) {
	WorkCount++;
	Working->Enabled = true;
	Working->Visible = true;
}

void __fastcall TForm1::WorkStop(void) {
	WorkCount--;
	if (WorkCount == 0) {
		Working->Enabled = false;
		Working->Visible = false;
	}
}

#pragma end_region

#pragma region Click

void __fastcall TForm1::BCollapseAllClick(TObject *Sender) {
	StoryBoard->Expand(false);
}

void __fastcall TForm1::BExpandAllClick(TObject *Sender) {
	StoryBoard->Expand(true);
}

void __fastcall TForm1::TreeView1Click(TObject *Sender) {
	if (TreeView1->Selected != NULL) {
		TreeView1->Selected->IsExpanded = !TreeView1->Selected->IsExpanded;
		ScanDisk->ScanFile();
		CalcFolderItemHeight(((TFolderItem*)(TreeView1->Selected)));
		TreeView1->Selected->IsExpanded = !TreeView1->Selected->IsExpanded;
		TreeView1->Selected->IsExpanded = !TreeView1->Selected->IsExpanded;
	}
}

void __fastcall TForm1::UpdateViewer(TThumbPanel *tp) {
	UnicodeString s;
	double focale, aperture;

	ThumbPanel = tp;
	ImageViewer1->Bitmap->LoadFromFile(ThumbPanel->Path);
	ImageViewer1->BestFit();

	aperture = ThumbPanel->Photo->Analys->Aperture->Value;
	focale = ThumbPanel->Photo->Analys->Focale->Value;

	LbExposureTime->Text = ThumbPanel->Photo->Analys->ExposureTime->Caption;
	LbAperture->Text = ThumbPanel->Photo->Analys->Aperture->Caption;
	LbIso->Text = ThumbPanel->Photo->Analys->Iso->Caption;

	LbLens->Text = ThumbPanel->Photo->Analys->Lens->Caption;
	TbEv->Enabled = false;
	TbEv->Value = float(ThumbPanel->Photo->Analys->Exposure->Relative->Value);
	TbEv->Enabled = true;

	PbLensQuality->Min = 0;
	PbLensQuality->Max = 1;
	PbLensQuality->Value = float(ThumbPanel->Photo->Analys->Lens->QueryIndice(focale, aperture));
	LbFocale->Text = ThumbPanel->Photo->Analys->Focale->Caption;

	ThumbPanel->Photo->Analys->Histogram->Compute(ThumbPanel->Bitmap, ImHistogram);
	UpdateLangVar();
	ThumbPanel->Selected = true;
}

void __fastcall TForm1::ThumbImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y) {
	UnicodeString s;
	double focale, aperture;

	if (Sender->ClassNameIs("TImage")) {
		ThumbPanel = GetThumbPanel(Sender);
		ImageViewer1->Bitmap->LoadFromFile(ThumbPanel->Path);
		ImageViewer1->BestFit();

		aperture = ThumbPanel->Photo->Analys->Aperture->Value;
		focale = ThumbPanel->Photo->Analys->Focale->Value;

		LbExposureTime->Text = ThumbPanel->Photo->Analys->ExposureTime->Caption;
		LbAperture->Text = ThumbPanel->Photo->Analys->Aperture->Caption;
		LbIso->Text = ThumbPanel->Photo->Analys->Iso->Caption;

		LbLens->Text = ThumbPanel->Photo->Analys->Lens->Caption;
		TbEv->Enabled = false;
		TbEv->Value = float(ThumbPanel->Photo->Analys->Exposure->Relative->Value);
		TbEv->Enabled = true;

		PbLensQuality->Min = 0;
		PbLensQuality->Max = 1;
		PbLensQuality->Value = float(ThumbPanel->Photo->Analys->Lens->QueryIndice(focale, aperture));
		LbFocale->Text = ThumbPanel->Photo->Analys->Focale->Caption;

		ThumbPanel->Photo->Analys->Histogram->Compute(ThumbPanel->Bitmap, ImHistogram);
		UpdateLangVar();
		ThumbPanel->Selected = true;
	}
}

void __fastcall TForm1::ButtonBrowseClick(TObject *Sender) {
	if (OpenDialog1->Execute()) {
		EditFileConfig->Text = RemoveEol(OpenDialog1->Files->Text);
	}
}

#pragma end_region

#pragma region Resize

void __fastcall TForm1::Panel1Resize(TObject *Sender) {
	if (Panel1->Width < IMAGESIZE + 4)
		Panel1->Width = float(IMAGESIZE + 4);
	CalcAllHeight(TreeView1);
	ImageViewer1->BestFit();
}

void __fastcall TForm1::FormResize(TObject *Sender) {
	ImageViewer1->BestFit();
}

#pragma end_region

#pragma region ExifData

void __fastcall TForm1::RadioButtonChange(TObject *Sender) {
	if (RadioButtonUserList->IsChecked)
		Verbose = 0;
	if (RadioButtonFullList->IsChecked)
		Verbose = 1;
	if (RadioButtonFullListExpert->IsChecked)
		Verbose = 2;
	if (ThumbPanel != NULL)
		ThumbPanel->Photo->DisplayIfds(TreeViewExif);
}

#pragma end_region

#pragma region Lang

void __fastcall TForm1::ComboBoxLangChange(TObject *Sender) {
	Lgs->ActiveLang = ComboBoxLang->Selected->Text;
	UpdateLangVar();
	UpdateLangConst();
}

#pragma end_region

#pragma region ExposureTime

void __fastcall TForm1::LbExposureTimeMouseEnter(TObject *Sender) {
	if (ThumbPanel != NULL) {
		if (!ThumbPanel->Photo->Analys->ExposureTime->Limit->IsInRange) {
			LbExposureTime->FontColor = 0xffff0000;
		}
		TbEv->Value = float(ThumbPanel->Photo->Analys->ExposureTime->ExposureCompens->Limit->Relative->Value);
		LbExposureTime->Text = ThumbPanel->Photo->Analys->ExposureTime->Limit->Caption;
		LbExposureTimeEv->Text = ThumbPanel->Photo->Analys->ExposureTime->ExposureCompens->Limit->Caption;
	}
}

void __fastcall TForm1::LbExposureTimeMouseLeave(TObject *Sender) {
	if (ThumbPanel != NULL) {
		LbExposureTime->FontColor = 0xffffffff;
		TbEv->Value = float(ThumbPanel->Photo->Analys->Exposure->Relative->Value);
		LbExposureTime->Text = ThumbPanel->Photo->Analys->ExposureTime->Caption;
		LbExposureTimeEv->Text = ThumbPanel->Photo->Analys->ExposureTime->ExposureCompens->Caption;
	}
}

#pragma end_region

#pragma region Aperture

void __fastcall TForm1::LbApertureMouseEnter(TObject *Sender) {
	if (ThumbPanel != NULL) {
		if (!ThumbPanel->Photo->Analys->Aperture->Limit->IsInRange) {
			LbAperture->FontColor = 0xffff0000;
		}
		TbEv->Value = float(ThumbPanel->Photo->Analys->Aperture->ExposureCompens->Limit->Relative->Value);
		PbLensQuality->Value = float(ThumbPanel->Photo->Analys->Lens->QueryIndice(ThumbPanel->Photo->Analys->Focale->Value, ThumbPanel->Photo->Analys->Aperture->Best->Value));
		LbAperture->Text = ThumbPanel->Photo->Analys->Aperture->Limit->Caption;
		LbApertureEv->Text = ThumbPanel->Photo->Analys->Aperture->ExposureCompens->Limit->Caption;
	}
}

void __fastcall TForm1::LbApertureMouseLeave(TObject *Sender) {
	if (ThumbPanel != NULL) {
		LbAperture->FontColor = 0xffffffff;
		TbEv->Value = float(ThumbPanel->Photo->Analys->Exposure->Relative->Value);
		PbLensQuality->Value = float(ThumbPanel->Photo->Analys->Lens->QueryIndice(ThumbPanel->Photo->Analys->Focale->Value, ThumbPanel->Photo->Analys->Aperture->Value));
		LbAperture->Text = ThumbPanel->Photo->Analys->Aperture->Caption;
		LbApertureEv->Text = ThumbPanel->Photo->Analys->Aperture->ExposureCompens->Caption;
	}
}

#pragma end_region

#pragma region Iso

void __fastcall TForm1::LbIsoMouseEnter(TObject *Sender) {
	if (ThumbPanel != NULL) {
		if (!ThumbPanel->Photo->Analys->Iso->Limit->IsInRange) {
			LbIso->FontColor = 0xffff0000;
		}
		TbEv->Value = float(ThumbPanel->Photo->Analys->Iso->ExposureCompens->Limit->Relative->Value);
		LbIso->Text = ThumbPanel->Photo->Analys->Iso->Limit->Caption;
		LbIsoEv->Text = ThumbPanel->Photo->Analys->Iso->ExposureCompens->Limit->Caption;
	}
}

void __fastcall TForm1::LbIsoMouseLeave(TObject *Sender) {
	if (ThumbPanel != NULL) {
		LbIso->FontColor = 0xffffffff;
		TbEv->Value = float(ThumbPanel->Photo->Analys->Exposure->Relative->Value);
		LbIso->Text = ThumbPanel->Photo->Analys->Iso->Caption;
		LbIsoEv->Text = ThumbPanel->Photo->Analys->Iso->ExposureCompens->Caption;
	}
}

#pragma end_region

#pragma region Exposure

void __fastcall TForm1::TbEvChange(TObject *Sender) {
	double v;
	if (ThumbPanel != NULL) {
		v = (TbEv->Value - ThumbPanel->Photo->Analys->Exposure->Relative->Value);
		v /= 30;
		ContrastEffect1->Brightness = float(v);
	}
}

#pragma end_region

#pragma region Filter

void __fastcall TForm1::QueryFilterData(void) {
	ImageFilter->FilterData.Dev1 = CtbFilterExposureDev1->Value;
	ImageFilter->FilterData.Dev2 = CtbFilterExposureDev2->Value;
	ImageFilter->FilterData.Ev1 = CtbFilterLightningEv1->Value;
	ImageFilter->FilterData.Ev2 = CtbFilterLightningEv2->Value;
	ImageFilter->FilterData.Tol = CtbFilterFlashTol->Value;
	ImageFilter->FilterData.Fc1 = CtbFilterFocale24x36Min->Value;
	ImageFilter->FilterData.Fc2 = CtbFilterFocale24x36Max->Value;
	ImageFilter->FilterData.Ff1 = CtbFilterFocale24x36Fixe->Value;
	ImageFilter->FilterData.Ff2 = CtbFilterFocale24x36Tol->Value;
	ImageFilter->FilterData.Et1 = CtbFilterExposureTimeStop->Value;
	ImageFilter->FilterData.Et2 = CtbFilterExposureTimeSubjectSpeed->Value;
	ImageFilter->FilterData.B1 = CtbFilterBorderMin->Value;
	ImageFilter->FilterData.B2 = CtbFilterBorderMax->Value;
	ImageFilter->FilterData.Dof1 = CtbFilterDepthOfFieldMin->Value;
	ImageFilter->FilterData.Dof2 = CtbFilterDepthOfFieldMax->Value;
}

void __fastcall TForm1::RecurseTviFilter(TTreeViewItem *tvi) {
	int i;

	if (tvi->ClassNameIs(L"TFolderItem")) {
		for (i = 0; i < tvi->Count; i++) {
			if (tvi->Items[i]->ClassNameIs(L"TFolderItem"))
				RecurseTvi(tvi->Items[i]);
			else if (tvi->Items[i]->ClassNameIs(L"TGroupPanel"))
				ImageFilter->ApplyToGroup(((TGroupPanel*)(tvi->Items[i])));
		}
	}
}

void __fastcall TForm1::ApplyGlobalFilter(void) {
	int i;

	QueryFilterData();
	for (i = 0; i < TreeView1->Count; i++) {
		RecurseTviFilter(TreeView1->Items[i]);
	}
}

void __fastcall TForm1::ExFilterChangeClick(TObject *Sender) {
	if (Sender->ClassNameIs(L"TExpander")) {
		if (((TExpander*)(Sender))->Name == L"ExFilterFlashNone") {
			ExFilterFlashNone->IsExpanded = true;
			ExFilterFlashNone->IsChecked = true;
		}
		if (((TExpander*)(Sender))->Name == L"ExFilterExposureNone") {
			ExFilterExposureNone->IsExpanded = true;
			ExFilterExposureNone->IsChecked = true;
		}
		if (((TExpander*)(Sender))->Name == L"ExFilterLightningNone") {
			ExFilterLightningNone->IsExpanded = true;
			ExFilterLightningNone->IsChecked = true;
		}
		if (((TExpander*)(Sender))->Name == L"ExFilterFocaleNo") {
			ExFilterFocaleNo->IsExpanded = true;
			ExFilterFocaleNo->IsChecked = true;
		}
	}
}

void __fastcall TForm1::FilterChangeCheck(TObject *Sender) {
	TCheckBox *cb;

	// Filter All
	if (ImageFilter != NULL) {
		if (ExFilterAll->IsChecked) {
			// Filter Flash
			if (!ExFilterFlashNone->IsChecked) {
				ImageFilter->VFlash = EFlash::flNone;
			}
			else if (!ExFilterFlashNone->IsExpanded) {
				if (Sender->ClassNameIs(L"TExpander")) {
					if (((TExpander*)(Sender))->Name == L"RBFilterFlashNone")
						ExFilterFlashNone->IsExpanded = true;
				}
			}

			if (RBFilterFlashNo->IsChecked && ExFilterFlashNone->IsChecked) {
				ImageFilter->VFlash = EFlash::flNo;
			}
			else if (RBFilterFlashError->IsChecked && ExFilterFlashNone->IsChecked) {
				ImageFilter->VFlash = EFlash::flDidNotFire;
			}
			if (RBFilterFlashYes->IsChecked && ExFilterFlashNone->IsChecked) {
				if (ExFilterFlashNone->IsExpanded) {
					ExFilterFlashNone->Height = float(157.0);
					PFilterFlashOption->Visible = true;
				}
				if (Sender->ClassNameIs(L"TCheckBox")) {
					cb = ((TCheckBox*)(Sender));
					if ((cb == CBFilterFlashBuiltIn) && !CBFilterFlashBuiltIn->IsChecked && !CBFilterFlashExternal->IsChecked)
						CBFilterFlashExternal->IsChecked = true;
					if ((cb == CBFilterFlashExternal) && !CBFilterFlashBuiltIn->IsChecked && !CBFilterFlashExternal->IsChecked)
						CBFilterFlashBuiltIn->IsChecked = true;
				}

				if (RBFilterFlashAll->IsChecked) {
					ImageFilter->VFlash = EFlash::flAll;
				}

				if (RBFilterFlashOutOfRange->IsChecked) {
					ImageFilter->VFlash = EFlash::flOutOfRange;
					CtbFilterFlashTol->Visible = true;
				}
				else {
					CtbFilterFlashTol->Visible = false;
				}
			}
			else {
				if (ExFilterFlashNone->IsExpanded) {
					PFilterFlashOption->Visible = false;
					ExFilterFlashNone->Height = float(85.0);
				}
			}

			// Filter Exposure
			if (!ExFilterExposureNone->IsChecked) {
				ImageFilter->VExposure = EExposure::flNone;
				// CtbExposureTolerance->Visible = false;
			}
			else {
				if (RBFilterExposureCorrect->IsChecked) {
					ImageFilter->VExposure = EExposure::flDeltaEv;
					CtbExposureTolerance->Visible = true;
					CtbFilterExposureDev1->Value = -CtbExposureTolerance->Value;
					CtbFilterExposureDev2->Value = CtbExposureTolerance->Value;
				}
				if (RBFilterExposureOver->IsChecked) {
					CtbExposureTolerance->Visible = true;
					ImageFilter->VExposure = EExposure::flDeltaEv;
					CtbFilterExposureDev1->Value = CtbExposureTolerance->Value;
					CtbFilterExposureDev2->Value = float(14.999);
				}
				if (RBFilterExposureUnder->IsChecked) {
					CtbExposureTolerance->Visible = true;
					ImageFilter->VExposure = EExposure::flDeltaEv;
					CtbFilterExposureDev1->Value = float(-14.999);
					CtbFilterExposureDev2->Value = -CtbExposureTolerance->Value;
				}
				if (RBFilterExposureOther->IsChecked) {
					CtbExposureTolerance->Visible = false;
					ImageFilter->VExposure = EExposure::flDeltaEv;
					CtbFilterExposureDev1->Enabled = true;
					CtbFilterExposureDev2->Enabled = true;
				}
				else {
					CtbFilterExposureDev1->Enabled = false;
					CtbFilterExposureDev2->Enabled = false;
				}
			}

			// Filter Lightning
			if (!ExFilterLightningNone->IsChecked) {
				ImageFilter->VLightning = ELightning::flNone;
			}
			else {

				if (RBFilterLightning6Ev->IsChecked) {
					ImageFilter->VLightning = ELightning::flEv;
					if (FlagLast1 != 1)
						CtbExposureTolerance->Value = float(3.0);
					CtbFilterLightningEv1->Value = float(0.0);
					CtbFilterLightningEv2->Value = float(6.0);
					FlagLast1 = 1;
				}
				if (RBFilterLightning9Ev->IsChecked) {
					ImageFilter->VLightning = ELightning::flEv;
					if (FlagLast1 != 2)
						CtbExposureTolerance->Value = float(1.5);
					CtbFilterLightningEv1->Value = float(6.0);
					CtbFilterLightningEv2->Value = float(9.0);
					FlagLast1 = 2;
				}
				if (RBFilterLightning11Ev->IsChecked) {
					ImageFilter->VLightning = ELightning::flEv;
					if (FlagLast1 != 3)
						CtbExposureTolerance->Value = float(1.0);
					CtbFilterLightningEv1->Value = float(9.0);
					CtbFilterLightningEv2->Value = float(14.0);
					FlagLast1 = 3;
				}
				if (RBFilterLightning14Ev->IsChecked) {
					ImageFilter->VLightning = ELightning::flEv;
					if (FlagLast1 != 4)
						CtbExposureTolerance->Value = float(1.0);
					CtbFilterLightningEv1->Value = float(14.0);
					CtbFilterLightningEv2->Value = float(17.999);
					FlagLast1 = 4;
				}

				if (RBFilterLightningOther->IsChecked) {
					ImageFilter->VLightning = ELightning::flEv;
					CtbFilterLightningEv1->Enabled = true;
					CtbFilterLightningEv2->Enabled = true;
				}
				else {
					CtbFilterLightningEv1->Enabled = false;
					CtbFilterLightningEv2->Enabled = false;
				}
			}

			// Filter Focale
			if (!ExFilterFocaleNo->IsChecked) {
				ImageFilter->VFocale = EFocale::flNone;
			}
			else {
				if (RBFilterFocaleWide->IsChecked) {
					ImageFilter->VFocale = EFocale::flFocaleBetween;
					CtbFilterFocale24x36Min->Value = float(1.0);
					CtbFilterFocale24x36Max->Value = float(24.0);
				}
				if (RBFilterFocaleStandard->IsChecked) {
					ImageFilter->VFocale = EFocale::flFocaleBetween;
					CtbFilterFocale24x36Min->Value = float(24.0);
					CtbFilterFocale24x36Max->Value = float(70.0);
				}
				if (RBFilterFocaleTele->IsChecked) {
					ImageFilter->VFocale = EFocale::flFocaleBetween;
					CtbFilterFocale24x36Min->Value = float(70.0);
					CtbFilterFocale24x36Max->Value = float(1000.0);
				}
				if (RBFilterFocale24x36Fixe->IsChecked) {
					ImageFilter->VFocale = EFocale::flFocaleFixe;
					CtbFilterFocale24x36Fixe->Enabled = true;
					CtbFilterFocale24x36Tol->Enabled = true;
				}
				else {
					CtbFilterFocale24x36Fixe->Enabled = false;
					CtbFilterFocale24x36Tol->Enabled = false;
				}
				if (RBFilterFocale24x36->IsChecked) {
					ImageFilter->VFocale = EFocale::flFocaleBetween;
					CtbFilterFocale24x36Min->Enabled = true;
					CtbFilterFocale24x36Max->Enabled = true;
				}
				else {
					CtbFilterFocale24x36Min->Enabled = false;
					CtbFilterFocale24x36Max->Enabled = false;
				}
			}

			// Filter ExposureTime
			if (!ExFilterExposureTimeNo->IsChecked) {
				ImageFilter->VExposureTime = EExposureTime::flNone;
			}
			else if (RBFilterExposureTimeTripod->IsChecked) {
				ImageFilter->VExposureTime = EExposureTime::flTripod;
			}
			else if (RBFilterExposureTimeStill->IsChecked) {
				ImageFilter->VExposureTime = EExposureTime::flStill;
			}
			else if (RBFilterExposureTimeVerySlow->IsChecked) {
				CtbFilterExposureTimeSubjectSpeed->Value = float(3.0);
				ImageFilter->VExposureTime = EExposureTime::flMove;
			}
			else if (RBFilterExposureTimeSlow->IsChecked) {
				CtbFilterExposureTimeSubjectSpeed->Value = float(6.0);
				ImageFilter->VExposureTime = EExposureTime::flMove;
			}
			else if (RBFilterExposureTimeRapid->IsChecked) {
				CtbFilterExposureTimeSubjectSpeed->Value = float(15.0);
				ImageFilter->VExposureTime = EExposureTime::flMove;
			}
			if (RBFilterExposureTimeSpeed->IsChecked) {
				ImageFilter->VExposureTime = EExposureTime::flMove;
				CtbFilterExposureTimeSubjectSpeed->Enabled = true;
			}
			else {
				CtbFilterExposureTimeSubjectSpeed->Enabled = false;
			}

			// Filter LensIs
			if (!CBFilterStab->IsChecked) {
				FlagLast2 = 1;
				ImageFilter->VLensIs = ELensIs::flNo;
				CtbFilterExposureTimeStop->Value = float(0.0);
				CtbFilterExposureTimeStop->Visible = false;
			}
			else {
				ImageFilter->VLensIs = ELensIs::flYes;
				if (FlagLast2 != 2)
					CtbFilterExposureTimeStop->Value = float(2.5);
				CtbFilterExposureTimeStop->Visible = true;
				FlagLast2 = 2;
			}

			// Filter ExFilterBorderNo
			if (!ExFilterBorderNo->IsChecked) {
				ImageFilter->VBorder = EBorder::flNone;
			}
			else if (RBFilterBorderClose->IsChecked) {
				ImageFilter->VBorder = EBorder::flBorder;
				if (FlagLast3 != 1) {
					CtbFilterBorderMin->Value = float(0.0);
					CtbFilterBorderMax->Value = float(0.85);
				}
				FlagLast3 = 1;
			}
			else if (RBFilterBorderAmerican->IsChecked) {
				ImageFilter->VBorder = EBorder::flBorder;
				if (FlagLast3 != 2) {
					CtbFilterBorderMin->Value = float(0.85);
					CtbFilterBorderMax->Value = float(1.5);
				}
				FlagLast3 = 2;
			}
			else if (RBFilterBorderMedium->IsChecked) {
				ImageFilter->VBorder = EBorder::flBorder;
				if (FlagLast3 != 3) {
					CtbFilterBorderMin->Value = float(1.5);
					CtbFilterBorderMax->Value = float(8.0);
				}
				FlagLast3 = 3;
			}
			else if (RBFilterBorderLarge->IsChecked) {
				ImageFilter->VBorder = EBorder::flBorder;
				if (FlagLast3 != 4) {
					CtbFilterBorderMin->Value = float(8.0);
					CtbFilterBorderMax->Value = float(100.0);
				}
				FlagLast3 = 4;
			}

			// Filter ExFilterDepthOfFieldNo
			if (!ExDepthOfFieldNo->IsChecked) {
				ImageFilter->VDepthOfField = EDepthOfField::flNone;
			}
			else if (RBFilterDepthOfField1->IsChecked) {
				ImageFilter->VDepthOfField = EDepthOfField::flDepthOfField;
				if (FlagLast4 != 1) {
					CtbFilterDepthOfFieldMin->Value = float(0.0);
					CtbFilterDepthOfFieldMax->Value = float(0.1);
				}
				FlagLast4 = 1;
			}
			else if (RBFilterDepthOfField2->IsChecked) {
				ImageFilter->VDepthOfField = EDepthOfField::flDepthOfField;
				if (FlagLast4 != 2) {
					CtbFilterDepthOfFieldMin->Value = float(0.1);
					CtbFilterDepthOfFieldMax->Value = float(0.5);
				}
				FlagLast4 = 2;
			}
			else if (RBFilterDepthOfField3->IsChecked) {
				ImageFilter->VDepthOfField = EDepthOfField::flDepthOfField;
				if (FlagLast4 != 3) {
					CtbFilterDepthOfFieldMin->Value = float(0.5);
					CtbFilterDepthOfFieldMax->Value = float(1.5);
				}
				FlagLast4 = 3;
			}
			else if (RBFilterDepthOfField4->IsChecked) {
				ImageFilter->VDepthOfField = EDepthOfField::flDepthOfField;
				if (FlagLast4 != 4) {
					CtbFilterDepthOfFieldMin->Value = float(1.5);
					CtbFilterDepthOfFieldMax->Value = float(15.0);
				}
				FlagLast4 = 4;
			}

			// Filter Orientation
			if (!ExFilterOrientationNo->IsChecked) {
				ImageFilter->VRotate = ERotate::flNone;
			}
			else if (RBFilterOrientationLandscape->IsChecked) {
				ImageFilter->VRotate = ERotate::flLandscape;
			}
			else if (RBFilterOrientationPortrait->IsChecked) {
				ImageFilter->VRotate = ERotate::flPortrait;
			}

		}
		else {
			ImageFilter->VRotate = ERotate::flNone;
			ImageFilter->VDepthOfField = EDepthOfField::flNone;
			ImageFilter->VBorder = EBorder::flNone;
			ImageFilter->VFlash = EFlash::flNone;
			ImageFilter->VExposure = EExposure::flNone;
			ImageFilter->VLightning = ELightning::flNone;
			ImageFilter->VFocale = EFocale::flNone;
			ImageFilter->VExposureTime = EExposureTime::flNone;
			ImageFilter->VLensIs = ELensIs::flNo;
		}
		ApplyGlobalFilter();
	}
}

#pragma end_region

// ---------------------------------------------------------------------------

void __fastcall TForm1::CbGridVisibleChange(TObject *Sender) {
	StoryBoard->GridVisible = CbGridVisible->IsChecked;
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::CbGridSnapChange(TObject *Sender) {
	StoryBoard->GridSnap = CbGridSnap->IsChecked;

}
// ---------------------------------------------------------------------------

void __fastcall TForm1::ImHistogramClick(TObject *Sender) {
	ShellExecute(0, L"Open", L"C:\\", NULL, NULL, SW_SHOWNORMAL);

}
// ---------------------------------------------------------------------------






