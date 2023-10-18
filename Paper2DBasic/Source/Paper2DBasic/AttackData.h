#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackData.generated.h"

UCLASS()
class PAPER2DBASIC_API UAttackData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	FORCEINLINE float GetDamage() const { return Damage; }

	FORCEINLINE float GetHitStopDuration() const { return HitStopDuration; }

	FORCEINLINE TSubclassOf<UCameraShakeBase> GetHitCameraShake() const { return HitCameraShake; }

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage", meta=(AllowPrivateAccess="true"))
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Hit Stop", meta=(AllowPrivateAccess="true"))
	float HitStopDuration = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Hit", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UCameraShakeBase> HitCameraShake;
};