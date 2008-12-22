//----------------------------------------------------------------------------
//  File:   CMultiSAP.cpp
//
//  Desc:   DirectShow sample code
//          Implementation of CMultiSAP
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//----------------------------------------------------------------------------

#include "stdafx.h"
#include "project.h"
#include "videogroup.h"
#include "idgenerator.h"
#include "bitmapobject.h"
#include "EffectBitmap.h"
#include "textobject.h"
#include "EffectText.h"
#include "DynaEfBmpGroup.h"
#include "EffectTextGroup.h"
#include "DynamicEffectBitmap.h"
#include "EffectBitmapEx.h"
#include "EffectTextEx.h"
#include ".\dynamicbitmap.h"
#include "D3DHelpers/d3dutil.h"
#include ".\tinyxml\tinyxml.h"
#include <stdio.h>
#include <comutil.h>
#include <string>
#include <time.h>
using namespace std;

//CMultiSAP * g_pMultiSAP;
//-------------------------------------------------------------------------
//  constructor
//-------------------------------------------------------------------------
CMultiSAP::CMultiSAP(HWND hwndApplication, HRESULT *phr, ULONG uWidth, ULONG uHeight)
            : CUnknown(NAME("Allocator Presenter"), NULL),
            m_hwndApp(hwndApplication),
            m_hMonitor(NULL),
            m_lpDDObj(NULL),
            m_lpBackBuffer(NULL),
            m_pSparkle(NULL),
            m_dwFrameNum(0),
            m_dwThreadID(0),
            m_hThread(NULL),
            m_hQuitEvent(NULL),
            m_pWC(NULL),
            m_pAlloc(NULL),
            m_pPresenter(NULL),
            m_pEffect(NULL),
            m_pdwNextSelectedMovie(NULL),
            m_bErrorMessage( false ),
			m_pBMP(NULL),
//			m_pTextObject(NULL),
//			m_lpDDSBitmapCache(NULL),
			m_lSelectGroupID(-1),
			m_uSelectFrameColor(0xFFDDDD00),
			m_uSurfaceWidth(uWidth),
			m_uSurfaceHeight(uHeight),
			m_pBGVideo(NULL)

{
    ASSERT(phr);
    
    m_achErrorMessage[0] = 0;
    m_achErrorTitle[0] = 0;

    m_hQuitEvent = CreateEvent( NULL, FALSE, FALSE, TEXT("CMultiSAP_Quit"));
    if( !m_hQuitEvent )
    {
        OutputDebugString(TEXT("Failed to create quit event\n"));
        *phr = E_POINTER;
    }
#if 0
	for (int i = 0; i < 8; ++i)
	{
		m_movieListThread[i] = FALSE;
	}
#endif

	ZeroMemory(m_MediaFilePath, MAX_PATH);

	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

    AddRef();

	InitializeCriticalSection(&m_videoGroupsCS);
}

//-------------------------------------------------------------------------
//  destructor
//-------------------------------------------------------------------------
CMultiSAP::~CMultiSAP()
{
 //   Close();
}

void CMultiSAP::Close()
{
	//POSITION pos = m_videoGroups.GetHeadPosition();
	//while (pos)
	//{
	//	CVideoGroup* pVideoGroup = m_videoGroups.GetNext(pos);
	//	delete pVideoGroup;
	//}
	//m_videoGroups.RemoveAll();

	if (m_hThread != NULL) 
		TerminateThread(m_hThread, 0);
	m_hThread = NULL;

	if (m_pD3DHelper)
		delete m_pD3DHelper;
	m_pD3DHelper = NULL;

	if (m_pSparkle)
		delete m_pSparkle;
	m_pSparkle = NULL;
	m_lpDDObj = NULL;    
	m_pWC = NULL;
	m_pPresenter = NULL;
	m_lpBackBuffer = NULL;

	if (m_pAlloc) 
	{
		m_pAlloc->FreeSurface(0);
		m_pAlloc = NULL;
	}

	POSITION pos = m_drawList.GetHeadPosition();
	while (pos)
	{
		CAnsoplyObject* pAObject = m_drawList.GetNext(pos);
		delete pAObject;
	}
	m_drawList.RemoveAll();

	GdiplusShutdown(m_gdiplusToken);

	DeleteCriticalSection(&m_videoGroupsCS);

}

//-------------------------------------------------------------------------
//  DeleteAllMovies
//  pings movies to quit, and once this happens, cleans movie list
//-------------------------------------------------------------------------
void CMultiSAP::DeleteAllMovies()
{
    if (m_hQuitEvent) 
    {       
        if (m_hThread) 
        {            
            SetEvent(m_hQuitEvent);
            WaitForSingleObject(m_hThread, INFINITE);
            CloseHandle(m_hThread);
        }
        
        CloseHandle(m_hQuitEvent);
    }
    
    while( m_movieList.GetSize() )
    {
        CMovie *pmovie = m_movieList.GetMovieByIndex(0);
        if (pmovie)
            m_movieList.Delete( pmovie->m_dwUserID );
    }
}

//-------------------------------------------------------------------------
//  Initialize
//  configures D3D environment and creates composing thread
//-------------------------------------------------------------------------
HRESULT CMultiSAP::Initialize()
{
	srand((unsigned)time(NULL));
    HRESULT hr = CoInitialize(NULL);
    if (hr == S_FALSE)
        CoUninitialize();

    hr = InitializeEnvironment();
    if (SUCCEEDED(hr)) 
    {   
        m_hThread = CreateThread(NULL, 0, ComposeThreadProc, this, 0, &m_dwThreadID);
        if (!m_hThread)
            hr = E_FAIL;
    }

	m_pBGVideo = new CVideoGroup();
	m_pBGVideo->m_uSurfaceHeight = m_uSurfaceHeight;
	m_pBGVideo->m_uSurfaceWidth  = m_uSurfaceWidth;
	m_pBGVideo->m_pD3DHelper     = m_pD3DHelper;
	m_pBGVideo->m_rcDst          = m_rcDst;
	m_pBGVideo->m_pMultiSAP      = this;
	m_pBGVideo->SetPlayMode(PLAY_LOOP);

	sMovieInfo movieInfo;
	CVideoObject* pVideoObject = new CVideoObject();

	USES_CONVERSION;
	CRegKey rg;
	TCHAR szModuleFileName[MAX_PATH] = {0};
	if( rg.Open(HKEY_CLASSES_ROOT, "CLSID\\{D1EBA581-03B3-42EA-B097-7F97F0ADB87B}\\InprocServer32") == ERROR_SUCCESS )
	{
		ULONG nLen = MAX_PATH;
		if( rg.QueryStringValue(NULL, szModuleFileName, &nLen) != ERROR_SUCCESS )
			return E_FAIL;
	}

	CString BlankFileName(szModuleFileName);
	BlankFileName = BlankFileName.Left( BlankFileName.ReverseFind( '\\' ) );
	BlankFileName += "\\Blank.wmv";

	wcscpy( movieInfo.achPath, T2W(BlankFileName) );
	movieInfo.pdwUserID = IDGenerator::GetInstance().GenID();
	pVideoObject->Initialize(&movieInfo, this);

//		CmdAddEffect(eEffectFading, 2000, 300, 400, TRUE); // set next video effect "fading"

	if( m_pEffect ) // ping video effect change
	{
		m_pEffect->Finish();
	}
	m_movieList.Add( pVideoObject );

	hr = pVideoObject->OpenMovie();
	if( FAILED(hr) )
	{
		//pVideoObject->Release();
		//m_movieList.Delete(pVideoObject->m_dwUserID);
		//delete pVideoObject;
		return hr;
	}

	RECT rc;
	GetMoviePosition(&rc);
	PutMoviePosition(rc);

	if( m_pEffect )
	{
		m_pEffect->Invalidate();
	}

	// not to play at this time
	//pVideoObject->PlayMovie();
	m_pBGVideo->AddVideoObject(pVideoObject);
	m_pBGVideo->Play();

    return hr;
}

//-------------------------------------------------------------------------
//  CreateDefaultAllocatorPresenter
//
//  Why do we need default AP? In this sample, we use the same DirectDrawObject
//  for each VMR involved in presentation. 
//-------------------------------------------------------------------------
HRESULT
CMultiSAP::CreateDefaultAllocatorPresenter()
{
    HRESULT hr = S_OK;
    IVMRMonitorConfig * pMonConf = NULL;
    
    __try 
    {
        CHECK_HR(hr = CoCreateInstance(CLSID_AllocPresenter, NULL,
                                       CLSCTX_INPROC_SERVER,
                                       IID_IVMRSurfaceAllocator,
                                       (LPVOID*)&m_pAlloc));
        
        CHECK_HR(hr = m_pAlloc->QueryInterface(IID_IVMRImagePresenter,
            (LPVOID*)&m_pPresenter));
        
        CHECK_HR(hr = m_pAlloc->QueryInterface(IID_IVMRWindowlessControl,
            (LPVOID*)&m_pWC));
/*
		hr = m_pAlloc->QueryInterface(IID_IVMRFilterConfig, (void**)&m_config);
		if( SUCCEEDED(hr)) 
		{
			hr = m_config->SetRenderingMode(VMRMode_Windowless);

			// Set two streams - video and alpha-blended bitmap
			hr = m_config->SetNumberOfStreams(2);
			//m_config->Release();
		}
*/    
		// Important! At this point, we advised out custom window AND now we
        // have access to DDrawObject related to it.
        
        CHECK_HR(hr = m_pWC->SetVideoClippingWindow(m_hwndApp));
  
        CHECK_HR(hr = m_pAlloc->QueryInterface(IID_IVMRMonitorConfig,
                                              (LPVOID*)&pMonConf));
        VMRMONITORINFO vmrMonInf;
        ZeroMemory( &vmrMonInf, sizeof(VMRMONITORINFO));
        DWORD nDevices = 0;

        CHECK_HR(hr = pMonConf->GetAvailableMonitors( &vmrMonInf, 1, &nDevices));
        m_hMonitor = vmrMonInf.hMon;
    }
    __finally 
    {        
        if (FAILED(hr)) 
        {
            SAFERELEASE( pMonConf );
            m_pWC = NULL;
            m_pPresenter = NULL;
            m_pAlloc = NULL;
        }
    }

    SAFERELEASE( pMonConf );
    
    return hr;
}

//-------------------------------------------------------------------------
//  InitializeEnvironment
//  creates default allocator-presenter and sets D3D environment
//-------------------------------------------------------------------------
HRESULT CMultiSAP::InitializeEnvironment()
{
    HRESULT hr;
//  m_hMonitor = MonitorFromWindow(m_hwndApp, MONITOR_DEFAULTTOPRIMARY);
    
    hr = CreateDefaultAllocatorPresenter();
    if (hr != S_OK)
        return hr;
    
    BITMAPINFOHEADER  bi = 
    {
        sizeof(BITMAPINFOHEADER),     // biSize
            m_uSurfaceWidth,          // biWidth
            m_uSurfaceHeight,         // biHeight
            1,                        // biPlanes
            0,                        // biBitCount
            BI_RGB,                   // biCompression
            0,                        // biSizeImage,
            0,                        // biXpelsPerMeter
            0,                        // biYPelsPerMeter
            0,                        // biClrUsed
            0                         // biClrImportant
    };
    VMRALLOCATIONINFO ai = 
    {
        AMAP_3D_TARGET,             // dwFlags
        &bi,                        // lpHdr
        NULL,                       // lpPicFmt
        {4, 3},                     // szAspectRatio
        1,                          // dwMinBuffers
        1,                          // dwMaxBuffers
        0,                          // dwInterlaceFlags
        {m_uSurfaceWidth, m_uSurfaceHeight}   // szNativeSize
    };
    
    DWORD dwBuffers = 0;
    LPDIRECTDRAWSURFACE7 lpDDSurf;
    hr = m_pAlloc->AllocateSurface(0, &ai, &dwBuffers, &lpDDSurf);
    if (hr != DD_OK)
        return hr;
    
    DDSURFACEDESC2 ddsd = {sizeof(DDSURFACEDESC2)};
    hr = lpDDSurf->GetSurfaceDesc(&ddsd);
    if (hr != DD_OK) {
        return hr;
    }
    
    //
    // Overlay surfaces have these flags set, we need to remove
    // these flags prior to calling GetAttachedSurface
    //
    ddsd.ddsCaps.dwCaps &= ~(DDSCAPS_FRONTBUFFER | DDSCAPS_VISIBLE);
    
    hr = lpDDSurf->GetAttachedSurface(&ddsd.ddsCaps, &m_lpBackBuffer);
    
    
    m_lpBackBuffer->GetDDInterface((LPVOID *)&m_lpDDObj);

	//hr = m_lpDDObj->SetCooperativeLevel(m_hwndApp, DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN);
    
    //
    // get the h/w caps for this device
    //
    INITDDSTRUCT(m_ddHWCaps);
    m_lpDDObj->GetCaps(&m_ddHWCaps, NULL);   
    
    //
    // Create the device. The device is created off of our back buffer, which
    // becomes the render target for the newly created device. Note that the
    // z-buffer must be created BEFORE the device
    //    
    m_pD3DHelper = new CD3DHelper(m_lpBackBuffer, &hr);
    if(m_pD3DHelper == NULL || hr != DD_OK)
    {
        if(m_pD3DHelper == NULL)
        {
            hr = E_OUTOFMEMORY;
        }
        delete m_pD3DHelper;
    }
    
    SetRect(&m_rcDst, 0, 0, m_uSurfaceWidth, m_uSurfaceHeight);
    
#ifdef SPARKLE
	m_pSparkle = new CSparkle(m_lpDDObj);
	if (m_pSparkle)
		m_pSparkle->InitializeSparkle();
#endif
    m_pAlphaBlt = new CAlphaBlt(m_lpBackBuffer, &hr);
    return hr;
}

//-------------------------------------------------------------------------
//  RepositionMovie
//  Updates video position in windowless mode
//-------------------------------------------------------------------------
void CMultiSAP::RepositionMovie()
{
    RECT rcPos;
    
    GetMoviePosition(&rcPos);
    PutMoviePosition(rcPos);
}

//-------------------------------------------------------------------------
//  GetMoviePosition
//-------------------------------------------------------------------------
void CMultiSAP::GetMoviePosition( RECT * prc)
{
    GetClientRect(m_hwndApp, prc);
}

//-------------------------------------------------------------------------
//  PutMoviePosition
//-------------------------------------------------------------------------
void CMultiSAP::PutMoviePosition(RECT rc)
{
    CAutoLock Lock(&m_AppImageLock);
    m_pWC->SetVideoPosition(NULL, &rc);
	PAINTSTRUCT Paint;
	RECT wRect;
	HDC hDC = BeginPaint(m_hwndApp, &Paint);
	GetClientRect(m_hwndApp, &wRect);
	// Erase if needed
	if (Paint.fErase)
	{
		FillRect(hDC, &wRect, (HBRUSH) GetStockObject(BLACK_BRUSH));
	}
	m_pWC->RepaintVideo(m_hwndApp, hDC);
	EndPaint(m_hwndApp, &Paint);
}

//-------------------------------------------------------------------------
//  RePaint
//-------------------------------------------------------------------------
void CMultiSAP::RePaint()
{
    m_pWC->RepaintVideo(NULL, NULL);
}

//-------------------------------------------------------------------------
//  SetFocus
//  add sound management here
//-------------------------------------------------------------------------
void CMultiSAP::SetFocus()
{
    CMovie *pmovie = m_movieList.GetSelectedMovie();

    if(pmovie && pmovie->m_Fg)
    {
        // Tell the resource manager that we are being made active.  This
        // will then cause the sound to switch to THE SELECTED MEDIA SOURCE.  
        // This is especially
        // important when playing audio only files as there is no other
        // playback window.
        IResourceManager* pResourceManager;
        
        HRESULT hr = pmovie->m_Fg->QueryInterface(IID_IResourceManager, 
                                                 (void**)&pResourceManager);
        
        if(SUCCEEDED(hr))
        {
            IUnknown* pUnknown;
            
            hr = pmovie->m_Fg->QueryInterface(IID_IUnknown, (void**)&pUnknown);
            
            if(SUCCEEDED(hr))
            {
                pResourceManager->SetFocus(pUnknown);
                pUnknown->Release();
            }
            
            pResourceManager->Release();
        }
    }
}

//-------------------------------------------------------------------------
//  ReleaseFocus
//  add sound management here
//-------------------------------------------------------------------------
void CMultiSAP::ReleaseFocus()
{
    CMovie *pmovie = m_movieList.GetSelectedMovie();

    if(pmovie && pmovie->m_Fg)
    {
        // Tell the resource manager that we are being made active.  This
        // will then cause the sound to switch to THE SELECTED MEDIA SOURCE.  
        // This is especially
        // important when playing audio only files as there is no other
        // playback window.
        IResourceManager* pResourceManager;
        
        HRESULT hr = pmovie->m_Fg->QueryInterface(IID_IResourceManager, 
                                                 (void**)&pResourceManager);
        
        if(SUCCEEDED(hr))
        {
            IUnknown* pUnknown;
            
            hr = pmovie->m_Fg->QueryInterface(IID_IUnknown, (void**)&pUnknown);
            
            if(SUCCEEDED(hr))
            {
                pResourceManager->ReleaseFocus(pUnknown);
                pUnknown->Release();
            }
            
            pResourceManager->Release();
        }
    }
}

//
//  COMMAND FUNCTIONS
//

//-------------------------------------------------------------------------
//      Name:   CmdAddMovie
//      Desc:   Processes command "add movie" from the parent dialog
//      Parameters:     (sMovieInfo *)lParam;
//      Return: 
//      Other:   1. Create CMovie
//               2. Add movie to the end of the list
//               3. Start playing
//-------------------------------------------------------------------------
void CMultiSAP::CmdAddMovie(sMovieInfo* pMovInf)
{
    
    HRESULT hr = S_OK;
    RECT rc;
    CMovie *pmovie = NULL;

    CAutoLock Lock(&m_AppImageLock);

    CmdAddEffect(eEffectFading, 2000, 300, 400, TRUE); // set next video effect "fading"
    
    if( m_pEffect ) // ping video effect change
    {
        m_pEffect->Finish();
    }
    
    if( !pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdAddMovie()\n"));
        return;
    }
    
    if( 0 == m_movieList.GetSize() )
    {
        ShowWindow( m_hwndApp, SW_SHOW);
    }
    
    pmovie = new CMovie;
    if( !pmovie )
    {
        OutputDebugStringA("Failed to allocate new movie in CmdAddMovie()\n");
        return;
    }
    pmovie->Initialize(pMovInf, this);

    if( FALSE == m_movieList.Add( pmovie ))
    {
        OutputDebugStringA("Failed to add new movie to the list in CmdAddMovie()\n");
        pmovie->Release();
        delete pmovie;
        return;
    }
        
    try
    {
        if( !m_movieList.GetMovie( pMovInf->pdwUserID) )
            throw;
        hr = m_movieList.GetMovie( pMovInf->pdwUserID)->OpenMovie();
    }
    catch(...)
    {
        pmovie->Release();
        delete pmovie;
        OutputDebugString(TEXT("Unhandled exception when trying to open the movie\n"));
        hr = E_POINTER;
    }
    
    if( FAILED(hr))
    {
        m_movieList.Delete( pMovInf->pdwUserID );

        if( m_bErrorMessage )
        {
            MessageBox(NULL, m_achErrorMessage, m_achErrorTitle, MB_ICONEXCLAMATION);
            m_bErrorMessage = false;
        }
        else
        {
#ifdef UNICODE
            swprintf( m_achErrorMessage, TEXT("Direct3D object returned error code 0x%08x.\r\n"), hr);
#else
            sprintf( m_achErrorMessage, TEXT("Direct3D object returned error code 0x%08x.\r\n"), hr);
#endif
            _tcsncat( m_achErrorMessage,  TEXT("Please use DirectX Error Lookup tool and verify DirectX\r\n")\
                                          TEXT("capabilities of your video driver. We are sorry for inconvenience.\r\n")\
                                          TEXT("You may want to try a different media file, or try a different video driver."), 2048);

            _tcsncpy( m_achErrorTitle, TEXT("Error when trying to render media file"), MAX_PATH);

            MessageBox(NULL, m_achErrorMessage, m_achErrorTitle, MB_ICONEXCLAMATION);
            m_bErrorMessage = false;
        }
        return;
    }

    GetMoviePosition(&rc);
    PutMoviePosition(rc);

    if( m_pEffect )
    {
        m_pEffect->Invalidate();
    }
	try
    {
        hr = PlayMovie(pMovInf->pdwUserID);
    }
    catch(...)
    {
        OutputDebugString(TEXT("Failed to start movie\n"));
        m_movieList.Delete( pMovInf->pdwUserID );
        hr = E_FAIL;
    }
    if( FAILED(hr))
    {
        m_movieList.Delete( pMovInf->pdwUserID );
    }
}

//-------------------------------------------------------------------------
//      Name:   CmdPlayMovie
//      Desc:   Processes command "play movie" from the parent dialog
//      Parameters:     (sMovieInfo *)lParam;
//      Return: 
//      Other:  just find this movie in the list and call its PlayMovie()
//-------------------------------------------------------------------------
void CMultiSAP::CmdPlayMovie(sMovieInfo* pMovInf)
{
    HRESULT hr = S_OK;
    
    if( NULL == pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdPlayMovie()\n"));
        return;
    }
    
    hr = PlayMovie( pMovInf->pdwUserID );
    if( FAILED(hr))
    {
        OutputDebugString(TEXT("Failed to play movie\n"));
    }
    
    return;
}

//-------------------------------------------------------------------------
//  CmdPauseMovie
//-------------------------------------------------------------------------
void CMultiSAP::CmdPauseMovie(sMovieInfo * pMovInf)
{
    int nVMR = -1;
    
    if( NULL == pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdPauseMovie()\n"));
        return;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdPauseMovie() received unrecognized UserID\n"));
        return;
    }
    
    OAFilterState State = pmovie->GetStateMovie();
    BOOL fPlaying = (State & State_Running);
    BOOL fPaused  = (State & State_Paused);
    
    if (fPlaying) 
    {
        pmovie->PauseMovie();
    }
    else if (fPaused) 
    {
        pmovie->PlayMovie();
    }
    
    return;
}

//-------------------------------------------------------------------------
//  CmdEjectMovie
//  
//  Function only sets "bDelete" flag for the movie and pings
//  videoeffect change
//-------------------------------------------------------------------------
void CMultiSAP::CmdEjectMovie(sMovieInfo * pMovInf)
{
    if( NULL == pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdPauseMovie()\n"));
        return;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdPauseMovie() received unrecognized UserID\n"));
        return;
    }   
    pmovie->m_bDelete = TRUE;

    CmdAddEffect(eEffectFading,2000, 300, 400, TRUE);
    
    if( m_pEffect )
    {
        m_pEffect->Finish();
    }
}

//-------------------------------------------------------------------------
//  CmdStopMovie
//-------------------------------------------------------------------------     
void CMultiSAP::CmdStopMovie(sMovieInfo * pMovInf)
{
    if( NULL == pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdStopMovie()\n"));
        return;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdStopMovie() received unrecognized UserID\n"));
        return;
    }
    
    pmovie->StopMovie();
    
    return;
}

//-------------------------------------------------------------------------
//  CmdExpandMovie
//  processes command "change selection" from the list box
//-------------------------------------------------------------------------
void CMultiSAP::CmdExpandMovie(sMovieInfo * pMovInf)
{
    CAutoLock Lock(&m_AppImageLock);

    if( NULL == pMovInf)
    {
        OutputDebugString(TEXT("Invalid parameter sent to CmdExpandMovie()\n"));
        return;
    }

    m_pdwNextSelectedMovie = pMovInf->pdwUserID;

    if( m_pEffect )
    {
        m_pEffect->Finish();
    }

    CmdAddEffect(eEffectFountain, 10, 10, 10, TRUE);

    return;
}

//-------------------------------------------------------------------------
//  CmdProcessDoubleClick
//  processes command "change selection" from the playback window
//-------------------------------------------------------------------------
void CMultiSAP::CmdProcessDoubleClick( int xPos, int yPos)
{
    if( !m_pEffect || eEffectStagePlaying != m_pEffect->GetStage() )
    {
        return;
    }

    RECT rect;
    GetClientRect( m_hwndApp, &rect );

    RECT rectRT = m_movieList.GetDefaultTarget();

    // given xPos, yPos are in client coordinates of the window;
    // transform then to client coordinates of the render target and find the movie

    float xPosRT = (float)xPos / (float)(WIDTH(&rect)) * (float)(WIDTH(&rectRT));
    float yPosRT = (float)yPos / (float)(HEIGHT(&rect)) * (float)(HEIGHT(&rectRT));

    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovieFromRTPoint( xPosRT, yPosRT);

    if( pmovie && pmovie->m_dwUserID != m_movieList.GetSelectedMovieID() )
    {
        m_pdwNextSelectedMovie = pmovie->m_dwUserID;
        if( m_pEffect )
        {
            m_pEffect->Finish();
        }

        CmdAddEffect(eEffectFountain, 10, 10, 10, TRUE);

        return;
    }
}

//-------------------------------------------------------------------------
//  CmdGetMovieState
//  
//  returns media control state of the movie (running, paused, or stopped)
//-------------------------------------------------------------------------
OAFilterState CMultiSAP::CmdGetMovieState(sMovieInfo* pMovInf)
{   
    if( !pMovInf )
    {
        OutputDebugString(TEXT("CmdNotifySelected received a wrong parameter\n"));
        return 0;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdNotifySelected received unrecognized UserID\n"));
        ZeroMemory( pMovInf, sizeof(sMovieInfo));
        return 0;
    }
    
    return pmovie->GetStateMovie();
}


//-------------------------------------------------------------------------
//  CmdSetMoviePosition
//
//  sets media position for the movie
//-------------------------------------------------------------------------
void CMultiSAP::CmdSetMoviePosition(sMovieInfo * pMovInf, REFTIME rtPos)
{
    if( !pMovInf )
    {
        OutputDebugString(TEXT("CmdNotifySelected received a wrong parameter\n"));
        return;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdNotifySelected received unrecognized UserID\n"));
        ZeroMemory( pMovInf, sizeof(sMovieInfo));
        return;
    }
    
    pmovie->SeekToPosition(rtPos, TRUE);
    return;
}

//-------------------------------------------------------------------------
//  CmdGetMoviePosition
//
//  gets media position of the movie
//-------------------------------------------------------------------------
REFTIME CMultiSAP::CmdGetMoviePosition(sMovieInfo * pMovInf)
{
    if( !pMovInf )
    {
        OutputDebugString(TEXT("CmdNotifySelected received a wrong parameter\n"));
        return (REFTIME)0;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdNotifySelected received unrecognized UserID\n"));
        ZeroMemory( pMovInf, sizeof(sMovieInfo));
        return (REFTIME)0;
    }
    
    return pmovie->GetCurrentPosition();
}

//-------------------------------------------------------------------------
//  CmdGetMovieDuration
// 
//  gets movie's duration, in   REFTIME
//-------------------------------------------------------------------------
REFTIME CMultiSAP::CmdGetMovieDuration(sMovieInfo * pMovInf)
{
    if( !pMovInf )
    {
        OutputDebugString(TEXT("CmdNotifySelected received a wrong parameter\n"));
        return (REFTIME)0;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdNotifySelected received unrecognized UserID\n"));
        ZeroMemory( pMovInf, sizeof(sMovieInfo));
        return (REFTIME)0;
    }
    
    return pmovie->GetDuration();
}

//-------------------------------------------------------------------------
//  CmdGetMovieFramesFlipped
//
//  returns number of delivered frames
//-------------------------------------------------------------------------
DWORD CMultiSAP::CmdGetMovieFramesFlipped(sMovieInfo* pMovInf) 
{   
    if( !pMovInf )
    {
        OutputDebugString(TEXT("CmdNotifySelected received a wrong parameter\n"));
        return 0;
    }
    
    CMovie *pmovie = NULL;
    pmovie = m_movieList.GetMovie( pMovInf->pdwUserID );
    
    if( NULL == pmovie)
    {
        OutputDebugString(TEXT("CmdNotifySelected received unrecognized UserID\n"));
        return 0;
    }
    
    return pmovie->m_dwFrameCount;
}

//-------------------------------------------------------------------------
//  CmdAddEffect
//
//  adds new video effect to the effect queue
//-------------------------------------------------------------------------
void CMultiSAP::CmdAddEffect( eEffect effect, 
                              DWORD dwStartTime, 
                              LONG lPlayTime, 
                              DWORD dwEndTime, 
                              BOOL bAddFirst /*= FALSE*/)
{
    BOOL bRes = TRUE;
    CEffect *pEffect = NULL;

    switch( effect )
    {
        case eEffectDefault:
            pEffect = new CEffect(eEffectDefault);
            break;
        case eEffectStillArrangement:
            pEffect = new CEffectStillArrangement;
            break;
        case eEffectFading:
            pEffect = new CEffectFading;
            break;
        case eEffectFountain:
            pEffect = new CEffectFountain;
            break;
        default:
            OutputDebugStringA("Unsupported effect in CMultiSAP::CmdAddEffect\n");
            return;
    }

    if( !pEffect )
    {
        OutputDebugStringA("Failed to allocate new effect in CMultiSAP::CmdAddEffect\n");
        return;
    }

    HRESULT hr = pEffect->Initialize( &m_movieList, dwStartTime, lPlayTime, dwEndTime );
    if( FAILED( hr))
    {
        OutputDebugStringA("Failed to initialize a new effect\n");
        delete pEffect;
        return;
    }

    if( bAddFirst )
    {
        bRes = m_EffectQueue.AddLast( pEffect );
    }
    else
    {
        bRes = m_EffectQueue.AddFirst( pEffect );
    }
    if( FALSE == bRes )
    {
        OutputDebugStringA("Failed to add a new effect to the queue\n");
        delete pEffect;
        return;
    }
}

//-------------------------------------------------------------------------
//      Name:   CmdQuit
//      Desc:   correct termination of this thread upon the request from the dialog
//      Parameters:     
//      Return: 
//      Other:  (1) Stop all movies
//              (2) Set quit event
//-------------------------------------------------------------------------
void CMultiSAP::CmdQuit(sMovieInfo * pMovInf)
{
    for( int i=0; i<m_movieList.GetSize(); i++)
    {
        CMovie *pmovie = m_movieList.GetMovieByIndex(i);
        if( pmovie )
        {
            pmovie->PauseMovie();
            pmovie->StopMovie();
        }
    }
    
    return;
}

#if 0
void CMultiSAP::CmdAddMovieEx( sMovieInfo* pMovInf, int index )
{
	HRESULT hr = S_OK;
	RECT rc;
	CMovie *pmovie = NULL;
	CMovieList * movieList = &m_movieListArray[index];

	CAutoLock Lock(&m_AppImageLock);

	CmdAddEffect(eEffectFading, 2000, 300, 400, TRUE); // set next video effect "fading"

	if( m_pEffect ) // ping video effect change
	{
		m_pEffect->Finish();
	}

	if( !pMovInf)
	{
		OutputDebugString(TEXT("Invalid parameter sent to CmdAddMovie()\n"));
		return;
	}

	if( 0 == movieList->GetSize() )
	{
		ShowWindow( m_hwndApp, SW_SHOW);
	}

	pmovie = new CMovie;
	if( !pmovie )
	{
		OutputDebugStringA("Failed to allocate new movie in CmdAddMovie()\n");
		return;
	}
	pmovie->Initialize(pMovInf, this);

	if( FALSE == movieList->Add( pmovie ))
	{
		OutputDebugStringA("Failed to add new movie to the list in CmdAddMovie()\n");
		pmovie->Release();
		delete pmovie;
		return;
	}
/*
	try
	{
		if( !movieList->GetMovie( pMovInf->pdwUserID) )
			throw;
		hr = movieList->GetMovie( pMovInf->pdwUserID)->OpenMovie();
	}
	catch(...)
	{
		pmovie->Release();
		delete pmovie;
		OutputDebugString(TEXT("Unhandled exception when trying to open the movie\n"));
		hr = E_POINTER;
	}

	if( FAILED(hr))
	{
		movieList->Delete( pMovInf->pdwUserID );

		if( m_bErrorMessage )
		{
			MessageBox(NULL, m_achErrorMessage, m_achErrorTitle, MB_ICONEXCLAMATION);
			m_bErrorMessage = false;
		}
		else
		{
#ifdef UNICODE
			swprintf( m_achErrorMessage, TEXT("Direct3D object returned error code 0x%08x.\r\n"), hr);
#else
			sprintf( m_achErrorMessage, TEXT("Direct3D object returned error code 0x%08x.\r\n"), hr);
#endif
			_tcsncat( m_achErrorMessage,  TEXT("Please use DirectX Error Lookup tool and verify DirectX\r\n")\
				TEXT("capabilities of your video driver. We are sorry for inconvenience.\r\n")\
				TEXT("You may want to try a different media file, or try a different video driver."), 2048);

			_tcsncpy( m_achErrorTitle, TEXT("Error when trying to render media file"), MAX_PATH);

			MessageBox(NULL, m_achErrorMessage, m_achErrorTitle, MB_ICONEXCLAMATION);
			m_bErrorMessage = false;
		}
		return;
	}

	GetMoviePosition(&rc);
	PutMoviePosition(rc);

	if( m_pEffect )
	{
		m_pEffect->Invalidate();
	}
	try
	{
		hr = PlayMovie(pMovInf->pdwUserID);
	}
	catch(...)
	{
		OutputDebugString(TEXT("Failed to start movie\n"));
		m_movieList.Delete( pMovInf->pdwUserID );
		hr = E_FAIL;
	}

	if( FAILED(hr))
	{
		m_movieList.Delete( pMovInf->pdwUserID );
	}
*/
}

typedef struct tagSmoothThreadParam
{
	CMultiSAP * pSAP;
	int         index;
}SmoothThreadParam;

SmoothThreadParam g_param;


UINT CMultiSAP::SmoothPlayThread(LPVOID param)
{
	SmoothThreadParam * STParam = (SmoothThreadParam*)param;
	CMultiSAP * pSAP             = STParam->pSAP;
	int         index            = STParam->index;
	HRESULT     hr;
	RECT        rc;

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	for( int i = 0; i < pSAP->m_movieListArray[index].GetSize(); ++i )
	{
		CMovie * pMovie = pSAP->m_movieListArray[index].GetMovieByIndex(i);
		//PostMessage(AfxGetMainWnd()->GetSafeHwnd(), WM_PLAY, (WPARAM)pMovie, 0);
		try
		{
			hr = pMovie->OpenMovie();
		}
		catch(...)
		{
			pMovie->Release();
			delete pMovie;
			OutputDebugString(TEXT("Unhandled exception when trying to open the movie\n"));
			hr = E_POINTER;
		}
#if 0
		if( FAILED(hr))
		{
			movieList->Delete( pMovInf->pdwUserID );

			if( m_bErrorMessage )
			{
				MessageBox(NULL, m_achErrorMessage, m_achErrorTitle, MB_ICONEXCLAMATION);
				m_bErrorMessage = false;
			}
			else
			{
#ifdef UNICODE
				swprintf( m_achErrorMessage, TEXT("Direct3D object returned error code 0x%08x.\r\n"), hr);
#else
				sprintf( m_achErrorMessage, TEXT("Direct3D object returned error code 0x%08x.\r\n"), hr);
#endif
				_tcsncat( m_achErrorMessage,  TEXT("Please use DirectX Error Lookup tool and verify DirectX\r\n")\
					TEXT("capabilities of your video driver. We are sorry for inconvenience.\r\n")\
					TEXT("You may want to try a different media file, or try a different video driver."), 2048);

				_tcsncpy( m_achErrorTitle, TEXT("Error when trying to render media file"), MAX_PATH);

				MessageBox(NULL, m_achErrorMessage, m_achErrorTitle, MB_ICONEXCLAMATION);
				m_bErrorMessage = false;
			}
			return;
		}
#endif
		pSAP->GetMoviePosition(&rc);
		pSAP->PutMoviePosition(rc);

//		if( m_pEffect )
//		{
//			m_pEffect->Invalidate();
//		}
		try
		{
			hr = pMovie->PlayMovie();
		}
		catch(...)
		{
			OutputDebugString(TEXT("Failed to start movie\n"));
			//m_movieList.Delete( pMovInf->pdwUserID );
			hr = E_FAIL;
		}

//		long event;
//		pMovie->m_Me->WaitForCompletion(INFINITE, &event);

//		if( FAILED(hr))
//		{
//			m_movieList.Delete( pMovInf->pdwUserID );
//		}

	}

	return 0;
}

void CMultiSAP::CmdPlayMovieEx( sMovieInfo* pMovInf, int index )
{
	if( index < 0 || index > 8 )
		return;

	if( !m_movieListThread[index] )
	{
		m_movieListThread[index] = TRUE;
		g_param.pSAP  = this;
		g_param.index = index;
		AfxBeginThread( SmoothPlayThread, &g_param );
	}
}

#endif

//////////////////////////////////////////////////////////////////////////
// add by egg.
LONG CMultiSAP::CreateVideoGroup()
{
//	size_t nCount = m_videoGroups.GetCount();
//	if ( nCount < 8)
	//	{

	CVideoGroup* pVideoGroup = new CVideoGroup();
	pVideoGroup->m_uSurfaceHeight = m_uSurfaceHeight;
	pVideoGroup->m_uSurfaceWidth  = m_uSurfaceWidth;
	pVideoGroup->m_pD3DHelper     = m_pD3DHelper;
	pVideoGroup->m_rcDst          = m_rcDst;
	pVideoGroup->m_pMultiSAP      = this;
	m_videoGroups.AddTail(pVideoGroup);
	EnterCriticalSection(&m_videoGroupsCS);
	m_drawList.AddHead(pVideoGroup);
	LeaveCriticalSection(&m_videoGroupsCS);
	return pVideoGroup->GetObjectID();
//	}
//	return -1;
}

LONG CMultiSAP::Create_Dy_Ef_Bmp_Group()
{
	CDynaEfBmpGroup * pGroup = new CDynaEfBmpGroup();

	m_dy_ef_bmp_Group[pGroup->GetObjectID()] = pGroup;
	EnterCriticalSection(&m_videoGroupsCS);
	m_drawList.AddHead(pGroup);
	LeaveCriticalSection(&m_videoGroupsCS);
	return pGroup->GetObjectID();
}

LONG CMultiSAP::AddDynamicEffectBmp(ULONG uGroupID, LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle, ULONG uDelay)
{
	CDynaEfBmpGroup * pGroup;
	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.find(uGroupID);
	//if( m_dy_ef_bmp_Group.Lookup(uGroupID, pGroup) )

	if( iter != m_dy_ef_bmp_Group.end() )
	{
		pGroup = iter->second;
		CEffectBitmapEx * pEffectBitmap = new CEffectBitmapEx();


		if ( pEffectBitmap->SetBitmap(sBitmapFilePath, uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, uDrawStyle, uDelay, m_hwndApp) == -1)
			return -1;

		pEffectBitmap->m_pMultiSAP = this;
		pEffectBitmap->SetAlphaBlt(m_pAlphaBlt);

		HRESULT hr = DD_OK;
		//	if( !m_lpDDSBitmapCache ) 
		IDirectDrawSurface7* pDDS = NULL;
		//	hr = DDARGB32SurfaceInit(&m_lpDDSBitmapCache, TRUE, 640, 480);
		HBITMAP hBmp;
		Color backColor;

		BITMAP bm;

		if (uOriginalSize == 1)
		{
			pEffectBitmap->m_pBitmap->GetHBITMAP(backColor, &hBmp);
			GetObject( hBmp, sizeof(BITMAP), &bm );
		}

		// Get the bitmap structure (to extract width, height, and bpp)


		ULONG Width, Height;
		if( uOriginalSize == 1 )
		{

			Width  = bm.bmWidth;
			Height = bm.bmHeight;
		}
		else
		{
			Width  = uWidth;
			Height = uHeight;
		}

		hr = DDARGB32SurfaceInit(&pDDS, TRUE, Width, Height);
		if(hr == DD_OK)
		{

			pEffectBitmap->SetSurface(pDDS);
		}

		pGroup->AddBitmap(pEffectBitmap);
		return pEffectBitmap->GetObjectID();
	}
	return -1;
}


LONG CMultiSAP::InsertDynamicEffectBmp(ULONG uGroupID, ULONG uWhere, LPCTSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle, ULONG uDelay)
{
	CDynaEfBmpGroup * pGroup;
	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.find(uGroupID);

	if( iter != m_dy_ef_bmp_Group.end() )
	{
		pGroup = iter->second;
		CEffectBitmapEx * pEffectBitmap = new CEffectBitmapEx();


		if ( pEffectBitmap->SetBitmap(sBitmapFilePath, uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, uDrawStyle, uDelay, m_hwndApp) == -1)
			return -1;

		pEffectBitmap->m_pMultiSAP = this;
		pEffectBitmap->SetAlphaBlt(m_pAlphaBlt);

		HRESULT hr = DD_OK;
		//	if( !m_lpDDSBitmapCache ) 
		IDirectDrawSurface7* pDDS = NULL;
		//	hr = DDARGB32SurfaceInit(&m_lpDDSBitmapCache, TRUE, 640, 480);
		HBITMAP hBmp;
		Color backColor;

		BITMAP bm;

		if (uOriginalSize == 1)
		{
			pEffectBitmap->m_pBitmap->GetHBITMAP(backColor, &hBmp);
			GetObject( hBmp, sizeof(BITMAP), &bm );
		}

		// Get the bitmap structure (to extract width, height, and bpp)


		ULONG Width, Height;
		if( uOriginalSize == 1 )
		{

			Width  = bm.bmWidth;
			Height = bm.bmHeight;
		}
		else
		{
			Width  = uWidth;
			Height = uHeight;
		}

		hr = DDARGB32SurfaceInit(&pDDS, TRUE, Width, Height);
		if(hr == DD_OK)
		{

			pEffectBitmap->SetSurface(pDDS);
		}

		pGroup->InsertBitmap(uWhere, pEffectBitmap);
		return pEffectBitmap->GetObjectID();
	}
	return -1;
}

LONG CMultiSAP::AddVideoFile(ULONG uGroupID, LPCTSTR sFilePathName)
{
//	if ( uGroupID < 0 || uGroupID > 8 )
//		return GROUP_EXCEED;

	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		sMovieInfo movieInfo;
		CVideoObject* pVideoObject = new CVideoObject();

		USES_CONVERSION;
		wcscpy( movieInfo.achPath, T2W(sFilePathName) );
		movieInfo.pdwUserID = IDGenerator::GetInstance().GenID();
		pVideoObject->Initialize(&movieInfo, this);

//		CmdAddEffect(eEffectFading, 2000, 300, 400, TRUE); // set next video effect "fading"

		if( m_pEffect ) // ping video effect change
		{
			m_pEffect->Finish();
		}
		m_movieList.Add( pVideoObject );

		HRESULT hr = pVideoObject->OpenMovie();
		if( FAILED(hr) )
		{
			//DDCAPS_DX7 hwCaps;
			//ZeroMemory( &hwCaps, sizeof(DDCAPS_DX7));
			//hwCaps.dwSize = sizeof(DDCAPS_DX7);
			//m_lpDDObj->GetCaps( &hwCaps, NULL );


			//char msg[100] = {0};
			//sprintf(msg, "Total Video Memory:%d   Free Video Memory:%d", hwCaps.dwVidMemTotal, hwCaps.dwVidMemFree);
			//MessageBox(NULL, msg, "free", MB_OK);


			m_movieList.Delete(pVideoObject->m_dwUserID);
			delete pVideoObject;
			return -1;
		}

		RECT rc;
		GetMoviePosition(&rc);
		PutMoviePosition(rc);

		if( m_pEffect )
		{
			m_pEffect->Invalidate();
		}

		// not to play at this time
		//pVideoObject->PlayMovie();
		pVideoGroup->AddVideoObject(pVideoObject);
		return pVideoObject->GetObjectID();
	}
	return -1;
}

LONG CMultiSAP::DelVideoFile(ULONG uGroupID, ULONG uFileID)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->DelVideoFile(uFileID);
	}
	return -1;
}

LONG CMultiSAP::DelVideoGroup(ULONG uGroupID)
{
	EnterCriticalSection(&m_videoGroupsCS);
	int ret = -1;
	POSITION pos = m_videoGroups.GetHeadPosition();
	while (pos)
	{
		// Silly BUG!!!!!
		POSITION RemovePos = pos;
		CVideoGroup* pVideoGroup = m_videoGroups.GetNext(pos);
		if (pVideoGroup->GetObjectID() == uGroupID)
		{
			//delete pVideoGroup;
			m_videoGroups.RemoveAt(RemovePos);
			ret = 0;
			break;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	pos = m_drawList.GetHeadPosition();
	while (pos)
	{
		POSITION RemovePos = pos;
		CAnsoplyObject* pObject = m_drawList.GetNext(pos);
		if (pObject->GetObjectID() == uGroupID)
		{
			delete pObject;
			m_drawList.RemoveAt(RemovePos);
			ret = 0;
			break;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return ret;
}

LONG CMultiSAP::SetPlayMode(ULONG uGroupID, ULONG uPlayMode)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->SetPlayMode(uPlayMode);
	}
	CDynamicBitmap * pDynamicBitmap;
	if( m_dynamicBitmap.Lookup(uGroupID, pDynamicBitmap) )
	{
		if (PLAY_THROUGH == uPlayMode || PLAY_LOOP == uPlayMode)
		{
			pDynamicBitmap->m_playType = (PLAY_TYPE)uPlayMode;
			if( PLAY_THROUGH == uPlayMode )
				pDynamicBitmap->m_uPlayTimes = 0;
			return 0;
		}
	}

	CBitmapObject * pBitmap;
	if( m_bitmapObject.Lookup(uGroupID, pBitmap) )
	{
		if (PLAY_THROUGH == uPlayMode || PLAY_LOOP == uPlayMode)
		{
			CEffectBitmap * pEB = static_cast<CEffectBitmap*>(pBitmap);
			pEB->m_bPlayEnd = FALSE;
			pBitmap->m_playType = (PLAY_TYPE)uPlayMode;	
			if( PLAY_THROUGH == uPlayMode )
				pBitmap->m_uPlayTimes = 0;
			return 0;
		}
	}

	CTextObject * pText;
	if( m_textObject.Lookup(uGroupID, pText) )
	{
		if (PLAY_THROUGH == uPlayMode || PLAY_LOOP == uPlayMode)
		{
			CEffectText * pET = static_cast<CEffectText*>(pText);
			pET->m_bPlayEnd = FALSE;
			pText->m_playType = (PLAY_TYPE)uPlayMode;
			if( PLAY_THROUGH == uPlayMode )
				pText->m_uPlayTimes = 0;
			return 0;
		}
	}

	CDynamicEffectBitmap * pDEBitmap;
	if( m_dynamicEffectBitmap.Lookup(uGroupID, pDEBitmap) )
	{
		if (PLAY_THROUGH == uPlayMode || PLAY_LOOP == uPlayMode)
		{
			pDEBitmap->m_bPlayEnd = FALSE;
			pDEBitmap->m_playType = (PLAY_TYPE)uPlayMode;
			if( PLAY_THROUGH == uPlayMode )
				pDEBitmap->m_uPlayTimes = 0;
			return 0;
		}
	}
	return -1;
}

LONG CMultiSAP::Play(ULONG uGroupID)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->Play();
	}

	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		if( pGroup->GetObjectID() == uGroupID )
		{
			pGroup->m_bPlay = TRUE;
			return 0;
		}
	}

	std::map<ULONG, CEffectTextGroup*>::iterator itertext = m_EffectTextGroup.begin();
	for( ; itertext != m_EffectTextGroup.end(); ++itertext )
	{
		CEffectTextGroup * pGroup = itertext->second;
		if( pGroup->GetObjectID() == uGroupID )
		{
			pGroup->m_bPlay = TRUE;
			return 0;
		}
	}
	return -1;
}

LONG CMultiSAP::Next(ULONG uGroupID)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->Next();
	}
	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		if( pGroup->GetObjectID() == uGroupID )
		{
			if( pGroup->m_iter != pGroup->m_effectbmplist.end() )
			{
				pGroup->m_iter++;
				if( pGroup->m_iter != pGroup->m_effectbmplist.end() )
				{
					CEffectBitmapEx * pBitmap = *pGroup->m_iter;
					pBitmap->m_nProgress = 0;
					pBitmap->Clear();
				}
			}
			return 0;
		}
	}

	std::map<ULONG, CEffectTextGroup*>::iterator itertext = m_EffectTextGroup.begin();
	for( ; itertext != m_EffectTextGroup.end(); ++itertext )
	{
		CEffectTextGroup * pGroup = itertext->second;
		if( pGroup->GetObjectID() == uGroupID )
		{
			if( pGroup->m_iter != pGroup->m_effectextlist.end() )
			{
				pGroup->m_iter++;
				if( pGroup->m_iter != pGroup->m_effectextlist.end() )
				{
					CEffectTextEx * pText = *pGroup->m_iter;
					pText->m_nProgress = 0;
					pText->Clear();
				}
			}
			return 0;
		}
	}
	return -1;
}

LONG CMultiSAP::Previous(ULONG uGroupID)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->Previous();
	}
	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		if( pGroup->GetObjectID() == uGroupID )
		{
			if( pGroup->m_iter != pGroup->m_effectbmplist.begin() )
			{
				pGroup->m_iter--;
				//if( pGroup->m_iter != pGroup->m_effectbmplist.begin() )
				{
					CEffectBitmapEx * pBitmap = *pGroup->m_iter;
					pBitmap->m_nProgress = 0;
					pBitmap->Clear();
				}
			}

			return 0;
		}
	}

	std::map<ULONG, CEffectTextGroup*>::iterator itertext = m_EffectTextGroup.begin();
	for( ; itertext != m_EffectTextGroup.end(); ++itertext )
	{
		CEffectTextGroup * pGroup = itertext->second;
		if( pGroup->GetObjectID() == uGroupID )
		{
			if( pGroup->m_iter != pGroup->m_effectextlist.end() )
			{
				pGroup->m_iter++;
				if( pGroup->m_iter != pGroup->m_effectextlist.end() )
				{
					CEffectTextEx * pText = *pGroup->m_iter;
					pText->m_nProgress = 0;
					pText->Clear();
				}
			}
			return 0;
		}
	}
	return -1;
}

LONG CMultiSAP::Seek(ULONG uGroupID, ULONG uPosition)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->Seek(uPosition);
	}
	return -1;
}

LONG CMultiSAP::SetPlayRate(ULONG uGroupID, DOUBLE dRate)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->SetRate(dRate);
	}
	return -1;
}

LONG CMultiSAP::Pause(ULONG uGroupID)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		pVideoGroup->Pause();
		return 0;
	}

	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		if( pGroup->GetObjectID() == uGroupID )
		{
			pGroup->m_bPlay = FALSE;
			return 0;
		}
	}

	std::map<ULONG, CEffectTextGroup*>::iterator itertext = m_EffectTextGroup.begin();
	for( ; itertext != m_EffectTextGroup.end(); ++itertext )
	{
		CEffectTextGroup * pGroup = itertext->second;
		if( pGroup->GetObjectID() == uGroupID )
		{
			pGroup->m_bPlay = FALSE;
			return 0;
		}
	}
	return -1;
}

LONG CMultiSAP::Stop(ULONG uGroupID)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		pVideoGroup->Stop();
		return 0;
	}

	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		if( pGroup->GetObjectID() == uGroupID )
		{
			pGroup->m_bPlay = FALSE;
			CEffectBitmapEx * pBitmap = *pGroup->m_iter;
			pBitmap->Clear();
			pBitmap->m_nProgress = 0;
			pGroup->m_iter = pGroup->m_effectbmplist.begin();
			return 0;
		}
	}

	std::map<ULONG, CEffectTextGroup*>::iterator itertext = m_EffectTextGroup.begin();
	for( ; itertext != m_EffectTextGroup.end(); ++itertext )
	{
		CEffectTextGroup * pGroup = itertext->second;
		if( pGroup->GetObjectID() == uGroupID )
		{
			pGroup->m_bPlay = FALSE;
			CEffectTextEx * pText = *pGroup->m_iter;
			pText->Clear();
			pText->m_nProgress = 0;
			pGroup->m_iter = pGroup->m_effectextlist.begin();
			return 0;
		}
	}

	return -1;
}


LONG CMultiSAP::SetBitmap(
				  LPCTSTR sBitmapFilePath,
				  ULONG uAlpha,
				  ULONG uTransparentColor,   
				  ULONG uX,
				  ULONG uY,
				  ULONG uWidth,
				  ULONG uHeight,
				  ULONG uOriginalSize
				  )
{
	CBitmapObject* pBitmapObject = new CBitmapObject();

	if ( pBitmapObject->SetBitmap(sBitmapFilePath, uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize) == -1)
		return -1;

	pBitmapObject->m_pMultiSAP = this;
	pBitmapObject->SetAlphaBlt(m_pAlphaBlt);

	HRESULT hr = DD_OK;
//	if( !m_lpDDSBitmapCache ) 
	IDirectDrawSurface7* pDDS = NULL;
//	hr = DDARGB32SurfaceInit(&m_lpDDSBitmapCache, TRUE, 640, 480);
	HBITMAP hBmp;
	Color backColor;

	BITMAP bm;

	if (uOriginalSize == 1)
	{
		pBitmapObject->m_pBitmap->GetHBITMAP(backColor, &hBmp);
		GetObject( hBmp, sizeof(BITMAP), &bm );
	}

	// Get the bitmap structure (to extract width, height, and bpp)


	ULONG Width, Height;
	if( uOriginalSize == 1 )
	{

		Width  = bm.bmWidth;
		Height = bm.bmHeight;
	}
	else
	{
		Width  = uWidth;
		Height = uHeight;
	}

	hr = DDARGB32SurfaceInit(&pDDS, TRUE, Width, Height);
	if(hr == DD_OK)
	{
		HDC hdcDest;
//		m_lpDDSBitmapCache->GetDC(&hdcDest);
		pDDS->GetDC(&hdcDest);

		// Get a DC for the bitmap
		HDC hdcBitmap = CreateCompatibleDC( NULL );
		if( NULL == hdcBitmap )
			return -1;

		if( uOriginalSize == 1)
		{
			::SelectObject( hdcBitmap, hBmp );
			BitBlt( hdcDest, 0, 0, Width, Height, hdcBitmap, 0, 0, SRCCOPY );
		}
		else
		{
			USES_CONVERSION;
			Bitmap originalBMP(T2W(sBitmapFilePath));
			Graphics g(hdcDest);
			g.DrawImage(&originalBMP, Rect(0, 0, Width, Height), 0, 0, 
				originalBMP.GetWidth(), originalBMP.GetHeight(), UnitPixel, NULL );
		}

		if( uOriginalSize == 1)
		{
			DeleteObject( hBmp );
		}
		pDDS->ReleaseDC(hdcDest);

		DWORD dwFlags = D3DTEXTR_TRANSPARENTWHITE;
		if( dwFlags & (D3DTEXTR_TRANSPARENTWHITE|D3DTEXTR_TRANSPARENTBLACK) )
		{
			// Lock the texture surface
			DDSURFACEDESC2 ddsdAlpha={0};
			ddsdAlpha.dwSize = sizeof(ddsdAlpha);
			pDDS->Lock( NULL, &ddsdAlpha, 0, NULL );

			//DWORD dwAlphaMask = ddsdAlpha.ddpfPixelFormat.dwRGBAlphaBitMask;
			DWORD dwAlphaMask = uAlpha << 24;
			DWORD dwRGBMask   = ( ddsdAlpha.ddpfPixelFormat.dwRBitMask |
				ddsdAlpha.ddpfPixelFormat.dwGBitMask |
				ddsdAlpha.ddpfPixelFormat.dwBBitMask );
			//DWORD dwColorkey  = 0x00000000; // Colorkey on black
			DWORD dwColorkey  = uTransparentColor;

			//if( dwFlags & D3DTEXTR_TRANSPARENTWHITE )
			//	dwColorkey = dwRGBMask;     // Colorkey on white

			// Add an opaque alpha value to each non-colorkeyed pixel
			for( DWORD y = 0; y < Height; y++ )
			{
				WORD*  p16 =  (WORD*)((BYTE*)ddsdAlpha.lpSurface + y*ddsdAlpha.lPitch);
				DWORD* p32 = (DWORD*)((BYTE*)ddsdAlpha.lpSurface + y*ddsdAlpha.lPitch);

				for( DWORD x = 0; x < Width; x++ )
				{
					if( ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 16 )
					{
						if( ( *p16 &= dwRGBMask ) != dwColorkey )
							*p16 |= dwAlphaMask;
						p16++;
					}
					if( ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 32 || ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 24)
					{
						if( ( *p32 &= dwRGBMask ) != dwColorkey )
							*p32 |= dwAlphaMask;
						p32++;
					}
				}
			}
			pDDS->Unlock( NULL );
			DeleteDC( hdcBitmap );
			pDDS->ReleaseDC(hdcDest);
		}
		pDDS->ReleaseDC(hdcDest);
		m_bitmapObject[pBitmapObject->GetObjectID()] = pBitmapObject;
		pBitmapObject->SetSurface(pDDS);

		EnterCriticalSection(&m_videoGroupsCS);
		m_drawList.AddHead(pBitmapObject);
		LeaveCriticalSection(&m_videoGroupsCS);
		return pBitmapObject->GetObjectID();
	}

	return -1;
}


CVideoGroup * CMultiSAP::FindGroup( ULONG uGroupID )
{
	POSITION pos = m_videoGroups.GetHeadPosition();
	while (pos)
	{
		CVideoGroup* pVideoGroup = m_videoGroups.GetNext(pos);
		if (pVideoGroup->GetObjectID() == uGroupID)
		{
			return pVideoGroup;
		}
	}
	return NULL;
}

LONG CMultiSAP::BringToFront(ULONG uGroupID)
{
/*	POSITION pos = m_videoGroups.GetHeadPosition();
	while (pos)
	{
		CVideoGroup* pVideoGroup = m_videoGroups.GetNext(pos);
		if (pVideoGroup->GetObjectID() == uGroupID)
		{
			m_videoGroups.MoveToHead(pos);
			break;
		}
*/
	EnterCriticalSection(&m_videoGroupsCS);
	POSITION pos = m_drawList.GetHeadPosition();
	while( pos )
	{
		POSITION tempPos = pos;
		CAnsoplyObject * pObject = m_drawList.GetNext( pos );
		if (pObject->GetObjectID() == uGroupID)
		{
			m_drawList.MoveToHead(tempPos);
			break;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return 0;
}

LONG CMultiSAP::SendToBack(ULONG uGroupID)
{
/*	POSITION pos = m_videoGroups.GetHeadPosition();
	while (pos)
	{
		CVideoGroup* pVideoGroup = m_videoGroups.GetNext(pos);
		if (pVideoGroup->GetObjectID() == uGroupID)
		{
			m_videoGroups.MoveToTail(pos);
			break;
		}
	}
*/
	EnterCriticalSection(&m_videoGroupsCS);
	POSITION pos = m_drawList.GetHeadPosition();
	while( pos )
	{
		POSITION tempPos = pos;
		CAnsoplyObject * pObject = m_drawList.GetNext( pos );
		if (pObject->GetObjectID() == uGroupID)
		{
			m_drawList.MoveToTail(tempPos);
			break;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return 0;
}

LONG CMultiSAP::BringUp(ULONG uGroupID)
{
/*	for ( int i = 0; i < m_videoGroups.GetCount(); i++ )
	{
		CVideoGroup* pVideoGroup = m_videoGroups.GetAt(m_videoGroups.FindIndex(i));
		if ( pVideoGroup->GetObjectID() == uGroupID )
		{
			if (i != 0)
			{
				m_videoGroups.SwapElements( m_videoGroups.FindIndex(i), 
											m_videoGroups.FindIndex(i - 1) );
			}
			break;
		}
	}

	for ( int i = 0; i < m_drawList.GetCount(); i++ )
	{
		CAnsoplyObject * pObject = m_drawList.GetAt(m_drawList.FindIndex(i));
		int j = 0;
	}*/
	EnterCriticalSection(&m_videoGroupsCS);
	for ( int i = 0; i < m_drawList.GetCount(); i++ )
	{
		CAnsoplyObject * pObject = m_drawList.GetAt(m_drawList.FindIndex(i));
		if ( pObject->GetObjectID() == uGroupID )
		{
			if (i != 0)
			{
				m_drawList.SwapElements( m_drawList.FindIndex(i), 
					m_drawList.FindIndex(i - 1) );
			}
			break;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return 0;
}

LONG CMultiSAP::SendBack (ULONG uGroupID)
{
/*	for ( int i = 0; i < m_videoGroups.GetCount(); i++ )
	{
		CVideoGroup* pVideoGroup = m_videoGroups.GetAt(m_videoGroups.FindIndex(i));
		if ( pVideoGroup->GetObjectID() == uGroupID )
		{
			if (i != m_videoGroups.GetCount() - 1)
			{
				m_videoGroups.SwapElements( m_videoGroups.FindIndex(i), 
											m_videoGroups.FindIndex(i + 1) );
			}
			break;
		}
	}
*/
	EnterCriticalSection(&m_videoGroupsCS);
	for ( int i = 0; i < m_drawList.GetCount(); i++ )
	{
		CAnsoplyObject * pObject = m_drawList.GetAt(m_drawList.FindIndex(i));
		if ( pObject->GetObjectID() == uGroupID )
		{
			if (i != m_drawList.GetCount() - 1)
			{
				m_drawList.SwapElements( m_drawList.FindIndex(i), 
					m_drawList.FindIndex(i + 1) );
			}
			break;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return 0;
}

CVideoGroup * CMultiSAP::GetFirstGroup( ULONG & uGroupID )
{
	return 0;
}

CVideoGroup * CMultiSAP::GetNextGroup( ULONG & uGroupID )
{
	return 0;
}

LONG CMultiSAP::GetVideoGroupZOrder(ULONG uGroupID, ULONG * uZOrder)
{
	ULONG uCount = 0;
	POSITION pos = m_videoGroups.GetHeadPosition();
	while (pos)
	{
		CVideoGroup* pVideoGroup = m_videoGroups.GetNext(pos);
		if (pVideoGroup->GetObjectID() == uGroupID)
		{
			*uZOrder = uCount;
			return 0;
		}
		uCount++;
	}
	return -1;
}

LONG CMultiSAP::SelectVideoGroup(LONG cX, LONG cY, ULONG* uGroupID)
{
	POSITION pos = m_videoGroups.GetHeadPosition();
	while (pos)
	{
		CVideoGroup* pVideoGroup = m_videoGroups.GetNext(pos);
		if (pVideoGroup->SelectGroup(cX, cY))
		{
			*uGroupID = pVideoGroup->GetObjectID();
			return 0;
		}
	}
	return -1;
}


LONG CMultiSAP::SetVideoPosAndSize(
					  ULONG uGroupID,
					  ULONG uX,
					  ULONG uY,
					  ULONG uWidth,
					  ULONG uHeight
					  )
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		pVideoGroup->SetVideoPosAndSize(uX, uY, uWidth, uHeight);
		pVideoGroup->m_bDefaultOutput = FALSE;
		return 0;
	}
	return -1;
}

LONG CMultiSAP::GetVideoPositionAndSize(ULONG uGroupID, ULONG* uX, ULONG* uY, ULONG* uWeight, ULONG* uHeight)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->GetVideoPosAndSize(uX, uY, uWeight, uHeight);
	}
	return -1;
}

LONG CMultiSAP::SetVideoAlpha(
							  ULONG uGroupID,
							  ULONG uAlpha	
							  )
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->SetVideoAlpha(uAlpha);
	}
	return -1;
}

LONG CMultiSAP::GetVideoAlpha(
							  ULONG uGroupID,
							  ULONG* uAlpha	
							  )
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->GetVideoAlpha(*uAlpha);
	}
	return -1;
}

void CMultiSAP::RenderText()
{
	HRESULT hr = E_FAIL;
	RECT srcRECT = {0, 0, m_uSurfaceWidth, m_uSurfaceHeight};
	RECT dstRECT = {0, 0, m_uSurfaceWidth, m_uSurfaceHeight};
	POSITION pos = m_textObject.GetStartPosition();
	while (pos)
	{
		CTextObject* pTextObject = m_textObject.GetNextValue(pos);
		IDirectDrawSurface7* pDDS = pTextObject->GetDDSFontCache();
		if (pDDS)
		{
//			hr = m_pAlphaBlt->AlphaBlt(&dstRECT, pDDS, &srcRECT, 0x80);
		}
	}
}

void CMultiSAP::RenderBitmap()
{
	//////////////////////////////////////////////////////////////////////////
//	HRESULT hr;
//	if (m_lpDDSBitmapCache)
//	{
//		RECT srcRECT = {0, 0, 640, 480};
//		RECT dstRECT = {0, 0, 640, 480};
//		hr = m_pAlphaBlt->AlphaBlt(&dstRECT, m_lpDDSBitmapCache, &srcRECT, 0x00);
//	}
	//////////////////////////////////////////////////////////////////////////
	HRESULT hr = E_FAIL;
	POSITION pos = m_bitmapObject.GetStartPosition();
	while (pos)
	{
		CBitmapObject* pBitmapObject = m_bitmapObject.GetNextValue(pos);
		IDirectDrawSurface7* pDDS = pBitmapObject->GetSurface();
		if (pDDS)
		{
			RECT srcRECT = {
				0,
				0, 
				pBitmapObject->m_uWidth, 
				pBitmapObject->m_uHeight};
			RECT dstRECT = {
				pBitmapObject->m_uX,
				pBitmapObject->m_uY,
				pBitmapObject->m_uWidth, 
				pBitmapObject->m_uHeight};

//			hr = m_pAlphaBlt->AlphaBlt(&dstRECT, pDDS, &srcRECT, 0x00);
		}
	}
}

void CMultiSAP::RenderDynamicBitmap()
{
/*	HRESULT hr;
	if (m_lpDDSDynamicBitmapCache)
	{
		RECT srcRECT = {0, 0, 640, 480};
		RECT dstRECT = {0, 0, 640, 480};
		hr = m_pAlphaBlt->AlphaBlt(&dstRECT, m_lpDDSDynamicBitmapCache, &srcRECT, 0xFF);
	}
*/
	HRESULT hr = E_FAIL;
	POSITION pos = m_dynamicBitmap.GetStartPosition();
	while (pos)
	{
		CDynamicBitmap* pBitmap = m_dynamicBitmap.GetNextValue(pos);
		IDirectDrawSurface7* pDDS = pBitmap->GetSurface();
		if (pDDS)
		{
			RECT srcRECT = {
				0,
				0, 
				pBitmap->m_uWidth, 
				pBitmap->m_uHeight};
				RECT dstRECT = {
				pBitmap->m_uX,
				pBitmap->m_uY,
				pBitmap->m_uWidth, 
				pBitmap->m_uHeight};
//			hr = m_pAlphaBlt->AlphaBlt(&dstRECT, pDDS, &srcRECT, 0x00);
		}
	}
}

HRESULT
CMultiSAP::DDARGB32SurfaceInit(
							   LPDIRECTDRAWSURFACE7* lplpDDS,
							   BOOL bTexture,
							   DWORD cx,
							   DWORD cy
							   )
{
	DDSURFACEDESC2 ddsd;
	HRESULT hRet;

	CheckPointer(lplpDDS,E_POINTER);
	*lplpDDS = NULL;

	INITDDSTRUCT(ddsd);

	ddsd.ddpfPixelFormat.dwSize = sizeof(DDPIXELFORMAT);
	ddsd.ddpfPixelFormat.dwFlags = DDPF_RGB;
	if(bTexture)
	{
		ddsd.ddpfPixelFormat.dwFlags |= DDPF_ALPHAPIXELS;
	}

	ddsd.ddpfPixelFormat.dwRGBBitCount = 32;
	if(bTexture)
	{
		ddsd.ddpfPixelFormat.dwRGBAlphaBitMask = 0xFF000000;
	}

	ddsd.ddpfPixelFormat.dwRBitMask = 0x00FF0000;
	ddsd.ddpfPixelFormat.dwGBitMask = 0x0000FF00;
	ddsd.ddpfPixelFormat.dwBBitMask = 0x000000FF;

	if(bTexture)
	{
		ddsd.ddsCaps.dwCaps  =  DDSCAPS_TEXTURE;
		ddsd.ddsCaps.dwCaps2 = (DDSCAPS2_TEXTUREMANAGE | DDSCAPS2_HINTDYNAMIC);
	}
	else
	{
		ddsd.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN;
	}

	ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_PIXELFORMAT;
	ddsd.dwBackBufferCount = 0;

	if(bTexture)
	{
		for(ddsd.dwWidth=1;  cx>ddsd.dwWidth;   ddsd.dwWidth<<=1);
		for(ddsd.dwHeight=1; cy>ddsd.dwHeight; ddsd.dwHeight<<=1);
	}
	else
	{
		ddsd.dwWidth=cx;
		ddsd.dwHeight=cy;
	}

	// Attempt to create the surface with these settings
	hRet = m_lpDDObj->CreateSurface(&ddsd, lplpDDS, NULL);
	if( FAILED( hRet ))
	{
		TCHAR achT[MAX_PATH];
		HRESULT hrT = StringCchPrintf( achT, NUMELMS(achT),TEXT("<***> FAILED TO CREATE SURFACE (%s, #%ld), hr = 0x%08x"),
			__FILE__, __LINE__, hRet);
		OutputDebugString(achT);
	}

	return hRet;
}

HRESULT
CMultiSAP::CreateFontCache(int cyFont, CTextObject* pTextObject, IDirectDrawSurface7** pDDSurface, BOOL bRegion)
{
	//
	// Initialize the LOGFONT structure - we want to
	// create an "anti-aliased" Lucida Consol font
	//
	HRESULT hr;

	//	POSITION pos = m_textObject.GetStartPosition();
	//	CTextObject* pTextObject = m_textObject.GetNextValue(pos);

	HFONT hFont = CreateFontIndirect(&pTextObject->GetFont()) ;
	if(!hFont)
	{
		return E_OUTOFMEMORY;
	}

	//
	// The following magic is necessary to get GDI to rasterize
	// the font with anti-aliasing switched on when we later use
	// the font in a DDraw Surface.  The doc's say that this is only
	// necessary in Win9X - but Win2K seems to require it too.
	//
/*	SIZE size;
	HDC hdcWin = GetDC(NULL);
	hFont = (HFONT)::SelectObject(hdcWin, hFont);
	GetTextExtentPoint32(hdcWin, TEXT("A"), 1, &size);

	hFont = (HFONT)::SelectObject(hdcWin, hFont);
	ReleaseDC(NULL, hdcWin);
*/
	//
	// Make sure that the font doesn't get too big.
	//
	//	if(size.cx * 40/*GRID_CX*/ > 1024)
	//	{
	//		return S_OK;
	//	}

	//
	// Delete the old font and assign the new one
	//
	//	m_lpDDSFontCache.Release();
	//if(m_hFont)
	//{
	//	DeleteObject(m_hFont);
	//}
	//	m_cxFont = size.cx; m_cyFont = size.cy;
	//m_hFont = hFont;


	//
	// Create the DDraw ARGB32 surface that we will use
	// for the font cache.
	//
	hr = DDARGB32SurfaceInit(pDDSurface, TRUE, m_uSurfaceWidth, m_uSurfaceHeight/*16 * size.cx, 6 * size.cy*/);

	if(hr == DD_OK)
	{
		HDC hdcDest;

		(*pDDSurface)->GetDC(&hdcDest);

		//
		// Select the font into the DDraw surface and draw the characters
		//
		(HFONT)::SelectObject(hdcDest, hFont);
		SetTextColor(hdcDest, RGB(255, 255, 255));
		SetBkColor(hdcDest, RGB(0,0,0));
		SetBkMode(hdcDest, TRANSPARENT);

		//		pos = m_textObject.GetStartPosition();
		//		while (pos)
		//		{
		//			CTextObject* pTextObject = m_textObject.GetNextValue(pos);
		if( !bRegion )
		{
			int row = pTextObject->GetYCoordinate();
			int col = pTextObject->GetXCoordinate();
			TextOut(hdcDest, col, row, pTextObject->GetText(), pTextObject->GetTextLen());
		}
		else
		{
			RECT rt;
			rt.top = pTextObject->GetYCoordinate();
			rt.left = pTextObject->GetXCoordinate();
			rt.right = pTextObject->GetXCoordinate() + pTextObject->m_uRegionWidth;
			rt.bottom = pTextObject->GetYCoordinate() + pTextObject->m_uRegionHeight;
			DrawText(hdcDest, pTextObject->GetText(), pTextObject->GetTextLen(), &rt, DT_WORDBREAK);
		}
		DeleteFont(hFont);
		
		//		}

		//m_hFont = (HFONT)SelectObject(hdcDest, m_hFont);
		(*pDDSurface)->ReleaseDC(hdcDest);

		DDSURFACEDESC2 surfDesc;
		INITDDSTRUCT(surfDesc);

		hr = (*pDDSurface)->Lock(NULL, &surfDesc, DDLOCK_WAIT, NULL);

		if(hr == DD_OK)
		{
			LPDWORD lpDst = (LPDWORD)surfDesc.lpSurface;

			//			for(row = 0; row < 1 * size.cy; row++)
			for(int i = 0; i < m_uSurfaceHeight; i++)
			{
				LPDWORD lp = lpDst;

				//				for(col = 0; col < m_pTextObject->GetTextLen() * size.cx; col++)
				for(int j = 0; j < m_uSurfaceWidth; j++)
				{
					DWORD dwPel = *lp;

					if(dwPel)
					{
						dwPel <<= 24;
						//						dwPel |= 0x00FFFFFF;
						dwPel |= pTextObject->GetColor();
					}
					else
					{
						//						dwPel = 0x80000000;
					}

					*lp++ = dwPel;
				}
				lpDst += (surfDesc.lPitch / 4);
			}
			(*pDDSurface)->Unlock(NULL);
		}

	}

	return S_OK;
}

LONG CMultiSAP::GetText(
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
			 ULONG* uAlpha, ULONG* uTransparentColor, ULONG* uDrawStyle, ULONG* uDelay)
{
//	CTextObject* pTextObject = m_textObject[uID];
//	if (pTextObject)
//	{
//		*uX = pTextObject->GetXCoordinate();
//		*uY = pTextObject->GetYCoordinate();
//		_tcscpy(sOutputText, pTextObject->GetText());
//		_tcscpy(FaceName, pTextObject->GetFaceName());
//		*uItalic = pTextObject->GetItalic();
//		*uBold   = pTextObject->GetBold();
//		*uUnderLine = pTextObject->GetUnderLine();
//		*uWidth   = pTextObject->GetWidth();
//		*uHeight  = pTextObject->GetHeight();
////		memcpy(pFont, &pTextObject->GetFont(), sizeof(LOGFONT));
//		*uColor = pTextObject->GetColor();
//		return 0;
//	}
//	return -1;

	std::map<ULONG, CEffectTextGroup*>::iterator textiter = m_EffectTextGroup.begin();
	for( ; textiter != m_EffectTextGroup.end(); ++textiter )
	{
		CEffectTextGroup * pGroup = textiter->second;
		std::list<CEffectTextEx*>::iterator iterinner = pGroup->m_effectextlist.begin();
		for (; iterinner != pGroup->m_effectextlist.end(); ++iterinner)
		{
			CEffectTextEx * pTextObject = *iterinner;
			if(pTextObject->GetObjectID() == uID)
			{
				*uX = pTextObject->GetXCoordinate();
				*uY = pTextObject->GetYCoordinate();
				_tcscpy(sOutputText, pTextObject->GetText());
				_tcscpy(FaceName, pTextObject->GetFaceName());
				*uItalic = pTextObject->GetItalic();
				*uBold   = pTextObject->GetBold();
				*uUnderLine = pTextObject->GetUnderLine();
				*uWidth   = pTextObject->GetWidth();
				*uHeight  = pTextObject->GetHeight();
				*uColor = pTextObject->GetColor();
				*uAlpha = pTextObject->m_uAlpha;
				*uTransparentColor = pTextObject->m_uTransparentColor;
				*uDrawStyle = pTextObject->m_uDrawStyle;
				*uDelay = pTextObject->m_uDelay;
				return 0;
			}
		}
	}
	return -1;
}

LONG CMultiSAP::SetText(
			 ULONG uX,
			 ULONG uY,
			 LPCTSTR sOutputText,
			 LPCTSTR  sFaceName,
			 ULONG    uItalic,
			 ULONG   uBold,
			 ULONG   uUnderLine,
			 ULONG   uWidth,
			 ULONG   uHeight,
			 ULONG   uColor,
			 ULONG* uID)
{
	HRESULT hr;
	CTextObject* pTextObject = new CTextObject();
	m_textObject[pTextObject->GetObjectID()] = pTextObject;
	*uID = pTextObject->GetObjectID();

	pTextObject->m_pMultiSAP = this;

	pTextObject->SetAlphaBlt(m_pAlphaBlt);
	pTextObject->m_uSurfaceWidth  = m_uSurfaceWidth;
	pTextObject->m_uSurfaceHeight = m_uSurfaceHeight;

	LOGFONT lfChar;
	ZeroMemory(&lfChar, sizeof(lfChar));
	lfChar.lfWidth          = uWidth;
	lfChar.lfHeight         = uHeight;
	if( uItalic == 1) lfChar.lfItalic         = TRUE;
	if( uUnderLine == 1) lfChar.lfUnderline   = TRUE;
	lfChar.lfCharSet        = DEFAULT_CHARSET;
	lfChar.lfPitchAndFamily = DEFAULT_PITCH;
	StringCchCopy(lfChar.lfFaceName, NUMELMS(lfChar.lfFaceName), sFaceName);
	if( uBold == 1)	
		lfChar.lfWeight        = FW_BOLD;
	else	
		lfChar.lfWeight        = FW_NORMAL;
	lfChar.lfOutPrecision  = OUT_DEFAULT_PRECIS;
	lfChar.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lfChar.lfQuality       = ANTIALIASED_QUALITY;
	pTextObject->SetLogFont( &lfChar );

	hr = pTextObject->SetText(uX, uY, sOutputText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor);
	//	if (m_lpDDSFontCache != NULL) m_lpDDSFontCache.Release();
	IDirectDrawSurface7* pDDS = NULL;
	hr = CreateFontCache(32, pTextObject, &pDDS, FALSE);
	pTextObject->SetDDSFontCache(pDDS);

	EnterCriticalSection(&m_videoGroupsCS);
	m_drawList.AddHead(pTextObject);
	LeaveCriticalSection(&m_videoGroupsCS);
	return hr;
}

LONG CMultiSAP::SetTextInRegion(
						ULONG uX,
						ULONG uY,
						LPCTSTR sOutputText,
						LPCTSTR  sFaceName,
						ULONG    uItalic,
						ULONG   uBold,
						ULONG   uUnderLine,
						ULONG   uWidth,
						ULONG   uHeight,
						ULONG   uColor,
						ULONG*  uID,
						ULONG   uRegionWidth,
						ULONG   uRegionHeight)
{
	HRESULT hr;
	CTextObject* pTextObject = new CTextObject();
	m_textObject[pTextObject->GetObjectID()] = pTextObject;
	*uID = pTextObject->GetObjectID();

	pTextObject->m_pMultiSAP = this;

	pTextObject->SetAlphaBlt(m_pAlphaBlt);
	pTextObject->m_uSurfaceWidth  = m_uSurfaceWidth;
	pTextObject->m_uSurfaceHeight = m_uSurfaceHeight;
	pTextObject->m_uRegionWidth   = uRegionWidth;
	pTextObject->m_uRegionHeight  = uRegionHeight;


	LOGFONT lfChar;
	ZeroMemory(&lfChar, sizeof(lfChar));
	lfChar.lfWidth          = uWidth;
	lfChar.lfHeight         = uHeight;
	if( uItalic == 1) lfChar.lfItalic         = TRUE;
	if( uUnderLine == 1) lfChar.lfUnderline   = TRUE;
	lfChar.lfCharSet        = DEFAULT_CHARSET;
	lfChar.lfPitchAndFamily = DEFAULT_PITCH;
	StringCchCopy(lfChar.lfFaceName, NUMELMS(lfChar.lfFaceName), sFaceName);
	if( uBold == 1)	
		lfChar.lfWeight        = FW_BOLD;
	else	
		lfChar.lfWeight        = FW_NORMAL;
	lfChar.lfOutPrecision  = OUT_DEFAULT_PRECIS;
	lfChar.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lfChar.lfQuality       = ANTIALIASED_QUALITY;
	pTextObject->SetLogFont( &lfChar );

	hr = pTextObject->SetText(uX, uY, sOutputText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor);

	IDirectDrawSurface7* pDDS = NULL;
	hr = CreateFontCache(32, pTextObject, &pDDS, TRUE);

	pTextObject->SetDDSFontCache(pDDS);
	EnterCriticalSection(&m_videoGroupsCS);
	m_drawList.AddHead(pTextObject);
	LeaveCriticalSection(&m_videoGroupsCS);
	return hr;
}

LONG CMultiSAP::SetEffectTextInRegion(
								ULONG uX,
								ULONG uY,
								LPCTSTR sOutputText,
								LPCTSTR  sFaceName,
								ULONG    uItalic,
								ULONG   uBold,
								ULONG   uUnderLine,
								ULONG   uWidth,
								ULONG   uHeight,
								ULONG   uColor,
								ULONG*  uID,
								ULONG   uRegionWidth,
								ULONG   uRegionHeight,
								ULONG   uDrawStyle,
								ULONG   uDelay)
{
	HRESULT hr;
	CEffectText* pTextObject = new CEffectText();
	m_textObject[pTextObject->GetObjectID()] = pTextObject;
	*uID = pTextObject->GetObjectID();

	pTextObject->m_pMultiSAP = this;

	pTextObject->SetAlphaBlt(m_pAlphaBlt);
	pTextObject->m_uSurfaceWidth  = m_uSurfaceWidth;
	pTextObject->m_uSurfaceHeight = m_uSurfaceHeight;
	pTextObject->m_uRegionWidth   = uRegionWidth;
	pTextObject->m_uRegionHeight  = uRegionHeight;
//	m_drawList.AddHead(pTextObject);

	LOGFONT lfChar;
	ZeroMemory(&lfChar, sizeof(lfChar));
	lfChar.lfWidth          = uWidth;
	lfChar.lfHeight         = uHeight;
	if( uItalic == 1) lfChar.lfItalic         = TRUE;
	if( uUnderLine == 1) lfChar.lfUnderline   = TRUE;
	lfChar.lfCharSet        = DEFAULT_CHARSET;
	lfChar.lfPitchAndFamily = DEFAULT_PITCH;
	StringCchCopy(lfChar.lfFaceName, NUMELMS(lfChar.lfFaceName), sFaceName);
	if( uBold == 1)	
		lfChar.lfWeight        = FW_BOLD;
	else	
		lfChar.lfWeight        = FW_NORMAL;
	lfChar.lfOutPrecision  = OUT_DEFAULT_PRECIS;
	lfChar.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lfChar.lfQuality       = ANTIALIASED_QUALITY;
	pTextObject->SetLogFont( &lfChar );

//	hr = pTextObject->SetText(uX, uY, sOutputText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor, uDrawStyle, uDelay);

	IDirectDrawSurface7* pDDS = NULL;
	//hr = CreateFontCache(32, pTextObject, &pDDS, TRUE);
	//hr = DDARGB32SurfaceInit(&pDDS, TRUE, m_uSurfaceWidth, m_uSurfaceHeight);
	hr = DDARGB32SurfaceInit(&pDDS, TRUE, uRegionWidth, uRegionHeight);
	pTextObject->SetDDSFontCache(pDDS);


	hr = pTextObject->SetText(uX, uY, sOutputText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor, uDrawStyle, uDelay);


	EnterCriticalSection(&m_videoGroupsCS);
	m_drawList.AddHead(pTextObject);
	LeaveCriticalSection(&m_videoGroupsCS);
	return hr;
}

LONG CMultiSAP::DelText(ULONG uID)
{
	EnterCriticalSection(&m_videoGroupsCS);
	int ret = -1;
	CTextObject* pTextObject = m_textObject[uID];
	if (pTextObject)
	{
		// bug!!!!!
		//delete pTextObject;
		m_textObject.RemoveKey(uID);
		ret = 0;
	}

	std::map<ULONG, CEffectTextGroup*>::iterator iter = m_EffectTextGroup.begin();
	for( ; iter != m_EffectTextGroup.end(); ++iter )
	{
		CEffectTextGroup * pGroup = iter->second;
		std::list<CEffectTextEx*>::iterator iterinner = pGroup->m_effectextlist.begin();
		for (; iterinner != pGroup->m_effectextlist.end(); ++iterinner)
		{
			CEffectTextEx * pText = *iterinner;
			if(pText->GetObjectID() == uID)
			{
				EnterCriticalSection(&pGroup->m_cs);
				if( pGroup->m_iter == iterinner )
				{
					// current playing
					pGroup->m_iter = pGroup->m_effectextlist.erase(iterinner);
				}
				else
					pGroup->m_effectextlist.erase(iterinner);
				ret = 0;
				LeaveCriticalSection(&pGroup->m_cs);
				break;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	POSITION pos = m_drawList.GetHeadPosition();
	while( pos )
	{
		POSITION tempPos = pos;
		CAnsoplyObject * pObject = m_drawList.GetNext( pos );
		if( pObject && pObject->GetObjectID() == uID )
		{
			m_drawList.RemoveAt( tempPos );
			ret = 0;
			break;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return ret;
}

LONG CMultiSAP::GetFirstVideoObjectID(ULONG uGroupID)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->GetFirstVideoObjectID();
	}
	return -1;
}

LONG CMultiSAP::GetNextVideoObjectID(ULONG uGroupID, ULONG & uObjectID)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->GetNextVideoObjectID(uObjectID);
	}
	return -1;
}

LONG CMultiSAP::GetVideoObjectCount(ULONG uGroupID)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->GetCount();
	}
	return -1;
}

LONG CMultiSAP::GetVideoGroupCount()
{
    return m_videoGroups.GetCount();
}

LONG CMultiSAP::GetFirstVideoGroupID()
{
	if( m_videoGroups.IsEmpty() ) 
		return -1;
	CVideoGroup * pVideoGroup = m_videoGroups.GetHead();
	return pVideoGroup->GetObjectID();
}

LONG CMultiSAP::GetNextVideoGroupID(LONG & uGroupID)
{
	if( m_videoGroups.IsEmpty() )
		return -1;

	POSITION pos = m_videoGroups.GetHeadPosition();
	while( pos )
	{
		CVideoGroup * pVideoGroup = m_videoGroups.GetNext( pos );
		if( pVideoGroup )
		{
			if (pVideoGroup->GetObjectID() == uGroupID)
			{
				if( !pos )
				{
					uGroupID = -1;
					break;
				}
				pVideoGroup = m_videoGroups.GetNext( pos );
				if( pVideoGroup )
					uGroupID = pVideoGroup->GetObjectID();
				break;
			}
		}
	}
	//uGroupID = -1;
	return 0;
}

LONG CMultiSAP::GetVideoObjectFileName (ULONG uGroupID, ULONG uFileID, LPWSTR sFilePathName)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		CVideoObject* pVideoObject = pVideoGroup->GetVideoObject(uFileID);
		if (pVideoObject)
		{
			//USES_CONVERSION;
			wcsncpy( sFilePathName, pVideoObject->m_achPath, wcslen(pVideoObject->m_achPath) );
			return 0;
		}
	}
	return -1;
}

LONG CMultiSAP::GetVideoLength(ULONG uGroupID, ULONG uFileID, DOUBLE* uLength)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if (pVideoGroup)
	{
		return pVideoGroup->GetVideoLength(uFileID, uLength);
	}
	return -1;
}

LONG CMultiSAP::GetCurrentFileID(ULONG uGroupID, LONG * uFileID)
{
	CVideoGroup * pVideoGroup = FindGroup(uGroupID);
	if( pVideoGroup )
	{
		return pVideoGroup->GetCurrentFileID(uFileID);
	}
	return -1;
}

LONG CMultiSAP::GetCurrentPlayingPos(ULONG uGroupID, ULONG * uCurPos)
{
	CVideoGroup * pVideoGroup = FindGroup(uGroupID);
	if( pVideoGroup )
	{
		return pVideoGroup->GetCurrentPlayingPos(uCurPos);
	}
	return -1;
}

LONG CMultiSAP::SelectObject(ULONG uGroupID, ULONG uFrameColor)
{
//	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
//	if (pVideoGroup)
	{
		m_lSelectGroupID = uGroupID;
		m_uSelectFrameColor = uFrameColor;
		return 0;
	}
//	return -1;
}

LONG CMultiSAP::UnSelectVideoGroup()
{
	m_lSelectGroupID = -1;
	return 0;
}

LONG CMultiSAP::SelectObjectByCoordinate(
	ULONG * uObjectID,
	ULONG * uObjectType,
	ULONG uX,
	ULONG  uY,
	ULONG uFrameColor
	)
{
	m_lSelectGroupID = -1;
/*	POSITION pos = m_videoGroups.GetHeadPosition();
	while (pos)
	{
		CVideoGroup* pVideoGroup = m_videoGroups.GetNext(pos);
		if (pVideoGroup && pVideoGroup->SelectGroup(uX, uY))
		{
			*uGroupID = pVideoGroup->GetObjectID();
			m_lSelectGroupID = pVideoGroup->GetObjectID();
			m_uSelectFrameColor = uFrameColor;
			return 0;
		}
	}
*/
	POSITION pos = m_drawList.GetHeadPosition();  // the tail is the bottom
	while( pos )
	{
		CAnsoplyObject * pObject = m_drawList.GetNext( pos );
		if( pObject && pObject->SelectGroup(uX, uY) )
		{
			*uObjectID          = pObject->GetObjectID();
			*uObjectType        = (ULONG)pObject->GetObjectType();
			m_lSelectGroupID    = pObject->GetObjectID();
			m_uSelectFrameColor = uFrameColor;
			return 0;
		}
	}
	return -1;
}

LONG CMultiSAP::GetBitmap(
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
			   ULONG* uDelay)
{
	//CBitmapObject* pBitmapObject = m_bitmapObject[uBitmapID];
	//if (pBitmapObject)
	//{
	//	*sBitmapFilePath = _com_util::ConvertStringToBSTR(pBitmapObject->m_sFilePath.c_str());
	//	*uAlpha = pBitmapObject->m_uAlpha;
	//	*uTransparentColor = pBitmapObject->m_uTransparentColor;
	//	*uX = pBitmapObject->m_uX;
	//	*uY = pBitmapObject->m_uY;
	//	return 0;
	//}

	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		std::list<CEffectBitmapEx*>::iterator iterinner = pGroup->m_effectbmplist.begin();
		for (; iterinner != pGroup->m_effectbmplist.end(); ++iterinner)
		{
			CEffectBitmapEx * pBitmapObject = *iterinner;
			if(pBitmapObject->GetObjectID() == uBitmapID)
			{
				*sBitmapFilePath = _com_util::ConvertStringToBSTR(pBitmapObject->m_sFilePath.c_str());
				*uAlpha = pBitmapObject->m_uAlpha;
				*uTransparentColor = pBitmapObject->m_uTransparentColor;
				*uX = pBitmapObject->m_uX;
				*uY = pBitmapObject->m_uY;
				*uWidth = pBitmapObject->m_uWidth;
				*uHeight = pBitmapObject->m_uHeight;
				*uOriginalSize = pBitmapObject->m_uOriginalSize;
				*uDrawStyle = pBitmapObject->m_uDrawStyle;
				*uDelay = pBitmapObject->m_uDelay;
				return 0;
			}
		}
	}
	return -1;
}

LONG CMultiSAP::DelBitmap(ULONG uBitmapID)
{
	EnterCriticalSection(&m_videoGroupsCS);
	int ret = -1;
	CBitmapObject* pBitmapObject = m_bitmapObject[uBitmapID];
	if (pBitmapObject)
	{
		// bug!!!!!!
		//delete pBitmapObject;
		m_bitmapObject.RemoveKey(uBitmapID);
		ret = 0;
	}

	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		std::list<CEffectBitmapEx*>::iterator iterinner = pGroup->m_effectbmplist.begin();
		for (; iterinner != pGroup->m_effectbmplist.end(); ++iterinner)
		{
			CEffectBitmapEx * pBitmap = *iterinner;
			if(pBitmap->GetObjectID() == uBitmapID)
			{
				EnterCriticalSection(&pGroup->m_cs);
				if( pGroup->m_iter == iterinner )
				{
					// current playing
					pGroup->m_iter = pGroup->m_effectbmplist.erase(iterinner);
				}
				else
					pGroup->m_effectbmplist.erase(iterinner);
				LeaveCriticalSection(&pGroup->m_cs);
				ret = 0;
				break;
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	POSITION pos = m_drawList.GetHeadPosition();
	while( pos )
	{
		POSITION tempPos = pos;
		CAnsoplyObject * pObject = m_drawList.GetNext( pos );
		if( pObject && pObject->GetObjectID() == uBitmapID )
		{
			m_drawList.RemoveAt( tempPos );
			delete pObject;
			ret = 0;
			break;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return ret;
}

LONG CMultiSAP::DelDynamicBitmap(ULONG uDynamicBitmapID)
{
	EnterCriticalSection(&m_videoGroupsCS);
	int ret = -1;
	CDynamicBitmap* pBitmapObject = m_dynamicBitmap[uDynamicBitmapID];
	if (pBitmapObject)
	{
		// bug!!!!!!
		//delete pBitmapObject;
		m_dynamicBitmap.RemoveKey(uDynamicBitmapID);
		ret = 0;
	}
	//////////////////////////////////////////////////////////////////////////
	POSITION pos = m_drawList.GetHeadPosition();
	while( pos )
	{
		POSITION tempPos = pos;
		CAnsoplyObject * pObject = m_drawList.GetNext( pos );
		if( pObject && pObject->GetObjectID() == uDynamicBitmapID )
		{
			m_drawList.RemoveAt( tempPos );
			delete pObject;
			ret = 0;
			break;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return ret;
}

typedef struct _dynamic_struct_
{
	CMultiSAP * pMultiSAP;
	ULONG       nMilli;
	ULONG       nObjectMapKey;
}DYNAMIC_STRUCT;

LONG CMultiSAP::SetDynamicBitmap(
					  ULONG  * uObjectID,
					  LPCTSTR sBitmapFilePath,
					  ULONG uAlpha,
					  ULONG uTransparentColor,   
					  ULONG uX,
					  ULONG uY,
					  ULONG uWidth,
					  ULONG uHeight,
					  ULONG uOriginalSize,
					  ULONG uMilli)
{
	CDynamicBitmap * pDyanmicBitmapObject = new CDynamicBitmap();
	pDyanmicBitmapObject->SetDynamicBitmap(sBitmapFilePath, uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, uMilli);

	pDyanmicBitmapObject->m_pMultiSAP = this;
	pDyanmicBitmapObject->SetAlphaBlt(m_pAlphaBlt);

	HRESULT hr = DD_OK;
	//if( !m_lpDDSBitmapCache )
	IDirectDrawSurface7* pDDS = NULL;
	hr = DDARGB32SurfaceInit(&pDDS, TRUE, 640, 480);
	pDyanmicBitmapObject->SetSurface(pDDS);

	m_dynamicBitmap[pDyanmicBitmapObject->GetObjectID()] = pDyanmicBitmapObject;
	*uObjectID = pDyanmicBitmapObject->GetObjectID();

	EnterCriticalSection(&m_videoGroupsCS);
	m_drawList.AddHead(pDyanmicBitmapObject);
	LeaveCriticalSection(&m_videoGroupsCS);

	//	AfxBeginThread( ChangeDynamicBitmap, this );

	DYNAMIC_STRUCT * dy_struct = new DYNAMIC_STRUCT;
	dy_struct->pMultiSAP     = this;
	dy_struct->nObjectMapKey = pDyanmicBitmapObject->GetObjectID();
	dy_struct->nMilli        = uMilli;
	_beginthread(ChangeDynamicBitmap, 0, dy_struct);
	return 0;
}

LONG CMultiSAP::SetDynamicEffectBitmap(
								 ULONG  * uObjectID,
								 LPCTSTR sBitmapFilePath,
								 ULONG uAlpha,
								 ULONG uTransparentColor,   
								 ULONG uX,
								 ULONG uY,
								 ULONG uWidth,
								 ULONG uHeight,
								 ULONG uOriginalSize,
								 ULONG uDrawStyle)
{
	CDynamicEffectBitmap * pDyanmicBitmapObject = new CDynamicEffectBitmap();
	pDyanmicBitmapObject->SetDynamicEffectBitmap(sBitmapFilePath, uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, uDrawStyle);

	pDyanmicBitmapObject->m_pMultiSAP = this;
	pDyanmicBitmapObject->SetAlphaBlt(m_pAlphaBlt);

	HRESULT hr = DD_OK;
	//if( !m_lpDDSBitmapCache )
	IDirectDrawSurface7* pDDS = NULL;
	hr = DDARGB32SurfaceInit(&pDDS, TRUE, 640, 480);
	pDyanmicBitmapObject->SetSurface(pDDS);

	m_dynamicEffectBitmap[pDyanmicBitmapObject->GetObjectID()] = pDyanmicBitmapObject;
	*uObjectID = pDyanmicBitmapObject->GetObjectID();

	EnterCriticalSection(&m_videoGroupsCS);
	m_drawList.AddHead(pDyanmicBitmapObject);
	LeaveCriticalSection(&m_videoGroupsCS);


	//DYNAMIC_STRUCT * dy_struct = new DYNAMIC_STRUCT;
	//dy_struct->pMultiSAP     = this;
	//dy_struct->nObjectMapKey = pDyanmicBitmapObject->GetObjectID();
	//dy_struct->nMilli        = uMilli;
//	_beginthread(ChangeDynamicEffectBitmap, 0, dy_struct);
	return 0;
}

void CMultiSAP::ChangeDynamicEffectBitmap(LPVOID param)
{
/*	DYNAMIC_STRUCT * pDy_struct = (DYNAMIC_STRUCT*)param;

	CMultiSAP * pMultiSAP =  pDy_struct->pMultiSAP;
	ULONG key = pDy_struct->nObjectMapKey;
	ULONG milli = pDy_struct->nMilli;

	//it's important to delete the memory
	delete pDy_struct;

	POSITION pos = pMultiSAP->m_dynamicBitmap.GetStartPosition();
	CDynamicEffectBitmap * pDynamicBitmap;

	if( !pMultiSAP->m_dynamicEffectBitmap.Lookup(key, pDynamicBitmap) )
		return;

	do
	{
		BOOL bBreak = FALSE;
		std::list<BitmapType>::iterator iter = pDynamicBitmap->m_BitmapList.begin();
		while ( iter != pDynamicBitmap->m_BitmapList.end() )
		{
			EnterCriticalSection(&pDynamicBitmap->m_CS);
			HDC hdcDest;
			//IDirectDrawSurface7 * pDDS = pDynamicBitmap->GetSurface();
			//if( DD_OK != pDDS->GetDC(&hdcDest) )
			//	return;

			Color backColor;
			HBITMAP hBmp;
			BitmapType bmpType = (*iter);
			Bitmap * bmp = bmpType.pBitmap;
			bmp->GetHBITMAP(backColor, &hBmp);
			// Get the bitmap structure (to extract width, height, and bpp)
			BITMAP bm;
			GetObject( hBmp, sizeof(BITMAP), &bm );

			// Get a DC for the bitmap
			//HDC hdcBitmap = CreateCompatibleDC( NULL );
			//if( NULL == hdcBitmap )
			//	return;

			if( pDynamicBitmap->m_uOriginalSize == 1 )
			{
				::SelectObject( pDynamicBitmap->m_hdcBitmap, hBmp );
				pDynamicBitmap->m_uWidth = bm.bmWidth;
				pDynamicBitmap->m_uHeight = bm.bmHeight;
				//BitBlt( hdcDest, 0, 0, bm.bmWidth, bm.bmHeight, hdcBitmap, 0, 0, SRCCOPY );
			}
			else
			{
				//USES_CONVERSION;
				////Bitmap originalBMP(T2W(sBitmapFilePath));
				//Graphics g(hdcDest);

				//g.DrawImage(bmp, Rect(0, 0, pDynamicBitmap->m_uWidth, pDynamicBitmap->m_uHeight), 0, 0, 
				//	bmp->GetWidth(), bmp->GetHeight(), UnitPixel, NULL );
			}
			DeleteObject( hBmp );

			iter++;

			LeaveCriticalSection(&pDynamicBitmap->m_CS);
			Sleep(milli);
			if( pDynamicBitmap->m_StopTimeExpire && GetTickCount() > pDynamicBitmap->m_StopTimeExpire )
			{
				bBreak = TRUE;
				break;
			}
		}
		if( bBreak )
			break;
	}while( pDynamicBitmap->m_playType == PLAY_LOOP || pDynamicBitmap->m_uPlayBeginTime++ < pDynamicBitmap->m_uPlayTimes);
*/
}

void CMultiSAP::ChangeDynamicBitmap(LPVOID param)
{
//	CMultiSAP * pMultiSAP = (CMultiSAP*)param;
	DYNAMIC_STRUCT * pDy_struct = (DYNAMIC_STRUCT*)param;

	CMultiSAP * pMultiSAP =  pDy_struct->pMultiSAP;
	ULONG key = pDy_struct->nObjectMapKey;
	ULONG milli = pDy_struct->nMilli;

	//it's important to delete the memory
	delete pDy_struct;

	POSITION pos = pMultiSAP->m_dynamicBitmap.GetStartPosition();
	CDynamicBitmap * pDynamicBitmap;

	if( !pMultiSAP->m_dynamicBitmap.Lookup(key, pDynamicBitmap) )
		return;

	do
	{
		BOOL bBreak = FALSE;
		std::list<BitmapType>::iterator iter = pDynamicBitmap->m_BitmapList.begin();
		while ( iter != pDynamicBitmap->m_BitmapList.end() )
		{
			EnterCriticalSection(&pDynamicBitmap->m_CS);
			HDC hdcDest;
			IDirectDrawSurface7 * pDDS = pDynamicBitmap->GetSurface();
			if( DD_OK != pDDS->GetDC(&hdcDest) )
				return;

			Color backColor;
			HBITMAP hBmp;
			BitmapType bmpType = (*iter);
			Bitmap * bmp = bmpType.pBitmap;
			bmp->GetHBITMAP(backColor, &hBmp);
			// Get the bitmap structure (to extract width, height, and bpp)
			BITMAP bm;
			GetObject( hBmp, sizeof(BITMAP), &bm );

			// Get a DC for the bitmap
			HDC hdcBitmap = CreateCompatibleDC( NULL );
			if( NULL == hdcBitmap )
				return;

			if( pDynamicBitmap->m_uOriginalSize == 1 )
			{
				::SelectObject( hdcBitmap, hBmp );
				pDynamicBitmap->m_uWidth = bm.bmWidth;
				pDynamicBitmap->m_uHeight = bm.bmHeight;
				BitBlt( hdcDest, 0, 0, bm.bmWidth, bm.bmHeight, hdcBitmap, 0, 0, SRCCOPY );
			}
			else
			{
				USES_CONVERSION;
				//Bitmap originalBMP(T2W(sBitmapFilePath));
				Graphics g(hdcDest);

				g.DrawImage(bmp, Rect(0, 0, pDynamicBitmap->m_uWidth, pDynamicBitmap->m_uHeight), 0, 0, 
					bmp->GetWidth(), bmp->GetHeight(), UnitPixel, NULL );
			}

			//SelectObject( hdcBitmap, oldhBmp);
			DeleteObject( hBmp );

			pDDS->ReleaseDC(hdcDest);

			DWORD dwFlags = D3DTEXTR_TRANSPARENTWHITE;
			if( dwFlags & (D3DTEXTR_TRANSPARENTWHITE|D3DTEXTR_TRANSPARENTBLACK) )
			{
				// Lock the texture surface
				DDSURFACEDESC2 ddsdAlpha={0};
				ddsdAlpha.dwSize = sizeof(ddsdAlpha);
				pDDS->Lock( NULL, &ddsdAlpha, 0, NULL );

				//DWORD dwAlphaMask = ddsdAlpha.ddpfPixelFormat.dwRGBAlphaBitMask;
				DWORD dwAlphaMask = pDynamicBitmap->m_uAlpha << 24;
				DWORD dwRGBMask   = ( ddsdAlpha.ddpfPixelFormat.dwRBitMask |
					ddsdAlpha.ddpfPixelFormat.dwGBitMask |
					ddsdAlpha.ddpfPixelFormat.dwBBitMask );
				DWORD dwColorkey  = pDynamicBitmap->m_uTransparentColor; // Colorkey on black
				//if( dwFlags & D3DTEXTR_TRANSPARENTWHITE )
				//	dwColorkey = dwRGBMask;     // Colorkey on white

				// Add an opaque alpha value to each non-colorkeyed pixel
				for( DWORD y = 0; y < bm.bmHeight; y++ )
				{
					WORD*  p16 =  (WORD*)((BYTE*)ddsdAlpha.lpSurface + y*ddsdAlpha.lPitch);
					DWORD* p32 = (DWORD*)((BYTE*)ddsdAlpha.lpSurface + y*ddsdAlpha.lPitch);

					for( DWORD x = 0; x < bm.bmWidth; x++ )
					{
						if( ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 16 )
						{
							if( ( *p16 &= dwRGBMask ) != dwColorkey )
								*p16 |= dwAlphaMask;
							p16++;
						}
						if( ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 32 || ddsdAlpha.ddpfPixelFormat.dwRGBBitCount == 24 )
						{
							if( ( *p32 &= dwRGBMask ) != dwColorkey )
								*p32 |= dwAlphaMask;
							p32++;
						}
					}
				}
				pDDS->Unlock( NULL );
			}
			DeleteDC( hdcBitmap );
			pDDS->ReleaseDC(hdcDest);
			DeleteDC( hdcDest );

			//if ( ++iter == pDynamicBitmap->m_BitmapList.end() )
			//	iter = pDynamicBitmap->m_BitmapList.begin();

			iter++;
			//OutputDebugString("iter\n");

			LeaveCriticalSection(&pDynamicBitmap->m_CS);
			Sleep(milli);
			if( pDynamicBitmap->m_StopTimeExpire && GetTickCount() > pDynamicBitmap->m_StopTimeExpire )
			{
				bBreak = TRUE;
				break;
			}
		}
		if( bBreak )
			break;
	}while( pDynamicBitmap->m_playType == PLAY_LOOP || pDynamicBitmap->m_uPlayBeginTime++ < pDynamicBitmap->m_uPlayTimes);

	pMultiSAP->DelDynamicBitmap(key);
}

LONG CMultiSAP::SavePlayList(LPCTSTR sFile)
{
	TiXmlDocument xmlDoc;
	TiXmlElement* root = new TiXmlElement("PlayList");
	xmlDoc.LinkEndChild(root);

	ULONG uZOrder = 0;
	POSITION pos = m_videoGroups.GetHeadPosition();
	while (pos)
	{
		uZOrder++;
		CVideoGroup* pVideoGroup = m_videoGroups.GetNext(pos);

		TiXmlElement* group = new TiXmlElement("VideoGroup");

		ULONG uAlpha = 0;
		pVideoGroup->GetVideoAlpha(uAlpha);
		group->SetAttribute("Alpha", uAlpha);

		ULONG uX = 0;
		ULONG uY = 0;
		ULONG uWidth = 0;
		ULONG uHeight = 0;
		pVideoGroup->GetVideoPosAndSize(&uX, &uY, &uWidth, &uHeight);
		group->SetAttribute("Width", uWidth);
		group->SetAttribute("Height", uWidth);
		group->SetAttribute("X", uWidth);
		group->SetAttribute("Y", uWidth);
		group->SetAttribute("ZOrder", uZOrder);

		DOUBLE dRate = 0.0;
		pVideoGroup->GetRate(dRate);
		group->SetAttribute("PlayRate", dRate);
		ULONG uPlayMode = 0;
		pVideoGroup->GetPlayMode(uPlayMode);
		group->SetAttribute("PlayMode", uPlayMode);

		root->LinkEndChild(group);

		TiXmlElement* pVideoObject = new TiXmlElement("VideoObject");
		group->LinkEndChild(pVideoObject);

		for ( list<CVideoObject*>::iterator i = pVideoGroup->m_videos.begin();
			i != pVideoGroup->m_videos.end(); i++ )
		{
			CVideoObject* pVideo = *i;
			TiXmlElement* pFileName = new TiXmlElement("FileName");
			pVideoObject->LinkEndChild(pFileName);
			USES_CONVERSION;
			CString str = W2A(pVideo->m_achPath);
            str = str.Mid( str.ReverseFind('\\') + 1 );
			TiXmlText* pFilePath = new TiXmlText( str );
			pFileName->LinkEndChild(pFilePath);
		}
	}

	xmlDoc.SaveFile(sFile);
	return 0;
}


LONG CMultiSAP::LoadPlayList(LPCTSTR sFile)
{
//	EnterCriticalSection(&m_videoGroupsCS);
	POSITION pos = m_videoGroups.GetHeadPosition();
	while (pos)
	{
		CVideoGroup* pVideoGroup = m_videoGroups.GetNext(pos);
		delete pVideoGroup;
	}
	m_videoGroups.RemoveAll();
	//////////////////////////////////////////////////////////////////////////
	m_drawList.RemoveAll();
/*	POSITION pos = m_drawList.GetHeadPosition();
	while( pos )
	{
		POSITION tempPos = pos;
		CAnsoplyObject * pObject = m_drawList.GetNext( pos );
		if( pObject && pObject->GetObjectID() == uBitmapID )
		{
			m_drawList.RemoveAt( tempPos );
			ret = 0;
			break;
		}
	}*/
	//////////////////////////////////////////////////////////////////////////
	

	TiXmlDocument xmlDoc;
	if (xmlDoc.LoadFile(sFile))
	{
		TiXmlNode* pChildNode = xmlDoc.FirstChildElement();
		if (pChildNode) 
		{
			string sNodeName = pChildNode->Value();
			if (sNodeName == "PlayList")
			{
				TiXmlElement * pGroupNode = pChildNode->FirstChildElement();
				while (pGroupNode)
				{
					string sGroup = pGroupNode->Value();
					int nAlpha = 0;
					int nWidth = 0;
					int nHeight = 0;
					int nX = 0;
					int nY = 0;
					double dPlayRate = 0;
					int nPlayMode = 0;
					pGroupNode->QueryIntAttribute("Alpha", &nAlpha);
					pGroupNode->QueryIntAttribute("Width", &nWidth);
					pGroupNode->QueryIntAttribute("Height", &nHeight);
					pGroupNode->QueryIntAttribute("X", &nX);
					pGroupNode->QueryIntAttribute("Y", &nY);
					pGroupNode->QueryDoubleAttribute("PlayRate", &dPlayRate);
					pGroupNode->QueryIntAttribute("PlayMode", &nPlayMode);

					LONG nGroupID = CreateVideoGroup();
					CVideoGroup* pVideoGroup = FindGroup(nGroupID);
					if (pVideoGroup)
					{
						pVideoGroup->SetVideoAlpha(nAlpha);
						pVideoGroup->SetVideoPosAndSize(nX, nY, nWidth, nHeight);
						pVideoGroup->SetRate(dPlayRate);
						pVideoGroup->SetPlayMode(nPlayMode);

						TiXmlElement* pVideoObjectNode = pGroupNode->FirstChildElement();
						string sVideoName = pVideoObjectNode->Value();
						if (sVideoName == "VideoObject")
						{
							TiXmlElement* pVideoFile = pVideoObjectNode->FirstChildElement();
							while (pVideoFile)
							{
								TCHAR szFileName[500] = {0};
								_tcsncpy(szFileName, m_MediaFilePath, _tcslen(m_MediaFilePath));
								//_tcscpy(szFileName + _tcslen(m_MediaFilePath), "\\");
								_tcscpy(szFileName + _tcslen(m_MediaFilePath), pVideoFile->FirstChild()->Value());
								AddVideoFile(nGroupID, szFileName);
								pVideoFile = pVideoFile->NextSiblingElement();
							}
						}
					}
					pGroupNode = pGroupNode->NextSiblingElement();
				}
			}
			//			pChildNode = xmlDoc.NextSibling();
		} 

//		LeaveCriticalSection(&m_videoGroupsCS);
		return 0;
	}
//	LeaveCriticalSection(&m_videoGroupsCS);
	return -1;
}

LONG CMultiSAP::SetMediaFilePath(LPCTSTR sFilePathName)
{
	int Len = _tcslen(sFilePathName);
	if( Len > MAX_PATH )
		return -1;
	_tcsncpy(m_MediaFilePath, sFilePathName, Len);
	return 0;
}

LONG CMultiSAP::SetDefaultVideoSize(ULONG uGroupID, ULONG uX, ULONG uY)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if ( pVideoGroup )
	{
		pVideoGroup->m_uX = uX;
		pVideoGroup->m_uY = uY;
		pVideoGroup->m_bDefaultOutput = TRUE;
/*		CVideoObject * pVideoObject = pVideoGroup->GetCurVideoObj();
		if( pVideoObject )
		{
            LONG Width, Height;
			pVideoObject->GetNativeMovieSize( &Width, &Height );
			pVideoGroup->m_uWidth  = Width;
			pVideoGroup->m_uHeight = Height;
		}*/
		_beginthread(SetDefaultThread, 0, pVideoGroup);

		return 0;
	}
	return -1;
}

void CMultiSAP::SetDefaultThread(LPVOID param)
{
	CoInitialize(NULL);
	CVideoGroup * pVideoGroup = (CVideoGroup*)param;
	CVideoObject *pVideoObject = pVideoGroup->GetCurVideoObj();
	if( !pVideoObject )
		return;

	CComPtr<IUnknown>                   pUnk;
	CComPtr<IGraphBuilder>              m_Gb;       // graph builder
	CComPtr<IBasicVideo>                BasicVideo;
	// to call functions of the default AP
	HRESULT hres = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IUnknown, (LPVOID *)&pUnk);
	hres = pUnk->QueryInterface(IID_IGraphBuilder, (LPVOID *)&m_Gb);
	hres = m_Gb->RenderFile(pVideoObject->m_achPath, NULL);
	m_Gb->QueryInterface(IID_IBasicVideo, (LPVOID*)&BasicVideo);

	LONG x, y;
	BasicVideo->GetVideoSize(&x, &y);
	pVideoGroup->m_uWidth  = x;
	pVideoGroup->m_uHeight = y;

//	ATLTRACE("%d %d\n", x, y);

	CoUninitialize();
}

void CMultiSAP::Refresh()
{
//#define WM_FIN WM_USER+10
//	SendMessage(m_hwndApp, WM_FIN, 0, 0);

	if( m_pWC )
	{
		//HDC hDC = ::GetDC(m_hwndApp);
		PAINTSTRUCT Paint;
		RECT wRect;
		HDC hDC = BeginPaint(m_hwndApp, &Paint);
		GetClientRect(m_hwndApp, &wRect);
		// Erase if needed
		if (Paint.fErase)
		{
			FillRect(hDC, &wRect, (HBRUSH) GetStockObject(BLACK_BRUSH));
		}
		HRESULT hr = m_pWC->RepaintVideo(m_hwndApp, hDC);
		EndPaint(m_hwndApp, &Paint);

		//CString str;
		//str.Format("HRESULT:%d", hr);
		//OutputDebugString(str);
	}
}

LONG CMultiSAP::SetVideoFile(ULONG uGroupID, LPCTSTR sFileName, ULONG uOldFileID, ULONG * uNewFileID)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if ( pVideoGroup )
	{
		sMovieInfo movieInfo;
		CVideoObject* pVideoObject = new CVideoObject();

		USES_CONVERSION;
		wcscpy( movieInfo.achPath, T2W(sFileName) );
		movieInfo.pdwUserID = IDGenerator::GetInstance().GenID();
		pVideoObject->Initialize(&movieInfo, this);

		//		CmdAddEffect(eEffectFading, 2000, 300, 400, TRUE); // set next video effect "fading"

		if( m_pEffect ) // ping video effect change
		{
			m_pEffect->Finish();
		}
		m_movieList.Add( pVideoObject );

		HRESULT hr = pVideoObject->OpenMovie();
		if( FAILED(hr) )
		{
			m_movieList.Delete(pVideoObject->m_dwUserID);
			delete pVideoObject;
			return -1;
		}

		RECT rc;
		GetMoviePosition(&rc);
		PutMoviePosition(rc);

		if( m_pEffect )
		{
			m_pEffect->Invalidate();
		}

		if( pVideoGroup->SetVideoFile(pVideoObject, uOldFileID) == 0 )
			return pVideoObject->GetObjectID();
	}
	return -1;
}

LONG CMultiSAP::SetVisibility(ULONG uObjectID, ULONG bVisibility)
{
	EnterCriticalSection(&m_videoGroupsCS);
	POSITION pos = m_drawList.GetHeadPosition();
	while (pos)
	{
		CAnsoplyObject* pAnsoplyObj = m_drawList.GetNext(pos);
		if (pAnsoplyObj->GetObjectID() == uObjectID)
		{
			pAnsoplyObj->m_bVisibility = (BOOL)bVisibility;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return 0;
}

LONG CMultiSAP::SetPlayTimes(ULONG uGroupID, ULONG uPlayTimes)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if ( pVideoGroup )
	{
		pVideoGroup->SetPlayTimes(uPlayTimes);
	}
	CDynamicBitmap * pDynamicBitmap;
	if( m_dynamicBitmap.Lookup(uGroupID, pDynamicBitmap) )
	{
		pDynamicBitmap->m_uPlayBeginTime = 1;
		pDynamicBitmap->m_uPlayTimes = uPlayTimes;

		pDynamicBitmap->m_StopTimeExpire = 0;

		pDynamicBitmap->m_playType = (PLAY_TYPE)PLAY_THROUGH;
		return 0;
	}

	CBitmapObject * pBitmap;
	if( m_bitmapObject.Lookup(uGroupID, pBitmap) )
	{
		CEffectBitmap * pEB = static_cast<CEffectBitmap*>(pBitmap);
		pEB->m_bPlayEnd = FALSE;
		pBitmap->m_uPlayBeginTime = 1;
		pBitmap->m_uPlayTimes = uPlayTimes;

		pBitmap->m_StopTimeExpire = 0;

		pBitmap->m_playType = (PLAY_TYPE)PLAY_THROUGH;
		return 0;
	}

	CTextObject * pText;
	if( m_textObject.Lookup(uGroupID, pText) )
	{
		CEffectText * pET = static_cast<CEffectText*>(pText);
		pET->m_bPlayEnd = FALSE;
		pET->m_uPlayBeginTime = 1;
		pET->m_uPlayTimes = uPlayTimes;

		pET->m_StopTimeExpire = 0;

		pET->m_playType = (PLAY_TYPE)PLAY_THROUGH;
		return 0;
	}

	CDynamicEffectBitmap * pDEBitmap;
	if( m_dynamicEffectBitmap.Lookup(uGroupID, pDEBitmap) )
	{
		pDEBitmap->m_bPlayEnd = FALSE;
		pDEBitmap->m_uPlayBeginTime = 1;
		pDEBitmap->m_uPlayTimes = uPlayTimes;

		pDEBitmap->m_StopTimeExpire = 0;

		//pDEBitmap->m_playType = (PLAY_TYPE)PLAY_THROUGH;
		return 0;
	}

	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		std::list<CEffectBitmapEx*>::iterator iterinner = pGroup->m_effectbmplist.begin();
		for (; iterinner != pGroup->m_effectbmplist.end(); ++iterinner)
		{
			CEffectBitmapEx * pBitmap = *iterinner;
			if(pBitmap->GetObjectID() == uGroupID)
			{
				pBitmap->m_bPlayEnd = FALSE;
				pBitmap->m_uPlayBeginTime = 1;
				pBitmap->m_uPlayTimes = uPlayTimes;

				pBitmap->m_StopTimeExpire = 0;
				return 0;
			}
		}
	}

	std::map<ULONG, CEffectTextGroup*>::iterator textiter = m_EffectTextGroup.begin();
	for( ; textiter != m_EffectTextGroup.end(); ++textiter )
	{
		CEffectTextGroup * pGroup = textiter->second;
		std::list<CEffectTextEx*>::iterator iterinner = pGroup->m_effectextlist.begin();
		for (; iterinner != pGroup->m_effectextlist.end(); ++iterinner)
		{
			CEffectTextEx * pText = *iterinner;
			if(pText->GetObjectID() == uGroupID)
			{
				pText->m_bPlayEnd = FALSE;
				pText->m_uPlayBeginTime = 1;
				pText->m_uPlayTimes = uPlayTimes;

				pText->m_StopTimeExpire = 0;
				return 0;
			}
		}
	}
	return -1;
}

LONG CMultiSAP::SetPlayTimeout(ULONG uGroupID, ULONG uTimeout_s)
{
	CVideoGroup* pVideoGroup = FindGroup(uGroupID);
	if ( pVideoGroup )
	{
		pVideoGroup->SetPlayTimeout(uTimeout_s);
	}
	CDynamicBitmap * pDynamicBitmap;
	if( m_dynamicBitmap.Lookup(uGroupID, pDynamicBitmap) )
	{
		pDynamicBitmap->m_StopTimeExpire = GetTickCount() + uTimeout_s * 1000;
		return 0;
	}
	CBitmapObject * pBitmap;
	if( m_bitmapObject.Lookup(uGroupID, pBitmap) )
	{
		pBitmap->m_StopTimeExpire = GetTickCount() + uTimeout_s * 1000;
		return 0;
	}

	CTextObject * pText;
	if( m_textObject.Lookup(uGroupID, pText) )
	{
		pText->m_StopTimeExpire = GetTickCount() + uTimeout_s * 1000;
		return 0;
	}

	CDynamicEffectBitmap * pDEBitmap;
	if( m_dynamicEffectBitmap.Lookup(uGroupID, pDEBitmap) )
	{
		pDEBitmap->m_StopTimeExpire = GetTickCount() + uTimeout_s * 1000;
		return 0;
	}

	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		std::list<CEffectBitmapEx*>::iterator iterinner = pGroup->m_effectbmplist.begin();
		for (; iterinner != pGroup->m_effectbmplist.end(); ++iterinner)
		{
			CEffectBitmapEx * pBitmap = *iterinner;
			if(pBitmap->GetObjectID() == uGroupID)
			{
				pBitmap->m_StopTimeExpire = GetTickCount() + uTimeout_s * 1000;
				return 0;
			}
		}
	}

	std::map<ULONG, CEffectTextGroup*>::iterator textiter = m_EffectTextGroup.begin();
	for( ; textiter != m_EffectTextGroup.end(); ++textiter )
	{
		CEffectTextGroup * pGroup = textiter->second;
		std::list<CEffectTextEx*>::iterator iterinner = pGroup->m_effectextlist.begin();
		for (; iterinner != pGroup->m_effectextlist.end(); ++iterinner)
		{
			CEffectTextEx * pText = *iterinner;
			if(pText->GetObjectID() == uGroupID)
			{
				pText->m_StopTimeExpire = GetTickCount() + uTimeout_s * 1000;
				return 0;
			}
		}
	}

	return 0;
}

LONG CMultiSAP::SetEffectBitmapStyle(ULONG uID, ULONG uStyle)
{
	CBitmapObject * pBitmap;
	if( m_bitmapObject.Lookup(uID, pBitmap) )
	{
		CEffectBitmap * pEB = static_cast<CEffectBitmap*>(pBitmap);
		pEB->m_uDrawStyle = uStyle;
		pEB->m_drawtype = PLAY_NONE;  // discard the random or sequence play mode
		return 0;
	}
	CTextObject * pText;
	if( m_textObject.Lookup(uID, pText) )
	{
		CEffectText * pET = static_cast<CEffectText*>(pText);
		pET->m_uDrawStyle = uStyle;
		pET->m_drawtype = PLAY_NONE;  // discard the random or sequence play mode
		return 0;
	}

	CDynamicEffectBitmap * pDEBitmap;
	if( m_dynamicEffectBitmap.Lookup(uID, pDEBitmap) )
	{
		pDEBitmap->m_uDrawStyle = uStyle;
		pDEBitmap->m_drawtype = PLAY_NONE;  // discard the random or sequence play mode
		return 0;
	}

	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		std::list<CEffectBitmapEx*>::iterator iterinner = pGroup->m_effectbmplist.begin();
		for (; iterinner != pGroup->m_effectbmplist.end(); ++iterinner)
		{
			CEffectBitmapEx * pBitmap = *iterinner;
			if(pBitmap->GetObjectID() == uID)
			{
				pBitmap->m_uDrawStyle = uStyle;
				//pBitmap->m_drawtype = PLAY_NONE;
				return 0;
			}
		}
	}

	std::map<ULONG, CEffectTextGroup*>::iterator textiter = m_EffectTextGroup.begin();
	for( ; textiter != m_EffectTextGroup.end(); ++textiter )
	{
		CEffectTextGroup * pGroup = textiter->second;
		std::list<CEffectTextEx*>::iterator iterinner = pGroup->m_effectextlist.begin();
		for (; iterinner != pGroup->m_effectextlist.end(); ++iterinner)
		{
			CEffectTextEx * pText = *iterinner;
			if(pText->GetObjectID() == uID)
			{
				pText->m_uDrawStyle = uStyle;
				//pText->m_drawtype = PLAY_NONE;
				return 0;
			}
		}
	}
	return -1;
}

LONG CMultiSAP::SetEffectPlayRange(ULONG uID, ULONG uPlayMode, ULONG uRangeStart, ULONG uRangeEnd)
{
	CBitmapObject * pBitmap;
	if( m_bitmapObject.Lookup(uID, pBitmap) )
	{
		CEffectBitmap * pEB = static_cast<CEffectBitmap*>(pBitmap);
		pEB->m_drawtype = (PLAY_TYPE)uPlayMode;
		pEB->m_uDrawStyleBegin = uRangeStart;
		pEB->m_uDrawStyleEnd = uRangeEnd;
		pEB->m_playType = PLAY_NONE;
		return 0;
	}
	CTextObject * pText;
	if( m_textObject.Lookup(uID, pText) )
	{
		CEffectText * pET = static_cast<CEffectText*>(pText);
		pET->m_drawtype = (PLAY_TYPE)uPlayMode;
		pET->m_uDrawStyleBegin = uRangeStart;
		pET->m_uDrawStyleEnd = uRangeEnd;
		pET->m_playType = PLAY_NONE;
		return 0;
	}

	CDynamicEffectBitmap * pDEBitmap;
	if( m_dynamicEffectBitmap.Lookup(uID, pDEBitmap) )
	{
		pDEBitmap->m_drawtype = (PLAY_TYPE)uPlayMode;
		pDEBitmap->m_uDrawStyleBegin = uRangeStart;
		pDEBitmap->m_uDrawStyleEnd = uRangeEnd;
		pDEBitmap->m_playType = PLAY_NONE;
		return 0;
	}

	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		pGroup->m_group_type = PLAY_NONE;
		std::list<CEffectBitmapEx*>::iterator iterinner = pGroup->m_effectbmplist.begin();
		for (; iterinner != pGroup->m_effectbmplist.end(); ++iterinner)
		{
			CEffectBitmapEx * pBitmap = *iterinner;
			if(pBitmap->GetObjectID() == uID)
			{
				pBitmap->m_drawtype = (PLAY_TYPE)uPlayMode;
				pBitmap->m_uDrawStyleBegin = uRangeStart;
				pBitmap->m_uDrawStyleEnd = uRangeEnd;
				pBitmap->m_playType = PLAY_NONE;
				return 0;
			}
		}
	}

	std::map<ULONG, CEffectTextGroup*>::iterator textiter = m_EffectTextGroup.begin();
	for( ; textiter != m_EffectTextGroup.end(); ++textiter )
	{
		CEffectTextGroup * pGroup = textiter->second;
		pGroup->m_group_type = PLAY_NONE;
		std::list<CEffectTextEx*>::iterator iterinner = pGroup->m_effectextlist.begin();
		for (; iterinner != pGroup->m_effectextlist.end(); ++iterinner)
		{
			CEffectTextEx * pText = *iterinner;
			if(pText->GetObjectID() == uID)
			{
				pText->m_drawtype = (PLAY_TYPE)uPlayMode;
				pText->m_uDrawStyleBegin = uRangeStart;
				pText->m_uDrawStyleEnd = uRangeEnd;
				pText->m_playType = PLAY_NONE;
				return 0;
			}
		}
	}
	return -1;
}

LONG CMultiSAP::SetEffectEndTime(ULONG uID, LONG EndTime)
{
	CBitmapObject * pBitmap;
	if( m_bitmapObject.Lookup(uID, pBitmap) )
	{
		CEffectBitmap * pEB = static_cast<CEffectBitmap*>(pBitmap);
		pEB->m_endtime = EndTime * 1000;
		return 0;
	}
	CTextObject * pText;
	if( m_textObject.Lookup(uID, pText) )
	{
		CEffectText * pET = static_cast<CEffectText*>(pText);
		pET->m_endtime = EndTime * 1000;
		return 0;
	}

	CDynamicEffectBitmap * pDEBitmap;
	if( m_dynamicEffectBitmap.Lookup(uID, pDEBitmap) )
	{
		pDEBitmap->m_endtime = EndTime * 1000;
		return 0;
	}

	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		std::list<CEffectBitmapEx*>::iterator iterinner = pGroup->m_effectbmplist.begin();
		for (; iterinner != pGroup->m_effectbmplist.end(); ++iterinner)
		{
			CEffectBitmapEx * pBitmap = *iterinner;
			if(pBitmap->GetObjectID() == uID)
			{
				pBitmap->m_endtime = EndTime * 1000;
				return 0;
			}
		}
	}

	std::map<ULONG, CEffectTextGroup*>::iterator textiter = m_EffectTextGroup.begin();
	for( ; textiter != m_EffectTextGroup.end(); ++textiter )
	{
		CEffectTextGroup * pGroup = textiter->second;
		std::list<CEffectTextEx*>::iterator iterinner = pGroup->m_effectextlist.begin();
		for (; iterinner != pGroup->m_effectextlist.end(); ++iterinner)
		{
			CEffectTextEx * pText = *iterinner;
			if(pText->GetObjectID() == uID)
			{
				pText->m_endtime = EndTime * 1000;
				return 0;
			}
		}
	}

	return -1;
}

LONG CMultiSAP::SetEffectBitmap(
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
						  )
{
	CEffectBitmap* pBitmapObject = new CEffectBitmap();

	if ( pBitmapObject->SetBitmap(sBitmapFilePath, uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, uDrawStyle, uDelay, m_hwndApp) == -1)
		return -1;

	pBitmapObject->m_pMultiSAP = this;
	pBitmapObject->SetAlphaBlt(m_pAlphaBlt);

	HRESULT hr = DD_OK;
	//	if( !m_lpDDSBitmapCache ) 
	IDirectDrawSurface7* pDDS = NULL;
	//	hr = DDARGB32SurfaceInit(&m_lpDDSBitmapCache, TRUE, 640, 480);
	HBITMAP hBmp;
	Color backColor;

	BITMAP bm;

	if (uOriginalSize == 1)
	{
		pBitmapObject->m_pBitmap->GetHBITMAP(backColor, &hBmp);
		GetObject( hBmp, sizeof(BITMAP), &bm );
	}

	// Get the bitmap structure (to extract width, height, and bpp)


	ULONG Width, Height;
	if( uOriginalSize == 1 )
	{

		Width  = bm.bmWidth;
		Height = bm.bmHeight;
	}
	else
	{
		Width  = uWidth;
		Height = uHeight;
	}

	hr = DDARGB32SurfaceInit(&pDDS, TRUE, Width, Height);
	if(hr == DD_OK)
	{
		m_bitmapObject[pBitmapObject->GetObjectID()] = pBitmapObject;
		pBitmapObject->SetSurface(pDDS);
		EnterCriticalSection(&m_videoGroupsCS);
		m_drawList.AddHead(pBitmapObject);
		LeaveCriticalSection(&m_videoGroupsCS);
		return pBitmapObject->GetObjectID();
	}

	return -1;
}

LONG CMultiSAP::DelBitmapGroup(ULONG uGroupID)
{
	LONG ret = -1;
	EnterCriticalSection(&m_videoGroupsCS);
	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		if (pGroup->GetObjectID() == uGroupID )
		{
			m_dy_ef_bmp_Group.erase(iter);
		}
	}
	POSITION pos = m_drawList.GetHeadPosition();
	while( pos )
	{
		POSITION tempPos = pos;
		CAnsoplyObject * pObject = m_drawList.GetNext( pos );
		if( pObject && pObject->GetObjectID() == uGroupID )
		{
			m_drawList.RemoveAt( tempPos );
			delete pObject;
			ret = 0;
			break;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return ret;
}

LONG CMultiSAP::CreateTextGroup()
{
	CEffectTextGroup * pGroup = new CEffectTextGroup();

	m_EffectTextGroup[pGroup->GetObjectID()] = pGroup;
	EnterCriticalSection(&m_videoGroupsCS);
	m_drawList.AddHead(pGroup);
	LeaveCriticalSection(&m_videoGroupsCS);
	return pGroup->GetObjectID();
}

LONG CMultiSAP::AddText(ULONG uGroupID, ULONG uX, ULONG uY, LPCTSTR sOutputText, LPCTSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID, ULONG uRegionWidth, ULONG uRegionHeight, ULONG uDrawStyle, ULONG uDelay, ULONG uAlpha, ULONG uTransparentColor)
{
	//HRESULT hr;
	//CEffectTextEx* pTextObject = new CEffectTextEx();
	//m_textObject[pTextObject->GetObjectID()] = pTextObject;

	CEffectTextGroup * pGroup;
	std::map<ULONG, CEffectTextGroup*>::iterator iter = m_EffectTextGroup.find(uGroupID);
	//if( m_dy_ef_bmp_Group.Lookup(uGroupID, pGroup) )

	if( iter != m_EffectTextGroup.end() )
	{
		pGroup = iter->second;
		CEffectTextEx * pTextObject = new CEffectTextEx();
		*uObjectID = pTextObject->GetObjectID();

		pTextObject->m_pMultiSAP = this;

		pTextObject->SetAlphaBlt(m_pAlphaBlt);
		pTextObject->m_uSurfaceWidth  = m_uSurfaceWidth;
		pTextObject->m_uSurfaceHeight = m_uSurfaceHeight;
		pTextObject->m_uRegionWidth   = uRegionWidth;
		pTextObject->m_uRegionHeight  = uRegionHeight;
		//	m_drawList.AddHead(pTextObject);

		LOGFONT lfChar;
		ZeroMemory(&lfChar, sizeof(lfChar));
		lfChar.lfWidth          = uWidth;
		lfChar.lfHeight         = uHeight;
		if( uItalic == 1) lfChar.lfItalic         = TRUE;
		if( uUnderLine == 1) lfChar.lfUnderline   = TRUE;
		lfChar.lfCharSet        = DEFAULT_CHARSET;
		lfChar.lfPitchAndFamily = DEFAULT_PITCH;
		StringCchCopy(lfChar.lfFaceName, NUMELMS(lfChar.lfFaceName), sFaceName);
		if( uBold == 1)	
			lfChar.lfWeight        = FW_BOLD;
		else	
			lfChar.lfWeight        = FW_NORMAL;
		lfChar.lfOutPrecision  = OUT_DEFAULT_PRECIS;
		lfChar.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		lfChar.lfQuality       = ANTIALIASED_QUALITY;
		pTextObject->SetLogFont( &lfChar );

		//	hr = pTextObject->SetText(uX, uY, sOutputText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor, uDrawStyle, uDelay);

		IDirectDrawSurface7* pDDS = NULL;
		//hr = CreateFontCache(32, pTextObject, &pDDS, TRUE);
		//hr = DDARGB32SurfaceInit(&pDDS, TRUE, m_uSurfaceWidth, m_uSurfaceHeight);
		DDARGB32SurfaceInit(&pDDS, TRUE, uRegionWidth, uRegionHeight);
		pTextObject->SetDDSFontCache(pDDS);


		pTextObject->SetText(uX, uY, sOutputText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor, uDrawStyle, uDelay, uAlpha, uTransparentColor);

		pGroup->AddText(pTextObject);

		//EnterCriticalSection(&m_videoGroupsCS);
		//m_drawList.AddHead(pTextObject);
		//LeaveCriticalSection(&m_videoGroupsCS);
		return 0;
	}
	return -1;
}

LONG CMultiSAP::InsertEffectTextInRegion(
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
							  ULONG    uDelay)
{

	CEffectTextGroup * pGroup;
	std::map<ULONG, CEffectTextGroup*>::iterator iter = m_EffectTextGroup.find(uGroupID);
	//if( m_dy_ef_bmp_Group.Lookup(uGroupID, pGroup) )

	if( iter != m_EffectTextGroup.end() )
	{
		pGroup = iter->second;
		CEffectTextEx * pTextObject = new CEffectTextEx();
		*uID = pTextObject->GetObjectID();

		pTextObject->m_pMultiSAP = this;

		pTextObject->SetAlphaBlt(m_pAlphaBlt);
		pTextObject->m_uSurfaceWidth  = m_uSurfaceWidth;
		pTextObject->m_uSurfaceHeight = m_uSurfaceHeight;
		pTextObject->m_uRegionWidth   = uRegionWidth;
		pTextObject->m_uRegionHeight  = uRegionHeight;
		//	m_drawList.AddHead(pTextObject);

		LOGFONT lfChar;
		ZeroMemory(&lfChar, sizeof(lfChar));
		lfChar.lfWidth          = uWidth;
		lfChar.lfHeight         = uHeight;
		if( uItalic == 1) lfChar.lfItalic         = TRUE;
		if( uUnderLine == 1) lfChar.lfUnderline   = TRUE;
		lfChar.lfCharSet        = DEFAULT_CHARSET;
		lfChar.lfPitchAndFamily = DEFAULT_PITCH;
		StringCchCopy(lfChar.lfFaceName, NUMELMS(lfChar.lfFaceName), sFaceName);
		if( uBold == 1)	
			lfChar.lfWeight        = FW_BOLD;
		else	
			lfChar.lfWeight        = FW_NORMAL;
		lfChar.lfOutPrecision  = OUT_DEFAULT_PRECIS;
		lfChar.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		lfChar.lfQuality       = ANTIALIASED_QUALITY;
		pTextObject->SetLogFont( &lfChar );

		//	hr = pTextObject->SetText(uX, uY, sOutputText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor, uDrawStyle, uDelay);

		IDirectDrawSurface7* pDDS = NULL;
		//hr = CreateFontCache(32, pTextObject, &pDDS, TRUE);
		//hr = DDARGB32SurfaceInit(&pDDS, TRUE, m_uSurfaceWidth, m_uSurfaceHeight);
		DDARGB32SurfaceInit(&pDDS, TRUE, uRegionWidth, uRegionHeight);
		pTextObject->SetDDSFontCache(pDDS);


		pTextObject->SetText(uX, uY, sOutputText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor, uDrawStyle, uDelay, 0xFF, 0xFFFFF);

		pGroup->InsertText(uWhere, pTextObject);

		//EnterCriticalSection(&m_videoGroupsCS);
		//m_drawList.AddHead(pTextObject);
		//LeaveCriticalSection(&m_videoGroupsCS);
		return 0;
	}
	return -1;
}

LONG CMultiSAP::DelTextGroup(ULONG uGroupID)
{
	LONG ret = -1;
	EnterCriticalSection(&m_videoGroupsCS);
	std::map<ULONG, CEffectTextGroup*>::iterator iter = m_EffectTextGroup.begin();
	for( ; iter != m_EffectTextGroup.end(); ++iter )
	{
		CEffectTextGroup * pGroup = iter->second;
		if (pGroup->GetObjectID() == uGroupID )
		{
			m_EffectTextGroup.erase(iter);
		}
	}
	POSITION pos = m_drawList.GetHeadPosition();
	while( pos )
	{
		POSITION tempPos = pos;
		CAnsoplyObject * pObject = m_drawList.GetNext( pos );
		if( pObject && pObject->GetObjectID() == uGroupID )
		{
			m_drawList.RemoveAt( tempPos );
			delete pObject;
			ret = 0;
			break;
		}
	}
	LeaveCriticalSection(&m_videoGroupsCS);
	return ret;
}

LONG CMultiSAP::SetBitmapParam(ULONG uBitmapID, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight)
{
	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.begin();
	for( ; iter != m_dy_ef_bmp_Group.end(); ++iter )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		std::list<CEffectBitmapEx*>::iterator iterinner = pGroup->m_effectbmplist.begin();
		for (; iterinner != pGroup->m_effectbmplist.end(); ++iterinner)
		{
			CEffectBitmapEx * pBitmap = *iterinner;
			if(pBitmap->GetObjectID() == uBitmapID)
			{
				pBitmap->SetBitmap(this, uAlpha, uTransparentColor, uX, uY, uWidth, uHeight);
				return 0;
			}
		}
	}
	return -1;
}

LONG CMultiSAP::SetTextParam(ULONG uTextID, ULONG uX, ULONG uY, LPCTSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG uAlpha, ULONG uTransparentColor)
{
	std::map<ULONG, CEffectTextGroup*>::iterator textiter = m_EffectTextGroup.begin();
	for( ; textiter != m_EffectTextGroup.end(); ++textiter )
	{
		CEffectTextGroup * pGroup = textiter->second;
		std::list<CEffectTextEx*>::iterator iterinner = pGroup->m_effectextlist.begin();
		for (; iterinner != pGroup->m_effectextlist.end(); ++iterinner)
		{
			CEffectTextEx * pText = *iterinner;
			if(pText->GetObjectID() == uTextID)
			{
				pText->SetText(this, uX, uY, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor, uAlpha, uTransparentColor);
				return 0;
			}
		}
	}
	return -1;
}

LONG CMultiSAP::SetPlayParam(ULONG uGroupID, ULONG uID, ULONG uDrawStyle)
{
	int ret = -1;
	do 
	{
		std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.find(uGroupID);
		if( iter != m_dy_ef_bmp_Group.end() )
		{
			CDynaEfBmpGroup * pGroup = iter->second;
			EnterCriticalSection(&pGroup->m_cs);
			pGroup->m_group_type = PLAY_BY_GROUP;
			pGroup->m_group_draw_style = uDrawStyle;
			if( uID == 0 )
			{
				CEffectBitmapEx * pBitmap = *pGroup->m_iter;
				pBitmap->m_nProgress = 0;
				pBitmap->Clear();
				//pBitmap->m_uDrawStyle = uDrawStyle;
				ret = 0;
				LeaveCriticalSection(&pGroup->m_cs);
				break;
			}
			std::list<CEffectBitmapEx*>::iterator iterinner = pGroup->m_effectbmplist.begin();
			for (; iterinner != pGroup->m_effectbmplist.end(); ++iterinner)
			{
				CEffectBitmapEx * pBitmap = *iterinner;
				if(pBitmap->GetObjectID() == uID)
				{
					pGroup->m_iter = iterinner;
					//pBitmap->m_uDrawStyle = uDrawStyle;				
					ret = 0;
				}
			}
			LeaveCriticalSection(&pGroup->m_cs);
		}

	} while (false);

	do 
	{
		std::map<ULONG, CEffectTextGroup*>::iterator textiter = m_EffectTextGroup.find(uGroupID);
		if( textiter != m_EffectTextGroup.end() )
		{
			CEffectTextGroup * pGroup = textiter->second;
			EnterCriticalSection(&pGroup->m_cs);
			pGroup->m_group_type = PLAY_BY_GROUP;
			pGroup->m_group_draw_style = uDrawStyle;
			if( uID == 0 )
			{
				CEffectTextEx * pText = *pGroup->m_iter;
				//pText->m_uDrawStyle = uDrawStyle;
				ret = 0;
				LeaveCriticalSection(&pGroup->m_cs);
				break;
			}
			std::list<CEffectTextEx*>::iterator iterinner = pGroup->m_effectextlist.begin();
			for (; iterinner != pGroup->m_effectextlist.end(); ++iterinner)
			{
				CEffectTextEx * pText = *iterinner;
				if(pText->GetObjectID() == uID)
				{
					pGroup->m_iter = iterinner;
					//pText->m_uDrawStyle = uDrawStyle;	
					ret = 0;
				}
			}
			LeaveCriticalSection(&pGroup->m_cs);
		}
	} while (false);

	return ret;
}

LONG CMultiSAP::GetPlayParam(ULONG uGroupID, ULONG* uID, ULONG* uDrawStyle)
{
	std::map<ULONG, CDynaEfBmpGroup*>::iterator iter = m_dy_ef_bmp_Group.find(uGroupID);
	if( iter != m_dy_ef_bmp_Group.end() )
	{
		CDynaEfBmpGroup * pGroup = iter->second;
		EnterCriticalSection(&pGroup->m_cs);
		CEffectBitmapEx * pBitmap = *pGroup->m_iter;
		*uID = pBitmap->GetObjectID();
		*uDrawStyle = pBitmap->m_uDrawStyle;
		LeaveCriticalSection(&pGroup->m_cs);
		return 0;
	}

	std::map<ULONG, CEffectTextGroup*>::iterator textiter = m_EffectTextGroup.find(uGroupID);
	if( textiter != m_EffectTextGroup.end() )
	{
		CEffectTextGroup * pGroup = textiter->second;
		EnterCriticalSection(&pGroup->m_cs);
		CEffectTextEx * pText = *pGroup->m_iter;
		*uID = pText->GetObjectID();
		*uDrawStyle = pText->m_uDrawStyle;
		LeaveCriticalSection(&pGroup->m_cs);
		return 0;
	}

	return -1;
}
