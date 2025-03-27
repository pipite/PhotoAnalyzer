#ifndef mainH
#define mainH

#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.TreeView.hpp>
#include <FMX.Types.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Memo.hpp>

#include <FMX.ExtCtrls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Layers3D.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <FMX.Edit.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Colors.hpp>
#include <FMX.Filter.Effects.hpp>
#include <FMX.Effects.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Objects3D.hpp>
#include <FMX.ComboEdit.hpp>
#include <FMX.ComboTrackBar.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls3D.hpp>
#include <FMX.StdCtrls.hpp>
#include <System.Math.Vectors.hpp>
#include <FMX.Viewport3D.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.adomxmldom.hpp>
#include <Xml.Win.msxmldom.hpp>
#include <Xml.omnixmldom.hpp>
#include <FMX.EditBox.hpp>


class TForm1;

#include "ClassScandisk.h"
#include "UtilCommon.h"
#include "classtraitement.h"
#include "ClassStoryboard2D.h"
#include "ClassImageFilter.h"

#define APPNAME L"Photo Analyzer 1.0";

class TForm1 : public TForm {
__published: // Composants gérés par l'EDI

	TStyleBook *StyleBook1;
	TPanel *Panel1;
	TPanel *Panel2;
	TSplitter *Splitter3;
	TStatusBar *StatusBar1;
	TTabControl *TabControlMain;
	TTabItem *TabItemViewer;
	TTabItem *TabItemExifData;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TTabItem *TabItemConfig;
	TTreeView *TreeViewExif;
	TPanel *Panel6;
	TPanel *Panel8;
	TEdit *EditFileConfig;
	TLabel *LabelFileConfig;
	TLabel *LabelDefaultSearchPath;
	TEdit *Edit2;
	TRadioButton *RadioButtonUserList;
	TRadioButton *RadioButtonFullList;
	TRadioButton *RadioButtonFullListExpert;
	TPanel *Panel9;
	TPanel *Panel10;
	TPanel *Panel11;
	TLabel *LbExposureTime;
	TPanel *Panel12;
	TLabel *LbAperture;
	TPanel *Panel13;
	TLabel *LbIso;
	TPanel *Panel14;
	TPanel *Panel15;
	TLabel *LbExposureProgram;
	TPanel *Panel24;
	TPanel *Panel16;
	TPanel *Panel18;
	TTrackBar *TbEv;
	TLabel *Label9;
	TPanel *Panel21;
	TLabel *LbMeteringMode;
	TPanel *Panel20;
	TPanel *Panel22;
	TLabel *LbFocusAreaMode;
	TPanel *Panel19;
	TLabel *LbFocusMode;
	TButton *ButtonBrowse;
	TToolBar *ToolBar1;
	TImage *Image1;
	TOpenDialog *OpenDialog1;
	TTabItem *TabItem4;
	TImage *Image5;
	TImage *Image6;
	TLabel *LbExposureTimeEv;
	TLabel *LbApertureEv;
	TLabel *LbIsoEv;
	TLabel *LbMesuredEv;
	TPanel *Panel28;
	TComboBox *ComboBoxLang;
	TLabel *LabelLang;
	TAniIndicator *Working;
	TLabel *LbPhotoInfo;
	TLabel *LbLens;
	TLabel *LbFocale;
	TPanel *Panel27;
	TProgressBar *PbLensQuality;
	TImage *Image4;
	TTreeView *TreeView2;
	TPanel *Panel17;
	TPanel *Panel25;
	TImage *Image8;
	TImage *ImHistogram;
	TTreeView *TreeView3;
	TExpander *ExFilterAll;
	TExpander *ExFilterFlashNone;
	TExpander *ExFilterExposureNone;
	TRadioButton *RBFilterExposureCorrect;
	TRadioButton *RBFilterExposureOver;
	TRadioButton *RBFilterExposureUnder;
	TRadioButton *RBFilterExposureOther;
	TComboTrackBar *CtbFilterExposureDev1;
	TComboTrackBar *CtbFilterExposureDev2;
	TExpander *ExFilterLightningNone;
	TComboTrackBar *CtbFilterLightningEv1;
	TComboTrackBar *CtbFilterLightningEv2;
	TPanel *PFilterFlashOption;
	TComboTrackBar *CtbFilterFlashTol;
	TRadioButton *RBFilterFlashOutOfRange;
	TRadioButton *RBFilterFlashAll;
	TRadioButton *RBFilterFlashYes;
	TRadioButton *RBFilterFlashError;
	TRadioButton *RBFilterFlashNo;
	TComboTrackBar *CtbExposureTolerance;
	TLabel *Label2;
	TRadioButton *RBFilterLightning6Ev;
	TRadioButton *RBFilterLightning9Ev;
	TRadioButton *RBFilterLightning11Ev;
	TRadioButton *RBFilterLightning14Ev;
	TRadioButton *RBFilterLightningOther;
	TExpander *ExFilterFocaleNo;
	TRadioButton *RBFilterFocaleWide;
	TRadioButton *RBFilterFocaleTele;
	TRadioButton *RBFilterFocaleStandard;
	TRadioButton *RBFilterFocale24x36;
	TComboTrackBar *CtbFilterFocale24x36Min;
	TComboTrackBar *CtbFilterFocale24x36Max;
	TExpander *ExFilterExposureTimeNo;
	TRadioButton *RBFilterExposureTimeStill;
	TRadioButton *RBFilterExposureTimeTripod;
	TRadioButton *RBFilterExposureTimeRapid;
	TRadioButton *RBFilterExposureTimeSlow;
	TRadioButton *RBFilterExposureTimeSpeed;
	TComboTrackBar *CtbFilterExposureTimeSubjectSpeed;
	TLabel *Label3;
	TLabel *Label4;
	TComboTrackBar *CtbFilterFocale24x36Tol;
	TRadioButton *RBFilterFocale24x36Fixe;
	TComboTrackBar *CtbFilterFocale24x36Fixe;
	TPanel *Panel7;
	TCheckBox *CBFilterFlashBuiltIn;
	TCheckBox *CBFilterFlashExternal;
	TLabel *Label5;
	TComboTrackBar *CtbFilterExposureTimeStop;
	TLabel *Label6;
	TCheckBox *CBFilterStab;
	TRadioButton *RBFilterExposureTimeVerySlow;
	TExpander *ExFilterBorderNo;
	TRadioButton *RBFilterBorderClose;
	TRadioButton *RBFilterBorderLarge;
	TRadioButton *RBFilterBorderMedium;
	TRadioButton *RBFilterBorderAmerican;
	TComboTrackBar *CtbFilterBorderMin;
	TLabel *Label7;
	TComboTrackBar *CtbFilterBorderMax;
	TLabel *Label8;
	TExpander *ExDepthOfFieldNo;
	TRadioButton *RBFilterDepthOfField1;
	TRadioButton *RBFilterDepthOfField4;
	TRadioButton *RBFilterDepthOfField3;
	TRadioButton *RBFilterDepthOfField2;
	TComboTrackBar *CtbFilterDepthOfFieldMin;
	TComboTrackBar *CtbFilterDepthOfFieldMax;
	TPanel *Panel26;
	TSpeedButton *SbFolderBrowser;
	TExpander *ExFilterOrientationNo;
	TRadioButton *RBFilterOrientationLandscape;
	TRadioButton *RBFilterOrientationPortrait;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TCornerButton *BCollapseAll;
	TCornerButton *BExpandAll;
	TImage3D *Image3D2;
	TPanel *StoryBoardContainer;
	TTabItem *TabItem1;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TCheckBox *CbGridVisible;
	TCheckBox *CbGridSnap;
	TLabel *Label17;
	TLabel *Label18;
	TImageViewer *ImageViewer1;
	TContrastEffect *ContrastEffect1;
	TTreeView *TreeView1;
	TViewport3D *Viewport3D1;
	TGrid3D *Grid3D1;

	void __fastcall TreeView1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Panel1Resize(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall RadioButtonChange(TObject *Sender);
	void __fastcall ButtonBrowseClick(TObject *Sender);
	void __fastcall ComboBoxLangChange(TObject *Sender);
	void __fastcall TbEvChange(TObject *Sender);
	void __fastcall LbExposureTimeMouseEnter(TObject *Sender);
	void __fastcall LbExposureTimeMouseLeave(TObject *Sender);
	void __fastcall LbApertureMouseLeave(TObject *Sender);
	void __fastcall LbApertureMouseEnter(TObject *Sender);
	void __fastcall LbIsoMouseEnter(TObject *Sender);
	void __fastcall LbIsoMouseLeave(TObject *Sender);
	void __fastcall FilterChangeCheck(TObject *Sender);
	void __fastcall ExFilterChangeClick(TObject *Sender);
	void __fastcall BCollapseAllClick(TObject *Sender);
	void __fastcall BExpandAllClick(TObject *Sender);
	void __fastcall CbGridVisibleChange(TObject *Sender);
	void __fastcall CbGridSnapChange(TObject *Sender);
	void __fastcall ImHistogramClick(TObject *Sender);

private: // Déclarations utilisateur

	float XPanel;
	unsigned FlagLast1;
	unsigned FlagLast2;
	unsigned FlagLast3;
	unsigned FlagLast4;
	TImageFilter *ImageFilter;

	void __fastcall RecurseTviFilter(TTreeViewItem *tvi);
	void __fastcall RecurseTvi(TTreeViewItem *tvi);
	void __fastcall ApplyGlobalFilter(void);
	void __fastcall UpdateLangConst(void);

public: // Déclarations utilisateur

	TContrastEffect *ContrastEffect;
	TStoryBoard *StoryBoard;
	TScanDisk *ScanDisk;
	TLgs *Lgs;
	TThumbPanel *ThumbPanel;
	TBrightness *Brightness;
	unsigned WorkCount;

	void __fastcall UpdateViewer(TThumbPanel *ThumbPanel);
	void __fastcall UpdateLangVar(void);
	void __fastcall QueryFilterData(void);
	__fastcall TForm1(TComponent* Owner);

	void __fastcall ImageDblClick(TObject *Sender);
	void __fastcall ThumbImageMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall WorkStart(void);
	void __fastcall WorkStop(void);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
// ---------------------------------------------------------------------------
#endif
