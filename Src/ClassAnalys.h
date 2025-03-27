#ifndef CLASSANALYSH
#define CLASSANALYSH

#include <math.h>

class FPower;
class FNg;
class FFired;
class FRequired;
class TFlash;
class TFocale;
class TSubjectDistance;
class TUpper;
class TLower;
class THyperfocale;
class TExposure;
class TExposureTime;
class TEvaluate;
class TRelative;
class TRotate;
class TAnalys;

#include "UtilCommon.h"
#include "ClassTagMap.h"
#include "ClassImageFilter.h"


#pragma region TApex

// -----------------------------------------------------
// CLASS TApex
// -----------------------------------------------------
class TApex {
	double PIsoRef;
	double PApertureRef;
	double PExposureTimeRef;

	double __fastcall GetExposureTimeApexRef(void);
	double __fastcall GetApertureApexRef(void);
	double __fastcall GetIsoApexRef(void);
	double __fastcall GetApexRef(void);

public:
		   TApex(void);
		   ~TApex(void);

	double __fastcall Iso2Apex(double s);
	double __fastcall Apex2Iso(double sv);
	double __fastcall Aperture2Apex(double a);
	double __fastcall Apex2Aperture(double av);
	double __fastcall ExposureTime2Apex(double t);
	double __fastcall Apex2ExposureTime(double tv);
	double __fastcall ApexOf(double t, double a, double s);
	double __fastcall ApexDelta(double t, double a, double s, double ev);
	double __fastcall PerfectExposureTime(double a, double s, double ev);
	double __fastcall PerfectAperture(double t, double s, double ev);
	double __fastcall PerfectIso(double t, double a, double ev);

	__property double ExposureTimeApexRef = {read = GetExposureTimeApexRef};
	__property double ApertureApexRef     = {read = GetApertureApexRef};
	__property double IsoApexRef          = {read = GetIsoApexRef};
	__property double ApexRef             = {read = GetApexRef};
};
#pragma end_region

#pragma region TCoc

// -----------------------------------------------------
// CLASS TCoc
// -----------------------------------------------------
class TCoc {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);
	double        __fastcall GetValue(void);

public:
				  TCoc(TAnalys *analys);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

#pragma end_region

#pragma region TPixelSize

// -----------------------------------------------------
// CLASS TPixelSize
// -----------------------------------------------------
class TPixelSize {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);
	double        __fastcall GetValue(void);

public:
				  TPixelSize(TAnalys *analys);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};
#pragma end_region

#pragma region TCropFactor

// -----------------------------------------------------
// CLASS TCropFactor
// -----------------------------------------------------
class TCropFactor {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);
	double        __fastcall GetValue(void);

public:
				  TCropFactor(TAnalys *analys);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};
#pragma end_region

#pragma region TSensor

// -----------------------------------------------------
// CLASS TSensor
// -----------------------------------------------------
class TSensor {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);
	double        __fastcall GetDiagonal(void);
	double        __fastcall GetHeight(void);
	double        __fastcall GetWidth(void);
	bool          __fastcall GetIsFullFrame(void);

public:
	TCoc        *Coc;
	TCropFactor *CropFactor;
	TPixelSize  *PixelSize;

				  TSensor(TAnalys *analys);
				  ~TSensor(void);

	__property UnicodeString Caption     = {read = GetCaption};
	__property double        Diagonal    = {read = GetDiagonal};
	__property double        Height      = {read = GetHeight};
	__property double        Width       = {read = GetWidth};
	__property bool          IsFullFrame = {read = GetIsFullFrame};
};
#pragma end_region

#pragma region TRotate

// -----------------------------------------------------
// CLASS TRotate
// -----------------------------------------------------
class TRotate {
public:
	ERotate Value;

	TRotate(void);

	void __fastcall SetValue(double v);
};
#pragma end_region

#pragma region TLens

// -----------------------------------------------------
// CLASS TLens
// -----------------------------------------------------
class TLens {
	TAnalys       *Analys;
	UnicodeString PCaption;
	bool          PIsData;
	TLensData     *PLensData;

	TLensData* __fastcall GetLensData(void);
	void       __fastcall SetCaption(UnicodeString caption);
	double     __fastcall QueryIndiceForXY(double x, double y);
	double     __fastcall QueryIndiceForFocaleAperture(double focale, double aperture);
	double     __fastcall Focale2x(double focale);
	double     __fastcall x2Focale(double x);
	double     __fastcall Aperture2y(double aperture);
	double     __fastcall y2Aperture(double y);
	bool       __fastcall GetIsData(void);

public:
			   TLens(TAnalys *analys);

	double     __fastcall QueryIndice(double focale, double aperture);
	double     __fastcall QueryApertureMax(double focale);
	double     __fastcall QueryApertureMin(double focale);
	double     __fastcall QueryIndiceMax(double focale, double aperture);
	double     __fastcall QueryIndiceMin(double focale, double aperture);
	double     __fastcall QueryBestAperture(double focale);
	unsigned   __fastcall QueryIndiceBestLens(double focale);

	__property TLensData     *LensData = {read = GetLensData, write = PLensData};
	__property UnicodeString Caption   = {read = PCaption, write = SetCaption};
	__property bool          IsData    = {read = GetIsData};
};
#pragma end_region

#pragma region TExposureTime

// -----------------------------------------------------
// CLASS ETBest
// -----------------------------------------------------
class ETBest {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:

	ETBest(TAnalys *analys);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS ETLimit
// -----------------------------------------------------
class ETLimit {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);
	bool __fastcall GetIsInRange(void);

public:

	ETLimit(TAnalys *analys);

	__property UnicodeString Caption   = {read = GetCaption};
	__property double        Value     = {read = GetValue};
	__property bool          IsInRange = {read = GetIsInRange};
};

// -----------------------------------------------------
// CLASS ETEXBest
// -----------------------------------------------------
class ETEXBest {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:

	ETEXBest(TAnalys *analys);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS ETEXLimitRelative
// -----------------------------------------------------
class ETEXLimitRelative {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:

	ETEXLimitRelative(TAnalys *analys);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS ETEXLimit
// -----------------------------------------------------
class ETEXLimit {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:
	ETEXLimitRelative *Relative;

	ETEXLimit(TAnalys *analys);
	~ETEXLimit(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS ETExposureCompens
// -----------------------------------------------------
class ETExposureCompens {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:
	ETEXBest *Best;
	ETEXLimit *Limit;

	ETExposureCompens(TAnalys *analys);
	~ETExposureCompens(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS TExposureTime
// -----------------------------------------------------
class TExposureTime {
	double PValue;

	void __fastcall SetValue(double exposuretime);
	UnicodeString __fastcall GetCaption(void);

public:
	ETExposureCompens *ExposureCompens;
	ETBest *Best;
	ETLimit *Limit;

	TExposureTime(TAnalys *analys);
	~TExposureTime(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = PValue, write = SetValue};
};

#pragma end_region

#pragma region TAperture

// -----------------------------------------------------
// CLASS ABest
// -----------------------------------------------------
class ABest {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:
	ABest(TAnalys *analys);
	~ABest(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS AEXLimitRelative
// -----------------------------------------------------
class AEXLimitRelative {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:
	AEXLimitRelative(TAnalys *analys);
	~AEXLimitRelative(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS ALimit
// -----------------------------------------------------
class ALimit {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);
	bool __fastcall GetIsInRange(void);

public:

	ALimit(TAnalys *analys);
	~ALimit(void);

	__property UnicodeString Caption   = {read = GetCaption};
	__property double        Value     = {read = GetValue};
	__property bool          IsInRange = {read = GetIsInRange};
};

// -----------------------------------------------------
// CLASS AEXBest
// -----------------------------------------------------
class AEXBest {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:
	AEXBest(TAnalys *analys);
	~AEXBest(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS AEXLimit
// -----------------------------------------------------
class AEXLimit {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:
	AEXLimitRelative *Relative;

	AEXLimit(TAnalys *analys);
	~AEXLimit(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS AExposureCompens
// -----------------------------------------------------
class AExposureCompens {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:
	AEXBest *Best;
	AEXLimit *Limit;

	AExposureCompens(TAnalys *analys);
	~AExposureCompens(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS TAperture
// -----------------------------------------------------
class TAperture {
	double PValue;

	void __fastcall SetValue(double aperture);
	UnicodeString __fastcall GetCaption(void);

public:
	ABest *Best;
	ALimit *Limit;
	AExposureCompens *ExposureCompens;

	TAperture(TAnalys *analys);
	~TAperture(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = PValue, write = SetValue};
};

#pragma end_region

#pragma region TIso

// -----------------------------------------------------
// CLASS IBest
// -----------------------------------------------------
class IBest {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:

	IBest(TAnalys *analys);
	~IBest(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS ILimit
// -----------------------------------------------------
class ILimit {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);
	bool __fastcall GetIsInRange(void);

public:

	ILimit(TAnalys *analys);
	~ILimit(void);

	__property UnicodeString Caption   = {read = GetCaption};
	__property double        Value     = {read = GetValue};
	__property bool          IsInRange = {read = GetIsInRange};
};

// -----------------------------------------------------
// CLASS IEXBest
// -----------------------------------------------------
class IEXBest {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:

	IEXBest(TAnalys *analys);
	~IEXBest(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS IEXLimitRelative
// -----------------------------------------------------
class IEXLimitRelative {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:

	IEXLimitRelative(TAnalys *analys);
	~IEXLimitRelative(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS IEXLimit
// -----------------------------------------------------
class IEXLimit {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:
	IEXLimitRelative *Relative;

	IEXLimit(TAnalys *analys);
	~IEXLimit(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS IEXDeltaLimitBest
// -----------------------------------------------------
class IEXDeltaLimitBest {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:

	IEXDeltaLimitBest(TAnalys *analys);
	~IEXDeltaLimitBest(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS IExposureCompens
// -----------------------------------------------------
class IExposureCompens {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:
	IEXLimit *Limit;
	IEXBest *Best;
	IEXDeltaLimitBest *DeltaLimitBest;

	IExposureCompens(TAnalys *analys);
	~IExposureCompens(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

// -----------------------------------------------------
// CLASS TIso
// -----------------------------------------------------
class TIso {
	double PValue;

	void __fastcall SetValue(double iso);
	UnicodeString __fastcall GetCaption(void);

public:
	IExposureCompens *ExposureCompens;
	IBest* Best;
	ILimit* Limit;

	TIso(TAnalys *analys);
	~TIso(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = PValue, write = SetValue};
};

#pragma end_region

#pragma region TIn24x36

// -----------------------------------------------------
// CLASS TIn24x36
// -----------------------------------------------------
class TIn24x36 {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);
	double __fastcall GetValue(void);

public:
	TIn24x36(TAnalys *analys);
	~TIn24x36(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

#pragma end_region

#pragma region TAngle

// -----------------------------------------------------
// CLASS TAngle
// -----------------------------------------------------
class TAngle {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);
	double __fastcall GetValue(void);

public:
	TAngle(TAnalys *analys);
	~TAngle(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

#pragma end_region

#pragma region TBorder

// -----------------------------------------------------
// CLASS TBorder
// -----------------------------------------------------
class TBorder {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);
	double __fastcall GetValue(void);

public:
	TBorder(TAnalys *analys);
	~TBorder(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

#pragma end_region

#pragma region TFocale

// -----------------------------------------------------
// CLASS TFocale
// -----------------------------------------------------
class TFocale {
	double PValue;

	void __fastcall SetValue(double f);
	UnicodeString __fastcall GetCaption(void);

public:
	TIn24x36 *In24x36;
	TAngle *Angle;
	TBorder *Border;

	TFocale(TAnalys *analys);
	~TFocale(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = PValue, write = SetValue};
};

#pragma end_region

#pragma region TDepthOfField

// -----------------------------------------------------
// CLASS TDepthOfField
// -----------------------------------------------------
class TDepthOfField {
	TSubjectDistance *SubjectDistance;
	TUpper *Upper;
	TLower *Lower;

	UnicodeString __fastcall GetCaption(void);
	double __fastcall GetValue(void);

public:
	TDepthOfField(TSubjectDistance *subjectdistance, TUpper *upper, TLower *lower);
	~TDepthOfField(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

#pragma end_region

#pragma region TSubjectDistance

// -----------------------------------------------------
// CLASS TSubjectDistance
// -----------------------------------------------------
class TSubjectDistance {
	TAnalys *Analys;
	double PValue;
	UnicodeString PCaption;
	bool PIsValid;

	UnicodeString __fastcall GetCaption(void);
	UnicodeString __fastcall GetVerbose(void);
	void __fastcall SetValue(double value);
	void __fastcall WriteValue(double value, bool bracket);

public:

	TSubjectDistance(TAnalys *analys);
	~TSubjectDistance(void);

	void __fastcall Compute(double Focale, double Hyperfocale, double FocusDistanceLower, double upperdcraw);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = PValue, write = SetValue};
	__property bool          IsValid = {read = PIsValid};
	__property UnicodeString Verbose = {read = GetVerbose};
};

#pragma end_region

#pragma region TUpper

// -----------------------------------------------------
// CLASS TUpper
// -----------------------------------------------------
class TUpper {
	double PValue;
	double POriginalValue;
	UnicodeString PCaption;

	void __fastcall SetValue(double v);
	void __fastcall SetOriginalValue(double dfc);
	UnicodeString __fastcall GetCaption(void);

public:
	TUpper(void);
	~TUpper(void);
	void __fastcall Compute(double SujectDistance, double Hyperfocale, double Focale);

	__property UnicodeString Caption       = {read = GetCaption};
	__property double        Value         = {read = PValue, write = SetValue};
	__property double        OriginalValue = {read = POriginalValue, write = SetOriginalValue};
};

#pragma end_region

#pragma region TLower

// -----------------------------------------------------
// CLASS TLower
// -----------------------------------------------------
class TLower {
	double PValue;
	UnicodeString PCaption;
	bool PComment;
	bool PBracket;

	void __fastcall SetValue(double v);
	UnicodeString __fastcall GetCaption(void);

public:

	TLower(void);
	~TLower(void);

	void __fastcall Compute(double sujectdist, double hyperfocale, double HyperfocaleLower, double Focale, double upperdcraw);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = PValue, write = SetValue};
};

#pragma end_region

#pragma region TFocusDistance

// -----------------------------------------------------
// CLASS TFocusDistance
// -----------------------------------------------------
class TFocusDistance {
	TAnalys *Analys;
	UnicodeString PVerbose;

	UnicodeString __fastcall GetVerbose(void);

public:
	TSubjectDistance *SubjectDistance;
	TDepthOfField *DepthOfField;
	TUpper *Upper;
	TLower *Lower;

	TFocusDistance(TAnalys *analys);
	~TFocusDistance(void);

	void __fastcall Compute(double focusdistancelower, double Hyperfocale, double HyperfocaleLower, double Focale);

	__property UnicodeString Verbose = {read = GetVerbose};
};

#pragma end_region

#pragma region TSubjectSpeedLimit

// -----------------------------------------------------
// CLASS TSubjectSpeedLimit
// -----------------------------------------------------
class TSubjectSpeedLimit {
	TAnalys *Analys;

	double __fastcall GetValue(void);
	UnicodeString __fastcall GetCaption(void);

public:

	TSubjectSpeedLimit(TAnalys *analys);
	~TSubjectSpeedLimit(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

#pragma end_region

#pragma region THyperfocale

// -----------------------------------------------------
// CLASS THyperfocale
// -----------------------------------------------------
class THyperfocale {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);
	UnicodeString __fastcall GetVerbose(void);
	double __fastcall GetValue(void);

public:
	TFocusDistance *FocusDistance;

	THyperfocale(TAnalys *analys);
	~THyperfocale(void);

	void __fastcall Compute(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
	__property UnicodeString Verbose = {read = GetVerbose};
};

#pragma end_region

#pragma region THistogram

class THistogram {
	TBitmap *PBitmap;

public:
	THistogram(void);
	~THistogram(void);

	void __fastcall Compute(TBitmap *bitmap, TImage *dest);
};

#pragma end_region

#pragma region TEvaluate

// -----------------------------------------------------
// CLASS TEvaluate
// -----------------------------------------------------
class TEvaluate {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);
	double __fastcall GetValue(void);

public:
	TEvaluate(TAnalys *analys);
	~TEvaluate(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

#pragma end_region

#pragma region TRelative

// -----------------------------------------------------
// CLASS TRelative
// -----------------------------------------------------
class TRelative {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);
	double __fastcall GetValue(void);

public:
	TRelative(TAnalys *analys);
	~TRelative(void);

	__property UnicodeString Caption = {read = GetCaption};
	__property double        Value   = {read = GetValue};
};

#pragma end_region

#pragma region TNaturalLight

// -----------------------------------------------------
// CLASS TNaturalLight
// -----------------------------------------------------
class TNaturalLight {
	TAnalys *Analys;

	UnicodeString __fastcall GetCaption(void);

public:
	TNaturalLight(TAnalys *analys);
	~TNaturalLight(void);

	__property UnicodeString Caption = {read = GetCaption};
};

#pragma end_region

#pragma region TExposure

// -----------------------------------------------------
// CLASS TExposure
// -----------------------------------------------------
class TExposure {
	double PValue;
	double PRelativeDec;
	bool PIsFromCamera;
	TAnalys *Analys;

	void __fastcall SetValue(double Ev);
	UnicodeString __fastcall GetCaption(void);

public:
	TEvaluate *Evaluate;
	TRelative *Relative;
	TNaturalLight *NaturalLight;

	TExposure(TAnalys *analys);
	~TExposure(void);

	__property UnicodeString Caption      = {read = GetCaption};
	__property double        Value        = {read = PValue, write = SetValue};
	__property bool          IsFromCamera = {read = PIsFromCamera};
};

#pragma end_region

#pragma region TFlash

// -----------------------------------------------------
// CLASS FDuration
// -----------------------------------------------------
class FDuration {
	TAnalys *Analys;

	double __fastcall GetValue(void);

public:

	FDuration(TAnalys *analys);
	~FDuration(void);

	__property double Value = {read = GetValue};
};

// -----------------------------------------------------
// CLASS FPower
// -----------------------------------------------------
class FPower {
	TAnalys *Analys;

	double __fastcall GetValue(void);

public:

	FPower(TAnalys *analys);
	~FPower(void);

	__property double Value = {read = GetValue};
};

// -----------------------------------------------------
// CLASS FBiasTag
// -----------------------------------------------------
class FBiasTag {
public:
	double Value;

	FBiasTag(void);
	~FBiasTag(void);
};

// -----------------------------------------------------
// CLASS FBias
// -----------------------------------------------------
class FBias {
	TAnalys *Analys;

	double __fastcall GetValue(void);

public:
	FBiasTag *Tag;

	FBias(TAnalys *analys);
	 ~FBias(void);

	__property double Value = {read = GetValue};
};

// -----------------------------------------------------
// CLASS FFiredTag
// -----------------------------------------------------
class FFiredTag {
	TAnalys *Analys;

	double PValue;

	void __fastcall SetValue(double v);

public:

	FFiredTag(TAnalys *analys);
	~FFiredTag(void);

	__property double Value = {read = PValue, write = SetValue};
};

// -----------------------------------------------------
// CLASS FFired
// -----------------------------------------------------
class FFired {
public:
	bool IsFired;
	FFiredTag *Tag;

	FFired(TAnalys *analys);
	~FFired(void);
};

// -----------------------------------------------------
// CLASS FRequiredTag
// -----------------------------------------------------
class FRequiredTag {
	TAnalys *Analys;

	double PValue;

	void __fastcall SetValue(double v);

public:

	FRequiredTag(TAnalys *analys);
	~FRequiredTag(void);

	__property double Value = {read = PValue, write = SetValue};
};

// -----------------------------------------------------
// CLASS FRequired
// -----------------------------------------------------
class FRequired {
public:
	bool Value;
	FRequiredTag *Tag;

	FRequired(TAnalys *analys);
	 ~FRequired(void);
};

// -----------------------------------------------------
// CLASS FDidNotFire
// -----------------------------------------------------
class FDidNotFire {
	TAnalys *Analys;

	bool __fastcall GetIsNotFired(void);

public:
	FDidNotFire(TAnalys *analys);
	~FDidNotFire(void);

	__property bool IsNotFired = {read = GetIsNotFired};
};

// -----------------------------------------------------
// CLASS FNgLimit
// -----------------------------------------------------
class FNgLimit {
	TAnalys *Analys;

	double __fastcall GetValue(void);

public:

	FNgLimit(TAnalys *analys);
	~FNgLimit(void);

	__property double Value = {read = GetValue};
};

// -----------------------------------------------------
// CLASS FNg
// -----------------------------------------------------
class FNg {
	TAnalys *Analys;

	double __fastcall GetValue(void);

public:
	FNgLimit *Limit;

	FNg(TAnalys *analys);
	~FNg(void);

	__property double Value = {read = GetValue};
};

// -----------------------------------------------------
// CLASS FExposureCompens
// -----------------------------------------------------
class FExposureCompens {
	TAnalys *Analys;

	double __fastcall GetValue(void);

public:

	FExposureCompens(TAnalys *analys);
	~FExposureCompens(void);

	__property double Value = {read = GetValue};
};

// -----------------------------------------------------
// CLASS FAperture
// -----------------------------------------------------
class FAperture {
	TAnalys *Analys;

	double __fastcall GetValue(void);

public:

	FAperture(TAnalys *analys);
	~FAperture(void);

	__property double Value = {read = GetValue};
};

// -----------------------------------------------------
// CLASS FDistance
// -----------------------------------------------------
class FDistance {
	TAnalys *Analys;

	double __fastcall GetValue(void);

public:

	FDistance(TAnalys *analys);
	~FDistance(void);

	__property double Value = {read = GetValue};
};

// -----------------------------------------------------
// CLASS FLimit
// -----------------------------------------------------
class FLimit {
public:
	FDistance *Distance;
    FAperture *Aperture;

	FLimit(TAnalys *analys);
	~FLimit(void);
};

// -----------------------------------------------------
// CLASS FRange
// -----------------------------------------------------
class FRange {
	TAnalys *Analys;

	bool __fastcall GetIsOkWithBias(void);
	bool __fastcall GetIsOkWithoutBias(void);
//	bool __fastcall GetIsLimitWithBias(void);
//	bool __fastcall GetIsLimitWithoutBias(void);

public:

	FRange(TAnalys *analys);
	~FRange(void);

	__property bool IsOkWithBias    = {read = GetIsOkWithBias};
	__property bool IsOkWithoutBias = {read = GetIsOkWithoutBias};
//	__declspec(property(get = GetIsLimitWithBias))bool IsLimitWithBias;
//	__declspec(property(get = GetIsLimitWithoutBias))bool IsLimitWithoutBias;
};

// -----------------------------------------------------
// CLASS TFlash
// -----------------------------------------------------
class TFlash {
public:
	TFlashData *FlashData;
	FFired *Fired;
	FRequired *Required;
	FDidNotFire *DidNotFire;
	FNg *Ng;
	FBias *Bias;
	FPower *Power;
	FDuration *Duration;
	FExposureCompens *ExposureCompens;
	FLimit *Limit;
	FRange *Range;

	bool IsValid;
	bool External;
	bool BuiltIn;
	double ValueExternal;
	double ValueBuiltIn;

	TFlash(TAnalys *analys);
	~TFlash(void);
};
#pragma end_region

#pragma region TAnalys

// -----------------------------------------------------
// CLASS TAnalys
// -----------------------------------------------------
class TAnalys {
	TLgs* PLgs;

public:
	TMapCamera          *MapCamera;
	TSensor             *Sensor;
	TLens               *Lens;
	TExposureTime       *ExposureTime;
	TAperture           *Aperture;
	TFocale             *Focale;
	TFocusDistance      *FocusDistance;
	THyperfocale        *Hyperfocale;
	TIso                *Iso;
	TExposure           *Exposure;
	TFlash              *Flash;
	TApex               *Apex;
	THistogram          *Histogram;
	TSubjectSpeedLimit  *SubjectSpeedLimit;
	TRotate             *Rotate;

		 TAnalys(TLgs *lgs);
		 ~TAnalys(void);

	void __fastcall InitData(void);
	void __fastcall Compute(void);

	__property TLgs *Lgs = {read = PLgs};
};

#pragma end_region

#endif
