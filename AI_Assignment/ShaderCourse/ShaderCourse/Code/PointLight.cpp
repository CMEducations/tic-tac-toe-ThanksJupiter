#include "PointLight.h"
#include "Material.h"
#include <stdio.h> //printf, sprintf, etc..

void PointLight::UploadToMaterial(int Index, const Material& TargetMaterial)
{
	static char StringBuffer[100];

	sprintf_s(StringBuffer, 100, "u_PointLights[%d].Position", Index);
	TargetMaterial.Set(StringBuffer, Position);

	sprintf_s(StringBuffer, 100, "u_PointLights[%d].Color", Index);
	TargetMaterial.Set(StringBuffer, Color);

	sprintf_s(StringBuffer, 100, "u_PointLights[%d].Radius", Index);
	TargetMaterial.Set(StringBuffer, Radius);
}