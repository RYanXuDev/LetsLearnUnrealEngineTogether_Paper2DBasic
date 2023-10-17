#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "CharacterBase.generated.h"

class UPaperZDAnimSequence;
class UNiagaraComponent;
class UNiagaraSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackHit, ACharacterBase*, CharacterHit);

UCLASS()
class PAPER2DBASIC_API ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	ACharacterBase();

	FAttackHit AttackHit;

	FORCEINLINE UPaperZDAnimSequence* GetHurtAnimSequence() const { return HurtAnimSequence; }

protected:

	UNiagaraComponent* SpawnVfx(UNiagaraSystem* Template, const FName SocketName) const;

	UFUNCTION(BlueprintCallable, Category=VFX)
	void SpawnChargeVfx(UNiagaraSystem* Template);

	UFUNCTION(BlueprintCallable, Category=VFX)
	void PoolChargeVfx() const;

	UPROPERTY(EditDefaultsOnly, Category=Animations, meta=(AllowPrivateAccess="true"));
	UPaperZDAnimSequence* HurtAnimSequence;

private:

	UPROPERTY()
	UNiagaraComponent* ChargeVfxToPool;
};