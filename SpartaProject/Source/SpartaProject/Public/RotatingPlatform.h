// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class SPARTAPROJECT_API ARotatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform|Properties")
	float RotationSpeed;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MovingPlatform|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovingPlatform|Components")
	UStaticMeshComponent* StaticMeshComp;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
