#ifndef CLASSTAGMAP
#define CLASSTAGMAP
// ---------------------------------------------------------------------------
#pragma hdrstop

#include "ClassTagMap.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma region Commentaires
// TTagMap []
// ....TModels [Count, Model[Count], Verbose]
// ......QueryModelIndex(ModelCaption) ........................................ex: QueryModelIndex("Canon EOS 7D") .......-> 3
// ........TModel [ Caption, Ifds, Verbose ]
// ..........QueryMapIfdIndex(char*MapIfdCaption)
// ..........QueryMapData(char*MapDataCaption, char*MapIfdCaption, unsigned short*MapDataTagNumber, unsigned*MapDataIndex, bool*MapDataMemoryDump)
// ..........QueryMapDataDump(char*MapIfdCaption, unsigned short MapDataTagNumber)
// ..........QueryMapDataCaption(char*MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex)
// ..........QueryMapDataForceType(char*MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex)
// ............TMapIfds [ Count, Ifd[Count], Verbose ]
// ................TMapIfd [ Caption, SubIfds, Datas, Verbose ]
// ....................TMapSubIfds [ Count, SubIfd[Count], Verbose ]
// ..................... QueryMapSubIfdCaption (DataTagNumber) ................ex: QueryDataCaption(0x9727) ..............-> "MakerNote"
// ..................... QueryMapSubIfdTagNumber (DataCaption) ................ex: QueryDataTagNumber("MakerNote") .......-> 0x9727
// ..................... QueryMapSubIfdIsPointer (DataTagNumber) ..............ex: QueryDataCaption(0x9727) ..............-> true/false
// ..................... QueryMapSubIfdIsPointer (DataCaption) ................ex: QueryDataTagNumber("MakerNote") .......-> true/false
// ..................... QueryMapSubIfdSeek (DataTagNumber) ...................ex: QueryDataCaption(0x9727) ..............-> true/false
// ..................... QueryMapSubIfdSeek (DataCaption) .....................ex: QueryDataTagNumber("MakerNote") .......-> true/false
// ..................... QueryMapSubIfdIndex (DataCaption) ....................ex: QueryDataIndex("MakerNote") ...........-> 2
// ..................... QueryMapSubIfdIndex (DataTagNumber) ..................ex: QueryDataIndex(0x9727) ................-> 2
// ........................TMapSubIfd [Caption, TagNumber, IsPointer, Seek, Verbose ]
// ....................TMapDatas [ Count, Data[Count], Verbose ]
// ..................... QueryDataCaption (DataTagNumber) .....................ex: QueryDataCaption(0x0015) ..............-> "Aperture"
// ..................... QueryDataTagNumber (DataCaption) .....................ex: QueryDataTagNumber("Aperture") ........-> 0x0015
// ..................... QueryDataFormula(DataTagNumber) ......................ex: QueryDataCaption(0x0015) ..............-> "(Value/100)"
// ..................... QueryDataFormula(DataCaption) ........................ex: QueryDataCaption("Aperture") ..........-> "(Value/100)"
// ..................... QueryDataIndex (DataCaption) .........................ex: QueryDataIndex("Aperture") ............-> 4
// ..................... QueryDataIndex (DataTagNumber) .......................ex: QueryDataIndex(0x0015) ................-> 4
// ........................TMapData [Caption, TagNumber, Index, MemoryDump, Verbose ]
#pragma end_region

#pragma region TLensData

// -----------------------------------------------------
// CLASS TLensData
// -----------------------------------------------------
TLensData::TLensData(void) {
	PMaker       = L"";
	PModel       = L"";
	PLensModel   = L"";
	PFocaleMin   = float(0.0);
	PFocaleMax   = float(0.0);
	PApertureMin = float(0.0);
	PApertureMax = float(0.0);
	PPrice       = unsigned(0);
	PBitmapData  = NULL;
	PBitmapView  = NULL;
	PStabilized  = false;
	PIsData      = false;
}

TLensData::~TLensData(void) {
	if (PBitmapData != NULL)
		delete PBitmapData;
	if (PBitmapView != NULL)
		delete PBitmapView;
	PBitmapData = NULL;
	PBitmapView = NULL;
}

void __fastcall TLensData::Load(UnicodeString maker, UnicodeString model, UnicodeString lensmodel) {
	UnicodeString s;
	char *str1;
	FILE *cfp;

	PMaker = maker;
	PModel = model;
	PLensModel = lensmodel;
	s = RootPath + L"\\Data\\Camera\\" + RemoveStr(maker, L"/") + L"\\" + RemoveStr(model, L"/") + L"\\Lens\\" + RemoveStr(lensmodel, L"/") + L"\\";
	if (FileExists(s + L"Indice.png")) {
		PBitmapData = new TBitmap(0, 0);
		PBitmapData->LoadFromFile(s + L"Indice.png");
		PIsData = true;
	}
	s = RootPath + L"\\Data\\Lens\\" + RemoveStr(lensmodel, L"/") + L"\\";
	if (FileExists(s + L"Property.txt")) {
		cfp = fopen(U2c(s + L"Property.txt"), "r");
		if (cfp) {
			PIsData = (PIsData == true ? true : false);
			str1 = (char*) malloc(MAXSTR*sizeof(char));
			FFStringUntilEqual(cfp, str1);
			PFocaleMin = float(FFDouble(cfp, 1, str1));
			FFStringUntilEqual(cfp, str1);
			PFocaleMax = float(FFDouble(cfp, 1, str1));
			FFStringUntilEqual(cfp, str1);
			PApertureMin = float(FFDouble(cfp, 1, str1));
			FFStringUntilEqual(cfp, str1);
			PApertureMax = float(FFDouble(cfp, 1, str1));
			FFStringUntilEqual(cfp, str1);
			PPrice = unsigned(FFDouble(cfp, 1, str1));
			FFStringUntilEqual(cfp, str1);
			s = FFString(cfp, 1, str1);
			if (s == L"Yes")
				PStabilized = true;
			fclose(cfp);
			free(str1);
		}
	}
	if (FileExists(s + L"View.png")) {
		PBitmapView = new TBitmap(0, 0);
		PBitmapView->LoadFromFile(s + L"View.png");
	}
}

#pragma end_region

#pragma region TLensDatas

// -----------------------------------------------------
// CLASS TLensDatas
// -----------------------------------------------------
TLensDatas::TLensDatas(void) {
}

TLensDatas::~TLensDatas(void) {
	Clear();
}

unsigned __fastcall TLensDatas::GetCount(void) {
	return LensData.size();
}

void __fastcall TLensDatas::Clear(void) {
	while (LensData.size() != 0) {
		delete LensData.at(LensData.size()-1);
		LensData.pop_back();
	}
}

TLensData* __fastcall TLensDatas::Get(unsigned idx) {
	return LensData.at(idx);
}

TLensData* __fastcall TLensDatas::QueryLensData(UnicodeString lensmodel) {
	unsigned i;

	for (i = 0; i < Count; i++)
		if (Get(i) != NULL)
			if (RemoveStr(lensmodel, L"/") == Get(i)->LensModel)
				return Get(i);

	return NULL;
}

void __fastcall TLensDatas::Add(UnicodeString maker, UnicodeString model) {
	int v;
	TSearchRec sr;
	UnicodeString s;
	TLensData* ld;

	s = RootPath + L"\\Data\\Camera\\" + RemoveStr(maker, L"/") + L"\\" + RemoveStr(model, L"/") + L"\\Lens";
	if (DirectoryExists(s)) {
		v = FindFirst(s + L"\\*.*", faAnyFile, sr);
		while (v == 0) {
			if ((sr.Attr == 16) && (sr.Name[1] != L'.')) {
				ld = new TLensData;
				ld->Load(maker, model, sr.Name);
				LensData.push_back(ld);
			}
			v = FindNext(sr);
		}
		FindClose(sr);
	}
}

#pragma end_region

#pragma region TFlashData

// -----------------------------------------------------
// CLASS TFlashData
// -----------------------------------------------------
TFlashData::TFlashData(void) {
	PBitmapView = NULL;
	PMaker = L"";
	PModel = L"";
	PFlashModel = L"";
	PType = L"";
	PPriority = 0;

	PBaseNg = 0.0;
	PBaseFocale = 0.0;
	PBaseIso = 0.0;
	PDistanceMin = 0.0;
	PDistanceMax = 0.0;
	PDistanceMAxHSync = 0.0;
	PHSync = 0.0;
	PHSyncCoef = 0.0;
	PTolerance = 0.0;
	PFlashDurationCount = 0;
}

TFlashData::~TFlashData(void) {
	if (PBitmapView != NULL)
		delete PBitmapView;
	PBitmapView = NULL;
	if (PFlashDurationCount > 0) {
		free(FlashDurationAtPower);
		free(FlashDuration);
	}
}

void __fastcall TFlashData::SetFlashDurationCount(unsigned count) {
	if (PFlashDurationCount > 0) {
		free(FlashDurationAtPower);
		free(FlashDuration);
	}
	PFlashDurationCount = count;
	if (count > 0) {
		FlashDurationAtPower = (double*) malloc(count*sizeof(double));
		FlashDuration = (double*) malloc(count*sizeof(double));
	}
}

void __fastcall TFlashData::Load(UnicodeString maker, UnicodeString model, UnicodeString flashmodel) {
	UnicodeString s;
	char *str1;
	FILE *cfp;
	unsigned int i;

	str1 = (char*) malloc(MAXSTR*sizeof(char));

	PMaker = maker;
	PModel = model;
	PFlashModel = flashmodel;
	s = RootPath + L"\\Data\\Camera\\" + RemoveStr(maker, L"/") + L"\\" + RemoveStr(model, L"/") + L"\\Flash\\" + RemoveStr(flashmodel, L"/") + L"\\";
	if (FileExists(s + L"Type.txt")) {
		cfp = fopen(U2c(s + L"Type.txt"), "r");
		if (cfp) {
			PType = FFString(cfp, 2, str1);
			PPriority = unsigned(FFDouble(cfp, 2, str1));
			PHSync = FFDouble(cfp, 2, str1);
			fclose(cfp);
		}
	}
	s = RootPath + L"\\Data\\Flash\\" + RemoveStr(flashmodel, L"/") + L"\\";
	if (FileExists(s + L"Property.txt")) {
		cfp = fopen(U2c(s + L"Property.txt"), "r");
		if (cfp) {
			PBaseNg = FFDouble(cfp, 2, str1);
			PBaseFocale = FFDouble(cfp, 2, str1);
			PBaseIso = FFDouble(cfp, 2, str1);
			PDistanceMin = FFDouble(cfp, 2, str1);
			PDistanceMax = FFDouble(cfp, 2, str1);
			PDistanceMAxHSync = FFDouble(cfp, 2, str1);
			PHSyncCoef = FFDouble(cfp, 2, str1);
			PTolerance = FFDouble(cfp, 2, str1);
			if (FFString(cfp, 1, str1) == L"FlashDurationCount:") {
				FlashDurationCount = FFUnsigned(cfp, 1, str1);
				for (i = 0; i < FlashDurationCount; i++) {
					FlashDurationAtPower[i] = FFDouble(cfp, 2, str1);
					FlashDuration[i] = FFDouble(cfp, 1, str1);
				}
			}
			fclose(cfp);
		}
	}
	if (FileExists(s + L"View.jpg")) {
		PBitmapView = new TBitmap(0, 0);
		PBitmapView->LoadFromFile(s + L"View.jpg");
	}

	free(str1);
}

#pragma end_region

#pragma region TFlashDatas

// -----------------------------------------------------
// CLASS TFlashDatas
// -----------------------------------------------------
TFlashDatas::TFlashDatas(void) {
}

TFlashDatas::~TFlashDatas(void) {
	Clear();
}

unsigned __fastcall TFlashDatas::GetCount(void) {
	return FlashData.size();
}

void __fastcall TFlashDatas::Clear(void) {
	while (FlashData.size() != 0) {
		delete FlashData.at(FlashData.size()-1);
		FlashData.pop_back();
	}
}

TFlashData* __fastcall TFlashDatas::Get(unsigned idx) {
	return FlashData.at(idx);
}

TFlashData* __fastcall TFlashDatas::QueryFlashData(UnicodeString maker, UnicodeString model, UnicodeString flashtype) {
	unsigned i;

	for (i = 0; i < Count; i++)
		if (Get(i) != NULL)
			if ((RemoveStr(maker, L"/") == Get(i)->Maker) && (RemoveStr(model, L"/") == Get(i)->Model) && (flashtype == Get(i)->Type))
				return Get(i);

	return NULL;
}

void __fastcall TFlashDatas::Add(UnicodeString maker, UnicodeString model) {
	int v;
	TSearchRec sr;
	UnicodeString s;
	TFlashData *fd;

	s = RootPath + L"\\Data\\Camera\\" + RemoveStr(maker, L"/") + L"\\" + RemoveStr(model, L"/") + L"\\Flash";
	if (DirectoryExists(s)) {
		v = FindFirst(s + L"\\*.*", faAnyFile, sr);
		while (v == 0) {
			if ((sr.Attr == 16) && (sr.Name[1] != L'.')) {
				fd = new TFlashData;
				fd->Load(maker, model, sr.Name);
				FlashData.push_back(fd);
			}
			v = FindNext(sr);
		}
		FindClose(sr);
	}
}

#pragma end_region

#pragma region TMapEnumArray

// -----------------------------------------------------
// CLASS TMapEnumArray
// -----------------------------------------------------

TEnumArray::TEnumArray(void) {
	Maker   = L"Default";
	Model   = L"Default";
	Ifd     = L"Default";
	Caption = L"Default";
	PEnums  = L"None";
	BitEnum = false;
}

void __fastcall TEnumArray::SetEnums(UnicodeString enums) {
	PEnums  = RemoveEol(enums);
}

UnicodeString __fastcall TEnumArray::QueryEnumCaption(double value) {
	double val;
	unsigned enum32;
	UnicodeString target, tmp, bit, s;

	target = PEnums;
	s      = L"";
	enum32 = (unsigned) value;

	if (target != L"None") {
		target += L";";
		while (1) {
			tmp = target.SubString(1, target.Pos(L"=") - 1);
			if (tmp != L"") {
				if (!BitEnum) {
					// Cas Enum
					if (tmp.Pos(L"x") > 0)
						val = (double) strtol(U2c(tmp), NULL, 0);
					else
						val = tmp.ToDouble();

					if (val == value)
						return target.SubString(target.Pos(L"=") + 1, target.Pos(L";") - target.Pos(L"=") - 1);
					else
						target = target.SubString(target.Pos(L";") + 1, target.Length());
				}
				else {
					if (QueryEnumFlag(enum32, tmp)) {
						s += target.SubString(target.Pos(L"=") + 1, target.Pos(L";") - target.Pos(L"=") - 1) + L", ";
					}
					target = target.SubString(target.Pos(L";") + 1, target.Length());
				}
			}
			else {
				if (!BitEnum) {
					return L"Value not in Enum list";
				}
				else {
					s = s.SubString(1, s.Length() - 2);
					return s;
				}
			}
		}
	}
	return L"None";
}

bool __fastcall TEnumArray::QueryEnumFlag(unsigned value, UnicodeString bits) {
	unsigned i, len, bitmask, bitval;
	UnicodeString tmp, bit;

	bitmask = 0;
	bitval = 0;
	len = bits.Length();
	for (i = 0; i < len; i++) {
		bit = bits.SubString(len - i, 1);
		if (bit != L"*") {
			bitmask += 1 << i;
			bitval += bit.ToInt() << i;
		}
	}
	return ((bitmask & value) == bitval ? true : false);
}

#pragma end_region

#pragma region TMapEnumArrays

// -----------------------------------------------------
// CLASS TMapEnumArrays
// -----------------------------------------------------
TEnumArrays::TEnumArrays(void) {
	PVerbose = "EnumArray: Count= 0";
}

TEnumArrays::~TEnumArrays(void) {
	Clear();
}

unsigned __fastcall TEnumArrays::GetCount(void) {
	return EnumArray.size();
}

TEnumArray* __fastcall TEnumArrays::Get(unsigned idx) {
	return EnumArray.at(idx);
}

TEnumArray* __fastcall TEnumArrays::Add(void) {
	TEnumArray *ea;

	ea = new TEnumArray;
	EnumArray.push_back(ea);
	PVerbose = Uprintf(L"EnumArray: Count= %d", Count);
	return ea;
}

void __fastcall TEnumArrays::Clear(void) {
	while (EnumArray.size() != 0) {
		delete EnumArray.at(EnumArray.size()-1);
		EnumArray.pop_back();
	}
}

TEnumArray* __fastcall TEnumArrays::QueryEnumArray(UnicodeString caption, UnicodeString maker, UnicodeString model, UnicodeString ifd) {
	unsigned i;
	TEnumArray *ea;

	if (Count > 0) {
		for (i = 0; i < Count; i++) {
			ea = Get(i);
			if ((maker == ea->Maker) && (model == ea->Model) && (ifd == ea->Ifd) && (caption == ea->Caption)) {
				return ea;
			}
			if ((maker == ea->Maker) && ("Default" == ea->Model) && (ifd == ea->Ifd) && (caption == ea->Caption)) {
				return ea;
			}
			if ((maker == ea->Maker) && (model == ea->Model) && ("Default" == ea->Ifd) && (caption == ea->Caption)) {
				return ea;
			}
			if ((maker == EnumArray[i]->Maker) && ("Default" == ea->Model) && ("Default" == ea->Ifd) && (caption == ea->Caption)) {
				return ea;
			}
			if (("Default" == EnumArray[i]->Maker) && ("Default" == ea->Model) && (ifd == ea->Ifd) && (caption == ea->Caption)) {
				return ea;
			}
			if (("Default" == EnumArray[i]->Maker) && ("Default" == ea->Model) && ("Default" == ea->Ifd) && caption == ea->Caption) {
				return ea;
			}
		}
	}
	return NULL;
}

bool __fastcall TEnumArrays::QueryEnumFlag(UnicodeString caption, UnicodeString maker, UnicodeString model, UnicodeString ifd, double value, UnicodeString bits) {
	TEnumArray *enumarray;

	enumarray = QueryEnumArray(caption, maker, model, ifd);
	if (enumarray != NULL)
		return enumarray->QueryEnumFlag((unsigned) value, bits);
	else
		return false;
}

#pragma end_region

#pragma region TMapSubIfd

// -----------------------------------------------------
// CLASS TMapSubIfd
// -----------------------------------------------------
TMapSubIfd::TMapSubIfd(void) {
	Caption = L"n/a";
	PIsPointer = false;
	PSeek = 0;
}

UnicodeString __fastcall TMapSubIfd::GetVerbose(void) {
	return Uprintf(L"MapSubIfd: Caption= \"%s\" TagNumber= %#06X IsPointer= %d Seek= %d", Caption.w_str(), PTagNumber, PIsPointer, PSeek);
}


void __fastcall TMapSubIfd::SetMapSubIfd(UnicodeString *caption, unsigned short tagnumber, bool ispointer, int seek) {
	Caption = *caption;
	PTagNumber = tagnumber;
	PIsPointer = ispointer;
	PSeek = seek;
}
#pragma end_region

#pragma region TMapSubIfds

// -----------------------------------------------------
// CLASS TMapSubIfds
// -----------------------------------------------------

TMapSubIfds::TMapSubIfds(void) {
	PVerbose = "MapSubIfds: Count= 0";
}

TMapSubIfds::~TMapSubIfds(void) {
	Clear();
}

void __fastcall TMapSubIfds::Clear(void) {
	while (MapSubIfd.size() != 0) {
		delete MapSubIfd.at(MapSubIfd.size()-1);
		MapSubIfd.pop_back();
	}
}

unsigned __fastcall TMapSubIfds::GetCount(void) {
	return MapSubIfd.size();
}

TMapSubIfd* __fastcall TMapSubIfds::Get(unsigned idx) {
	return MapSubIfd.at(idx);
}

TMapSubIfd* __fastcall TMapSubIfds::Add(void) {
	TMapSubIfd *msi;

	msi = new TMapSubIfd;
	MapSubIfd.push_back(msi);
	PVerbose = Uprintf(L"MapSubIfds: Count= %d", Count);
	return msi;
}

UnicodeString __fastcall TMapSubIfds::QueryMapSubIfdCaption(unsigned short MapSubIfdTagNumber) {
	unsigned i;
	if ((i = QueryMapSubIfdIndex(MapSubIfdTagNumber)) != 0xFFFF)
		return Get(i)->Caption;
	return "";
}

unsigned short __fastcall TMapSubIfds::QueryMapSubIfdTagNumber(UnicodeString *MapSubIfdCaption) {
	unsigned i;
	if ((i = QueryMapSubIfdIndex(MapSubIfdCaption)) != 0xFFFF)
		return Get(i)->TagNumber;
	return 0;
}

bool __fastcall TMapSubIfds::QueryMapSubIfdIsPointer(unsigned short MapSubIfdTagNumber) {
	unsigned i;
	if ((i = QueryMapSubIfdIndex(MapSubIfdTagNumber)) != 0xFFFF)
		return Get(i)->IsPointer;
	return false;
}

int __fastcall TMapSubIfds::QueryMapSubIfdSeek(unsigned short MapSubIfdTagNumber) {
	unsigned i;
	if ((i = QueryMapSubIfdIndex(MapSubIfdTagNumber)) != 0xFFFF)
		return Get(i)->Seek;
	return 0;
}

bool __fastcall TMapSubIfds::QueryMapSubIfdIsPointer(UnicodeString *MapSubIfdCaption) {
	unsigned i;
	if ((i = QueryMapSubIfdIndex(MapSubIfdCaption)) != 0xFFFF)
		return Get(i)->IsPointer;
	return 0;
}

int __fastcall TMapSubIfds::QueryMapSubIfdSeek(UnicodeString *MapSubIfdCaption) {
	unsigned i;
	if ((i = QueryMapSubIfdIndex(MapSubIfdCaption)) != 0xFFFF)
		return Get(i)->Seek;
	return 0;
}

unsigned __fastcall TMapSubIfds::QueryMapSubIfdIndex(UnicodeString *MapSubIfdCaption) {
	unsigned i;
	for (i = 0; i < Count; i++)
		if (Get(i)->Caption == *MapSubIfdCaption)
			return i;
	return 0xFFFF;
}

unsigned __fastcall TMapSubIfds::QueryMapSubIfdIndex(unsigned short MapSubIfdTagNumber) {
	unsigned i;
	for (i = 0; i < Count; i++)
		if (Get(i)->TagNumber == MapSubIfdTagNumber)
			return i;
	return 0xFFFF;
}
#pragma end_region

#pragma region TMapData

// -----------------------------------------------------
// CLASS TMapData
// -----------------------------------------------------
TMapData::TMapData(void) {
	PTagNumber = 0;
	PIndex = 0;
	PUsed = 0;
	PForceType = 0;
	PFormat = 1;
	PSubOffset = 0;
	PDump = False;
	Caption = L"n/a";
	Formula = L"Self";
}

UnicodeString __fastcall TMapData::GetVerbose(void) {
	PVerbose = Uprintf(L"MapData: TagNumber= %#06X Index= %3d Type= %d SubOffset= %#10X Used= %d Dump= %d ", PTagNumber, PIndex, PForceType, PSubOffset, PUsed, PDump);
	if (Formula != L"Self")
		PVerbose += Uprintf(L"Formula= \"%s\" = %s", Caption.w_str(), Formula.w_str());
	else
		PVerbose += Uprintf(L"Caption= \"%s\"", Caption.w_str());
	return PVerbose;
}

#pragma end_region

#pragma region TMapDatas

// -----------------------------------------------------
// CLASS TMapDatas
// -----------------------------------------------------
TMapDatas::TMapDatas(void) {
	PVerbose = "MapDatas: Count= 0";
}

TMapDatas::~TMapDatas(void) {
	Clear();
}

void __fastcall TMapDatas::Clear(void) {
	while (MapData.size() != 0) {
		delete MapData.at(MapData.size()-1);
		MapData.pop_back();
	}
}

unsigned __fastcall TMapDatas::GetCount(void) {
	return MapData.size();
}

TMapData* __fastcall TMapDatas::Get(unsigned idx) {
	return MapData.at(idx);
}

TMapData* __fastcall TMapDatas::Add(void) {
	MapData.push_back(new TMapData);
	PVerbose = Uprintf(L"MapDatas: Count= %d", Count);
	return MapData.at(MapData.size()-1);
}


UnicodeString __fastcall TMapDatas::QueryMapDataCaption(unsigned short DataTagNumber) {
	unsigned i;
	if ((i = QueryMapDataIndex(DataTagNumber)) != 0xFFFF)
		return Get(i)->Caption;
	return "";
}

UnicodeString __fastcall TMapDatas::QueryMapDataFormula(unsigned short DataTagNumber) {
	unsigned i;
	if ((i = QueryMapDataIndex(DataTagNumber)) != 0xFFFF)
		return Get(i)->Formula;
	return "Self";
}

UnicodeString __fastcall TMapDatas::QueryMapDataFormula(UnicodeString *DataCaption) {
	unsigned i;
	if ((i = QueryMapDataIndex(DataCaption)) != 0xFFFF)
		return Get(i)->Formula;
	return "Self";
}

unsigned short __fastcall TMapDatas::QueryMapDataTagNumber(UnicodeString *DataCaption) {
	unsigned i;
	if ((i = QueryMapDataIndex(DataCaption)) != 0xFFFF)
		return Get(i)->TagNumber;
	return 0;
}

unsigned __fastcall TMapDatas::QueryMapDataIndex(UnicodeString *DataCaption) {
	unsigned i;
	for (i = 0; i < Count; i++)
		if (Get(i)->Caption == *DataCaption && Get(i)->Used == 1)
			return i;
	return 0xFFFF;
}

unsigned __fastcall TMapDatas::QueryMapDataIndex(unsigned short DataTagNumber) {
	unsigned i;
	for (i = 0; i < Count; i++)
		if (Get(i)->TagNumber == DataTagNumber && Get(i)->Used == 1)
			return i;
	return 0xFFFF;
}
#pragma end_region

#pragma region TMapIfd

// -----------------------------------------------------
// CLASS TMapIfd
// -----------------------------------------------------
TMapIfd::TMapIfd(void) {
	MapDatas = new TMapDatas;
	MapSubIfds = new TMapSubIfds;
	Caption = L"n/a";
}

TMapIfd::~TMapIfd(void) {
	delete MapDatas;
	delete MapSubIfds;
}

UnicodeString __fastcall TMapIfd::GetVerbose(void) {
	return Uprintf(L"MapIfd: Caption= \"%s\"", Caption.w_str());
}

#pragma end_region

#pragma region TMaPIfds

// -----------------------------------------------------
// CLASS TMaPIfds
// -----------------------------------------------------

TMapIfds::TMapIfds(void) {
	verifadd = 0;
	verifdel = 0;
	verifcopy = 0;
	verifdepop = 0;
}

TMapIfds::~TMapIfds(void) {
	Clear();
	verifdepop = verifdepop + 0;
}

void __fastcall TMapIfds::Clear(void) {
	while (MapIfd.size() != 0) {
		delete MapIfd.at(MapIfd.size()-1);
		MapIfd.at(MapIfd.size()-1) = NULL;
		verifdel++;
		MapIfd.pop_back();
	}
}

unsigned __fastcall TMapIfds::GetCount(void) {
	return MapIfd.size();
}

TMapIfd* __fastcall TMapIfds::Get(unsigned idx) {
	return MapIfd.at(idx);
}

TMapIfd* __fastcall TMapIfds::Add(void) {
	verifadd++;
	TMapIfd *mi = new TMapIfd;
	MapIfd.push_back(mi);
	return mi;
}

TMapIfd* __fastcall TMapIfds::Copy(TMapIfd *mi) {
	verifcopy++;
	MapIfd.push_back(mi);
	return mi;
}

UnicodeString __fastcall TMapIfds::GetVerbose(void) {
	return Uprintf(L"MapIfds: Count= %d", Count);
}

#pragma end_region

#pragma region TMapCamera

// -----------------------------------------------------
// CLASS TMapCamera
// -----------------------------------------------------

TMapCamera::TMapCamera(void) {
	MapIfds          = new TMapIfds;
	LensDatas        = new TLensDatas;
	FlashDatas       = new TFlashDatas;
	MakerCaption     = L"Default";
	Caption          = L"Default";
	ExposureTimeMin  = 0.000125;
	ExposureTimeMax  = 30.0;
	IsoMin           = 100.0;
	IsoMax           = 1600.0;
	FlashFillInLight = -3.5;
	SensorSizeX      = 36.0;
	SensorSizeY      = 24.0;
	Resolution       = 3000000.0;
	SensorCaption    = L"n/a";
	LensBuiltIn      = false;

	IfdFlashFired    = L"";
	IfdFlashOff      = L"";
	IfdFlashExternal = L"";
	IfdFlashBuiltIn  = L"";
	TagFlashFired    = L"None";
	TagFlashOff      = L"None";
	TagFlashExternal = L"None";
	TagFlashBuiltIn  = L"None";
	BitFlashFired    = L"";
	BitFlashOff      = L"";
	BitFlashExternal = L"";
	BitFlashBuiltIn  = L"";

	EnumArrays       = NULL;
}

TMapCamera::~TMapCamera(void) {
	delete MapIfds;
	delete LensDatas;
	delete FlashDatas;
}

UnicodeString __fastcall TMapCamera::GetVerbose(void) {
	return Uprintf(L"MapCamera: Caption= \"%s\"", Caption.w_str());
}

UnicodeString __fastcall TMapCamera::GetMakerModelCaption(void) {
	return Uprintf(L"%s - %s", MakerCaption.Trim().w_str(), Caption.Trim().w_str());
}

void __fastcall TMapCamera::LoadLens(void) {
	LensDatas->Add(MakerCaption, Caption);
}

void __fastcall TMapCamera::LoadFlash(void) {
	FlashDatas->Add(MakerCaption, Caption);
}

unsigned short __fastcall TMapCamera::QueryMapIfdIndex(UnicodeString *MapIfdCaption) {
	unsigned i;
	for (i = 0; i < MapIfds->Count; i++)
		if (*MapIfdCaption == MapIfds->Get(i)->Caption)
			return (unsigned short)(i);
	return 0xFFFF;
}

TEnumArray* __fastcall TMapCamera::QueryEnumArray(UnicodeString caption, UnicodeString maker, UnicodeString model, UnicodeString ifd) {
	return EnumArrays->QueryEnumArray(caption, maker, model, ifd);
}

bool __fastcall TMapCamera::QueryMapData(UnicodeString *MapDataCaption, UnicodeString *MapIfdCaption, unsigned short*MapDataTagNumber, unsigned*MapDataIndex, bool*MapDataMemoryDump) {
	unsigned i, j, used;
	bool flag;

	used = 1000;
	flag = false;
	for (i = 0; i < MapIfds->Count; i++) {
		for (j = 0; j < MapIfds->Get(i)->MapDatas->Count; j++) {
			if (MapIfds->Get(i)->MapDatas->Get(j)->Caption == *MapDataCaption && MapIfds->Get(i)->MapDatas->Get(j)->Used > 0) {
				if (MapIfds->Get(i)->MapDatas->Get(j)->Used < used) {
					used = MapIfds->Get(i)->MapDatas->Get(j)->Used;
					*MapIfdCaption = MapIfds->Get(i)->Caption;
					*MapDataTagNumber = MapIfds->Get(i)->MapDatas->Get(j)->TagNumber;
					*MapDataIndex = MapIfds->Get(i)->MapDatas->Get(j)->Index;
					*MapDataMemoryDump = MapIfds->Get(i)->MapDatas->Get(j)->Dump;
					flag = true;
				}
			}
		}
	}

	return flag;
}

TMapData* __fastcall TMapCamera::QueryMapDataPtr(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex) {
	unsigned i, j;
	for (i = 0; i < MapIfds->Count; i++) {
		if (MapIfds->Get(i)->Caption == *MapIfdCaption) {
			for (j = 0; j < MapIfds->Get(i)->MapDatas->Count; j++) {
				if (MapDataTagNumber == MapIfds->Get(i)->MapDatas->Get(j)->TagNumber && MapDataIndex == MapIfds->Get(i)->MapDatas->Get(j)->Index) {
					return MapIfds->Get(i)->MapDatas->Get(j);
				}
			}
		}
	}
	return NULL;
}

bool __fastcall TMapCamera::QueryMapDataDump(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber) {
	unsigned i, j;
	for (i = 0; i < MapIfds->Count; i++) {
		if (MapIfds->Get(i)->Caption == *MapIfdCaption) {
			for (j = 0; j < MapIfds->Get(i)->MapDatas->Count; j++) {
				if (MapDataTagNumber == MapIfds->Get(i)->MapDatas->Get(j)->TagNumber) {
					return MapIfds->Get(i)->MapDatas->Get(j)->Dump;
				}
			}
		}
	}
	return ForceDump;
}

UnicodeString __fastcall TMapCamera::QueryMapDataCaption(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex) {
	unsigned i, j;
	for (i = 0; i < MapIfds->Count; i++) {
		if (MapIfds->Get(i)->Caption == *MapIfdCaption) {
			for (j = 0; j < MapIfds->Get(i)->MapDatas->Count; j++) {
				if (MapDataTagNumber == MapIfds->Get(i)->MapDatas->Get(j)->TagNumber && MapDataIndex == MapIfds->Get(i)->MapDatas->Get(j)->Index) {
					return MapIfds->Get(i)->MapDatas->Get(j)->Caption;
				}
			}
		}
	}
	return "n/a";
}

UnicodeString __fastcall TMapCamera::QueryMapDataFormula(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex) {
	unsigned i, j;
	for (i = 0; i < MapIfds->Count; i++) {
		if (MapIfds->Get(i)->Caption == *MapIfdCaption) {
			for (j = 0; j < MapIfds->Get(i)->MapDatas->Count; j++) {
				if (MapDataTagNumber == MapIfds->Get(i)->MapDatas->Get(j)->TagNumber && MapDataIndex == MapIfds->Get(i)->MapDatas->Get(j)->Index) {
					return MapIfds->Get(i)->MapDatas->Get(j)->Formula;
				}
			}
		}
	}
	return "Self";
}

unsigned short __fastcall TMapCamera::QueryMapDataForceType(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex) {
	unsigned i, j;
	for (i = 0; i < MapIfds->Count; i++) {
		if (MapIfds->Get(i)->Caption == *MapIfdCaption) {
			for (j = 0; j < MapIfds->Get(i)->MapDatas->Count; j++) {
				if (MapDataTagNumber == MapIfds->Get(i)->MapDatas->Get(j)->TagNumber && MapDataIndex == MapIfds->Get(i)->MapDatas->Get(j)->Index) {
					return MapIfds->Get(i)->MapDatas->Get(j)->ForceType;
				}
			}
		}
	}
	return 0;
}

unsigned __fastcall TMapCamera::QueryMapDataSubOffset(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex) {
	unsigned i, j;
	for (i = 0; i < MapIfds->Count; i++) {
		if (MapIfds->Get(i)->Caption == *MapIfdCaption) {
			for (j = 0; j < MapIfds->Get(i)->MapDatas->Count; j++) {
				if (MapDataTagNumber == MapIfds->Get(i)->MapDatas->Get(j)->TagNumber && MapDataIndex == MapIfds->Get(i)->MapDatas->Get(j)->Index) {
					return MapIfds->Get(i)->MapDatas->Get(j)->SubOffset;
				}
			}
		}
	}
	return 0;
}

unsigned short __fastcall TMapCamera::QueryMapDataTagNumberCount(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber) {
	unsigned i, j;
	unsigned short count;
	count = 0;
	for (i = 0; i < MapIfds->Count; i++) {
		if (MapIfds->Get(i)->Caption == *MapIfdCaption) {
			for (j = 0; j < MapIfds->Get(i)->MapDatas->Count; j++) {
				if (MapDataTagNumber == MapIfds->Get(i)->MapDatas->Get(j)->TagNumber) {
					count++;
				}
			}
		}
	}
	return count;
}

#pragma end_region

#pragma region TMapCameras

// -----------------------------------------------------
// CLASS TMapCameras
// -----------------------------------------------------
TMapCameras::TMapCameras(void) {
}

TMapCameras::~TMapCameras(void) {
	Clear();
}

UnicodeString __fastcall TMapCameras::GetVerbose(void) {
	return Uprintf(L"Cameras: Count= %d", Count);
}

void __fastcall TMapCameras::Clear(void) {
	while (MapCamera.size() != 0) {
		delete MapCamera.at(MapCamera.size()-1);
		MapCamera.pop_back();
	}
}

unsigned __fastcall TMapCameras::GetCount(void) {
	return MapCamera.size();
}

TMapCamera* __fastcall TMapCameras::Get(unsigned idx) {
	return MapCamera.at(idx);
}

TMapCamera* __fastcall TMapCameras::Add(void) {
	TMapCamera *mc;

	mc = new TMapCamera;
	MapCamera.push_back(mc);
	return mc;
}

TMapCamera* __fastcall TMapCameras::QueryMapCamera(UnicodeString *ModelCaption) {
	unsigned i;
	for (i = 0; i < Count; i++) {
		if (*ModelCaption == Get(i)->Caption) {
			return Get(i);
		}
	}
	return Get(0);
}

TMapIfd* __fastcall TMapCameras::QueryMapIfdPtr(UnicodeString *maker, UnicodeString *mapcamera, UnicodeString *ifd) {
	unsigned i, j;
	for (i = 0; i < Count; i++) {
		if ((*maker == Get(i)->MakerCaption) && (*mapcamera == Get(i)->Caption)) {
			for (j = 0; j < Get(i)->MapIfds->Count; j++) {
				if (*ifd == Get(i)->MapIfds->Get(j)->Caption) {
					return Get(i)->MapIfds->Get(j);
				}
			}
		}
	}
	return NULL;
}

#pragma end_region

#pragma region TTagMap

// -----------------------------------------------------
// CLASS TTagMap
// -----------------------------------------------------
TTagMap::TTagMap(TTreeView *treeview) {
	MapCameras = new TMapCameras;
	EnumArrays = NULL;
	TreeView   = treeview;
}

TTagMap::~TTagMap(void) {
	if (MapCameras != NULL)
		delete MapCameras;
	if (EnumArrays != NULL)
		delete EnumArrays;
}

void __fastcall TTagMap::ParseEnumTag(TEnumArray *enumarray, UnicodeString s) {
	unsigned i, j, count;
	UnicodeString str[5];

	count = PointCount(s);
	if (count > 0) {
		for (i = 0; i <= count; i++) {
			j = s.Pos(".");
			str[i] = s.SubString(1, j - 1);
			s = s.SubString(j + 1, s.Length() - j + 1);
		}
		str[i - 1] = s;
	}

	if (count > 0) {
		if (str[count] == L"BitEnum") {
			// Cas .BitEnum
			enumarray->BitEnum = true;
			count--;
			s = str[count];
		}
	}

	if (count == 0) {
		// Cas Caption
		enumarray->Caption = s;
	}
	else if ((count == 1) && ((str[0] == L"Exif") || (str[0] == L"MakerNote") || (str[0].SubString(1, 3) == L"Ifd"))) {
		// Cas Exif.Caption, MakerNote.Caption, Ifd.Caption
		enumarray->Ifd = str[0];
		enumarray->Caption = str[1];
	}
	else if (count == 1) {
		// Cas Maker.Caption
		enumarray->Maker = str[0];
		enumarray->Caption = str[1];
	}
	else if (count == 2) {
		if ((str[1] == L"Exif") || (str[1] == L"MakerNote") || (str[1].SubString(1, 3) == L"Ifd")) {
			// Cas Maker.Ifd.Caption
			enumarray->Maker = str[0];
			enumarray->Ifd = str[1];
			enumarray->Caption = str[2];
		}
		else {
			// Cas Maker.Model.Caption
			enumarray->Maker = str[0];
			enumarray->Model = str[1];
			enumarray->Caption = str[2];
		}
	}
	else if (count == 3) {
		// Cas Maker.Model.Ifd.Caption
		enumarray->Maker = str[0];
		enumarray->Model = str[1];
		enumarray->Ifd = str[2];
		enumarray->Caption = str[3];
	}
	i++; // ?????????????????????????????????????????
}

void __fastcall TTagMap::Debug(UnicodeString txt) {
	UnicodeString s;
	s = txt;
	if (TreeView != NULL) {
		//Memo->Lines->Add(txt);
	}
}

unsigned __fastcall TTagMap::CountSpace(UnicodeString s) {
	unsigned i;
	for (i = 1; i <= (unsigned) s.Length(); i++) {
		if (s[i] != L' ')
			return i;
	}
	return 1;
}

void __fastcall TTagMap::TreeViewLoad(UnicodeString filename) {
	TStringList *sl;
	TTreeViewItem *lv[20];
	int i, c;

	sl = new TStringList;
	sl->LoadFromFile(filename);
	TreeView->BeginUpdate();
	for (i = 0; i < sl->Count; i++) {
		c = CountSpace(sl->Strings[i]);
		lv[c] = new TTreeViewItem(TreeView);
		lv[c]->Text = sl->Strings[i].SubString(c, sl->Strings[i].Length() - c + 1);
		lv[c]->Font->Family = L"Courier new";
		if (c == 1)
			lv[c]->Parent = TreeView;
		else
			lv[c]->Parent = lv[c - 1];

	}
	TreeView->EndUpdate();
	delete sl;
}

void __fastcall TTagMap::LoadFromFile(UnicodeString filename) {
	FILE          *cfp;
	unsigned      i, j, k, countea, countmsi, countmd, countmi, countc;
	unsigned      tagnumber;
	UnicodeString tmp, tmp1;
	UnicodeString maker, model, ifd, makercopy, modelcopy, ifdcopy;
	char          *str1, *str2, *s;
	char c;
	TMapData      *md;
	TEnumArray    *ea;
	TMapSubIfd    *msi;
	TMapIfd       *mi;
	TMapCamera    *mc;

	str1 = (char*) malloc(MAXSTR*sizeof(char));
	str2 = (char*) malloc(MAXSTR*sizeof(char));
	s = (char*)malloc(MAXSTR*sizeof(char));

	cfp = fopen(U2c(filename), "r");
	if (cfp) {
		// Section EnumArrays
		FFGotoSection(cfp, "[EnumArrays]", str1);
		c = 0;
		i = 0;
		while (c != '[') {
			c = char(fgetc(cfp));
			if (c == '{')
				i++;
		}
		if (i > 0) {
			EnumArrays = new TEnumArrays();
			countea = i;
			fseek(cfp, 0, SEEK_SET);
			FFGotoSection(cfp, "[EnumArrays]", str1);
			for (j = 0; j < countea; j++) {
				ea = EnumArrays->Add();
				ParseEnumTag(ea, FFStringUntilEqual(cfp, str1));
				ea->Enums = FFBracketString(cfp, 1, str1);
			}
		}

		fseek(cfp, 0, SEEK_SET);
		// Section MapData
		if (TreeView != NULL)
			TreeView->Clear();
		FFGotoSection(cfp, "[Models MapData]", str1);

		tmp = FFString(cfp, 1, str1);
		if (tmp != L"Models:") {
			Debug("Error section Models MapData -> " + tmp);
			fclose(cfp);
			return;
		}
		tmp = FFString(cfp, 1, str1);
		if (tmp != L"Count=") {
			Debug("Error Models Count -> " + tmp);
			fclose(cfp);
			return;
		}
		countc = FFUnsigned(cfp, 1, str1);
		Debug("Models->Count = " + UnicodeString(countc));

		for (i = 0; i < countc; i++) {
			mc = MapCameras->Add();
			tmp = FFString(cfp, 1, str1);
			if (tmp != L"Model:") {
				Debug("Error Model -> " + tmp);
				fclose(cfp);
				return;
			}
			tmp = FFString(cfp, 1, str1);
			if (tmp != L"Caption=") {
				Debug("Error Model Caption -> " + tmp);
				fclose(cfp);
				return;
			}
			maker = FFQuoteString(cfp, 1, str1);
			model = FFQuoteString(cfp, 1, str1);
			Debug("");
			mc->MakerCaption = maker;
			mc->Caption = model;
			mc->LoadLens();
			mc->LoadFlash();
			mc->EnumArrays = EnumArrays;
			Debug("Models->Caption = " + mc->MakerCaption + " - " + mc->Caption);

			tmp = FFString(cfp, 1, str1);
			while (tmp == L"Set:") {
				tmp = FFStringUntilEqual(cfp, str1);
				if (tmp == L"Sensor") {
					mc->SensorSizeX = FFDouble(cfp, 1, str1);
					mc->SensorSizeY = FFDouble(cfp, 1, str1);
					mc->SensorCaption = FFQuoteString(cfp, 1, str1);
					mc->Resolution = FFDouble(cfp, 1, str1);
				}
				if (tmp == L"ExposureTimeRange") {
					mc->ExposureTimeMin = FFDouble(cfp, 1, str1);
					mc->ExposureTimeMax = FFDouble(cfp, 1, str1);
				}
				if (tmp == L"IsoRange") {
					mc->IsoMin = FFDouble(cfp, 1, str1);
					mc->IsoMax = FFDouble(cfp, 1, str1);
				}
				if (tmp == L"LensBuiltIn") {
					tmp = FFString(cfp, 1, str1);
					if (tmp == L"Yes") {
						mc->LensBuiltIn = true;
					}
				}
				if (tmp == L"FlashFillInLight") {
					mc->FlashFillInLight = FFDouble(cfp, 1, str1);
				}
				tmp = FFString(cfp, 1, str1);
			}

			while (tmp == L"SetBitTag:") {
				tmp = FFString(cfp, 1, str1);
				if (tmp == L"Flash.Fired") {
					mc->IfdFlashFired = FFString(cfp, 1, str1);
					mc->TagFlashFired = FFStringUntilEqual(cfp, str1);
					mc->BitFlashFired = FFString(cfp, 1, str1);
				}
				else if (tmp == L"Flash.Off") {
					mc->IfdFlashOff = FFString(cfp, 1, str1);
					mc->TagFlashOff = FFStringUntilEqual(cfp, str1);
					mc->BitFlashOff = FFString(cfp, 1, str1);
				}
				else if (tmp == L"Flash.External") {
					mc->IfdFlashExternal = FFString(cfp, 1, str1);
					mc->TagFlashExternal = FFStringUntilEqual(cfp, str1);
					mc->BitFlashExternal = FFString(cfp, 1, str1);
				}
				else if (tmp == L"Flash.BuiltIn") {
					mc->IfdFlashBuiltIn = FFString(cfp, 1, str1);
					mc->TagFlashBuiltIn = FFStringUntilEqual(cfp, str1);
					mc->BitFlashBuiltIn = FFString(cfp, 1, str1);
				}
				tmp = FFString(cfp, 1, str1);
			}

			if (tmp != L"MapIfds:") {
				Debug("Error MapIfds -> " + tmp);
				fclose(cfp);
				return;
			}
			tmp = FFString(cfp, 1, str1);
			if (tmp != L"Count=") {
				Debug("Error MapIfds Count -> " + tmp);
				fclose(cfp);
				return;
			}
			countmi = FFUnsigned(cfp, 1, str1);
			Debug("Models->MapIfds->Count = " + UnicodeString(countmi));

			for (j = 0; j < countmi; j++) {
				tmp = FFString(cfp, 1, str1);
				if (tmp != L"MapIfd:") {
					Debug("Error MapIfd -> " + tmp);
					fclose(cfp);
					return;
				}
				tmp = FFString(cfp, 1, str1);
				if (tmp != L"Caption=") {
					Debug("Error MapIfd Caption -> " + tmp);
					fclose(cfp);
					return;
				}
				ifd = FFQuoteString(cfp, 1, str1);
				Debug("Models->Model[" + UnicodeString(i) + "]->MapIfds->MapIfd[" + UnicodeString(j) + "]->Caption = " + ifd);

				tmp = FFString(cfp, 1, str1);

				if (tmp != L"Use:") {
					mi = mc->MapIfds->Add();
					mi->Caption = ifd;
					Debug("Start MapSubIfds");
					if (tmp != L"MapSubIfds:") {
						Debug("Error MapSubIfds -> " + tmp);
						fclose(cfp);
						return;
					}
					tmp = FFString(cfp, 1, str1);
					if (tmp != L"Count=") {
						Debug("Error MapSubIfds Count -> " + tmp);
						fclose(cfp);
						return;
					}
					countmsi = FFUnsigned(cfp, 1, str1);
					Debug("Models->Model[" + UnicodeString(i) + "]->MapIfds->MapIfd[" + UnicodeString(j) + "]->Count = " + UnicodeString(countmsi));

					Debug("Start MapSubIfd");
					for (k = 0; k < countmsi; k++) {
						tmp = FFString(cfp, 1, str1);
						if (tmp != L"MapSubIfd:") {
							Debug("Error MapSubIfd -> " + tmp);
							fclose(cfp);
							return;
						}
						msi            = mi->MapSubIfds->Add();
						msi->Caption   = FFQuoteString(cfp, 2, str1);
						msi->TagNumber = FFUnsignedShortHexa(cfp, 2, str1);
						msi->IsPointer = FFBool(cfp, 2, str1);
						msi->Seek      = FFInt(cfp, 2, str1);
					}
					Debug("End MapSubIfd");
					Debug("End MapSubIfds");

					tmp = FFString(cfp, 1, str1);
					Debug("Start MapDatas");
					if (tmp != L"MapDatas:" && tmp != L"TagNumber=") {
						Debug("   Error MapDatas -> " + UnicodeString(j));
						fclose(cfp);
						return;
					}
					tmp = FFNextString(cfp, 1, str1);
					if (tmp != L"Use:") {
						countmd = FFCount(cfp, "MapData:", "MapIfd:", "Model:", str1, str2);
						Debug("MapData count = " + UnicodeString(countmd));
						for (k = 0; k < countmd; k++) {
							md = mi->MapDatas->Add();
							tmp = FFString(cfp, 1, str1);
							if (tmp != L"Group:" && tmp != L"MapData:") {
								Debug("   Error MapData -> " + UnicodeString(k));
								fclose(cfp);
								return;
							}
							if (tmp == L"Group:") {
								tagnumber = FFUnsignedShortHexa(cfp, 3, str1);
								FFString(cfp, 1, str1);
							}
							if (FFString(cfp, 1, str1) == L"TagNumber=") {
								md->TagNumber = FFUnsignedShortHexa(cfp, 1, str1);
								md->Index = FFUnsigned(cfp, 2, str1);
							}
							else {
								md->TagNumber = (unsigned short)(tagnumber);
								md->Index = FFUnsigned(cfp, 1, str1);
							}
							md->ForceType = (unsigned short) FFUnsigned(cfp, 2, str1);
							md->SubOffset = FFUnsignedHexa(cfp, 2, str1);
							md->Used      = FFUnsigned(cfp, 2, str1);
							md->Dump      = FFBool(cfp, 2, str1);
							md->Format    = FFUnsigned(cfp, 2, str1);
							tmp           = FFString(cfp, 1, str1);
							md->Caption   = FFQuoteString(cfp, 1, str1);
							if (tmp == L"Formula=") {
								md->Formula = FFQuoteString(cfp, 2, str1);
							}
							Debug("MapData -> " + md->Caption);
						}
						Debug("End MapDatas");
					}
					else {
						// Use: MapDatas
						FFString(cfp, 1, str1);
						makercopy = FFStringUntilPoint(cfp, str1);
						modelcopy = FFStringUntilPoint(cfp, str1);
						ifdcopy = FFString(cfp, 1, str1);
						// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    creer Copy
						mi->MapDatas = MapCameras->QueryMapIfdPtr(&makercopy, &modelcopy, &ifdcopy)->MapDatas;
						Debug("Use MapDatas: " + makercopy + "." + modelcopy + "." + ifdcopy);
					}
				}
				else {
					// Use: MapIfd
					makercopy = FFStringUntilPoint(cfp, str1);
					modelcopy = FFStringUntilPoint(cfp, str1);
					ifdcopy = FFString(cfp, 1, str1);
					 /* TODO : Perte de memoire  mi a été réservé.. on réassigne sans detruire l'ancien */
					mc->MapIfds->Copy(MapCameras->QueryMapIfdPtr(&makercopy, &modelcopy, &ifdcopy));
					Debug("Use MapIfd: " + makercopy + "." + modelcopy + "." + ifdcopy);
				}
			}
		}
		fclose(cfp);
		TreeViewLoad(filename);
	}
	free(str1);
	free(str2);
	free(s);
}

#pragma end_region

#endif
