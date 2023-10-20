#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "CharacterBase.generated.h"

class UVisualEffectsComponent;
class UAttackComponent;
class UAttackData;
class UPaperZDAnimSequence;
class UNiagaraComponent;
class UNiagaraSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttackHit, ACharacterBase*, CharacterHit, const UAttackData*, AttackData);

UCLASS()
class PAPER2DBASIC_API ACharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	ACharacterBase();

	FAttackHit AttackHit;

	FORCEINLINE UPaperZDAnimSequence* GetHurtAnimSequence() const { return HurtAnimSequence; }
	
	void StartHitStop(const float InHitStopDuration);

	void EndHitStop();

	void SetMaterial(UMaterialInstance* InMaterialInstance) const;

	void StartSpriteShake(const float InShakeDuration);

	void EndSpriteShake() const;
	
	void ApplyForce(const FVector& InVelocity) const;
	
	void PlayHurtAnimationOverride() const;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category="Components", meta=(AllowPrivateAccess="true"))
	UAttackComponent* AttackComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UVisualEffectsComponent* VisualEffectsComponent;
	
	bool HasSuperArmor;

	UPROPERTY(EditDefaultsOnly, Category=Animations, meta=(AllowPrivateAccess="true"))
	UPaperZDAnimSequence* HurtAnimSequence;

	UPROPERTY(EditAnywhere, Category="Attacks|Hit", meta=(AllowPrivateAccess="true"))
	UMaterialInstance* HitMaterialInstance;

	UPROPERTY()
	UMaterialInstance* DefaultMaterialInstance;
};