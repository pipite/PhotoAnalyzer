#ifndef CLASSDIAGNOSTICH
#define CLASSDIAGNOSTICH

#include <FMX.TreeView.hpp>

class DDiagnostic;
class DExposure;
class DSettings;
class DExposureTime;
class DAperture;
class DIso;
class DFocale;
class DFlashUse;
class DSubjectMove;
class DBlur;
class DFlashImpact;

#include "ClassAnalys.h"
#include "UtilCommon.h"

// -----------------------------------------------------
// CLASS DDiagnostic
// -----------------------------------------------------
class DDiagnostic {
public:
	TAnalys* Analys;
	TTreeView* Tv;
	DSettings* Settings;
	DExposure* Exposure;
	DExposureTime* ExposureTime;
	DAperture* Aperture;
	DIso* Iso;
	DFocale* Focale;
	DFlashUse* FlashUse;
	DSubjectMove* SubjectMove;
	DBlur* Blur;
	DFlashImpact* FlashImpact;


	DDiagnostic(TAnalys *analys);
	~DDiagnostic(void);

	void __fastcall Compute(TTreeView* tv);
	TTreeViewItem* __fastcall AddRoot(UnicodeString s);
	TTreeViewItem* __fastcall AddChild(TTreeViewItem* tvi, UnicodeString s);
	void __fastcall SetCalcAnalys(TAnalys *OAnalys, TAnalys *analys, double e, double a, double i, double ev);
	void __fastcall RecurseCalc(TTreeViewItem * item, TAnalys *analys, bool cV, bool cA, bool cI);
};

// -----------------------------------------------------
// CLASS DSettings
// -----------------------------------------------------
class DSettings {
	DDiagnostic* Diag;

public:
	DSettings(DDiagnostic *diag);
	~DSettings(void);

	void __fastcall Diagnostic(void);
};

// -----------------------------------------------------
// CLASS DSubjectMove
// -----------------------------------------------------
class DSubjectMove {
	DDiagnostic* Diag;

	double __fastcall GetValue(double v, double d);
	UnicodeString __fastcall GetCaption(double v, double d);
	UnicodeString __fastcall Row(double d);

public:

	DSubjectMove(DDiagnostic *diag);
	~DSubjectMove(void);

	void __fastcall SpreadSheet(TTreeViewItem *Item0);
};

// -----------------------------------------------------
// CLASS DFlashImpact
// -----------------------------------------------------
class DFlashImpact {
	DDiagnostic* Diag;
public:

	DFlashImpact(DDiagnostic *diag);
	~DFlashImpact(void);

	void __fastcall Compute(TTreeViewItem *Item0);
};

// -----------------------------------------------------
// CLASS DBlur
// -----------------------------------------------------
class DBlur {
	DDiagnostic* Diag;
public:

	DBlur(DDiagnostic *diag);
	~DBlur(void);

	void __fastcall Compute(TTreeViewItem *Item0, double exposuretime);
};

// -----------------------------------------------------
// CLASS DExposureTime
// -----------------------------------------------------
class DExposureTime {
	DDiagnostic* Diag;
public:

	DExposureTime(DDiagnostic *diag);
	~DExposureTime(void);

	void __fastcall Diagnostic(TTreeViewItem * Item0, TAnalys *analys, double exposuretime);
};

// -----------------------------------------------------
// CLASS DDepthOfField
// -----------------------------------------------------
class DDepthOfField {
	DDiagnostic* Diag;

public:
	DDepthOfField(DDiagnostic *diag);
	~DDepthOfField(void);

	void __fastcall Diagnostic(TTreeViewItem * Item0, TAnalys *analys, double aperture);
};

// -----------------------------------------------------
// CLASS DAperture
// -----------------------------------------------------
class DAperture {
	DDiagnostic* Diag;

public:
	DAperture(DDiagnostic *diag);
	~DAperture(void);

	void __fastcall Diagnostic(TTreeViewItem * Item0, TAnalys *analys, double aperture);
};

// -----------------------------------------------------
// CLASS DIso
// -----------------------------------------------------
class DIso {
	DDiagnostic* Diag;

public:
	DIso(DDiagnostic *diag);
	~DIso(void);

	void __fastcall Diagnostic(TTreeViewItem * Item0, TAnalys *analys, double iso);
};

// -----------------------------------------------------
// CLASS DFocale
// -----------------------------------------------------
class DFocale {
	DDiagnostic* Diag;

public:
	DFocale(DDiagnostic *diag);
	~DFocale(void);

	void __fastcall Diagnostic(TTreeViewItem * Item0, TAnalys *analys, double focale);
};

// -----------------------------------------------------
// CLASS DFlashUse
// -----------------------------------------------------
class DFlashUse {
	DDiagnostic* Diag;

public:
	DFlashUse(DDiagnostic *diag);
	~DFlashUse(void);

	void __fastcall Diagnostic(TTreeViewItem* Item0, TAnalys *analys);
};

// -----------------------------------------------------
// CLASS DExposure
// -----------------------------------------------------
class DExposure {
	DDiagnostic* Diag;

public:
	DExposure(DDiagnostic *diag);
	~DExposure(void);

	void __fastcall Diagnostic(void);
};

#endif
