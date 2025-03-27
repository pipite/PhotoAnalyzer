#ifndef CLASSSCANDISKH
#define CLASSSCANDISKH
// ---------------------------------------------------------------------------

#include <FMX.TreeView.hpp>
#include <FMX.Types.hpp>
#include <FMX.Effects.hpp>
#include <FMX.Layouts.hpp>
#include <stdlib.h>

class TThumbPanel;
class TFolderItem;
class TGroupPanel;
class TScanDisk;
class TThreadScanFile;

#include "ClassPhoto.h"
#include "ClassTiff.h"
#include "ClassStoryboard.h"
#include "ClassImageFilter.h"

void         __fastcall CalcFolderItemHeight(TFolderItem *FolderItem);
void         __fastcall CalcAllHeight(TFmxObject *Object);
TThumbPanel*            GetThumbPanel(TObject *Sender);

//---------------------------------------------------------------------------
class TThumbPanel : public TPanel
{
private:
	UnicodeString PPath;
	TStoryBoard *StoryBoard;
	bool PSelected;

	void     __fastcall SetSelected(bool selected);
	TBitmap* __fastcall GetBitmap(void);

protected:
public:
	TPhoto  *Photo;
	TImage  *Image;
	TLabel  *Label;
	TLgs    *Lgs;
	double  Ratio;
	double  OffsetX;
	ERotate Rotate;

			 TThumbPanel(TGridLayout* Owner, TTagMap *tagmap, UnicodeString path, TLgs *lgs, TStoryBoard *storyboard);
			 ~TThumbPanel(void);

	void     __fastcall UpdateInfo(void);
	void     __fastcall DoClick(TObject *Sender);
	void     __fastcall DoMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);

__published:
	__property UnicodeString Path = {read = PPath, write = PPath};
	__property TBitmap* Bitmap    = {read = GetBitmap};
	__property bool Selected      = {read = PSelected, write = SetSelected};
};

//---------------------------------------------------------------------------
class TFolderItem: public TTreeViewItem
{
	void __fastcall FIMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y);
	void __fastcall FIClick(TObject *Sender);

public:
	TGroupPanel   *GroupPanel;
	UnicodeString Path;
	int           ImagesLevel1Count;
	int           ImagesAllLevelCount;
	int           SubFoldersCount;

		 TFolderItem(TFmxObject* Owner);
		 ~TFolderItem(void);
};

//---------------------------------------------------------------------------
class TGroupPanel: public TFolderItem
{
	void __fastcall CBChange(TObject *Sender);

public:
	TPanel       *Panel;
	TLabel       *Label;
	TStringList  *ListModel;
	TStringList  *ListLens;
	TGroupBox    *GBModel;
	TGroupBox    *GBLens;
	TProgressBar *ProgressBar;
	TGridLayout  *GridLayout;
	TLgs         *Lgs;
	int          Count;

		 TGroupPanel(TFolderItem* Owner, TLgs *lgs);
		 ~TGroupPanel(void);

	void __fastcall OpenProgressBar(int max);
	void __fastcall CloseProgressBar(void);
	void __fastcall AddInfo(TAnalys *Analys);
	void __fastcall UpdateInfo(void);
};

//---------------------------------------------------------------------------
class TScanDisk {
public:
	TTreeView     *TreeView;
	TLgs          *Lgs;
	TTagMap       *TagMap;
	TStoryBoard   *StoryBoard;
	UnicodeString Path;
	UnicodeString TagMapFile;
	int           Count;

		 TScanDisk(TTreeView *Tv, TTreeView *Tv3, UnicodeString tagmapfile, TLgs *lgs, TStoryBoard *storyboard);
		 ~TScanDisk(void);

	int  __fastcall ScanFolder(TFmxObject *Owner, UnicodeString *path);
	void __fastcall ScanFile(void);
};

//---------------------------------------------------------------------------
class TThreadScanFile : public TThread
{
private:
	TFolderItem   *Tfi;
	TStoryBoard   *StoryBoard;
	TGridLayout   *GridLayout;
	TThumbPanel   *ThumbPanel;
	UnicodeString FullName;
	TTagMap       *TagMap;
	TLgs          *Lgs;

protected:
	void __fastcall Execute(void);
	void __fastcall ThumbLoad(void);
	void __fastcall UpdateGroupPanelInfo(void);
	void __fastcall UpdateThumbPanelInfo(void);
	void __fastcall Compute(void);
public:
		 TThreadScanFile(bool CreateSuspended, TFolderItem *tfi, TTagMap *tagmap, TLgs *lgs, TStoryBoard *storyboard);
};

#endif
