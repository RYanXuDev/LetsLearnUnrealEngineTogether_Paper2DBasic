#include "AnimNotify_JumpToIdleOrRun.h"

#include "Warrior.h"

void UAnimNotify_JumpToIdleOrRun::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if (OwningInstance == nullptr) return;

	if (OwningInstance->GetOwningActor() == nullptr) return;
	
	if (const AWarrior* Warrior = Cast<AWarrior>(OwningInstance->GetOwningActor()); Warrior != nullptr)
	{
		Warrior->OnReceiveNotifyJumpToIdleOrRun();
	}
}