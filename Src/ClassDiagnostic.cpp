#ifndef CLASSDIAGNOSTIC
#define CLASSDIAGNOSTIC

#include "ClassDiagnostic.h"

#pragma region DDiagnostic

// -----------------------------------------------------
// CLASS DDiagnostic
// -----------------------------------------------------
DDiagnostic::DDiagnostic(TAnalys *analys) {
	Tv           = NULL;
	Analys       = analys;
	Settings     = new DSettings(this);
	Exposure     = new DExposure(this);
	ExposureTime = new DExposureTime(this);
	Aperture     = new DAperture(this);
	Iso          = new DIso(this);
	Focale       = new DFocale(this);
	FlashUse     = new DFlashUse(this);
	SubjectMove  = new DSubjectMove(this);
	Blur         = new DBlur(this);
	FlashImpact  = new DFlashImpact(this);
}

DDiagnostic::~DDiagnostic(void) {
	delete Exposure;
	delete Settings;
	delete ExposureTime;
	delete Aperture;
	delete Iso;
	delete Focale;
	delete FlashUse;
	delete SubjectMove;
	delete Blur;
	delete FlashImpact;
}

void __fastcall DDiagnostic::Compute(TTreeView* tv) {
	Tv = tv;
	tv->Clear();
	Settings->Diagnostic();
	Exposure->Diagnostic();
	tv->ExpandAll();
}

TTreeViewItem* __fastcall DDiagnostic::AddRoot(UnicodeString s) {
	TTreeViewItem* Item;
	Item = new TTreeViewItem(Tv);
	Item->Font->Family = L"Courier new";
	Item->Text = s;
	Item->Parent = Tv;
	return Item;
}

TTreeViewItem* __fastcall DDiagnostic::AddChild(TTreeViewItem* tvi, UnicodeString s) {
	TTreeViewItem* Item;
	Item = new TTreeViewItem(tvi);
	Item->Font->Family = L"Courier new";
	Item->Text = s;
	Item->Parent = tvi;
	return Item;
}

void __fastcall DDiagnostic::SetCalcAnalys(TAnalys *OAnalys, TAnalys *analys, double e, double a, double i, double ev) {
	analys->MapCamera                           = OAnalys->MapCamera;
	analys->Lens->Caption                       = OAnalys->Lens->Caption;
	analys->Lens->LensData                      = OAnalys->Lens->LensData;
	analys->Aperture->Value                     = a;
	analys->ExposureTime->Value                 = e;
	analys->Focale->Value                       = OAnalys->Focale->Value;
	analys->Iso->Value                          = i;
	analys->FocusDistance->Upper->OriginalValue = OAnalys->FocusDistance->Upper->OriginalValue;
	analys->FocusDistance->Lower->Value         = OAnalys->FocusDistance->Lower->Value;
	analys->Exposure->Value                     = OAnalys->Exposure->Value - ev;
	analys->Flash->Fired->Tag->Value            = OAnalys->Flash->Fired->Tag->Value;
	analys->Flash->Required->Tag->Value         = OAnalys->Flash->Required->Tag->Value;
	analys->Flash->ValueBuiltIn                 = OAnalys->Flash->ValueBuiltIn;
	analys->Flash->ValueExternal                = OAnalys->Flash->ValueExternal;
	analys->Compute();
}

void __fastcall DDiagnostic::RecurseCalc(TTreeViewItem * item, TAnalys *analys, bool cV, bool cA, bool cI) {
	TTreeViewItem *Item1, *Item2, *Item3;
	UnicodeString s;
	TAnalys *CalcAnalys;

	Item1 = item;
	if (cV) {
		// "Vitesse optimale pour (%s, %s) = %s"
		s = Uprintf(Analys->Lgs->QueryKey(L"DIAG.ExposureOptimSpeed").w_str(), analys->Aperture->Caption.w_str(), analys->Iso->Caption.w_str(), analys->ExposureTime->Best->Caption.w_str());
		Item2 = AddChild(Item1, s);
		ExposureTime->Diagnostic(Item2, analys, analys->ExposureTime->Best->Value);

		if (!analys->ExposureTime->Limit->IsInRange) {
			// "Votre appareil n'est pas capable d'atteindre %s. Sa limite est: %s"
			s = Uprintf(Analys->Lgs->QueryKey(L"DIAG.OutOfCameraRange").w_str(), analys->ExposureTime->Best->Caption.w_str(), analys->ExposureTime->Limit->Caption.w_str());
			Item3 = AddChild(Item2, s);
			cV = false;
			if (cA || cI) {
				if (analys->ExposureTime->Limit->Caption != analys->ExposureTime->Caption) {
					CalcAnalys = new TAnalys(Analys->Lgs);
					SetCalcAnalys(analys, CalcAnalys, analys->ExposureTime->Limit->Value, analys->Aperture->Value, analys->Iso->Value, 0.0);
					RecurseCalc(Item3, CalcAnalys, false, cA, cI);
					delete CalcAnalys;
				}
			}
		}
	}
	if (cA) {
		// "Ouverture optimale pour (%s, %s) = %s"
		s = Uprintf(Analys->Lgs->QueryKey(L"DIAG.ExposureOptimAperture").w_str(), analys->ExposureTime->Caption.w_str(), analys->Iso->Caption.w_str(), analys->Aperture->Best->Caption.w_str());
		Item2 = AddChild(Item1, s);
		if (!analys->Aperture->Limit->IsInRange) {
			// "Votre objectif n'est pas capable d'atteindre %s. Sa limite est: %s"
			s = Uprintf(Analys->Lgs->QueryKey(L"DIAG.OutOfLensRange").w_str(), analys->Aperture->Best->Caption.w_str(), analys->Aperture->Limit->Caption.w_str());
			Item3 = AddChild(Item2, s);
			cA = false;
			if (cV || cI) {
				if (analys->Aperture->Limit->Caption != analys->Aperture->Caption) {
					CalcAnalys = new TAnalys(Analys->Lgs);
					SetCalcAnalys(analys, CalcAnalys, analys->ExposureTime->Value, analys->Aperture->Limit->Value, analys->Iso->Value, 0.0);
					RecurseCalc(Item3, CalcAnalys, cV, false, cI);
					delete CalcAnalys;
				}
			}
		}
		else {
			Aperture->Diagnostic(Item2, analys, analys->Aperture->Best->Value);
			// "Evaluation de la qualité de l'objectif pour %s et %s: %.1f / 10"
//			s = Uprintf(lgs->QueryKey(L"DIAG.LensQuality").w_str(), analys->Lens->Caption, analys->Focale->Caption, analys->Aperture->Best->Caption, 10.0 * analys->Lens->QueryIndice(analys->Focale->Value, analys->Aperture->Best->Value));
//			Item3 = AddChild(Item2, s);
		}
	}
	if (cI) {
		// "Iso optimal pour (%s, %s) = %s"
		s = Uprintf(Analys->Lgs->QueryKey(L"DIAG.ExposureOptimIso").w_str(), analys->ExposureTime->Caption.w_str(), analys->Aperture->Caption.w_str(), analys->Iso->Best->Caption.w_str());
		Item2 = AddChild(Item1, s);
		if (!analys->Iso->Limit->IsInRange) {
			// "Votre appareil n'est pas capable d'atteindre %s. Sa limite est: %s"
			s = Uprintf(Analys->Lgs->QueryKey(L"DIAG.OutOfCameraRange").w_str(), analys->Iso->Best->Caption.w_str(), analys->Iso->Limit->Caption.w_str());
			Item3 = AddChild(Item2, s);
			cI = false;
			if (cV || cA) {
				if (analys->Iso->Limit->Caption != analys->Iso->Caption) {
					CalcAnalys = new TAnalys(Analys->Lgs);
					SetCalcAnalys(analys, CalcAnalys, analys->ExposureTime->Value, analys->Aperture->Value, analys->Iso->Limit->Value, analys->Iso->ExposureCompens->DeltaLimitBest->Value);
					RecurseCalc(Item3, CalcAnalys, cV, cA, false);
					delete CalcAnalys;
				}
			}
		}
	}
}

#pragma end_region

#pragma region DSettings

// -----------------------------------------------------
// CLASS DSettings
// -----------------------------------------------------

DSettings::DSettings(DDiagnostic *diag) {
	Diag = diag;
}

DSettings::~DSettings(void) {

}

void __fastcall DSettings::Diagnostic(void) {
	TTreeViewItem *Item0, *Item1, *Item2, *Item3;
	double aperture;
	UnicodeString s;
	TAnalys *CalcAnalys;

	s = Uprintf(L"Angle = %.2f, Diagonale = %.2f",Diag->Analys->Focale->Angle->Value,Diag->Analys->Focale->Border->Value);
	Item0 = Diag->AddRoot(s);

	// "Réglage du %s - %s"
	s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.Settings").w_str(), Diag->Analys->MapCamera->MakerCaption.w_str(), Diag->Analys->MapCamera->Caption.w_str());
	Item0 = Diag->AddRoot(s);

	// "Vitesse réglé à %s"
	s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.ExposureTime").w_str(), Diag->Analys->ExposureTime->Caption.w_str());
	Item1 = Diag->AddChild(Item0, s);
	Diag->ExposureTime->Diagnostic(Item1, Diag->Analys, Diag->Analys->ExposureTime->Value);

	// "Ouverture réglé à %s"
	s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.Aperture").w_str(), Diag->Analys->Aperture->Caption.w_str());
	Item1 = Diag->AddChild(Item0, s);
	Diag->Aperture->Diagnostic(Item1, Diag->Analys, Diag->Analys->Aperture->Value);

	// "Iso réglé à %s"
	s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.Iso").w_str(), Diag->Analys->Iso->Caption.w_str());
	Item1 = Diag->AddChild(Item0, s);
	//Iso = new DIso(Lgs);
	Diag->Iso->Diagnostic(Item1, Diag->Analys, Diag->Analys->Iso->Value);
	//delete Iso;

	// "Focale réglé à %s (en 24x36 = %s)"
	s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.Focale").w_str(), Diag->Analys->Focale->Caption.w_str(), Diag->Analys->Focale->In24x36->Caption.w_str());
	Item1 = Diag->AddChild(Item0, s);
	Diag->Focale->Diagnostic(Item1, Diag->Analys, Diag->Analys->Focale->Value);

	if (Diag->Analys->FocusDistance->SubjectDistance->IsValid) {
		// "Distance du sujet: %s"
		s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.SubjectDistance").w_str(), Diag->Analys->FocusDistance->SubjectDistance->Caption.w_str());
		Diag->AddChild(Item0, s);
	}
	else {
		// "Distance du sujet non disponible"
		Diag->AddChild(Item0, Diag->Analys->Lgs->QueryKey(L"DIAG.NoSubjectDistance"));
	}

	// "Le flash %sa été utilisé"
	Diag->FlashUse->Diagnostic(Item0, Diag->Analys);

	// "Objectif: %s"
	s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.Lens").w_str(), Diag->Analys->Lens->Caption.w_str());
	Item1 = Diag->AddChild(Item0, s);

	if (Diag->Analys->Lens->IsData) {
		// "Indice de qualité (%s, %s) = %.1f/10"
		s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.LensQuality").w_str(), Diag->Analys->Focale->Caption.w_str(), Diag->Analys->Aperture->Caption.w_str(), 10.0 * Diag->Analys->Lens->QueryIndice(Diag->Analys->Focale->Value, Diag->Analys->Aperture->Value));
		Item2 = Diag->AddChild(Item1, s);

		aperture = Diag->Analys->Lens->QueryBestAperture(Diag->Analys->Focale->Value);
		if (aperture != Diag->Analys->Aperture->Value) {
			// "Indice max de qualité (%s, %s) =  %.1f/10"
			s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.LensQualityBestFocale").w_str(), Diag->Analys->Focale->Caption.w_str(), ApertureFormat(aperture).w_str(), 10.0 * Diag->Analys->Lens->QueryIndice(Diag->Analys->Focale->Value, aperture));
			Item3 = Diag->AddChild(Item2, s);
			CalcAnalys = new TAnalys(Diag->Analys->Lgs);
			Diag->SetCalcAnalys(Diag->Analys, CalcAnalys, Diag->Analys->ExposureTime->Limit->Value, aperture, Diag->Analys->Iso->Value, 0.0);
			Diag->RecurseCalc(Item3, CalcAnalys, true, false, true);
			delete CalcAnalys;
		}
	}
}

#pragma end_region

#pragma region DExposureTime

#pragma region DFlashImpact

// -----------------------------------------------------
// CLASS DFlashImpact
// -----------------------------------------------------
DFlashImpact::DFlashImpact(DDiagnostic *diag) {
	Diag = diag;
}

DFlashImpact::~DFlashImpact(void) {
}

void __fastcall DFlashImpact::Compute(TTreeViewItem *Item0) {
	UnicodeString s;

	s = L"";
	if (Diag->Analys->Flash->ExposureCompens->Value >= Diag->Analys->MapCamera->FlashFillInLight) {
		if (Diag->Analys->Flash->Range->IsOkWithoutBias) {
			// "Vitesse à considérer = %s (durée de l'éclair du flash)"
			s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashExposureTime").w_str(), ExposureTimeFormat(Diag->Analys->Flash->Duration->Value).w_str());
			Diag->AddChild(Item0, s);
			// diagnostic du flou
			Diag->Blur->Compute(Item0, Diag->Analys->Flash->Duration->Value);
		}
	}
	else {
		Diag->Blur->Compute(Item0, Diag->Analys->ExposureTime->Value);
	}
}

#pragma end_region

#pragma region DSubjectMove

// -----------------------------------------------------
// CLASS DSubjectMove
// -----------------------------------------------------
DSubjectMove::DSubjectMove(DDiagnostic *diag) {
	Diag = diag;
}

DSubjectMove::~DSubjectMove(void) {
}

double __fastcall DSubjectMove::GetValue(double v, double d) {
	double size, t;

	size = Diag->Analys->Sensor->PixelSize->Value / 10.0;
	if (v > 0.0) {
		t = d * (35.0 * 35.0 / Diag->Analys->Focale->In24x36->Value) * size / ((v * 1000.0) / 3600.0);
		return t;
	}
	return 0.0;
}

UnicodeString __fastcall DSubjectMove::GetCaption(double v, double d) {
	return ExposureTimeFormat(GetValue(v, d));
}

UnicodeString __fastcall DSubjectMove::Row(double d) {
	UnicodeString s;

	s = Uprintf(L"|%3.0fm |", d);
	s += Uprintf(L"%8s |", GetCaption(3.0, d).w_str());
	s += Uprintf(L"%8s |", GetCaption(6.0, d).w_str());
	s += Uprintf(L"%8s |", GetCaption(8.0, d).w_str());
	s += Uprintf(L"%8s |", GetCaption(16.0, d).w_str());
	s += Uprintf(L"%8s |", GetCaption(40.0, d).w_str());
	s += Uprintf(L"%8s |", GetCaption(80.0, d).w_str());
	s += Uprintf(L"%8s |", GetCaption(120.0, d).w_str());
	s += Uprintf(L"%8s |", GetCaption(200.0, d).w_str());

	return s;

}

void __fastcall DSubjectMove::SpreadSheet(TTreeViewItem *Item0) {
	Diag->AddChild(Item0, L"+-----+---------+---------+---------+---------+---------+---------+---------+---------+");
	Diag->AddChild(Item0, L"| d/v | 3 k/h   | 6 k/h   | 8 k/h   | 16 k/h  | 40 k/h  | 80 k/h  | 120 k/h | 200 k/h |");
	Diag->AddChild(Item0, L"+-----+---------+---------+---------+---------+---------+---------+---------+---------+");
	Diag->AddChild(Item0, Row(2.0));
	Diag->AddChild(Item0, Row(4.0));
	Diag->AddChild(Item0, Row(8.0));
	Diag->AddChild(Item0, Row(15.0));
	Diag->AddChild(Item0, Row(30.0));
	Diag->AddChild(Item0, Row(50.0));
	Diag->AddChild(Item0, Row(80.0));
	Diag->AddChild(Item0, L"+-----+---------+---------+---------+---------+---------+---------+---------+---------+");
}

#pragma end_region

#pragma region DBlur

// -----------------------------------------------------
// CLASS DBlur
// -----------------------------------------------------
DBlur::DBlur(DDiagnostic *diag) {
	Diag = diag;
}

DBlur::~DBlur(void) {
}

void __fastcall DBlur::Compute(TTreeViewItem *Item0, double exposuretime) {
	TTreeViewItem *Item1, *Item2;
	UnicodeString s;

	// "Sujet fixe"
	Item1 = Diag->AddChild(Item0, Diag->Analys->Lgs->QueryKey(L"DIAG.StillSubject"));
	if (exposuretime < (1.0 / Diag->Analys->Focale->In24x36->Value)) {
		// "%s est correct pour eviter le flou de bouger avec un %s. (limite: %s)"
		s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.NoBlur").w_str(), ExposureTimeFormat(exposuretime).w_str(), Diag->Analys->Lgs->QueryKey(L"DIAG.NoStab").w_str(), ExposureTimeFormat(1.0 / Diag->Analys->Focale->In24x36->Value).w_str());
		Diag->AddChild(Item1, s);
	}
	else {
		// "%s risque de produire un flou de bouger avec un %s. (Limite: %s)"
		s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.Blur").w_str(), ExposureTimeFormat(exposuretime).w_str(), Diag->Analys->Lgs->QueryKey(L"DIAG.NoStab").w_str(), ExposureTimeFormat(1.0 / Diag->Analys->Focale->In24x36->Value).w_str());
		Item2 = Diag->AddChild(Item1, s);
		// "Utilisation d'un trepied conseillé"
		Diag->AddChild(Item2, Diag->Analys->Lgs->QueryKey(L"DIAG.UseTripod"));

		if (exposuretime < (1.0 / Diag->Analys->Focale->In24x36->Value + Diag->Analys->Apex->Apex2ExposureTime(2.5))) {
			// "%s est correct pour eviter le flou de bouger avec un %s. (limite: %s)"
			s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.NoBlur").w_str(), ExposureTimeFormat(exposuretime).w_str(), Diag->Analys->Lgs->QueryKey(L"DIAG.Stab").w_str(), ExposureTimeFormat(Diag->Analys->Apex->Apex2ExposureTime(Diag->Analys->Apex->ExposureTime2Apex(1.0 / Diag->Analys->Focale->In24x36->Value) - 2.5)).w_str());
			Diag->AddChild(Item1, s);
		}
		else {
			// "%s risque de produire un flou de bouger avec un %s. (Limite: %s)"
			s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.Blur").w_str(), ExposureTimeFormat(exposuretime).w_str(), Diag->Analys->Lgs->QueryKey(L"DIAG.Stab").w_str(), ExposureTimeFormat(Diag->Analys->Apex->Apex2ExposureTime(Diag->Analys->Apex->ExposureTime2Apex(1.0 / Diag->Analys->Focale->In24x36->Value) - 2.5)).w_str());
			Item2 = Diag->AddChild(Item1, s);

			// "Utilisation d'un trepied conseillé"
			Diag->AddChild(Item2, Diag->Analys->Lgs->QueryKey(L"DIAG.UseTripod"));
		}
	}

	// "Sujets en mouvement"
	Item1 = Diag->AddChild(Item0, Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.MoveSubject").w_str(), Diag->Analys->Focale->Caption.w_str()));
	// "+-------+---------+---------+---------+---------+---------+---------+---------+"
	// "|  d/v  | 3 k/h   | 6 k/h   | 8 k/h   | 16 k/h  | 40 k/h  | 80 k/h  | 120 k/h |"
	// "|-------+---------+---------+---------+---------+---------+---------+---------+"
	// "|  2m   | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 |"
	// "|  4m   | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 |"
	// "|  8m   | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 |"
	// "| 15m   | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 |"
	// "| 30m   | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 |"
	// "| 50m   | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 |"
	// "| 80m   | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 | 1/11111 |"
	// "+-------+---------+---------+---------+---------+---------+---------+---------+"
	Diag->SubjectMove->SpreadSheet(Item1);
}

#pragma end_region

#pragma region DExposureTime

// -----------------------------------------------------
// CLASS DExposureTime
// -----------------------------------------------------
DExposureTime::DExposureTime(DDiagnostic *diag) {
	Diag = diag;
}

DExposureTime::~DExposureTime(void) {
}

void __fastcall DExposureTime::Diagnostic(TTreeViewItem * Item0, TAnalys* analys, double exposuretime) {

	if (analys->Flash->Fired->IsFired) {
		// Flash impact
		Diag->FlashImpact->Compute(Item0);
	}
	else {
		// diagnostic du flou
		Diag->Blur->Compute(Item0, exposuretime);
	}
}

#pragma end_region

#pragma end_region

#pragma region DAperture

#pragma region DDepthOfField

// -----------------------------------------------------
// CLASS DDepthOfField
// -----------------------------------------------------
DDepthOfField::DDepthOfField(DDiagnostic *diag) {
	Diag = diag;
}

DDepthOfField::~DDepthOfField(void) {
}

void __fastcall DDepthOfField::Diagnostic(TTreeViewItem * Item0, TAnalys* analys, double aperture) {
	UnicodeString s;
	TAnalys *CalcAnalys;

	CalcAnalys = new TAnalys(Diag->Analys->Lgs);
	Diag->SetCalcAnalys(analys, CalcAnalys, analys->ExposureTime->Value, aperture, analys->Iso->Value, 0.0);

	if (analys->FocusDistance->SubjectDistance->IsValid) {
		// "Netteté: mini %s, maxi %s >> profondeur de champ = %s"
		s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.DepthOfField").w_str(), CalcAnalys->FocusDistance->Lower->Caption.w_str(),CalcAnalys->FocusDistance->Upper->Caption.w_str(), CalcAnalys->FocusDistance->DepthOfField->Caption.w_str());
		Diag->AddChild(Item0, s);
	}
	// "Hyperfocale: %s >> Netteté: mini %s, infini"
	s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.Hyperfocal").w_str(), CalcAnalys->Hyperfocale->Caption.w_str(), CalcAnalys->Hyperfocale->FocusDistance->Lower->Caption.w_str());
	Diag->AddChild(Item0, s);
	delete CalcAnalys;
}

#pragma end_region

#pragma region DAperture

// -----------------------------------------------------
// CLASS DAperture
// -----------------------------------------------------
DAperture::DAperture(DDiagnostic *diag) {
	Diag = diag;
}

DAperture::~DAperture(void) {
}

void __fastcall DAperture::Diagnostic(TTreeViewItem * Item0, TAnalys* analys, double aperture) {
	UnicodeString s;
	DDepthOfField *DepthOfField;

	DepthOfField = new DDepthOfField(Diag);
	DepthOfField->Diagnostic(Item0,analys,aperture);
	delete DepthOfField;
}

#pragma end_region

#pragma end_region

#pragma region DIso

// -----------------------------------------------------
// CLASS DIso
// -----------------------------------------------------
DIso::DIso(DDiagnostic *diag) {
	Diag = diag;
}

DIso::~DIso(void) {
}

void __fastcall DIso::Diagnostic(TTreeViewItem * Item0, TAnalys* analys, double iso) {
}

#pragma end_region

#pragma region DFocale

// -----------------------------------------------------
// CLASS DFocale
// -----------------------------------------------------
DFocale::DFocale(DDiagnostic *diag) {
	Diag = diag;
}

DFocale::~DFocale(void) {
}

void __fastcall DFocale::Diagnostic(TTreeViewItem * Item0, TAnalys* analys, double iso) {
}

#pragma end_region

#pragma region DFlash

// -----------------------------------------------------
// CLASS DFlashUse
// -----------------------------------------------------
DFlashUse::DFlashUse(DDiagnostic *diag) {
	Diag = diag;
}

DFlashUse::~DFlashUse(void) {
}

void __fastcall DFlashUse::Diagnostic(TTreeViewItem* tvi, TAnalys* analys) {
	TTreeViewItem *Item1;
	UnicodeString flashname, s;

	if (analys->Flash->IsValid) {
		flashname = L"";
		if (analys->Flash->External)
			// "externe"
				flashname = Diag->Analys->Lgs->QueryKey(L"DIAG.FlashExternal") + L" ";
		else
			// "intégré"
				flashname = Diag->Analys->Lgs->QueryKey(L"DIAG.FlashInternal") + L" ";

		if (analys->Flash->Fired->IsFired) {
			// "Flash %sutilisé"
			s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashFired").w_str(), flashname.w_str());
			Item1 = Diag->AddChild(tvi, s);
			if (analys->Flash->Bias->Value != 0.0) {
				// "Correction d'exposition du flash de %s"
				s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashExposureBias").w_str(), ExposureFormat(analys->Flash->Bias->Value, Diag->Analys->Lgs).w_str());
				Diag->AddChild(Item1, s);
			}
			if (analys->Flash->FlashData != NULL) {
				if (analys->ExposureTime->Value < analys->Flash->FlashData->HSync) {
					// "Synchro haute vitesse utilisé"
					s = Diag->Analys->Lgs->QueryKey(L"DIAG.FlashHightSync");
					Diag->AddChild(Item1, s);
				}
			}
			if (analys->FocusDistance->SubjectDistance->IsValid) {
				if ((analys->Flash->Range->IsOkWithoutBias) && analys->Exposure->Relative->Value > analys->MapCamera->FlashFillInLight) {
					// "Flash utilisé pour déboucher les ombres"
					s = Diag->Analys->Lgs->QueryKey(L"DIAG.FlashFillIn");
					Diag->AddChild(Item1, s);
					// "Portée maxi du flash = %s"
					s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashRangeMax").w_str(), FocusDistanceFormat(analys->Flash->Limit->Distance->Value, false).w_str());
					Diag->AddChild(Item1, s);
				}
				else if (!analys->Flash->Range->IsOkWithoutBias) {
					// "Portée du flash insufisante (portée maxi = %s)"
					s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashOutOfRange").w_str(), FocusDistanceFormat(analys->Flash->Limit->Distance->Value, false).w_str());
					Diag->AddChild(Item1, s);
				} else if (!analys->Flash->Range->IsOkWithoutBias) {
					// "A la limite de la Portée du flash (portée maxi = %s)"
					s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashLimit").w_str(), FocusDistanceFormat(analys->Flash->Limit->Distance->Value, false).w_str());
					Diag->AddChild(Item1, s);
				} else {
					// "Portée maxi du flash = %s"
					s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashRangeMax").w_str(), FocusDistanceFormat(analys->Flash->Limit->Distance->Value, false).w_str());
					Diag->AddChild(Item1, s);
				}
				if (analys->Flash->Range->IsOkWithoutBias) {
					// "Durée de l'éclair du flash = %s"
					s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashDuration").w_str(), ExposureTimeFormat(analys->Flash->Duration->Value).w_str());
					Diag->AddChild(Item1, s);
				}
				if (analys->Flash->Power->Value <= 1.0) {
					// "Flash utilisé a %s%% de sa puissance maxi"
					s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashPowerUsed").w_str(), analys->Flash->Power->Value * 100.0);
					Diag->AddChild(Item1, s);
				}
				// "NG calculé: %.0f, NG mini nécessaire: %.0f"
				s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashNGNGLimit").w_str(), analys->Flash->Ng->Value, analys->Flash->Ng->Limit->Value);
				Diag->AddChild(Item1, s);
			}
			else {
				// "Portée maxi du flash = %s"
				s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashRangeMax").w_str(), FocusDistanceFormat(analys->Flash->Limit->Distance->Value, false).w_str());
				Diag->AddChild(Item1, s);

				// "NG calculé: %.0f"
				s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashNG").w_str(), analys->Flash->Ng->Value);
				Diag->AddChild(Item1, s);
			}
		}
		else {
			if (analys->Flash->Required->Value)
				// "Le flash n'a pas fonctionné"
					s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.FlashDidNotFire").w_str());
			else
				// "La photo a été prise sans flash"
					s = Diag->Analys->Lgs->QueryKey(L"DIAG.FlashNotUsed");
			Diag->AddChild(tvi, s);
		}
	}
	else {
		// "Pas d'information disponible concernant le flash"
		s = Diag->Analys->Lgs->QueryKey(L"DIAG.FlashNoInfo");
		Diag->AddChild(tvi, s);
	}
}

#pragma end_region

#pragma region DExposure

// -----------------------------------------------------
// CLASS DExposure
// -----------------------------------------------------

DExposure::DExposure(DDiagnostic *diag) {
	Diag = diag;
}

DExposure::~DExposure(void) {
}

void __fastcall DExposure::Diagnostic(void) {
	TTreeViewItem *Item0, *Item1;
	UnicodeString s;
	unsigned idx;
	double ev;

	Item0 = Diag->AddRoot(Diag->Analys->Lgs->QueryKey(L"DIAG.Exposure"));

	if (Diag->Analys->Exposure->IsFromCamera) {
		// "%s mesuré. Condition d'éclairage équivalente %s."
		s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.ExposureNaturalLight").w_str(), Diag->Analys->Exposure->Caption.w_str(), Diag->Analys->Exposure->NaturalLight->Caption.w_str());
		Item1 = Diag->AddChild(Item0, s);

		// "Votre photo semble %s avec vos réglages (%s, %s, %s)"
		if (Diag->Analys->Exposure->Value > 0.0) {
			ev = Diag->Analys->Exposure->Relative->Value;
			if (!Diag->Analys->Flash->Fired->IsFired) {
				if ((ev > -0.5) && (ev < 0.5))
					idx = 0; // correcte
				else if ((ev > -1) && (ev <= -0.5))
					idx = 1; // legerement sous exposée
				else if ((ev > -1.4) && (ev <= -1))
					idx = 2; // sous exposée
				else if ((ev <= -1.4))
					idx = 3; // fortement sous exposée
				else if ((ev >= 0.5) && (ev < 1))
					idx = 4; // legerement sur exposée
				else if ((ev >= 1) && (ev < 1.4))
					idx = 5; // sur exposée
				else if ((ev >= 1.4))
					idx = 6; // fortement sur exposée
			}
			else {
				if (ev < -0.5)
					if (Diag->Analys->Flash->Range->IsOkWithoutBias) {
						idx = 7; // correcte compensée par le flash
					}
					else {
						idx = 8; // sous exposée, sujet trop loin du flash
					}
				else if ((ev >= -0.5) && (ev < 0.5)) {
					if (Diag->Analys->Flash->Range->IsOkWithoutBias) {
						idx = 9; // correcte, ombres débouchées au flash
					}
					else {
						idx = 10; // correcte, sujet trop loin du flash
					}
				}
				else {
					if (Diag->Analys->Flash->Range->IsOkWithoutBias) {
						idx = 11; // sur exposée, débouchage des ombres au flash
					} else {
						idx = 12; // sur exposée, sujet trop loin du flash
                    }
				}
			}
		}
		else
			idx = 13;
		s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.ExposureOSettings").w_str(), Diag->Analys->Lgs->QueryKey(L"Exposure.Idx" + UnicodeString(idx)).w_str(), Diag->Analys->ExposureTime->Caption.w_str(), Diag->Analys->Aperture->Caption.w_str(), Diag->Analys->Iso->Caption.w_str());
		Item1 = Diag->AddChild(Item0, s);
		if (Diag->Analys->Exposure->Relative->Value != 0.0) {
			Diag->RecurseCalc(Item1, Diag->Analys, true, true, true);
		}
	}
	else {
		// "%s estimé. Condition d'éclairage équivalente %s."
		s = Uprintf(Diag->Analys->Lgs->QueryKey(L"DIAG.ExposureCalculated").w_str(), Diag->Analys->Exposure->Caption.w_str(), Diag->Analys->Exposure->NaturalLight->Caption.w_str());
		Item1 = Diag->AddChild(Item0, s);
	}
}

#pragma end_region

#endif
