#ifndef CLASSIMAGEFILTERH
#define CLASSIMAGEFILTERH

struct SFilterData {
	double Dev1, Dev2, Ev1, Ev2, Tol, Fc1, Fc2, Ff1, Ff2, Et1, Et2, B1, B2, Dof1, Dof2;
};

enum EFlash {
	flNone, flNo, flDidNotFire, flAll, flOutOfRange
};

enum class EExposure {
	flNone, flDeltaEv
};

enum class ELightning {
	flNone, lNone, flEv
};

enum class EFocale {
	flNone, flFocaleBetween, flFocaleFixe
};

enum class EExposureTime {
	flNone, flTripod, flStill, flMove
};

enum class ELensIs {
	flYes, flNo
};

enum class EBorder {
	flNone, flBorder
};

enum class EDepthOfField {
	flNone, flDepthOfField
};

enum class ERotate {
	flNone, flPortrait, flLandscape
};

#include "ClassScandisk.h"

// -----------------------------------------------------
// CLASS TImageFilter
// -----------------------------------------------------
class TImageFilter {
	TThumbPanel *tp;

	bool __fastcall Model(void);
	bool __fastcall Lens(void);
	bool __fastcall Flash(void);
	bool __fastcall Exposure(void);
	bool __fastcall Lightning(void);
	bool __fastcall Focale(void);
	bool __fastcall ExposureTime(void);
	bool __fastcall Border(void);
	bool __fastcall DepthOfField(void);
	bool __fastcall Orientation(void);

public:
	SFilterData   FilterData;
	EFlash        VFlash;
	EExposure     VExposure;
	ELightning    VLightning;
	EFocale       VFocale;
	EExposureTime VExposureTime;
	ELensIs       VLensIs;
	EBorder       VBorder;
	EDepthOfField VDepthOfField;
	ERotate       VRotate;

	TImageFilter(void);
	~TImageFilter(void);

	void __fastcall ApplyToGroup(TGroupPanel *grouppanel);
	void __fastcall ApplyToThumb(TThumbPanel *thumbpanel);
};

#endif
