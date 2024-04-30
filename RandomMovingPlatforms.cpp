

#include "RandomMovingPlatforms.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

URandomMovingPlatforms::URandomMovingPlatforms()
{
	PrimaryComponentTick.bCanEverTick = true;

	NewVector = StartLocation;
}

void URandomMovingPlatforms::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URandomMovingPlatforms, NewVector);

}


void URandomMovingPlatforms::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	
}


void URandomMovingPlatforms::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Owner && Owner->HasAuthority())
	{
		ServerMovePlatform(DeltaTime);
	}

}

void URandomMovingPlatforms::ServerMovePlatform_Implementation(float DeltaTime)
{
	FVector DistanceVector;
	DistanceVector = EndLocation - StartLocation;
	Speed += PlatformSpeed * DeltaTime;
	float MovingVar = (0.5 + 0.5 * FMath::Sin(Speed));
	NewVector = StartLocation + DistanceVector * MovingVar;
	Owner->SetActorLocation(NewVector);
}

void URandomMovingPlatforms::OnRep_MovePlatform()
{
	if (Owner)
	{
		Owner->SetActorLocation(NewVector);
	}
}

