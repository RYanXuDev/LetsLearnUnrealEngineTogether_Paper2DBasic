#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ComboComponent.generated.h"

UENUM(BlueprintType)
enum class EComboInput : uint8
{
	NoValue		UMETA(DISPLAYNAME = "No Value"),
	LightAttack	UMETA(DISPLAYNAME = "Light Attack"),
	HeavyAttack UMETA(DISPLAYNAME = "Heavy Attack")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FComboFinishedEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAPER2DBASIC_API UComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category=AttackCombos)
	void ComboCheck(EComboInput InComboInput);

private:
	
	UPROPERTY(BlueprintAssignable, Category=AttackCombos)
	FComboFinishedEvent ComboFinishedEvent;
	
	EComboInput NextComboInput = EComboInput::NoValue;

	FGameplayTagContainer ComboTags;

	UPROPERTY(EditDefaultsOnly, Category=ComboTags, meta=(AllowPrivateAccess="true"))
	FGameplayTag ComboTag = FGameplayTag::RequestGameplayTag(FName(TEXT("Combo")));
	
	UPROPERTY(EditDefaultsOnly, Category=ComboTags, meta=(AllowPrivateAccess="true"))
	FGameplayTag ComboStartTag = FGameplayTag::RequestGameplayTag(FName(TEXT("Combo.Start")));
	
	UPROPERTY(EditDefaultsOnly, Category=ComboTags, meta=(AllowPrivateAccess="true"))
	FGameplayTag ComboOnGoingTag = FGameplayTag::RequestGameplayTag(FName(TEXT("Combo.OnGoing")));
	
	UPROPERTY(EditDefaultsOnly, Category=ComboTags, meta=(AllowPrivateAccess="true"))
	FGameplayTag ComboInputWindowOpenTag = FGameplayTag::RequestGameplayTag(FName(TEXT("Combo.InputWindowOpen")));

	UFUNCTION(BlueprintCallable, Category=AttackCombos)
	void OnComboStart();

	UFUNCTION(BlueprintCallable, Category=AttackCombos)
	void OnInterCombo();

	UFUNCTION(BlueprintCallable, Category=AttackCombos)
	void OnLastCombo();

	UFUNCTION(BlueprintCallable, Category=AttackCombos)
	void OnComboAnimSequenceFinished() const;

	UFUNCTION(BlueprintCallable, Category=AttackCombos)
	void OnComboFinished();
	
	void ConsumeInput();

	void ClearComboTags();

	UFUNCTION(BlueprintCallable, Category=AnimationParameters)
	FORCEINLINE bool CheckComboTag(const FGameplayTag TagToCompare) const { return ComboTags.HasTag(TagToCompare); }

	UFUNCTION(BlueprintCallable, Category=AnimationParameters)
	FORCEINLINE bool CheckNextComboInput(const EComboInput ComboInputToCompare) const { return NextComboInput == ComboInputToCompare; }
};