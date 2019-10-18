#version 330 core
#define MAX_POINT_LIGHTS 2

struct DirectionalLight
{
	vec3 Direction;
	vec3 Color;
	sampler2D ShadowBuffer;
	mat4 ViewProjection;
};

struct PointLight
{
	vec3 Position;
	vec3 Color;
	float Radius;
};

struct SpotLight
{
	vec3 Position;
	vec3 Direction;
	vec3 Color;
	float Length;
	float Angle;
};

uniform sampler2D u_MainTexture;

uniform float u_Time;
uniform vec3 u_EyePosition;
uniform DirectionalLight u_DirLight;
uniform PointLight u_PointLights[MAX_POINT_LIGHTS];
uniform SpotLight u_SpotLight;

in vec3 f_World;
in vec3 f_Normal;
in vec2 f_TexCoord;
in float f_CameraDepth;
out vec4 o_Color;

const vec3 AmbientColor = vec3(0.6, 0.7, 1.0);
const float SpecExponent = 11.0;
const float SpecIntensity = 0.24;
const float ShadowBias = 0.001;

const float AttenuationExponent = 2.0;
const float AttenuationConstant = 1.0;
const float AttenuationLinear = 0.02;
const float AttenuationQuadratic = 0.01;

const float SpotLightFalloff = radians(2.f);

const float FogDistance = 80.0;
const float FogMinDistance = 20.0;
const vec3 FogColor = vec3(0.75, 0.8, 1.0);

vec3 CalculateDirLightColor(DirectionalLight Light, vec3 Albedo)
{
	// Calculate light
	// Diffuse Lighting
	vec3 Diffuse = Albedo * Light.Color * max(-dot(Light.Direction, f_Normal), 0.0);

	// Specular highlighting
	// Blinn-phong model
	vec3 WorldToEye = normalize(u_EyePosition - f_World);
	vec3 HalfwayVector = normalize(WorldToEye - Light.Direction);
	float SpecularValue = max(dot(HalfwayVector, f_Normal), 0.0);
	SpecularValue = pow(SpecularValue, SpecExponent) * SpecIntensity;

	vec3 Specular = Light.Color * SpecularValue;

	// Shadows baby
	vec4 LightNDC = Light.ViewProjection * vec4(f_World, 1.0);

	// Everything is shifted in the light buffer from [-1, 1] to [0, 1].
	// Because its a texture :)
	LightNDC = LightNDC * 0.5 + 0.5;
	float LightDepth = texture(Light.ShadowBuffer, LightNDC.xy).x;
	float OurDepth = LightNDC.z;
	float Shadow = step(OurDepth, LightDepth + ShadowBias);

	Diffuse *= Shadow;
	Specular *= Shadow;

	return Diffuse + Specular;
}

vec3 CalculatePointLightColor(PointLight Light, vec3 Albedo)
{
	vec3 LightDirection = normalize(f_World - Light.Position);

	float Distance = length(f_World - Light.Position);
	// Polynomial attenuation!
	//float Attenuation = 1.0 / (Distance * Distance * AttenuationQuadratic + Distance * AttenuationLinear + AttenuationConstant);

	// Exponential attenuation!
	float Attenuation = max(1.0 - (Distance / Light.Radius), 0.0);
	Attenuation = pow(Attenuation, AttenuationExponent);

	// Diffuse lighting bejbii
	vec3 Diffuse = Albedo * Light.Color * Attenuation * max(-dot(LightDirection, f_Normal), 0.0);

	// Specular highlighting
	vec3 WorldToEye = normalize(u_EyePosition - f_World);
	vec3 HalfVector = normalize(WorldToEye - LightDirection);
	float SpecularValue = max(dot(HalfVector, f_Normal), 0.0);
	SpecularValue = pow(SpecularValue, SpecExponent) * SpecIntensity;

	vec3 Specular = Light.Color * Attenuation * SpecularValue;

	return Diffuse + Specular;
}

vec3 CalculateSpotLightColor(SpotLight Light, vec3 Albedo)
{
	vec3 LightDirection = normalize(f_World - Light.Position);

	float Distance = length(f_World - Light.Position);
	// Polynomial attenuation!
	//float Attenuation = 1.0 / (Distance * Distance * AttenuationQuadratic + Distance * AttenuationLinear + AttenuationConstant);

	// Exponential attenuation!
	float Attenuation = max(1.0 - (Distance / Light.Length), 0.0);
	Attenuation = pow(Attenuation, AttenuationExponent);

	// Diffuse lighting bejbii
	vec3 Diffuse = Albedo * Light.Color * Attenuation * max(-dot(LightDirection, f_Normal), 0.0);

	// Specular highlighting
	vec3 WorldToEye = normalize(u_EyePosition - f_World);
	vec3 HalfVector = normalize(WorldToEye - LightDirection);
	float SpecularValue = max(dot(HalfVector, f_Normal), 0.0);
	SpecularValue = pow(SpecularValue, SpecExponent) * SpecIntensity;

	vec3 Specular = Light.Color * Attenuation * SpecularValue;

	// Angle cutoff
	float CosAngle = dot(LightDirection, Light.Direction);
	float Angle = acos(CosAngle);
	float Cutoff = 1.0 - smoothstep(Light.Angle - SpotLightFalloff, Light.Angle, Angle);
	//float Cutoff = smoothstep(Light.Angle, Light.Angle - SpotLightFalloff, Angle);

	return (Diffuse + Specular) * Cutoff;
}

void main()
{
	vec3 Albedo = texture(u_MainTexture, f_TexCoord).xyz;

	// Ambient light
	vec3 Ambient = AmbientColor * Albedo * 0.2;

	// Apply light sources!
	o_Color = vec4(0.0, 0.0, 0.0, 1.0);
	o_Color.xyz += CalculateDirLightColor(u_DirLight, Albedo);
	for(int i=0; i<MAX_POINT_LIGHTS; ++i)
	{
		o_Color.xyz += CalculatePointLightColor(u_PointLights[i], Albedo);
	}
	o_Color.xyz += CalculateSpotLightColor(u_SpotLight, Albedo);
	o_Color.xyz += Ambient;

	// Apply fog to the lit pixel
	float FogIntensity = clamp((f_CameraDepth - FogMinDistance) / FogDistance, 0.0, 1.0);
	FogIntensity = pow(FogIntensity, 0.75);
	o_Color.xyz = mix(o_Color.xyz, FogColor, FogIntensity);

	//o_Color.xyz = CalculatePointLightColor(u_PointLight, Albedo);
}