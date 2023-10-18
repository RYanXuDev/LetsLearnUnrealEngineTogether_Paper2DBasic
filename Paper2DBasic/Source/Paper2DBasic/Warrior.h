#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Warrior.generated.h"

class UCameraComponent;
class UComboComponent;
class USpringArmComponent;

UCLASS()
class PAPER2DBASIC_API AWarrior : public ACharacterBase
{
	GENERATED_BODY()
public:
	AWarrior();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category=Actions)
	void ResetAction();

protected:
	
	virtual void BeginPlay() override;

private:
	
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, Category=Components, meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category=Components, meta=(AllowPrivateAccess="true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	UComboComponent* ComboComponent;

#pragma endregion

#pragma region Jump To Animation Nodes

	void JumpToAnimationNode(const FName JumpToNodeName, FName JumpToStateMachineName = NAME_None) const;

	UPROPERTY(EditDefaultsOnly, Category = "Animations|State Machine Name", meta=(AllowPrivateAccess = "true"))
	FName LocomotionStateMachineName = FName(TEXT("Locomotion"));
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|State Machine Name", meta=(AllowPrivateAccess = "true"))
	FName ComboStateMachineName = FName(TEXT("Combo"));

	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToAttackAnimNodeName = FName("JumpToAttack");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToChargeAttackAnimNodeName = FName("JumpToChargeAttack");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToChargeAttackReleaseAnimNodeName = FName("JumpToChargeAttackRelease");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToLandAnimNodeName = FName("JumpToLand");

	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToJumpUpNodeName = FName("JumpToJumpUp");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToFallNodeName = FName("JumpToFall");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToCrouchNodeName = FName("JumpToCrouch");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToCrouchingNodeName = FName("JumpToCrouching");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToRunNodeName = FName("JumpToRun");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToIdleNodeName = FName("JumpToIdle");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToSlideNodeName = FName("JumpToSlide");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToStopSlidingNodeName = FName("JumpToStopSliding");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToStopDashingNodeName = FName("JumpToStopDashing");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animations|Jump Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToWallSlideNodeName = FName("JumpToWallSlide");

#pragma endregion

#pragma region Boolean Flags
	
	bool IsAttacking;
	bool IsCharging;
	bool IsDashing;
	bool IsSliding;
	bool IsWallSliding;
	bool HasMoveInput;
	bool HasCrouchedInput;
	bool RunAnimationTriggered;
		
	UFUNCTION(BlueprintPure, Category = "Animation Parameters")
	FORCEINLINE bool IsFalling() const { return !IsGrounded() && GetVelocity().Z <= 0.0f; }

	UFUNCTION(BlueprintPure, Category = "Animation Parameters")
	bool IsGrounded() const;

#pragma endregion

#pragma region Properties

	UPROPERTY(EditAnywhere, Category = "Actions|Default Settings", meta=(AllowPrivateAccess = "true"))
	float DefaultGravityScale = 4.0f;
	
	UPROPERTY(EditAnywhere, Category = "Actions|Slide", meta=(AllowPrivateAccess = "true"))
	float SlideDuration = 0.5f;
	
	UPROPERTY(EditAnywhere, Category = "Actions|Crouch", meta=(AllowPrivateAccess = "true"))
	float CrouchedSpriteHeight = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Actions|Dash", meta=(AllowPrivateAccess = "true"))
	float DashSpeed = 8000.0f;
	
	UPROPERTY(EditAnywhere, Category = "Actions|Wall Slide", meta=(AllowPrivateAccess = "true"))
	float WallSlideGravityScale = 0.1f;
	
	UPROPERTY(EditAnywhere, Category = "Actions|Wall Slide", meta=(AllowPrivateAccess = "true"))
	float WallSlideTolerance = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Actions|Wall Jump", meta=(AllowPrivateAccess = "true"))
	FVector WallJumpVelocity = FVector(600.0f, 0.0f, 1000.0f);

	const FVector DefaultSpriteOffset = FVector(25.0f, 0.0f, 18.0f);
	
	FVector CrouchedSpriteOffset;

#pragma endregion

#pragma region Actions

	UFUNCTION(BlueprintCallable, Category=Actions)
	void LightAttack();
	
	UFUNCTION(BlueprintCallable, Category=Actions)
	void HeavyAttack();

	UFUNCTION(BlueprintCallable, Category=Actions)
	void ChargeAttack();

	UFUNCTION(BlueprintCallable, Category=Actions)
	void ReleaseChargeAttack();
	
	UFUNCTION(BlueprintCallable, Category=Actions)
	void Move(const float InputActionValue);

	UFUNCTION(BlueprintCallable, Category=Actions)
	void StopMoving();

	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;

	void Slide();

	void StopSliding();
	
	UFUNCTION(BlueprintCallable, Category=Actions)
	void OnJumpInput();

	UFUNCTION(BlueprintCallable, Category=Actions)
	void Dash();

	UFUNCTION(BlueprintCallable, Category=Actions)
	void StopDashing();

	UFUNCTION(BlueprintCallable, Category=Actions)
	void OnEnterLocomotion();

	void WallSlide();

	void WallJump();

#pragma endregion

#pragma region Overrides
	
	virtual void OnJumped_Implementation() override;

	virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta) override;

	virtual void Landed(const FHitResult& Hit) override;

#pragma endregion
	
#pragma region Wall Check
	
	UPROPERTY(BlueprintReadOnly, Category = "Wall Check", meta=(AllowPrivateAccess = "true"))
	FName WallTag =  FName(TEXT("Wall"));
	
	bool IsWallAbove() const;
	
	bool WallSlideCheck() const;

#pragma endregion

#pragma region Others

	
	
#pragma endregion
};