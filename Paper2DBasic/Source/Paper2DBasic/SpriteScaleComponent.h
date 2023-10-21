#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpriteScaleComponent.generated.h"

class ACharacterBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PAPER2DBASIC_API USpriteScaleComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	USpriteScaleComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void JumpSqueeze();

	void LandSquash();
	
protected:
	
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	ACharacterBase* Character;

	FVector DefaultSpriteScale;

	FVector TargetSpriteScale;

	UPROPERTY(EditAnywhere, Category="Jump Squeeze", meta=(AllowPrivateAccess="true"))
	FVector JumpSqueezeScaleMultiplier = FVector(0.8f, 1.0f, 1.25f);
	
	UPROPERTY(EditAnywhere, Category="Land Squash", meta=(AllowPrivateAccess="true"))
	FVector LandSquashScaleMultiplier = FVector(1.25f, 1.0f, 0.5f);
	
	UPROPERTY(EditAnywhere, Category="Curve", meta=(AllowPrivateAccess="true"))
	UCurveFloat* Curve;

	float CurveStartTime;

	float CurveMaxTime;

	bool ShouldScale;

	void ScaleSprite();
	
	void Initialize(const FVector& ScaleMultiplier);
};