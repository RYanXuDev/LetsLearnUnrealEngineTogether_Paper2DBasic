#include "CharacterBase.h"

#include "AttackComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "VisualEffectsComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterBase::ACharacterBase()
{
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(TEXT("Attack Component"));

	VisualEffectsComponent = CreateDefaultSubobject<UVisualEffectsComponent>(TEXT("VFX Component"));
	
	GetSprite()->SetCastShadow(true);
	
	GetCapsuleComponent()->CanCharacterStepUpOn = ECB_No;

	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	GetCharacterMovement()->bConstrainToPlane = true;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	DefaultMaterialInstance = Cast<UMaterialInstance>(GetSprite()->GetMaterial(0));
}

void ACharacterBase::StartHitStop(const float InHitStopDuration)
{
	CustomTimeDilation = 0.0f;

	FTimerHandle HitStopTimerHandle;
	GetWorldTimerManager().SetTimer(HitStopTimerHandle, this, &ACharacterBase::EndHitStop, InHitStopDuration);
}

void ACharacterBase::EndHitStop()
{
	CustomTimeDilation = 1.0f;
}

void ACharacterBase::SetMaterial(UMaterialInstance* InMaterialInstance) const
{
	if (InMaterialInstance == nullptr) return;
		
	GetSprite()->SetMaterial(0, InMaterialInstance);
}

void ACharacterBase::StartSpriteShake(const float InShakeDuration)
{
	SetMaterial(HitMaterialInstance);

	FTimerHandle HitStopTimerHandle;
	GetWorldTimerManager().SetTimer(HitStopTimerHandle, this, &ACharacterBase::EndSpriteShake, InShakeDuration);
}

void ACharacterBase::EndSpriteShake() const
{
	SetMaterial(DefaultMaterialInstance);
}

void ACharacterBase::ApplyForce(const FVector& InVelocity) const
{
	GetCharacterMovement()->AddImpulse(InVelocity, true);
}

void ACharacterBase::PlayHurtAnimationOverride() const
{
	if (GetAnimInstance() == nullptr || HurtAnimSequence == nullptr || HasSuperArmor) return;
		
	GetAnimInstance()->PlayAnimationOverride(HurtAnimSequence);
}
