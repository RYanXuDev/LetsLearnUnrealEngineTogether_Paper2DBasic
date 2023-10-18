#include "CharacterBase.h"

#include "AttackData.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterBase::ACharacterBase()
{
	GetSprite()->SetCastShadow(true);
	
	GetCapsuleComponent()->CanCharacterStepUpOn = ECB_No;

	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	GetCharacterMovement()->bConstrainToPlane = true;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	DefaultMaterialInstance = Cast<UMaterialInstance>(GetSprite()->GetMaterial(0));
	
	AttackHit.AddDynamic(this, &ACharacterBase::OnAttackHit);
}

UNiagaraComponent* ACharacterBase::SpawnVfx(UNiagaraSystem* Template, const FName SocketName) const
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(
		Template,
		GetSprite(),
		SocketName,
		FVector::Zero(),
		FRotator(0.0f, 0.0f, 0.0f),
		EAttachLocation::SnapToTarget,
		false,
		true,
		ENCPoolMethod::ManualRelease);
}

void ACharacterBase::SpawnChargeVfx(UNiagaraSystem* Template)
{
	ChargeVfxToPool = SpawnVfx(Template, FName(TEXT("ChargeLocation")));
}

void ACharacterBase::PoolChargeVfx() const
{
	ChargeVfxToPool->ReleaseToPool();
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

void ACharacterBase::StartSpriteShake(UMaterialInstance* ShakeMaterialInstance, const float InShakeDuration)
{
	SetMaterial(ShakeMaterialInstance);

	FTimerHandle HitStopTimerHandle;
	GetWorldTimerManager().SetTimer(HitStopTimerHandle, this, &ACharacterBase::EndSpriteShake, InShakeDuration);
}

void ACharacterBase::EndSpriteShake() const
{
	SetMaterial(DefaultMaterialInstance);
}

void ACharacterBase::OnAttackHit(ACharacterBase* CharacterHit, const UAttackData* AttackData)
{
	StartHitStop(AttackData->GetHitStopDuration());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(AttackData->GetHitCameraShake());
	CharacterHit->StartHitStop(AttackData->GetHitStopDuration());
	CharacterHit->StartSpriteShake(HitMaterialInstance, AttackData->GetHitStopDuration());
	
	if (CharacterHit->GetAnimInstance() == nullptr || CharacterHit->HurtAnimSequence == nullptr) return;
		
	CharacterHit->GetAnimInstance()->PlayAnimationOverride(CharacterHit->HurtAnimSequence);
}