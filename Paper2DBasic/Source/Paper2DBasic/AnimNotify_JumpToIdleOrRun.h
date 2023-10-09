#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotify.h"
#include "AnimNotify_JumpToIdleOrRun.generated.h"

UCLASS()
class PAPER2DBASIC_API UAnimNotify_JumpToIdleOrRun : public UPaperZDAnimNotify
{
	GENERATED_BODY()

	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) override;
};