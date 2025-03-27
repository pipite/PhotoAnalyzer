//---------------------------------------------------------------------------

#pragma hdrstop

#include "ClassLgs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// -----------------------------------------------------
// CLASS TLgKey
// -----------------------------------------------------
TLgKey::TLgKey(UnicodeString key) {
	Key = key;
	Traduct = new TStringList;
}
TLgKey::~TLgKey(void) {
	delete Traduct;
}

#pragma region TLgs

// -----------------------------------------------------
// CLASS TLgs
// -----------------------------------------------------
__fastcall TLgs::TLgs(void) {
	PActiveLang = L"English";
	PIdxLang = 0;
	Lang = new TStringList;
}

__fastcall TLgs::~TLgs(void) {
	Clear();
	delete Lang;
}

unsigned __fastcall TLgs::GetCountLang(void) {
	return (unsigned) Lang->Count;
}

unsigned __fastcall TLgs::GetCountLgKey(void) {
	return LgKey.size();
}

void __fastcall TLgs::Clear(void) {
	unsigned i;

	for (i = 0; i < LgKey.size(); i++) {
		delete LgKey.at(i);
	}
	LgKey.empty();
	Lang->Clear();
}

TLgKey* __fastcall TLgs::GetLgKey(unsigned idx) {
	return LgKey.at(idx);
}

void __fastcall TLgs::AddLang(UnicodeString lang) {
	Lang->Add(lang);
}

TLgKey* __fastcall TLgs::FindOrAddKey(UnicodeString key) {
	for ( unsigned i = 0; i < CountLgKey; i++ ) {
		if ( GetLgKey(i)->Key == key ) {
			return GetLgKey(i);
		}
	}
	LgKey.push_back(new TLgKey(key));
	return LgKey.at(LgKey.size() - 1);
}

void __fastcall TLgs::SetActiveLang(UnicodeString lang) {
	for ( unsigned i = 0; i < CountLang; i++ ) {
		if ( Lang->Strings[i] == lang ) {
			PIdxLang = i;
			PActiveLang = lang;
			break;
		}
	}
}

UnicodeString __fastcall TLgs::QueryKey(UnicodeString key) {
	for ( unsigned i = 0; i < CountLgKey; i++ ) {
		if ( GetLgKey(i)->Key == key ) {
			return GetLgKey(i)->Traduct->Strings[PIdxLang];
		}
	}
	return "Undef";
}

void __fastcall TLgs::LoadXML(UnicodeString filename) {
	const _di_IXMLDocument xml = interface_cast<Xmlintf::IXMLDocument> (new TXMLDocument(NULL));
	TLgKey *lgk;

	xml->LoadFromFile(filename);
	const _di_IXMLNode nRoot = xml->ChildNodes->FindNode("Lang");

	for (int i = 0; i < nRoot->ChildNodes->Count ; i++) {
		const _di_IXMLNode nLang = nRoot->ChildNodes->Get(i);
		AddLang(nLang->NodeName);
		for (int j = 0; j < nLang->ChildNodes->Count ; j++) {
			const _di_IXMLNode nClass = nLang->ChildNodes->Get(j);
			for (int k = 0; k < nClass->AttributeNodes->Count ; k++) {
				const _di_IXMLNode nNode = nClass->AttributeNodes->Get(k);
				lgk = FindOrAddKey(nClass->NodeName + "." + nNode->NodeName);
				lgk->Traduct->Add(nNode->NodeValue);
			}
        }
	}
}

#pragma end_region
