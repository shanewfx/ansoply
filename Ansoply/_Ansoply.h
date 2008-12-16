

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue Dec 16 16:29:11 2008
 */
/* Compiler settings for _Ansoply.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___Ansoply_h__
#define ___Ansoply_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAnsoplyInterface_FWD_DEFINED__
#define __IAnsoplyInterface_FWD_DEFINED__
typedef interface IAnsoplyInterface IAnsoplyInterface;
#endif 	/* __IAnsoplyInterface_FWD_DEFINED__ */


#ifndef __CAnsoplyInterface_FWD_DEFINED__
#define __CAnsoplyInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAnsoplyInterface CAnsoplyInterface;
#else
typedef struct CAnsoplyInterface CAnsoplyInterface;
#endif /* __cplusplus */

#endif 	/* __CAnsoplyInterface_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IAnsoplyInterface_INTERFACE_DEFINED__
#define __IAnsoplyInterface_INTERFACE_DEFINED__

/* interface IAnsoplyInterface */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAnsoplyInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("016AACB4-4B78-40E7-9903-9D73AD75DAC5")
    IAnsoplyInterface : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateVideoGroup( 
            /* [in] */ ULONG *uNewGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DelVideoGroup( 
            /* [in] */ ULONG uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddVideoFile( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ BSTR sFilePathName,
            /* [in] */ ULONG *uFileObjectID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DelVideoFile( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uFileID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoObjectCount( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uFileCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFirstVideoObjectID( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uFileID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNextVideoObjectID( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uFileID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoObjectFileName( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uFileID,
            /* [out] */ BSTR *ch) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetObjectLevel( 
            /* [in] */ ULONG uObjectID,
            /* [in] */ ULONG uLevel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetObjectLevel( 
            /* [in] */ ULONG uObjectID,
            /* [in] */ ULONG *uLevel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Play( 
            /* [in] */ ULONG uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pause( 
            /* [in] */ ULONG uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( 
            /* [in] */ ULONG uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Previous( 
            /* [in] */ ULONG uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Seek( 
            /* [in] */ ULONG GroupID,
            /* [in] */ ULONG uPosition) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SavePlayList( 
            /* [in] */ BSTR sFilePathName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadPlayList( 
            /* [in] */ BSTR sFilePathName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVideoPosition( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoPosition( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uX,
            /* [in] */ ULONG *uY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVideoPosAndSize( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWeight,
            /* [in] */ ULONG uHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoPositionAndSize( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uX,
            /* [in] */ ULONG *uY,
            /* [in] */ ULONG *uWeight,
            /* [in] */ ULONG *uHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVideoAlpha( 
            /* [in] */ ULONG GroupID,
            /* [in] */ ULONG uAlpha) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoAlpha( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uAlpha) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBitmap( 
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBitmap( 
            /* [in] */ ULONG uBitmapID,
            /* [in] */ BSTR *sBitmapFilePath,
            /* [in] */ ULONG *uAlpha,
            /* [in] */ ULONG *uTransparentColor,
            /* [in] */ ULONG *uX,
            /* [in] */ ULONG *uY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DelBitmap( 
            /* [in] */ ULONG uBitmapID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDynamicBitmap( 
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize,
            /* [in] */ ULONG uMilliSec) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDynamicBitmap( 
            /* [in] */ ULONG uBitmapID,
            /* [in] */ BSTR *sBitmapFilePath,
            /* [in] */ ULONG *uAlpha,
            /* [in] */ ULONG *uTransparentColor,
            /* [in] */ ULONG *uX,
            /* [in] */ ULONG *uY,
            /* [in] */ ULONG *uMilliSec) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetText( 
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ BSTR sOutputText,
            /* [in] */ BSTR sFaceName,
            /* [in] */ ULONG uItalic,
            /* [in] */ ULONG uBold,
            /* [in] */ ULONG uUnderLine,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uColor,
            /* [in] */ ULONG *uObjectID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetText( 
            /* [in] */ ULONG uObjectID,
            /* [in] */ ULONG *uX,
            /* [in] */ ULONG *uY,
            /* [in] */ BSTR *sOutputText,
            /* [in] */ BSTR *sFaceName,
            /* [in] */ ULONG *uItalic,
            /* [in] */ ULONG *uBold,
            /* [in] */ ULONG *uUnderLine,
            /* [in] */ ULONG *uWidth,
            /* [in] */ ULONG *uHeight,
            /* [in] */ ULONG *uColor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DelText( 
            /* [in] */ ULONG uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLastError( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ LONG hWnd,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPlayRate( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ DOUBLE dRate) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectObjectByCoordinate( 
            /* [in] */ ULONG *uGroupID,
            /* [in] */ ULONG *uObjectType,
            /* [in] */ ULONG cX,
            /* [in] */ ULONG cY,
            /* [in] */ ULONG uFrameColor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectObject( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uFrameColor) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BringToFront( 
            /* [in] */ ULONG uObjectID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendToBack( 
            /* [in] */ ULONG uObjectID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BringUp( 
            /* [in] */ ULONG uObjectID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendBack( 
            /* [in] */ ULONG uObjectID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPlayMode( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uPlayMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoLength( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uFileID,
            /* [in] */ DOUBLE *uLength) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoGroupZOrder( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uZOrder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnSelectVideoGroup( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMediaFilePath( 
            /* [in] */ BSTR sFilePathName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDefaultVideoSize( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVideoGroupCount( 
            /* [in] */ ULONG *uGroupCount) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFirstVideoGroupID( 
            /* [in] */ LONG *uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNextVideoGroupID( 
            /* [in] */ LONG *uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCurrentFileID( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ LONG *uFileID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCurrentPlayingPos( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uCurPos) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTextInRegion( 
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ BSTR sOutputText,
            /* [in] */ BSTR sFaceName,
            /* [in] */ ULONG uItalic,
            /* [in] */ ULONG uBold,
            /* [in] */ ULONG uUnderLine,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uColor,
            /* [in] */ ULONG *uObjectID,
            /* [in] */ ULONG uRegionWidth,
            /* [in] */ ULONG uRegionHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVideoFile( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ BSTR sFileName,
            /* [in] */ ULONG uOldFileID,
            /* [in] */ ULONG *uNewFileID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetVisibility( 
            /* [in] */ ULONG uObjectID,
            /* [in] */ ULONG bVisibility) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPlayTimes( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uPlayTimes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPlayTimeout( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uTimeout_s) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEffectBitmap( 
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize,
            /* [in] */ ULONG DrawStyle,
            /* [in] */ ULONG uDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEffectBitmapStyle( 
            /* [in] */ ULONG uID,
            /* [in] */ ULONG uStyle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEffectTextInRegion( 
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ BSTR sOutputText,
            /* [in] */ BSTR sFaceName,
            /* [in] */ ULONG uItalic,
            /* [in] */ ULONG uBold,
            /* [in] */ ULONG uUnderLine,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uColor,
            /* [in] */ ULONG *uObjectID,
            /* [in] */ ULONG uRegionWidth,
            /* [in] */ ULONG uRegionHeight,
            /* [in] */ ULONG uDrawStyle,
            /* [in] */ ULONG uDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEffectPlayRange( 
            /* [in] */ ULONG uID,
            /* [in] */ ULONG uPlayMode,
            /* [in] */ ULONG uRangeStart,
            /* [in] */ ULONG uRangeEnd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEffectEndTime( 
            /* [in] */ ULONG uID,
            /* [in] */ LONG EndTime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDynamicEffectBitmap( 
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize,
            /* [in] */ ULONG uDrawStyle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateBitmapGroup( 
            /* [in] */ ULONG *uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddBitmap( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize,
            /* [in] */ ULONG uDrawStyle,
            /* [in] */ ULONG uDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DelBitmapGroup( 
            /* [in] */ ULONG uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertBitmap( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uWhere,
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize,
            /* [in] */ ULONG uDrawStyle,
            /* [in] */ ULONG uDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateTextGroup( 
            /* [in] */ ULONG *uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddText( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ BSTR sOutputText,
            /* [in] */ BSTR sFaceName,
            /* [in] */ ULONG uItalic,
            /* [in] */ ULONG uBold,
            /* [in] */ ULONG uUnderLine,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uColor,
            /* [in] */ ULONG *uObjectID,
            /* [in] */ ULONG uRegionWidth,
            /* [in] */ ULONG uRegionHeight,
            /* [in] */ ULONG uDrawStyle,
            /* [in] */ ULONG uDelay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DelTextGroup( 
            /* [in] */ ULONG uGroupID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertText( 
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uWhere,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ BSTR sOutputText,
            /* [in] */ BSTR sFaceName,
            /* [in] */ ULONG uItalic,
            /* [in] */ ULONG uBold,
            /* [in] */ ULONG uUnderLine,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uColor,
            /* [in] */ ULONG *uObjectID,
            /* [in] */ ULONG uRegionWidth,
            /* [in] */ ULONG uRegionHeight,
            /* [in] */ ULONG uDrawStyle,
            /* [in] */ LONG uDelay) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAnsoplyInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAnsoplyInterface * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAnsoplyInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAnsoplyInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAnsoplyInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAnsoplyInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAnsoplyInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAnsoplyInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateVideoGroup )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG *uNewGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DelVideoGroup )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddVideoFile )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ BSTR sFilePathName,
            /* [in] */ ULONG *uFileObjectID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DelVideoFile )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uFileID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoObjectCount )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uFileCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFirstVideoObjectID )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uFileID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNextVideoObjectID )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uFileID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoObjectFileName )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uFileID,
            /* [out] */ BSTR *ch);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetObjectLevel )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uObjectID,
            /* [in] */ ULONG uLevel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetObjectLevel )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uObjectID,
            /* [in] */ ULONG *uLevel);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Play )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pause )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Previous )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Seek )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG GroupID,
            /* [in] */ ULONG uPosition);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SavePlayList )( 
            IAnsoplyInterface * This,
            /* [in] */ BSTR sFilePathName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadPlayList )( 
            IAnsoplyInterface * This,
            /* [in] */ BSTR sFilePathName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVideoPosition )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoPosition )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uX,
            /* [in] */ ULONG *uY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVideoPosAndSize )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWeight,
            /* [in] */ ULONG uHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoPositionAndSize )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uX,
            /* [in] */ ULONG *uY,
            /* [in] */ ULONG *uWeight,
            /* [in] */ ULONG *uHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVideoAlpha )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG GroupID,
            /* [in] */ ULONG uAlpha);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoAlpha )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uAlpha);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetBitmap )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBitmap )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uBitmapID,
            /* [in] */ BSTR *sBitmapFilePath,
            /* [in] */ ULONG *uAlpha,
            /* [in] */ ULONG *uTransparentColor,
            /* [in] */ ULONG *uX,
            /* [in] */ ULONG *uY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DelBitmap )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uBitmapID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDynamicBitmap )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize,
            /* [in] */ ULONG uMilliSec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDynamicBitmap )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uBitmapID,
            /* [in] */ BSTR *sBitmapFilePath,
            /* [in] */ ULONG *uAlpha,
            /* [in] */ ULONG *uTransparentColor,
            /* [in] */ ULONG *uX,
            /* [in] */ ULONG *uY,
            /* [in] */ ULONG *uMilliSec);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetText )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ BSTR sOutputText,
            /* [in] */ BSTR sFaceName,
            /* [in] */ ULONG uItalic,
            /* [in] */ ULONG uBold,
            /* [in] */ ULONG uUnderLine,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uColor,
            /* [in] */ ULONG *uObjectID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetText )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uObjectID,
            /* [in] */ ULONG *uX,
            /* [in] */ ULONG *uY,
            /* [in] */ BSTR *sOutputText,
            /* [in] */ BSTR *sFaceName,
            /* [in] */ ULONG *uItalic,
            /* [in] */ ULONG *uBold,
            /* [in] */ ULONG *uUnderLine,
            /* [in] */ ULONG *uWidth,
            /* [in] */ ULONG *uHeight,
            /* [in] */ ULONG *uColor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DelText )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLastError )( 
            IAnsoplyInterface * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IAnsoplyInterface * This,
            /* [in] */ LONG hWnd,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPlayRate )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ DOUBLE dRate);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectObjectByCoordinate )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG *uGroupID,
            /* [in] */ ULONG *uObjectType,
            /* [in] */ ULONG cX,
            /* [in] */ ULONG cY,
            /* [in] */ ULONG uFrameColor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectObject )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uFrameColor);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BringToFront )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uObjectID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendToBack )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uObjectID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BringUp )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uObjectID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SendBack )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uObjectID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPlayMode )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uPlayMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoLength )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uFileID,
            /* [in] */ DOUBLE *uLength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoGroupZOrder )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uZOrder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnSelectVideoGroup )( 
            IAnsoplyInterface * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetMediaFilePath )( 
            IAnsoplyInterface * This,
            /* [in] */ BSTR sFilePathName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDefaultVideoSize )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetVideoGroupCount )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG *uGroupCount);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFirstVideoGroupID )( 
            IAnsoplyInterface * This,
            /* [in] */ LONG *uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNextVideoGroupID )( 
            IAnsoplyInterface * This,
            /* [in] */ LONG *uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            IAnsoplyInterface * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IAnsoplyInterface * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCurrentFileID )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ LONG *uFileID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCurrentPlayingPos )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uCurPos);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetTextInRegion )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ BSTR sOutputText,
            /* [in] */ BSTR sFaceName,
            /* [in] */ ULONG uItalic,
            /* [in] */ ULONG uBold,
            /* [in] */ ULONG uUnderLine,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uColor,
            /* [in] */ ULONG *uObjectID,
            /* [in] */ ULONG uRegionWidth,
            /* [in] */ ULONG uRegionHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVideoFile )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ BSTR sFileName,
            /* [in] */ ULONG uOldFileID,
            /* [in] */ ULONG *uNewFileID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetVisibility )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uObjectID,
            /* [in] */ ULONG bVisibility);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPlayTimes )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uPlayTimes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetPlayTimeout )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uTimeout_s);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEffectBitmap )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize,
            /* [in] */ ULONG DrawStyle,
            /* [in] */ ULONG uDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEffectBitmapStyle )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uID,
            /* [in] */ ULONG uStyle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEffectTextInRegion )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ BSTR sOutputText,
            /* [in] */ BSTR sFaceName,
            /* [in] */ ULONG uItalic,
            /* [in] */ ULONG uBold,
            /* [in] */ ULONG uUnderLine,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uColor,
            /* [in] */ ULONG *uObjectID,
            /* [in] */ ULONG uRegionWidth,
            /* [in] */ ULONG uRegionHeight,
            /* [in] */ ULONG uDrawStyle,
            /* [in] */ ULONG uDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEffectPlayRange )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uID,
            /* [in] */ ULONG uPlayMode,
            /* [in] */ ULONG uRangeStart,
            /* [in] */ ULONG uRangeEnd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetEffectEndTime )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uID,
            /* [in] */ LONG EndTime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetDynamicEffectBitmap )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize,
            /* [in] */ ULONG uDrawStyle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateBitmapGroup )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG *uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddBitmap )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize,
            /* [in] */ ULONG uDrawStyle,
            /* [in] */ ULONG uDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DelBitmapGroup )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InsertBitmap )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uWhere,
            /* [in] */ ULONG *uBitmapID,
            /* [in] */ BSTR sBitmapFilePath,
            /* [in] */ ULONG uAlpha,
            /* [in] */ ULONG uTransparentColor,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uOriginalSize,
            /* [in] */ ULONG uDrawStyle,
            /* [in] */ ULONG uDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CreateTextGroup )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG *uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddText )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ BSTR sOutputText,
            /* [in] */ BSTR sFaceName,
            /* [in] */ ULONG uItalic,
            /* [in] */ ULONG uBold,
            /* [in] */ ULONG uUnderLine,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uColor,
            /* [in] */ ULONG *uObjectID,
            /* [in] */ ULONG uRegionWidth,
            /* [in] */ ULONG uRegionHeight,
            /* [in] */ ULONG uDrawStyle,
            /* [in] */ ULONG uDelay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DelTextGroup )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InsertText )( 
            IAnsoplyInterface * This,
            /* [in] */ ULONG uGroupID,
            /* [in] */ ULONG uWhere,
            /* [in] */ ULONG uX,
            /* [in] */ ULONG uY,
            /* [in] */ BSTR sOutputText,
            /* [in] */ BSTR sFaceName,
            /* [in] */ ULONG uItalic,
            /* [in] */ ULONG uBold,
            /* [in] */ ULONG uUnderLine,
            /* [in] */ ULONG uWidth,
            /* [in] */ ULONG uHeight,
            /* [in] */ ULONG uColor,
            /* [in] */ ULONG *uObjectID,
            /* [in] */ ULONG uRegionWidth,
            /* [in] */ ULONG uRegionHeight,
            /* [in] */ ULONG uDrawStyle,
            /* [in] */ LONG uDelay);
        
        END_INTERFACE
    } IAnsoplyInterfaceVtbl;

    interface IAnsoplyInterface
    {
        CONST_VTBL struct IAnsoplyInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnsoplyInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAnsoplyInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAnsoplyInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAnsoplyInterface_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAnsoplyInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAnsoplyInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAnsoplyInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAnsoplyInterface_CreateVideoGroup(This,uNewGroupID)	\
    (This)->lpVtbl -> CreateVideoGroup(This,uNewGroupID)

#define IAnsoplyInterface_DelVideoGroup(This,uGroupID)	\
    (This)->lpVtbl -> DelVideoGroup(This,uGroupID)

#define IAnsoplyInterface_AddVideoFile(This,uGroupID,sFilePathName,uFileObjectID)	\
    (This)->lpVtbl -> AddVideoFile(This,uGroupID,sFilePathName,uFileObjectID)

#define IAnsoplyInterface_DelVideoFile(This,uGroupID,uFileID)	\
    (This)->lpVtbl -> DelVideoFile(This,uGroupID,uFileID)

#define IAnsoplyInterface_GetVideoObjectCount(This,uGroupID,uFileCount)	\
    (This)->lpVtbl -> GetVideoObjectCount(This,uGroupID,uFileCount)

#define IAnsoplyInterface_GetFirstVideoObjectID(This,uGroupID,uFileID)	\
    (This)->lpVtbl -> GetFirstVideoObjectID(This,uGroupID,uFileID)

#define IAnsoplyInterface_GetNextVideoObjectID(This,uGroupID,uFileID)	\
    (This)->lpVtbl -> GetNextVideoObjectID(This,uGroupID,uFileID)

#define IAnsoplyInterface_GetVideoObjectFileName(This,uGroupID,uFileID,ch)	\
    (This)->lpVtbl -> GetVideoObjectFileName(This,uGroupID,uFileID,ch)

#define IAnsoplyInterface_SetObjectLevel(This,uObjectID,uLevel)	\
    (This)->lpVtbl -> SetObjectLevel(This,uObjectID,uLevel)

#define IAnsoplyInterface_GetObjectLevel(This,uObjectID,uLevel)	\
    (This)->lpVtbl -> GetObjectLevel(This,uObjectID,uLevel)

#define IAnsoplyInterface_Play(This,uGroupID)	\
    (This)->lpVtbl -> Play(This,uGroupID)

#define IAnsoplyInterface_Pause(This,uGroupID)	\
    (This)->lpVtbl -> Pause(This,uGroupID)

#define IAnsoplyInterface_Stop(This,uGroupID)	\
    (This)->lpVtbl -> Stop(This,uGroupID)

#define IAnsoplyInterface_Next(This,uGroupID)	\
    (This)->lpVtbl -> Next(This,uGroupID)

#define IAnsoplyInterface_Previous(This,uGroupID)	\
    (This)->lpVtbl -> Previous(This,uGroupID)

#define IAnsoplyInterface_Seek(This,GroupID,uPosition)	\
    (This)->lpVtbl -> Seek(This,GroupID,uPosition)

#define IAnsoplyInterface_SavePlayList(This,sFilePathName)	\
    (This)->lpVtbl -> SavePlayList(This,sFilePathName)

#define IAnsoplyInterface_LoadPlayList(This,sFilePathName)	\
    (This)->lpVtbl -> LoadPlayList(This,sFilePathName)

#define IAnsoplyInterface_SetVideoPosition(This,uGroupID,uX,uY)	\
    (This)->lpVtbl -> SetVideoPosition(This,uGroupID,uX,uY)

#define IAnsoplyInterface_GetVideoPosition(This,uGroupID,uX,uY)	\
    (This)->lpVtbl -> GetVideoPosition(This,uGroupID,uX,uY)

#define IAnsoplyInterface_SetVideoPosAndSize(This,uGroupID,uX,uY,uWeight,uHeight)	\
    (This)->lpVtbl -> SetVideoPosAndSize(This,uGroupID,uX,uY,uWeight,uHeight)

#define IAnsoplyInterface_GetVideoPositionAndSize(This,uGroupID,uX,uY,uWeight,uHeight)	\
    (This)->lpVtbl -> GetVideoPositionAndSize(This,uGroupID,uX,uY,uWeight,uHeight)

#define IAnsoplyInterface_SetVideoAlpha(This,GroupID,uAlpha)	\
    (This)->lpVtbl -> SetVideoAlpha(This,GroupID,uAlpha)

#define IAnsoplyInterface_GetVideoAlpha(This,uGroupID,uAlpha)	\
    (This)->lpVtbl -> GetVideoAlpha(This,uGroupID,uAlpha)

#define IAnsoplyInterface_SetBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize)	\
    (This)->lpVtbl -> SetBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize)

#define IAnsoplyInterface_GetBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY)	\
    (This)->lpVtbl -> GetBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY)

#define IAnsoplyInterface_DelBitmap(This,uBitmapID)	\
    (This)->lpVtbl -> DelBitmap(This,uBitmapID)

#define IAnsoplyInterface_SetDynamicBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize,uMilliSec)	\
    (This)->lpVtbl -> SetDynamicBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize,uMilliSec)

#define IAnsoplyInterface_GetDynamicBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uMilliSec)	\
    (This)->lpVtbl -> GetDynamicBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uMilliSec)

#define IAnsoplyInterface_SetText(This,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor,uObjectID)	\
    (This)->lpVtbl -> SetText(This,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor,uObjectID)

#define IAnsoplyInterface_GetText(This,uObjectID,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor)	\
    (This)->lpVtbl -> GetText(This,uObjectID,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor)

#define IAnsoplyInterface_DelText(This,uGroupID)	\
    (This)->lpVtbl -> DelText(This,uGroupID)

#define IAnsoplyInterface_GetLastError(This)	\
    (This)->lpVtbl -> GetLastError(This)

#define IAnsoplyInterface_Init(This,hWnd,uWidth,uHeight)	\
    (This)->lpVtbl -> Init(This,hWnd,uWidth,uHeight)

#define IAnsoplyInterface_SetPlayRate(This,uGroupID,dRate)	\
    (This)->lpVtbl -> SetPlayRate(This,uGroupID,dRate)

#define IAnsoplyInterface_SelectObjectByCoordinate(This,uGroupID,uObjectType,cX,cY,uFrameColor)	\
    (This)->lpVtbl -> SelectObjectByCoordinate(This,uGroupID,uObjectType,cX,cY,uFrameColor)

#define IAnsoplyInterface_SelectObject(This,uGroupID,uFrameColor)	\
    (This)->lpVtbl -> SelectObject(This,uGroupID,uFrameColor)

#define IAnsoplyInterface_BringToFront(This,uObjectID)	\
    (This)->lpVtbl -> BringToFront(This,uObjectID)

#define IAnsoplyInterface_SendToBack(This,uObjectID)	\
    (This)->lpVtbl -> SendToBack(This,uObjectID)

#define IAnsoplyInterface_BringUp(This,uObjectID)	\
    (This)->lpVtbl -> BringUp(This,uObjectID)

#define IAnsoplyInterface_SendBack(This,uObjectID)	\
    (This)->lpVtbl -> SendBack(This,uObjectID)

#define IAnsoplyInterface_SetPlayMode(This,uGroupID,uPlayMode)	\
    (This)->lpVtbl -> SetPlayMode(This,uGroupID,uPlayMode)

#define IAnsoplyInterface_GetVideoLength(This,uGroupID,uFileID,uLength)	\
    (This)->lpVtbl -> GetVideoLength(This,uGroupID,uFileID,uLength)

#define IAnsoplyInterface_GetVideoGroupZOrder(This,uGroupID,uZOrder)	\
    (This)->lpVtbl -> GetVideoGroupZOrder(This,uGroupID,uZOrder)

#define IAnsoplyInterface_UnSelectVideoGroup(This)	\
    (This)->lpVtbl -> UnSelectVideoGroup(This)

#define IAnsoplyInterface_SetMediaFilePath(This,sFilePathName)	\
    (This)->lpVtbl -> SetMediaFilePath(This,sFilePathName)

#define IAnsoplyInterface_SetDefaultVideoSize(This,uGroupID,uX,uY)	\
    (This)->lpVtbl -> SetDefaultVideoSize(This,uGroupID,uX,uY)

#define IAnsoplyInterface_GetVideoGroupCount(This,uGroupCount)	\
    (This)->lpVtbl -> GetVideoGroupCount(This,uGroupCount)

#define IAnsoplyInterface_GetFirstVideoGroupID(This,uGroupID)	\
    (This)->lpVtbl -> GetFirstVideoGroupID(This,uGroupID)

#define IAnsoplyInterface_GetNextVideoGroupID(This,uGroupID)	\
    (This)->lpVtbl -> GetNextVideoGroupID(This,uGroupID)

#define IAnsoplyInterface_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IAnsoplyInterface_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IAnsoplyInterface_GetCurrentFileID(This,uGroupID,uFileID)	\
    (This)->lpVtbl -> GetCurrentFileID(This,uGroupID,uFileID)

#define IAnsoplyInterface_GetCurrentPlayingPos(This,uGroupID,uCurPos)	\
    (This)->lpVtbl -> GetCurrentPlayingPos(This,uGroupID,uCurPos)

#define IAnsoplyInterface_SetTextInRegion(This,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor,uObjectID,uRegionWidth,uRegionHeight)	\
    (This)->lpVtbl -> SetTextInRegion(This,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor,uObjectID,uRegionWidth,uRegionHeight)

#define IAnsoplyInterface_SetVideoFile(This,uGroupID,sFileName,uOldFileID,uNewFileID)	\
    (This)->lpVtbl -> SetVideoFile(This,uGroupID,sFileName,uOldFileID,uNewFileID)

#define IAnsoplyInterface_SetVisibility(This,uObjectID,bVisibility)	\
    (This)->lpVtbl -> SetVisibility(This,uObjectID,bVisibility)

#define IAnsoplyInterface_SetPlayTimes(This,uGroupID,uPlayTimes)	\
    (This)->lpVtbl -> SetPlayTimes(This,uGroupID,uPlayTimes)

#define IAnsoplyInterface_SetPlayTimeout(This,uGroupID,uTimeout_s)	\
    (This)->lpVtbl -> SetPlayTimeout(This,uGroupID,uTimeout_s)

#define IAnsoplyInterface_SetEffectBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize,DrawStyle,uDelay)	\
    (This)->lpVtbl -> SetEffectBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize,DrawStyle,uDelay)

#define IAnsoplyInterface_SetEffectBitmapStyle(This,uID,uStyle)	\
    (This)->lpVtbl -> SetEffectBitmapStyle(This,uID,uStyle)

#define IAnsoplyInterface_SetEffectTextInRegion(This,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor,uObjectID,uRegionWidth,uRegionHeight,uDrawStyle,uDelay)	\
    (This)->lpVtbl -> SetEffectTextInRegion(This,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor,uObjectID,uRegionWidth,uRegionHeight,uDrawStyle,uDelay)

#define IAnsoplyInterface_SetEffectPlayRange(This,uID,uPlayMode,uRangeStart,uRangeEnd)	\
    (This)->lpVtbl -> SetEffectPlayRange(This,uID,uPlayMode,uRangeStart,uRangeEnd)

#define IAnsoplyInterface_SetEffectEndTime(This,uID,EndTime)	\
    (This)->lpVtbl -> SetEffectEndTime(This,uID,EndTime)

#define IAnsoplyInterface_SetDynamicEffectBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize,uDrawStyle)	\
    (This)->lpVtbl -> SetDynamicEffectBitmap(This,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize,uDrawStyle)

#define IAnsoplyInterface_CreateBitmapGroup(This,uGroupID)	\
    (This)->lpVtbl -> CreateBitmapGroup(This,uGroupID)

#define IAnsoplyInterface_AddBitmap(This,uGroupID,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize,uDrawStyle,uDelay)	\
    (This)->lpVtbl -> AddBitmap(This,uGroupID,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize,uDrawStyle,uDelay)

#define IAnsoplyInterface_DelBitmapGroup(This,uGroupID)	\
    (This)->lpVtbl -> DelBitmapGroup(This,uGroupID)

#define IAnsoplyInterface_InsertBitmap(This,uGroupID,uWhere,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize,uDrawStyle,uDelay)	\
    (This)->lpVtbl -> InsertBitmap(This,uGroupID,uWhere,uBitmapID,sBitmapFilePath,uAlpha,uTransparentColor,uX,uY,uWidth,uHeight,uOriginalSize,uDrawStyle,uDelay)

#define IAnsoplyInterface_CreateTextGroup(This,uGroupID)	\
    (This)->lpVtbl -> CreateTextGroup(This,uGroupID)

#define IAnsoplyInterface_AddText(This,uGroupID,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor,uObjectID,uRegionWidth,uRegionHeight,uDrawStyle,uDelay)	\
    (This)->lpVtbl -> AddText(This,uGroupID,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor,uObjectID,uRegionWidth,uRegionHeight,uDrawStyle,uDelay)

#define IAnsoplyInterface_DelTextGroup(This,uGroupID)	\
    (This)->lpVtbl -> DelTextGroup(This,uGroupID)

#define IAnsoplyInterface_InsertText(This,uGroupID,uWhere,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor,uObjectID,uRegionWidth,uRegionHeight,uDrawStyle,uDelay)	\
    (This)->lpVtbl -> InsertText(This,uGroupID,uWhere,uX,uY,sOutputText,sFaceName,uItalic,uBold,uUnderLine,uWidth,uHeight,uColor,uObjectID,uRegionWidth,uRegionHeight,uDrawStyle,uDelay)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_CreateVideoGroup_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG *uNewGroupID);


void __RPC_STUB IAnsoplyInterface_CreateVideoGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_DelVideoGroup_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID);


void __RPC_STUB IAnsoplyInterface_DelVideoGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_AddVideoFile_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ BSTR sFilePathName,
    /* [in] */ ULONG *uFileObjectID);


void __RPC_STUB IAnsoplyInterface_AddVideoFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_DelVideoFile_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uFileID);


void __RPC_STUB IAnsoplyInterface_DelVideoFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetVideoObjectCount_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG *uFileCount);


void __RPC_STUB IAnsoplyInterface_GetVideoObjectCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetFirstVideoObjectID_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG *uFileID);


void __RPC_STUB IAnsoplyInterface_GetFirstVideoObjectID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetNextVideoObjectID_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG *uFileID);


void __RPC_STUB IAnsoplyInterface_GetNextVideoObjectID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetVideoObjectFileName_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uFileID,
    /* [out] */ BSTR *ch);


void __RPC_STUB IAnsoplyInterface_GetVideoObjectFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetObjectLevel_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uObjectID,
    /* [in] */ ULONG uLevel);


void __RPC_STUB IAnsoplyInterface_SetObjectLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetObjectLevel_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uObjectID,
    /* [in] */ ULONG *uLevel);


void __RPC_STUB IAnsoplyInterface_GetObjectLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_Play_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID);


void __RPC_STUB IAnsoplyInterface_Play_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_Pause_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID);


void __RPC_STUB IAnsoplyInterface_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_Stop_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID);


void __RPC_STUB IAnsoplyInterface_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_Next_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID);


void __RPC_STUB IAnsoplyInterface_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_Previous_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID);


void __RPC_STUB IAnsoplyInterface_Previous_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_Seek_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG GroupID,
    /* [in] */ ULONG uPosition);


void __RPC_STUB IAnsoplyInterface_Seek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SavePlayList_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ BSTR sFilePathName);


void __RPC_STUB IAnsoplyInterface_SavePlayList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_LoadPlayList_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ BSTR sFilePathName);


void __RPC_STUB IAnsoplyInterface_LoadPlayList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetVideoPosition_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY);


void __RPC_STUB IAnsoplyInterface_SetVideoPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetVideoPosition_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG *uX,
    /* [in] */ ULONG *uY);


void __RPC_STUB IAnsoplyInterface_GetVideoPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetVideoPosAndSize_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ ULONG uWeight,
    /* [in] */ ULONG uHeight);


void __RPC_STUB IAnsoplyInterface_SetVideoPosAndSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetVideoPositionAndSize_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG *uX,
    /* [in] */ ULONG *uY,
    /* [in] */ ULONG *uWeight,
    /* [in] */ ULONG *uHeight);


void __RPC_STUB IAnsoplyInterface_GetVideoPositionAndSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetVideoAlpha_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG GroupID,
    /* [in] */ ULONG uAlpha);


void __RPC_STUB IAnsoplyInterface_SetVideoAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetVideoAlpha_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG *uAlpha);


void __RPC_STUB IAnsoplyInterface_GetVideoAlpha_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetBitmap_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG *uBitmapID,
    /* [in] */ BSTR sBitmapFilePath,
    /* [in] */ ULONG uAlpha,
    /* [in] */ ULONG uTransparentColor,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uOriginalSize);


void __RPC_STUB IAnsoplyInterface_SetBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetBitmap_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uBitmapID,
    /* [in] */ BSTR *sBitmapFilePath,
    /* [in] */ ULONG *uAlpha,
    /* [in] */ ULONG *uTransparentColor,
    /* [in] */ ULONG *uX,
    /* [in] */ ULONG *uY);


void __RPC_STUB IAnsoplyInterface_GetBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_DelBitmap_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uBitmapID);


void __RPC_STUB IAnsoplyInterface_DelBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetDynamicBitmap_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG *uBitmapID,
    /* [in] */ BSTR sBitmapFilePath,
    /* [in] */ ULONG uAlpha,
    /* [in] */ ULONG uTransparentColor,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uOriginalSize,
    /* [in] */ ULONG uMilliSec);


void __RPC_STUB IAnsoplyInterface_SetDynamicBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetDynamicBitmap_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uBitmapID,
    /* [in] */ BSTR *sBitmapFilePath,
    /* [in] */ ULONG *uAlpha,
    /* [in] */ ULONG *uTransparentColor,
    /* [in] */ ULONG *uX,
    /* [in] */ ULONG *uY,
    /* [in] */ ULONG *uMilliSec);


void __RPC_STUB IAnsoplyInterface_GetDynamicBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetText_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ BSTR sOutputText,
    /* [in] */ BSTR sFaceName,
    /* [in] */ ULONG uItalic,
    /* [in] */ ULONG uBold,
    /* [in] */ ULONG uUnderLine,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uColor,
    /* [in] */ ULONG *uObjectID);


void __RPC_STUB IAnsoplyInterface_SetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetText_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uObjectID,
    /* [in] */ ULONG *uX,
    /* [in] */ ULONG *uY,
    /* [in] */ BSTR *sOutputText,
    /* [in] */ BSTR *sFaceName,
    /* [in] */ ULONG *uItalic,
    /* [in] */ ULONG *uBold,
    /* [in] */ ULONG *uUnderLine,
    /* [in] */ ULONG *uWidth,
    /* [in] */ ULONG *uHeight,
    /* [in] */ ULONG *uColor);


void __RPC_STUB IAnsoplyInterface_GetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_DelText_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID);


void __RPC_STUB IAnsoplyInterface_DelText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetLastError_Proxy( 
    IAnsoplyInterface * This);


void __RPC_STUB IAnsoplyInterface_GetLastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_Init_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ LONG hWnd,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight);


void __RPC_STUB IAnsoplyInterface_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetPlayRate_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ DOUBLE dRate);


void __RPC_STUB IAnsoplyInterface_SetPlayRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SelectObjectByCoordinate_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG *uGroupID,
    /* [in] */ ULONG *uObjectType,
    /* [in] */ ULONG cX,
    /* [in] */ ULONG cY,
    /* [in] */ ULONG uFrameColor);


void __RPC_STUB IAnsoplyInterface_SelectObjectByCoordinate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SelectObject_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uFrameColor);


void __RPC_STUB IAnsoplyInterface_SelectObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_BringToFront_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uObjectID);


void __RPC_STUB IAnsoplyInterface_BringToFront_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SendToBack_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uObjectID);


void __RPC_STUB IAnsoplyInterface_SendToBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_BringUp_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uObjectID);


void __RPC_STUB IAnsoplyInterface_BringUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SendBack_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uObjectID);


void __RPC_STUB IAnsoplyInterface_SendBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetPlayMode_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uPlayMode);


void __RPC_STUB IAnsoplyInterface_SetPlayMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetVideoLength_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uFileID,
    /* [in] */ DOUBLE *uLength);


void __RPC_STUB IAnsoplyInterface_GetVideoLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetVideoGroupZOrder_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG *uZOrder);


void __RPC_STUB IAnsoplyInterface_GetVideoGroupZOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_UnSelectVideoGroup_Proxy( 
    IAnsoplyInterface * This);


void __RPC_STUB IAnsoplyInterface_UnSelectVideoGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetMediaFilePath_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ BSTR sFilePathName);


void __RPC_STUB IAnsoplyInterface_SetMediaFilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetDefaultVideoSize_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY);


void __RPC_STUB IAnsoplyInterface_SetDefaultVideoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetVideoGroupCount_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG *uGroupCount);


void __RPC_STUB IAnsoplyInterface_GetVideoGroupCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetFirstVideoGroupID_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ LONG *uGroupID);


void __RPC_STUB IAnsoplyInterface_GetFirstVideoGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetNextVideoGroupID_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ LONG *uGroupID);


void __RPC_STUB IAnsoplyInterface_GetNextVideoGroupID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_Close_Proxy( 
    IAnsoplyInterface * This);


void __RPC_STUB IAnsoplyInterface_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_Refresh_Proxy( 
    IAnsoplyInterface * This);


void __RPC_STUB IAnsoplyInterface_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetCurrentFileID_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ LONG *uFileID);


void __RPC_STUB IAnsoplyInterface_GetCurrentFileID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_GetCurrentPlayingPos_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG *uCurPos);


void __RPC_STUB IAnsoplyInterface_GetCurrentPlayingPos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetTextInRegion_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ BSTR sOutputText,
    /* [in] */ BSTR sFaceName,
    /* [in] */ ULONG uItalic,
    /* [in] */ ULONG uBold,
    /* [in] */ ULONG uUnderLine,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uColor,
    /* [in] */ ULONG *uObjectID,
    /* [in] */ ULONG uRegionWidth,
    /* [in] */ ULONG uRegionHeight);


void __RPC_STUB IAnsoplyInterface_SetTextInRegion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetVideoFile_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ BSTR sFileName,
    /* [in] */ ULONG uOldFileID,
    /* [in] */ ULONG *uNewFileID);


void __RPC_STUB IAnsoplyInterface_SetVideoFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetVisibility_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uObjectID,
    /* [in] */ ULONG bVisibility);


void __RPC_STUB IAnsoplyInterface_SetVisibility_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetPlayTimes_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uPlayTimes);


void __RPC_STUB IAnsoplyInterface_SetPlayTimes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetPlayTimeout_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uTimeout_s);


void __RPC_STUB IAnsoplyInterface_SetPlayTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetEffectBitmap_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG *uBitmapID,
    /* [in] */ BSTR sBitmapFilePath,
    /* [in] */ ULONG uAlpha,
    /* [in] */ ULONG uTransparentColor,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uOriginalSize,
    /* [in] */ ULONG DrawStyle,
    /* [in] */ ULONG uDelay);


void __RPC_STUB IAnsoplyInterface_SetEffectBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetEffectBitmapStyle_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uID,
    /* [in] */ ULONG uStyle);


void __RPC_STUB IAnsoplyInterface_SetEffectBitmapStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetEffectTextInRegion_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ BSTR sOutputText,
    /* [in] */ BSTR sFaceName,
    /* [in] */ ULONG uItalic,
    /* [in] */ ULONG uBold,
    /* [in] */ ULONG uUnderLine,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uColor,
    /* [in] */ ULONG *uObjectID,
    /* [in] */ ULONG uRegionWidth,
    /* [in] */ ULONG uRegionHeight,
    /* [in] */ ULONG uDrawStyle,
    /* [in] */ ULONG uDelay);


void __RPC_STUB IAnsoplyInterface_SetEffectTextInRegion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetEffectPlayRange_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uID,
    /* [in] */ ULONG uPlayMode,
    /* [in] */ ULONG uRangeStart,
    /* [in] */ ULONG uRangeEnd);


void __RPC_STUB IAnsoplyInterface_SetEffectPlayRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetEffectEndTime_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uID,
    /* [in] */ LONG EndTime);


void __RPC_STUB IAnsoplyInterface_SetEffectEndTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_SetDynamicEffectBitmap_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG *uBitmapID,
    /* [in] */ BSTR sBitmapFilePath,
    /* [in] */ ULONG uAlpha,
    /* [in] */ ULONG uTransparentColor,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uOriginalSize,
    /* [in] */ ULONG uDrawStyle);


void __RPC_STUB IAnsoplyInterface_SetDynamicEffectBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_CreateBitmapGroup_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG *uGroupID);


void __RPC_STUB IAnsoplyInterface_CreateBitmapGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_AddBitmap_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG *uBitmapID,
    /* [in] */ BSTR sBitmapFilePath,
    /* [in] */ ULONG uAlpha,
    /* [in] */ ULONG uTransparentColor,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uOriginalSize,
    /* [in] */ ULONG uDrawStyle,
    /* [in] */ ULONG uDelay);


void __RPC_STUB IAnsoplyInterface_AddBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_DelBitmapGroup_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID);


void __RPC_STUB IAnsoplyInterface_DelBitmapGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_InsertBitmap_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uWhere,
    /* [in] */ ULONG *uBitmapID,
    /* [in] */ BSTR sBitmapFilePath,
    /* [in] */ ULONG uAlpha,
    /* [in] */ ULONG uTransparentColor,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uOriginalSize,
    /* [in] */ ULONG uDrawStyle,
    /* [in] */ ULONG uDelay);


void __RPC_STUB IAnsoplyInterface_InsertBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_CreateTextGroup_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG *uGroupID);


void __RPC_STUB IAnsoplyInterface_CreateTextGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_AddText_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ BSTR sOutputText,
    /* [in] */ BSTR sFaceName,
    /* [in] */ ULONG uItalic,
    /* [in] */ ULONG uBold,
    /* [in] */ ULONG uUnderLine,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uColor,
    /* [in] */ ULONG *uObjectID,
    /* [in] */ ULONG uRegionWidth,
    /* [in] */ ULONG uRegionHeight,
    /* [in] */ ULONG uDrawStyle,
    /* [in] */ ULONG uDelay);


void __RPC_STUB IAnsoplyInterface_AddText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_DelTextGroup_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID);


void __RPC_STUB IAnsoplyInterface_DelTextGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnsoplyInterface_InsertText_Proxy( 
    IAnsoplyInterface * This,
    /* [in] */ ULONG uGroupID,
    /* [in] */ ULONG uWhere,
    /* [in] */ ULONG uX,
    /* [in] */ ULONG uY,
    /* [in] */ BSTR sOutputText,
    /* [in] */ BSTR sFaceName,
    /* [in] */ ULONG uItalic,
    /* [in] */ ULONG uBold,
    /* [in] */ ULONG uUnderLine,
    /* [in] */ ULONG uWidth,
    /* [in] */ ULONG uHeight,
    /* [in] */ ULONG uColor,
    /* [in] */ ULONG *uObjectID,
    /* [in] */ ULONG uRegionWidth,
    /* [in] */ ULONG uRegionHeight,
    /* [in] */ ULONG uDrawStyle,
    /* [in] */ LONG uDelay);


void __RPC_STUB IAnsoplyInterface_InsertText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAnsoplyInterface_INTERFACE_DEFINED__ */



#ifndef __Ansoply_LIBRARY_DEFINED__
#define __Ansoply_LIBRARY_DEFINED__

/* library Ansoply */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_Ansoply;

EXTERN_C const CLSID CLSID_CAnsoplyInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("D1EBA581-03B3-42EA-B097-7F97F0ADB87B")
CAnsoplyInterface;
#endif
#endif /* __Ansoply_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


