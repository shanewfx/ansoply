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

STDMETHODIMP CAnsoplyInterface::GetBitmap(ULONG uBitmapID, BSTR* sBitmapFilePath, ULONG* uAlpha, ULONG* uTransparentColor, ULONG* uX, ULONG* uY)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return S_OK;
}

STDMETHODIMP CAnsoplyInterface::DelBitmap(ULONG uBitmapID)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->DelBitmap(uBitmapID);
}

STDMETHODIMP CAnsoplyInterface::SetDynamicBitmap(ULONG * uBitmapID, BSTR sBitmapFilePath, ULONG uAlpha, ULONG uTransparentColor, ULONG uX, ULONG uY, ULONG uMilliSec)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetDynamicBitmap(uBitmapID, 
		_com_util::ConvertBSTRToString(sBitmapFilePath),
		uAlpha, uTransparentColor, uX, uY, uMilliSec);
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

STDMETHODIMP CAnsoplyInterface::GetText(ULONG uID, ULONG* uX, ULONG* uY, BSTR* sOutputText, BSTR* sFaceName, ULONG* uItalic, ULONG* uBold, ULONG* uUnderLine, ULONG* uWidth, ULONG* uHeight, ULONG* uColor)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	
	TCHAR sText[1024];
	TCHAR FaceName[1024] = {0};
	ZeroMemory(sText, 1024);
	if ( 0 == m_pMultiSAP->GetText(uID, uX, uY, sText, FaceName, uItalic, uBold, uUnderLine, uWidth, uHeight, uColor) )
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
	return hr;
}

STDMETHODIMP CAnsoplyInterface::SetPlayRate(ULONG uGroupID, DOUBLE dRate)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SetPlayRate(uGroupID, dRate);
}

STDMETHODIMP CAnsoplyInterface::SelectVideoGroupByCoordinate(ULONG * uGroupID, ULONG cX, ULONG cY, ULONG uFrameColor)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SelectVideoGroupByCoordinate(uGroupID, cX, cY, uFrameColor);
}

STDMETHODIMP CAnsoplyInterface::SelectVideoGroup(ULONG uGroupID, ULONG uFrameColor)
{
	// TODO: Add your implementation code here
	if( !m_pMultiSAP )
		return E_FAIL;
	return m_pMultiSAP->SelectVideoGroup(uGroupID, uFrameColor);
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
	delete m_pMultiSAP;
	return S_OK;
}
