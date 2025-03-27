#ifndef CLASSIMAGEFILTER
#define CLASSIMAGEFILTER

#include "ClassImageFilter.h"

// -----------------------------------------------------
// CLASS TGroupFilter
// -----------------------------------------------------
TImageFilter::TImageFilter(void) {
	VFlash = EFlash::flNone;
	VExposure = EExposure::flNone;
	VLightning = ELightning::flNone;
	VFocale = EFocale::flNone;
	VExposureTime = EExposureTime::flNone;
	VLensIs = ELensIs::flNo;
	VBorder = EBorder::flNone;
	VDepthOfField = EDepthOfField::flNone;
	VRotate = ERotate::flNone;
}

TImageFilter::~TImageFilter(void) {
}

bool __fastcall TImageFilter::Model(void) {
//	unsigned i;
//	TCheckBox *cb;

	// filtre sur les modèles
	// for (i = 0; i < (unsigned) GBModel->ChildrenCount; i++) {
	// if (GBModel->Children[i]->ClassNameIs(L"TCheckBox")) {
	// cb = (TCheckBox*)GBModel->Children[i];
	// if (tp->Photo->Analys->MapCamera != NULL)
	// if (tp->Photo->Analys->MapCamera->MakerModelCaption == cb->Text)
	// return cb->IsChecked;
	// }
	// }
	return true;
}

bool __fastcall TImageFilter::Lens(void) {
//	unsigned i;
//	TCheckBox *cb;

	// filtre sur les objectifs
	// for (i = 0; i < (unsigned) GBLens->ChildrenCount; i++) {
	// if (GBLens->Children[i]->ClassNameIs(L"TCheckBox")) {
	// cb = (TCheckBox*)GBLens->Children[i];
	// if (tp->Photo->Analys->Lens->Caption == cb->Text) {
	// return cb->IsChecked;
	// }
	// }
	// }
	return true;
}

bool __fastcall TImageFilter::Flash(void) {
	double vb;

	if (VFlash == EFlash::flNone) {
		return true;
	}
	else if (VFlash == EFlash::flNo) {
		return !tp->Photo->Analys->Flash->Fired->IsFired;
	}
	else if (VFlash == EFlash::flAll) {
		return tp->Photo->Analys->Flash->Fired->IsFired;
	}
	else if (VFlash == EFlash::flDidNotFire) {
		return tp->Photo->Analys->Flash->DidNotFire->IsNotFired;
	}
	else if (VFlash == EFlash::flOutOfRange) {
		if (tp->Photo->Analys->Flash->Fired->IsFired && !tp->Photo->Analys->Flash->DidNotFire->IsNotFired) {
			vb = tp->Photo->Analys->Flash->Bias->Tag->Value;
			tp->Photo->Analys->Flash->Bias->Tag->Value = 0.0;
			if (tp->Photo->Analys->FocusDistance->SubjectDistance->Value > tp->Photo->Analys->Flash->Limit->Distance->Value + FilterData.Tol) {
				tp->Photo->Analys->Flash->Bias->Tag->Value = vb;
				return true;
			}
		}
		tp->Photo->Analys->Flash->Bias->Tag->Value = vb;
		return false;
	}
	return true;
}

bool __fastcall TImageFilter::Exposure(void) {
	if (VExposure == EExposure::flNone)
		return true;
	else if (VExposure == EExposure::flDeltaEv) {
		if ((tp->Photo->Analys->Exposure->Relative->Value > FilterData.Dev1) && (tp->Photo->Analys->Exposure->Relative->Value <= FilterData.Dev2))
			return true;
		else
			return false;
	}
	return true;
}

bool __fastcall TImageFilter::Lightning(void) {
	if (VLightning == ELightning::flNone)
		return true;
	else if (VLightning == ELightning::flEv) {
		if ((tp->Photo->Analys->Exposure->Value > FilterData.Ev1) && (tp->Photo->Analys->Exposure->Value <= FilterData.Ev2))
			return true;
		else
			return false;
	}
	return true;
}

bool __fastcall TImageFilter::Focale(void) {
	if (VFocale == EFocale::flNone)
		return true;
	else if (VFocale == EFocale::flFocaleBetween) {
		if ((tp->Photo->Analys->Focale->In24x36->Value > FilterData.Fc1) && (tp->Photo->Analys->Focale->In24x36->Value <= FilterData.Fc2))
			return true;
		else
			return false;
	}
	else if (VFocale == EFocale::flFocaleFixe) {
		if ((tp->Photo->Analys->Focale->In24x36->Value > FilterData.Ff1 - FilterData.Ff2) && (tp->Photo->Analys->Focale->In24x36->Value <= FilterData.Ff1 + FilterData.Ff2))
			return true;
		else
			return false;
	}
	return true;
}

bool __fastcall TImageFilter::ExposureTime(void) {
	if (VExposureTime == EExposureTime::flNone)
		return true;
	else if (VExposureTime == EExposureTime::flTripod) {
		if (tp->Photo->Analys->Apex->Apex2ExposureTime(tp->Photo->Analys->Apex->ExposureTime2Apex(tp->Photo->Analys->ExposureTime->Value) + FilterData.Et1) > (1.0 / tp->Photo->Analys->Focale->In24x36->Value))
			return true;
		else
			return false;
	}
	else if (VExposureTime == EExposureTime::flStill) {
		if (tp->Photo->Analys->Apex->Apex2ExposureTime(tp->Photo->Analys->Apex->ExposureTime2Apex(tp->Photo->Analys->ExposureTime->Value) + FilterData.Et1) <= (1.0 / tp->Photo->Analys->Focale->In24x36->Value))
			return true;
		else
			return false;
	}
	else if (VExposureTime == EExposureTime::flMove) {
		if ((tp->Photo->Analys->SubjectSpeedLimit->Value >= FilterData.Et2) && (tp->Photo->Analys->Apex->Apex2ExposureTime(tp->Photo->Analys->Apex->ExposureTime2Apex(tp->Photo->Analys->ExposureTime->Value) + FilterData.Et1) <=
			(1.0 / tp->Photo->Analys->Focale->In24x36->Value)))
			return true;
		else
			return false;
	}
	return true;
}

bool __fastcall TImageFilter::Border(void) {
	if (VBorder == EBorder::flNone)
		return true;
	else if (VBorder == EBorder::flBorder) {
		if (FilterData.B2 == 100.0) {
			if (tp->Photo->Analys->Focale->Border->Value > FilterData.B1)
				return true;
			else
				return false;
		}
		else {
			if ((tp->Photo->Analys->Focale->Border->Value > FilterData.B1) && (tp->Photo->Analys->Focale->Border->Value <= FilterData.B2))
				return true;
			else
				return false;
		}
	}
	return true;
}

bool __fastcall TImageFilter::DepthOfField(void) {
	if (VDepthOfField == EDepthOfField::flNone)
		return true;
	else if (VDepthOfField == EDepthOfField::flDepthOfField) {
		if (FilterData.Dof2 == 15.0) {
			if (tp->Photo->Analys->FocusDistance->DepthOfField->Value > FilterData.Dof1)
				return true;
			else
				return false;
		}
		else {
			if ((tp->Photo->Analys->FocusDistance->DepthOfField->Value > FilterData.Dof1) && (tp->Photo->Analys->FocusDistance->DepthOfField->Value <= FilterData.Dof2))
				return true;
			else
				return false;
		}
	}
	return true;
}

bool __fastcall TImageFilter::Orientation(void) {
	if (tp->Photo->Analys->Rotate->Value == ERotate::flPortrait)
		return true;
	else
		return false;
//	o = tp->Photo->Analys->Rotate->Value;
//	if ( (VRotate == ERotate::flNone) || (o == 0) )
//		return true;
//	else if (VRotate == ERotate::flPortrait) {
//		if ( (o == 1) || (o == 2) ||(o == 3) || (o == 4) || (o == 5) || (o == 7) )
//			return true;
//		else
//			return false;
//	} else if (VRotate == ERotate::flLandscape) {
//		if ( (o == 6) || (o == 8) )
//			return true;
//		else
//			return false;
//	}
//	return true;
}

void __fastcall TImageFilter::ApplyToGroup(TGroupPanel *grouppanel) {
	unsigned i;

	for (i = 0; i < (unsigned) grouppanel->GridLayout->ChildrenCount; i++) {
		tp = (TThumbPanel*) grouppanel->GridLayout->Children->Items[i];
		if (Model() && Lens() && Flash() && Exposure() && Lightning() && Focale() && ExposureTime() && Border() && DepthOfField() && Orientation()) {
			tp->Opacity = float(1.0);
			tp->Selected = true;
		}
		else {
			tp->Opacity = float(0.2);
			tp->Selected = false;
		}
	}
}

void __fastcall TImageFilter::ApplyToThumb(TThumbPanel *thumbpanel) {
	tp = thumbpanel;
	if (Model() && Lens() && Flash() && Exposure() && Lightning() && Focale() && ExposureTime() && Border() && DepthOfField()) {
		tp->Opacity = float(1.0);
		tp->Selected = true;
	}
	else {
		tp->Opacity = float(0.2);
		tp->Selected = false;
	}
}

#endif
