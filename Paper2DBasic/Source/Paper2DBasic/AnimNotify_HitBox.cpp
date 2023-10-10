#include "AnimNotify_HitBox.h"

void UAnimNotify_HitBox::OnReceiveNotify_Implementation(UPaperZDAnimInstance* OwningInstance)
{
	Super::OnReceiveNotify_Implementation(OwningInstance);

	if (OwningInstance == nullptr) return;

	if (OwningInstance->GetOwningActor() == nullptr) return;

	TArray<FOverlapResult> Results;
	const FCollisionShape Shape = FCollisionShape::MakeBox(HitBoxHalfExtent);
	const FVector Center = SequenceRenderComponent->GetSocketLocation(FName(TEXT("HitBox")));
	FCollisionQueryParams Params;
	
	Params.AddIgnoredActor(OwningInstance->GetOwningActor());

	if (DrawDebug)
	{
		DrawDebugBox(
			GetWorld(),
			Center,
			HitBoxHalfExtent,
			FColor::Red,
			false,
			0.5f,
			0,
			0.0f);
	}
	
	GetWorld()->OverlapMultiByChannel(
		Results,
		Center,
		SequenceRenderComponent->GetComponentRotation().Quaternion(),
		ECC_Pawn,
		Shape,
		Params);
	
	for (FOverlapResult Result : Results)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, *Result.GetActor()->GetActorNameOrLabel());
	}
}