#include "Warrior.h"

#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AWarrior::AWarrior()
{
	JumpMaxHoldTime = 0.3f;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 900.0f;
	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	SpringArmComponent->SetRelativeRotation(FRotator(0.0f, -90.0f,  0.0f));
	SpringArmComponent->bInheritYaw = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetArrowComponent()->SetHiddenInGame(false);
	
	GetSprite()->SetCastShadow(true);
	GetSprite()->SetRelativeLocation(DefaultSpriteOffset);
	GetSprite()->SetRelativeScale3D(FVector(5.0f));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 10000.0f, 0.0f);
	GetCharacterMovement()->CrouchedHalfHeight = 50.0f;
	GetCharacterMovement()->GravityScale = 4.0f;
	GetCharacterMovement()->JumpZVelocity = 800.0f;
	GetCharacterMovement()->AirControl = 0.9f;
}

void AWarrior::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsSliding)
	{
		AddMovementInput(GetActorForwardVector());
	}
}

void AWarrior::BeginPlay()
{
	Super::BeginPlay();

	CrouchedSpriteOffset = FVector(DefaultSpriteOffset.X, DefaultSpriteOffset.Y, CrouchedSpriteHeight);

	LandedDelegate.AddDynamic(this, &AWarrior::OnCharacterLanded);
}

void AWarrior::Move(const float InputActionValue)
{
	if (bIsCrouched)
	{
		if (InputActionValue < 0.0f)
		{
			SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
		}
		else if (InputActionValue > 0.0f)
		{
			SetActorRotation(FRotator(0.0f));
		}
		
		return;
	}
	
	AddMovementInput(FVector::ForwardVector, InputActionValue);
	SetMoveInputValue(InputActionValue);
}

void AWarrior::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);
	GetSprite()->SetRelativeLocation(CrouchedSpriteOffset);
}

void AWarrior::UnCrouch(bool bClientSimulation)
{
	if (IsSliding || IsWallAbove())
	{
		return;
	}
	
	Super::UnCrouch(bClientSimulation);
	GetSprite()->SetRelativeLocation(DefaultSpriteOffset);
}

void AWarrior::Slide()
{
	IsSliding = true;

	FTimerHandle SlideTimerHandle;
	GetWorldTimerManager().SetTimer(SlideTimerHandle, this, &AWarrior::StopSlide, SlideDuration);
}

void AWarrior::StopSlide()
{
	IsSliding = false;

	if (bIsCrouched) return; // TODO: DEBUG Crouch Input
		
	UnCrouch();
}

void AWarrior::OnJumpInput()
{
	if (IsSliding) return;
		
	if (bIsCrouched)
	{
		Slide();

		return;
	}

	Jump();
	IsJumping = true;
}

bool AWarrior::IsGrounded() const
{
	return GetCharacterMovement()->IsMovingOnGround();
}

void AWarrior::OnCharacterLanded(const FHitResult& Hit)
{
	IsJumping = false;
}

bool AWarrior::IsWallAbove() const
{
	FHitResult HitResult;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + FVector(0.0f, 0.0f, 100.0f),
		ECC_Visibility,
		Params);

	return HitResult.bBlockingHit && HitResult.GetActor()->ActorHasTag(WallTag);
}