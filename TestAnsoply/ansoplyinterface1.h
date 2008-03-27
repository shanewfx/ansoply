#pragma once

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CAnsoplyinterface1 wrapper class

class CAnsoplyinterface1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CAnsoplyinterface1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xD1EBA581, 0x3B3, 0x42EA, { 0xB0, 0x97, 0x7F, 0x97, 0xF0, 0xAD, 0xB8, 0x7B } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:


// Operations
public:

// IAnsoplyInterface

// Functions
//

	void CreateVideoGroup(unsigned long * uNewGroupID)
	{
		static BYTE parms[] = VTS_PUI4 ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uNewGroupID);
	}
	void DelVideoGroup(unsigned long uGroupID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void AddVideoFile(unsigned long uGroupID, LPCTSTR sFilePathName, unsigned long * uFileObjectID)
	{
		static BYTE parms[] = VTS_UI4 VTS_BSTR VTS_PUI4 ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, sFilePathName, uFileObjectID);
	}
	void DelVideoFile(unsigned long uGroupID, unsigned long uFileID)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uFileID);
	}
	void GetVideoObjectCount(unsigned long uGroupID, unsigned long * uFileCount)
	{
		static BYTE parms[] = VTS_UI4 VTS_PUI4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uFileCount);
	}
	void GetFirstVideoObjectID(unsigned long uGroupID, unsigned long * uFileID)
	{
		static BYTE parms[] = VTS_UI4 VTS_PUI4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uFileID);
	}
	void GetNextVideoObjectID(unsigned long uGroupID, unsigned long * uFileID)
	{
		static BYTE parms[] = VTS_UI4 VTS_PUI4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uFileID);
	}
	void GetVideoObjectFileName(unsigned long uGroupID, unsigned long uFileID, signed char * ch)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_PI1 ;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uFileID, ch);
	}
	void SetObjectLevel(unsigned long uObjectID, unsigned long uLevel)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uObjectID, uLevel);
	}
	void GetObjectLevel(unsigned long uObjectID, unsigned long * uLevel)
	{
		static BYTE parms[] = VTS_UI4 VTS_PUI4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uObjectID, uLevel);
	}
	void Play(unsigned long uGroupID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void Pause(unsigned long uGroupID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void Stop(unsigned long uGroupID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void Next(unsigned long uGroupID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void Previous(unsigned long uGroupID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void Seek(unsigned long GroupID, unsigned long uPosition)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, GroupID, uPosition);
	}
	void SavePlayList(LPCTSTR sFilePathName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sFilePathName);
	}
	void LoadPlayList(LPCTSTR sFilePathName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sFilePathName);
	}
	void SetVideoPosition(unsigned long uGroupID, unsigned long uX, unsigned long uY)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uX, uY);
	}
	void GetVideoPosition(unsigned long uGroupID, unsigned long * uX, unsigned long * uY)
	{
		static BYTE parms[] = VTS_UI4 VTS_PUI4 VTS_PUI4 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uX, uY);
	}
	void SetVideoPosAndSize(unsigned long uGroupID, unsigned long uX, unsigned long uY, unsigned long uWeight, unsigned long uHeight)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uX, uY, uWeight, uHeight);
	}
	void GetVideoPositionAndSize(unsigned long uGroupID, unsigned long * uX, unsigned long * uY, unsigned long * uWeight, unsigned long * uHeight)
	{
		static BYTE parms[] = VTS_UI4 VTS_PUI4 VTS_PUI4 VTS_PUI4 VTS_PUI4 ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uX, uY, uWeight, uHeight);
	}
	void SetVideoAlpha(unsigned long GroupID, unsigned long uAlpha)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms, GroupID, uAlpha);
	}
	void GetVideoAlpha(unsigned long uGroupID, unsigned long * uAlpha)
	{
		static BYTE parms[] = VTS_UI4 VTS_PUI4 ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uAlpha);
	}
	void SetBitmap(unsigned long * uBitmapID, LPCTSTR sBitmapFilePath, unsigned long uAlpha, unsigned long uTransparentColor, unsigned long uX, unsigned long uY, unsigned long uWidth, unsigned long uHeight, unsigned long uOriginalSize)
	{
		static BYTE parms[] = VTS_PUI4 VTS_BSTR VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uBitmapID, sBitmapFilePath, uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize);
	}
	void GetBitmap(unsigned long uBitmapID, BSTR * sBitmapFilePath, unsigned long * uAlpha, unsigned long * uTransparentColor, unsigned long * uX, unsigned long * uY)
	{
		static BYTE parms[] = VTS_UI4 VTS_PBSTR VTS_PUI4 VTS_PUI4 VTS_PUI4 VTS_PUI4 ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uBitmapID, sBitmapFilePath, uAlpha, uTransparentColor, uX, uY);
	}
	void DelBitmap(unsigned long uBitmapID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uBitmapID);
	}
	void SetDynamicBitmap(unsigned long * uBitmapID, LPCTSTR sBitmapFilePath, unsigned long uAlpha, unsigned long uTransparentColor, unsigned long uX, unsigned long uY, unsigned long uMilliSec)
	{
		static BYTE parms[] = VTS_PUI4 VTS_BSTR VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uBitmapID, sBitmapFilePath, uAlpha, uTransparentColor, uX, uY, uMilliSec);
	}
	void GetDynamicBitmap(unsigned long uBitmapID, BSTR * sBitmapFilePath, unsigned long * uAlpha, unsigned long * uTransparentColor, unsigned long * uX, unsigned long * uY, unsigned long * uMilliSec)
	{
		static BYTE parms[] = VTS_UI4 VTS_PBSTR VTS_PUI4 VTS_PUI4 VTS_PUI4 VTS_PUI4 VTS_PUI4 ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uBitmapID, sBitmapFilePath, uAlpha, uTransparentColor, uX, uY, uMilliSec);
	}
	void SetText(unsigned long uX, unsigned long uY, LPCTSTR sOutputText, LPCTSTR sFaceName, unsigned long uItalic, unsigned long uBold, unsigned long uUnderLine, unsigned long uWidth, unsigned long uHeight, unsigned long uColor, unsigned long * uObjectID)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_BSTR VTS_BSTR VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 VTS_PUI4 ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uX, uY, sOutputText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor, uObjectID);
	}
	void GetText(unsigned long uObjectID, unsigned long * uX, unsigned long * uY, BSTR * sOutputText, BSTR * sFaceName, unsigned long * uItalic, unsigned long * uBold, unsigned long * uUnderLine, unsigned long * uWidth, unsigned long * uHeight, unsigned long * uColor)
	{
		static BYTE parms[] = VTS_UI4 VTS_PUI4 VTS_PUI4 VTS_PBSTR VTS_PBSTR VTS_PUI4 VTS_PUI4 VTS_PUI4 VTS_PUI4 VTS_PUI4 VTS_PUI4 ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uObjectID, uX, uY, sOutputText, sFaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor);
	}
	void DelText(unsigned long uGroupID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void GetLastError()
	{
		InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Init(long hWnd, unsigned long uWidth, unsigned long uHeight)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms, hWnd, uWidth, uHeight);
	}
	void SetPlayRate(unsigned long uGroupID, double dRate)
	{
		static BYTE parms[] = VTS_UI4 VTS_R8 ;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, dRate);
	}
	void SelectVideoGroupByCoordinate(unsigned long * uGroupID, unsigned long cX, unsigned long cY, unsigned long uFrameColor)
	{
		static BYTE parms[] = VTS_PUI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, cX, cY, uFrameColor);
	}
	void SelectVideoGroup(unsigned long uGroupID, unsigned long uFrameColor)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uFrameColor);
	}
	void BringToFront(unsigned long uGroupID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void SendToBack(unsigned long uGroupID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void BringUp(unsigned long uGroup)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroup);
	}
	void SendBack(unsigned long uGroupID)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void SetPlayMode(unsigned long uGroupID, unsigned long uPlayMode)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uPlayMode);
	}
	void GetVideoLength(unsigned long uGroupID, unsigned long uFileID, double * uLength)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_PR8 ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uFileID, uLength);
	}
	void GetVideoGroupZOrder(unsigned long uGroupID, unsigned long * uZOrder)
	{
		static BYTE parms[] = VTS_UI4 VTS_PUI4 ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uZOrder);
	}
	void UnSelectVideoGroup()
	{
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetMediaFilePath(LPCTSTR sFilePathName)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, sFilePathName);
	}
	void SetDefaultVideoSize(unsigned long uGroupID, unsigned long uX, unsigned long uY)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID, uX, uY);
	}
	void GetVideoGroupCount(unsigned long * uGroupCount)
	{
		static BYTE parms[] = VTS_PUI4 ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupCount);
	}
	void GetFirstVideoGroupID(unsigned long * uGroupID)
	{
		static BYTE parms[] = VTS_PUI4 ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}
	void GetNextVideoGroupID(unsigned long * uGroupID)
	{
		static BYTE parms[] = VTS_PUI4 ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, parms, uGroupID);
	}

// Properties
//



};
