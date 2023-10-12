#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "CharacterBase.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackHit, ACharacterBase*, CharacterHit);

UCLASS()
class PAPER2DBASIC_API ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	FAttackHit AttackHit;

protected:

	UNiagaraComponent* SpawnVfx(UNiagaraSystem* Template, const FName SocketName) const;

	UFUNCTION(BlueprintCallable, Category=VFX)
	void SpawnChargeVfx(UNiagaraSystem* Template);

	UFUNCTION(BlueprintCallable, Category=VFX)
	void PoolChargeVfx() const;

private:

	UPROPERTY()
	UNiagaraComponent* ChargeVfxToPool;
};