#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorSpawn.generated.h"

UCLASS()
class SPARTAPROJECT_API AActorSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorSpawn();

	UFUNCTION()
	void SpawnActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* SpawnVolume;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
