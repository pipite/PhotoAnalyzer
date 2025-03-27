#ifndef CLASSTAGMAPH
#define CLASSTAGMAPH

#include <FMX.Layouts.hpp>
#include <FMX.TreeView.hpp>
#include <vector>

#include "UtilCommon.h"

// -----------------------------------------------------
// CLASS TLensData
// -----------------------------------------------------
class TLensData{
	TBitmap       *PBitmapData;
	TBitmap       *PBitmapView;
	UnicodeString PMaker;
	UnicodeString PModel;
	UnicodeString PLensModel;
	float         PFocaleMin;
	float         PFocaleMax;
	float         PApertureMin;
	float         PApertureMax;
	unsigned      PPrice;
	bool          PStabilized;
	bool          PIsData;

	bool __fastcall GetIsBitmapData(void);

	public:

		 TLensData(void);
		 ~TLensData(void);

	void __fastcall Load(UnicodeString maker, UnicodeString model, UnicodeString lensmodel);

	__property TBitmap       *BitmapData = {read = PBitmapData};
	__property bool          IsData      = {read = PIsData};
	__property UnicodeString Maker       = {read = PMaker};
	__property UnicodeString Model       = {read = PModel};
	__property UnicodeString LensModel   = {read = PLensModel};
	__property float         FocaleMin   = {read = PFocaleMin};
	__property float         FocaleMax   = {read = PFocaleMax};
	__property float         ApertureMin = {read = PApertureMin};
	__property float         ApertureMax = {read = PApertureMax};
	__property unsigned      Price       = {read = PPrice};
	__property bool          Stabilized  = {read = PStabilized};
};

// -----------------------------------------------------
// CLASS TLensDatas
// -----------------------------------------------------
class TLensDatas {
	unsigned   __fastcall GetCount(void);
	void       __fastcall Clear(void);

public:
	std::vector<TLensData*>LensData;

			   TLensDatas(void);
			   ~TLensDatas(void);

	TLensData* __fastcall Get(unsigned idx);
	void       __fastcall Add(UnicodeString maker, UnicodeString model);
	TLensData* __fastcall QueryLensData(UnicodeString lensmodel);

	__property unsigned Count = {read = GetCount};
};

// -----------------------------------------------------
// CLASS TFlashData
// -----------------------------------------------------
class TFlashData{
	TBitmap       *PBitmapView;
	UnicodeString PMaker;
	UnicodeString PModel;
	UnicodeString PFlashModel;
	UnicodeString PType;
	unsigned      PPriority;
	double        PBaseNg;
	double        PBaseFocale;
	double        PBaseIso;
	double        PDistanceMin;
	double        PDistanceMax;
	double        PDistanceMAxHSync;
	double        PHSync;
	double        PHSyncCoef;
	double        PTolerance;
	unsigned      PFlashDurationCount;

	void __fastcall SetFlashDurationCount(unsigned count);

	public:
	double *FlashDurationAtPower;
	double *FlashDuration;

		 TFlashData(void);
		 ~TFlashData(void);

	void __fastcall Load(UnicodeString maker, UnicodeString model, UnicodeString flashmodel);

	__property UnicodeString Maker              = {read = PMaker};
	__property UnicodeString Model              = {read = PModel};
	__property UnicodeString FlashModel         = {read = PFlashModel};
	__property double        BaseNg             = {read = PBaseNg};
	__property double        BaseFocale         = {read = PBaseFocale};
	__property double        BaseIso            = {read = PBaseIso};
	__property double        DistanceMin        = {read = PDistanceMin};
	__property double        DistanceMax        = {read = PDistanceMax};
	__property double        DistanceMAxHSync   = {read = PDistanceMAxHSync};
	__property double        HSync              = {read = PHSync};
	__property double        HSyncCoef          = {read = PHSyncCoef};
	__property double        Tolerance          = {read = PTolerance, write = PTolerance};
	__property UnicodeString Type               = {read = PType};
	__property unsigned      Priority           = {read = PPriority};
	__property unsigned      FlashDurationCount = {read = PFlashDurationCount, write = SetFlashDurationCount};
};

// -----------------------------------------------------
// CLASS TFlashDatas
// -----------------------------------------------------
class TFlashDatas {
	unsigned    __fastcall GetCount(void);
	void        __fastcall Clear(void);

public:
	std::vector<TFlashData*>FlashData;

				TFlashDatas(void);
				~TFlashDatas(void);

	TFlashData* __fastcall Get(unsigned idx);
	void        __fastcall Add(UnicodeString maker, UnicodeString model);
	TFlashData* __fastcall QueryFlashData(UnicodeString maker, UnicodeString model, UnicodeString flashtype);

	__property unsigned Count = {read = GetCount};
};

// -----------------------------------------------------
// CLASS TEnumArray
// -----------------------------------------------------
class TEnumArray {
	UnicodeString PEnums;

	void          __fastcall SetEnums(UnicodeString enums);

public:
	UnicodeString Maker;
	UnicodeString Model;
	UnicodeString Ifd;
	UnicodeString Caption;
	bool          BitEnum;

				  TEnumArray(void);

	UnicodeString __fastcall QueryEnumCaption(double value);
	bool          __fastcall QueryEnumFlag(unsigned value, UnicodeString bits);

	__property UnicodeString Enums = {read = PEnums, write = SetEnums};
	// TMapEnumArray
};

// -----------------------------------------------------
// CLASS TEnumArrays
// -----------------------------------------------------
class TEnumArrays {
	UnicodeString PVerbose;

	unsigned    __fastcall GetCount(void);
	void        __fastcall Clear(void);

public:
	std::vector<TEnumArray*>EnumArray;

				TEnumArrays(void);
				~TEnumArrays(void);

	TEnumArray* __fastcall Get(unsigned idx);
	TEnumArray* __fastcall Add(void);
	TEnumArray* __fastcall QueryEnumArray(UnicodeString caption, UnicodeString maker, UnicodeString model, UnicodeString ifd);
	bool        __fastcall QueryEnumFlag(UnicodeString caption, UnicodeString maker, UnicodeString model, UnicodeString ifd, double value, UnicodeString bits);

	__property unsigned Count        = {read = GetCount};
	__property UnicodeString Verbose = {read = PVerbose};
	// TEnumArrays
};

// -----------------------------------------------------
// CLASS TMapSubIfd
// -----------------------------------------------------
class TMapSubIfd {
	unsigned short PTagNumber;
	bool           PIsPointer;
	unsigned       PSeek;

	UnicodeString __fastcall GetVerbose(void);

public:
	UnicodeString Caption;

				 TMapSubIfd(void);

	void         __fastcall SetMapSubIfd(UnicodeString *caption, unsigned short tagnumber, bool ispointer, int seek);

	__property bool IsPointer           = {read = PIsPointer, write = PIsPointer};
	__property UnicodeString Verbose    = {read = GetVerbose};
	__property unsigned short TagNumber = {read = PTagNumber, write = PTagNumber};
	__property unsigned Seek            = {read = PSeek, write = PSeek};
	// TMapSubIfd
};

// -----------------------------------------------------
// CLASS TMapSubIfds
// -----------------------------------------------------
class TMapSubIfds {
	UnicodeString PVerbose;

	unsigned       __fastcall GetCount(void);

public:
	std::vector<TMapSubIfd*>MapSubIfd;

				   TMapSubIfds(void);
				   ~TMapSubIfds(void);

	void           __fastcall Clear(void);
	TMapSubIfd*    __fastcall Get(unsigned idx);
	TMapSubIfd*    __fastcall Add(void);
	UnicodeString  __fastcall QueryMapSubIfdCaption(unsigned short MapSubIfdTagNumber);
	unsigned short __fastcall QueryMapSubIfdTagNumber(UnicodeString *MapSubIfdCaption);
	bool           __fastcall QueryMapSubIfdIsPointer(unsigned short MapSubIfdTagNumber);
	int            __fastcall QueryMapSubIfdSeek(unsigned short MapSubIfdTagNumber);
	bool           __fastcall QueryMapSubIfdIsPointer(UnicodeString *MapSubIfdCaption);
	int            __fastcall QueryMapSubIfdSeek(UnicodeString *MapSubIfdCaption);
	unsigned       __fastcall QueryMapSubIfdIndex(UnicodeString *MapSubIfdCaption);
	unsigned       __fastcall QueryMapSubIfdIndex(unsigned short MapSubIfdTagNumber);

	__property unsigned Count        = {read = GetCount};
	__property UnicodeString Verbose = {read = PVerbose};
	// TMapSubIfds
};

// -----------------------------------------------------
// CLASS TMapData
// -----------------------------------------------------
class TMapData {
	unsigned short PTagNumber;
	unsigned       PUsed;
	unsigned       PIndex;
	bool           PDump;
	UnicodeString  PVerbose;
	/* TODO : recuperer pointeur si IfdChild */
	unsigned       PSubOffset;
	unsigned short PForceType;
	unsigned       PFormat;

	UnicodeString __fastcall GetVerbose(void);

public:
	UnicodeString Caption;
	UnicodeString Formula;

	TMapData(void);

	__property UnicodeString Verbose    = {read = GetVerbose};
	__property unsigned short TagNumber = {read = PTagNumber, write = PTagNumber};
	__property unsigned short ForceType = {read = PForceType, write = PForceType};
	__property unsigned Format          = {read = PFormat, write = PFormat};
	__property unsigned Index           = {read = PIndex, write = PIndex};
	__property unsigned Used            = {read = PUsed, write = PUsed};
	__property unsigned SubOffset       = {read = PSubOffset, write = PSubOffset};
	__property bool Dump                = {read = PDump, write = PDump};
	// TMapData
};

// -----------------------------------------------------
// CLASS TMapDatas
// -----------------------------------------------------
class TMapDatas {
	UnicodeString PVerbose;

	unsigned       __fastcall GetCount(void);

public:
	std::vector<TMapData*>MapData;

				   TMapDatas(void);
				   ~TMapDatas(void);

	void           __fastcall Clear(void);
	TMapData*      __fastcall Get(unsigned idx);
	TMapData*      __fastcall Add(void);
	UnicodeString  __fastcall QueryMapDataCaption(unsigned short DataTagNumber);
	UnicodeString  __fastcall QueryMapDataFormula(unsigned short DataTagNumber);
	UnicodeString  __fastcall QueryMapDataFormula(UnicodeString *DataCaption);
	unsigned short __fastcall QueryMapDataTagNumber(UnicodeString *DataCaption);
	unsigned       __fastcall QueryMapDataIndex(UnicodeString *DataCaption);
	unsigned       __fastcall QueryMapDataIndex(unsigned short DataTagNumber);

	__property unsigned      Count   = {read = GetCount};
	__property UnicodeString Verbose = {read = PVerbose};
	// TMapDatas
};

// -----------------------------------------------------
// CLASS TMapIfd
// -----------------------------------------------------
class TMapIfd {

	UnicodeString __fastcall GetVerbose(void);

public:
	UnicodeString Caption;
	TMapSubIfds   *MapSubIfds;
	TMapDatas     *MapDatas;

				 TMapIfd(void);
				 ~TMapIfd(void);

	__property UnicodeString Verbose = {read = GetVerbose};
	// TMapIfd
};

// -----------------------------------------------------
// CLASS TMaPIfds
// -----------------------------------------------------
class TMapIfds {
	unsigned      __fastcall GetCount(void);
	UnicodeString __fastcall GetVerbose(void);
	int verifadd, verifdel, verifcopy, verifdepop;

public:
	std::vector<TMapIfd*>MapIfd;

				  TMapIfds(void);
				  ~TMapIfds(void);

	void          __fastcall Clear(void);
	TMapIfd*      __fastcall Get(unsigned idx);
	TMapIfd*      __fastcall Add(void);
	TMapIfd*      __fastcall Copy(TMapIfd *mi);

	__property unsigned      Count   = {read = GetCount};
	__property UnicodeString Verbose = {read = GetVerbose};
	// TMapIfds
};

// -----------------------------------------------------
// CLASS TMapCamera
// -----------------------------------------------------
class TMapCamera {
	UnicodeString  __fastcall GetVerbose(void);
	UnicodeString  __fastcall GetMakerModelCaption(void);
	double         __fastcall GetCropFactor(void);

public:
	UnicodeString MakerCaption;
	UnicodeString Caption;
	UnicodeString SensorCaption;
	UnicodeString TagFlashFired;
	UnicodeString TagFlashOff;
	UnicodeString TagFlashExternal;
	UnicodeString TagFlashBuiltIn;
	UnicodeString IfdFlashFired;
	UnicodeString IfdFlashOff;
	UnicodeString IfdFlashExternal;
	UnicodeString IfdFlashBuiltIn;
	UnicodeString BitFlashFired;
	UnicodeString BitFlashOff;
	UnicodeString BitFlashExternal;
	UnicodeString BitFlashBuiltIn;
	double        SensorSizeX;
	double        SensorSizeY;
	double        ExposureTimeMin;
	double        ExposureTimeMax;
	double        IsoMin;
	double        IsoMax;
	double        FlashFillInLight;
	double        Resolution;
	bool          LensBuiltIn;
	TMapIfds      *MapIfds;
	TEnumArrays   *EnumArrays;
	TLensDatas    *LensDatas;
	TFlashDatas   *FlashDatas;

				   TMapCamera(void);
				   ~TMapCamera(void);

	void           __fastcall LoadLens(void);
	void           __fastcall LoadFlash(void);

	unsigned short __fastcall QueryMapIfdIndex(UnicodeString *MapIfdCaption);
	TEnumArray*    __fastcall QueryEnumArray(UnicodeString caption, UnicodeString maker, UnicodeString model, UnicodeString ifd);
	bool           __fastcall QueryMapData(UnicodeString *MapDataCaption, UnicodeString *MapIfdCaption, unsigned short*MapDataTagNumber, unsigned*MapDataIndex, bool*MapDataMemoryDump);
	TMapData*      __fastcall QueryMapDataPtr(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex);
	bool           __fastcall QueryMapDataDump(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber);
	UnicodeString  __fastcall QueryMapDataCaption(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex);
	UnicodeString  __fastcall QueryMapDataFormula(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex);
	unsigned short __fastcall QueryMapDataForceType(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex);
	unsigned       __fastcall QueryMapDataSubOffset(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber, unsigned MapDataIndex);
	unsigned short __fastcall QueryMapDataTagNumberCount(UnicodeString *MapIfdCaption, unsigned short MapDataTagNumber);

	__property UnicodeString Verbose           = {read = GetVerbose};
	__property UnicodeString MakerModelCaption = {read = GetMakerModelCaption};
	// TMapCamera
};

// -----------------------------------------------------
// CLASS TMapCameras
// -----------------------------------------------------
class TMapCameras {
	unsigned      __fastcall GetCount(void);
	UnicodeString __fastcall GetVerbose(void);

public:
	std::vector<TMapCamera*>MapCamera;

				  TMapCameras(void);
				  ~TMapCameras(void);

	void          __fastcall Clear(void);
	TMapCamera*   __fastcall Get(unsigned idx);
	TMapCamera*   __fastcall Add(void);
	TMapCamera*   __fastcall QueryMapCamera(UnicodeString *ModelCaption);
	TMapIfd*      __fastcall QueryMapIfdPtr(UnicodeString *maker, UnicodeString *model, UnicodeString *ifd);

	__property unsigned      Count   = {read = GetCount};
	__property UnicodeString Verbose = {read = GetVerbose};
	// TMapCameras
};

// -----------------------------------------------------
// CLASS TTagMap
// -----------------------------------------------------
class TTagMap {
	void     __fastcall Debug(UnicodeString txt);
	void     __fastcall ParseEnumTag(TEnumArray *EnumArray, UnicodeString s);
	unsigned __fastcall CountSpace(UnicodeString s);
	void     __fastcall TreeViewLoad(UnicodeString filename);

public:
	TMapCameras *MapCameras;
	TEnumArrays *EnumArrays;
	TTreeView   *TreeView;

			 TTagMap(TTreeView *treeView);
			 ~TTagMap(void);

	void     __fastcall LoadFromFile(UnicodeString filename);
};

#endif
