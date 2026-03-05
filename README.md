# NH Trade Logger

NH투자증권 QV Open API 체결 데이터를 조회(s8180, 조건부 s8118)하고, 매매 근거를 입력해 엑셀로 내보내는 Windows 데스크톱 도구입니다.

## 지원 범위
- OS: Windows 10+
- 운영 형태: 단일 사용자 / 단일 PC
- 배포 형태: x86 onedir

## 디렉토리
- `cpp/`: `fetch.exe` (QV DLL 연동, JSON 출력)
- `python/`: GUI/SQLite/엑셀
- `data/`: runtime DB/JSON/엑셀
- `scripts/`: 실행/스케줄/패키징 배치

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

## 보안/운영 주의
- `wmca.dll`은 NH 자산이므로 재배포 금지
- 인증서 비밀번호는 디스크 저장 금지
- 로그 기본 보존기간 30일

## 테스트
- 단위/계약 테스트: `python/tests/`
- 실행: `pytest python/tests`
