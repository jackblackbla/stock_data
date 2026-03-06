# NH Trade Logger

NH투자증권 QV Open API 체결 데이터를 조회하고, 매매 근거를 입력해 엑셀로 내보내는 Windows 데스크톱 도구입니다.

## 지원 범위
- OS: Windows 10+
- 운영 형태: 단일 사용자 / 단일 PC
- 배포 형태: x86 onedir + Inno Setup 설치 프로그램

## 디렉토리
- `cpp/`: `fetch.exe` (QV DLL 연동, JSON 출력)
- `python/`: GUI/SQLite/엑셀
- `data/`: runtime DB/JSON/엑셀
- `scripts/`: 실행/스케줄/패키징 배치
- `installer/`: Inno Setup 설치 스크립트

## JSON 계약
`fetch.exe` 출력 루트 필드:
- `schema_version`
- `trade_date`
- `generated_at`
- `account_masked`
- `status`
- `errors[]`
- `executions[]`

`order_no`는 전 구간 10자리 문자열(`0` padding) 기준입니다.

## C++ fetch 빌드 (Windows x86)
1. Visual Studio에서 x86 툴체인 사용
2. `cmake -S cpp -B cpp/build -A Win32`
3. `cmake --build cpp/build --config Release`

CLI:
- `fetch.exe --date YYYYMMDD --output <json_path> [--log <log_path>]`

종료코드:
- `0`: 성공
- `10`: DLL 로드 실패
- `20`: 로그인 실패
- `30`: TR 조회 실패
- `40`: JSON 저장 실패

## QV 로그인 환경변수
`fetch.exe`는 `wmcaConnect`를 통해 로그인합니다.

- `QV_ID`: 로그인 ID
- `QV_PASSWORD`: 계좌 비밀번호
- `QV_CERT_PASSWORD`: 인증서 비밀번호
- `QV_ACCOUNT_INDEX` (기본 `1`): 조회 계좌 인덱스
- `QV_DLL_PATH` (선택): `wmca.dll` 절대경로

환경변수가 비어 있으면 Windows 로그인 다이얼로그를 띄웁니다.
다이얼로그를 사용할 수 없는 경우에만 콘솔 입력으로 fallback 합니다.

## TR 설정 환경변수
- `QV_EXEC_TR_CODE` (기본 `s8180`): 체결 조회 TR 코드
- `QV_SPLIT_TR_CODE` (기본 `s8118`): 분할체결 상세 TR 코드
- `QV_QUERY_TIMEOUT_MS` (기본 `15000`)
- `QV_TRADE_PASSWORD1`, `QV_TRADE_PASSWORD2` (선택): TR 입력 거래비밀번호
- `QV_ACCOUNT_PASSWORD` (선택): s8180 입력 비밀번호

기본 구현은 문서 기준 `s8180` 체결조회 + `s8118` 분할체결 상세 구조체 파서를 사용합니다.

s8180 페이징은 `CTS + ISPAGEUP(\"N\")` 로직을 사용합니다.
`SOR시장분할여부 == Y`인 주문에 대해 s8118을 호출하고, 체결단가는 `체결금액 / 체결수량`으로 역산합니다.

## Python 실행
1. x86 Python 3 설치
2. 의존성 설치
   - `pip install -r python/requirements.txt`
3. GUI 실행
   - `python python/main.py`
4. 자동 모드
   - `python python/main.py --auto`

## 자동 모드 동작
1. fetch 실행(JSON 생성)
2. 근거 미입력 건수 확인
3. 미입력 있으면 트레이 알림
4. 미입력 없으면 엑셀 생성 후 종료

## Windows 스크립트
- `scripts/run.bat`: fetch 후 GUI 실행
- `scripts/schedule_setup.bat`: 15:40 스케줄 작업 등록
- `scripts/build_pyinstaller.bat`: onedir 패키징
- `scripts/build_installer.bat`: Inno Setup 설치 프로그램 생성
- `scripts/build_release.bat`: PyInstaller + Inno Setup 일괄 빌드
- `scripts/launch_trade_logger.bat`: 배포본 실행용 배치

## 설치형 배포
1. `scripts/build_pyinstaller.bat`
2. `scripts/build_installer.bat`

또는 한 번에:
- `scripts/build_release.bat`

설치 프로그램 산출물:
- `dist/installer/nh-trade-logger-setup-<version>.exe`

설치 경로 기본값:
- `%LOCALAPPDATA%\Programs\NHTradeLogger`

사용자 데이터 저장 위치:
- `%LOCALAPPDATA%\NHTradeLogger\data`
- `%LOCALAPPDATA%\NHTradeLogger\data\output`
- `%LOCALAPPDATA%\NHTradeLogger\logs`

## 배포본 전달 방식
최종 사용자에게는 `dist/installer/` 아래 생성된 설치 프로그램 `.exe` 하나를 전달합니다.

전달 폴더에는 다음이 포함됩니다.
- `nh-trade-logger.exe`
- `fetch.exe`
- `launch_trade_logger.bat`
- `USER_GUIDE.txt`
- 설치 후 데이터는 `%LOCALAPPDATA%\NHTradeLogger` 아래에 생성됨

## 보안/운영 주의
- `wmca.dll`은 NH 자산이므로 재배포 금지
- 인증서 비밀번호는 디스크 저장 금지
- 로그 기본 보존기간 30일
- 설치 프로그램은 NH QV Open API를 포함하지 않음

## 테스트
- 단위/계약 테스트: `python/tests/`
- 실행: `pytest python/tests`
