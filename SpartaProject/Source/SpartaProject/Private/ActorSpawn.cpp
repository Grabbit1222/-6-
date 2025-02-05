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
    // Spawn parameters ����
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // SpawnVolume�� ũ��� �߽� ��� (�����Ϳ��� ������ �� ���)
    FVector BoxCenter = SpawnVolume->GetComponentLocation();  // �ڽ��� �߽� ��ġ
    FVector BoxExtent = SpawnVolume->GetScaledBoxExtent();    // �ڽ��� ũ�� (������)

    for (int32 i = 0; i < 10; ++i)
    {
        // �ڽ� ���� ������ X, Y, Z ��ǥ ������ ���� RandRange ����
        float RandomX = FMath::RandRange(BoxCenter.X - BoxExtent.X, BoxCenter.X + BoxExtent.X);
        float RandomY = FMath::RandRange(BoxCenter.Y - BoxExtent.Y, BoxCenter.Y + BoxExtent.Y);
        float RandomZ = FMath::RandRange(BoxCenter.Z - BoxExtent.Z, BoxCenter.Z + BoxExtent.Z);

        FVector RandomLocation = FVector(RandomX, RandomY, RandomZ);

        // MovingPlatform�� ȸ�� �ӵ�, �̵� �ӵ� �� �̵� ���� ���� ����
        float RandomRotationSpeed = FMath::RandRange(30.0f, 100.0f);  // ��: 30~100 ����
        float RandomMoveSpeed = FMath::RandRange(5.0f, 500.0f);       // ��: 5~500 ����
        EPlatformMovementType RandomMovementType = static_cast<EPlatformMovementType>(FMath::RandRange(0, 1)); // 0 �Ǵ� 1 (��: SingleShot or PingPong)

        // SpawnLocation�� Rotation ����
        FRotator SpawnRotation = FRotator::ZeroRotator;

        // MovingPlatform ����
        AMovingPlatform* SpawnedActor = GetWorld()->SpawnActor<AMovingPlatform>(AMovingPlatform::StaticClass(), RandomLocation, SpawnRotation, SpawnParams);

        if (SpawnedActor)
        {
            // �������� ������ ���� MovingPlatform�� �Ķ���Ϳ� ����
            SpawnedActor->RotationSpeed = RandomRotationSpeed;
            SpawnedActor->MoveSpeed = RandomMoveSpeed;
            SpawnedActor->MovementType = RandomMovementType;

            // NewLocation ���� ���� (X, Y�� �������� ����, Z�� ����)
            FVector RandomNewLocation = FVector(
                FMath::RandRange(BoxCenter.X - BoxExtent.X, BoxCenter.X + BoxExtent.X),
                FMath::RandRange(BoxCenter.Y - BoxExtent.Y, BoxCenter.Y + BoxExtent.Y),
                RandomLocation.Z  // Z�� ����
            );
            SpawnedActor->SetNewLocation(RandomNewLocation);  // NewLocation�� �����ϴ� �Լ� ȣ��

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
    SpawnActor(); // 10���� MovingPlatform�� �����մϴ�.
}

// Called every frame
void AActorSpawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
