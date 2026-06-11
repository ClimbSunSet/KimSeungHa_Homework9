Homework9 - 멀티플레이어 숫자야구 게임

프로젝트 개요

언리얼 엔진 5 기반의 멀티플레이어 숫자야구 게임입니다.

Dedicated Server 환경에서 2명의 플레이어가 동시에 숫자를 맞추는 방식으로 진행됩니다.



구현 기능

필수 기능

GameMode 서버 로직 구현



AHK9\_GameModeBase에서 게임의 모든 핵심 로직을 서버에서 처리

입력 유효성 검사(ChackClientNum): 3자리 숫자, 중복 없음, 숫자 여부 확인

정답 판정(CheckAnswer): Strike/Ball/OUT 계산 후 결과 반환

게임 결과 판정(CheckGameResult): 승리/무승부 조건 확인



난수 생성 로직 구현



BeginPlay에서 1\~9 범위의 중복 없는 3자리 숫자 생성

FMath::RandRange + 중복 체크 루프로 구현



판정 로직



Strike: 같은 자리, 같은 숫자

Ball: 다른 자리, 같은 숫자

OUT: Strike/Ball 모두 0



시도 횟수 및 상태 관리



AHK9\_PlayerState에 CurrentAttempts / MaxAttempts(3) 관리

DOREPLIFETIME으로 모든 클라이언트에 복제

3회 초과 입력 시 차단



승리, 무승부, 게임 리셋



승리: 3 Strike 달성 시 승자 이름 포함 위젯 표시

무승부: 모든 플레이어가 3회 시도를 소진했을 때 판정

리셋: GameOverWidget의 재시작 버튼 → Server RPC → UGameplayStatics::OpenLevel



C++ 라이브러리 작성



HK9\_GameModeBase / HK9\_GameStateBase / HK9\_PlayerState / HK9\_PlayerController

HK9\_ChatInput / HK9\_GameOverWidget 위젯 클래스 C++로 작성





네트워크 구조

\[클라이언트] 입력

&#x20;   ↓ Server RPC (SetChatMessageString)

\[서버] 유효성 검사 → 시도 횟수 증가 → 정답 판정 → 결과 판정

&#x20;   ↓ Client RPC (PrintChatMessageString)

\[클라이언트] 결과 출력

&#x20;   ↓ NetMulticast (GameOverCallWidget)

\[모든 클라이언트] 게임 오버 위젯 표시



| 클래스              | 서버 | 클라이언트 |

| GameMode       |  ✅  | ❌            |

| GameState        |  ✅  | ✅ (복제)   |

| PlayerState        |  ✅  | ✅ (복제)   |

| PlayerController |  ✅  |    본인만    |



트러블슈팅

Client RPC 방향 혼동



문제: Client RPC를 클라이언트에서 호출하려 했으나 의도대로 동작하지 않음

원인: Client RPC는 서버가 호출, 클라이언트가 실행하는 구조

해결: Server RPC로 서버에 요청 후, 서버에서 Client RPC 호출하는 흐름으로 수정



GameState GetFirstPlayerController 이슈



문제: 2명에게 위젯을 띄워야 하는데 GetFirstPlayerController만 호출

원인: Dedicated Server 환경에서 각 클라이언트 월드에는 자신의 PC만 존재

해결: NetMulticast로 모든 클라이언트에서 실행되므로 각자 자신의 PC를 가져오면 정상 동작



AGameMode vs AGameModeBase



문제: RestartGame 함수를 찾을 수 없음

원인: HK9\_GameModeBase가 AGameModeBase 상속 → RestartGame 없음

해결: ServerTravel / OpenLevel로 우회, 이후 AGameMode 사용 예정

