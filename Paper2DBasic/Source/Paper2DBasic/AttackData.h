#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackData.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EAttackEffectType : uint8
{
	Normal		UMETA(DisplayName="Normal"),
	KnockBack	UMETA(DisplayName="Knock Back"),
	KnockUp		UMETA(DisplayName="Knock Up"),
	Stun		UMETA(DisplayName="Stun")
};

UCLASS()
class PAPER2DBASIC_API UAttackData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	FORCEINLINE float GetDamage() const { return Damage; }

	FORCEINLINE float GetHitStopDuration() const { return HitStopDuration; }
	
	FORCEINLINE float GetKnockBackForce() const { return KnockBackForce; }
	FORCEINLINE float GetKnockUpForce() const { return KnockUpForce; }

	FORCEINLINE TSubclassOf<UCameraShakeBase> GetHitCameraShake() const { return HitCameraShake; }

	FORCEINLINE TArray<EAttackEffectType> GetAttackEffects() const { return AttackEffects; }

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float HitStopDuration = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float KnockBackForce;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	float KnockUpForce;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<UCameraShakeBase> HitCameraShake;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<EAttackEffectType> AttackEffects;
};