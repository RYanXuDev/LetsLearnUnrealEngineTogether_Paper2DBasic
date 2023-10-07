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

protected:
	virtual void BeginPlay() override;
	
	bool IsWallAbove() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Wall Check", meta=(AllowPrivateAccess = "true"))
	FName WallTag =  FName(TEXT("Wall"));
	
	UPROPERTY(BlueprintReadOnly, Category = "Animation Parameters", meta=(AllowPrivateAccess = "true"))
	bool IsSliding;

	UPROPERTY(BlueprintReadOnly, Category = "Animation Parameters", meta=(AllowPrivateAccess = "true"))
	bool IsJumping;

	UPROPERTY(EditAnywhere, Category = "Movement|Slide", meta=(AllowPrivateAccess = "true"))
	float SlideDuration = 0.5f;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float MoveInputValue;

	UPROPERTY(EditAnywhere, Category = "Movement|Crouch", meta=(AllowPrivateAccess = "true"))
	float CrouchedSpriteHeight = 50.0f;

	const FVector DefaultSpriteOffset = FVector(25.0f, 0.0f, 18.0f);
	
	FVector CrouchedSpriteOffset;
	
	UFUNCTION(BlueprintPure, Category = "Animation Parameters")
	FORCEINLINE bool IsRunning() const { return IsGrounded() && MoveInputValue != 0.0f; }

	UFUNCTION(BlueprintPure, Category = "Animation Parameters")
	FORCEINLINE bool IsFalling() const { return !IsGrounded() && GetVelocity().Z <= 0.0f; }

	UFUNCTION(BlueprintPure, Category = "Animation Parameters")
	bool IsGrounded() const;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Move(const float InputActionValue);

	virtual void Crouch(bool bClientSimulation = false) override;
	virtual void UnCrouch(bool bClientSimulation = false) override;

	void Slide();
	void StopSlide();

	UFUNCTION(BlueprintCallable, Category=Movement)
	void OnJumpInput();

	UFUNCTION(BlueprintCallable, Category=Movement)
	FORCEINLINE void SetMoveInputValue(const float InValue) { MoveInputValue = InValue; }

	UFUNCTION()
	void OnCharacterLanded(const FHitResult& Hit);
};