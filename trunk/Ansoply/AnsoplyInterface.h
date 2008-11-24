// AnsoplyInterface.h : Declaration of the CAnsoplyInterface
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>

#include "CMultiSAP.h"

// IAnsoplyInterface
[
	object,
	uuid(016AACB4-4B78-40E7-9903-9D73AD75DAC5),
	dual,
	helpstring("IAnsoplyInterface Interface"),
	pointer_default(unique)
]
__interface IAnsoplyInterface : public IDispatch
{
	[id(1), helpstring("method CreateVideoGroup")] HRESULT CreateVideoGroup(ULONG* uNewGroupID);
	[id(2), helpstring("method DelVideoGroup")] HRESULT DelVideoGroup(ULONG uGroupID);
	[id(3), helpstring("method AddVideoFile")] HRESULT AddVideoFile(ULONG uGroupID, BSTR sFilePathName, ULONG* uFileObjectID);
	[id(4), helpstring("method DelVideoFile")] HRESULT DelVideoFile(ULONG uGroupID, ULONG uFileID);
	[id(5), helpstring("method GetVideoObjectCount")] HRESULT GetVideoObjectCount(ULONG uGroupID,ULONG * uFileCount);
	[id(6), helpstring("method GetFirstVideoObjectID")] HRESULT GetFirstVideoObjectID(ULONG uGroupID, ULONG * uFileID);
	[id(7), helpstring("method GetNextVideoObjectID")] HRESULT GetNextVideoObjectID(ULONG uGroupID, ULONG * uFileID);
	[id(8), helpstring("method GetVideoObjectFileName")] HRESULT GetVideoObjectFileName(ULONG uGroupID, ULONG uFileID, [out] BSTR * ch);
	[id(9), helpstring("method SetObjectLevel")] HRESULT SetObjectLevel(ULONG uObjectID, ULONG uLevel);
	[id(10), helpstring("method GetObjectLevel")] HRESULT GetObjectLevel(ULONG uObjectID, ULONG* uLevel);
	[id(11), helpstring("method Play")] HRESULT Play(ULONG uGroupID);
	[id(12), helpstring("method Pause")] HRESULT Pause(ULONG uGroupID);
	[id(13), helpstring("method Stop")] HRESULT Stop(ULONG uGroupID);
	[id(14), helpstring("method Next")] HRESULT Next(ULONG uGroupID);
	[id(15), helpstring("method Previous")] HRESULT Previous(ULONG uGroupID);
	[id(16), helpstring("method Seek")] HRESULT Seek(ULONG GroupID, ULONG uPosition);
	[id(17), helpstring("method SavePlayList")] HRESULT SavePlayList([in] BSTR sFilePathName);
	[id(18), helpstring("method LoadPlayList")] HRESULT LoadPlayList(BSTR sFilePathName);
	[id(19), helpstring("method SetVideoPosition")] HRESULT SetVideoPosition([in] ULONG uGroupID, [in] ULONG uX, [in] ULONG uY);
	[id(20), helpstring("method GetVideoPosition")] HRESULT GetVideoPosition([in] ULONG uGroupID, ULONG* uX, ULONG* uY);
	[id(21), helpstring("method SetVideoPosAndSize")] HRESULT SetVideoPosAndSize([in] ULONG uGroupID, ULONG uX, ULONG uY, [in] ULONG uWeight, [in] ULONG uHeight);
	[id(22), helpstring("method GetVideoPositionAndSize")] HRESULT GetVideoPositionAndSize([in] ULONG uGroupID, [in] ULONG* uX, ULONG* uY, [in] ULONG* uWeight, ULONG* uHeight);
	[id(23), helpstring("method SetVideoAlpha")] HRESULT SetVideoAlpha([in] ULONG GroupID, [in] ULONG uAlpha);
	[id(24), helpstring("method GetVideoAlpha")] HRESULT GetVideoAlpha([in] ULONG uGroupID, ULONG* uAlpha);
	[id(25), helpstring("method SetBitmap")] HRESULT SetBitmap(ULONG* uBitmapID, [in] BSTR sBitmapFilePath, [in] ULONG uAlpha, [in] ULONG uTransparentColor, [in] ULONG uX, [in] ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize);
	[id(26), helpstring("method GetBitmap")] HRESULT GetBitmap([in] ULONG uBitmapID, BSTR* sBitmapFilePath, [in] ULONG* uAlpha, ULONG* uTransparentColor, ULONG* uX, ULONG* uY);
	[id(27), helpstring("method DelBitmap")] HRESULT DelBitmap([in] ULONG uBitmapID);
	[id(28), helpstring("method SetDynamicBitmap")] HRESULT SetDynamicBitmap(ULONG * uBitmapID, [in] BSTR sBitmapFilePath, [in] ULONG uAlpha, [in] ULONG uTransparentColor, [in] ULONG uX, [in] ULONG uY, [in] ULONG uWidth, [in] ULONG uHeight, [in] ULONG uOriginalSize, [in] ULONG uMilliSec);
	[id(29), helpstring("method GetDynamicBitmap")] HRESULT GetDynamicBitmap(ULONG uBitmapID, BSTR* sBitmapFilePath, ULONG* uAlpha, ULONG* uTransparentColor, ULONG* uX, ULONG* uY, ULONG* uMilliSec);
	[id(30), helpstring("method SetText")] HRESULT SetText([in] ULONG uX, [in] ULONG uY, [in] BSTR sOutputText, [in] BSTR sFaceName, [in] ULONG uItalic, [in] ULONG uBold, [in] ULONG uUnderLine, [in]ULONG uWidth, [in] ULONG uHeight, [in] ULONG uColor, [in] ULONG* uObjectID);
	[id(31), helpstring("method GetText")] HRESULT GetText([in] ULONG uObjectID, ULONG* uX, ULONG* uY, BSTR* sOutputText, BSTR* sFaceName, ULONG* uItalic, ULONG* uBold, ULONG* uUnderLine, ULONG* uWidth, ULONG* uHeight, ULONG* uColor);
	[id(32), helpstring("method DelText")] HRESULT DelText(ULONG uGroupID);
	[id(33), helpstring("method GetLastError")] HRESULT GetLastError(void);
	[id(34), helpstring("method Init")] HRESULT Init([in] LONG hWnd, ULONG uWidth, ULONG uHeight);
	[id(35), helpstring("method SetPlayRate")] HRESULT SetPlayRate([in] ULONG uGroupID, [in] DOUBLE dRate);
	[id(36), helpstring("method SelectObjectByCoordinate")] HRESULT SelectObjectByCoordinate([in] ULONG * uGroupID, [in] ULONG * uObjectType, [in] ULONG cX, [in] ULONG cY, [in] ULONG uFrameColor);
	[id(37), helpstring("method SelectObject")] HRESULT SelectObject([in] ULONG uGroupID, [in] ULONG uFrameColor);
	[id(38), helpstring("method BringToFront")] HRESULT BringToFront([in] ULONG uObjectID);
	[id(39), helpstring("method SendToBack")] HRESULT SendToBack([in] ULONG uObjectID);
	[id(40), helpstring("method BringUp")] HRESULT BringUp([in] ULONG uObjectID);
	[id(41), helpstring("method SendBack")] HRESULT SendBack([in] ULONG uObjectID);
	[id(42), helpstring("method SetPlayMode")] HRESULT SetPlayMode([in] ULONG uGroupID, [in] ULONG uPlayMode);
	[id(43), helpstring("method GetVideoLength")] HRESULT GetVideoLength([in] ULONG uGroupID, [in] ULONG uFileID, [in] DOUBLE* uLength);
	[id(44), helpstring("method GetVideoGroupZOrder")] HRESULT GetVideoGroupZOrder([in] ULONG uGroupID, [in] ULONG* uZOrder);
	[id(45), helpstring("method UnSelectVideoGroup")] HRESULT UnSelectVideoGroup(void);
	[id(46), helpstring("method SetMediaFilePath")] HRESULT SetMediaFilePath(BSTR sFilePathName);
	[id(47), helpstring("method SetDefaultVideoSize")] HRESULT SetDefaultVideoSize(ULONG uGroupID, ULONG uX, ULONG uY);
	[id(48), helpstring("method GetVideoGroupCount")] HRESULT GetVideoGroupCount(ULONG * uGroupCount);
	[id(49), helpstring("method GetFirstVideoGroupID")] HRESULT GetFirstVideoGroupID(LONG * uGroupID);
	[id(50), helpstring("method GetNextVideoGroupID")] HRESULT GetNextVideoGroupID(LONG * uGroupID);
	[id(51), helpstring("method Close")] HRESULT Close(void);
	[id(52), helpstring("method Refresh")] HRESULT Refresh(void);
	[id(53), helpstring("method GetCurrentFileID")] HRESULT GetCurrentFileID(ULONG uGroupID, LONG* uFileID);
	[id(54), helpstring("method GetCurrentPlayingPos")] HRESULT GetCurrentPlayingPos(ULONG uGroupID, ULONG * uCurPos);
	[id(55), helpstring("method SetTextInRegion")] HRESULT SetTextInRegion(ULONG uX, ULONG uY, BSTR sOutputText, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID, ULONG uRegionWidth, ULONG uRegionHeight);
	[id(56), helpstring("method SetVideoFile")] HRESULT SetVideoFile(ULONG uGroupID, BSTR sFileName, ULONG uOldFileID, ULONG * uNewFileID);
	[id(57), helpstring("method SetVisibility")] HRESULT SetVisibility(ULONG uObjectID, ULONG bVisibility);
	[id(58), helpstring("method SetPlayTimes")] HRESULT SetPlayTimes(ULONG uGroupID, ULONG uPlayTimes);
	[id(59), helpstring("method SetPlayTimeout")] HRESULT SetPlayTimeout(ULONG uGroupID, ULONG uTimeout_s);
	[id(60), helpstring("method SetEffectBitmap")] HRESULT SetEffectBitmap(ULONG* uBitmapID, BSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG DrawStyle, ULONG uDelay);
	[id(61), helpstring("method SetEffectBitmapStyle")] HRESULT SetEffectBitmapStyle(ULONG uID, ULONG uStyle);
	[id(62), helpstring("method SetEffectTextInRegion")] HRESULT SetEffectTextInRegion(ULONG uX, ULONG uY, BSTR sOutputText, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID, ULONG uRegionWidth, ULONG uRegionHeight, ULONG uDrawStyle, ULONG uDelay);
	[id(63), helpstring("method SetEffectPlayRange")] HRESULT SetEffectPlayRange(ULONG uID, ULONG uPlayMode, ULONG uRangeStart, ULONG uRangeEnd);
	[id(64), helpstring("method SetEffectEndTime")] HRESULT SetEffectEndTime(ULONG uID, LONG EndTime);
};


// CAnsoplyInterface
[
	coclass,
	threading("apartment"),
	vi_progid("Ansoply.AnsoplyInterface"),
	progid("Ansoply.AnsoplyInterface.1"),
	version(1.0),
	uuid("D1EBA581-03B3-42EA-B097-7F97F0ADB87B"),
	helpstring("AnsoplyInterface Class"),
	support_error_info(IAnsoplyInterface),
	registration_script("control.rgs")
]
class ATL_NO_VTABLE CAnsoplyInterface : 
	public IAnsoplyInterface,
	public IPersistStreamInitImpl<CAnsoplyInterface>,
	public IOleControlImpl<CAnsoplyInterface>,
	public IOleObjectImpl<CAnsoplyInterface>,
	public IOleInPlaceActiveObjectImpl<CAnsoplyInterface>,
	public IViewObjectExImpl<CAnsoplyInterface>,
	public IOleInPlaceObjectWindowlessImpl<CAnsoplyInterface>,
	public IPersistStorageImpl<CAnsoplyInterface>,
	public ISpecifyPropertyPagesImpl<CAnsoplyInterface>,
	public IQuickActivateImpl<CAnsoplyInterface>,
	public IDataObjectImpl<CAnsoplyInterface>,
	public IProvideClassInfo2Impl<&__uuidof(CAnsoplyInterface), NULL>,
	public CComControl<CAnsoplyInterface>
{
public:

	CAnsoplyInterface()
	{
		m_pMultiSAP = NULL;
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)


BEGIN_PROP_MAP(CAnsoplyInterface)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()


BEGIN_MSG_MAP(CAnsoplyInterface)
	CHAIN_MSG_MAP(CComControl<CAnsoplyInterface>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

private:
	CMultiSAP * m_pMultiSAP;

// IAnsoplyInterface
public:
		HRESULT OnDraw(ATL_DRAWINFO& di)
		{
		RECT& rc = *(RECT*)di.prcBounds;
		// Set Clip region to the rectangle specified by di.prcBounds
		HRGN hRgnOld = NULL;
		if (GetClipRgn(di.hdcDraw, hRgnOld) != 1)
			hRgnOld = NULL;
		bool bSelectOldRgn = false;

		HRGN hRgnNew = CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);

		if (hRgnNew != NULL)
		{
			bSelectOldRgn = (SelectClipRgn(di.hdcDraw, hRgnNew) != ERROR);
		}

		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 7.0 : AnsoplyInterface");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		if (bSelectOldRgn)
			SelectClipRgn(di.hdcDraw, hRgnOld);

		return S_OK;
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}
	STDMETHOD(CreateVideoGroup)(ULONG* uNewGroupID);
	STDMETHOD(DelVideoGroup)(ULONG uGroupID);
	STDMETHOD(AddVideoFile)(ULONG uGroupID, BSTR sFilePathName, ULONG* uFileObjectID);
	STDMETHOD(DelVideoFile)(ULONG uGroupID, ULONG uFileID);
	STDMETHOD(GetVideoObjectCount)(ULONG uGroupID, ULONG * uFileCount);
	STDMETHOD(GetFirstVideoObjectID)(ULONG uGroupID, ULONG * uFileID);
	STDMETHOD(GetNextVideoObjectID)(ULONG uGroupID, ULONG * uFileID);
	STDMETHOD(GetVideoObjectFileName)(ULONG uGroupID, ULONG uFileID, BSTR * ch);
	STDMETHOD(SetObjectLevel)(ULONG uObjectID, ULONG uLevel);
	STDMETHOD(GetObjectLevel)(ULONG uObjectID, ULONG* uLevel);
	STDMETHOD(Play)(ULONG uGroupID);
	STDMETHOD(Pause)(ULONG uGroupID);
	STDMETHOD(Stop)(ULONG uGroupID);
	STDMETHOD(Next)(ULONG uGroupID);
	STDMETHOD(Previous)(ULONG uGroupID);
	STDMETHOD(Seek)(ULONG GroupID, ULONG uPosition);
	STDMETHOD(SavePlayList)(BSTR sFilePathName);
	STDMETHOD(LoadPlayList)(BSTR sFilePathName);
	STDMETHOD(SetVideoPosition)(ULONG uGroupID, ULONG uX, ULONG uY);
	STDMETHOD(GetVideoPosition)(ULONG uGroupID, ULONG* uX, ULONG* uY);
	STDMETHOD(SetVideoPosAndSize)(ULONG uGroupID, ULONG uX, ULONG uY, ULONG uWeight, ULONG uHeight);
	STDMETHOD(GetVideoPositionAndSize)(ULONG uGroupID, ULONG* uX, ULONG* uY, ULONG* uWeight, ULONG* uHeight);
	STDMETHOD(SetVideoAlpha)(ULONG GroupID, ULONG uAlpha);
	STDMETHOD(GetVideoAlpha)(ULONG uGroupID, ULONG* uAlpha);
	STDMETHOD(SetBitmap)(ULONG* uBitmapID, BSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize);
	STDMETHOD(GetBitmap)(ULONG uBitmapID, BSTR* sBitmapFilePath, ULONG* uAlpha, ULONG* uTransparentColor, ULONG* uX, ULONG* uY);
	STDMETHOD(DelBitmap)(ULONG uBitmapID);
	STDMETHOD(SetDynamicBitmap)(ULONG * uBitmapID, BSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uMilliSec);
	STDMETHOD(GetDynamicBitmap)(ULONG uBitmapID, BSTR* sBitmapFilePath, ULONG* uAlpha, ULONG* uTransparentColor, ULONG* uX, ULONG* uY, ULONG* uMilliSec);
	STDMETHOD(SetText)(ULONG uX, ULONG uY, BSTR sOutputText, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID);
	STDMETHOD(GetText)(ULONG uObjectID, ULONG* uX, ULONG* uY, BSTR* sOutputText, BSTR* sFaceName, ULONG* uItalic, ULONG* uBold, ULONG* uUnderLine, ULONG* uWidth, ULONG* uHeight, ULONG* uColor);
	STDMETHOD(DelText)(ULONG uGroupID);
	STDMETHOD(GetLastError)(void);
	STDMETHOD(Init)(LONG hWnd, ULONG uWidth, ULONG uHeight);
	STDMETHOD(SetPlayRate)(ULONG uGroupID, DOUBLE dRate);
	STDMETHOD(SelectObjectByCoordinate)(ULONG * uGroupID, ULONG * uObjectType, ULONG cX, ULONG cY, ULONG uFrameColor);
	STDMETHOD(SelectObject)(ULONG uGroupID, ULONG uFrameColor);
	STDMETHOD(BringToFront)(ULONG uObjectID);
	STDMETHOD(SendToBack)(ULONG uObjectID);
	STDMETHOD(BringUp)(ULONG uObjectID);
	STDMETHOD(SendBack)(ULONG uObjectID);
	STDMETHOD(SetPlayMode)(ULONG uGroupID, ULONG uPlayMode);
	STDMETHOD(GetVideoLength)(ULONG uGroupID, ULONG uFileID, DOUBLE* uLength);
	STDMETHOD(GetVideoGroupZOrder)(ULONG uGroupID, ULONG* uZOrder);
	STDMETHOD(UnSelectVideoGroup)(void);
	STDMETHOD(SetMediaFilePath)(BSTR sFilePathName);
	STDMETHOD(SetDefaultVideoSize)(ULONG uGroupID, ULONG uX, ULONG uY);
	STDMETHOD(GetVideoGroupCount)(ULONG * uGroupCount);
	STDMETHOD(GetFirstVideoGroupID)(LONG * uGroupID);
	STDMETHOD(GetNextVideoGroupID)(LONG * uGroupID);
	STDMETHOD(Close)(void);
	STDMETHOD(Refresh)(void);
	STDMETHOD(GetCurrentFileID)(ULONG uGroupID, LONG* uFileID);
	STDMETHOD(GetCurrentPlayingPos)(ULONG uGroupID, ULONG * uCurPos);
	STDMETHOD(SetTextInRegion)(ULONG uX, ULONG uY, BSTR sOutputText, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID, ULONG uRegionWidth, ULONG uRegionHeight);
	STDMETHOD(SetVideoFile)(ULONG uGroupID, BSTR sFileName, ULONG uOldFileID, ULONG * uNewFileID);
	STDMETHOD(SetVisibility)(ULONG uObjectID, ULONG bVisibility);
	STDMETHOD(SetPlayTimes)(ULONG uGroupID, ULONG uPlayTimes);
	STDMETHOD(SetPlayTimeout)(ULONG uGroupID, ULONG uTimeout_s);
	STDMETHOD(SetEffectBitmap)(ULONG* uBitmapID, BSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG DrawStyle, ULONG uDelay);
	STDMETHOD(SetEffectBitmapStyle)(ULONG uID, ULONG uStyle);
	STDMETHOD(SetEffectTextInRegion)(ULONG uX, ULONG uY, BSTR sOutputText, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID, ULONG uRegionWidth, ULONG uRegionHeight, ULONG uDrawStyle, ULONG uDelay);
	STDMETHOD(SetEffectPlayRange)(ULONG uID, ULONG uPlayMode, ULONG uRangeStart, ULONG uRangeEnd);
	STDMETHOD(SetEffectEndTime)(ULONG uID, LONG EndTime);
};

