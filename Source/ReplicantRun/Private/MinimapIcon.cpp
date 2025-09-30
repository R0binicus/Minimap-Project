#include "MinimapIcon.h"

void UMinimapIcon::SetIconImage(UTexture2D* NewImage)
{
	if (!NewImage)
	{
		return;
	}

	if (!IconImage)
	{
		return;
	}
	
	IconImage->SetBrushFromTexture(NewImage);
}
