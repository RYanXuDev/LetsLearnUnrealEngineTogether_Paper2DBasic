#include "AnimNotify_JumpToIdleOrRun.h"

#include "Warrior.h"

void UAnimNotify_JumpToIdleOrRun::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if (const AWarrior* Warrior = Cast<AWarrior>(OwningInstance->GetOwningActor()); Warrior != nullptr)
	{
		Warrior->OnReceiveNotifyJumpToIdleOrRun();
	}
}