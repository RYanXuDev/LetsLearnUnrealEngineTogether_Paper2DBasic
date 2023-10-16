#include "AnimNotify_ResetAction.h"

#include "Warrior.h"

void UAnimNotify_ResetAction::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if (OwningInstance == nullptr) return;

	if (OwningInstance->GetOwningActor() == nullptr) return;
	
	if (AWarrior* Warrior = Cast<AWarrior>(OwningInstance->GetOwningActor()); Warrior != nullptr)
	{
		Warrior->ResetAction();
	}
}