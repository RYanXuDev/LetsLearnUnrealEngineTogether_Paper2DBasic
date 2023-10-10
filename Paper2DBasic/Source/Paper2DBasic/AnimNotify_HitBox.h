#pragma once

#include "CoreMinimal.h"
#include "Notifies/PaperZDAnimNotify.h"
#include "AnimNotify_HitBox.generated.h"

UCLASS()
class PAPER2DBASIC_API UAnimNotify_HitBox : public UPaperZDAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance) override;

private:
	UPROPERTY(EditAnywhere, Category=Settings, meta=(AllowPrivateAccess="true"))
	FVector HitBoxHalfExtent = FVector(50.0f);

	UPROPERTY(EditAnywhere, Category=Settings, meta=(AllowPrivateAccess="true"))
	bool DrawDebug = true;
};