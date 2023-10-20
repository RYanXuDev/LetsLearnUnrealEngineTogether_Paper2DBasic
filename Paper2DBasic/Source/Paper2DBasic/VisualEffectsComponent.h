#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VisualEffectsComponent.generated.h"

class ACharacterBase;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PAPER2DBASIC_API UVisualEffectsComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	ACharacterBase* Character;
	
	UPROPERTY()
	UNiagaraComponent* ChargeVfxToPool;
	
	UNiagaraComponent* SpawnVfx(UNiagaraSystem* Template, const FName SocketName) const;

	UFUNCTION(BlueprintCallable, Category=VFX)
	void SpawnChargeVfx(UNiagaraSystem* Template);

	UFUNCTION(BlueprintCallable, Category=VFX)
	void PoolChargeVfx() const;
};