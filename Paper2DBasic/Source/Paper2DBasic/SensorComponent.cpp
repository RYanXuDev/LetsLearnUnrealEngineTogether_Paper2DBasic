#include "SensorComponent.h"

#include "CharacterBase.h"
#include "Components/CapsuleComponent.h"

USensorComponent::USensorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USensorComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacterBase>(GetOwner());

	if (Character == nullptr) return;

	CheckParams.AddIgnoredActor(Character);
}

void USensorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool USensorComponent::SightLineCheck(FHitResult& OutHitResult, float SightLineLength, FName ActorTag, ECollisionChannel CheckChannel) const
{
	const FVector RayStart = GetComponentLocation();
	const FVector RayEnd = RayStart + Character->GetActorForwardVector() * SightLineLength;
	const bool Hit = GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		RayStart,
		RayEnd,
		CheckChannel,
		CheckParams);

	if (DrawSightLine)
	{
		const FColor RayColor = Hit ? ResultTrueColor : ResultFalseColor;
		DrawDebugLine(GetWorld(), RayStart, RayEnd, RayColor, false, 0.1f, 0, DefaultRayThickness);
	}

	if (OutHitResult.GetActor() == nullptr)
	{
		return false;
	}

	if (ActorTag != NAME_None && OutHitResult.GetActor()->ActorHasTag(ActorTag))
	{
		return true;
	}
	
	return false;
}

FVector USensorComponent::GetLedgeGrabLocation() const
{
	FHitResult HitResult;
	float CharacterCapsuleHalfHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	FVector WallCornerLocation = FVector::ZeroVector;
	FVector LedgeGrabLocation = FVector::ZeroVector;
	const FVector RayStart = GetComponentLocation() + Character->GetActorForwardVector() * WallCheckSightLineLength;
	const FVector RayEnd = RayStart + FVector::DownVector * CharacterCapsuleHalfHeight * 2;

	WallCornerLocation.X = Character->GetActorLocation().X;
	WallCornerLocation.Y = 0;
	
	bool Hit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		RayStart,
		RayEnd,
		ECC_Visibility,
		CheckParams);
	
	if (HitResult.GetActor() == nullptr)
	{
		return GetComponentLocation();
	}

	if (HitResult.GetActor()->ActorHasTag(WallTag))
	{
		WallCornerLocation.Z = HitResult.Location.Z;

		if (DrawWallCornerLocation)
		{
			const FColor RayColor = Hit ? ResultTrueColor : ResultFalseColor;
			DrawDebugLine(GetWorld(), RayStart, RayEnd, RayColor, false, 3.0f, 0, DefaultRayThickness);
			DrawDebugSphere(GetWorld(), WallCornerLocation, WallCornerCheckRadius, 32, RayColor, false, 3.0f, 0, DefaultRayThickness);
		}
		
		LedgeGrabLocation = WallCornerLocation - FVector(0.0f, 0.0f, CharacterCapsuleHalfHeight + LedgeGrabLocationOffset);
		return LedgeGrabLocation;
	}
	
	return GetComponentLocation();
}

bool USensorComponent::WallBlockSightLine() const
{
	FHitResult HitResult;
	return SightLineCheck(HitResult, WallCheckSightLineLength, WallTag);
}
