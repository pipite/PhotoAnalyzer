#ifndef CLASSIFDSH
#define CLASSIFDSH

#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "ClassTagMap.h"
#include "mathexpr.h"
#include "UtilCommon.h"

// -----------------------------------------------------
// CLASS TData
// -----------------------------------------------------
class TData {
	TLgs           *Lgs;
	SURational     PURational;
	SSRational     PSRational;
	UnicodeString  PCaption;       // ..Query:Yes . chaine si type 2
	UnicodeString  PVerbose;       // ..Query:No .. chaine affichage explicite
	unsigned       PLength;        // ..Query:No  . longueur en type (1 si type 2)
	unsigned       PIndex;         // ..Query:Yes . index du tag
	double         PValue;         // ..Query:Yes . valeur du tag
	unsigned       POffset;        // ..Query:Yes . offset du tag
	unsigned short PType;          // ..Query:Yes . type (1 a 12)
	bool           PDump;          // ..Query:Yes . Tag a memoriser ou non
	unsigned       PVirtualLength; // ..Query:No  . longueur en type non mémorisé
	char           *PMemData;      // ..Query:No .. dump en memoire
	unsigned       PDumpStrCount;  // ..Query:No .. Nombre de chaine du dump en clair

	UnicodeString __fastcall GetMapDataCaption(void);
	unsigned      __fastcall short GetUsed(void);
	UnicodeString __fastcall GetFormula(void);
	unsigned      __fastcall GetFormat(void);
	double        __fastcall GetCalcValue(void);
	UnicodeString __fastcall GetEnumCaption(void);
	UnicodeString __fastcall GetCaption(void);
	void          __fastcall SetCaption(UnicodeString caption);
	void          __fastcall SetLength(unsigned length);
	double        __fastcall GetValue(void);
	UnicodeString __fastcall GetVerbose(void);
	UnicodeString __fastcall GetShortVerbose(void);
	UnicodeString __fastcall GetUserVerbose(void);

	unsigned short __fastcall GetType(void);

public:
	TMapData      *MapData;
	TEnumArray    *EnumArray;
	UnicodeString SubDir;     // Query:Yes . Nom du subifd si ce tag pointe sur un subifd
	TStringList   *DumpStr;   // Query:No .. chaines data en clair

	TData(TLgs *lgs);
	~TData(void);

	bool __fastcall GenerateDumpStr(unsigned nlong);

	__property UnicodeString MapDataCaption = {read = GetMapDataCaption};
	__property UnicodeString Formula        = {read = GetFormula};
	__property unsigned Format              = {read = GetFormat};
	__property unsigned short Used          = {read = GetUsed};
	__property UnicodeString Caption        = {read = GetCaption, write = SetCaption};
	__property UnicodeString EnumCaption    = {read = GetEnumCaption};
	__property char *MemData                = {read = PMemData, write = PMemData};
	__property unsigned DumpStrCount        = {read = PDumpStrCount};
	__property UnicodeString Verbose        = {read = GetVerbose};
	__property UnicodeString ShortVerbose   = {read = GetShortVerbose};
	__property UnicodeString UserVerbose    = {read = GetUserVerbose};
	__property double Value                 = {read = GetValue, write = PValue};
	__property double CalcValue             = {read = GetCalcValue};
	__property bool Dump                    = {read = PDump, write = PDump};
	__property unsigned short Type          = {read = PType, write = PType};
	__property unsigned Index               = {read = PIndex, write = PIndex};
	__property unsigned Offset              = {read = POffset, write = POffset};
	__property unsigned Length              = {read = PLength, write = SetLength};
	__property unsigned VirtualLength       = {read = PVirtualLength, write = PVirtualLength};
	__property SURational URational         = {read = PURational, write = PURational};
	__property SSRational SRational         = {read = PSRational, write = PSRational};
	// TData
};

// -----------------------------------------------------
// CLASS TDatas    6 query
// -----------------------------------------------------
class TDatas {
	TLgs           *Lgs;
	unsigned short PTagNumber;
	unsigned       PType;
	unsigned       PIndex;
	unsigned       POffset;
	int            i;

	UnicodeString  __fastcall GetVerbose(void);
	void           __fastcall SetCount(unsigned count);
	unsigned       __fastcall GetCount(void);

public:
	std::vector<TData*>Data;

				   TDatas(TLgs *lgs);
				   ~TDatas(void);

	void           __fastcall Clear(void);
	TData*         __fastcall GetData(unsigned idx);

	double         __fastcall QueryDataValue(unsigned DataIndex);
	double         __fastcall QueryDataCalcValue(unsigned DataIndex);
	unsigned       __fastcall QueryDataOffset(unsigned DataIndex);
	unsigned       __fastcall QueryDataFormat(unsigned DataIndex);
	UnicodeString  __fastcall QueryDataCaption(unsigned DataIndex);
	UnicodeString  __fastcall QueryDataVerbose(unsigned DataIndex);
	unsigned short __fastcall QueryDataType(unsigned DataIndex);
	bool           __fastcall QueryDataDump(unsigned DataIndex);
	UnicodeString  __fastcall QueryDataSubDir(unsigned DataIndex);

	__property unsigned       Index     = {read = PIndex, write = PIndex};
	__property unsigned       Count     = {read = GetCount, write = SetCount};
	__property unsigned       Type      = {read = PType, write = PType};
	__property unsigned short TagNumber = {read = PTagNumber, write = PTagNumber};
	__property unsigned       Offset    = {read = POffset, write = POffset};
	__property UnicodeString  Verbose   = {read = GetVerbose};
	// TDatas
};

// -----------------------------------------------------
// CLASS TIfd      6 query
// -----------------------------------------------------
class TIfd {
	TLgs     *Lgs;
	unsigned POffset;

	UnicodeString  __fastcall GetVerbose(void);
	void           __fastcall SetCount(unsigned short count);
	unsigned short __fastcall GetCount(void);

public:
	std::vector<TDatas*>Datas;
	UnicodeString Caption;

				   TIfd(TLgs *lgs);
				   ~TIfd(void);

	void           __fastcall Clear(void);
	void           __fastcall Parse(FILE *ifp, unsigned base, TMapCamera *mapcamera, int *ByteOrder);
	TDatas*        __fastcall GetDatas(unsigned idx);

	// Query
	double         __fastcall QueryDataValue(unsigned short DatasTagnumber, unsigned DataIndex);
	double         __fastcall QueryDataCalcValue(unsigned short DatasTagnumber, unsigned DataIndex);
	unsigned       __fastcall QueryDataOffset(unsigned short DatasTagnumber, unsigned DataIndex);
	UnicodeString  __fastcall QueryDataCaption(unsigned short DatasTagnumber, unsigned DataIndex);
	UnicodeString  __fastcall QueryDataVerbose(unsigned short DatasTagnumber, unsigned DataIndex);
	unsigned short __fastcall QueryDataType(unsigned short DatasTagnumber, unsigned DataIndex);
	bool           __fastcall QueryDataDump(unsigned short DatasTagnumber, unsigned DataIndex);
	UnicodeString  __fastcall QueryDataSubDir(unsigned short DatasTagnumber, unsigned DataIndex);

	__property unsigned short Count     = {read = GetCount, write = SetCount};
	__property unsigned       Offset    = {read = POffset, write = POffset};
	__property UnicodeString  Verbose   = {read = GetVerbose};
	// TIfd
};

// -----------------------------------------------------
// CLASS TFileHeader
// -----------------------------------------------------
class TFileHeader {
	unsigned      PHeaderLength;
	unsigned      PFileSize;
	unsigned      PFirstIfdsOffset;
	unsigned      base;
	UnicodeString PFormat;
	char          *PHead;
	/* TODO : inclure byteorder ici */
public:

	TFileHeader(void);
	~TFileHeader(void);

	bool __fastcall parse(FILE *ifp, unsigned *Baseifp, int *ByteOrder);

	__property unsigned FirstIfdsOffset   = {read = PFirstIfdsOffset};
	// TFileHeader
};

// -----------------------------------------------------
// CLASS TIfds    13 query
// -----------------------------------------------------
class TIfds {
	TLgs        *Lgs;
	TFileHeader *FileHeader;
	TTagMap     *TagMap;
	int         ByteOrder;

	void           __fastcall SetCount(unsigned short count);
	unsigned short __fastcall GetCount(void);
	UnicodeString  __fastcall GetVerbose(void);
	unsigned       __fastcall RecurseParseSubDir(FILE *ifp, unsigned base, unsigned idxifd, UnicodeString *parentname, TMapCamera *mapcamera);

public:
	std::vector<TIfd*>Ifd;
	TMapCamera* MapCamera;

				   TIfds(TTagMap *tagmap, TLgs *lgs);
				   ~TIfds(void);

	void           __fastcall Clear(void);
	void           __fastcall Parse(FILE *ifp, unsigned *Baseifp);
	TIfd*          __fastcall GetIfd(unsigned idx);

	// Query
	double         __fastcall QueryDataValue(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex);
	double         __fastcall QueryDataCalcValue(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex);
	unsigned       __fastcall QueryDataOffset(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex);
	UnicodeString  __fastcall QueryDataCaption(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex);
	UnicodeString  __fastcall QueryDataVerbose(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex);
	unsigned short __fastcall QueryDataType(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex);
	bool           __fastcall QueryDataDump(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex);
	UnicodeString  __fastcall QueryDataSubDir(unsigned short IfdIndex, unsigned short DatasTagnumber, unsigned DataIndex);
	double         __fastcall QueryDataValue(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex);
	unsigned       __fastcall QueryDataOffset(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex);
	UnicodeString  __fastcall QueryDataCaption(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex);
	UnicodeString  __fastcall QueryDataVerbose(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex);
	unsigned short __fastcall QueryDataType(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex);
	bool           __fastcall QueryDataDump(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex);
	UnicodeString  __fastcall QueryDataSubDir(UnicodeString *IfdCaption, unsigned short DatasTagnumber, unsigned DataIndex);
	unsigned short __fastcall QueryIfdIndex(UnicodeString *IfdCaption);

	__property unsigned short Count     = {read = GetCount, write = SetCount};
	__property UnicodeString  Verbose   = {read = GetVerbose};
};

#endif