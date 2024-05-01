
#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "RandomMovingPlatforms.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MADI_API URandomMovingPlatforms : public USceneComponent
{
	GENERATED_BODY()

public:	
	URandomMovingPlatforms();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Movement)
	float PlatformSpeed;
	float Speed = 0;

	UPROPERTY(EditAnywhere, Category = Movement)
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = Movement)
	FVector EndLocation;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UFUNCTION(Server, Reliable)
	void ServerMovePlatform(float DeltaTime);

	UPROPERTY(ReplicatedUsing = OnRep_MovePlatform)
	FVector NewVector;

	UFUNCTION()
	void OnRep_MovePlatform();

	AActor* Owner;

		
};
