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

bool USensorComponent::AheadLedgeCheck() const
{
	FHitResult HitResult;
	const float OffsetX = Character->GetCapsuleComponent()->GetScaledCapsuleRadius() * 1.5f * Character->GetActorForwardVector().X;
	const float CharacterCapsuleHalfHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	const FVector Offset = FVector(OffsetX, 0, -CharacterCapsuleHalfHeight);
	const FVector RayStart = Character->GetActorLocation() + Offset;
	const FVector RayEnd = RayStart - FVector(0, 0, CharacterCapsuleHalfHeight * 2);
	bool AheadLedge = true;

	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		RayStart,
		RayEnd,
		ECC_Visibility,
		CheckParams);

	if (HitResult.bBlockingHit)
	{
		AheadLedge = false;
	}

	if (DrawLedgeCheckRay)
	{
		FColor CheckColor = AheadLedge ? ResultTrueColor : ResultFalseColor;
		DrawDebugLine(GetWorld(), RayStart, RayEnd, CheckColor, false, 3.0f, 0, DefaultRayThickness);
	}

	return AheadLedge;
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

FVector USensorComponent::GetLedgeClimbingDownLocation() const
{
	FHitResult HitResult;
	const float CharacterCapsuleHalfHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	const float CharacterCapsuleRadius = Character->GetCapsuleComponent()->GetScaledCapsuleRadius();
	const float OffsetZ = Character->GetActorLocation().Z - CharacterCapsuleHalfHeight * 2.0f;
	const float OffsetX = Character->GetActorLocation().X + CharacterCapsuleRadius * 2 * Character->GetActorForwardVector().X;
	const FVector RayStart = FVector(OffsetX, 0, OffsetZ);
	const FVector RayEnd = RayStart + FVector(CharacterCapsuleRadius * 3 * Character->GetActorForwardVector().X * -1, 0, 0);
	FVector ClimbingDownLocation = Character->GetActorLocation();
	bool Hit = false;
	
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		RayStart,
		RayEnd,
		ECC_Visibility,
		CheckParams);

	if (HitResult.bBlockingHit && HitResult.GetActor() != nullptr && HitResult.GetActor()->ActorHasTag(WallTag))
	{
		Hit = true;
		ClimbingDownLocation.X = HitResult.Location.X + CharacterCapsuleRadius * Character->GetActorForwardVector().X;
	}

	if (DrawLedgeClimbingDownLocation)
	{
		FColor CheckColor = Hit ? ResultTrueColor : ResultFalseColor;
		DrawDebugLine(GetWorld(), RayStart, RayEnd, CheckColor, false, 3.0f, 0, DefaultRayThickness);
		DrawDebugSphere(GetWorld(), ClimbingDownLocation, 10.0f, 32, CheckColor, false, 3.0f, 0, DefaultRayThickness);
	}

	return ClimbingDownLocation;
}

bool USensorComponent::WallBlockSightLine() const
{
	FHitResult HitResult;
	return SightLineCheck(HitResult, WallCheckSightLineLength, WallTag);
}
