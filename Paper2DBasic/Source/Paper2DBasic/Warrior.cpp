#include "Warrior.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"

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
	
	GetSprite()->SetCastShadow(true);
	GetSprite()->SetRelativeLocation(DefaultSpriteOffset);
	GetSprite()->SetRelativeScale3D(FVector(5.0f));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->SetCrouchedHalfHeight(50.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 10000.0f, 0.0f);
	GetCharacterMovement()->GravityScale = 4.0f;
	GetCharacterMovement()->JumpZVelocity = 800.0f;
	GetCharacterMovement()->AirControl = 0.9f;
}

#pragma region Life Circle Events

void AWarrior::BeginPlay()
{
	Super::BeginPlay();

	CrouchedSpriteOffset = FVector(DefaultSpriteOffset.X, DefaultSpriteOffset.Y, CrouchedSpriteHeight);
	ComboAttackIndex = -1;
}

void AWarrior::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsSliding)
	{
		AddMovementInput(GetActorForwardVector());
	}
}

#pragma endregion

#pragma region Movement Functions

void AWarrior::Attack()
{
	if (!IsGrounded() || bIsCrouched) return;
		
	if (IsAttacking) return;

	JumpToAnimationNode(JumpToAttackAnimNodeName);
	IsAttacking = true;
}

void AWarrior::Move(const float InputActionValue)
{
	HasMoveInput = true;
	
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

	if (IsAttacking) return;
	
	AddMovementInput(FVector::ForwardVector, InputActionValue);

	if (!RunAnimationTriggered && IsGrounded())
	{
		JumpToAnimationNode(JumpToRunNodeName);
		RunAnimationTriggered = true;
	}
}

void AWarrior::StopMoving()
{
	HasMoveInput = false;
	RunAnimationTriggered = false;

	if (IsAttacking || !IsGrounded() || IsSliding || bIsCrouched) return;

	JumpToAnimationNode(JumpToIdleNodeName);
}

void AWarrior::Crouch(bool bClientSimulation)
{
	HasCrouchedInput = true;

	if (IsAttacking || IsSliding || !IsGrounded() || IsWallAbove()) return;
	
	Super::Crouch(bClientSimulation);
	GetSprite()->SetRelativeLocation(CrouchedSpriteOffset);
	JumpToAnimationNode(JumpToCrouchNodeName);
}

void AWarrior::UnCrouch(bool bClientSimulation)
{
	HasCrouchedInput = false;
	
	if (!bIsCrouched || IsSliding || IsAttacking || IsWallAbove()) return;
	
	Super::UnCrouch(bClientSimulation);
	GetSprite()->SetRelativeLocation(DefaultSpriteOffset);
}

void AWarrior::Slide()
{
	IsSliding = true;
	JumpToAnimationNode(JumpToSlideNodeName);

	FTimerHandle SlideTimerHandle;
	GetWorldTimerManager().SetTimer(SlideTimerHandle, this, &AWarrior::StopSliding, SlideDuration);
}

void AWarrior::StopSliding()
{
	IsSliding = false;

	if (HasCrouchedInput || IsWallAbove())
	{
		GetSprite()->SetRelativeLocation(CrouchedSpriteOffset);
		JumpToAnimationNode(JumpToCrouchingNodeName);
	}
	else
	{
		Super::UnCrouch();
		GetSprite()->SetRelativeLocation(DefaultSpriteOffset);
		JumpToAnimationNode(JumpToStopSlidingNodeName);
	}
}

void AWarrior::OnJumpInput()
{
	if (IsAttacking || !IsGrounded()) return;
		
	if (bIsCrouched && !IsSliding)
	{
		Slide();

		return;
	}

	Jump();
}

#pragma endregion

#pragma region Overrides

void AWarrior::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	JumpToAnimationNode(JumpToJumpUpNodeName);
}

void AWarrior::OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal,
	const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta)
{
	Super::OnWalkingOffLedge_Implementation(
		PreviousFloorImpactNormal,
		PreviousFloorContactNormal,
		PreviousLocation,
		TimeDelta);
	JumpToAnimationNode(JumpToFallNodeName);
}

void AWarrior::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (HasCrouchedInput)
	{
		Super::Crouch();
		GetSprite()->SetRelativeLocation(CrouchedSpriteOffset);
		JumpToAnimationNode(JumpToCrouchingNodeName);
	}
	else if (HasMoveInput)
	{
		JumpToAnimationNode(JumpToRunNodeName);
	}
	else
	{
		JumpToAnimationNode(JumpToLandAnimNodeName);
	}
}

#pragma endregion

#pragma region Boolean Flags

bool AWarrior::IsGrounded() const
{
	return GetCharacterMovement()->IsMovingOnGround();
}

#pragma endregion

#pragma region Wall Check

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

#pragma endregion

#pragma region Jump To Animation Node

void AWarrior::JumpToAnimationNode(const FName JumpToNodeName, const FName JumpToStateMachineName) const
{
	GetAnimationComponent()->GetAnimInstance()->JumpToNode(JumpToNodeName, JumpToStateMachineName);
}

#pragma endregion

#pragma region Public Usages

void AWarrior::OnReceiveNotifyJumpToIdleOrRun()
{
	IsAttacking = false;

	if (ComboAttackIndex >= MaxComboAttackIndex)
	{
		ComboAttackIndex = 0;
	}
	else
	{
		ComboAttackIndex++;
	}

	if (HasMoveInput)
	{
		JumpToAnimationNode(JumpToRunNodeName);
	}
	else
	{
		JumpToAnimationNode(JumpToIdleNodeName);
	}
}

#pragma endregion