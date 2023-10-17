#include "CharacterBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACharacterBase::ACharacterBase()
{
	GetSprite()->SetCastShadow(true);
	
	GetCapsuleComponent()->CanCharacterStepUpOn = ECB_No;

	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
	GetCharacterMovement()->bConstrainToPlane = true;
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