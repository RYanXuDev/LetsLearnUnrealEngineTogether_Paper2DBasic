#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SensorComponent.generated.h"

class ACharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAPER2DBASIC_API USensorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	

	USensorComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	bool WallBlockSightLine() const;

	bool SightLineCheck(FHitResult& OutHitResult, float SightLineLength = 1000.0f, FName ActorTag = NAME_None, ECollisionChannel CheckChannel = ECC_Visibility) const;

	FVector GetLedgeGrabLocation() const;

protected:
	
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	ACharacterBase* Character;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall Check", meta=(AllowPrivateAccess = "true"))
	float WallCheckSightLineLength = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ledge Grab", meta=(AllowPrivateAccess = "true"))
	float LedgeGrabLocationOffset = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wall Check", meta=(AllowPrivateAccess = "true"))
	FName WallTag =  FName(TEXT("Wall"));
	
	UPROPERTY(EditAnywhere, Category="Debug Settings", meta=(AllowPrivateAccess="true"))
	bool DrawSightLine = true;

	UPROPERTY(EditAnywhere, Category="Debug Settings", meta=(AllowPrivateAccess="true"))
	bool DrawWallCornerLocation = true;

	UPROPERTY(EditAnywhere, Category="Debug Settings", meta=(AllowPrivateAccess="true"))
	float WallCornerCheckRadius = 10.0f;

	UPROPERTY(EditAnywhere, Category="Debug Settings", meta=(AllowPrivateAccess="true"))
	float DefaultRayThickness = 1.0f;

	UPROPERTY(EditAnywhere, Category="Debug Settings", meta=(AllowPrivateAccess="true"))
	FColor ResultTrueColor = FColor::Green;
	
	UPROPERTY(EditAnywhere, Category="Debug Settings", meta=(AllowPrivateAccess="true"))
	FColor ResultFalseColor = FColor::Red;
	
	FCollisionQueryParams CheckParams;
};