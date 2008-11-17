/******************************************************************************
{                      ͼ����Ч��ʾAPI��������VC6��VC.NET                      }
{                      ���ָգ�yulingang1969@yahoo.com.cn                      }
{                                   2004��4��                                  }
{����������Щ�����Ѿ���β��ԣ����������ɵ�ʹ�ã������߲��Կ�����ɵĺ������}
{����ʹ����Щ����ʱ���뱣�ִ���ԭ������Ҫ�޸ģ�����޸ĺ�Ĵ��뷢�͸����ߡ�    }
{���÷���Ԥ���������Ŷ���(��Project|Settings|C++|Preprocessor definitions�ж���)
{   1. Ҫ����ΪDLL���������EFFECTDRAW_EXPORTS��ͬʱ�����EffectDraw.def�ļ� }
{   2. ���Ĺ���Ҫ��̬����DLL�⣬���趨�����                                   }
{   3. ���Ĺ��̲���DLL��ֱ�Ӱ���Դ���룬�������EFFECTDRAW_NOTDLL            }
{���������������ͼ����Ч�㷨�ı���Delphi���PicShow��������˵����             }
{------------------------------------------------------------------------------}
{  TCustomPicShow v3.07                                                        }
{  by Kambiz R. Khojasteh                                                      }
{                                                                              }
{  kambiz@delphiarea.com                                                       }
{  http://www.delphiarea.com                                                   }
{                                                                              }
{  Special thanks to:                                                          }
{  :: <k3nx@hotmail.com> for help on D5 support.                               }
{  :: Douglass Titjan <support@delphipages.com> for help on D5 support.        }
{  :: Jerry McLain <jkmclain@srcaccess.net> for manual control idea.           }
{  :: M. R. Zamani <M_R_Zamani@yahoo.com> for adding 8 effects (110..117).     }
{  :: Elliott Shevin <ShevinE@aol.com> for adding 4 effects (123..126).        }
{  :: Ken Otto <ken.otto@enviros.com> for adding native JPG support to         }
{     TDBPicShow and fixing a memory leak bug.                                 }
{  :: Gary Bond <gary.bond@tesco.net> for name of the transitions.             }
{  :: Viatcheslav V. Vassiliev <vvv@spacenet.ru> for optimizing the            }
{     thread's termination.                                                    }
{  :: Miguel Gastelumendi Dargent <mgd@satelier.com.br> for fixing the         }
{     possible off-screen problem on the first time transition.                }
{  :: Terry Bogard <voyage_technologies@yahoo.com> for fixing the bug in       }
{     choosing transition style by name.                                       }
*******************************************************************************/

#if !defined(AFX_EFFECTDRAW_H__07FDB52B_1DD5_42F0_A674_BF75AC2395BA__INCLUDED_)
#define AFX_EFFECTDRAW_H__07FDB52B_1DD5_42F0_A674_BF75AC2395BA__INCLUDED_

#if defined(EFFECTDRAW_EXPORTS)
	#define EFFECTDRAW_API __declspec(dllexport)
#elif defined(EFFECTDRAW_NOTDLL)
	#define EFFECTDRAW_API
#else
	#define EFFECTDRAW_API __declspec(dllimport)
#endif

#define ED_MAXSTYLE		310 //151�Ժ�����ҡ����»�Խ����Ч��
                            //�Լ������ߡ�������Ч��Ϊ��������

/////////////////////////////////////////////////////////////////////////
//       Style       Description
//-----------------------------------------------------------------------
//        000        Custom effect
//        001        Expand from right
//        002        Expand from left
//        003        Slide in from right
//        004        Slide in from left
//        005        Reveal from left
//        006        Reveal from right
//        007        Expand in from right
//        008        Expand in from left
//        009        Expand in to middle
//        010        Expand out from middle
//        011        Reveal out from middle
//        012        Reveal in from sides
//        013        Expand in from sides
//        014        Unroll from left
//        015        Unroll from right
//        016        Build up from right
//        017        Build up from left
//        018        Expand from bottom
//        019        Expand from top
//        020        Slide in from bottom
//        021        Slide in from top
//        022        Reveal from top
//        023        Reveal from bottom
//        024        Expand in from bottom
//        025        Expand in from top
//        026        Expand in to middle(horiz)
//        027        Expand out from middle(horiz)
//        028        Reveal from middle(horiz)
//        029        Slide in from top/bottom
//        030        Expand in from top/bottom
//        031        Unroll from top
//        032        Unroll from bottom
//        033        Expand in from bottom
//        034        Expand in from top
//        035        Expand from bottom right
//        036        Expand from top right
//        037        Expand from top left
//        038        Expand from bottom left
//        039        Slide in from bottom right
//        040        Slide in from top right
//        041        Slide in from top left
//        042        Slide in from bottom left
//        043        Reveal from top left
//        044        Reveal from bottom left
//        045        Reveal from bottom right
//        046        Reveal from top right
//        047        Appear and Contract to top left
//        048        Appear and Contract to bottom left
//        049        Appear and Contract to bottom right
//        050        Appear and Contract to top right
//        051        Appear and Contract to middle
//        052        Expand out from centre
//        053        Reveal out from centre
//        054        Reveal in to centre
//        055        Quarters Reveal in to middle
//        056        Quarters Expand to middle
//        057        Quarters Slide in to middle
//        058        Curved Reveal from left
//        059        Curved Reveal from right
//        060        Bars in from right
//        061        Bars in from left
//        062        Bars left/right
//        063        Bars right/left
//        064        Bars from both sides
//        065        Uneven shred from right
//        066        Uneven shred from left
//        067        Uneven shred out from middle(horiz)
//        068        Uneven shred in to middle(horiz)
//        069        Curved Reveal from top
//        070        Curved Reveal from bottom
//        071        Bars from bottom
//        072        Bars from top
//        073        Bars top/bottom
//        074        Bars bottom/top
//        075        Bars from top and bottom
//        076        Unven shred from bottom
//        077        Uneven shred from top
//        078        Uneven shred from horizon
//        079        Uneven shred in to horizon
//        080        Curved reveal from top left
//        081        Curved reveal from top right
//        082        Curved reveal from bottom left
//        083        Curved reveal from bottom right
//        084        Circular reveal from centre
//        085        Circular reveal to centre
//        086        Criss Cross reveal from bottom right
//        087        Criss Cross reveal from top right
//        088        Criss Cross reveal from bottom left
//        089        Criss Cross reveal from top left
//        090        Criss Cross reveal bounce from top left
//        091        Criss Cross reveal bounce from bottom left
//        092        Criss Cross reveal bounce from top right
//        093        Criss Cross reveal bounce from bottom right
//        094        Criss Cross reveal from right top and bottom
//        095        Criss Cross reveal from left top and bottom
//        096        Criss Cross reveal from left right and bottom
//        097        Criss Cross reveal from left right and top
//        098        Criss Cross reveal from top left right and bottom
//        099        Criss Cross reveal from bottom left top right
//        100        Uneven shred from bottom and right
//        101        Uneven shred from top and right
//        102        Uneven shred from bottom and left
//        103        Uneven shred from top and left
//        104        Uneven shred from horiz and right
//        105        Uneven shred from horiz and left
//        106        Uneven shred from bottom and vert middle
//        107        Uneven shred from top and vert middle
//        108        Uneven shred from centre
//        109        Uneven shred to centre
//        110        Reveal diagonal from top left
//        111        Reveal diagonal from top right
//        112        Reveal diagonal from bottom left
//        113        Reveal diagonal from bottom right
//        114        Diagonal sweep from top left bottom right anticlockwise
//        115        Diagonal sweep from top left bottom right clockwise
//        116        Starburst clockwise from center
//        117        Triangular shred to top left
//        118        Fade
//        119        Pivot from top left
//        120        Pivot from bottom left
//        121        Pivot from top right
//        122        Pivot from bottom right
//        123        Speckle appear from right
//        124        Speckle appear from left
//        125        Speckle appear from bottom
//        126        Speckle appear from top
//        127        Random squares appear
//        128        Push right
//        129        Push left
//        130        Push and squeeze right
//        131        Push and squeeze left
//        132        Push down
//        133        Push up
//        134        Push and sqeeze down
//        135        Push and sqeeze up
//        136        Blind vertically
//        137        Blind horizontally
//        138        Uneven blind from left
//        139        Uneven blind from right
//        140        Uneven blind from top
//        141        Uneven blind from bottom
//        142        Rectangular shred
//        143        Sweep clockwise
//        144        Sweep anticlockwise
//        145        Rectangles apear from left and disapear to right
//        146        Rectangles apear from right and disapear to left
//        147        Rectangles apear from up and disapear to bottom
//        148        Rectangles apear from bottom and disapear to up
//        149        Rotational rectangle
//        150        Rotational star
/////////////////////////////////////////////////////////////////////////

//�Զ�����Ч�����в���aRect�����Ͻ�Ϊ(0, 0)���豸����hdcSrc, hdcDstΪ�ڴ��豸����
typedef BOOL (WINAPI *EFFECTDRAWPROC)(HDC hdcDst, HDC hdcSrc, const RECT aRect, int Step, int Progress);

#define ED_BEFOREDRAW			0
#define ED_AFTERDRAW			1
#define ED_BEFOREDRAWPROGRESS	2
#define ED_AFTERDRAWPROGRESS	3
#define ED_BEFORECLEAR			4
#define ED_AFTERCLEAR			5
#define ED_BEFORECLEARPROGRESS	6
#define ED_AFTERCLEARPROGRESS	7

//������������¼��Ļص������Ĳ����ṹ
typedef struct tagDRAWCLEARSTRUCT //dcs
{
	int nEvent;		//ED_BEFOREDRAW          - ��������ʼǰ
					//ED_AFTERDRAW           - ������������
					//ED_BEFORECLEAR         - �߳�������ʼǰ
					//ED_AFTERCLEAR          - �߳�����������
					//ED_BEFOREDRAWPROGRESS  - ÿ����������ʼǰ
					//ED_AFTERDRAWPROGRESS   - ÿ��������������
					//ED_BEFORECLEARPROGRESS - ÿ���߳�������ʼǰ
					//ED_AFTERCLEARPROGRESS  - ÿ���߳�����������
	HWND hWnd;      //Ŀ�괰�ھ��
	HDC hdc;		//������ǰΪԴλͼ���ڴ��豸����
					//�߳�����ǰΪ����λͼ���ڴ��豸����
					//����ΪĿ�괰�ڵ��ڴ��豸����
	int nWidth;		//�ڴ��豸�����Ŀ��
	int nHeight;	//�ڴ��豸�����ĸ߶�
	int nStyle;		//��ǰ���������������Ч���
	int nStep;		//ÿ��������������İٷֱ���
	int nProgress;	//������������ѽ��еİٷֱ���
} DRAWCLEARSTRUCT, *LPDRAWCLEARSTRUCT;

//������������¼��Ļص��������ͣ����ڱ�д����ص�����ʱ��ע�⣺
//1. �����ڲ���ʹ�ô����MFC����(���ǲ������̼߳乲��)�������Ǵ�
//   CObjectֱ�������Ķ���������򵥶�����CString��CRect��CPoint�ȣ�
//2. �������̷߳�����Ϣ����PostMessage���͡�
typedef void (WINAPI *EFFECTDRAWEVENTPROC)(LPDRAWCLEARSTRUCT pDCS);

//ͼ����Ƶ�ģʽ
//���ڱ���ͼ��ֻ����ƽ�̺���չģʽ
//����Դλͼ����Ϊ����ģʽ֮һ����ͬʱ����͸��ģʽ
#define ED_NONE				0		//���Ͻ�
#define ED_CENTERED			1		//����
#define ED_TITLED			2		//ƽ��
#define ED_STRETCHED		3		//��չ
#define ED_FINESTRETCHED	4		//�����ݺ����չ
#define ED_TRANSPARENT		0x100	//͸����ͬʱӦָ��͸��ɫ(-1��ʾ��ͼ�����Ͻǵ���ɫ)

//������SetParams�������������ñ���ͼ��ľ��
#define ED_HBITMAPDESKTOP	((HBITMAP)0)	 //�������λͼ��Ϊ����
#define ED_HBITMAPWNDBK		((HBITMAP)-1)    //�ô���m_hWndDraw��λͼ��Ϊ����

typedef HANDLE HEFFECTDRAW;

EFFECTDRAW_API void WINAPI DrawHorzText(HDC hdc, int top, int bottom, LPCTSTR szText, LPCTSTR szFontName, int nFontSize, COLORREF crText, COLORREF crBack = -1, BOOL bBold = FALSE, int nHorzAlign = DT_CENTER);
EFFECTDRAW_API HBITMAP WINAPI GetBitmapHandleFromBuffer(HGLOBAL hGraphData, int cxDesired = 0, int cyDesired = 0);
EFFECTDRAW_API HBITMAP WINAPI GetBitmapHandleFromResource(int nGraphID, LPCTSTR szResType = RT_RCDATA, int cxDesired = 0, int cyDesired = 0);
EFFECTDRAW_API HBITMAP WINAPI GetBitmapHandleFromFile(LPCTSTR szGraphFile, int cxDesired = 0, int cyDesired = 0);
EFFECTDRAW_API RGBTRIPLE * WINAPI GetBitmapData(HDC hdc, int &nWidth, int &nHeight, int &nWidthBytes);
EFFECTDRAW_API RGBTRIPLE * WINAPI GetBitmapPixel(RGBTRIPLE *pBmpData, int nWidthBytes, int x, int y);
EFFECTDRAW_API void WINAPI DrawHorzTextOnBitmap(HBITMAP &hbmp, int top, int bottom, LPCTSTR szText, LPCTSTR szFontName, int nFontSize, COLORREF crText, COLORREF crBack = -1, BOOL bBold = FALSE, int nHorzAlign = DT_CENTER);
EFFECTDRAW_API void WINAPI Create24BPPDC(const RECT rcSrc, HDC hdcSrc, int dstW, int dstH, HDC *phdcDst, int nMode = ED_STRETCHED, COLORREF crBkColor = (COLORREF)-1);
EFFECTDRAW_API void WINAPI MakeTransparent(HDC hdcSrc, HDC hdcBkgnd, COLORREF crTrans = (COLORREF)-1);
EFFECTDRAW_API void WINAPI RotatePoints(int nPoint, LPPOINT Points, int xOrg, int yOrg, double Angle);
EFFECTDRAW_API HRGN WINAPI CreateTriangleRgn(int X1, int Y1, int X2, int Y2, int X3, int Y3);
EFFECTDRAW_API HRGN WINAPI CreateArcRgn(int mX, int mY, int Radius, double StartAngle, double EndAngle, int NumPts);
EFFECTDRAW_API HRGN WINAPI CreatePartRgn(int ndstW, int ndstH, int nPart);

EFFECTDRAW_API void WINAPI RandomSeed(unsigned int nSeed);
EFFECTDRAW_API int WINAPI Random(int nMax); //Random value, 0<=value<nMax
EFFECTDRAW_API void WINAPI InstallCustomEffectProc(EFFECTDRAWPROC CustomEffectProc);
EFFECTDRAW_API EFFECTDRAWPROC WINAPI GetEffectProc(int Style);

EFFECTDRAW_API HEFFECTDRAW WINAPI CreateEffectDraw();          //ʹ��ǰ�����ȴ���
EFFECTDRAW_API void WINAPI DeleteEffectDraw(HEFFECTDRAW hED);  //ʹ�ú����ɾ���������ڴ�й©
//����������SetParams�������ò������������������ú�����������Ժ�ĸ��ֲ�������
EFFECTDRAW_API void WINAPI SetParams(HEFFECTDRAW hED, HWND hWndDst, HBITMAP hbmpSrc, HBITMAP hbmpBkgnd = ED_HBITMAPWNDBK, LPCRECT prcDst = NULL,
		int nSrcMode = ED_STRETCHED, COLORREF crSrcTrans = (COLORREF)-1, int nBkgndMode = ED_STRETCHED,
		int nDrawStyle = 118, int nClearStyle = 118, int nStep = 4, int nDelay = 40);
EFFECTDRAW_API void WINAPI SetSourceBitmap(HEFFECTDRAW hED, HBITMAP hbmpSrc, int nSrcMode = ED_STRETCHED, COLORREF crSrcTrans = -1);
EFFECTDRAW_API void WINAPI SetBkgndBitmap(HEFFECTDRAW hED, HBITMAP hbmpBkgnd, int nBkgndMode = ED_STRETCHED);
EFFECTDRAW_API void WINAPI SetBkgndColor(HEFFECTDRAW hED, COLORREF crBkgnd);
EFFECTDRAW_API void WINAPI IncDrawStyle(HEFFECTDRAW hED, int nIncrement);
EFFECTDRAW_API void WINAPI IncClearStyle(HEFFECTDRAW hED, int nIncrement);
EFFECTDRAW_API void WINAPI SetRandomDrawStyle(HEFFECTDRAW hED);
EFFECTDRAW_API void WINAPI SetRandomClearStyle(HEFFECTDRAW hED);
EFFECTDRAW_API void WINAPI GetDestinationRect(HEFFECTDRAW hED, LPRECT prcDst);
EFFECTDRAW_API void WINAPI SetDrawStyle(HEFFECTDRAW hED, int nDrawStyle);
EFFECTDRAW_API int WINAPI GetDrawStyle(HEFFECTDRAW hED);
EFFECTDRAW_API void WINAPI SetClearStyle(HEFFECTDRAW hED, int nClearStyle);
EFFECTDRAW_API int WINAPI GetClearStyle(HEFFECTDRAW hED);
EFFECTDRAW_API void WINAPI SetStep(HEFFECTDRAW hED, int nStep);
EFFECTDRAW_API int WINAPI GetStep(HEFFECTDRAW hED);
EFFECTDRAW_API void WINAPI SetDelay(HEFFECTDRAW hED, int nDelay);
EFFECTDRAW_API int WINAPI GetDelay(HEFFECTDRAW hED);
EFFECTDRAW_API void WINAPI InstallEventProc(HEFFECTDRAW hED, EFFECTDRAWEVENTPROC fnDCC);
EFFECTDRAW_API BOOL WINAPI IsBusy(HEFFECTDRAW hED);
EFFECTDRAW_API void WINAPI Draw(HEFFECTDRAW hED, BOOL bAsynchronous = TRUE);
EFFECTDRAW_API void WINAPI Clear(HEFFECTDRAW hED, BOOL bAsynchronous = TRUE);
EFFECTDRAW_API void WINAPI Stop(HEFFECTDRAW hED);

#endif //!defined(AFX_EFFECTDRAW_H__07FDB52B_1DD5_42F0_A674_BF75AC2395BA__INCLUDED_)
