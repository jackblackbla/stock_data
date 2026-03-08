// WMCALOADERDlg.cpp : implementation file
//
#include "stdafx.h"
#include "WMCALOADER.h"
#include "WMCALOADERDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "trio_inv.h"
#include "trio_ord.h"
#include "math.h"

// 아래 TRID값들은 사용 예시를 보이기 위해 임의의 값을 지정한 것일 뿐이며
// 반드시 고정값을 사용해야하는 것은 아닙니다

const	int	TRID_IVWUTKMST04 = 1;
const	int	TRID_c8201 = 2;
const	int	TRID_c8102 = 3;

/************************************************************************************

							!!! 주의 !!!

	제공해드리는 본 예제 코드는 wmca.dll library 사용 방법을 익히기 위한 예제입니다.

	본 예제만으로는 사용자께서 필요로하는 모든 정보를 확인할 수는 없으며
	기본적인 사용방법을 익히는 용도로만 활용하시기 바랍니다.
	
	TR 및 실시간 전문 SPEC 정보는 문서 자료(*.doc)를 우선 참조하시기 바랍니다.

	이 예제에는 의도하지 않은 프로그램 오류가 포함될 수 있으므로 
	실환경에 바로 사용하시는 것은 권장하지 않습니다.
	용도에 맞게 프로젝트를 새로 생성해서 작성하시기를 권장드립니다.

	* 당사에서는 이 예제를 통한 프로그램 오동작에 대해서 어떠한 책임도 지지 않습니다.
	* 본 소스 코드는 사용자 요청 또는 당사 내부 사정에 따라 언제든지 변경될 수 있습니다.
	* 예제에 사용된 서비스 I/O(TR 및 실시간시세 패킷)는 변경될 가능성이 있으며
	* 변경시 OpenAPI 전용 공지사항(WEB)을 통해 안내가 제공됩니다
	  (작성하신 프로그램의 로그인 시점에 공지사항의 신규 게시물이 웹페이지로 자동 노출됨)
	
	* 이용자분들의 개발 환경에 대해 지원 범위를 최대한으로 유지하기 위해 이 예제는 
	  다소 오래된 개발 환경(Microsoft Visual C++ 2010) 기반으로 제공되고 있으니
	  참고만 하시되 새로 작성하시는 것은 최신 버전으로 작성하시는 것을 권장 드립니다
	
	* wmca.dll 및 예제 코드는 Ansi code(MBCS)기반 32bit로 제공되며
	* 64bit 또는 Unicode방식으로의 동작은 지원 또는 보장되지 않습니다

************************************************************************************/





/************************************************************************************

	wmca.dll 을 wrapping 한 CWmcaIntf class를 이용하여 다음 기능들을 테스트합니다.
	
	0. 인증(당사인증 + 공동인증)	
	1. 투자정보 조회(현재가)		IVWUTKMST04
	2. 계좌정보 조회(잔고조회)	c8102
	3. 실시간 시세 수신			mc, oc, nc(실시간 주식 체결가)
	4. 실시간 체결통보			d2


************************************************************************************/



/////////////////////////////////////////////////////////////////////////////
// CWMCALOADERDlg dialog
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
CWMCALOADERDlg::CWMCALOADERDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWMCALOADERDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWMCALOADERDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWMCALOADERDlg)
	DDX_Control(pDX, IDC_LIST1, m_listboxTrace);
	DDX_Control(pDX, IDC_COMBOACCOUNTLIST, m_comboAccountList);
	DDX_Control(pDX, IDC_STATICLOGIN, m_staticLoginTime);
	DDX_Control(pDX, IDC_EDIT3, m_editSignPassword);
	DDX_Control(pDX, IDC_EDIT2, m_editPassword);
	DDX_Control(pDX, IDC_EDIT1, m_editID);
	DDX_Control(pDX, IDC_CONNECT, m_buttonConnect);
	DDX_Control(pDX, IDC_CONNECT_LOCAL, m_buttonLocal);
	DDX_Control(pDX, IDC_CONNECT_CLOUD, m_buttonCloud);
	DDX_Control(pDX, IDC_DISCONNECT, m_buttonDisconnect);
	DDX_Control(pDX, IDC_BALANCE, m_buttonBalance);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_MARKET, m_ctlMarket);
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
BEGIN_MESSAGE_MAP(CWMCALOADERDlg, CDialog)
	//{{AFX_MSG_MAP(CWMCALOADERDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_BALANCE, OnBalance)
	ON_BN_CLICKED(IDC_BUTTON_CURRENT, OnButtonCurrent)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_ORDER, OnButtonOrder)
	ON_BN_CLICKED(IDC_CONNECT_LOCAL, &CWMCALOADERDlg::OnBnClickedConnectLocal)
	ON_BN_CLICKED(IDC_CONNECT_CLOUD, &CWMCALOADERDlg::OnBnClickedConnectCloud)
	//}}AFX_MSG_MAP

	ON_MESSAGE(CA_WMCAEVENT, OnWmcaEvent)
END_MESSAGE_MAP()
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/////////////////////////////////////////////////////////////////////////////
// CWMCALOADERDlg message handlers
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
HCURSOR CWMCALOADERDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnOK() 
{
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnCancel() 
{
	CDialog::OnCancel();
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnConnect() 
{
	CString	strID;
	CString	strPassword;
	CString	strSignPassword;

	m_editID.GetWindowText(strID);
	m_editPassword.GetWindowText(strPassword);
	m_editSignPassword.GetWindowText(strSignPassword);

	//접속 및 로그인
	//매체코드는 특별한 경우를 제외하고 항상 아래 기본값을 사용하시기 바랍니다.
	if (!strID.IsEmpty() && !strPassword.IsEmpty())
		m_wmca.Connect(GetSafeHwnd(),CA_WMCAEVENT,'P','1',strID,strPassword,strSignPassword);	//N2 OpenAPI 사용자용
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnDisconnect() 
{
	m_wmca.Disconnect();
}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	문자열을 구조체 필드로 적절히 채우는 유틸리티 함수입니다. (넘치면 잘림)
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void	_smove(char* szTarget,int nSize,CString strSource)
{
	int	nMin	=min(nSize,strSource.GetLength());

	memset(szTarget,' ',nSize);
	strncpy(szTarget,strSource,nMin);
}

#define SMOVE(fTarget,strSource)	_smove(fTarget,sizeof fTarget,strSource)

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	숫자를 구조체 필드로 적절히 채우는 유틸리티 함수입니다.	  (넘치면 버림)
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void	_nmove(char* szTarget,int nTarget,CString strSource)
{
	if(strSource.GetLength()>nTarget)
		return;

	memset(szTarget,'0',nTarget);
	strncpy(szTarget+nTarget-strSource.GetLength(),strSource,strSource.GetLength());
}

#define NMOVE(fTarget,strSource)	_nmove(fTarget,sizeof fTarget,strSource)

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	구조체 필드값을 문자열 형태로 변환하는 유틸리티 함수입니다.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
CString	_scopy(const char* szData,int nSize)
{
	char	szBuf[256];				//필드의 최대 크기는 상황에 따라 조절할 필요가 있음
	memset(szBuf,0,sizeof szBuf);
	strncpy(szBuf,szData,nSize);
	
	return szBuf;
}

#define SCOPY(x)	_scopy(x,sizeof x)

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	구조체 필드값을 숫자 형태로 변환하는 유틸리티 함수입니다.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
CString	_ncopy(const char* szData,int nSize)
{
	CString	strInput	=_scopy(szData,nSize);

	for(int i=0;i<strInput.GetLength();i++)
		if(strInput.GetAt(i)=='0')
		{
			//마지막 '0' 또는 다음에 소수점이 오는 경우에는 지우지 않는다
			if(i!=strInput.GetLength()-1 && strInput.GetAt(i+1)!='.')	
				strInput.SetAt(i,' ');
		}
		else if(strInput.GetAt(i)=='-')	//minus
			;
		else if(strInput.GetAt(i)==' ')	//숫자형임에도 공백문자가 오는 경우가 있음
			;
		else
			break;

	return	strInput;
}

#define NCOPY(x)	_ncopy(x,sizeof x)

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	 숫자에 천 단위로 컴마 삽입하는 유틸리티 함수입니다.
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
CString	_comma(const char* szData,int nSize,int decimal=0)
{
	CString	strInput	=_scopy(szData,nSize);
	strInput.TrimLeft();
	strInput.TrimRight();
	
	double	fInput	=atof(strInput);

	CString	strTemp;
	strTemp.Format("%0.*f",decimal,fInput);

	if(fInput>=1000000000.0F)
		strTemp.Insert(strTemp.GetLength()-9,',');
	if(fInput>=1000000.0F)
		strTemp.Insert(strTemp.GetLength()-6,',');
	if(fInput>=1000.0F)
		strTemp.Insert(strTemp.GetLength()-3,',');

	CString	strOutput;
	strOutput.Format("%*s",nSize,strTemp);

	return strOutput;
}

#define COMMA(x)	_comma(x,sizeof x)
#define COMMAF(x,d)	_comma(x,sizeof x,d)

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//	wmca.dll로 부터 수신한 윈도우 메시지를 통해 각 이벤트 핸들러로 분기합니다
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
LRESULT CWMCALOADERDlg::OnWmcaEvent(WPARAM dwMessageType, LPARAM lParam)
{
	switch(dwMessageType) {
	case CA_CONNECTED:			//로그인 성공
		OnWmConnected( (LOGINBLOCK*)lParam );
		break;
	case CA_DISCONNECTED:		//접속 끊김
		OnWmDisconnected();
		break;
	case CA_SOCKETERROR:		//통신 오류 발생
		OnWmSocketerror( (int)lParam );
		break;
	case CA_RECEIVEDATA:		//서비스 응답 수신(TR)
		OnWmReceivedata( (OUTDATABLOCK*)lParam );
		break;
	case CA_RECEIVESISE:		//실시간 데이터 수신(BC)
		OnWmReceivesise( (OUTDATABLOCK*)lParam );
		break;
	case CA_RECEIVEMESSAGE:		//상태 메시지 수신 (입력값이 잘못되었을 경우 문자열형태로 설명이 수신됨)
		OnWmReceivemessage( (OUTDATABLOCK*)lParam );
		break;
	case CA_RECEIVECOMPLETE:	//서비스 처리 완료
		OnWmReceivecomplete( (OUTDATABLOCK*)lParam );
		break;
	case CA_RECEIVEERROR:		//서비스 처리중 오류 발생 (입력값 오류등)
		OnWmReceiveerror( (OUTDATABLOCK*)lParam );
		break;
	default:
		break;
	}

	return TRUE;
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnWmConnected( LOGINBLOCK* pLogin )
{
	//로그인이 성공하면, 접속시각 및 계좌번호 정보를 받아 적절히 보관/출력합니다.
	//계좌번호에 대한 순서(인덱스)는 계좌관련 서비스 호출시 사용되므로 중요합니다.
	
	//컨트롤 활성상태변경
	m_editID.EnableWindow(FALSE);

	m_editPassword.EnableWindow(FALSE);
	m_editSignPassword.EnableWindow(FALSE);

	m_buttonConnect.EnableWindow(FALSE);
	m_buttonDisconnect.EnableWindow(TRUE);
	m_buttonLocal.EnableWindow(FALSE);
	m_buttonCloud.EnableWindow(FALSE);

	//접속시각 출력
	char	szText[256]	={0};
	strncpy(szText,pLogin->pLoginInfo->szDate,sizeof pLogin->pLoginInfo->szDate);
	CString	strText	="접속시각 : ";
	strText	+=szText;
	m_staticLoginTime.SetWindowText(strText);

	//계좌번호 출력
	char	szAccountCount[8]	={0};
	strncpy(szAccountCount,pLogin->pLoginInfo->szAccountCount,sizeof pLogin->pLoginInfo->szAccountCount);
	int	nAccountCount	=atoi(szAccountCount);

	m_comboAccountList.ResetContent();

	for(int i=0;i<nAccountCount;i++)
	{
		char	szAccountNo[16]	={0};
		strncpy(szAccountNo,(char*)&pLogin->pLoginInfo->accountlist[i].szAccountNo,sizeof pLogin->pLoginInfo->accountlist[i].szAccountNo);

		CString	strAccountNo	=szAccountNo;
		m_comboAccountList.AddString(strAccountNo);

		//strAccountNo.Insert(3,'-');
		//strAccountNo.Insert(6,'-');

		//CString	strIndex;
		//strIndex.Format("계좌%3d:%s",i+1,strAccountNo);		//계좌번호는 '1'번부터 시작합니다. 

		//m_comboAccountList.AddString(strIndex);
	}

	//자동으로 첫 번째 계좌를 선택
	if(nAccountCount)
		m_comboAccountList.SetCurSel(0);

	//
	m_listboxTrace.AddString("정상 접속되었습니다");
	ScrollDown();

	UpdateControlStatus(TRUE);
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnWmDisconnected()
{
	//접속이 끊겼을 경우 처리
	m_staticLoginTime.SetWindowText("");

	m_editID.EnableWindow(TRUE);

	m_editPassword.EnableWindow(TRUE);
	m_editSignPassword.EnableWindow(TRUE);

	m_buttonConnect.EnableWindow(TRUE);
	m_buttonDisconnect.EnableWindow(FALSE);
	m_buttonLocal.EnableWindow(TRUE);
	m_buttonCloud.EnableWindow(TRUE);
	
	//
	m_listboxTrace.AddString("접속이 끊겼습니다");
	ScrollDown();

	UpdateControlStatus(FALSE);
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnWmSocketerror(int socket_error_code)
{
	m_listboxTrace.AddString("통신오류발생");
	ScrollDown();
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnWmReceivedata( OUTDATABLOCK* pOutData )
{
	switch(pOutData->TrIndex)
	{
	case TRID_IVWUTKMST04:
		// 종목마스터 기본 자료	(단순출력)
		if (strcmp(pOutData->pData->szBlockName, "IVWUTKMST04Out1") == 0)
		{
			TIVWUTKMST04Out1* pOut1 = (TIVWUTKMST04Out1*)pOutData->pData->szData;

			m_listboxTrace.AddString(">>  주식현재가조회 - 현재가");

			CString	strList;
			strList.Format("%8s %6s %41s %10s원 %12s주",
				SCOPY(pOut1->hoga_bsop_hour),
				SCOPY(pOut1->shrn_iscd),
				SCOPY(pOut1->hts_isnm),
				COMMA(pOut1->stck_prpr),
				COMMA(pOut1->acml_vol)
			);

			m_listboxTrace.AddString(strList);
			ScrollDown();

			if ("실시간 시세 수신 요청")
			{
				// 주식 실시간 체결가(현재가) 전문 요청 예시
				// 이용하는 거래소 유형에 맞춰 적절히 실시간 패킷 유형을 지정하시기 바랍니다.	
				// ex)	mc(통합),	oc(KRX),	nc(NXT)
				m_wmca.Attach(
					GetSafeHwnd(),			//실시간 데이터 수신 메시지를 이 윈도우로 받겠습니다.
					"mc",					//요청하는 실시간 패킷은 '주식현재가'(mc/통합시세)입니다		
					pOut1->shrn_iscd,		//요청하려는 종목코드를 지정합니다.
					6,						//개별 종목코드의 길이는 6바이트이며
					6						//전체종목코드의 길이도 6바이트입니다. 여러 종목일 경우에는 (개별 종목코드길이 x 종목수)를 지정합니다.
				);

				// 주식 실시간 체결가(현재가) 전문 취소 예시
				// 
				// 불필요한 실시간 전문을 취소하지 않을 경우 해당 전문 수신으로 인한 
				// 프로그램 오동작 및 성능 저하가 있게되므로 주의하시기 바랍니다
				//
				//m_wmca.Detach(
				//	GetSafeHwnd(),			//실시간 데이터 수신 메시지를 이 윈도우로 받겠습니다.
				//	"mc",					//취소하는 실시간 패킷은 '코스피주식현재가'(mc)입니다
				//	strJCode,				//취소하려는 종목에 대한 코드를 지정합니다
				//	6,						//개별종목코드의 길이는 6바이트이며
				//	6						//전체종목코드의 길이도 6바이트입니다.
				//	);			

				//3종목(000660,005940,005930)에 대한 실시간 현재가 데이터 요청 예시
				//m_wmca.Attach(GetSafeHwnd(), "mc", "000660005940005930",	6/*종목코드 길이*/,18/*=종목코드길이(6)*종목수(3)*/);		
				//	ex)	mc(통합),	oc(KRX),	nc(NXT)

				//선물 현재가, 호가 실시간 데이터 요청
				//m_wmca.Attach(GetSafeHwnd(),"f8","101N6000", 8, 8);	//2018년 6월물 선물 현재가
				//m_wmca.Attach(GetSafeHwnd(),"f1","101N6000", 8, 8);	//2018년 6월물 선물 호가

				//옵션 현재가, 호가 실시간 데이터 요청
				//m_wmca.Attach(GetSafeHwnd(),"o2","201N5315", 8, 8);	//2018년 05월물 콜옵션 행사가 315.0 체결가(현재가)
				//m_wmca.Attach(GetSafeHwnd(),"o1","201N5315", 8, 8);	//2018년 05월물 콜옵션 행사가 315.0 호가
			}
		}

		// 변동거래량자료		(반복출력)
		else if(strcmp(pOutData->pData->szBlockName,"IVWUTKMST04Out2")==0)		
		{
			TIVWUTKMST04Out2*	pOut2	=(TIVWUTKMST04Out2*)pOutData->pData->szData;
			
			m_listboxTrace.AddString(">>  주식현재가조회 - 변동거래량");
			
			//실제 데이터에 따라 수신 데이터 행의 수가 가변적이므로
			//수신자료 크기를 구조체 크기로 나누어 몇 번 반복되는지 계산함
			int		nOccurs = pOutData->pData->nLen / sizeof(TIVWUTKMST04Out2);
			
			for (int i = 0; i < nOccurs; i++)	//회수만큼 반복하면서 데이터 구함
			{
				CString	strList;
				strList.Format("%8s %10s원 %10s원 %10s원 %10s원 %12s주 %12s주",
					SCOPY(pOut2->bsop_hour),
					COMMA(pOut2->stck_prpr),
					COMMA(pOut2->prdy_vrss),
					COMMA(pOut2->askp),
					COMMA(pOut2->bidp),
					COMMA(pOut2->cntg_vol),
					COMMA(pOut2->acml_vol)
				);

				m_listboxTrace.AddString(strList);

				pOut2++;	//다음행으로 포인터 이동
			}

			ScrollDown();
		}
		break;
	case TRID_c8201:
		//////////////////////////////////////////////////////////////////////////
		//반복되지 않는 단순출력 처리 방식
		//////////////////////////////////////////////////////////////////////////
		if(strcmp(pOutData->pData->szBlockName,"c8201OutBlock")==0)			
		{
			Tc8201OutBlock*	pc8201outblock	=(Tc8201OutBlock*)pOutData->pData->szData;
			
			m_listboxTrace.AddString("*** 잔고조회 예시 ***");
			m_listboxTrace.AddString("  총평가총액    ="+COMMA(pc8201outblock->dpsit_amtz16));
			m_listboxTrace.AddString("  증거금총액    ="+COMMA(pc8201outblock->chgm_pos_amtz16));
			m_listboxTrace.AddString("  주문가능금액  ="+COMMA(pc8201outblock->pos_csamt4z16));

			ScrollDown();
		}
		//////////////////////////////////////////////////////////////////////////
		//반복가능한 출력에 대한 처리 방식
		//////////////////////////////////////////////////////////////////////////
		else if(strcmp(pOutData->pData->szBlockName,"c8201OutBlock1")==0)			
		{
			Tc8201OutBlock1*	pc8201outblock1	=(Tc8201OutBlock1*)pOutData->pData->szData;

			int		nOccursCount	=pOutData->pData->nLen/sizeof(Tc8201OutBlock1);			//수신 크기를 레코드 크기로 나누어서 실제 반복 회수를 알 수 있음
			m_listboxTrace.AddString("*** 보유종목조회 예시 ***");

			for(int i=0;i<nOccursCount;i++)	//회수만큼 반복하면서 데이터 구함
			{
				//아래 항목들은 단순히 예시를 위해 넣은 값들입니다. 필요에 따라 첨삭하시기 바랍니다.
				//당사 HTS에 조회되는 내용과 동일하며 동일 종목이 여러줄에 걸쳐 표기될 경우 종목명과 종목코드가 생략되기도 합니다.
				m_listboxTrace.AddString("  종목코드      ="	+SCOPY(pc8201outblock1->issue_codez6));
				m_listboxTrace.AddString("  종목명        ="	+SCOPY(pc8201outblock1->issue_namez40));
				m_listboxTrace.AddString("  증거금률(%)   ="	+COMMA(pc8201outblock1->issue_mgamt_ratez6));
				m_listboxTrace.AddString("  잔고유형      ="	+SCOPY(pc8201outblock1->bal_typez6));
				m_listboxTrace.AddString("  미결제        ="	+COMMA(pc8201outblock1->unstl_qtyz16));
				m_listboxTrace.AddString("  현재잔고      ="	+COMMA(pc8201outblock1->jan_qtyz16));
				m_listboxTrace.AddString("  평균매입가    ="	+COMMA(pc8201outblock1->slby_amtz16));
				m_listboxTrace.AddString("  평가손익(천원)="	+COMMA(pc8201outblock1->lsnpf_amtz16));
				m_listboxTrace.AddString("  손익률        ="	+COMMAF(pc8201outblock1->earn_ratez9,2));
				m_listboxTrace.AddString("  평가금액      ="	+COMMA(pc8201outblock1->ass_amtz16));
				m_listboxTrace.AddString(" ");

				pc8201outblock1++;	//다음행으로 포인터 이동
			}

			ScrollDown();
		}
		break;
	case TRID_c8102:
		//////////////////////////////////////////////////////////////////////////
		//반복되지 않는 단순출력 처리 방식
		//////////////////////////////////////////////////////////////////////////
		if(strcmp(pOutData->pData->szBlockName,"c8102OutBlock")==0)			
		{
			Tc8102OutBlock*	pc8102OutBlock	=(Tc8102OutBlock*)pOutData->pData->szData;
			
			CString	strOrderNum		=SCOPY(pc8102OutBlock->order_noz10);
			strOrderNum.TrimLeft();
			strOrderNum.TrimRight();

			if(strOrderNum.IsEmpty())
			{
				m_listboxTrace.AddString(">>  주문 실패");
				break;
			}
			
			m_listboxTrace.AddString(">>  주문 정상");
			m_listboxTrace.AddString("주문번호 ="+strOrderNum);
			
			ScrollDown();
		}
		break;
	}
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::ScrollDown()
{
//	m_listboxTrace.AddString("");
	m_listboxTrace.SetTopIndex(	m_listboxTrace.GetCount()-1	);
	m_listboxTrace.SetSel(m_listboxTrace.GetCount()-1);
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnWmReceivesise(OUTDATABLOCK* pSiseData)
{
	//코스피 주식현재가 실시간 시세 수신
	//	ex)	mc(통합),	oc(KRX),	nc(NXT)
	if (strncmp(pSiseData->pData->szBlockName, "mc", 2) == 0 || 
		strncmp(pSiseData->pData->szBlockName, "oc", 2) == 0 || 
		strncmp(pSiseData->pData->szBlockName, "nc", 2) == 0)
	{
		TmcOutBlock* pmc = (TmcOutBlock*)(pSiseData->pData->szData + 3);	// 4번째부터 전문의 본문이 시작됨

		CString	strOut;
		strOut.Format("     %8s    %6s    %7s원    %9s주",
			SCOPY(pmc->time),
			SCOPY(pmc->code),
			COMMA(pmc->price),
			COMMA(pmc->volume)
		);

		m_listboxTrace.AddString(strOut);
		ScrollDown();
	}

	//주의) 본인이 낸 주문에 대한 실시간 체결 통보 전문은 	일반 실시간 시세와 달리 Attach()함수 호출이 불필요합니다
	//d2 구조체 정보를 통해 필요로 하는 정보를 추출할 수 있습니다.
	else if (strncmp(pSiseData->pData->szBlockName, "d2", 2) == 0)
	{
		Td2OutBlock* pd2 = (Td2OutBlock*)(pSiseData->pData->szData + 3);	//앞쪽 3바이트는 패킷유형과 압축구분이므로 skip

		//
		CString	strResult;
		strResult.Format("실시간 체결통보- 시각(%s) 계좌번호(%s) 수량(%15s) 가격(%15s)", SCOPY(pd2->conctime),
			SCOPY(pd2->accountno), COMMA(pd2->concgty), COMMA(pd2->concprc));
		m_listboxTrace.AddString(strResult);
		ScrollDown();
	}
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnWmReceivemessage( OUTDATABLOCK* pMessage )
{
	//현재 상태를 문자열 형태로 출력함
	MSGHEADER*	pMsgHeader		=(MSGHEADER*)pMessage->pData->szData;

	CString	strMsg;
	strMsg.Format("[%10d]  %5s : %s",
			pMessage->TrIndex,
			SCOPY(pMsgHeader->msg_cd),
			SCOPY(pMsgHeader->user_msg)	
	);

	m_listboxTrace.AddString(strMsg);
	ScrollDown();
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnWmReceivecomplete( OUTDATABLOCK* pOutData )
{
	//TR 호출 완료시점에 뭔가 해야한다면 아래와 같이 처리할 수 있습니다
	switch(pOutData->TrIndex)
	{
	case TRID_IVWUTKMST04:	;
		m_listboxTrace.AddString("주식 현재가 조회 완료");
		ScrollDown();
		break;
	case TRID_c8201:	;
		m_listboxTrace.AddString("계좌 잔고 조회 완료");
		ScrollDown();
		break;
	}
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnWmReceiveerror( OUTDATABLOCK* pError )
{
	//서비스 호출이 실패할 경우 수신됨
	m_listboxTrace.AddString("*** ERROR ***");
	m_listboxTrace.AddString(pError->pData->szData);
	ScrollDown();
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnBalance()					//잔고 조회(Query함수 사용 버전)
{
	//잔고조회를 위해 사용할 계좌번호 인덱스를 구합니다.
	//계좌번호 인덱스는 '1'부터 시작됩니다.
	int	nAccountIndex = m_comboAccountList.GetCurSel() + 1;

	//잔고조회 서비스에서 요구하는 입력값을 저장할 구조체 변수입니다.
	//속성바이트 누락을 방지하기 위해 가급적 입력구조체를 사용하는 것을 권장합니다.
	//당사 OpenAPI를 처음 사용하시는 분들께서 가장 많이 실수하는 부분입니다. 
	//
	//ex)'입력값을 제대로 넣었다고 생각하는데 뭐가 맞지 않다고 계속 거부됩니다. 뭐가 잘못된 걸까요?'

	Tc8201InBlock	c8201inblock;
	memset(&c8201inblock, 0x20, sizeof Tc8201InBlock);	//공백문자(space)로 초기화합니다.

	//화면상의 계좌 평문 비밀번호를 OpenAPI에서 제공되고 있는 hash함수에 입력하면
	//지정한 입력필드에 hash 비밀번호로 채워집니다.
	//모든 hash 비밀번호의 길이는 44바이트 고정입니다.
	CString	strPassword;
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(strPassword);
	m_wmca.SetAccountIndexPwd(c8201inblock.pswd_noz8, nAccountIndex, strPassword);

	//각 입력 필드에서 요구하는 값들에 대한 정의는 *.doc 문서를 통해 확인할 수 있습니다.
	SMOVE(c8201inblock.bnc_bse_cdz1, "1");			//구분	

	m_wmca.Query(
		GetSafeHwnd(),			//이 윈도우로 응답 메시지를 받겠습니다.
		TRID_c8201,				//이 서비스에 대해서 TRID_c8201(3) 식별자를 붙이겠다는 의미이며 반드시 상수일 필요는 없습니다.
		"c8201",				//호출하려는 서비스 코드는 'c8201' 입니다.
		(char*)&c8201inblock,	//c8201에서 요구하는 입력 구조체 포인터를 지정합니다
		sizeof Tc8201InBlock,	//입력 구조체 크기입니다
		nAccountIndex			//계좌번호 인덱스는 '1'부터 시작됩니다.
	);
}
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
void CWMCALOADERDlg::OnButtonCurrent()	// 주식 현재가 조회
{
	//주식현재가조회 서비스에서 요구하는 입력값을 저장할 구조체 변수입니다.
	TIVWUTKMST04In	inblock;
	memset(&inblock, 0x20, sizeof TIVWUTKMST04In);

	//화면상의 종목코드를 구합니다
	CString	strJCode;
	GetDlgItem(IDC_EDIT_JCODE)->GetWindowText(strJCode);
	
	//각 입력 필드에서 요구하는 값들에 대한 정의는 *.doc 문서를 통해 확인할 수 있습니다.
	SMOVE(inblock.form_lang, "k");
	SMOVE(inblock.shrn_iscd, strJCode);

	//선택된 거래소 확인
	CString strMarket;
	m_ctlMarket.GetWindowText(strMarket);	// SOR, KRX, NXT

	// 시세 조회용과 주문용 거래소 코드가 일부 차이가 있음
	// 시세 거래소 : UNT(통합 시세),  KRX, NXT
	// 주문 거래소 : SOR(스마트주문), KRX, NXT
	if (strMarket == "SOR")
		strMarket = "UNT";	

	//주식 현재가 조회
	m_wmca.Query(
			GetSafeHwnd(),				//이 윈도우로 응답 메시지를 받겠습니다.
			TRID_IVWUTKMST04,			//이 서비스에 대해서 TIVWUTKMST04 식별자를 붙이겠다는 의미이며 반드시 상수일 필요는 없습니다.
			"IVWUTKMST04." + strMarket,	//호출하려는 서비스 코드는 'TIVWUTKMST04'이며 거래소는 지정한 값입니다 (주1)
			(char*)&inblock,			//TIVWUTKMST04 서비스에서 요구하는 입력 구조체 포인터를 지정합니다
			sizeof TIVWUTKMST04In 		//입력 구조체 크기입니다
										//현재가를 포함한 투자정보 조회는 계좌번호와 무관하므로 계좌번호 인덱스를 지정하지 않습니다.
	);

	/*
	주1) 서비스 코드명(TR) 지정 방법에 따른 각 시세 기준은 아래와 같습니다.
	필요한 거래소를 지정하여 사용할 수 있습니다

	"IVWUTKMST04"			KRX (거래소 코드를 명시하지 않는 경우 암묵적으로 KRX로 처리)
	"IVWUTKMST04.UNT"		통합시세
	"IVWUTKMST04.KRX"		한국거래소(KRX)
	"IVWUTKMST04.NXT"		대체거래소(NXT)
	*/

	//기존에 요청한 실시간 전문이 있다면 일괄 취소
	m_wmca.DetachAll();
}

void CWMCALOADERDlg::OnButtonClear() 
{
	m_listboxTrace.ResetContent();
}

void CWMCALOADERDlg::OnButtonOrder()
{
	//계좌번호 인덱스를 구합니다.	(계좌번호는 '1'번부터 시작)
	int	nAccountIndex = m_comboAccountList.GetCurSel() + 1;

	//주문 test는 주의가 요구됩니다
	//주식주문 서비스에서 요구하는 입력값을 저장할 구조체 변수입니다.
	Tc8102InBlock	c8102inblock = {};
	memset(&c8102inblock, 0x20, sizeof Tc8102InBlock);

	//화면상의 계좌 비밀번호(평문)를 확인합니다
	CString	strPassword;
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(strPassword);

	//종목코드 확인
	CString	strItemCode;
	GetDlgItem(IDC_EDIT_JCODE)->GetWindowText(strItemCode);
	strItemCode.TrimRight();

	//수량 확인
	CString	strAmount;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowText(strAmount);
	strAmount.TrimRight();

	//단가 확인
	CString	strPrice;
	GetDlgItem(IDC_EDIT_PRICE)->GetWindowText(strPrice);
	strPrice.TrimRight();

	// 각 입력 필드에서 요구하는 값들에 대한 자세한 정의는 *.doc 문서를 통해 확인할 수 있습니다.
	// 계좌비밀번호는 거래비밀번호와는 다릅니다. 거래비밀번호가 입력되지 않도록 주의하시기 바랍니다.
	// 서버로 전송되는 비밀번호는 평문이 아닌 복호화 불가능한 hash 비밀번호로 채웁니다
	m_wmca.SetAccountIndexPwd(c8102inblock.pswd_noz8, nAccountIndex, strPassword);

	CString strMarket;
	m_ctlMarket.GetWindowText(strMarket);

	SMOVE(c8102inblock.issue_codez6, strItemCode);		//종목코드
	NMOVE(c8102inblock.order_qtyz12, strAmount);		//수량
	NMOVE(c8102inblock.order_unit_pricez10, strPrice);	//가격
	SMOVE(c8102inblock.trade_typez2, "00");				//지정가(00),시장가(03)
	SMOVE(c8102inblock.rmt_mkt_cdz3, strMarket);		//거래소(SOR,KRX,NXT)
	//아래 입력하는 거래비밀번호1, 2란에는 사용자의 거래비밀번호를 입력해야합니다.
	//거래(주문)비밀번호는 계좌비밀번호와는 다르며 계좌비밀번호를 넣지 않도록 주의하시기 바랍니다.
	m_wmca.SetOrderPwd(c8102inblock.trad_pswd_no_1z8, "--------");
	m_wmca.SetOrderPwd(c8102inblock.trad_pswd_no_2z8, "--------");

	//주식 주문
	m_wmca.Query(
		GetSafeHwnd(),			//이 윈도우로 응답 메시지를 받겠습니다.
		TRID_c8102,				//이 서비스에 대해서 TRID_c8102 식별자를 붙이겠습니다. (예시일 뿐이며,다른 값을 넣어서 사용하셔도 됩니다)
		"c8102",				//호출하려는 서비스 코드는 c8102 입니다.
		(char*)&c8102inblock,	//c8102에서 요구하는 입력 구조체 포인터를 지정합니다.
		sizeof Tc8102InBlock,	//입력 구조체 크기입니다
		nAccountIndex			//원하는 계좌번호 인덱스를 지정합니다.		(계좌번호는 '1'번부터 시작)
	);

}

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
BOOL CWMCALOADERDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_ctlMarket.InsertString(0, "SOR");	// SOR 주문 
	m_ctlMarket.InsertString(1, "KRX");	// KRX 거래소로 주문
	m_ctlMarket.InsertString(2, "NXT");	// NXT 거래소로 주문

	m_ctlMarket.SetCurSel(0);

	UpdateControlStatus(FALSE);

	//////////////////////////////////////////////////////////////////////////
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CWMCALOADERDlg::OnBnClickedConnectLocal()
{
	//접속 및 로그인	(PC저장 인증서)
	//매체코드는 특별한 경우를 제외하고 항상 아래 기본값을 사용하시기 바랍니다.
	m_wmca.ConnectCert(GetSafeHwnd(), CA_WMCAEVENT, 'P', '1', 1/*PC저장 인증서로 접속*/);
}


void CWMCALOADERDlg::OnBnClickedConnectCloud()
{
	//접속 및 로그인	(클라우드 인증서)
	//매체코드는 특별한 경우를 제외하고 항상 아래 기본값을 사용하시기 바랍니다.
	m_wmca.ConnectCert(GetSafeHwnd(), CA_WMCAEVENT, 'P', '1', 2/*클라우드 인증서로 접속*/);
}

void CWMCALOADERDlg::UpdateControlStatus(BOOL bConntected)
{
	// 접속되었음
	GetDlgItem(IDC_COMBOACCOUNTLIST)->EnableWindow(bConntected);
	GetDlgItem(IDC_STATICLOGIN)->EnableWindow(bConntected);
	GetDlgItem(IDC_EDIT3)->EnableWindow(!bConntected);
	GetDlgItem(IDC_EDIT2)->EnableWindow(!bConntected);
	GetDlgItem(IDC_EDIT1)->EnableWindow(!bConntected);
	GetDlgItem(IDC_CONNECT)->EnableWindow(!bConntected);
	GetDlgItem(IDC_CONNECT_LOCAL)->EnableWindow(!bConntected);
	GetDlgItem(IDC_CONNECT_CLOUD)->EnableWindow(!bConntected);
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(bConntected);
	GetDlgItem(IDC_BALANCE)->EnableWindow(bConntected);
	GetDlgItem(IDC_COMBO_MARKET)->EnableWindow(bConntected);

	GetDlgItem(IDC_EDIT_JCODE)->EnableWindow(bConntected);
	GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(bConntected);
	GetDlgItem(IDC_EDIT_AMOUNT)->EnableWindow(bConntected);
	GetDlgItem(IDC_EDIT_PRICE)->EnableWindow(bConntected);

	GetDlgItem(IDC_BUTTON_CURRENT)->EnableWindow(bConntected);
	GetDlgItem(IDC_ORDER)->EnableWindow(bConntected);
	GetDlgItem(IDC_BALANCE)->EnableWindow(bConntected);
}
