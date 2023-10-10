#include "DefaultPlayerController.h"

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const FInputModeGameOnly GameOnlyInputMode;
	
	SetInputMode(GameOnlyInputMode);
}