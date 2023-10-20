#include "SpriteScaleComponent.h"

#include "CharacterBase.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/KismetMathLibrary.h"

USpriteScaleComponent::USpriteScaleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpriteScaleComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacterBase>(GetOwner());

	if (Character == nullptr) return;
 
	DefaultSpriteScale = Character->GetSprite()->GetRelativeScale3D();
}

void USpriteScaleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ScaleSprite();
}

void USpriteScaleComponent::ScaleSprite() const
{
	const float ElapsedTime = GetWorld()->GetWorld()->GetTimeSeconds() - CurveStartTime;
	const float CurveValue = Curve->GetFloatValue(ElapsedTime);
	const FVector NewScale = UKismetMathLibrary::VLerp(DefaultSpriteScale, TargetSpriteScale, CurveValue);
	Character->GetSprite()->SetRelativeScale3D(NewScale);
}

void USpriteScaleComponent::JumpSqueeze()
{
	CurveStartTime = GetWorld()->GetTimeSeconds();
	TargetSpriteScale = DefaultSpriteScale * JumpSqueezeScaleMultiplier;
}

void USpriteScaleComponent::LandSquash()
{
	CurveStartTime = GetWorld()->GetTimeSeconds();
	TargetSpriteScale = DefaultSpriteScale * LandSquashScaleMultiplier;
}
