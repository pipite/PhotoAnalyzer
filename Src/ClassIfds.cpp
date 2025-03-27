#ifndef CLASSIFDS
#define CLASSIFDS

#pragma hdrstop

#include "ClassIfds.h"

#pragma package(smart_init)

#pragma region Commentaires
// TIfds              Ifds->Count = 3
// ....TIfd              [00] Ifd0      Offset: 0X00000010 Length =   17
// ........TDatas             Idx:(  0)  Tag:0X0100   Type: 3   Nbr=    1  Offset: 0X00000012 CameraInfo
// ............TData              Idx:(  0) -> Offset: 0X0000001A  signed short [ 0X1440 -> +5184 ] ImageWidth

// TIfds [ Count ]
// ...... QueryDataValue (IfdIndex, DatasTagnumber, DataIndex) .........ex: QueryDataValue (2,0x0002,4) ...........-> 5.6
// ...... QueryDataCalcValue (IfdIndex, DatasTagnumber, DataIndex) .....ex: QueryDataCalcValue (2,0x0002,4) .......-> 5.6
// ...... QueryDataOffset (IfdIndex, DatasTagnumber, DataIndex) ........ex: QueryDataOffset (2,0x0002,4) ..........-> 0x12345678
// ...... QueryDataCaption (IfdIndex, DatasTagnumber, DataIndex) .......ex: QueryDataCaption(2,0x0002,4) ..........-> Canon EOS 7D
// ...... QueryDataType (IfdIndex, DatasTagnumber, DataIndex) ..........ex: QueryDataCaption(2,0x0002,4) ..........-> 1 a 12
// ...... QueryDataDump (IfdIndex, DatasTagnumber, DataIndex) ..........ex: QueryDataDump(2,0x0002,4) .............-> true/false
// ...... QueryDataSubdir (IfdIndex, DatasTagnumber, DataIndex) ........ex: QueryDataDump(2,0x0002,4) .............-> "MakerNote"
// ...... QueryDataValue (IfdCaption, DatasTagnumber, DataIndex) .......ex: QueryDataValue ("MakerNote",0x0002,4)  -> 5.6
// ...... QueryDataOffset (IfdCaption, DatasTagnumber, DataIndex) ......ex: QueryDataOffset ("MakerNote",0x0002,4) -> 0x12345678
// ...... QueryDataCaption (IfdCaption, DatasTagnumber, DataIndex) .....ex: QueryDataCaption("MakerNote",0x0002,4) -> Canon EOS 7D
// ...... QueryDataType (IfdCaption, DatasTagnumber, DataIndex) ........ex: QueryDataCaption("MakerNote",0x0002,4) -> 1 a 12
// ...... QueryDataDump (IfdCaption, DatasTagnumber, DataIndex) ........ex: QueryDataDump("MakerNote",0x0002,4) ...-> true/false
// ...... QueryDataSubdir (IfdCaption, DatasTagnumber, DataIndex) ......ex: QueryDataDump("MakerNote",0x0002,4) ...-> "MakerNote"
// ...... QueryIfdIndex (IfdCaption) ...................................ex: QueryIfdIndex("MakerNote") ............-> 2

// ....TIfd [ Count, Index, Offset, Caption, Verbose ]
// .......... QueryDataValue (DatasTagnumber, DataIndex) ...............ex: QueryDataValue (0x0002,4) .............-> 5.6
// .......... QueryDataCalcValue (DatasTagnumber, DataIndex) ...........ex: QueryDataCalcValue (0x0002,4) .........-> 5.6
// .......... QueryDataOffset (DatasTagnumber, DataIndex) ..............ex: QueryDataOffset (0x0002,4) ............-> 0x12345678
// .......... QueryDataCaption (DatasTagnumber, DataIndex) .............ex: QueryDataCaption(0x0002,4) ............-> Canon EOS 7D
// .......... QueryDataType (DatasTagnumber, DataIndex) ................ex: QueryDataCaption(0x0002,4) ............-> 1 a 12
// .......... QueryDataDump (DatasTagnumber, DataIndex) ................ex: QueryDataDump(0x0002,4) ...............-> true/false
// .......... QueryDataSubdir (DatasTagnumber, DataIndex) ..............ex: QueryDataDump(0x0002,4) ...............-> "MakerNote"

// ........TDatas   [ Count, Index, Offset, Type, TagNumber, Verbose]
// .............. QueryDataValue (DataIndex) ...........................ex: QueryDataValue (4) ....................-> 5.6
// .............. QueryDataCalcValue (DataIndex) .......................ex: QueryDataCalcValue (4) ................-> 5.6
// .............. QueryDataOffset (DataIndex) ..........................ex: QueryDataOffset (4) ...................-> 0x12345678
// .............. QueryDataCaption (DataIndex) .........................ex: QueryDataCaption(4) ...................-> Canon EOS 7D
// .............. QueryDataType (DataIndex) ............................ex: QueryDataCaption(4) ...................-> 1 a 12
// .............. QueryDataDump (DataIndex) ............................ex: QueryDataDump(4) ......................-> true/false
// .............. QueryDataSubdir (DataIndex) ..........................ex: QueryDataDump(4) ......................-> "MakerNote"
// ................TData   [ Caption, Length, Index, Type, Value, Offset, SubDir, Dump, MemData, DumpStr, DumpStrCount, Verbose]
#pragma end_region

#pragma region TData

// -----------------------------------------------------
// CLASS TData
// -----------------------------------------------------
TData::TData(TLgs *lgs) {
	Lgs = lgs;
	PValue = 0;
	PIndex = 0;
	PLength = 0;
	POffset = 0;
	PType = 0;
	PDump = false;
	PURational.Numerator = 0;
	PURational.Denominator = 0;
	PCaption = "n/a";
	SubDir = "";
	PMemData = NULL;
	DumpStr = new TStringList;
	MapData = NULL;
	EnumArray = NULL;
	PDumpStrCount = 0;
	PVerbose = "";
}

TData::~TData(void) {
	if (PMemData != NULL)
		free(PMemData);
	delete DumpStr;
}

UnicodeString __fastcall TData::GetMapDataCaption(void) {
	if (MapData != NULL)
		return MapData->Caption;
	else
		return L"Not mapped";
}

unsigned short __fastcall TData::GetUsed(void) {
	if (MapData != NULL)
		return MapData->Used;
	else
		return 0;
}

UnicodeString __fastcall TData::GetFormula(void) {
	if (MapData != NULL)
		return MapData->Formula;
	else
		return L"Self";
}

unsigned __fastcall TData::GetFormat(void) {
	if (MapData != NULL)
		return MapData->Format;
	else
		return 0;
}

double __fastcall TData::GetCalcValue(void) {
	double x;
	double y;

	if (Formula != L"Self") {
		RVar xvar("Value", &x);
		RVar* vararray[1];
		vararray[0] = &xvar;
		ROperation op(U2c(Formula), 1, vararray);
		if (PType == 1)
			x = (unsigned char)PValue;
		else if (PType == 3)
			x = (signed short)PValue;
		else if (PType == 4)
			x = (unsigned int)PValue;
		else if (PType == 6)
			x = (signed char)PValue;
		else if (PType == 7 || PType == 8)
			x = (signed short)PValue;
		else if (PType == 9)
			x = (signed int)PValue;
		else
			x = PValue;
		y = op.Val();
		return y;
	}
	else
		return PValue;
}

UnicodeString __fastcall TData::GetEnumCaption(void) {
	if (EnumArray != NULL) {
		return EnumArray->QueryEnumCaption(PValue);
	}
	return L"";
}

void __fastcall TData::SetCaption(UnicodeString caption) {
	PLength = caption.Length();
	PCaption = SpecialTrim(caption);
}

void __fastcall TData::SetLength(unsigned length) {
	PLength = length;
	if (Dump) {
		if (PMemData != NULL)
			free(PMemData);
		PMemData = (char*)malloc(length + 1);
	}
}

UnicodeString __fastcall TData::GetCaption(void) {
	if (EnumArray != NULL) {
		return EnumArray->QueryEnumCaption(PValue);
	}
	return PCaption;
}

double __fastcall TData::GetValue(void) {
	return PValue;
}

UnicodeString __fastcall TData::GetVerbose(void) {
	if (Dump) {
		PVerbose = Uprintf(L"Dump      -> Offset: %#010X  Length: %6d %75s%s", POffset, PVirtualLength, "", MapDataCaption.w_str());
	}
	else {
		PVerbose = Uprintf(L"Idx:(%3d) -> Offset: %#010X  ", PIndex, POffset);
		if (PType == 1)
			PVerbose += Uprintf(L"unsigned char                 [ %#04X                  ->        %4d%20s]", (unsigned char)PValue, (unsigned char)PValue, "");
		else if (PType == 2)
			PVerbose += Uprintf(L"char[%04d]%20s%-59s", PLength, L"", PCaption.w_str());
		else if (PType == 3)
			PVerbose += Uprintf(L"signed short                  [ %#06X                ->      %+6d%20s]", (unsigned short)PValue, (signed short)Value, "");
		else if (PType == 4)
			PVerbose += Uprintf(L"signed int                    [ %#010X            -> %+11d%20s]", (unsigned int)PValue, (unsigned int)PValue, "");
		else if (PType == 5) {
			PVerbose += Uprintf(L"unsigned rational             [ %#010X/%#010X ->  %+14.3f ", PURational.Numerator, PURational.Denominator, PValue);
			PVerbose += Uprintf(L"%-15s]", Uprintf(L"(%d/%d)", PURational.Numerator, PURational.Denominator).w_str()); ;
		}
		else if (PType == 10) {
			PVerbose += Uprintf(L"signed rational               [ %#010X/%#010X ->  %+14.3f ", PSRational.Numerator, PSRational.Denominator, PValue);
			PVerbose += Uprintf(L"%-15s]", Uprintf(L"(%d/%d)", PSRational.Numerator, PSRational.Denominator).w_str()); ;
		}
		else
			PVerbose += Uprintf(L"Value:                        [%14.3f   %#010X   %+11d%20s]", Value, Value, Value, "");
		PVerbose += Uprintf(L" %-29s", MapDataCaption.w_str());
		if (Formula != L"Self")
			PVerbose += Uprintf(L"  Formula: %s = %.3f", Formula.w_str(), CalcValue);
		else if (EnumArray != NULL)
			PVerbose += Uprintf(L"  Enum:    %s", EnumCaption.w_str());
	}
	return PVerbose;
}

UnicodeString __fastcall TData::GetShortVerbose(void) {
	UnicodeString s;

	PVerbose = Uprintf(L"%-35s: ", MapDataCaption.w_str());
	if (PType == 1)
		PVerbose += Uprintf(L"%-26d", (unsigned char)PValue);
	else if (PType == 2)
		PVerbose += PCaption;
	else if (PType == 3)
		PVerbose += Uprintf(L"%-26d", (signed short)PValue);
	else if (PType == 4)
		PVerbose += Uprintf(L"%-26d", (signed int)PValue);
	else if ((PType == 5) || (PType == 10)) {
		s = Uprintf(L"%d/%d", PURational.Numerator, PURational.Denominator);
		PVerbose += Uprintf(L"%-26s= %-10.4f", s.w_str(), PValue);
	}
	else
		PVerbose += Uprintf(L"%-26d", Value);

	if (EnumArray != NULL)
		PVerbose += Uprintf(L"= %s", EnumCaption.w_str());
	else if (Formula != L"Self") {
		if ((PType == 5) || (PType == 10)) {
			PVerbose += Uprintf(L" --> %s = %-10.4f", Formula.w_str(), CalcValue);
		} else {
			PVerbose += Uprintf(L"= %.3f --> %s = %-10.4f", PValue, Formula.w_str(), CalcValue);
		}
	}
	return PVerbose;
}

UnicodeString __fastcall TData::GetUserVerbose(void) {
	UnicodeString s;

	if (Format != 0) {
		PVerbose = Uprintf(L"%-35s: ", MapDataCaption.w_str());
		if (Format == 1) {
			if (PType == 2) {
				if (PCaption.Trim() == L"") {
					return L"";
				}
				PVerbose += PCaption;
			}
			else if (EnumArray != NULL)
				PVerbose += Uprintf(L"%s", EnumCaption.w_str());
			else if (Formula != L"Self")
				PVerbose += Uprintf(L"%-10.4f", CalcValue);
			else if (PType == 1)
				PVerbose += Uprintf(L"%-26d", (unsigned char)PValue);
			else if (PType == 3)
				PVerbose += Uprintf(L"%-26d", (signed short)PValue);
			else if (PType == 4)
				PVerbose += Uprintf(L"%-26d", (signed int)PValue);
			else if ((PType == 5) || (PType == 10))
				PVerbose += Uprintf(L"%-10.4f", PValue);
			else
				PVerbose += Uprintf(L"%-26d", Value);
		}
		else {
			if (Format == 2) { // Aperture
				PVerbose += ApertureFormat(CalcValue);
			}
			else if (Format == 3) { // ExposureTimeFormat
				PVerbose += ExposureTimeFormat(CalcValue);
			}
			else if (Format == 4) { // IsoFormat
				PVerbose += IsoFormat(CalcValue);
			}
			else if (Format == 5) { // FocaleFormat
				PVerbose += FocaleFormat(CalcValue);
			}
			else if (Format == 6) { // FocusDistanceFormat
				PVerbose += FocusDistanceFormat(CalcValue, false);
			}
			else if (Format == 7) { // ExposureFormat
				PVerbose += ExposureFormat(CalcValue, Lgs);
			}
		}
		return PVerbose;
	}
	else {
		return L"";
	}
}

bool __fastcall TData::GenerateDumpStr(unsigned nlong) {
	unsigned a, b, n;
	UnicodeString tmp1;
	UnicodeString tmp2;
	char ch;

	if (Dump) {
		a = n = 0;
		DumpStr->Clear();
		while (a < PLength) {
			a += nlong;
			n++;
		}
		if (n > 0)
			PDumpStrCount = n;

		a = n = 0;
		while (a < PLength) {
			tmp1 = L"[";
			tmp2 = L"";
			b = 0;
			while (a < PLength && b < nlong) {
				ch = PMemData[a];
				if (ch >= 32 && ch < 127)
					tmp2 += UnicodeString(ch);
				else
					tmp2 += L".";
				tmp1 += Uprintf(L"%02X", (char)ch & 0x00FF);
				a++;
				b++;
				if (b < nlong && a < PLength)
					tmp1 += L",";
			}
			while (b++ < nlong)
				tmp1 += L"   ";
			DumpStr->Add(tmp1 + L"] " + tmp2);
			n++;
			b = 0;
		}
		return true;
	}
	else {
		return false;
	}
}

#pragma end_region

#pragma region TDatas

// -----------------------------------------------------
// CLASS TDatas    6 query
// -----------------------------------------------------
TDatas::TDatas(TLgs *lgs) {
	Lgs = lgs;
	PTagNumber = 0;
	PType = 0;
	POffset = 0;
	PIndex = 0;
}

TDatas::~TDatas(void) {
	Clear();
}

UnicodeString __fastcall TDatas::GetVerbose(void) {
	return Uprintf(L"Idx:(%3d)  Tag:%#06X   Type:%2d   Nbr= %4d  Offset: %#010X", PIndex, PTagNumber, PType, Count, POffset);
}

unsigned __fastcall TDatas::GetCount(void) {
	return Data.size();
}

void __fastcall TDatas::SetCount(unsigned count) {
	unsigned i;
	Clear();
	if (count > 0) {
		for (i = 0; i < count; i++)
			Data.push_back(new TData(Lgs));
	}
}

void __fastcall TDatas::Clear(void) {
	unsigned i;

	for (i = 0; i < Data.size(); i++) {
		if ( Data.at(i) != NULL ) {
			delete Data.at(i);
			Data.at(i) = NULL;
		}
	}
	Data.empty();
}

TData* __fastcall TDatas::GetData(unsigned idx) {
	return Data.at(idx);
}

double __fastcall TDatas::QueryDataValue(unsigned DataIndex) {
	if (DataIndex < Data.size())
		return GetData(DataIndex)->Value;
	return 0.0;
}

double __fastcall TDatas::QueryDataCalcValue(unsigned DataIndex) {
	if (DataIndex < Data.size())
		return GetData(DataIndex)->CalcValue;
	return 0.0;
}

unsigned __fastcall TDatas::QueryDataOffset(unsigned DataIndex) {
	if (DataIndex < Data.size())
		return GetData(DataIndex)->Offset;
	return 0;
}

unsigned __fastcall TDatas::QueryDataFormat(unsigned DataIndex) {
	if (DataIndex < Data.size())
		return GetData(DataIndex)->Format;
	return 0;
}

UnicodeString __fastcall TDatas::QueryDataCaption(unsigned DataIndex) {
	if (DataIndex < Data.size())
		return GetData(DataIndex)->Caption;
	return "";
}

UnicodeString __fastcall TDatas::QueryDataVerbose(unsigned DataIndex) {
	if (DataIndex < Data.size())
		return GetData(DataIndex)->Verbose;
	return "";
}

unsigned short __fastcall TDatas::QueryDataType(unsigned DataIndex) {
	if (DataIndex < Data.size())
		return GetData(DataIndex)->Type;
	return 0;
}

bool __fastcall TDatas::QueryDataDump(unsigned DataIndex) {
	if (DataIndex < Data.size())
		return GetData(DataIndex)->Dump;
	return true;
}

UnicodeString __fastcall TDatas::QueryDataSubDir(unsigned DataIndex) {
	if (DataIndex < Data.size())
		return GetData(DataIndex)->SubDir;
	return "";
}
#pragma end_region

#pragma region TIfd

// -----------------------------------------------------
// CLASS TIfd      6 query
// -----------------------------------------------------
TIfd::TIfd(TLgs *lgs) {
	Lgs = lgs;
	Caption = L"";
	POffset = 0;
}

TIfd::~TIfd(void) {
	Clear();
}

UnicodeString __fastcall TIfd::GetVerbose(void) {
	return Uprintf(L"%-9s Offset: %#010X Length = %4d", Caption.w_str(), POffset, Count);
}

void __fastcall TIfd::SetCount(unsigned short count) {
	unsigned short i;
	Clear();
	if (count > 0) {
		for (i = 0; i < count; i++)
			Datas.push_back(new TDatas(Lgs));
	}
}

unsigned short __fastcall TIfd::GetCount(void) {
	return (unsigned short) Datas.size();
}

void __fastcall TIfd::Clear(void) {
	unsigned i;

	for (i = 0; i < Datas.size(); i++) {
		delete Datas.at(i);
	}
	Datas.empty();
}

TDatas* __fastcall TIfd::GetDatas(unsigned idx) {
	return Datas.at(idx);
}

void __fastcall TIfd::Parse(FILE *ifp, unsigned base, TMapCamera *mapcamera, int *ByteOrder) { // Parse Ifd
	unsigned i, j;
	unsigned count;
	unsigned idx = 0;
	char *tmp;
	unsigned save, sv = 0, sv1 = 0;
	SURational urational;
	SSRational srational;
	unsigned short entries, number, type;
	bool dump;
	unsigned short forcetype;
	UnicodeString s;
	TDatas *ds;
	TData *d;

	save = ftell(ifp);
	fseek(ifp, base + POffset, SEEK_SET);
	SetCount(Get2(ifp, ByteOrder));
	entries = Count;
	while (entries--) {
		ds = GetDatas(idx);
		ds->Offset = ftell(ifp);
		number = Get2(ifp, ByteOrder);
		type = Get2(ifp, ByteOrder);
		count = Get4(ifp, ByteOrder);
		sv = ftell(ifp) + 4;
		if (type > 13)
			type = 0;
		if ((count * GetSizeOf(&type)) > 4)
			fseek(ifp, Get4(ifp, ByteOrder) + base, SEEK_SET);

		ds->Type = type;
		dump = mapcamera->QueryMapDataDump(&Caption, number);

		// Verification si type forcé dans le number
		forcetype = mapcamera->QueryMapDataForceType(&Caption, number, 0);
		if (forcetype > 0) {
			sv1 = ftell(ifp);
			ds->Count = mapcamera->QueryMapDataTagNumberCount(&Caption, number);

			for (i = 0; i < GetDatas(idx)->Count; i++) {
				d = ds->GetData(i);
				d->MapData = mapcamera->QueryMapDataPtr(&Caption, number, i);
				forcetype = mapcamera->QueryMapDataForceType(&Caption, number, i);
				if (forcetype == 2) {
					d->Length = GetStringLenZeroTerminal(ifp);
					d->Offset = ftell(ifp);
					tmp = (char*)malloc(d->Length + 1);
					fread(tmp, d->Length, 1, ifp);
					d->Caption = tmp;
					free(tmp);
					d->Type = forcetype;
				}
				else {
					d->Length = GetSizeOf(&forcetype);
					fseek(ifp, sv1 + mapcamera->QueryMapDataSubOffset(&Caption, number, i), SEEK_SET);
					d->Offset = ftell(ifp);
					d->Type = forcetype;
					if (forcetype == 5) {
						d->Value = GetURational(ifp, &urational, ByteOrder);
						d->URational.Numerator = urational.Numerator;
						d->URational.Denominator = urational.Denominator;
					}
					else if (forcetype == 10) {
						d->Value = GetSRational(ifp, &srational, ByteOrder);
						d->SRational.Numerator = srational.Numerator;
						d->SRational.Denominator = srational.Denominator;
					}
					else {
						d->Value = (double)GetReal(ifp, forcetype, ByteOrder);
					}
					d->Index = i;
				}
				d->EnumArray = mapcamera->QueryEnumArray(d->MapDataCaption, mapcamera->MakerCaption, mapcamera->Caption, Caption);
			}
			fseek(ifp, sv1 + count, SEEK_SET);
		}

		else if (type == 2 && dump) {
			ds->Count = 1;
			d = GetDatas(idx)->GetData(0);
			d->MapData = mapcamera->QueryMapDataPtr(&Caption, number, 0);
			d->Type = type;
			d->Length = count;
			d->Offset = ftell(ifp);
			tmp = (char*)malloc(count + 1);
			fread(tmp, count, 1, ifp);
			d->Caption = tmp;
			free(tmp);
			d->EnumArray = mapcamera->QueryEnumArray(d->MapDataCaption, mapcamera->MakerCaption, mapcamera->Caption, Caption);
		}
		else if (type != 7 && type <= 12 && dump) {
			if (count > 2500)
				count = 2500;
			ds->Count = count;
			for (j = 0; j < count; j++) {
				d = ds->GetData(j);
				d->MapData = mapcamera->QueryMapDataPtr(&Caption, number, j);
				d->Length = GetSizeOf(&type);
				d->Offset = ftell(ifp);
				if (type == 5) {
					d->Value = GetURational(ifp, &urational, ByteOrder);
					d->URational.Numerator = urational.Numerator;
					d->URational.Denominator = urational.Denominator;
				}
				else if (type == 10) {
					d->Value = GetSRational(ifp, &srational, ByteOrder);
					d->SRational.Numerator = srational.Numerator;
					d->SRational.Denominator = srational.Denominator;
				}
				else {
					d->Value = (double)GetReal(ifp, type, ByteOrder);
				}
				d->Index = j;
				d->Type = type;
				d->EnumArray = mapcamera->QueryEnumArray(d->MapDataCaption, mapcamera->MakerCaption, mapcamera->Caption, Caption);
			}
		}
		else if (dump) {
			ds->Count = 1;
			d = GetDatas(idx)->GetData(0);
			d->MapData = mapcamera->QueryMapDataPtr(&Caption, number, 0);
			d->Offset = ftell(ifp);
			d->Dump = true;
			d->Length = count;
			d->VirtualLength = count;
			fread(d->MemData, count, 1, ifp);
		}
		else {
			ds->Count = 1;
			d = GetDatas(idx)->GetData(0);
			d->MapData = mapcamera->QueryMapDataPtr(&Caption, number, 0);
			d->Offset = ftell(ifp);
			d->Dump = true;
			d->Length = 12;
			d->VirtualLength = count;
			fread(d->MemData, 12, 1, ifp);
		}
		ds->TagNumber = number;
		ds->Index = idx;
		idx++;
		fseek(ifp, sv, SEEK_SET);
	}
	fseek(ifp, save, SEEK_SET);
}

// Query
double __fastcall TIfd::QueryDataValue(unsigned short DatasTagnumber, unsigned DataIndex) {
	unsigned short i;
	for (i = 0; i < Count; i++)
		if (GetDatas(i)->TagNumber == DatasTagnumber)
			return GetDatas(i)->QueryDataValue(DataIndex);
	return 0.0;
}

double __fastcall TIfd::QueryDataCalcValue(unsigned short DatasTagnumber, unsigned DataIndex) {
	unsigned short i;
	for (i = 0; i < Count; i++)
		if (GetDatas(i)->TagNumber == DatasTagnumber)
			return GetDatas(i)->QueryDataCalcValue(DataIndex);
	return 0.0;
}

unsigned __fastcall TIfd::QueryDataOffset(unsigned short DatasTagnumber, unsigned DataIndex) {
	unsigned short i;
	for (i = 0; i < Count; i++)
		if (GetDatas(i)->TagNumber == DatasTagnumber)
			return GetDatas(i)->QueryDataOffset(DataIndex);
	return 0;
}

UnicodeString __fastcall TIfd::QueryDataCaption(unsigned short DatasTagnumber, unsigned DataIndex) {
	unsigned short i;
	for (i = 0; i < Count; i++)
		if (GetDatas(i)->TagNumber == DatasTagnumber)
			return GetDatas(i)->QueryDataCaption(DataIndex);
	return "n/a";
}

UnicodeString __fastcall TIfd::QueryDataVerbose(unsigned short DatasTagnumber, unsigned DataIndex) {
	unsigned short i;
	for (i = 0; i < Count; i++)
		if (GetDatas(i)->TagNumber == DatasTagnumber)
			return GetDatas(i)->QueryDataVerbose(DataIndex);
	return "n/a";
}

unsigned short __fastcall TIfd::QueryDataType(unsigned short DatasTagnumber, unsigned DataIndex) {
	unsigned short i;
	for (i = 0; i < Count; i++)
		if (GetDatas(i)->TagNumber == DatasTagnumber)
			return GetDatas(i)->QueryDataType(DataIndex);
	return 0;
}

bool __fastcall TIfd::QueryDataDump(unsigned short DatasTagnumber, unsigned DataIndex) {
	unsigned short i;
	for (i = 0; i < Count; i++)
		if (GetDatas(i)->TagNumber == DatasTagnumber)
			return GetDatas(i)->QueryDataDump(DataIndex);
	return true;
}

UnicodeString __fastcall TIfd::QueryDataSubDir(unsigned short DatasTagnumber, unsigned DataIndex) {
	unsigned short i;
	for (i = 0; i < Count; i++)
		if (GetDatas(i)->TagNumber == DatasTagnumber)
			return GetDatas(i)->QueryDataSubDir(DataIndex);
	return "";
}
#pragma end_region

#pragma region TFileHeader

// -----------------------------------------------------
// CLASS TFileHeader
// -----------------------------------------------------
TFileHeader::TFileHeader(void) {
	PHead = (char*)malloc(48 * sizeof(char));
	PHeaderLength = 0;
	PFileSize = 0;
	PFirstIfdsOffset = 0;
	PFormat = L"Undef";
	strcpy(PHead, "");
}

TFileHeader::~TFileHeader(void) {
	free(PHead);
}

bool __fastcall TFileHeader::parse(FILE *ifp, unsigned *Baseifp, int *ByteOrder) {
	unsigned short ushort;
	unsigned short idx;

	idx = 0;
	fseek(ifp, 0, SEEK_END);
	PFileSize = ftell(ifp);
	fseek(ifp, 0, SEEK_SET);
	fread(PHead, 1, 48, ifp);
	idx = 0x0002;
	*ByteOrder = 0;
	ushort = Sget2((unsigned char*)PHead, unsigned(0x0000), ByteOrder);
			 //Sget2(unsigned char *c, unsigned pos, int *ByteOrder)
	// Analyse format
	if (ushort == 0x4949 || ushort == 0x4d4d) {
		*ByteOrder = ushort;
		if (Sget2((unsigned char*)PHead, 0x0002, ByteOrder) == 0x002a && PHead[8] == 0x43 && PHead[9] == 0x52 && PHead[10] == 0x02) {
			// Canon CR2
			PFormat = Uprintf(L"CR%d.%d", PHead[0x00a], PHead[0x00b]);
			PFirstIfdsOffset = Sget4((unsigned char*)PHead, 0x0004, ByteOrder);
			*Baseifp = 0x0000;
			return true;
		}
	}
	else if (ushort == 0xFFD8) { // Marqueur SOI JPEG (65496)
		idx = 0x0004;
		ushort = Sget2((unsigned char*)PHead, 0x0002, ByteOrder);
		if (ushort == 0xFFE0) { // Marqueur APP0 (65504)
			if (PHead[6] == 'J' && PHead[7] == 'F' && PHead[8] == 'I' && PHead[9] == 'F' && PHead[10] == 0x00) {
				// JFIF
				idx = Sget2((unsigned char*)PHead, 0x0004, ByteOrder) + idx;
				ushort = Sget2((unsigned char*)PHead, idx, ByteOrder);
				idx += 2;
			}
		}
		if (ushort == 0xFFE1) { // Marqueur APP1 (65505)
			idx += 2;
			if (PHead[idx] == 'E' && PHead[idx + 1] == 'x' && PHead[idx + 2] == 'i' && PHead[idx + 3] == 'f' && PHead[idx + 4] == 0x00 && PHead[idx + 5] == 0x00) {
				// Exif
				idx += 6;
				base = idx;
				ushort = Sget2((unsigned char*)PHead, idx, ByteOrder);
				idx += 2;
			}
		}
		if (ushort == 0x4949 || ushort == 0x4d4d) { // (18761=0x4949 19789=0x4d4d)
			*ByteOrder = ushort;
			if (PHead[idx] == 0x2A && PHead[idx + 1] == 0x00) { // Marqueur TIFF
				idx += 2;
				// TIFF
				PFormat = L"JPG";
				PFirstIfdsOffset = Sget2((unsigned char*)PHead, idx, ByteOrder);
				*Baseifp = base;
				return true;
			}
		}
	}
	return false;
}
#pragma end_region

#pragma region TIfds

// -----------------------------------------------------
// CLASS TIfds    13 query
// -----------------------------------------------------
TIfds::TIfds(TTagMap *tagmap, TLgs *lgs) {
	Lgs = lgs;
	FileHeader = new TFileHeader;
	TagMap = tagmap;
	ByteOrder = 0;
	MapCamera = TagMap->MapCameras->MapCamera[0];
}

TIfds::~TIfds() {
	delete FileHeader;
	Clear();
}

void __fastcall TIfds::SetCount(unsigned short count) {
	unsigned short i;
	Clear();
	if (count > 0) {
		for (i = 0; i < count; i++)
			Ifd.push_back(new TIfd(Lgs));
	}
}

unsigned short __fastcall TIfds::GetCount(void) {
	return (unsigned short) Ifd.size();
}

UnicodeString __fastcall TIfds::GetVerbose(void) {
	return Uprintf(L"Ifds->Count = %4d", Count);
}

unsigned __fastcall TIfds::RecurseParseSubDir(FILE *ifp, unsigned base, unsigned idxifd, UnicodeString *parentname, TMapCamera *mapcamera) {
	unsigned idx;
	unsigned i;
	TMapSubIfds* msis;
	TMapSubIfd* msi;

	idx = idxifd;
	idxifd = mapcamera->QueryMapIfdIndex(parentname);
	if (mapcamera->MapIfds->Count >= idxifd) {
		msis = mapcamera->MapIfds->MapIfd[idxifd]->MapSubIfds;
		for (i = 0; i < msis->Count; i++) {
			msi = msis->MapSubIfd[i];
			GetIfd(idx + 1)->Caption = msi->Caption;

			fseek(ifp, GetIfd(idx)->QueryDataOffset(msi->TagNumber, 0), SEEK_SET);
			if (msi->IsPointer)
				fseek(ifp, Get4(ifp, &ByteOrder) + base, SEEK_SET);
			if (msi->Seek > 0)
				fseek(ifp, msi->Seek, SEEK_CUR);

			GetIfd(idx + 1)->Offset = ftell(ifp) - base;
			GetIfd(idx + 1)->Parse(ifp, base, mapcamera, &ByteOrder);
			idx++;

			if (msis->Count) {
				idxifd = idx;
				idxifd = RecurseParseSubDir(ifp, base, idxifd, &(GetIfd(idxifd)->Caption), mapcamera);
				idx++;
			}
		}
	}
	return idx;
}

void __fastcall TIfds::Clear(void) {
	unsigned i;

	for (i = 0; i < Ifd.size(); i++) {
		delete Ifd.at(i);
	}
	Ifd.empty();
}

TIfd* __fastcall TIfds::GetIfd(unsigned idx) {
	return Ifd.at(idx);
}

void __fastcall TIfds::Parse(FILE *ifp, unsigned *Baseifp) {
	unsigned save;
	unsigned count, idxifd, ifdname;
	UnicodeString cameraname;

	if (FileHeader->parse(ifp, Baseifp, &ByteOrder)) {
		idxifd = 0;
		ifdname = 0;
		Count = 15;
		fseek(ifp, *Baseifp + FileHeader->FirstIfdsOffset, SEEK_SET);

		count = Get2(ifp, &ByteOrder);
		save = ftell(ifp);
		fseek(ifp, -2, SEEK_CUR);
		if (count <= 512) {
			GetIfd(idxifd)->Caption = L"Ifd0";
			GetIfd(idxifd)->Offset = ftell(ifp) - *Baseifp;
			GetIfd(idxifd)->Parse(ifp, *Baseifp, TagMap->MapCameras->MapCamera[0], &ByteOrder);
			ifdname++;
		}

		cameraname = GetIfd(idxifd)->QueryDataCaption(0x0110, 0);
		MapCamera = TagMap->MapCameras->QueryMapCamera(&cameraname);

		if (MapCamera != NULL) {
			while (1) {
				idxifd = RecurseParseSubDir(ifp, *Baseifp, idxifd, &(GetIfd(idxifd)->Caption), MapCamera);
				idxifd++;
				fseek(ifp, save + 12 * count, SEEK_SET);
				fseek(ifp, Get4(ifp, &ByteOrder) + *Baseifp, SEEK_SET);
				count = Get2(ifp, &ByteOrder);
				save = ftell(ifp);
				fseek(ifp, -2, SEEK_CUR);
				if (count <= 512) {
					GetIfd(idxifd)->Caption = Uprintf(L"Ifd%d", ifdname);
					GetIfd(idxifd)->Offset = ftell(ifp) - *Baseifp;
					GetIfd(idxifd)->Parse(ifp, *Baseifp, MapCamera, &ByteOrder);
					ifdname++;
				}
				else
					break;
			}
		}
	}
}

// Query
double __fastcall TIfds::QueryDataValue(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(IfdIndex)->QueryDataValue(DatasTagnumber, DataIndex);
}

double __fastcall TIfds::QueryDataCalcValue(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(IfdIndex)->QueryDataCalcValue(DatasTagnumber, DataIndex);
}

unsigned __fastcall TIfds::QueryDataOffset(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(IfdIndex)->QueryDataOffset(DatasTagnumber, DataIndex); ;
}

UnicodeString __fastcall TIfds::QueryDataCaption(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(IfdIndex)->QueryDataCaption(DatasTagnumber, DataIndex);
}

UnicodeString __fastcall TIfds::QueryDataVerbose(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(IfdIndex)->QueryDataVerbose(DatasTagnumber, DataIndex);
}

unsigned short __fastcall TIfds::QueryDataType(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(IfdIndex)->QueryDataType(DatasTagnumber, DataIndex); ;
}

bool __fastcall TIfds::QueryDataDump(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(IfdIndex)->QueryDataDump(DatasTagnumber, DataIndex); ;
}

UnicodeString __fastcall TIfds::QueryDataSubDir(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(IfdIndex)->QueryDataSubDir(DatasTagnumber, DataIndex);
}

double __fastcall TIfds::QueryDataValue(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(QueryIfdIndex(IfdCaption))->QueryDataValue(DatasTagnumber, DataIndex);
}

unsigned __fastcall TIfds::QueryDataOffset(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(QueryIfdIndex(IfdCaption))->QueryDataOffset(DatasTagnumber, DataIndex); ;
}

UnicodeString __fastcall TIfds::QueryDataCaption(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(QueryIfdIndex(IfdCaption))->QueryDataCaption(DatasTagnumber, DataIndex);
}

UnicodeString __fastcall TIfds::QueryDataVerbose(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(QueryIfdIndex(IfdCaption))->QueryDataVerbose(DatasTagnumber, DataIndex);
}

unsigned short __fastcall TIfds::QueryDataType(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(QueryIfdIndex(IfdCaption))->QueryDataType(DatasTagnumber, DataIndex); ;
}

bool __fastcall TIfds::QueryDataDump(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(QueryIfdIndex(IfdCaption))->QueryDataDump(DatasTagnumber, DataIndex); ;
}

UnicodeString __fastcall TIfds::QueryDataSubDir(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex) {
	return GetIfd(QueryIfdIndex(IfdCaption))->QueryDataSubDir(DatasTagnumber, DataIndex);
}

unsigned short __fastcall TIfds::QueryIfdIndex(UnicodeString *IfdCaption) {
	unsigned short i;
	for (i = 0; i < Count; i++)
		if (GetIfd(i)->Caption == *IfdCaption)
			return i;
	return 0xFFFF;
}
#pragma end_region

#endif
