#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "CharacterBase.generated.h"

class UAttackData;
class UPaperZDAnimSequence;
class UNiagaraComponent;
class UNiagaraSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttackHit, ACharacterBase*, CharacterHit, const UAttackData*, AttackData);

UCLASS()
class PAPER2DBASIC_API ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	ACharacterBase();

	FAttackHit AttackHit;

	FORCEINLINE UPaperZDAnimSequence* GetHurtAnimSequence() const { return HurtAnimSequence; }

protected:

	virtual void BeginPlay() override;

	UNiagaraComponent* SpawnVfx(UNiagaraSystem* Template, const FName SocketName) const;

	UFUNCTION(BlueprintCallable, Category=VFX)
	void SpawnChargeVfx(UNiagaraSystem* Template);

	UFUNCTION(BlueprintCallable, Category=VFX)
	void PoolChargeVfx() const;

private:

	UPROPERTY()
	UNiagaraComponent* ChargeVfxToPool;

	UPROPERTY(EditDefaultsOnly, Category=Animations, meta=(AllowPrivateAccess="true"))
	UPaperZDAnimSequence* HurtAnimSequence;

	UPROPERTY(EditAnywhere, Category="Attacks|Hit", meta=(AllowPrivateAccess="true"))
	UMaterialInstance* HitMaterialInstance;

	UPROPERTY()
	UMaterialInstance* DefaultMaterialInstance;

	void StartHitStop(const float InHitStopDuration);

	void EndHitStop();

	void SetMaterial(UMaterialInstance* InMaterialInstance) const;

	void StartSpriteShake(UMaterialInstance* ShakeMaterialInstance, const float InShakeDuration);

	void EndSpriteShake() const;
	
	UFUNCTION()
	void OnAttackHit(ACharacterBase* CharacterHit, const UAttackData* AttackData);
};