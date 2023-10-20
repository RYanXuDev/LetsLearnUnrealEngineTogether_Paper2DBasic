#include "AttackComponent.h"

#include "AttackData.h"
#include "CharacterBase.h"

void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacterBase>(GetOwner());

	if (Character == nullptr) return;

	Character->AttackHit.AddDynamic(this, &UAttackComponent::OnAttackHit);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UAttackComponent::OnAttackHit(ACharacterBase* CharacterHit, const UAttackData* AttackData)
{
	Character->StartHitStop(AttackData->GetHitStopDuration());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(AttackData->GetHitCameraShake());
	
	TriggerAttackEffects(AttackData, CharacterHit);

	CharacterHit->StartHitStop(AttackData->GetHitStopDuration());
	CharacterHit->StartSpriteShake(AttackData->GetHitStopDuration());
	CharacterHit->PlayHurtAnimationOverride();
}

void UAttackComponent::TriggerAttackEffects(const UAttackData* AttackData, ACharacterBase* CharacterHit) const
{
	for (const auto AttackEffect : AttackData->GetAttackEffects())
	{
		switch (AttackEffect)
		{
		case EAttackEffectType::Normal:
			break;
			
		case EAttackEffectType::KnockBack:
			CharacterHit->ApplyForce(Character->GetActorForwardVector() * AttackData->GetKnockBackForce());
			break;
			
		case EAttackEffectType::KnockUp:
			CharacterHit->ApplyForce(CharacterHit->GetActorUpVector() * AttackData->GetKnockUpForce());
			break;
			
		case EAttackEffectType::Stun:
			break;
			
		default: ;
		}	
	}
}
