#include "MovingPlatform.h"
#include "Components/AudioComponent.h"

AMovingPlatform::AMovingPlatform()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	// 메시 강제 설정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Fab/Megascans/3D/Beach_Shelf_Rock_wepodd3/Medium/wepodd3_tier_2.wepodd3_tier_2"));

	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load static mesh for AMovingPlatform!"));
	}


	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	AudioComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;
	
	RotationSpeed = 45.0f;
	MoveSpeed = 10.0f;
	OriginalLocation = FVector::ZeroVector;

	NewLocation = FVector(500.0f, 0.0f, 0.0f);
	float MaxRange = FVector::Dist(NewLocation, OriginalLocation);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetActorLocation();


	if (StaticMeshComp && StaticMeshComp->GetStaticMesh())
	{
		UE_LOG(LogTemp, Warning, TEXT("StaticMeshComp is valid and has a mesh."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StaticMeshComp is missing or has no mesh!"));
	}

	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMovingPlatform::DestroyPlatform, 15.0f, false);
}


void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (NewLocation - OriginalLocation).GetSafeNormal();
	FVector Velocity = Direction * MoveSpeed;
	FVector DeltaDist = Velocity * DeltaTime;

	/*회전*/
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}

	/*이동*/
	if (!FMath::IsNearlyZero(MoveSpeed) && !OriginalLocation.Equals(NewLocation, 2.0f))
	{
		/*싱글 샷*/
		if (MovementType == EPlatformMovementType::SingleShot) 
		{
			AddActorWorldOffset(DeltaDist);

			if (FVector::Dist(GetActorLocation(), NewLocation) <= 6.0f)
			{
				SetActorTickEnabled(false); // Tick 중지
			}
		}

		/*핑퐁*/
		else if (MovementType == EPlatformMovementType::PingPong)
		{
			CurrentLocation += DeltaDist;
			SetActorLocation(CurrentLocation);

			// Check proximity to NewLocation
			if (FVector::Dist(CurrentLocation, NewLocation) <= 6.0f)
			{
				// Reverse direction
				FVector Temp = OriginalLocation;
				OriginalLocation = NewLocation;
				NewLocation = Temp;
			}
		}

	}
}

void AMovingPlatform::SetNewLocation(const FVector& NewLoc)
{
	NewLocation = NewLoc;
}

void AMovingPlatform::DestroyPlatform()
{
	// 플랫폼 숨기기
	SetActorHiddenInGame(true);

	// StaticMeshComp에서 충돌을 비활성화
	if (StaticMeshComp)
	{
		StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// 일정 시간 후 리스폰
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMovingPlatform::RespawnPlatform, 3.0f, false);
}




void AMovingPlatform::RespawnPlatform()
{
	// 플랫폼 다시 보이기
	SetActorHiddenInGame(false);

	// StaticMeshComp에서 충돌을 활성화
	if (StaticMeshComp)
	{
		StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	// 원래 위치로 되돌리기
	SetActorLocation(OriginalLocation);

	// 리스폰 후 일정 시간 뒤 다시 파괴
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AMovingPlatform::DestroyPlatform, 15.0f, true);
}
