#include "Warrior.h"

#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AWarrior::AWarrior()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 900.0f;
	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	SpringArmComponent->SetRelativeRotation(FRotator(0.0f, -90.0f,  0.0f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetArrowComponent()->SetHiddenInGame(false);
	
	GetSprite()->SetCastShadow(true);
}

bool AWarrior::IsRunning() const
{
	return GetCharacterMovement()->IsMovingOnGround() && GetVelocity().X != 0.0f;
}

void AWarrior::Move(const float InputActionValue)
{
	AddMovementInput(FVector::ForwardVector, InputActionValue);
}