#include "VisualEffectsComponent.h"

#include "CharacterBase.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PaperFlipbookComponent.h"

void UVisualEffectsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Character = Cast<ACharacterBase>(GetOwner());
}

UNiagaraComponent* UVisualEffectsComponent::SpawnVfx(UNiagaraSystem* Template, const FName SocketName) const
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(
		Template,
		Character->GetSprite(),
		SocketName,
		FVector::Zero(),
		FRotator(0.0f, 0.0f, 0.0f),
		EAttachLocation::SnapToTarget,
		false,
		true,
		ENCPoolMethod::ManualRelease);
}

void UVisualEffectsComponent::SpawnChargeVfx(UNiagaraSystem* Template)
{
	ChargeVfxToPool = SpawnVfx(Template, FName(TEXT("ChargeLocation")));
}

void UVisualEffectsComponent::PoolChargeVfx() const
{
	ChargeVfxToPool->ReleaseToPool();
}