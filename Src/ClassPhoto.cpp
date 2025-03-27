#ifndef CLASSPHOTO
#define CLASSPHOTO

#include "ClassPhoto.h"

TPhoto::TPhoto(TTagMap *tagmap, TLgs *lgs) {
	UnicodeString s;

	TagMap        = tagmap;
	Lgs           = lgs;
	Analys        = new TAnalys(Lgs);
	Ifds          = new TIfds(TagMap, Lgs);
	Diagnostic    = new DDiagnostic(Analys);
	Width         = 0;
	Heigth        = 0;
	ThumbOffset   = 0;
	ThumbLength   = 0;
	PreviewOffset = 0;
	PreviewLength = 0;
	Path          = L"";
}

TPhoto::~TPhoto(void) {
	delete Analys;
	delete Ifds;
	delete Diagnostic;
}

UnicodeString __fastcall TPhoto::GetInfo(void) {
	return Uprintf(Lgs->QueryKey(L"INTF.PhotoInfo").w_str(),Ifds->MapCamera->MakerCaption.w_str(), Ifds->MapCamera->Caption.w_str(), QueryDataCaption(L"DateTimeOriginal").w_str());
}

void __fastcall TPhoto::AssignAnalysData(void) {
	Analys->MapCamera                           = Ifds->MapCamera;
	Analys->Lens->Caption                       = QueryDataCaption(L"Lens");
	Analys->Aperture->Value                     = QueryDataCalcValue(L"Aperture");
	Analys->ExposureTime->Value                 = QueryDataCalcValue(L"ExposureTime");
	Analys->Focale->Value                       = QueryDataCalcValue(L"Focale");
	Analys->Iso->Value                          = QueryDataCalcValue(L"Iso");
	Analys->FocusDistance->Upper->OriginalValue = QueryDataCalcValue(L"FocusDistanceUpper");
	Analys->FocusDistance->Lower->Value         = QueryDataCalcValue(L"FocusDistanceLower");
	Analys->Exposure->Value                     = QueryDataCalcValue(L"MeasuredEV2");
	Analys->Rotate->SetValue(QueryDataValue(L"Rotate"));

	Analys->Flash->Bias->Tag->Value = QueryDataCalcValue(L"FlashBias");
	if (Ifds != NULL) {
		if (Ifds->MapCamera != NULL) {
			Analys->MapCamera = Ifds->MapCamera;
			if (QueryDataValid(Ifds->MapCamera->TagFlashFired)) {
				Analys->Flash->IsValid = true;
				Analys->Flash->Fired->Tag->Value = QueryDataCalcValue(Ifds->MapCamera->TagFlashFired);
				Analys->Flash->Required->Tag->Value = QueryDataCalcValue(Ifds->MapCamera->TagFlashOff);

				Analys->Flash->ValueBuiltIn = QueryDataCalcValue(Ifds->MapCamera->TagFlashBuiltIn);
				Analys->Flash->ValueExternal = QueryDataCalcValue(Ifds->MapCamera->TagFlashExternal);
			}
		}
	}
}

void __fastcall TPhoto::DisplayIfdsExpert(TTreeView *TreeView) {
	unsigned short i, j;
	unsigned k, l;
	TTreeViewItem* Item0, *Item1, *Item2, *Item3, *Item4;

	Item0 = new TTreeViewItem(TreeView);
	Item0->Font->Family = L"Courier new";
	Item0->Text = Lgs->QueryKey(L"INTF.TiffData") + L" " + Ifds->MapCamera->MakerCaption + " - " + Ifds->MapCamera->Caption;
	Item0->Parent = TreeView;
	for (i = 0; i < Ifds->Count; i++) {
		if (Ifds->Ifd[i]->Count) {
			Item1 = new TTreeViewItem(Item0);
			Item1->Font->Family = L"Courier new";
			Item1->Text = Ifds->Ifd[i]->Verbose;
			Item1->Parent = Item0;
			for (j = 0; j < Ifds->Ifd[i]->Count; j++) {
				Item2 = new TTreeViewItem(Item1);
				Item2->Font->Family = L"Courier new";
				Item2->Text = Ifds->Ifd[i]->Datas[j]->Verbose;
				Item2->Parent = Item1;
				for (k = 0; k < Ifds->Ifd[i]->Datas[j]->Count; k++) {
					Item3 = new TTreeViewItem(Item2);
					Item3->Font->Family = L"Courier new";
					Item3->Text = Ifds->Ifd[i]->Datas[j]->Data[k]->Verbose;
					Item3->Parent = Item2;
					if (Ifds->Ifd[i]->Datas[j]->Data[k]->Dump) {
						Ifds->Ifd[i]->Datas[j]->Data[k]->GenerateDumpStr(25);
						for (l = 0; l < Ifds->Ifd[i]->Datas[j]->Data[k]->DumpStrCount; l++) {
							Item4 = new TTreeViewItem(Item3);
							Item4->Font->Family = L"Courier new";
							Item4->Text = Ifds->Ifd[i]->Datas[j]->Data[k]->DumpStr->Strings[l];
							Item4->Parent = Item3;
						}
					}
					Item3->IsExpanded = true;
				}
				Item2->IsExpanded = true;
			}
			Item1->IsExpanded = true;
		}
	}
}

void __fastcall TPhoto::DisplayIfdsShort(TTreeView *TreeView) {
	unsigned short i, j;
	unsigned k;
	TTreeViewItem* Item0, *Item1, *Item3;

	Item0 = new TTreeViewItem(TreeView);
	Item0->Font->Family = L"Courier new";
	Item0->Text = Lgs->QueryKey(L"INTF.TiffData") + L" " + Ifds->MapCamera->MakerCaption + " - " + Ifds->MapCamera->Caption;
	Item0->Parent = TreeView;
	for (i = 0; i < Ifds->Count; i++) {
		if (Ifds->Ifd[i]->Count) {
			Item1 = new TTreeViewItem(Item0);
			Item1->Font->Family = L"Courier new";
			Item1->Text = Ifds->Ifd[i]->Caption;
			Item1->Parent = Item0;
			for (j = 0; j < Ifds->Ifd[i]->Count; j++) {
				for (k = 0; k < Ifds->Ifd[i]->Datas[j]->Count; k++) {
					Item3 = new TTreeViewItem(Item1);
					Item3->Font->Family = L"Courier new";
					Item3->Text = Ifds->Ifd[i]->Datas[j]->Data[k]->ShortVerbose;
					Item3->Parent = Item1;
					Item3->IsExpanded = true;
				}
			}
			Item1->IsExpanded = true;
		}
	}
}

void __fastcall TPhoto::DisplayIfdsUser(TTreeView *TreeView) {
	unsigned short i, j;
	unsigned k;
	TTreeViewItem* Item0, *Item1, *Item3;
	UnicodeString s;

	Item0 = new TTreeViewItem(TreeView);
	Item0->Font->Family = L"Courier new";
	Item0->Text = Lgs->QueryKey(L"INTF.TiffData") + L" " + Ifds->MapCamera->MakerCaption + " - " + Ifds->MapCamera->Caption;
	Item0->Parent = TreeView;
	for (i = 0; i < Ifds->Count; i++) {
		if (Ifds->Ifd[i]->Count) {
			Item1 = new TTreeViewItem(Item0);
			Item1->Font->Family = L"Courier new";
			Item1->Text = Ifds->Ifd[i]->Caption;
			Item1->Parent = Item0;
			for (j = 0; j < Ifds->Ifd[i]->Count; j++) {
				for (k = 0; k < Ifds->Ifd[i]->Datas[j]->Count; k++) {
					s = Ifds->Ifd[i]->Datas[j]->Data[k]->MapDataCaption;
					if ( s != L"Not mapped" ) {
						if (Ifds->Ifd[i]->Datas[j]->Data[k]->EnumArray != NULL)
							s = Ifds->Ifd[i]->Datas[j]->Data[k]->EnumCaption;
						if (s != L"Default - Default") {
							s = Ifds->Ifd[i]->Datas[j]->Data[k]->UserVerbose;
							if (s != L"") {
								Item3 = new TTreeViewItem(Item1);
								Item3->Font->Family = L"Courier new";
								Item3->Text = Ifds->Ifd[i]->Datas[j]->Data[k]->UserVerbose;
								Item3->Parent = Item1;
								Item3->IsExpanded = true;
							}
						}
					}
				}
			}
			Item1->IsExpanded = true;
		}
	}
}

void __fastcall TPhoto::DisplayIfds(TTreeView *TreeView) {
	TreeView->BeginUpdate();
	TreeView->Clear();

	if (Verbose == 0) {
		DisplayIfdsUser(TreeView);
	}
	else if (Verbose == 1) {
		DisplayIfdsShort(TreeView);
	}
	else if (Verbose == 2) {
		DisplayIfdsExpert(TreeView);
	}
	TreeView->ExpandAll();
	TreeView->EndUpdate();

}

void __fastcall TPhoto::Compute(UnicodeString *fullname) {
	FILE *ifp;
	unsigned Baseifp = 0;

	ifp = fopen(U2c(*fullname), "rb");
	if (ifp) {
		Path = *fullname;
		Format = LowerCase(ExtractFileExt(Path));
		Ifds->Parse(ifp, &Baseifp);
		Width = (unsigned) QueryDataCalcValue(L"ImageWidth");
		Heigth = (unsigned) QueryDataCalcValue(L"ImageHeigth");
		ThumbOffset = (unsigned) QueryDataCalcValue(L"ThumbOffset");
		ThumbLength = (unsigned) QueryDataCalcValue(L"ThumbLength");
		PreviewOffset = (unsigned) QueryDataCalcValue(L"PreviewOffset");
		PreviewLength = (unsigned) QueryDataCalcValue(L"PreviewLength");
		Rotate = (unsigned) QueryDataCalcValue(L"Rotate");

		AssignAnalysData();
		Analys->Compute();
		fclose(ifp);
	}
}

// Interface Ifds / MapData
double __fastcall TPhoto::QueryDataValue(UnicodeString MapDataCaption) {
	UnicodeString ifdname;
	unsigned short tagnumber;
	unsigned index, ifdindex;
	bool dump;

	if (Ifds->MapCamera != NULL) {
		if (Ifds->MapCamera->QueryMapData(&MapDataCaption, &ifdname, &tagnumber, &index, &dump)) {
			ifdindex = Ifds->QueryIfdIndex(&ifdname);
			if (ifdindex != 0xFFFF) {
				return Ifds->Ifd[ifdindex]->QueryDataValue(tagnumber, index);
			}
		}
	}
	return 0.0;
}

double __fastcall TPhoto::QueryDataCalcValue(UnicodeString MapDataCaption) {
	UnicodeString ifdname, s;
	unsigned short tagnumber;
	unsigned index, ifdindex;
	bool dump;

	if (Ifds->MapCamera != NULL) {
		s = MapDataCaption;
		if (Ifds->MapCamera->QueryMapData(&MapDataCaption, &ifdname, &tagnumber, &index, &dump)) {
			ifdindex = Ifds->QueryIfdIndex(&ifdname);
			if (ifdindex != 0xFFFF) {
				return Ifds->Ifd[ifdindex]->QueryDataCalcValue(tagnumber, index);
			}
		}
	}
	return 0.0;
}

bool __fastcall TPhoto::QueryDataValid(UnicodeString MapDataCaption) {
	UnicodeString ifdname, s;
	unsigned short tagnumber;
	unsigned index, ifdindex;
	bool dump;

	if (Ifds->MapCamera != NULL) {
		s = MapDataCaption;
		if (Ifds->MapCamera->QueryMapData(&MapDataCaption, &ifdname, &tagnumber, &index, &dump)) {
			ifdindex = Ifds->QueryIfdIndex(&ifdname);
			if (ifdindex != 0xFFFF) {
				return true;
			}
		}
	}
	return false;
}

UnicodeString __fastcall TPhoto::QueryDataCaption(UnicodeString MapDataCaption) {
	UnicodeString ifdname;
	unsigned short tagnumber;
	unsigned index, ifdindex;
	bool dump;

	if (Ifds->MapCamera != NULL) {
		if (Ifds->MapCamera->QueryMapData(&MapDataCaption, &ifdname, &tagnumber, &index, &dump)) {
			ifdindex = Ifds->QueryIfdIndex(&ifdname);
			if (ifdindex != 0xFFFF) {
				return Ifds->Ifd[ifdindex]->QueryDataCaption(tagnumber, index);
			}
		}
	}
	return "";
}

// UnicodeString TPhoto::ComputeVstNode(TVirtualNode *Node) {
// return ScanDisk->ComputeVstNode(Node, Analys, Ifds, TagMap);
// }
// void SetVst(TVirtualStringTree *vst) {
// ScanDisk->Vst = vst;
// Tiff->Vst = vst;
// PVst = vst;
// testapex();
// }

// void TPhoto::testapex(void) {
// double sv, tv, av, f16rules, a1, a2, a3, a4, a5, a6, a7, a8, a9;
// double ev, tmin, amin, smax;
//
// ev = 14.0;
// sv = Apex->Iso2Apex(100.0);
// av = Apex->ExposureTime2Apex(1 / 100.0);
// tv = Apex->Aperture2Apex(16.0);
// f16rules = Apex->ApexReference();
//
// a1 = Apex->ApexOf(1.0 / 50.0, 8.0, 100.0);
// a2 = Apex->ApexDelta(1.0 / 5000.0, 8.0, 100.0, ev);
//
// tmin = 1.0 / 1000.0;
// amin = 4.0;
// smax = 100;
//
// a3 = Apex->PerfectExposureTime(amin, smax, ev);
// a4 = Apex->ApexDelta(a3, amin, smax, ev);
//
// a5 = Apex->PerfectAperture(tmin, smax, ev);
// a6 = Apex->ApexDelta(tmin, a5, smax, ev);
//
// a7 = Apex->PerfectIso(tmin, amin, ev);
// a8 = Apex->ApexDelta(tmin, amin, a7, ev);
//
// a9 = a8;
// }

#endif
