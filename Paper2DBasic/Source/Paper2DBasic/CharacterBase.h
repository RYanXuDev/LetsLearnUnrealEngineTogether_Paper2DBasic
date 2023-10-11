#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttackHit, ACharacterBase*, CharacterHit);

UCLASS()
class PAPER2DBASIC_API ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	FAttackHit AttackHit;
};