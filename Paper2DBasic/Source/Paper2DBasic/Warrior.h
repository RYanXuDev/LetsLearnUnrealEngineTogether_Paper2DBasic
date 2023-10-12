#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Warrior.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PAPER2DBASIC_API AWarrior : public ACharacterBase
{
	GENERATED_BODY()
public:
	AWarrior();

	virtual void Tick(float DeltaSeconds) override;

	void OnReceiveNotifyJumpToIdleOrRun();

protected:
	virtual void BeginPlay() override;

private:
	
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

#pragma endregion

#pragma region Jump To Animation Nodes

	void JumpToAnimationNode(const FName JumpToNodeName, const FName JumpToStateMachineName = NAME_None) const;

	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToAttackAnimNodeName = FName("JumpToAttack");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToChargeAttackAnimNodeName = FName("JumpToChargeAttack");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToChargeAttackReleaseAnimNodeName = FName("JumpToChargeAttackRelease");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToLandAnimNodeName = FName("JumpToLand");

	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToJumpUpNodeName = FName("JumpToJumpUp");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToFallNodeName = FName("JumpToFall");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToCrouchNodeName = FName("JumpToCrouch");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToCrouchingNodeName = FName("JumpToCrouching");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToRunNodeName = FName("JumpToRun");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToIdleNodeName = FName("JumpToIdle");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToSlideNodeName = FName("JumpToSlide");
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation Node Name", meta=(AllowPrivateAccess = "true"))
	FName JumpToStopSlidingNodeName = FName("JumpToStopSliding");

#pragma endregion

#pragma region Boolean Flags

	bool IsAttacking;
	bool IsCharging;
	bool IsSliding;
	bool HasMoveInput;
	bool HasCrouchedInput;
	bool RunAnimationTriggered;
		
	UFUNCTION(BlueprintPure, Category = "Animation Parameters")
	FORCEINLINE bool IsFalling() const { return !IsGrounded() && GetVelocity().Z <= 0.0f; }

	UFUNCTION(BlueprintPure, Category = "Animation Parameters")
	bool IsGrounded() const;

#pragma endregion

#pragma region Properties

	const int32 MaxComboAttackIndex = 2;

	UPROPERTY(BlueprintReadOnly, Category="Animation Parameters", meta=(AllowPrivateAccess="true"))
	int32 ComboAttackIndex = 0;
	
	UPROPERTY(EditAnywhere, Category = "Movement|Slide", meta=(AllowPrivateAccess = "true"))
	float SlideDuration = 0.5f;
	
	UPROPERTY(EditAnywhere, Category = "Movement|Crouch", meta=(AllowPrivateAccess = "true"))
	float CrouchedSpriteHeight = 50.0f;

	const FVector DefaultSpriteOffset = FVector(25.0f, 0.0f, 18.0f);
	
	FVector CrouchedSpriteOffset;

#pragma endregion

#pragma region Action Functions

	UFUNCTION(BlueprintCallable, Category=Actions)
	void Attack();

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

#pragma endregion
};