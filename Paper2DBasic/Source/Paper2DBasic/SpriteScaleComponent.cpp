#include "SpriteScaleComponent.h"

#include "CharacterBase.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/KismetMathLibrary.h"

USpriteScaleComponent::USpriteScaleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	if (Curve != nullptr) return;

	const TCHAR* CurvePath = TEXT("/Script/Engine.CurveFloat'/Game/Data/Curves/CF_SpriteScale.CF_SpriteScale'");
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFinder(CurvePath);

	if (CurveFinder.Succeeded())
	{
		Curve = CurveFinder.Object;
	}
}

void USpriteScaleComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Curve == nullptr) return;

	float CurveMinTime;
	Curve->GetTimeRange(CurveMinTime, CurveMaxTime);

	Character = Cast<ACharacterBase>(GetOwner());

	if (Character == nullptr) return;
 
	DefaultSpriteScale = Character->GetSprite()->GetRelativeScale3D();
}

void USpriteScaleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ShouldScale) return;
		
	ScaleSprite();
}

void USpriteScaleComponent::ScaleSprite()
{
	const float ElapsedTime = GetWorld()->GetWorld()->GetTimeSeconds() - CurveStartTime;

	if (ElapsedTime > CurveMaxTime)
	{
		ShouldScale = false;
	}
	
	const float CurveValue = Curve->GetFloatValue(ElapsedTime);
	const FVector NewScale = UKismetMathLibrary::VLerp(DefaultSpriteScale, TargetSpriteScale, CurveValue);
	Character->GetSprite()->SetRelativeScale3D(NewScale);
}

void USpriteScaleComponent::Initialize(const FVector& ScaleMultiplier)
{
	ShouldScale = true;
	CurveStartTime = GetWorld()->GetTimeSeconds();
	TargetSpriteScale = DefaultSpriteScale * ScaleMultiplier;
}

void USpriteScaleComponent::JumpSqueeze()
{
	Initialize(JumpSqueezeScaleMultiplier);
}

void USpriteScaleComponent::LandSquash()
{
	Initialize(LandSquashScaleMultiplier);
}
