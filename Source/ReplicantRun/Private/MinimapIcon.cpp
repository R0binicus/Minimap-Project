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
