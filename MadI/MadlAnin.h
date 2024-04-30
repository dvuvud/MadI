
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MadlAnin.generated.h"

/**
 * 
 */
class AMadlChar;

UCLASS()
class MADI_API UMadlAnin : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime);

private:

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	AMadlChar* MadlChar;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	bool bIsAccelerating;
};
