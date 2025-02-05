#include "ActorSpawn.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"
#include "DrawDebugHelpers.h"

// Sets default values
AActorSpawn::AActorSpawn()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
    SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AActorSpawn::SpawnActor()
{
    // Spawn parameters 설정
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // SpawnVolume의 크기와 중심 얻기 (에디터에서 설정된 값 사용)
    FVector BoxCenter = SpawnVolume->GetComponentLocation();  // 박스의 중심 위치
    FVector BoxExtent = SpawnVolume->GetScaledBoxExtent();    // 박스의 크기 (반지름)

    for (int32 i = 0; i < 10; ++i)
    {
        // 박스 범위 내에서 X, Y, Z 좌표 각각에 대해 RandRange 적용
        float RandomX = FMath::RandRange(BoxCenter.X - BoxExtent.X, BoxCenter.X + BoxExtent.X);
        float RandomY = FMath::RandRange(BoxCenter.Y - BoxExtent.Y, BoxCenter.Y + BoxExtent.Y);
        float RandomZ = FMath::RandRange(BoxCenter.Z - BoxExtent.Z, BoxCenter.Z + BoxExtent.Z);

        FVector RandomLocation = FVector(RandomX, RandomY, RandomZ);

        // MovingPlatform의 회전 속도, 이동 속도 및 이동 유형 랜덤 설정
        float RandomRotationSpeed = FMath::RandRange(30.0f, 100.0f);  // 예: 30~100 범위
        float RandomMoveSpeed = FMath::RandRange(5.0f, 500.0f);       // 예: 5~500 범위
        EPlatformMovementType RandomMovementType = static_cast<EPlatformMovementType>(FMath::RandRange(0, 1)); // 0 또는 1 (예: SingleShot or PingPong)

        // SpawnLocation과 Rotation 설정
        FRotator SpawnRotation = FRotator::ZeroRotator;

        // MovingPlatform 생성
        AMovingPlatform* SpawnedActor = GetWorld()->SpawnActor<AMovingPlatform>(AMovingPlatform::StaticClass(), RandomLocation, SpawnRotation, SpawnParams);

        if (SpawnedActor)
        {
            // 랜덤으로 설정된 값을 MovingPlatform의 파라미터에 적용
            SpawnedActor->RotationSpeed = RandomRotationSpeed;
            SpawnedActor->MoveSpeed = RandomMoveSpeed;
            SpawnedActor->MovementType = RandomMovementType;

            // NewLocation 랜덤 설정 (X, Y만 랜덤으로 변경, Z는 고정)
            FVector RandomNewLocation = FVector(
                FMath::RandRange(BoxCenter.X - BoxExtent.X, BoxCenter.X + BoxExtent.X),
                FMath::RandRange(BoxCenter.Y - BoxExtent.Y, BoxCenter.Y + BoxExtent.Y),
                RandomLocation.Z  // Z는 고정
            );
            SpawnedActor->SetNewLocation(RandomNewLocation);  // NewLocation을 설정하는 함수 호출

            UE_LOG(LogTemp, Warning, TEXT("Spawned AMovingPlatform at %s with RotationSpeed: %f, MoveSpeed: %f, MovementType: %d"),
                *SpawnedActor->GetActorLocation().ToString(),
                RandomRotationSpeed,
                RandomMoveSpeed,
                static_cast<int32>(RandomMovementType));
        }
    }
}

// Called when the game starts or when spawned
void AActorSpawn::BeginPlay()
{
    Super::BeginPlay();
    SpawnActor(); // 10개의 MovingPlatform을 스폰합니다.
}

// Called every frame
void AActorSpawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
