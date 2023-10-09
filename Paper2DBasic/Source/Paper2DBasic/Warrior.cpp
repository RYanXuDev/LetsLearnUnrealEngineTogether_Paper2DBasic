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

void AWarrior::BeginPlay()
{
	Super::BeginPlay();

	CrouchedSpriteOffset = FVector(DefaultSpriteOffset.X, DefaultSpriteOffset.Y, CrouchedSpriteHeight);
}

void AWarrior::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsSliding)
	{
		AddMovementInput(GetActorForwardVector());
	}
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
	
	AddMovementInput(FVector::ForwardVector, InputActionValue);

	if (!RunAnimationTriggered)
	{
		JumpToAnimationNode(JumpToRunNodeName);
		RunAnimationTriggered = true;
	}
}

void AWarrior::StopMoving()
{
	HasMoveInput = false;
	RunAnimationTriggered = false;

	if (IsGrounded())
	{
		JumpToAnimationNode(JumpToIdleNodeName);
	}
}

void AWarrior::Crouch(bool bClientSimulation)
{
	HasCrouchedInput = true;
	Super::Crouch(bClientSimulation);
	GetSprite()->SetRelativeLocation(CrouchedSpriteOffset);
}

void AWarrior::UnCrouch(bool bClientSimulation)
{
	HasCrouchedInput = false;
	
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
	JumpToAnimationNode(JumpToSlideNodeName);

	FTimerHandle SlideTimerHandle;
	GetWorldTimerManager().SetTimer(SlideTimerHandle, this, &AWarrior::StopSlide, SlideDuration);
}

void AWarrior::StopSlide()
{
	IsSliding = false;

	if (HasCrouchedInput)
	{
		JumpToAnimationNode(JumpToCrouchingNodeName);
		
		return;
	}
		
	UnCrouch();
}

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

void AWarrior::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	JumpToAnimationNode(JumpToCrouchNodeName);
}

void AWarrior::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (HasMoveInput)
	{
		JumpToAnimationNode(JumpToRunNodeName);
	}
	else
	{
		JumpToAnimationNode(JumpToLandAnimNodeName);
	}
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
}

bool AWarrior::IsGrounded() const
{
	return GetCharacterMovement()->IsMovingOnGround();
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

void AWarrior::JumpToAnimationNode(const FName JumpToNodeName, const FName JumpToStateMachineName) const
{
	GetAnimationComponent()->GetAnimInstance()->JumpToNode(JumpToNodeName, JumpToStateMachineName);
}

void AWarrior::OnReceiveNotifyJumpToIdleOrRun() const
{
	if (HasMoveInput)
	{
		JumpToAnimationNode(JumpToRunNodeName);
	}
	else
	{
		JumpToAnimationNode(JumpToIdleNodeName);
	}
}