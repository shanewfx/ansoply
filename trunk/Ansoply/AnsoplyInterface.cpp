// AnsoplyInterface.cpp : Implementation of CAnsoplyInterface
#include "stdafx.h"
#include "AnsoplyInterface.h"
#include ".\ansoplyinterface.h"
#include "project.h"
#include <comutil.h>
#pragma comment(lib, "comsupp.lib")


CFactoryTemplate g_Templates[1];

int g_cTemplates = 1; 
// CAnsoplyInterface

STDMETHODIMP CAnsoplyInterface::CreateVideoGroup(ULONG* uNewGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	LONG tempGroupID = m_pMultiSAP->CreateVideoGroup();
	if ( tempGroupID == -1 )
		return E_FAIL;

	*uNewGroupID = tempGroupID;

	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::DelVideoGroup(ULONG uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->DelVideoGroup(uGroupID);
}

STDMETHODIMP CAnsoplyInterface::AddVideoFile(ULONG uGroupID, BSTR sFilePathName, ULONG* uFileObjectID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	LONG FileObjectID = m_pMultiSAP->AddVideoFile( uGroupID, 
		_com_util::ConvertBSTRToString(sFilePathName) );
	if( FileObjectID == -1 )
		return E_FAIL;

	*uFileObjectID = FileObjectID;

	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::DelVideoFile(ULONG uGroupID, ULONG uFileID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->DelVideoFile(uGroupID, uFileID);
}

STDMETHODIMP CAnsoplyInterface::GetVideoObjectCount(ULONG uGroupID, ULONG * uFileCount)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	LONG FileCount = m_pMultiSAP->GetVideoObjectCount(uGroupID);
	if (FileCount == -1)
		return E_FAIL;

	*uFileCount = FileCount;

	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::GetFirstVideoObjectID(ULONG uGroupID, ULONG * uFileID)
{
	// TODO: Add your implementation code here
	LONG objectID = m_pMultiSAP->GetFirstVideoObjectID(uGroupID);
	if (objectID != -1)
	{
		*uFileID = objectID;
		return S_OK;
	}
	return E_FAIL;
}

STDMETHODIMP CAnsoplyInterface::GetNextVideoObjectID(ULONG uGroupID, ULONG * uFileID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	return m_pMultiSAP->GetNextVideoObjectID(uGroupID, *uFileID);
}

STDMETHODIMP CAnsoplyInterface::GetVideoObjectFileName(ULONG uGroupID, ULONG uFileID, BSTR * sFilePathName)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	WCHAR   szFilePath[MAX_PATH]  = {0};
	if (m_pMultiSAP->GetVideoObjectFileName(uGroupID, uFileID, szFilePath) == S_OK)
	{
		//USES_CONVERSION;
		CAtlString s( szFilePath );
		*sFilePathName = s.AllocSysString();
		return S_OK;
	}

	return E_FAIL;
}

STDMETHODIMP CAnsoplyInterface::SetObjectLevel(ULONG uObjectID, ULONG uLevel)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::GetObjectLevel(ULONG uObjectID, ULONG* uLevel)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::Play(ULONG uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	m_pMultiSAP->Play( uGroupID );

	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::Pause(ULONG uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->Pause(uGroupID);
}

STDMETHODIMP CAnsoplyInterface::Stop(ULONG uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->Stop(uGroupID);
}

STDMETHODIMP CAnsoplyInterface::Next(ULONG uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->Next(uGroupID);
}

STDMETHODIMP CAnsoplyInterface::Previous(ULONG uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->Previous(uGroupID);
}

STDMETHODIMP CAnsoplyInterface::Seek(ULONG GroupID, ULONG uPosition)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->Seek(GroupID, uPosition);
}

STDMETHODIMP CAnsoplyInterface::SavePlayList(BSTR sFilePathName)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SavePlayList( _com_util::ConvertBSTRToString(sFilePathName) );
}

STDMETHODIMP CAnsoplyInterface::LoadPlayList(BSTR sFilePathName)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->LoadPlayList(_com_util::ConvertBSTRToString(sFilePathName));
}

STDMETHODIMP CAnsoplyInterface::SetVideoPosition(ULONG uGroupID, ULONG uX, ULONG uY)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::GetVideoPosition(ULONG uGroupID, ULONG* uX, ULONG* uY)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::SetVideoPosAndSize(ULONG uGroupID, ULONG uX, ULONG uY, ULONG uWeight, ULONG uHeight)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	return m_pMultiSAP->SetVideoPosAndSize(uGroupID, uX, uY, uWeight, uHeight);
}

STDMETHODIMP CAnsoplyInterface::GetVideoPositionAndSize(ULONG uGroupID, ULONG* uX, ULONG* uY, ULONG* uWeight, ULONG* uHeight)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;	

	return m_pMultiSAP->GetVideoPositionAndSize(uGroupID, uX, uY, uWeight, uHeight);
}

STDMETHODIMP CAnsoplyInterface::SetVideoAlpha(ULONG GroupID, ULONG uAlpha)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetVideoAlpha(GroupID, uAlpha);
}

STDMETHODIMP CAnsoplyInterface::GetVideoAlpha(ULONG uGroupID, ULONG* uAlpha)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->GetVideoAlpha(uGroupID, uAlpha);
}

STDMETHODIMP CAnsoplyInterface::SetBitmap(ULONG* uBitmapID, BSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	LONG lRetCode = -1;
	lRetCode = m_pMultiSAP->SetBitmap(_com_util::ConvertBSTRToString(sBitmapFilePath),
		uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize);
	*uBitmapID = lRetCode;
	return lRetCode != -1 ? S_OK : E_FAIL;
}

STDMETHODIMP CAnsoplyInterface::GetBitmap(ULONG uBitmapID, BSTR* sBitmapFilePath, ULONG* uAlpha, ULONG* uTransparentColor, ULONG* uX, ULONG* uY, ULONG* uWidth, ULONG* uHeight, ULONG* uOriginalSize, ULONG* uDrawStyle, ULONG* uDelay)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	m_pMultiSAP->GetBitmap(uBitmapID, sBitmapFilePath, uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, uDrawStyle, uDelay);

	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::DelBitmap(ULONG uBitmapID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->DelBitmap(uBitmapID);
}

STDMETHODIMP CAnsoplyInterface::SetDynamicBitmap(ULONG * uBitmapID,
												 BSTR sBitmapFilePath,
												 ULONG uAlpha, 
												 ULONG uTransparentColor,
												 ULONG uX, 
												 ULONG uY, 	
												 ULONG uWidth,
												 ULONG uHeight,
												 ULONG uOriginalSize,
											     ULONG uMilliSec)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetDynamicBitmap(uBitmapID, 
		_com_util::ConvertBSTRToString(sBitmapFilePath),
		uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, uMilliSec);
}

STDMETHODIMP CAnsoplyInterface::GetDynamicBitmap(ULONG uBitmapID, BSTR* sBitmapFilePath, ULONG* uAlpha, ULONG* uTransparentColor, ULONG* uX, ULONG* uY, ULONG* uMilliSec)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::SetText(ULONG uX, ULONG uY, BSTR sOutputText, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetText(uX, uY,
		_com_util::ConvertBSTRToString(sOutputText),
		_com_util::ConvertBSTRToString(sFaceName),
		uItalic,
		uBold,
		uUnderLine,
		uWidth,
		uHeight,
		uColor, 
		uObjectID);
}

STDMETHODIMP CAnsoplyInterface::GetText(ULONG uID, ULONG* uX, ULONG* uY, BSTR* sOutputText, BSTR* sFaceName, ULONG* uItalic, ULONG* uBold, ULONG* uUnderLine, ULONG* uWidth, ULONG* uHeight, ULONG* uColor, ULONG* uAlpha, ULONG* uTransparentColor, ULONG* uDrawStyle, ULONG* uDelay)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	
	TCHAR sText[1024];
	TCHAR FaceName[1024] = {0};
	ZeroMemory(sText, 1024);
	if ( 0 == m_pMultiSAP->GetText(uID, uX, uY, sText, FaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor, uAlpha, uTransparentColor, uDrawStyle, uDelay) )
	{
		*sOutputText = _com_util::ConvertStringToBSTR(sText);
		*sFaceName   = _com_util::ConvertStringToBSTR(FaceName);
		return S_OK;
	}
	return E_FAIL;
}

STDMETHODIMP CAnsoplyInterface::DelText(ULONG uID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	return m_pMultiSAP->DelText(uID);
}

STDMETHODIMP CAnsoplyInterface::GetLastError(void)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::Init(LONG hWnd, ULONG uWidth, ULONG uHeight)
{
	// TODO: Add your implementation code here
	HRESULT hr = S_OK;

	m_pMultiSAP = new CMultiSAP((HWND)hWnd, &hr, uWidth, uHeight);
	if ( !m_pMultiSAP || FAILED(hr) ) 
	{
		delete m_pMultiSAP;
		m_pMultiSAP = NULL;
		return E_FAIL;
	}
	hr = m_pMultiSAP->Initialize();

	//m_pMultiSAP = new CMultiSAP((HWND)hWnd, &hr, uWidth, uHeight);
	//if ( !m_pMultiSAP || FAILED(hr) ) 
	//{
	//	delete m_pMultiSAP;
	//	m_pMultiSAP = NULL;
	//	return E_FAIL;
	//}

	//hr = m_pMultiSAP->Initialize();
	return hr;
}

STDMETHODIMP CAnsoplyInterface::SetPlayRate(ULONG uGroupID, DOUBLE dRate)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetPlayRate(uGroupID, dRate);
}

STDMETHODIMP CAnsoplyInterface::SelectObjectByCoordinate(ULONG * uObjectID ,ULONG * uObjectType, ULONG cX, ULONG cY, ULONG uFrameColor)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SelectObjectByCoordinate(uObjectID, uObjectType, cX, cY, uFrameColor);
}

STDMETHODIMP CAnsoplyInterface::SelectObject(ULONG uGroupID, ULONG uFrameColor)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SelectObject(uGroupID, uFrameColor);
}

STDMETHODIMP CAnsoplyInterface::BringToFront(ULONG uObjectID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->BringToFront(uObjectID);
}

STDMETHODIMP CAnsoplyInterface::SendToBack(ULONG uObjectID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SendToBack(uObjectID);
}

STDMETHODIMP CAnsoplyInterface::BringUp(ULONG uObjectID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->BringUp(uObjectID);
}

STDMETHODIMP CAnsoplyInterface::SendBack(ULONG uObjectID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SendBack(uObjectID);
}

STDMETHODIMP CAnsoplyInterface::SetPlayMode(ULONG uGroupID, ULONG uPlayMode)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetPlayMode(uGroupID, uPlayMode);
}

STDMETHODIMP CAnsoplyInterface::GetVideoLength(ULONG uGroupID, ULONG uFileID, DOUBLE* uLength)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->GetVideoLength(uGroupID, uFileID, uLength);
}

STDMETHODIMP CAnsoplyInterface::GetVideoGroupZOrder(ULONG uGroupID, ULONG* uZOrder)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->GetVideoGroupZOrder(uGroupID, uZOrder);
}

STDMETHODIMP CAnsoplyInterface::UnSelectVideoGroup(void)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->UnSelectVideoGroup();
}

STDMETHODIMP CAnsoplyInterface::SetMediaFilePath(BSTR sFilePathName)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetMediaFilePath(_com_util::ConvertBSTRToString(sFilePathName));
}

STDMETHODIMP CAnsoplyInterface::SetDefaultVideoSize(ULONG uGroupID, ULONG uX, ULONG uY)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetDefaultVideoSize(uGroupID, uX, uY);
}

STDMETHODIMP CAnsoplyInterface::GetVideoGroupCount(ULONG * uGroupCount)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	*uGroupCount = m_pMultiSAP->GetVideoGroupCount();
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::GetFirstVideoGroupID(LONG * uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	*uGroupID = m_pMultiSAP->GetFirstVideoGroupID();
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::GetNextVideoGroupID(LONG * uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	m_pMultiSAP->GetNextVideoGroupID(*uGroupID);
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::Close(void)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	m_pMultiSAP->Close();
//	delete m_pMultiSAP;
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::Refresh(void)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	m_pMultiSAP->Refresh();
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::GetCurrentFileID(ULONG uGroupID, LONG* uFileID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
    m_pMultiSAP->GetCurrentFileID(uGroupID, uFileID);
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::GetCurrentPlayingPos(ULONG uGroupID, ULONG * uCurPos)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	m_pMultiSAP->GetCurrentPlayingPos(uGroupID, uCurPos);
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::SetTextInRegion(ULONG uX, ULONG uY, BSTR sOutputText, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID, ULONG uRegionWidth, ULONG uRegionHeight)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetTextInRegion(uX, uY,
		_com_util::ConvertBSTRToString(sOutputText),
		_com_util::ConvertBSTRToString(sFaceName),
		uItalic,
		uBold,
		uUnderLine,
		uWidth,
		uHeight,
		uColor, 
		uObjectID,
		uRegionWidth,
		uRegionHeight);
}

STDMETHODIMP CAnsoplyInterface::SetVideoFile(ULONG uGroupID, BSTR sFileName, ULONG uOldFileID, ULONG * uNewFileID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetVideoFile(uGroupID,
		_com_util::ConvertBSTRToString(sFileName),
		uOldFileID,
		uNewFileID);
}

STDMETHODIMP CAnsoplyInterface::SetVisibility(ULONG uObjectID, ULONG bVisibility)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetVisibility(uObjectID, bVisibility);
}

STDMETHODIMP CAnsoplyInterface::SetPlayTimes(ULONG uGroupID, ULONG uPlayTimes)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetPlayTimes(uGroupID, uPlayTimes);
}

STDMETHODIMP CAnsoplyInterface::SetPlayTimeout(ULONG uGroupID, ULONG uTimeout_s)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetPlayTimeout(uGroupID, uTimeout_s);
}

STDMETHODIMP CAnsoplyInterface::SetEffectBitmap(ULONG* uBitmapID, BSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG DrawStyle, ULONG uDelay)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	LONG lRetCode = -1;
	lRetCode = m_pMultiSAP->SetEffectBitmap(_com_util::ConvertBSTRToString(sBitmapFilePath),
		uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, DrawStyle, uDelay);
	*uBitmapID = lRetCode;
	return lRetCode != -1 ? S_OK : E_FAIL;
}

STDMETHODIMP CAnsoplyInterface::SetEffectBitmapStyle(ULONG uID, ULONG uStyle)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetEffectBitmapStyle(uID, uStyle) != -1 ? S_OK : E_FAIL;
}

STDMETHODIMP CAnsoplyInterface::SetEffectTextInRegion(ULONG uX, ULONG uY, BSTR sOutputText, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID, ULONG uRegionWidth, ULONG uRegionHeight, ULONG uDrawStyle, ULONG uDelay)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetEffectTextInRegion(uX, uY,
		_com_util::ConvertBSTRToString(sOutputText),
		_com_util::ConvertBSTRToString(sFaceName),
		uItalic,
		uBold,
		uUnderLine,
		uWidth,
		uHeight,
		uColor, 
		uObjectID,
		uRegionWidth,
		uRegionHeight,
		uDrawStyle,
		uDelay);
}

STDMETHODIMP CAnsoplyInterface::SetEffectPlayRange(ULONG uID, ULONG uPlayMode, ULONG uRangeStart, ULONG uRangeEnd)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetEffectPlayRange(uID, uPlayMode, uRangeStart, uRangeEnd);
}

STDMETHODIMP CAnsoplyInterface::SetEffectEndTime(ULONG uID, LONG EndTime)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetEffectEndTime(uID, EndTime);
}

STDMETHODIMP CAnsoplyInterface::SetDynamicEffectBitmap(ULONG* uBitmapID, BSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetDynamicEffectBitmap(uBitmapID, 
		_com_util::ConvertBSTRToString(sBitmapFilePath),
		uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, uDrawStyle);
}

STDMETHODIMP CAnsoplyInterface::CreateBitmapGroup(ULONG* uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	LONG tempGroupID = m_pMultiSAP->Create_Dy_Ef_Bmp_Group();
	if ( tempGroupID == -1 )
		return E_FAIL;

	*uGroupID = tempGroupID;

	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::AddBitmap(ULONG uGroupID, ULONG* uBitmapID, BSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle, ULONG uDelay)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	LONG lRetCode = -1;
	lRetCode = m_pMultiSAP->AddDynamicEffectBmp(uGroupID, _com_util::ConvertBSTRToString(sBitmapFilePath),
		uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, uDrawStyle, uDelay);
	*uBitmapID = lRetCode;
	return lRetCode != -1 ? S_OK : E_FAIL;
}

STDMETHODIMP CAnsoplyInterface::DelBitmapGroup(ULONG uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->DelBitmapGroup(uGroupID);
}

STDMETHODIMP CAnsoplyInterface::InsertBitmap(ULONG uGroupID, ULONG uWhere, ULONG* uBitmapID, BSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize, ULONG uDrawStyle, ULONG uDelay)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	LONG lRetCode = -1;
	lRetCode = m_pMultiSAP->InsertDynamicEffectBmp(uGroupID, uWhere,  _com_util::ConvertBSTRToString(sBitmapFilePath),
		uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize, uDrawStyle, uDelay);
	*uBitmapID = lRetCode;
	return lRetCode != -1 ? S_OK : E_FAIL;
}

STDMETHODIMP CAnsoplyInterface::CreateTextGroup(ULONG* uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;

	LONG tempGroupID = m_pMultiSAP->CreateTextGroup();
	if ( tempGroupID == -1 )
		return E_FAIL;

	*uGroupID = tempGroupID;
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::AddText(ULONG uGroupID, ULONG uX, ULONG uY, BSTR sOutputText, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID, ULONG uRegionWidth, ULONG uRegionHeight, ULONG uDrawStyle, ULONG uDelay, ULONG uAlpha, ULONG uTransparentColor)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->AddText(uGroupID, uX, uY,
		_com_util::ConvertBSTRToString(sOutputText),
		_com_util::ConvertBSTRToString(sFaceName),
		uItalic,
		uBold,
		uUnderLine,
		uWidth,
		uHeight,
		uColor, 
		uObjectID,
		uRegionWidth,
		uRegionHeight,
		uDrawStyle,
		uDelay,
		uAlpha,
		uTransparentColor);
}

STDMETHODIMP CAnsoplyInterface::DelTextGroup(ULONG uGroupID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->DelTextGroup(uGroupID);
}

STDMETHODIMP CAnsoplyInterface::InsertText(ULONG uGroupID, ULONG uWhere, ULONG uX, ULONG uY, BSTR sOutputText, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG* uObjectID, ULONG uRegionWidth, ULONG uRegionHeight, ULONG uDrawStyle, LONG uDelay)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->InsertEffectTextInRegion(uGroupID, uWhere, uX, uY,
		_com_util::ConvertBSTRToString(sOutputText),
		_com_util::ConvertBSTRToString(sFaceName),
		uItalic,
		uBold,
		uUnderLine,
		uWidth,
		uHeight,
		uColor, 
		uObjectID,
		uRegionWidth,
		uRegionHeight,
		uDrawStyle,
		uDelay);
}

STDMETHODIMP CAnsoplyInterface::SetBitmapParam(ULONG uBitmapID, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uWidth, ULONG uHeight, ULONG uOriginalSize)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetBitmapParam(uBitmapID, uAlpha, uTransparentColor, uX, uY, uWidth, uHeight, uOriginalSize);
}

STDMETHODIMP CAnsoplyInterface::SetTextParam(ULONG uTextID, ULONG uX, ULONG uY, BSTR sFaceName, ULONG uItalic, ULONG uBold, ULONG uUnderLine, ULONG uWidth, ULONG uHeight, ULONG uColor, ULONG uAlpha, ULONG uTransparentColor, ULONG uRegionWidth, ULONG uRegionHeight)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetTextParam(uTextID,uX, uY,
		_com_util::ConvertBSTRToString(sFaceName),
		uItalic,
		uBold,
		uUnderLine,
		uWidth,
		uHeight,
		uColor,
		uAlpha,
		uTransparentColor,
		uRegionWidth,
		uRegionHeight);
}

STDMETHODIMP CAnsoplyInterface::SetPlayParam(ULONG uGroupID, ULONG uID, ULONG uDrawStyle)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetPlayParam(uGroupID, uID, uDrawStyle);
}

STDMETHODIMP CAnsoplyInterface::GetPlayParam(ULONG uGroupID, ULONG* uID, ULONG* uDrawStyle)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->GetPlayParam(uGroupID, uID, uDrawStyle);
}
