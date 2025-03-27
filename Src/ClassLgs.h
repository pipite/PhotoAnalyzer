//---------------------------------------------------------------------------

#ifndef ClassLgsH
#define ClassLgsH
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <FMX.Layouts.hpp>
#include <vector>

#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>

class TLg;
class TLgs;

#include "UtilCommon.h"

// -----------------------------------------------------
// CLASS TLgKey
// -----------------------------------------------------
class TLgKey {

	public:
	UnicodeString Key;
	TStringList *Traduct;

	TLgKey(UnicodeString key);
	~TLgKey(void);

};

// -----------------------------------------------------
// CLASS TLgs
// -----------------------------------------------------
class TLgs {
	unsigned      PIdxLang;
	UnicodeString PActiveLang;

	unsigned      __fastcall GetCountLgKey(void);
	unsigned      __fastcall GetCountLang(void);
	void          __fastcall SetActiveLang(UnicodeString lang);
	void          __fastcall Clear(void);

	public:

	std::vector<TLgKey*>LgKey;
	TStringList *Lang;

				  TLgs(void);
				  ~TLgs(void);

	TLgKey*       __fastcall GetLgKey(unsigned idx);
	void          __fastcall AddLang(UnicodeString lang);
	UnicodeString __fastcall QueryKey(UnicodeString key);
	TLgKey*       __fastcall FindOrAddKey(UnicodeString key);

	void          __fastcall LoadXML(UnicodeString filename);

	__property unsigned      CountLgKey = {read = GetCountLgKey};
	__property unsigned      CountLang  = {read = GetCountLang};
	__property UnicodeString ActiveLang = {read = PActiveLang, write = SetActiveLang};
};

#endif
