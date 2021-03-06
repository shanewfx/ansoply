//----------------------------------------------------------------------------
//  File:   CMultiSAP.h
//
//  Desc:   DirectShow sample code
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------
#ifndef HEADER_CMULTISAP
#define HEADER_CMULTISAP

#include "project.h"
#include "BltAlpha.h"
#include <map>
// #define MAXMOVIES 7
class CDynamicBitmap;
class CDynamicEffectBitmap;
class CTextObject;
class CBitmapObject;
class CVideoGroup;
class CAnsoplyObject;
struct sDialogInfo;
class CDynaEfBmpGroup;
class CEffectTextGroup;

#define CHK_RANGE( n, size, err, expr)\
if( n<0 || n> size-1 ) { return err; } else { return (expr); }

//----------------------------------------------------------------------------
//  Class:  CMultiSAP
//  Desc:   sample of custom Allocator-presenter 
//----------------------------------------------------------------------------
class CMultiSAP :
        public CUnknown,
        public IVMRSurfaceAllocator,
        public IVMRImagePresenter,
        public IAMGraphBuilderCallback
{
	friend class CVideoGroup;
	friend class CBitmapObject;
	friend class CTextObject;
	friend class CDynamicBitmap;
public:
#if 0
	CVideoGroup*    m_movieListArray[8];

	BOOL            m_movieListThread[8];
	static UINT  __cdecl  SmoothPlayThread(LPVOID param);

	void CmdAddMovieEx( sMovieInfo* pMovInf, int index );
	void CmdPlayMovieEx( sMovieInfo* pMovInf, int index );
#endif 
	
	LONG CreateVideoGroup();
	LONG AddVideoFile(ULONG uGroupID, LPCTSTR sFilePathName);
	LONG DelVideoFile(ULONG uGroupID, ULONG uFileID);
	LONG DelVideoGroup(ULONG uGroupID);

	LONG Create_Dy_Ef_Bmp_Group();
	LONG AddDynamicEffectBmp(ULONG uGroupID, LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle, ULONG uDelay);
	LONG InsertDynamicEffectBmp(ULONG uGroupID, ULONG uWhere, LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle, ULONG uDelay);
	LONG DelBitmapGroup(ULONG uGroupID);
	LONG SetBitmapParam(ULONG uBitmapID, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize);

	LONG CreateTextGroup();
	LONG AddText(ULONG uGroupID, ULONG uX, ULONG uY, LPCTSTR sOutputText, LPCTSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID, ULONG uRegionWidth, ULONG uRegionHeight, ULONG uDrawStyle, ULONG uDelay, ULONG uAlpha, ULONG uTransparentColor);
	LONG DelTextGroup(ULONG uGroupID);
	LONG SetTextParam(ULONG uTextID, ULONG uX, ULONG uY, LPCTSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG uAlpha, ULONG uTransparentColor, ULONG uRegionWidth, ULONG uRegionHeight);

	LONG SetPlayParam(ULONG uGroupID, ULONG uID, ULONG uDrawStyle);
	LONG GetPlayParam(ULONG uGroupID, ULONG* uID, ULONG* uDrawStyle);

	LONG GetVideoGroupCount();
	LONG GetFirstVideoGroupID();
	LONG GetNextVideoGroupID(LONG & uGroupID);

	LONG GetFirstVideoObjectID(ULONG uGroupID);
	LONG GetNextVideoObjectID(ULONG uGroupID, ULONG & uObjectID);
	LONG GetVideoObjectCount(ULONG uGroupID);
	LONG GetVideoObjectFileName (
		ULONG uGroupID, 
		ULONG uFileID,
		LPWSTR sFilePathName
		);
	LONG GetVideoLength(ULONG uGroupID, ULONG uFileID, DOUBLE* uLength);
	LONG GetCurrentFileID(ULONG uGroupID, LONG * uFileID);
	LONG GetCurrentPlayingPos(ULONG uGroupID, ULONG * uCurPos);

	LONG Play(ULONG uGroupID);
	LONG Pause(ULONG uGroupID);
	LONG Stop(ULONG uGroupID);
	LONG Next(ULONG uGroupID);
	LONG Previous(ULONG uGroupID);
	LONG Seek(ULONG uGroupID, ULONG uPosition);
	LONG SetPlayRate(ULONG uGroupID, DOUBLE dRate);
	LONG SetPlayMode(ULONG uGroupID, ULONG uPlayMode);

	LONG SetBitmap(
		LPCTSTR sBitmapFilePath,
		ULONG uAlpha,
		ULONG uTransparentColor,   
		ULONG uX,
		ULONG uY,
		ULONG uWidth,
		ULONG uHeight,
		ULONG uOriginalSize
		);

	LONG GetBitmap(
		ULONG uBitmapID, 
		BSTR* sBitmapFilePath, 
		ULONG* uAlpha, 
		ULONG* uTransparentColor, 
		ULONG* uX, 
		ULONG* uY,
		ULONG* uWidth,
		ULONG* uHeight,
		ULONG* uOriginalSize,
		ULONG* uDrawStyle,
		ULONG* uDelay);

	LONG DelBitmap(ULONG uBitmapID);
	LONG DelDynamicBitmap(ULONG uDynamicBitmapID);

	LONG SetDynamicBitmap(
		ULONG *  uObjectID,
		LPCTSTR sBitmapFilePath,
		ULONG uAlpha,
		ULONG uTransparentColor,   
		ULONG uX,
		ULONG uY,
		ULONG uWidth,
		ULONG uHeight,
		ULONG uOriginalSize,
		ULONG uMilli);

	LONG SetDynamicEffectBitmap(
		ULONG *  uObjectID,
		LPCTSTR sBitmapFilePath,
		ULONG uAlpha,
		ULONG uTransparentColor,   
		ULONG uX,
		ULONG uY,
		ULONG uWidth,
		ULONG uHeight,
		ULONG uOriginalSize,
		ULONG uMilli);

	LONG SetEffectBitmap(
		LPCTSTR sBitmapFilePath,
		ULONG uAlpha,
		ULONG uTransparentColor,   
		ULONG uX,
		ULONG uY,
		ULONG uWidth,
		ULONG uHeight,
		ULONG uOriginalSize,
		ULONG uDrawStyle,
		ULONG uDelay
		);

	LONG BringToFront(ULONG uGroupID);

	LONG SendToBack(ULONG uGroupID);

	LONG BringUp(ULONG uGroupID);

	LONG SendBack (ULONG uGroupID);

	CVideoGroup * FindGroup( ULONG uGroupID );
	// Get the First VideoGroup to Draw
	CVideoGroup * GetFirstGroup( ULONG & uGroupID );
	// Get the Next VideoGroup to Draw according to the Previous Max Level
	// If NULL, we get to the last
	CVideoGroup * GetNextGroup( ULONG & uGroupID );

	LONG SelectObject(ULONG uGroupID, ULONG uFrameColor);

	LONG UnSelectVideoGroup();

	LONG SelectObjectByCoordinate(
		ULONG * uObjectID,
		ULONG * uObjectType,
		ULONG uX,
		ULONG  uY,
		ULONG uFrameColor
		);


	LONG GetVideoGroupZOrder(ULONG uGroupID, ULONG * uZOrder);

	LONG SetVideoPosAndSize(
		ULONG uGroupID,
		ULONG uX,
		ULONG uY,
		ULONG uWidth,
		ULONG uHeight
		);

	LONG GetVideoPositionAndSize(ULONG uGroupID, ULONG* uX, ULONG* uY, ULONG* uWeight, ULONG* uHeight);

	LONG SetVideoAlpha(ULONG uGroupID, ULONG uAlpha);

	LONG GetVideoAlpha(ULONG uGroupID, ULONG* uAlpha);

	LONG SelectVideoGroup(LONG cX, LONG cY, ULONG* uGroupID);

	LONG GetText(
		ULONG uID,
		ULONG * uX,
		ULONG * uY,
		LPTSTR sOutputText,
		LPTSTR FaceName,
		ULONG * uItalic,
		ULONG * uBold,
		ULONG * uUnderLine,
		ULONG * uWidth,
		ULONG * uHeight,
		ULONG * uColor,
		ULONG* uAlpha, ULONG* uTransparentColor, ULONG* uDrawStyle, ULONG* uDelay);

	LONG SetText(
		ULONG uX,
		ULONG uY,
		LPCTSTR sOutputText,
		LPCTSTR  sFaceName,
		ULONG    uItalic,
		ULONG   uBold,
		ULONG   uUnderLine,
		ULONG   uWidth,
		ULONG   uHeight,
		ULONG uColor,
		ULONG* uID);

	LONG SetTextInRegion(
		ULONG uX,
		ULONG uY,
		LPCTSTR sOutputText,
		LPCTSTR  sFaceName,
		ULONG    uItalic,
		ULONG    uBold,
		ULONG    uUnderLine,
		ULONG    uWidth,
		ULONG    uHeight,
		ULONG    uColor,
		ULONG*   uID,
		ULONG    uRegionWidth,
		ULONG    uRegionHeight);

	LONG SetEffectTextInRegion(
		ULONG uX,
		ULONG uY,
		LPCTSTR sOutputText,
		LPCTSTR  sFaceName,
		ULONG    uItalic,
		ULONG    uBold,
		ULONG    uUnderLine,
		ULONG    uWidth,
		ULONG    uHeight,
		ULONG    uColor,
		ULONG*   uID,
		ULONG    uRegionWidth,
		ULONG    uRegionHeight,
		ULONG    uDrawStyle,
		ULONG    uDelay);

	LONG InsertEffectTextInRegion(
		ULONG uGroupID,
		ULONG uWhere,
		ULONG uX,
		ULONG uY,
		LPCTSTR sOutputText,
		LPCTSTR  sFaceName,
		ULONG    uItalic,
		ULONG    uBold,
		ULONG    uUnderLine,
		ULONG    uWidth,
		ULONG    uHeight,
		ULONG    uColor,
		ULONG*   uID,
		ULONG    uRegionWidth,
		ULONG    uRegionHeight,
		ULONG    uDrawStyle,
		ULONG    uDelay);

	LONG DelText(ULONG uID);

	void RenderVideo();
	void RenderText();
	void RenderBitmap();
	void RenderDynamicBitmap();

	void Refresh();

	LONG SetVideoFile(ULONG uGroupID, LPCTSTR sFileName, ULONG uOldFileID, ULONG * uNewFileID);

	LONG SetVisibility(ULONG uObjectID, ULONG bVisibility);
	LONG SetPlayTimes(ULONG uGroupID, ULONG uPlayTimes);
	LONG SetPlayTimeout(ULONG uGroupID, ULONG uTimeout_s);
	LONG SetEffectBitmapStyle(ULONG uID, ULONG uStyle);
	LONG SetEffectPlayRange(ULONG uID, ULONG uPlayMode, ULONG uRangeStart, ULONG uRangeEnd);
	LONG SetEffectEndTime(ULONG uID, LONG EndTime);

	LONG SavePlayList(LPCTSTR sFile);
	LONG LoadPlayList(LPCTSTR sFile);
	LONG SetMediaFilePath(LPCTSTR sFilePathName);
	LONG SetDefaultVideoSize(ULONG uGroupID, ULONG uX, ULONG uY);
	static void __cdecl SetDefaultThread(LPVOID param);

	void Close();

	TCHAR   m_MediaFilePath[MAX_PATH];
	HRESULT DDARGB32SurfaceInit(
		LPDIRECTDRAWSURFACE7* lplpDDS,
		BOOL bTexture,
		DWORD cx,
		DWORD cy
		);

	HRESULT CreateFontCache(int cyFont, CTextObject* pTextObject, IDirectDrawSurface7** pDDSurface, BOOL bRegion);

	static void ChangeDynamicBitmap(void* param);
	static void ChangeDynamicEffectBitmap(void* param);
public:
	CVideoGroup *                   m_pBGVideo;
	CAtlList<CVideoGroup*>			m_videoGroups;
	CRITICAL_SECTION                m_videoGroupsCS;
	std::map<ULONG, CDynaEfBmpGroup*> m_dy_ef_bmp_Group;

	std::map<ULONG, CEffectTextGroup*> m_EffectTextGroup;

	CAtlMap<ULONG, CBitmapObject*>  m_bitmapObject;
	CAtlMap<ULONG, CTextObject*>    m_textObject;
	CAtlMap<ULONG, CDynamicBitmap*> m_dynamicBitmap;
	CAtlMap<ULONG, CDynamicEffectBitmap*> m_dynamicEffectBitmap;

	// the key is the type
	// 1: VideoGroup
	// 2: Bitmap
	// 3: Text
	// 4: DynamicBitmap
	CAtlList<CAnsoplyObject*>       m_drawList;
	
//	CComPtr<IDirectDrawSurface7> m_lpDDSFontCache;
//	CComPtr<IDirectDrawSurface7> m_lpDDSBitmapCache;
//	CComPtr<IDirectDrawSurface7> m_lpDDSDynamicBitmapCache;
	CAlphaBlt* m_pAlphaBlt;
//	HFONT m_hFont;
//	int m_cxFont;
//	int m_cyFont;
//	int           m_cxFontImg;
//	int           m_cyFontImg;
//	CTextObject*  m_pTextObject;
	ULONG_PTR     m_gdiplusToken;
	LONG          m_lSelectGroupID;
	ULONG         m_uSelectFrameColor;

	ULONG         m_uSurfaceWidth;
	ULONG         m_uSurfaceHeight;
//////////////////////////////////////////////////////////////////////////

    CCritSec         m_AppImageLock;
    HWND             m_hwndApp;             // target video playback window
    RECT             m_rcDst;               // client size of the window
    CMovieList       m_movieList;           // list of movies in the presentation
    DWORD            m_DlgTID;              // thread ID of the parent dialog (the one that gets user input)
    DWORD            m_dwThreadID;          // ID of the thread where custom AP manager resides
    HANDLE           m_hThread;             // handle to the thread where custom AP manager resides
    HANDLE           m_hQuitEvent;          // handle to the quit event
        
    CEffectQueue     m_EffectQueue;         // presentation is a sequence of video effects
    CEffect*         m_pEffect;             // current video effect
    DWORD_PTR        m_pdwNextSelectedMovie;// 

    HMONITOR                    m_hMonitor;     // monitor handle
    CComPtr<IDirectDraw7>       m_lpDDObj;      // DirectDraw object
    CD3DHelper*                 m_pD3DHelper;   // object that performs most DirectDraw stuff
    CSparkle*                   m_pSparkle;     // sparkle effect on the background
    DWORD                       m_dwFrameNum;   // number of frames drawn

    TCHAR                       m_achErrorMessage[2048];
    TCHAR                       m_achErrorTitle[MAX_PATH];
    bool                        m_bErrorMessage;
    
    // DirectShow specific members
    DDCAPS                          m_ddHWCaps;     // hardware capabilities
    CComPtr<IVMRWindowlessControl>  m_pWC;          // windowless control
    CComPtr<IVMRSurfaceAllocator>   m_pAlloc;       // DEFAULT allocator presenter
    CComPtr<IVMRImagePresenter>     m_pPresenter;   // image presenter
    CComPtr<IDirectDrawSurface7>    m_lpBackBuffer; // back buffer

	CComPtr<IVMRFilterConfig>       m_config;


    
    // Allocator-presenter specific functions
    //
    HRESULT CreateDefaultAllocatorPresenter();

    HRESULT InitializeEnvironment();

    HRESULT AllocateSurfaceWorker(  CMovie *pmovie,
                                    DWORD dwFlags,
                                    LPBITMAPINFOHEADER lpHdr,
                                    LPDDPIXELFORMAT lpPixFmt,
                                    LPSIZE lpAspectRatio,
                                    DWORD dwMinBackBuffers,
                                    DWORD dwMaxBackBuffers,
                                    DWORD* lpdwBackBuffer,
                                    LPDIRECTDRAWSURFACE7* lplpSurface,
                                    DDSURFACEDESC2* pddsdDisplay);

    HRESULT AllocateOverlaySurface(
                            LPDIRECTDRAWSURFACE7* lplpSurf,
                            DWORD dwFlags,
                            DDSURFACEDESC2* pddsd,
                            DWORD dwMinBuffers,
                            DWORD dwMaxBuffers,
                            DWORD* lpdwBuffer
                            );

    HRESULT AllocateOffscreenSurface(
                                        LPDIRECTDRAWSURFACE7* lplpSurf,
                                        DWORD dwFlags,
                                        DDSURFACEDESC2* pddsd,
                                        DWORD dwMinBuffers,
                                        DWORD dwMaxBuffers,
                                        DWORD* lpdwBuffer,
                                        BOOL fAllowBackBuffer
                                        );

    HRESULT CreateBackBuffers(  LPDIRECTDRAWSURFACE7 lpSurf7FB,
                                DDSURFACEDESC2* pddsd,
                                LPDWORD lpdwBackBuffer);
        
    // Interaction with parent dialog    

    DWORD WaitForDialog();
        
        
public:
    CMultiSAP(HWND hwndApplication, HRESULT *phr, ULONG uWidth, ULONG uHeight);
    ~CMultiSAP();
    
    static DWORD WINAPI ComposeThreadProc(LPVOID lpParameter);
    DWORD ComposeThread();

	IVMRMixerBitmap *               m_pBMP;
    //
    // Interface implementation
    //
 
    DECLARE_IUNKNOWN STDMETHODIMP NonDelegatingQueryInterface(REFIID, void**);
    
    // IVMRSurfaceAllocator implementation
    //
    STDMETHODIMP AllocateSurface(   DWORD_PTR w,
                                    VMRALLOCATIONINFO *lpAllocInfo,
                                    DWORD* lpdwActualBackBuffers,
                                    LPDIRECTDRAWSURFACE7* lplpSurface);

    STDMETHODIMP FreeSurface( DWORD_PTR w );

    STDMETHODIMP PrepareSurface(    DWORD_PTR w, 
                                    LPDIRECTDRAWSURFACE7 lplpSurface,
                                    DWORD dwSurfaceFlags);

    STDMETHODIMP AdviseNotify(IVMRSurfaceAllocatorNotify* lpIVMRSurfAllocNotify);
    
    
    // IVMRImagePresenter implementation

    STDMETHODIMP StartPresenting(DWORD_PTR w);

    STDMETHODIMP StopPresenting(DWORD_PTR w);

    STDMETHODIMP PresentImage(DWORD_PTR w, VMRPRESENTATIONINFO* p);
    
    // IAMGraphBuilderCallback implementation

    STDMETHODIMP SelectedFilter( IMoniker *pMon );

    STDMETHODIMP CreatedFilter( IBaseFilter *pBf );
    
    // commands from the parent dialog
    void CmdAddMovie( sMovieInfo* pMovInf );
    void CmdPlayMovie( sMovieInfo* pMovInf );
    void CmdPauseMovie( sMovieInfo* pMovInf );
    void CmdEjectMovie( sMovieInfo* pMovInf );
    void CmdStopMovie( sMovieInfo* pMovInf );
    void CmdExpandMovie( sMovieInfo* pMovInf );

    void CmdAddEffect(  eEffect effect, 
                        DWORD dwStartTime, 
                        LONG lPlayTime, 
                        DWORD dwEndTime, 
                        BOOL bAddFirst = FALSE);
    void CmdProcessDoubleClick( int xPos, int yPos);
    
    REFTIME CmdGetMovieDuration( sMovieInfo* pMovInf );
    REFTIME CmdGetMoviePosition( sMovieInfo* pMovInf );
    void CmdSetMoviePosition( sMovieInfo* pMovInf, REFTIME rtPos );
    
    DWORD CmdGetMovieFramesFlipped( sMovieInfo* pMovInf );
    OAFilterState CmdGetMovieState( sMovieInfo* pMovInf );
    
    void CmdQuit(sMovieInfo* pMovInf);
    
    // Scene composition and rendering
    void ComposeAndRender();
    
    // app specific functions
    HRESULT Initialize();
    void RePaint();
    void RepositionMovie();
    void GetMoviePosition( RECT * rc);
    void PutMoviePosition( RECT rc);

    // Command functions
   
    HRESULT OpenMovie( DWORD_PTR dwID )
    {
        CMovie *pmovie = m_movieList.GetMovie( dwID );
        if( pmovie )
        {
            return pmovie->OpenMovie();
        }
        return E_INVALIDARG;
    }
    
    HRESULT PlayMovie( DWORD_PTR dwID)
    {
        CMovie *pmovie = m_movieList.GetMovie( dwID );
        if( pmovie )
        {
            return pmovie->PlayMovie();
/*
			pmovie->PlayMovie();
			long event;
			return pmovie->m_Me->WaitForCompletion(INFINITE, &event);
*/
        }
        return E_INVALIDARG;
    }
    
    HANDLE GetMovieEventHandle( DWORD_PTR dwID)
    {
        CMovie *pmovie = m_movieList.GetMovie( dwID );
        if( pmovie )
        {
            return pmovie->GetMovieEventHandle();
        }
        return NULL;
    }
    
    LONG GetMovieEventCode( DWORD_PTR dwID)
    {
        CMovie *pmovie = m_movieList.GetMovie( dwID );
        if( pmovie )
        {
            return pmovie->GetMovieEventCode();
        }
        return NULL;
    }
   
    HANDLE          GetQuitEvent()  { return m_hQuitEvent; }
    int             GetSize()       { return m_movieList.GetSize(); }
    HWND            GetWnd()        { return m_hwndApp; }
    LPDIRECTDRAW7   GetDDObject()   { return m_lpDDObj; }
    HMONITOR        GetMonitor()    { return m_hMonitor; }
    
    DWORD           GetCurrentFrameNumber() { return m_dwFrameNum;}
    
    void            SetFocus();
    void            ReleaseFocus();
    void            DeleteAllMovies();
};

//extern CMultiSAP * g_pMultiSAP;

#endif