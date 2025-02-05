# [6번 과제] 회전 발판과 움직이는 장애물 퍼즐 스테이지

## 📌 프로젝트 개요
언리얼 C++을 활용하여 **회전 발판과 이동 장애물**을 구현하는 프로젝트입니다.

## 🎮 주요 기능
- `Tick(float DeltaTime)`을 활용한 **프레임 독립적인 회전 및 이동**
- `UPROPERTY`를 통한 **변수(속도, 범위 등) 에디터 노출 및 조정 가능**
- `FTimerHandle`을 활용한 **시간 제한 및 동적 변화 기능** (선택 사항)
- `SpawnActor()`를 사용한 **랜덤 퍼즐 생성** (선택 사항)

## 🛠 구현 내용
### ✅ 1. C++ Actor 클래스 구현
- **회전 발판 (RotatingPlatform)**
- **이동 플랫폼 (MovingPlatform)**

### ✅ 2. `Tick()` 함수 활용한 이동/회전
- `AddActorLocalRotation()`으로 회전 구현
- `SetActorLocation()`으로 왕복 이동 구현

### ✅ 3. 리플렉션 적용
- `UPROPERTY(EditAnywhere, Category="Settings")` 적용
- 에디터에서 속도, 범위 조정 가능

## 🚀 도전 과제
- **타이머 기반 발판 변화**: `FTimerHandle` 활용
- **랜덤 퍼즐 스폰**: `SpawnActor()` 및 `FMath::RandRange()` 활용

## 📺 시연 영상
(https://youtu.be/l5MT1PED9vM?si=i1uZBrct-PrxcVnF)
