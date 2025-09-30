#include "MinimapIcon.h"

void UMinimapIcon::SetIconImage(UMaterialInstanceDynamic* NewImageMat)
{
	if (!NewImageMat)
	{
		return;
	}

	if (!NewImageMat)
	{
		return;
	}
	
	IconImage->SetBrushFromMaterial(NewImageMat);
}

bool UMinimapIcon::GetIconDisabled()
{
	return bIconDisabled;
}

void UMinimapIcon::SetIconDisabled(bool bDisabled)
{
	bIconDisabled = bDisabled;
	if (bIconDisabled)
	{

	}
	else
	{

	}
}
