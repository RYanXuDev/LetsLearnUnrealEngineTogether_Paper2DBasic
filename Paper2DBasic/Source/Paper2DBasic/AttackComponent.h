#pragma once

#include "CoreMinimal.h"
#include "AttackData.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

class ACharacterBase;
class UAttackData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAPER2DBASIC_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	ACharacterBase* Character;

	UFUNCTION()
	void OnAttackHit(ACharacterBase* CharacterHit, const UAttackData* AttackData);

	void TriggerAttackEffects(const UAttackData* AttackData, ACharacterBase* CharacterHit) const;
};