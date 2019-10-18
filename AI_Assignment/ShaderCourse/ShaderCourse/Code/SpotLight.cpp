#include "SpotLight.h"
#include "Material.h"

void SpotLight::UploadToMaterial(const Material& TargetMaterial)
{
	TargetMaterial.Use();
	TargetMaterial.Set("u_SpotLight.Position", Position);
	TargetMaterial.Set("u_SpotLight.Direction", Direction);
	TargetMaterial.Set("u_SpotLight.Color", Color);
	TargetMaterial.Set("u_SpotLight.Length", Length);
	TargetMaterial.Set("u_SpotLight.Angle", Angle);
}
