# QV API Required Spec

작성일: 2026-03-08

## 목적

현재 이슈는 `로그인 성공 후 s8180 조회 단계에서 특정 계좌만 계좌비밀번호 오류(21263)`가 나는 문제다.
코드 수정보다 먼저, 현재 기능과 디버깅에 실제로 필요한 QV Open API 명세를 고정해 둔다.

이 문서는 다음 범위만 다룬다.

- 로그인 후 계좌 목록을 받는 `WMCA_CONNECTED` 이벤트 구조
- 계좌비밀번호 해시를 만드는 `wmca.dll` 함수
- 체결 조회 `s8180`
- 분할체결 상세조회 `s8118`
- 위 명세를 앱 내부 JSON / Python UI 모델에 어떻게 보존해야 하는지

## 기준 자료

- `주문_SPEC_20251128.doc`
- `SAMPLES/VC++/WmcaIntf.h`
- `SAMPLES/VC++/trio_ord.h`
- 현재 구현: `cpp/src/qv_protocol.h`, `cpp/src/qv_auth.cpp`, `cpp/src/qv_query.cpp`

## 1. 필요한 wmca.dll 함수

현재 기능 기준으로 필요한 외부 함수는 아래와 같다.

| 함수 | 용도 | 비고 |
| --- | --- | --- |
| `wmcaConnect` | ID / 로그인 비밀번호 / 인증서 비밀번호로 로그인 | 로그인은 현재 정상 동작 중 |
| `wmcaQuery` | TR 조회 실행 | `s8180`, `s8118` 호출에 사용 |
| `wmcaSetAccountIndexPwd` | 계좌 인덱스 기준 계좌비밀번호 해시 생성 | `char[44]` 출력 버퍼 필요 |
| `wmcaSetAccountNoPwd` | 계좌번호 기준 계좌비밀번호 해시 생성 | 특정 계좌에서 index 기준 해시가 실패할 경우 비교 필요 |
| `wmcaSetAccountNoByIndex` | 계좌 인덱스로 계좌번호 확인 | 자동 검증/교차검증용 후보 |
| `wmcaSetOrderPwd` | 거래비밀번호1/2 해시 생성 | 현재는 선택 사용, `s8180`/`s8118` 입력에 연결 가능 |

샘플 헤더 기준 선언은 `SAMPLES/VC++/WmcaIntf.h`에 있다.

### 해시 관련 실무 규칙

- 계좌비밀번호 해시 출력 길이는 44바이트로 취급한다.
- TR 입력 구조체의 해당 필드는 공백 초기화 후 채우는 샘플 패턴을 우선 기준으로 본다.
- `wmcaSetAccountIndexPwd`와 `wmcaSetAccountNoPwd` 중 어느 기준이 실제 계좌별로 맞는지는 아직 런타임으로 확정되지 않았다.

## 2. 로그인 응답 계좌 구조 (`WMCA_CONNECTED`)

현재 앱이 가장 많이 버리고 있는 정보다.

`cpp/src/qv_protocol.h` 기준 계좌 구조:

| 필드 | 크기 | 의미 |
| --- | --- | --- |
| `account_no` | 11 | 계좌번호 |
| `account_name` | 40 | 계좌명 |
| `act_pdt_cdz3` | 3 | 상품코드 |
| `amn_tab_cdz4` | 4 | 관리점코드 |
| `expr_datez8` | 8 | 위임만기일 |
| `granted` | 1 | 일괄주문 허용계좌 여부 (`G` 허용) |
| `filler` | 189 | 미사용 |

### 현재 문제와 직접 연결되는 포인트

현재 앱은 로그인 후 계좌 목록에서 `account_index`, `account_no`만 보존한다.
하지만 실제로는 아래 필드도 같이 보존해야 한다.

- `account_name`
- `act_pdt_cdz3`
- `amn_tab_cdz4`
- `expr_datez8`
- `granted`

이유:

- `s8180` 조회 가능 계좌를 필터링하거나 라벨링할 근거가 된다.
- 동일한 로그인 세션에 보이는 계좌라도 상품코드/권한이 달라 조회 가능 여부가 다를 수 있다.
- 계좌비밀번호 해시 기준(`index` vs `account_no`)을 계좌 특성별로 나눠 볼 근거가 된다.

## 3. `s8180` 주문/체결 조회

출처: `주문_SPEC_20251128.doc`

### 입력 필드

| 순번 | 항목 | 타입 | 크기 | 비고 |
| --- | --- | --- | --- | --- |
| 1 | 조회주체구분 | char | 1 | `3` = 계좌별조회 |
| 2 | 비밀번호 | char | 44 | 계좌비밀번호 해시 |
| 3 | 그룹번호 | float | 4 | 기본 `0000` |
| 4 | 시장구분 | char | 1 | 기본 `0` 전체 |
| 5 | 주문일자 | char | 8 | `YYYYMMDD` |
| 6 | 종목번호 | char | 12 | 선택 |
| 7 | 매체구분 | char | 2 | `CC` 전체 / `AA` 영업 / `BB` 온라인 |
| 8 | 체결구분 | char | 1 | `2` = 체결 |
| 9 | 조회순서 | char | 1 | `0` = 번호 |
| 10 | 정렬구분 | char | 1 | `0` = 주문번호순 |
| 11 | 매수도구분 | char | 1 | 기본 `0` |
| 12 | 신용구분 | char | 1 | 기본 `0` |
| 13 | 계좌구분 | char | 1 | 기본 `0` |
| 14 | 주문번호 | float | 10 | 선택 |
| 15 | CTS | char | 56 | 페이징 키 |
| 16 | 거래비밀번호1 | char | 44 | 선택 |
| 17 | 거래비밀번호2 | char | 44 | 선택 |
| 18 | ISPAGEUP | char | 1 | 다음화면이 있으면 `N`, 없으면 공백 |

### 현재 앱에서 반드시 유지해야 하는 동작

- `조회주체구분 = 3`
- `비밀번호 = 계좌비밀번호 해시 44바이트`
- `주문일자 = 조회일`
- `체결구분 = 2`
- `CTS`, `ISPAGEUP`로 페이징 유지

### 현재 앱에서 읽는 주요 출력 필드

전체 출력 필드를 모두 쓰지는 않는다. 현재 앱/디버깅에 필요한 핵심 필드는 아래다.

- `주문일자`
- `주문번호`
- `원주문번호`
- `계좌번호`
- `종목번호`
- `종목명`
- `주문수량`
- `체결수량`
- `주문단가`
- `체결평균단가`
- `처리시간`
- `요청시장코드`
- `전송시장코드`
- `SOR시장분할여부`
- `CTS`
- `다음버튼유무`

### 현재 이슈와 연결된 해석

지금은 아래 사실이 확인된 상태다.

- 로그인은 성공한다.
- `wmcaSetAccountIndexPwd` 호출도 성공 로그가 남는다.
- 그런데 `s8180`에서만 `21263 계좌비밀번호를 잘못 입력하셨습니다.`가 반환된다.

즉, 현재 남은 원인 후보는 아래 둘이다.

1. 선택한 계좌 자체가 `s8180` 조회 대상이 아닌데 UI에서 구분 없이 노출된다.
2. 해당 계좌는 `wmcaSetAccountIndexPwd`가 아니라 `wmcaSetAccountNoPwd` 기준 해시가 맞다.

## 4. `s8118` 분할체결 상세조회

출처: `주문_SPEC_20251128.doc`

### 문서 기준 입력 필드

| 순번 | 항목 | 타입 | 크기 | 비고 |
| --- | --- | --- | --- | --- |
| 1 | 주문일자 | char | 8 | `YYYYMMDD` |
| 2 | 주문번호 | char | 10 | 앞에 `0` padding |
| 3 | 거래비밀번호1 | char | 44 | 선택 |
| 4 | 거래비밀번호2 | char | 44 | 선택 |

### 샘플 헤더와의 차이

`SAMPLES/VC++/trio_ord.h`의 `Ts8118InBlock`에는 `accnt_noz11`가 들어 있다.
하지만 최신 `주문_SPEC_20251128.doc`의 `s8118` 입력 필드 표에는 계좌번호가 없다.

정리:

- 현재 구현은 문서(주문일자 + 주문번호 + 거래비밀번호1/2)를 따르고 있다.
- 샘플 헤더와 문서가 다르므로, `s8118` 관련 구조체는 문서 우선으로 보되 런타임 검증이 필요하다.

### 현재 앱에서 읽는 주요 출력 필드

- 주문일자
- 주문번호
- 원주문번호
- 종목코드
- 종목명
- 주문명
- 매매명
- 주문수량
- 주문단가
- 체결수량
- 체결금액
- 처리명
- 거부코드
- 매체명
- 요청시장코드
- 전송시장코드
- 분할주문여부

## 5. 앱 내부 계약에서 반드시 추가/유지해야 할 필드

외부 QV API 명세만 맞아도, 내부 JSON / Python 모델이 메타데이터를 버리면 다시 같은 문제를 반복한다.

### 계좌 목록 JSON (`fetch.exe --list-accounts`)

현재 저장 필드:

- `account_index`
- `account_no`

추가 필요 필드:

- `account_name`
- `act_pdt_cd`
- `amn_tab_cd`
- `expr_date`
- `granted`

### Python 계좌 모델

현재 `AccountInfo`는 아래 두 필드만 가진다.

- `account_index`
- `account_no`

확장 필요 필드:

- `account_name`
- `act_pdt_cd`
- `amn_tab_cd`
- `expr_date`
- `granted`

### UI 계좌 선택 화면

다음 정보를 사용자에게 보여줄 수 있어야 한다.

- 계좌번호
- 계좌명
- 상품코드
- 일괄주문 허용 여부
- 필요 시 “조회 미보장” 또는 “추가 검증 필요” 같은 라벨

## 6. 다음 구현에서 확인할 실험 항목

우선순위대로 정리하면 아래와 같다.

1. 계좌 목록 JSON과 Python 모델에 로그인 응답 메타데이터를 모두 보존한다.
2. UI에서 `granted`, `act_pdt_cd`를 같이 노출한다.
3. `s8180` 호출 전 해시 바인딩을 `index`와 `account_no` 두 방식으로 비교 가능하게 한다.
4. 계좌별로 어떤 바인딩이 성공하는지 로그로 남긴다.
5. 필요하면 `wmcaSetAccountNoByIndex` 결과와 로그인 응답 `account_no`가 일치하는지도 교차검증한다.

## 7. 현재 확정된 것 vs 미확정인 것

### 확정된 것

- 로그인 자격증명 자체는 맞다.
- `s8180` 실패는 로그인 이후 특정 계좌 조회에서만 난다.
- `wmcaSetAccountIndexPwd` 호출 자체는 되고 있다.
- 예전 가설이던 “해시를 `std::string`으로 복사하면서 깨진다”는 것은 현재 로그로는 주원인이 아니다.

### 아직 미확정인 것

- 특정 계좌가 원래 `s8180` 조회 대상이 아닌지
- `index` 기준 해시가 틀리고 `account_no` 기준 해시가 맞는지
- `granted` / `act_pdt_cdz3` 중 어떤 필드가 조회 가능 여부와 직접 연결되는지

## 8. 진단 실행 스위치

원인 판별용 실행 스위치는 아래처럼 고정한다.

| 환경변수 | 값 | 의미 |
| --- | --- | --- |
| `QV_ACCOUNT_PASSWORD_HASH_BINDING` | `index` | `wmcaSetAccountIndexPwd`만 사용 |
| `QV_ACCOUNT_PASSWORD_HASH_BINDING` | `account_no` | `wmcaSetAccountNoPwd`만 사용 |
| `QV_ACCOUNT_PASSWORD_HASH_BINDING` | `auto_probe` | `index`가 21263일 때만 `account_no`를 1회 추가 시도 |
| `QV_DIAGNOSTIC_MODE` | `1` | 진단 sidecar JSON 생성 활성화 |
| `QV_DIAGNOSTIC_OUTPUT` | 파일 경로 | 진단 JSON 출력 경로 지정 |
| `QV_S8180_PASSWORD_MODE` | `encrypted` / `plain` / `blank` | `s8180` 비밀번호 입력 모드 |

기본값:

- `QV_ACCOUNT_PASSWORD_HASH_BINDING=auto_probe`
- `QV_DIAGNOSTIC_MODE=0`
- `QV_S8180_PASSWORD_MODE=encrypted`

## 9. 진단 JSON 계약

`QV_DIAGNOSTIC_MODE=1` 또는 `QV_DIAGNOSTIC_OUTPUT` 지정 시, `fetch.exe`는 별도 진단 JSON을 저장한다.
기본 출력 경로는 결과 JSON 옆의 `<output>.diagnostic.json`이다.

단일 계좌 기준 핵심 구조:

```json
{
  "schema_version": "1.0",
  "generated_at": "...",
  "trade_date": "20260308",
  "selected_account": {
    "account_index": 3,
    "account_no": "20001505931",
    "account_name": "...",
    "act_pdt_cd": "...",
    "amn_tab_cd": "...",
    "expr_date": "20271231",
    "granted": "G",
    "is_granted_batch": true,
    "diagnostic_labels": []
  },
  "s8180_diagnostic": {
    "binding_mode": "account_no",
    "binding_mode_requested": "auto_probe",
    "password_mode": "encrypted",
    "hash_generation_ok": true,
    "query_submitted": true,
    "query_succeeded": true,
    "hash_source": "wmcaSetAccountNoPwd",
    "server_message_code": "21263",
    "server_message": "계좌비밀번호를 잘못 입력하셨습니다.",
    "classification": "success_after_binding_switch",
    "candidate_cause": "hash_binding_mismatch",
    "attempts": []
  }
}
```

다중 계좌 실행 시에는 `account_diagnostics[]` 배열에 계좌별 진단 결과를 저장한다.

## 10. 분류 규칙

현재 구현에서 진단 JSON의 `classification` / `candidate_cause`는 아래처럼 해석한다.

- `success_after_binding_switch` + `hash_binding_mismatch`
  - `index` 실패 뒤 `account_no` 성공
- `account_password_rejected` + `account_ineligible_or_password_rejected_on_all_bindings`
  - `index`, `account_no` 모두 계좌비밀번호 오류
- `account_password_rejected` + `binding_mismatch_or_ineligible_account`
  - 단일 바인딩 실험에서 계좌비밀번호 오류
- `hash_generation_failed`
  - DLL 해시 생성 함수 호출 실패
- `query_timeout` / `event_wait_failed`
  - 전송/대기 또는 TR 계약 이슈 가능성
