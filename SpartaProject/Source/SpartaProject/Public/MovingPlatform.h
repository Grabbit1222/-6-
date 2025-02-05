// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

// 발판 움직임 타입 정의
UENUM(BlueprintType)
enum class EPlatformMovementType : uint8
{
	SingleShot UMETA(DisplayName = "Single Shot"),
	PingPong UMETA(DisplayName = "Ping Pong")
};

UCLASS(Blueprintable)
class SPARTAPROJECT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform|Properties")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform|Properties")
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform|Properties")
	FVector NewLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform|Properties")
	EPlatformMovementType MovementType;

	void SetNewLocation(const FVector& NewLoc);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovingPlatform|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform|Components")
	UAudioComponent* AudioComp;


	void DestroyPlatform();

	void RespawnPlatform();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle Timer;

	FVector OriginalLocation;
};
