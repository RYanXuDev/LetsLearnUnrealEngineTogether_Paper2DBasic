#include "Warrior.h"

#include "ComboComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperZDAnimInstance.h"
#include "Components/CapsuleComponent.h"

AWarrior::AWarrior()
{
	JumpMaxHoldTime = 0.3f;
	bUseControllerRotationYaw = false;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 40.0f));
	SpringArmComponent->SetRelativeRotation(FRotator(0.0f, -90.0f,  0.0f));
	SpringArmComponent->TargetArmLength = 900.0f;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 8.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ComboComponent = CreateDefaultSubobject<UComboComponent>(TEXT("Combo Component"));
	
	GetSprite()->SetRelativeLocation(DefaultSpriteOffset);
	GetSprite()->SetRelativeScale3D(FVector(5.0f));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->SetCrouchedHalfHeight(50.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bCanWalkOffLedgesWhenCrouching = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 10000.0f, 0.0f);
	GetCharacterMovement()->GravityScale = DefaultGravityScale;
	GetCharacterMovement()->JumpZVelocity = 800.0f;
	GetCharacterMovement()->AirControl = 0.9f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 600.0f;
	GetCharacterMovement()->LedgeCheckThreshold = 100.0f;
}

#pragma region Life Circle Events

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

	if (IsFalling() && WallSlideCheck())
	{
		WallSlide();
	}
	else
	{
		GetCharacterMovement()->GravityScale = DefaultGravityScale;
		IsWallSliding = false;
	}
}

#pragma endregion

#pragma region Movement Functions

void AWarrior::LightAttack()
{
	if (bIsCrouched) return;
	
	IsAttacking = true;
	ComboComponent->ComboCheck(EComboInput::LightAttack);
}

void AWarrior::HeavyAttack()
{
	if (bIsCrouched) return;
	
	IsAttacking = true;
	ComboComponent->ComboCheck(EComboInput::HeavyAttack);
}

void AWarrior::ChargeAttack()
{
	if (!IsGrounded() || IsAttacking || bIsCrouched) return;

	JumpToAnimationNode(JumpToChargeAttackAnimNodeName);
	IsAttacking = true;
	IsCharging = true;
}

void AWarrior::ReleaseChargeAttack()
{
	if (!IsCharging) return;
		
	JumpToAnimationNode(JumpToChargeAttackReleaseAnimNodeName);
	IsCharging = false;
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

	if (IsAttacking || IsDashing || IsWallSliding) return;
	
	AddMovementInput(FVector::ForwardVector, InputActionValue);

	if (!RunAnimationTriggered && IsGrounded())
	{
		JumpToAnimationNode(JumpToRunNodeName);
		RunAnimationTriggered = true;
		IsAttacking = false;
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
		if (IsFalling()) return;
		
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
	if (IsWallSliding)
	{
		WallJump();

		return;
	}
	
	if (IsAttacking || !IsGrounded() || IsDashing) return;
		
	if (bIsCrouched && !IsSliding)
	{
		Slide();

		return;
	}

	Jump();
}

void AWarrior::Dash()
{
	if (IsAttacking || IsDashing || bIsCrouched || !IsGrounded()) return;
	
	IsDashing = true;
	GetCharacterMovement()->bCanWalkOffLedges = false;
	GetCharacterMovement()->AddImpulse(GetActorForwardVector() * DashSpeed + GetActorUpVector() * -1.0f * DefaultGravityScale, true);
	ComboComponent->ComboCheck(EComboInput::Dash);
}

void AWarrior::StopDashing()
{
	IsDashing = false;
	GetCharacterMovement()->bCanWalkOffLedges = true;
}

void AWarrior::OnEnterLocomotion()
{
	if (IsDashing)
	{
		JumpToAnimationNode(JumpToStopDashingNodeName);
	}
	else
	{
		ResetAction();
	}
}

void AWarrior::WallSlide()
{
	if (IsWallSliding) return;

	IsWallSliding = true;
	
	JumpToAnimationNode(JumpToWallSlideNodeName);
	GetCharacterMovement()->Velocity = FVector::ZeroVector;
	GetCharacterMovement()->GravityScale = WallSlideGravityScale;
}

void AWarrior::WallJump()
{
	JumpToAnimationNode(JumpToJumpUpNodeName);
	
	const FVector HorizontalVelocity = GetActorForwardVector() * -1.0f * WallJumpVelocity.X;
	const FVector VerticalVelocity = GetActorUpVector() * WallJumpVelocity.Z;
	const FVector NewVelocity = HorizontalVelocity + VerticalVelocity;
	LaunchCharacter(NewVelocity, true, true);

	SetActorRotation((GetActorForwardVector() * -1.0).Rotation());
}

bool AWarrior::WallSlideCheck() const
{
	FHitResult HitResult;
	const FCollisionShape CheckShape = FCollisionShape::MakeCapsule(
		GetCapsuleComponent()->GetScaledCapsuleRadius() + WallSlideTolerance,
		GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this);
	GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation(),
		GetActorRotation().Quaternion(),
		ECC_Visibility,
		CheckShape,
		Params);

	if (HitResult.GetActor() == nullptr) return false;
	
	return HitResult.GetActor()->ActorHasTag(WallTag) && HitResult.bBlockingHit;
}

#pragma endregion

#pragma region Overrides

void AWarrior::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	JumpToAnimationNode(JumpToJumpUpNodeName);
	IsAttacking = false;
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
		IsAttacking = false;
	}
	else
	{
		JumpToAnimationNode(JumpToLandAnimNodeName);
		IsAttacking = false;
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

void AWarrior::JumpToAnimationNode(const FName JumpToNodeName, FName JumpToStateMachineName) const
{
	if (JumpToStateMachineName == NAME_None)
	{
		JumpToStateMachineName = LocomotionStateMachineName;
	}
	
	GetAnimationComponent()->GetAnimInstance()->JumpToNode(JumpToNodeName, JumpToStateMachineName);
}

#pragma endregion

#pragma region Public Usages

void AWarrior::ResetAction()
{
	IsAttacking = false;
	IsDashing = false;

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

#pragma region Others

#pragma endregion