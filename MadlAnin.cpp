

#include "MadlAnin.h"
#include "MadlChar.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMadlAnin::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    MadlChar = Cast<AMadlChar>(TryGetPawnOwner());
}

void UMadlAnin::NativeUpdateAnimation(float DeltaTime)
{
    Super::NativeUpdateAnimation(DeltaTime);

    if (MadlChar == nullptr)
    {
        MadlChar = Cast<AMadlChar>(TryGetPawnOwner());
    }
    if (!MadlChar)return;

    FVector Velocity = MadlChar->GetVelocity();
    Velocity.Z = 0.f;
    Speed = Velocity.Size();

    bIsInAir = MadlChar->GetCharacterMovement()->IsFalling();

    bIsAccelerating = MadlChar->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
}
