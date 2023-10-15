#include "ComboComponent.h"

void UComboComponent::ComboCheck(const EComboInput InComboInput)
{
	if (!ComboTags.HasTag(ComboTag))
	{
		ComboTags.AddTag(ComboStartTag);
		NextComboInput = InComboInput;

		return;
	}

	if (ComboTags.HasTag(ComboInputWindowOpenTag))
	{
		NextComboInput = InComboInput;
	}
}

void UComboComponent::OnComboStart()
{
	ComboTags.AddTag(ComboInputWindowOpenTag);
	ComboTags.RemoveTag(ComboStartTag);
}

void UComboComponent::OnInterCombo()
{
	ConsumeInput();
}

void UComboComponent::OnLastCombo()
{
	ConsumeInput();
	ComboTags.RemoveTag(ComboInputWindowOpenTag);
}

void UComboComponent::OnComboFinished()
{
	ClearComboTags();
}

void UComboComponent::OnComboAnimSequenceFinished() const
{
	if (NextComboInput == EComboInput::NoValue && ComboTags.HasTag(ComboTag))
	{
		ComboFinishedEvent.Broadcast();
	}
}

void UComboComponent::ConsumeInput()
{
	ComboTags.AddTag(ComboOnGoingTag);
	NextComboInput = EComboInput::NoValue;
}

void UComboComponent::ClearComboTags()
{
	ComboTags.RemoveTag(ComboOnGoingTag);
	ComboTags.RemoveTag(ComboInputWindowOpenTag);
}