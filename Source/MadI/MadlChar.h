
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MadlChar.generated.h"


	class UCameraComponent;
	class USpringArmComponent;
	class UInputAction;
	class UInputMappingContext;

UCLASS()
class MADI_API AMadlChar : public ACharacter
{
	GENERATED_BODY()

public:

	AMadlChar();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* MadlMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* NoGravityAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void NoGravity();

	int ToggleGravityOnAndOffInteger = 0;

	virtual void Jump() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	APlayerController* MadlPlayerController;

	UPROPERTY(EditAnywhere, Category = Camera)
	float MouseSensitivity = 0.5f;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

};
