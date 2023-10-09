#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Warrior.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PAPER2DBASIC_API AWarrior : public APaperZDCharacter
{
	GENERATED_BODY()
public:
	AWarrior();

	virtual void Tick(float DeltaSeconds) override;

	void OnReceiveNotifyJumpToIdleOrRun() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Wall Check", meta=(AllowPrivateAccess = "true"))
	FName WallTag =  FName(TEXT("Wall"));
	
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

	bool HasMoveInput;
	bool HasCrouchedInput;
	bool RunAnimationTriggered;

	UPROPERTY(BlueprintReadOnly, Category = "Animation Parameters", meta=(AllowPrivateAccess = "true"))
	bool IsSliding;

	UPROPERTY(EditAnywhere, Category = "Movement|Slide", meta=(AllowPrivateAccess = "true"))
	float SlideDuration = 0.5f;
	
	UPROPERTY(EditAnywhere, Category = "Movement|Crouch", meta=(AllowPrivateAccess = "true"))
	float CrouchedSpriteHeight = 50.0f;

	const FVector DefaultSpriteOffset = FVector(25.0f, 0.0f, 18.0f);
	
	FVector CrouchedSpriteOffset;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move(const float InputActionValue);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StopMoving();

	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;

	void Slide();

	void StopSlide();

	virtual void OnJumped_Implementation() override;

	virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta) override;

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable, Category=Movement)
	void OnJumpInput();
	
	UFUNCTION(BlueprintPure, Category = "Animation Parameters")
	FORCEINLINE bool IsFalling() const { return !IsGrounded() && GetVelocity().Z <= 0.0f; }

	UFUNCTION(BlueprintPure, Category = "Animation Parameters")
	bool IsGrounded() const;

	bool IsWallAbove() const;

	void JumpToAnimationNode(const FName JumpToNodeName, const FName JumpToStateMachineName = NAME_None) const;
};