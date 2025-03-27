#ifndef CLASSANALYS
#define CLASSANALYS

#pragma hdrstop

#include "ClassAnalys.h"

#pragma package(smart_init)

#pragma region TApex

// -----------------------------------------------------
// CLASS TApex
// -----------------------------------------------------
TApex::TApex(void) {
	PIsoRef = 100;
	PApertureRef = 16;
	PExposureTimeRef = 1.0 / PIsoRef;
}

TApex::~TApex(void) {
}

double __fastcall TApex::GetExposureTimeApexRef(void) {
	return ExposureTime2Apex(PExposureTimeRef);
}

double __fastcall TApex::GetApertureApexRef(void) {
	return Aperture2Apex(PApertureRef);
}

double __fastcall TApex::GetIsoApexRef(void) {
	return Iso2Apex(PIsoRef);
}

double __fastcall TApex::GetApexRef(void) {
	return ExposureTimeApexRef + ApertureApexRef;
}

double __fastcall TApex::Iso2Apex(double s) {
	if (s > 0)
		return log(s / 3.125) / log(2.0);
	else
		return 0.0;
}

double __fastcall TApex::Apex2Iso(double sv) {
	return pow(CNEPER, ((sv * log(2.0)) + log(3.125)));
}

double __fastcall TApex::Aperture2Apex(double a) {
	if (a > 0)
		return 2 * log(a) / log(2.0);
	else
		return 0.0;
}

double __fastcall TApex::Apex2Aperture(double av) {
	return pow(CNEPER, (av * log(2.0)) / 2);
}

double __fastcall TApex::ExposureTime2Apex(double t) {
	if (t > 0)
		return -log(t) / log(2.0);
	else
		return 0.0;
}

double __fastcall TApex::Apex2ExposureTime(double tv) {
	return pow(CNEPER, -tv * log(2.0));
}

double __fastcall TApex::ApexOf(double t, double a, double s) {
	return ExposureTime2Apex(t) + Aperture2Apex(a) + IsoApexRef - Iso2Apex(s);
}

double __fastcall TApex::ApexDelta(double t, double a, double s, double ev) {
	return ev - ApexOf(t, a, s);
}

double __fastcall TApex::PerfectExposureTime(double a, double s, double ev) {
	return Apex2ExposureTime(ev + Iso2Apex(s) - Aperture2Apex(a) - IsoApexRef);
}

double __fastcall TApex::PerfectAperture(double t, double s, double ev) {
	return Apex2Aperture(ev + Iso2Apex(s) - ExposureTime2Apex(t) - IsoApexRef);
}

double __fastcall TApex::PerfectIso(double t, double a, double ev) {
	return Apex2Iso(ExposureTime2Apex(t) + Aperture2Apex(a) + IsoApexRef - ev);
}
#pragma end_region

#pragma region TCoc

// -----------------------------------------------------
// CLASS TCoc
// -----------------------------------------------------
TCoc::TCoc(TAnalys *analys) {
	Analys = analys;
}

UnicodeString __fastcall TCoc::GetCaption(void) {
	return Uprintf(L"%.3f", Value);
}

double __fastcall TCoc::GetValue(void) {
	if (Analys->MapCamera != NULL) {
		if ((Analys->MapCamera->SensorSizeX > 0.0) && (Analys->MapCamera->SensorSizeY > 0.0)) {
			return (1.0 / 1500.0) * sqrt((Analys->MapCamera->SensorSizeX * Analys->MapCamera->SensorSizeX) + (Analys->MapCamera->SensorSizeY * Analys->MapCamera->SensorSizeY));
		}
	}
	return 0.0;
}



#pragma end_region

#pragma region TCropFactor

// -----------------------------------------------------
// CLASS TCropFactor
// -----------------------------------------------------
TCropFactor::TCropFactor(TAnalys *analys) {
	Analys = analys;
}

UnicodeString __fastcall TCropFactor::GetCaption(void) {
	return Uprintf(L"%.3f", Value);
}

double __fastcall TCropFactor::GetValue(void) {
	if (Analys->MapCamera != NULL) {
		if ((Analys->MapCamera->SensorSizeX > 0.0) && (Analys->MapCamera->SensorSizeY > 0.0)) {
			return 43 / sqrt((Analys->MapCamera->SensorSizeX * Analys->MapCamera->SensorSizeX) + (Analys->MapCamera->SensorSizeY * Analys->MapCamera->SensorSizeY));
		}
	}
	return 0.0;
}



#pragma end_region

#pragma region TPixelSize

// -----------------------------------------------------
// CLASS TPixelSize
// -----------------------------------------------------
TPixelSize::TPixelSize(TAnalys *analys) {
	Analys = analys;
}

UnicodeString __fastcall TPixelSize::GetCaption(void) {
	return Uprintf(L"%.6f", Value);
}

double __fastcall TPixelSize::GetValue(void) {
	double r, x, y;
	if (Analys->MapCamera != NULL) {
		if ((Analys->MapCamera->SensorSizeX > 0.0) && (Analys->MapCamera->SensorSizeY > 0.0) && Analys->MapCamera->Resolution > 0.0) {
			r = Analys->MapCamera->SensorSizeX * Analys->MapCamera->SensorSizeY / Analys->MapCamera->Resolution;
			x = Analys->MapCamera->SensorSizeX * r;
			y = Analys->MapCamera->SensorSizeY * r;
			return sqrt(x*x+y*y);
		}
	}
	return 0.0;
}

#pragma end_region

#pragma region TSensor

// -----------------------------------------------------
// CLASS TSensor
// -----------------------------------------------------
TSensor::TSensor(TAnalys *analys) {
	Analys     = analys;
	Coc        = new TCoc(Analys);
	CropFactor = new TCropFactor(Analys);
	PixelSize  = new TPixelSize(Analys);
}

TSensor::~TSensor(void) {
	delete Coc;
	delete CropFactor;
	delete PixelSize;
}

UnicodeString __fastcall TSensor::GetCaption(void) {
	return Analys->MapCamera->SensorCaption;
}

double __fastcall TSensor::GetDiagonal(void) {
	return sqrt(Analys->MapCamera->SensorSizeX * Analys->MapCamera->SensorSizeX + Analys->MapCamera->SensorSizeY * Analys->MapCamera->SensorSizeY);
}

double __fastcall TSensor::GetHeight(void) {
	return Analys->MapCamera->SensorSizeY;
}

double __fastcall TSensor::GetWidth(void) {
	return Analys->MapCamera->SensorSizeX;
}

bool __fastcall TSensor::GetIsFullFrame(void) {
	double ff;

	ff = 1.0 - CropFactor->Value;
	if (ff < 0.0)
		ff = (-ff);
	if (ff < 0.05)
		return true;
	return false;

}

#pragma end_region

#pragma region TRotate

// -----------------------------------------------------
// CLASS TRotate
// -----------------------------------------------------
TRotate::TRotate(void) {
	Value = ERotate::flNone;
}

void __fastcall TRotate::SetValue(double v) {
	switch ( (int) v ) {
		case 1  : Value = ERotate::flLandscape; // Horizontal
		case 2  : Value = ERotate::flLandscape;	// Flip horizontal
		case 3  : Value = ERotate::flLandscape;	// Rotate 180
		case 4  : Value = ERotate::flLandscape; // Flip vertical
		case 5  : Value = ERotate::flLandscape; // Transpose
		case 6  : Value = ERotate::flPortrait; 	// Rotate 90
		case 7  : Value = ERotate::flLandscape;	// Transverse
		case 8  : Value = ERotate::flPortrait; 	// Rotate 270
		default : Value = ERotate::flNone; 		// Not definied
    }
}

#pragma end_region

#pragma region TLens

// -----------------------------------------------------
// CLASS TLens
// -----------------------------------------------------
TLens::TLens(TAnalys *analys) {
	Analys = analys;
	PCaption = L"Default";
	LensData = NULL;
	PIsData = false;
}

void __fastcall TLens::SetCaption(UnicodeString caption) {
	if (Analys->MapCamera->LensBuiltIn)
		PCaption = Analys->MapCamera->Caption;
	else
		PCaption = caption;
}

TLensData* __fastcall TLens::GetLensData(void) {
	if ((Analys->MapCamera->LensDatas != NULL) && (PLensData == NULL))
		PLensData = Analys->MapCamera->LensDatas->QueryLensData(PCaption);
	return PLensData;
}

bool __fastcall TLens::GetIsData(void) {
	if (LensData != NULL)
		return LensData->IsData;
	else
		return false;
}

double __fastcall TLens::QueryIndiceForXY(double x, double y) {
	unsigned c, r, g;
	TBitmapData bd;

	if (LensData != NULL) {
		if (LensData->IsData) {
			x = ((x > 1.0) ? x : 1.0);
			x = ((x < (double) LensData->BitmapData->Width) ? x : (double) LensData->BitmapData->Width);
			y = ((y > 1.0) ? y : 1.0);
			y = ((y < (double) LensData->BitmapData->Height) ? y : (double) LensData->BitmapData->Height);
			LensData->BitmapData->Map(TMapAccess::ReadWrite,bd);
			c = bd.GetPixel((int)x,(int)y) & 0xffffff;
			LensData->BitmapData->Unmap(bd);
			if (c != 0.0) {
				r = (c & 0xff0000) >> 16;
				g = (c & 0x00ff00) >> 8;
				return ((double) g + (255 - (double) r)) / 512.0;
			}
		}
	}
	return 0.0;
}

double __fastcall TLens::QueryIndiceForFocaleAperture(double focale, double aperture) {
	unsigned c, r, g;
	double x, y;
	TBitmapData bd;

	if (LensData != NULL) {
		if (LensData->IsData) {
			x = Focale2x(focale);
			if (x == -1.0)
				return -1.0;
			y = Aperture2y(aperture);
			if (y == -1.0)
				return -1.0;

			c = 0;
			LensData->BitmapData->Map(TMapAccess::ReadWrite,bd);
			while (c == 0) {
				c = bd.GetPixel((int)x,(int)y) & 0xffffff;
				if (y > LensData->BitmapData->Height / 2)
					y--;
				else
					y++;
			}
			LensData->BitmapData->Unmap(bd);
			r = (c & 0xff0000) >> 16;
			g = (c & 0x00ff00) >> 8;
			return (g + (255 - r)) / 512.0;
		}
	}
	return 0.0;
}

double __fastcall TLens::Focale2x(double focale) {
	double x;

	if (LensData != NULL) {
		if (LensData->IsData) {
			if (LensData->FocaleMax == LensData->FocaleMin)
				return 1.0;
			else {
				x = LensData->BitmapData->Width * (focale - LensData->FocaleMin) / (LensData->FocaleMax - LensData->FocaleMin);
				if (x < 1.0)
					return -1.0;
				if (x > LensData->BitmapData->Width - 1)
					return -1.0;
				return x;
			}
		}
	}
	return -1.0;
}

double __fastcall TLens::x2Focale(double x) {
	double focale;

	if (LensData != NULL) {
		if (LensData->IsData) {
			focale = x * (LensData->FocaleMax - LensData->FocaleMin) / LensData->BitmapData->Width + LensData->FocaleMin;
			if (focale > LensData->FocaleMax)
				return -1.0;
			if (focale < LensData->FocaleMin)
				return -1.0;
			return focale;
		}
	}
	return -1.0;
}

double __fastcall TLens::Aperture2y(double aperture) {
	double y;
	double aapex, aminapex, amaxapex, h;

	if (LensData != NULL) {
		if (LensData->IsData) {
			aapex = Analys->Apex->Aperture2Apex(aperture);
			aminapex = Analys->Apex->Aperture2Apex(LensData->ApertureMin);
			amaxapex = Analys->Apex->Aperture2Apex(LensData->ApertureMax);
			h = LensData->BitmapData->Height;

			y = h - ((aapex - aminapex) * h) / (amaxapex - aminapex);
			if (y < 0.0)
				return -1.0;
			if (y > LensData->BitmapData->Height)
				return -1.0;
			return ((y > 1.0) ? y : 1.0);
		}
	}
	return -1.0;
}

double __fastcall TLens::y2Aperture(double y) {
	double aperture;
	double aminapex, amaxapex, h;

	if (LensData != NULL) {
		if (LensData->IsData) {
			aminapex = Analys->Apex->Aperture2Apex(LensData->ApertureMin);
			amaxapex = Analys->Apex->Aperture2Apex(LensData->ApertureMax);
			h = LensData->BitmapData->Height;

			aperture = Analys->Apex->Apex2Aperture(((h - y) * (amaxapex - aminapex) + (aminapex * h)) / h);
			if (aperture < LensData->ApertureMin)
				return -1.0;
			if (aperture > LensData->ApertureMax)
				return -1.0;
			return aperture;
		}
	}
	return -1.0;
}

double __fastcall TLens::QueryIndice(double focale, double aperture) {
	if (LensData != NULL)
		return QueryIndiceForFocaleAperture(focale, aperture);
	return -1.0;
}

double __fastcall TLens::QueryApertureMax(double focale) { // f1.8  y = LensData->BitmapData->Height
	double x, v;
	unsigned y;

	if (LensData != NULL) {
		if (LensData->IsData) {
			x = Focale2x(focale);
			for (y = 0; y < (unsigned) LensData->BitmapData->Height; y++) {
				v = QueryIndiceForXY(x, (double) y);
				if (v > 0.0)
					return y2Aperture((double) y);
			}
			return y2Aperture(LensData->BitmapData->Height);
		}
	}
	return -1.0;
}

double __fastcall TLens::QueryApertureMin(double focale) { // f32   y = 0
	double x, v;
	unsigned y;

	if (LensData != NULL) {
		if (LensData->IsData) {
			x = Focale2x(focale);
			for (y = (unsigned) LensData->BitmapData->Height; y > 0; y--) {
				v = QueryIndiceForXY(x, (double) y);
				if (v > 0.0)
					return ((double) y);
			}
			return y2Aperture(LensData->BitmapData->Height);
		}
	}
	return -1.0;
}

double __fastcall TLens::QueryIndiceMax(double focale, double aperture) {
	double x, imax, v;
	unsigned y;

	if (LensData != NULL) {
		if (LensData->IsData) {
			x = Focale2x(focale);
			imax = 0.0;
			for (y = 0; y < (unsigned) LensData->BitmapData->Height; y++) {
				v = QueryIndiceForXY(x, (double) y);
				imax = ((v > imax) ? v : imax);
			}
			return imax;
		}
	}
	return -1.0;
}

double __fastcall TLens::QueryIndiceMin(double focale, double aperture) {
	double x, imin, v;
	unsigned y;

	if (LensData != NULL) {
		if (LensData->IsData) {
			x = Focale2x(focale);
			imin = 1.0;
			for (y = 0; y < (unsigned) LensData->BitmapData->Height; y++) {
				v = QueryIndiceForXY(x, (double) y);
				if (v > 0.0)
					imin = ((v < imin) ? v : imin);
			}
			return imin;
		}
	}
	return -1.0;
}

double __fastcall TLens::QueryBestAperture(double focale) {
	double x, imax, v, a;
	unsigned y;

	if (LensData != NULL) {
		if (LensData->IsData) {
			x = Focale2x(focale);
			imax = v = a = 0.0;
			for (y = 0; y < (unsigned) LensData->BitmapData->Height; y++) {
				v = QueryIndiceForXY(x, (double) y);
				if (v > imax) {
					imax = v;
					a = (double) y;
				}
			}
			return y2Aperture(a);
		}
	}
	return 0.0;
}

unsigned __fastcall TLens::QueryIndiceBestLens(double focale) {
	return 0;
}

#pragma end_region

#pragma region TExposureTime

// -----------------------------------------------------
// CLASS ETBest
// -----------------------------------------------------
ETBest::ETBest(TAnalys *analys) {
	Analys = analys;
}

double __fastcall ETBest::GetValue(void) {
	if (Analys->Exposure->Relative != NULL)
		return Analys->Apex->Apex2ExposureTime(Analys->Apex->ExposureTime2Apex(Analys->ExposureTime->Value) + Analys->Exposure->Relative->Value);
	else
		return 0.0;
}

UnicodeString __fastcall ETBest::GetCaption(void) {
	return ExposureTimeFormat(Value);
}

// -----------------------------------------------------
// CLASS ETLimit
// -----------------------------------------------------
ETLimit::ETLimit(TAnalys *analys) {
	Analys = analys;
}

double __fastcall ETLimit::GetValue(void) {
	double limit;

	if (Analys->Exposure->Relative != NULL) {
		limit = Analys->Apex->Apex2ExposureTime(Analys->Apex->ExposureTime2Apex(Analys->ExposureTime->Value) + Analys->Exposure->Relative->Value);
		limit = ((Analys->MapCamera->ExposureTimeMin > limit) ? Analys->MapCamera->ExposureTimeMin : limit);
		limit = ((Analys->MapCamera->ExposureTimeMax < limit) ? Analys->MapCamera->ExposureTimeMax : limit);
		return limit;
	}
	else
		return 0.0;
}

UnicodeString __fastcall ETLimit::GetCaption(void) {
	return ExposureTimeFormat(Value);
}

bool __fastcall ETLimit::GetIsInRange(void) {
	double v;

	v = Analys->Apex->Apex2ExposureTime(Analys->Apex->ExposureTime2Apex(Analys->ExposureTime->Value) + Analys->Exposure->Relative->Value);
	if (v < Analys->MapCamera->ExposureTimeMin)
		return false;
	if (v > Analys->MapCamera->ExposureTimeMax)
		return false;
	return true;
}

// -----------------------------------------------------
// CLASS ETExposureCompens
// -----------------------------------------------------
ETExposureCompens::ETExposureCompens(TAnalys *analys) {
	Analys = analys;
	Best = new ETEXBest(analys);
	Limit = new ETEXLimit(analys);
}

ETExposureCompens::~ETExposureCompens(void) {
	delete Best;
	delete Limit;
}

double __fastcall ETExposureCompens::GetValue(void) {
	return Analys->Apex->ExposureTimeApexRef - Analys->Apex->ExposureTime2Apex(Analys->ExposureTime->Value);
}

UnicodeString __fastcall ETExposureCompens::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}



// -----------------------------------------------------
// CLASS ETEXBest
// -----------------------------------------------------
ETEXBest::ETEXBest(TAnalys *analys) {
	Analys = analys;
}

double __fastcall ETEXBest::GetValue(void) {
	return Analys->Apex->ExposureTimeApexRef - Analys->Apex->ExposureTime2Apex(Analys->ExposureTime->Best->Value);
}

UnicodeString __fastcall ETEXBest::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}



// -----------------------------------------------------
// CLASS ETEXLimitRelative
// -----------------------------------------------------
ETEXLimitRelative::ETEXLimitRelative(TAnalys *analys) {
	Analys = analys;
}

double __fastcall ETEXLimitRelative::GetValue(void) {
	return Analys->Exposure->Relative->Value + Analys->Apex->ExposureTime2Apex(Analys->ExposureTime->Value) - Analys->Apex->ExposureTime2Apex(Analys->ExposureTime->Limit->Value);
}

UnicodeString __fastcall ETEXLimitRelative::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

// -----------------------------------------------------
// CLASS ETEXLimit
// -----------------------------------------------------
ETEXLimit::ETEXLimit(TAnalys *analys) {
	Analys = analys;
	Relative = new ETEXLimitRelative(analys);
}

ETEXLimit::~ETEXLimit(void) {
	delete Relative;
}

double __fastcall ETEXLimit::GetValue(void) {
	return Analys->Apex->ExposureTimeApexRef - Analys->Apex->ExposureTime2Apex(Analys->ExposureTime->Limit->Value);
}

UnicodeString __fastcall ETEXLimit::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

// -----------------------------------------------------
// CLASS TExposureTime
// -----------------------------------------------------
TExposureTime::TExposureTime(TAnalys *analys) {
	Best = new ETBest(analys);
	Limit = new ETLimit(analys);
	ExposureCompens = new ETExposureCompens(analys);
	PValue = 0;
}

TExposureTime::~TExposureTime(void) {
	delete ExposureCompens;
	delete Best;
	delete Limit;
}

void __fastcall TExposureTime::SetValue(double exposuretime) {
	PValue = ((0.0 > exposuretime) ? 0.0 : exposuretime);
}

UnicodeString __fastcall TExposureTime::GetCaption(void) {
	return ExposureTimeFormat(PValue);
}


#pragma end_region

#pragma region TAperture

// -----------------------------------------------------
// CLASS ABest
// -----------------------------------------------------
ABest::ABest(TAnalys *analys) {
	Analys = analys;
}

ABest::~ABest(void) {
}

double __fastcall ABest::GetValue(void) {
	if (Analys->Exposure->Relative != NULL)
		return Analys->Apex->Apex2Aperture(Analys->Apex->Aperture2Apex(Analys->Aperture->Value) + Analys->Exposure->Relative->Value);
	else
		return 0.0;
}

UnicodeString __fastcall ABest::GetCaption(void) {
	return ApertureFormat(Value);
}

// -----------------------------------------------------
// CLASS ALimit
// -----------------------------------------------------
ALimit::ALimit(TAnalys *analys) {
	Analys = analys;
}

ALimit::~ALimit(void) {
}

double __fastcall ALimit::GetValue(void) {
	double limit;

	if (Analys->Exposure->Relative != NULL) {
		if (Analys->Lens->LensData != NULL) {
			if (Analys->Lens->LensData->IsData) {
				limit = Analys->Apex->Apex2Aperture(Analys->Apex->Aperture2Apex(Analys->Aperture->Value) + Analys->Exposure->Relative->Value);
				limit = ((Analys->Lens->LensData->ApertureMin > limit) ? Analys->Lens->LensData->ApertureMin : limit);
				limit = ((Analys->Lens->LensData->ApertureMax < limit) ? Analys->Lens->LensData->ApertureMax : limit);
				return limit;
			}
		}
	}
	return 0.0;
}

UnicodeString __fastcall ALimit::GetCaption(void) {
	return ApertureFormat(Value);
}

bool __fastcall ALimit::GetIsInRange(void) {
	double v;

	if (Analys->Lens->LensData != NULL) {
		if (Analys->Lens->LensData->IsData) {
			v = Analys->Apex->Apex2Aperture(Analys->Apex->Aperture2Apex(Analys->Aperture->Value) + Analys->Exposure->Relative->Value);
			if (v < Analys->Lens->LensData->ApertureMin + 0.01)
				return false;
			if (v > Analys->Lens->LensData->ApertureMax + 0.01)
				return false;
		}
	}
	return true;
}

// -----------------------------------------------------
// CLASS AExposureCompens
// -----------------------------------------------------
AExposureCompens::AExposureCompens(TAnalys *analys) {
	Analys = analys;
	Best = new AEXBest(analys);
	Limit = new AEXLimit(analys);
}

AExposureCompens::~AExposureCompens(void) {
	delete Best;
	delete Limit;
}

double __fastcall AExposureCompens::GetValue(void) {
	return Analys->Apex->ApertureApexRef - Analys->Apex->Aperture2Apex(Analys->Aperture->Value);
}

UnicodeString __fastcall AExposureCompens::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

// -----------------------------------------------------
// CLASS AEXBest
// -----------------------------------------------------
AEXBest::AEXBest(TAnalys *analys) {
	Analys = analys;
}

AEXBest::~AEXBest(void) {
}

double __fastcall AEXBest::GetValue(void) {
	return Analys->Apex->ApertureApexRef - Analys->Apex->Aperture2Apex(Analys->Aperture->Best->Value);
}

UnicodeString __fastcall AEXBest::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}



// -----------------------------------------------------
// CLASS AEXLimitRelative
// -----------------------------------------------------
AEXLimitRelative::AEXLimitRelative(TAnalys *analys) {
	Analys = analys;
}

AEXLimitRelative::~AEXLimitRelative(void) {
}

double __fastcall AEXLimitRelative::GetValue(void) {
	return Analys->Exposure->Relative->Value + Analys->Apex->Aperture2Apex(Analys->Aperture->Value) - Analys->Apex->Aperture2Apex(Analys->Aperture->Limit->Value);
}

UnicodeString __fastcall AEXLimitRelative::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

// -----------------------------------------------------
// CLASS AEXLimit
// -----------------------------------------------------
AEXLimit::AEXLimit(TAnalys *analys) {
	Analys = analys;
	Relative = new AEXLimitRelative(analys);
}

AEXLimit::~AEXLimit(void) {
	delete Relative;
}

double __fastcall AEXLimit::GetValue(void) {
	return Analys->Apex->ApertureApexRef - Analys->Apex->Aperture2Apex(Analys->Aperture->Limit->Value);
}

UnicodeString __fastcall AEXLimit::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

// -----------------------------------------------------
// CLASS TAperture
// -----------------------------------------------------
TAperture::TAperture(TAnalys *analys) {
	Best = new ABest(analys);
	Limit = new ALimit(analys);
	ExposureCompens = new AExposureCompens(analys);
	PValue = 0;
}

TAperture::~TAperture(void) {
	delete Best;
	delete Limit;
	delete ExposureCompens;
}

UnicodeString __fastcall TAperture::GetCaption(void) {
	return ApertureFormat(PValue);
}

void __fastcall TAperture::SetValue(double aperture) {
	PValue = ((0.0 > aperture) ? 0.0 : aperture);
}

#pragma end_region

#pragma region TIso

// -----------------------------------------------------
// CLASS IBest
// -----------------------------------------------------
IBest::IBest(TAnalys *analys) {
	Analys = analys;
}

IBest::~IBest(void) {
}


double __fastcall IBest::GetValue(void) {
	if (Analys->Exposure->Relative != NULL)
		return Analys->Apex->Apex2Iso(Analys->Apex->Iso2Apex(Analys->Iso->Value) - Analys->Exposure->Relative->Value);
	else
		return 0.0;
}

UnicodeString __fastcall IBest::GetCaption(void) {
	return IsoFormat(Value);
}

// -----------------------------------------------------
// CLASS ILimit
// -----------------------------------------------------
ILimit::ILimit(TAnalys *analys) {
	Analys = analys;
}

ILimit::~ILimit(void) {
}

double __fastcall ILimit::GetValue(void) {
	double limit;

	if (Analys->Exposure->Relative != NULL) {
		limit = Analys->Apex->Apex2Iso(Analys->Apex->Iso2Apex(Analys->Iso->Value) - Analys->Exposure->Relative->Value); // ok
		limit = ((Analys->MapCamera->IsoMin > limit) ? Analys->MapCamera->IsoMin : limit);
		limit = ((Analys->MapCamera->IsoMax < limit) ? Analys->MapCamera->IsoMax : limit);
		return limit;
	}
	else
		return 0.0;
}

UnicodeString __fastcall ILimit::GetCaption(void) {
	return IsoFormat(Value);
}

bool __fastcall ILimit::GetIsInRange(void) {
	double v;

	v = Analys->Apex->Apex2Iso(Analys->Apex->Iso2Apex(Analys->Iso->Value) - Analys->Exposure->Relative->Value);
	if (v < Analys->MapCamera->IsoMin)
		return false;
	if (v > Analys->MapCamera->IsoMax)
		return false;
	return true;
}


// -----------------------------------------------------
// CLASS IExposureCompens
// -----------------------------------------------------
IExposureCompens::IExposureCompens(TAnalys *analys) {
	Analys = analys;
	DeltaLimitBest = new IEXDeltaLimitBest(analys);
	Limit = new IEXLimit(analys);
	Best = new IEXBest(analys);
}

IExposureCompens::~IExposureCompens(void) {
	delete Best;
	delete Limit;
	delete DeltaLimitBest;
}

double __fastcall IExposureCompens::GetValue(void) {
	return Analys->Apex->Iso2Apex(Analys->Iso->Value) - Analys->Apex->IsoApexRef;
}

UnicodeString __fastcall IExposureCompens::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

// -----------------------------------------------------
// CLASS IEXBest
// -----------------------------------------------------
IEXBest::IEXBest(TAnalys *analys) {
	Analys = analys;
}

IEXBest::~IEXBest(void) {
}

double __fastcall IEXBest::GetValue(void) {
	return Analys->Apex->Iso2Apex(Analys->Iso->Best->Value) - Analys->Apex->IsoApexRef;
}

UnicodeString __fastcall IEXBest::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

// -----------------------------------------------------
// CLASS IEXDeltaLimitBest
// -----------------------------------------------------
IEXDeltaLimitBest::IEXDeltaLimitBest(TAnalys *analys) {
	Analys = analys;
}

IEXDeltaLimitBest::~IEXDeltaLimitBest(void) {
}

double __fastcall IEXDeltaLimitBest::GetValue(void) {
	return Analys->Apex->Iso2Apex(Analys->Iso->Best->Value) - Analys->Apex->Iso2Apex(Analys->Iso->Limit->Value);
}

UnicodeString __fastcall IEXDeltaLimitBest::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}


// -----------------------------------------------------
// CLASS IEXLimitRelative
// -----------------------------------------------------
IEXLimitRelative::IEXLimitRelative(TAnalys *analys) {
	Analys = analys;
}

IEXLimitRelative::~IEXLimitRelative(void) {
}

double __fastcall IEXLimitRelative::GetValue(void) {
	return Analys->Exposure->Relative->Value - Analys->Apex->Iso2Apex(Analys->Iso->Value) + Analys->Apex->Iso2Apex(Analys->Iso->Limit->Value);
}

UnicodeString __fastcall IEXLimitRelative::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

// -----------------------------------------------------
// CLASS IEXLimit
// -----------------------------------------------------
IEXLimit::IEXLimit(TAnalys *analys) {
	Analys = analys;
	Relative = new IEXLimitRelative(analys);
}

IEXLimit::~IEXLimit(void) {
	delete Relative;
}

double __fastcall IEXLimit::GetValue(void) {
	return Analys->Apex->Iso2Apex(Analys->Iso->Limit->Value) - Analys->Apex->IsoApexRef;
}

UnicodeString __fastcall IEXLimit::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

// -----------------------------------------------------
// CLASS TIso
// -----------------------------------------------------
TIso::TIso(TAnalys *analys) {
	Best = new IBest(analys);
	Limit = new ILimit(analys);
	ExposureCompens = new IExposureCompens(analys);
	PValue = 0.0;
}

TIso::~TIso(void) {
	delete Best;
	delete Limit;
	delete ExposureCompens;
}

UnicodeString __fastcall TIso::GetCaption(void) {
	return IsoFormat(PValue);
}

void __fastcall TIso::SetValue(double iso) {
	PValue = ((0.0 > iso) ? 0.0 : iso);
}

#pragma end_region

#pragma region TIn24x36

// -----------------------------------------------------
// CLASS TIn24x36
// -----------------------------------------------------
TIn24x36::TIn24x36(TAnalys *analys) {
	Analys = analys;
}

TIn24x36::~TIn24x36(void) {
}

UnicodeString __fastcall TIn24x36::GetCaption(void) {
	return FocaleFormat(Value);
}

double __fastcall TIn24x36::GetValue(void) {
	return ((1.0 > Analys->Focale->Value * Analys->Sensor->CropFactor->Value) ? 1.0 : Analys->Focale->Value * Analys->Sensor->CropFactor->Value);
}


#pragma end_region

#pragma region TAngle

// -----------------------------------------------------
// CLASS TAngle en degrès (sur diagonale)
// -----------------------------------------------------
TAngle::TAngle(TAnalys *analys) {
	Analys = analys;
}

TAngle::~TAngle(void) {
}

UnicodeString __fastcall TAngle::GetCaption(void) {
	return Uprintf(L"%.2f°",Value);
}

double __fastcall TAngle::GetValue(void) {
	return 180.0 * sqrt(Analys->Sensor->Width*Analys->Sensor->Width+Analys->Sensor->Height*Analys->Sensor->Height) / M_PI / Analys->Focale->Value;
}


#pragma end_region

#pragma region TBorder

// -----------------------------------------------------
// CLASS TBorder (sur diagonale)
// -----------------------------------------------------
TBorder::TBorder(TAnalys *analys) {
	Analys = analys;
}

TBorder::~TBorder(void) {
}

UnicodeString __fastcall TBorder::GetCaption(void) {
	return Uprintf(L"%.2f",Value);
}

double __fastcall TBorder::GetValue(void) {
	if (Analys->Focale->Angle->Value != 0.0) {
		return tan( (Analys->Focale->Angle->Value / 2.0) / 180.0 * M_PI ) * Analys->FocusDistance->SubjectDistance->Value * 2.0;
	}
	return 0.0;
}

#pragma end_region

#pragma region TFocale

// -----------------------------------------------------
// CLASS TFocale
// -----------------------------------------------------
TFocale::TFocale(TAnalys *analys) {
	PValue = 0.0;
	In24x36 = new TIn24x36(analys);
	Angle = new TAngle(analys);
	Border = new TBorder(analys);
}

TFocale::~TFocale(void) {
	delete In24x36;
	delete Angle;
	delete Border;
}

UnicodeString __fastcall TFocale::GetCaption(void) {
	return FocaleFormat(PValue);
}

void __fastcall TFocale::SetValue(double focale) {
	PValue = ((focale > 1.0) ? focale : 1.0);
}

#pragma end_region

#pragma region TDepthOfField

// -----------------------------------------------------
// CLASS TDepthOfField
// -----------------------------------------------------
TDepthOfField::TDepthOfField(TSubjectDistance *subjectdistance, TUpper *upper, TLower *lower) {
	SubjectDistance = subjectdistance;
	Upper = upper;
	Lower = lower;
}

TDepthOfField::~TDepthOfField(void) {
}

UnicodeString __fastcall TDepthOfField::GetCaption(void) {
	return FocusDistanceFormat(Value, false);
}

double __fastcall TDepthOfField::GetValue(void) {
	if (Upper->Value == INFINI)
		return INFINI;
	else if (SubjectDistance->Value > MACROLIMIT)
		return Upper->Value - Lower->Value;
	else
		return 0.0;
}

#pragma end_region

#pragma region TSubjectDistance

// -----------------------------------------------------
// CLASS TSubjectDistance
// -----------------------------------------------------
TSubjectDistance::TSubjectDistance(TAnalys *analys) {
	Analys = analys;
	PIsValid = false;
	PValue = 0;
}

 TSubjectDistance::~TSubjectDistance(void) {
}

UnicodeString __fastcall TSubjectDistance::GetCaption(void) {
	return FocusDistanceFormat(PValue, !PIsValid);
}

UnicodeString __fastcall TSubjectDistance::GetVerbose(void) {
	return Analys->Lgs->QueryKey(L"SubjectDist.SubjectDist") + L":  " + FocusDistanceFormat(PValue, !PIsValid);
}

void __fastcall TSubjectDistance::SetValue(double value) {
	PValue = ((0.0 > value) ? 0.0 : value);
}

void __fastcall TSubjectDistance::Compute(double focale, double hyperfocale, double focusdistancelower, double upperdcraw) {
	if (upperdcraw == INFINI || focusdistancelower == 0) {
		PIsValid = false;
		SetValue(hyperfocale);
	}
	else {
		PIsValid = true;
		if (focusdistancelower > MACROLIMIT && focusdistancelower < hyperfocale) {
			SetValue((hyperfocale * focusdistancelower) / (hyperfocale - focusdistancelower));
		}
		else {
			if (focusdistancelower > 0) {
				SetValue(focale / focusdistancelower);
			}
		}
	}
}

#pragma end_region

#pragma region TUpper

// -----------------------------------------------------
// CLASS TUpper
// -----------------------------------------------------
TUpper::TUpper(void) {
	PValue = 0;
}

TUpper::~TUpper(void) {
}

UnicodeString __fastcall TUpper::GetCaption(void) {
	return FocusDistanceFormat(PValue, false);
}

void __fastcall TUpper::SetValue(double value) {
	PValue = ((0.0 > value) ? 0.0 : value);
}

void __fastcall TUpper::SetOriginalValue(double dfc) {
	/* TODO : Attention   Valeur 655.35 lié a canon eos 7d */
	if (dfc == 655.35)
		POriginalValue = INFINI;
	else
		POriginalValue = dfc;
}

void __fastcall TUpper::Compute(double SujectDistance, double Hyperfocale, double Focale) {
	if (Hyperfocale != 0) {
		if (SujectDistance > MACROLIMIT) {
			if (SujectDistance >= Hyperfocale) {
				SetValue(INFINI);
			}
			else {
				SetValue(Hyperfocale * SujectDistance / (Hyperfocale - SujectDistance));
			}
		}
		else {
			SetValue(Hyperfocale * SujectDistance / Hyperfocale - (SujectDistance - Focale));
		}
	}
	else {
		SetValue(0.0);
	}
}

#pragma end_region

#pragma region TLower

// -----------------------------------------------------
// CLASS TLower
// -----------------------------------------------------
TLower::TLower(void) {
	PValue = 0.0;
	PBracket = false;
}

TLower::~TLower(void) {
}

UnicodeString __fastcall TLower::GetCaption(void) {
	return FocusDistanceFormat(PValue, PBracket);
}

void __fastcall TLower::SetValue(double value) {
	PValue = ((0.0 > value) ? 0.0 : value);
}

void __fastcall TLower::Compute(double sujectdist, double hyperfocale, double HyperfocaleLower, double Focale, double upperdcraw) {
	if (sujectdist == hyperfocale)
		PBracket = true;
	else
		PBracket = false;
	if (hyperfocale != 0.0) {
		if (sujectdist > MACROLIMIT) {
			SetValue(hyperfocale * sujectdist / (hyperfocale + sujectdist));
		}
		else {
			SetValue(hyperfocale * sujectdist / hyperfocale + (sujectdist - Focale));
		}
	}
	else {
		SetValue(0.0);
	}
}

#pragma end_region

#pragma region TFocusDistance

// -----------------------------------------------------
// CLASS TFocusDistance
// -----------------------------------------------------
TFocusDistance::TFocusDistance(TAnalys *analys) {
	Analys = analys;
	SubjectDistance = new TSubjectDistance(analys);
	Upper = new TUpper;
	Lower = new TLower;
	DepthOfField = new TDepthOfField(SubjectDistance, Upper, Lower);
}

TFocusDistance::~TFocusDistance(void) {
	delete DepthOfField;
	delete SubjectDistance;
	delete Upper;
	delete Lower;
}

UnicodeString __fastcall TFocusDistance::GetVerbose(void) {
	if (Upper->Value != INFINI)
		PVerbose = Uprintf(Analys->Lgs->QueryKey(L"FocusDist.FromTo").w_str(), Lower->Caption.w_str(), Upper->Caption.w_str(), FocusDistanceFormat(Upper->Value - Lower->Value, false).w_str());
	else
		PVerbose = PVerbose = Uprintf(Analys->Lgs->QueryKey(L"FocusDist.FromToInf").w_str(), Lower->Caption.w_str());
	return PVerbose;
}

void __fastcall TFocusDistance::Compute(double focusdistancelower, double hyperfocale, double hyperfocalelower, double focale) {
	if (focusdistancelower != hyperfocale) {
		SubjectDistance->Compute(focale, hyperfocale, focusdistancelower, Upper->OriginalValue);
		Upper->Compute(SubjectDistance->Value, hyperfocale, focale);
		Lower->Compute(SubjectDistance->Value, hyperfocale, hyperfocalelower, focale, Upper->OriginalValue);
	}
	else {
		Upper->Value = INFINI;
		Lower->Value = hyperfocale / 2.0;
		SubjectDistance->Value = hyperfocale;
	}
}

#pragma end_region

#pragma region TSubjectSpeedLimit

// -----------------------------------------------------
// CLASS TSubjectSpeedLimit
// -----------------------------------------------------
TSubjectSpeedLimit::TSubjectSpeedLimit(TAnalys *analys) {
	Analys = analys;
}

TSubjectSpeedLimit::~TSubjectSpeedLimit(void) {
}

double __fastcall TSubjectSpeedLimit::GetValue(void) {
	double size;

	size = Analys->Sensor->PixelSize->Value / 10.0;
	if ( (Analys->ExposureTime->Value > 0.0) && (size > 0.0) && (Analys->Focale->In24x36->Value > 0.0) && (Analys->ExposureTime->Value > 0.0) ) {
		return (3600.0 * (Analys->FocusDistance->SubjectDistance->Value * (35.0 * 35.0 / Analys->Focale->In24x36->Value) * size) / Analys->ExposureTime->Value) / 1000.0;
	}
	return 0.0;
}

UnicodeString __fastcall TSubjectSpeedLimit::GetCaption(void) {
	return Uprintf(L"%.2f",Value);
}


#pragma end_region

#pragma region THyperfocale

// -----------------------------------------------------
// CLASS THyperfocale
// -----------------------------------------------------
THyperfocale::THyperfocale(TAnalys *analys) {
	Analys = analys;
	FocusDistance = new TFocusDistance(analys);
}

THyperfocale::~THyperfocale(void) {
	delete FocusDistance;
}

UnicodeString __fastcall THyperfocale::GetCaption(void) {
	return FocusDistanceFormat(Value, false) + L"m";
}

UnicodeString __fastcall THyperfocale::GetVerbose(void) {
	return Analys->Lgs->QueryKey(L"Hyper.HyperDistance") + L":  " + FocusDistanceFormat(Value, false);
}

double __fastcall THyperfocale::GetValue(void) {
	if ((Analys->Sensor->Coc->Value * Analys->Aperture->Value) != 0.0)
		return ((Analys->Focale->Value * Analys->Focale->Value) / (Analys->Sensor->Coc->Value * Analys->Aperture->Value)) / 1000.0;
	else
		return 0.0;
}

void __fastcall THyperfocale::Compute(void) {
	if ((Analys->Sensor->Coc->Value * Analys->Aperture->Value) != 0.0)
		FocusDistance->Compute(Value, Value, MACROLIMIT, Analys->Focale->Value);

}
#pragma end_region

#pragma region THistogram

// -----------------------------------------------------
// CLASS THistogram
// -----------------------------------------------------
THistogram::THistogram(void) {
	PBitmap = NULL;
}

THistogram::~THistogram(void) {
	if (PBitmap != NULL)
		delete PBitmap;
}

void __fastcall THistogram::Compute(TBitmap *bitmap, TImage *dest) {
	unsigned x, y, c, r, g, b, idx, *px, pmax;
	double pr, pg, pb, h, w, *pxr, *pxg, *pxb, prgbmax;
	TPoint p1, p2;
	TBitmapData bd;

	w = 765.0; // = 255 * 3
	h = dest->Height;

	if (PBitmap == NULL) {
		PBitmap = new TBitmap(int(w + 1), int(h));
		PBitmap->Clear(0);

		px = (unsigned*) malloc(sizeof(unsigned) * unsigned(w));
		pxr = (double*) malloc(sizeof(double) * unsigned(w));
		pxg = (double*) malloc(sizeof(double) * unsigned(w));
		pxb = (double*) malloc(sizeof(double) * unsigned(w));

		for (x = 0; x < w; x++) {
			px[x] = 0;
			pxr[x] = pxg[x] = pxb[x] = 0.0;
		}

		pmax = 0;

		bitmap->Map(TMapAccess::ReadWrite,bd);
		for (x = 0; x < (unsigned) bitmap->Width; x++) {
			for (y = 0; y < (unsigned) bitmap->Height; y++) {
				c = bd.GetPixel((int)x,(int)y) & 0xffffff;
				r = (c & 0xff0000) >> 16;
				g = (c & 0x00ff00) >> 8;
				b = (c & 0x0000ff);
				idx = r + g + b;
				idx = unsigned ((idx < w) ? idx : w - 1);
				idx = ((idx > 0) ? idx : 0);
				pxr[idx] += (double) r;
				pxg[idx] += (double) g;
				pxb[idx] += (double) b;
				px[idx]++;
				pmax = ((pmax > px[idx]) ? pmax : px[idx]);
			}
		}
		bitmap->Unmap(bd);

		// draw Histogram
		PBitmap->Canvas->BeginScene();
		PBitmap->Canvas->Stroke->Kind = TBrushKind::Solid;
		PBitmap->Canvas->Stroke->Thickness = 1;

		for (x = 0; x < w; x++) {
			p1.X = (long) x + 1;
			p2.X = (long) x + 1;
			p1.Y = (long) h;
			prgbmax = pxr[x] + pxg[x] + pxb[x];
			if (prgbmax > 0) {
				pr = pxr[x] / prgbmax;
				pg = (pxr[x] + pxg[x]) / prgbmax;
				pb = 1.0;
			}
			if (pr + pg + pb > 0.0) {
				p2.Y = (long)(h - ((double)px[x] * pr * h / (double) pmax));
				PBitmap->Canvas->Stroke->Color = claRed;
				PBitmap->Canvas->DrawLine(p1, p2, (float)1.0);
				PBitmap->Canvas->Stroke->Color = claLime;
				p1.Y = (long)(h - ((double)px[x] * pg * h / (double) pmax));
				PBitmap->Canvas->DrawLine(p2, p1, (float)1.0);
				PBitmap->Canvas->Stroke->Color = claBlue;
				p2.Y = (long)(h - ((double)px[x] * pb * h / (double) pmax));
				PBitmap->Canvas->DrawLine(p1, p2, (float)1.0);
			}
			else {
				p2.Y = (long) (h - ((double)px[x] * h / (double) pmax));
				PBitmap->Canvas->Stroke->Color = claWhite;
				PBitmap->Canvas->DrawLine(p1, p2, (float)1.0);
			}
		}
		PBitmap->Canvas->EndScene();

		free(px);
		free(pxr);
		free(pxg);
		free(pxb);
	}
	dest->Bitmap = PBitmap;
}

#pragma end_region

#pragma region TRelative

// -----------------------------------------------------
// CLASS TRelative
// -----------------------------------------------------
TRelative::TRelative(TAnalys *analys) {
	Analys = analys;
}

TRelative::~TRelative(void) {
}

double __fastcall TRelative::GetValue(void) {
	if (Analys->Exposure->Evaluate->Value > 0.0)
		return Analys->Exposure->Evaluate->Value - Analys->Apex->ApexRef;
	else
		return 0.0;
}

UnicodeString __fastcall TRelative::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

#pragma end_region

#pragma region TEvaluate

// -----------------------------------------------------
// CLASS TEvaluate
// -----------------------------------------------------
TEvaluate::TEvaluate(TAnalys *analys) {
	Analys = analys;
}

TEvaluate::~TEvaluate(void) {
}

UnicodeString __fastcall TEvaluate::GetCaption(void) {
	return ExposureFormat(Value, Analys->Lgs);
}

double __fastcall TEvaluate::GetValue(void) {
	return Analys->Exposure->Value + Analys->ExposureTime->ExposureCompens->Value + Analys->Aperture->ExposureCompens->Value + Analys->Iso->ExposureCompens->Value + Analys->Flash->ExposureCompens->Value;
}


#pragma end_region

#pragma region TNaturalLight

// -----------------------------------------------------
// CLASS TNaturalLight
// -----------------------------------------------------
TNaturalLight::TNaturalLight(TAnalys *analys) {
	Analys = analys;
}

TNaturalLight::~TNaturalLight(void) {
}

UnicodeString __fastcall TNaturalLight::GetCaption(void) {
	unsigned idx;
	double v;

	v = Analys->Exposure->Value;
	if (v != 0.0) {
		if (v < 3.0)
			idx = 0;
		else if (v < 4.5)
			idx = 1;
		else if (v < 5.5)
			idx = 2;
		else if (v < 6.5)
			idx = 3;
		else if (v < 8.5)
			idx = 4;
		else if (v < 9.5)
			idx = 5;
		else if (v < 11.5)
			idx = 6;
		else if (v < 12)
			idx = 7;
		else if (v < 13)
			idx = 8;
		else if (v < 14)
			idx = 9;
		else if (v < 15)
			idx = 10;
		else if (v < 16)
			idx = 11;
		else if (v >= 16)
			idx = 12;
	}
	else
		idx = 13;
	return Analys->Lgs->QueryKey(L"NaturalLight.Idx" + UnicodeString(idx));
}

#pragma end_region

#pragma region TExposure

// -----------------------------------------------------
// CLASS TExposure
// -----------------------------------------------------
TExposure::TExposure(TAnalys *analys) {
	Analys = analys;
	PValue = 0.0;
	PIsFromCamera = false;
	Evaluate = new TEvaluate(analys);
	Relative = new TRelative(analys);
	NaturalLight = new TNaturalLight(analys);
}

TExposure::~TExposure(void) {
	delete Evaluate;
	delete Relative;
	delete NaturalLight;
}

void __fastcall TExposure::SetValue(double Ev) {
	if (Ev > 0) {
		PValue = Ev;
		PIsFromCamera = true;
	}
	else {
		PValue = Analys->Apex->ApexRef - Analys->ExposureTime->ExposureCompens->Value - Analys->Aperture->ExposureCompens->Value - Analys->Iso->ExposureCompens->Value;
		PIsFromCamera = false;
	}
}

UnicodeString __fastcall TExposure::GetCaption(void) {
	return ExposureFormat(PValue, Analys->Lgs);
}

#pragma end_region

#pragma region TFlash

// -----------------------------------------------------
// CLASS FDuration
// -----------------------------------------------------
FDuration::FDuration(TAnalys *analys) {
	Analys = analys;
}

FDuration::~FDuration(void) {
}

double __fastcall FDuration::GetValue(void) {
	double p;
	unsigned i;

	p = Analys->Flash->Power->Value;
	if (Analys->Flash->FlashData != NULL) {
		if (Analys->ExposureTime->Value >= Analys->Flash->FlashData->HSync) {
			if (Analys->Flash->Fired && (p > 0.0)) {
				for (i = 0; i < Analys->Flash->FlashData->FlashDurationCount; i++) {
					if (p >= Analys->Flash->FlashData->FlashDurationAtPower[i]) {
						i = (i - 1 > 0 ? i - 1 : 0);
						return Analys->Flash->FlashData->FlashDuration[i];
					}
				}
			}
		}
		else {
			return Analys->ExposureTime->Value;
		}
	}
	return 0.0;
}

// -----------------------------------------------------
// CLASS FPower
// -----------------------------------------------------
FPower::FPower(TAnalys *analys) {
	Analys = analys;
}

FPower::~FPower(void) {
}

double __fastcall FPower::GetValue(void) {
	if (Analys->Flash->Ng->Value > 0.0) {
		return Analys->Flash->Ng->Limit->Value / Analys->Flash->Ng->Value;
	}
	return 0.0;
}

// -----------------------------------------------------
// CLASS FBiasTag
// -----------------------------------------------------
FBiasTag::FBiasTag(void) {
	Value = 0.0;
}

FBiasTag::~FBiasTag(void) {
}

// -----------------------------------------------------
// CLASS FBias
// -----------------------------------------------------
FBias::FBias(TAnalys *analys) {
	Analys = analys;
	Tag = new FBiasTag;
}

FBias::~FBias(void) {
	delete Tag;
}

double __fastcall FBias::GetValue(void) {
	unsigned vb;
	double fb, fb1;

	fb = 0.0;
	if ((unsigned) Tag->Value > 0x8000) {
		vb = 0xFF - ((unsigned) Tag->Value & 0x00FF);
		fb = (double) vb * 2.0 / 64.0 * -1.0;
	}
	else if ((unsigned) Tag->Value != 0.0) {
		vb = (unsigned) Tag->Value;
		fb = (double) vb * 2.0 / 64.0;
	}

	// La puissance du flash est elle suffisante pour compenser un valeur positive?
	if (Analys->FocusDistance->SubjectDistance->Value * Analys->Aperture->Value > 0.0) {
		fb1 = Analys->Apex->Aperture2Apex(Analys->Flash->Ng->Value / (Analys->FocusDistance->SubjectDistance->Value * Analys->Aperture->Value));
		if ((fb1 > 0.0) && (fb1 < fb)) {
			fb = fb1;
		}
		else if (fb1 < 0.0) {
			fb = 0.0;
		}
	}
	return fb;
}

// -----------------------------------------------------
// CLASS FFiredTag
// -----------------------------------------------------
FFiredTag::FFiredTag(TAnalys *analys) {
	Analys = analys;
	PValue = 0.0;
}

FFiredTag::~FFiredTag(void) {
}

void __fastcall FFiredTag::SetValue(double v) {
	PValue = v;
	Analys->Flash->Fired->IsFired = Analys->MapCamera->EnumArrays->QueryEnumFlag(Analys->MapCamera->TagFlashFired, Analys->MapCamera->MakerCaption, Analys->MapCamera->Caption, Analys->MapCamera->IfdFlashFired, v, Analys->MapCamera->BitFlashFired);
}

// -----------------------------------------------------
// CLASS FFired
// -----------------------------------------------------
FFired::FFired(TAnalys *analys) {
	Tag = new FFiredTag(analys);
	IsFired = false;
}

FFired::~FFired(void) {
	delete Tag;
}

// -----------------------------------------------------
// CLASS FRequiredTag
// -----------------------------------------------------
FRequiredTag::FRequiredTag(TAnalys *analys) {
	Analys = analys;
	PValue = 0.0;
}

FRequiredTag::~FRequiredTag(void) {
}

void __fastcall FRequiredTag::SetValue(double v) {
	PValue = v;
	Analys->Flash->Required->Value = !Analys->MapCamera->EnumArrays->QueryEnumFlag(Analys->MapCamera->TagFlashOff, Analys->MapCamera->MakerCaption, Analys->MapCamera->Caption, Analys->MapCamera->IfdFlashOff, v, Analys->MapCamera->BitFlashOff);
}


// -----------------------------------------------------
// CLASS FRequired
// -----------------------------------------------------
FRequired::FRequired(TAnalys *analys) {
	Tag = new FRequiredTag(analys);
	Value = false;
}

FRequired::~FRequired(void) {
	delete Tag;
}

// -----------------------------------------------------
// CLASS FDidNotFire
// -----------------------------------------------------
FDidNotFire::FDidNotFire(TAnalys *analys) {
	Analys = analys;
}

FDidNotFire::~FDidNotFire(void) {
}

bool __fastcall FDidNotFire::GetIsNotFired(void) {
	if (!Analys->Flash->Fired->IsFired && Analys->Flash->Required->Value)
		return true;
	return false;
}

// -----------------------------------------------------
// CLASS FNgLimit
// -----------------------------------------------------
FNgLimit::FNgLimit(TAnalys *analys) {
	Analys = analys;
}

FNgLimit::~FNgLimit(void) {
}

double __fastcall FNgLimit::GetValue(void) {
	return Analys->FocusDistance->SubjectDistance->Value * Analys->Apex->Apex2Aperture(Analys->Apex->Aperture2Apex(Analys->Aperture->Value) + Analys->Flash->Bias->Value);
}


// -----------------------------------------------------
// CLASS FNg
// -----------------------------------------------------
FNg::FNg(TAnalys *analys) {
	Analys = analys;
	Limit = new FNgLimit(analys);
}

FNg::~FNg(void) {
	delete Limit;
}

double __fastcall FNg::GetValue(void) {
	double deltaapex;
	double coef;

	if (Analys->Flash->FlashData != NULL && (Analys->Iso->Value > 0.0) && (Analys->Focale->In24x36->Value > 0.0)) {
		if ((Analys->Flash->FlashData->BaseIso) > 0.0 && (Analys->Flash->FlashData->BaseFocale > 0.0)) {
			if (Analys->ExposureTime->Value >= Analys->Flash->FlashData->HSync) // Cas en dessous de HSync
					coef = 1.0;
			else {
				deltaapex = Analys->Apex->ExposureTime2Apex(Analys->ExposureTime->Value) - Analys->Apex->ExposureTime2Apex(Analys->Flash->FlashData->HSync);
				if (deltaapex > 0.0)
					coef = Analys->Flash->FlashData->HSyncCoef * pow(0.707107, deltaapex); // 0.5 pour 1/250   0.18 pour 1/2000
				else
					coef = Analys->Flash->FlashData->HSyncCoef;
			}
			return Analys->Flash->FlashData->BaseNg * sqrt(Analys->Iso->Value / Analys->Flash->FlashData->BaseIso) * sqrt(Analys->Focale->In24x36->Value / Analys->Flash->FlashData->BaseFocale) * coef;
		}
	}
	return 0.0;
}


// -----------------------------------------------------
// CLASS FExposureCompens
// -----------------------------------------------------
FExposureCompens::FExposureCompens(TAnalys *analys) {
	Analys = analys;
}

FExposureCompens::~FExposureCompens(void) {
}

double __fastcall FExposureCompens::GetValue(void) {
	if (Analys->Flash->Fired->IsFired)
		if ( (Analys->FocusDistance->SubjectDistance->IsValid) && (Analys->Flash->FlashData != NULL) )
			if (Analys->FocusDistance->SubjectDistance->Value <= Analys->Flash->Limit->Distance->Value - Analys->Flash->FlashData->Tolerance)
				return Analys->Apex->ApexRef - Analys->Exposure->Value - Analys->ExposureTime->ExposureCompens->Value - Analys->Aperture->ExposureCompens->Value - Analys->Iso->ExposureCompens->Value + Analys->Flash->Bias->Value;
	return 0.0;
}


// -----------------------------------------------------
// CLASS FAperture
// -----------------------------------------------------
FAperture::FAperture(TAnalys *analys) {
	Analys = analys;
}

FAperture::~FAperture(void) {
}

double __fastcall FAperture::GetValue(void) {
	if (Analys->FocusDistance->SubjectDistance->Value > 0.0)
		return Analys->Flash->Ng->Value / Analys->FocusDistance->SubjectDistance->Value;
	else
		return 0.0;
}

// -----------------------------------------------------
// CLASS FDistance
// -----------------------------------------------------
FDistance::FDistance(TAnalys *analys) {
	Analys = analys;
}

FDistance::~FDistance(void) {
}

double __fastcall FDistance::GetValue(void) {
	double a, b, c;
	if ((Analys->Flash->FlashData != NULL) && (Analys->Aperture->Value > 0.0)) {
		a = Analys->Flash->FlashData->DistanceMax;
		b = Analys->Flash->Ng->Value / Analys->Aperture->Value;
		c = (a < b ? a : b);
		a = Analys->Flash->FlashData->DistanceMin;
		return (a > c ? a : c);
	}
	else
		return 0.0;
}

// -----------------------------------------------------
// CLASS FLimit
// -----------------------------------------------------
FLimit::FLimit(TAnalys *analys) {
	Aperture = new FAperture(analys);
	Distance = new FDistance(analys);
}

FLimit::~FLimit(void) {
	delete Aperture;
	delete Distance;
}

// -----------------------------------------------------
// CLASS FRange
// -----------------------------------------------------
FRange::FRange(TAnalys *analys) {
	Analys = analys;
}

FRange::~FRange(void) {
}

bool __fastcall FRange::GetIsOkWithBias(void) {
	if (Analys->Flash->FlashData != NULL)
		if (Analys->FocusDistance->SubjectDistance->Value > Analys->Flash->Limit->Distance->Value + Analys->Flash->FlashData->Tolerance)
			return false;
	return true;
}

bool __fastcall FRange::GetIsOkWithoutBias(void) {
	double vb;

	vb = Analys->Flash->Bias->Tag->Value;
	Analys->Flash->Bias->Tag->Value = 0.0;
	if (Analys->Flash->FlashData != NULL) {
		if (Analys->FocusDistance->SubjectDistance->Value > Analys->Flash->Limit->Distance->Value + Analys->Flash->FlashData->Tolerance) {
			Analys->Flash->Bias->Tag->Value = vb;
			return false;
		}
	}
	Analys->Flash->Bias->Tag->Value = vb;
	return true;
}

// bool __fastcall FRange::GetIsLimitWithBias(void) {
// if (Analys->Flash->FlashData != NULL)
// if (Analys->FocusDistance->SubjectDistance->Value > Analys->Flash->Limit->Distance->Value - Analys->Flash->FlashData->Tolerance)
// return 2;
// return 0;
// }
//
// bool __fastcall FRange::GetIsLimitWithoutBias(void) {
// double vb;
// vb = Analys->Flash->Bias->Tag->Value;
//
// Analys->Flash->Bias->Tag->Value = 0.0;
// if (Analys->Flash->FlashData != NULL) {
// if (Analys->FocusDistance->SubjectDistance->Value > Analys->Flash->Limit->Distance->Value - Analys->Flash->FlashData->Tolerance) {
// Analys->Flash->Bias->Tag->Value = vb;
// return false;
// }
// }
// Analys->Flash->Bias->Tag->Value = vb;
// return true;
// }

// -----------------------------------------------------
// CLASS TFlash
// -----------------------------------------------------
TFlash::TFlash(TAnalys *analys) {
	FlashData = NULL;

	Fired           = new FFired(analys);
	Required        = new FRequired(analys);
	DidNotFire      = new FDidNotFire(analys);
	Bias            = new FBias(analys);
	Ng              = new FNg(analys);
	Power           = new FPower(analys);
	Duration        = new FDuration(analys);
	ExposureCompens = new FExposureCompens(analys);
	Limit           = new FLimit(analys);
	Range           = new FRange(analys);

	IsValid         = false;
	External        = false;
	BuiltIn         = true;
	ValueExternal   = 0.0;
	ValueBuiltIn    = 0.0;
}

TFlash::~TFlash(void) {
	delete Fired;
	delete Required;
	delete DidNotFire;
	delete Ng;
	delete Bias;
	delete Power;
	delete Duration;
	delete ExposureCompens;
	delete Limit;
	delete Range;
}

#pragma end_region

#pragma region TAnalys

// -----------------------------------------------------
// CLASS TAnalys
// -----------------------------------------------------

TAnalys::TAnalys(TLgs *lgs) {
	MapCamera         = NULL;
	PLgs              = lgs;
	Sensor            = new TSensor(this);
	Lens              = new TLens(this);
	ExposureTime      = new TExposureTime(this);
	Aperture          = new TAperture(this);
	Iso               = new TIso(this);
	Focale            = new TFocale(this);
	FocusDistance     = new TFocusDistance(this);
	Hyperfocale       = new THyperfocale(this);
	Exposure          = new TExposure(this);
	Flash             = new TFlash(this);
	SubjectSpeedLimit = new TSubjectSpeedLimit(this);
	Apex              = new TApex;
	Histogram         = new THistogram;
	Rotate            = new TRotate;
}

TAnalys::~TAnalys(void) {
	delete Rotate;
	delete Histogram;
	delete Apex;
	delete SubjectSpeedLimit;
	delete Flash;
	delete Exposure;
	delete Hyperfocale;
	delete FocusDistance;
	delete Focale;
	delete Iso;
	delete Aperture;
	delete ExposureTime;
	delete Lens;
	delete Sensor;
}

void __fastcall TAnalys::Compute(void) {
	if (MapCamera != NULL) {
		Flash->BuiltIn = MapCamera->EnumArrays->QueryEnumFlag(MapCamera->TagFlashBuiltIn, MapCamera->MakerCaption, MapCamera->Caption, MapCamera->IfdFlashBuiltIn, Flash->ValueBuiltIn, MapCamera->BitFlashBuiltIn);
		Flash->External = MapCamera->EnumArrays->QueryEnumFlag(MapCamera->TagFlashExternal, MapCamera->MakerCaption, MapCamera->Caption, MapCamera->IfdFlashExternal, Flash->ValueExternal, MapCamera->BitFlashExternal);
		if (Flash->BuiltIn)
			Flash->FlashData = MapCamera->FlashDatas->QueryFlashData(MapCamera->MakerCaption, MapCamera->Caption, L"BuiltIn");
		if (Flash->External)
			Flash->FlashData = MapCamera->FlashDatas->QueryFlashData(MapCamera->MakerCaption, MapCamera->Caption, L"External");
	}
	Hyperfocale->Compute();
	FocusDistance->Compute(FocusDistance->Lower->Value, Hyperfocale->Value, Hyperfocale->FocusDistance->Lower->Value, Focale->In24x36->Value);
}
#pragma end_region

#endif
