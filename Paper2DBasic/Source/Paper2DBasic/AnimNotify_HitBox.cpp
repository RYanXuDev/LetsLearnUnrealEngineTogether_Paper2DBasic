#include "AnimNotify_HitBox.h"

#include "CharacterBase.h"

void UAnimNotify_HitBox::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if (OwningInstance == nullptr) return;

	if (OwningInstance->GetOwningActor() == nullptr) return;

	const ACharacterBase* Character = Cast<ACharacterBase>(OwningInstance->GetOwningActor());
	
	if (Character == nullptr) return;

	const FCollisionShape Shape = FCollisionShape::MakeBox(HitBoxHalfExtent);
	const FVector Center = SequenceRenderComponent->GetSocketLocation(FName(TEXT("HitBox")));

	if (DrawDebug)
	{
		DrawDebugBox(GetWorld(), Center, HitBoxHalfExtent, HitBoxColor, false, DebugLifeTime, 0, 0.0f);
	}
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);
	
	if (TArray<FOverlapResult> OverlapResults;
		GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Center,
		SequenceRenderComponent->GetComponentRotation().Quaternion(),
		ECC_Pawn,
		Shape,
		Params))
	{
		for (FOverlapResult OverlapResult : OverlapResults)
		{
			if (OverlapResult.GetActor() == nullptr) continue;

			if (ACharacterBase* CharacterHit = Cast<ACharacterBase>(OverlapResult.GetActor()); CharacterHit != nullptr)
			{
				Character->AttackHit.Broadcast(CharacterHit);

				if (PrintMessage)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, MessageColor,
						FString::Printf(TEXT("Hit box detected %s"), *CharacterHit->GetActorNameOrLabel()));
				}
			}
		}
	}
}
