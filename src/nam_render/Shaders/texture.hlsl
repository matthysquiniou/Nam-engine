#define MAX_LIGHTS 64
#define MAX_TEXTURES 512
#define DIRECTIONNAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2

float3 reflect(float3 v, float3 n)
{
    return v - 2.0 * dot(v, n) * n;
}

float average(float3 v)
{
    return (v.x + v.y + v.z) / 3.f;
}

struct Light
{
    uint type;
    float3 color;

    float3 direction;
    uint id;
    
    float3 position;
    float pad2;
    
    float range;
    float beginAngleRad;
    float endAngleRad;
    float intensity;

};

cbuffer cbPerObject : register(b0)
{
	float4x4 gWorld;
    float4x4 invGWorld;
    int hasTexture;
};

cbuffer cbViewProj : register(b1)
{
    float4x4 view;
    float4x4 proj;
    float3 cameraPos;
    float time;

    float deltaTime;
};

cbuffer cbLight : register(b2)
{
    Light lights[MAX_LIGHTS];
    
    float3 ambientColor;
    uint lightsCount;
}

Texture2D gTexture : register(t0);
SamplerState gSampler : register(s0);

struct VertexIn
{
	float3 PosL  : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORDS;
    float3 NormalL : NORMAL;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORDS;
    float3 NormalH : NORMAL;
    float3 WorldPos : POSITION;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
    
    float4 worldPos = mul(float4(vin.PosL, 1), gWorld);
    vout.WorldPos = worldPos.xyz;

    vout.PosH = mul(worldPos, mul(view, proj));

    vout.Color = vin.Color;

    vout.UV = vin.UV;

    // Transform normal to world space
    vout.NormalH = normalize(mul(vin.NormalL, (float3x3) invGWorld));
   
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    float3 pixNormal = normalize(pin.NormalH);
    float3 pixToView = normalize(cameraPos - pin.WorldPos);
    
    float3 accumulatedLights = float3(0, 0, 0);
   
    float3 albedo = pin.Color.rgb;
  
    if(hasTexture == 1)
    {
        albedo *= gTexture.Sample(gSampler, pin.UV).rgb;
    }

    for (int i = 0; i < lightsCount; i++)
    {
        float3 lightColor = lights[i].color * lights[i].intensity;
        float3 lightDir = float3(0, 0, 0);
        
        if (lights[i].type == DIRECTIONNAL_LIGHT)
        {
            lightDir = normalize(-lights[i].direction);
        }
        else if (lights[i].type == POINT_LIGHT)
        {
            lightDir = normalize(lights[i].position - pin.WorldPos);
            
            float distance = length(lights[i].position - pin.WorldPos);
            
            float attenuation = saturate(1.0 - distance / lights[i].range);
            lightColor *= attenuation;
        }
        else if (lights[i].type == SPOT_LIGHT)
        {
            lightDir = normalize(lights[i].position - pin.WorldPos);
        
            float theta = dot(lightDir, normalize(-lights[i].direction));
            float diff = lights[i].beginAngleRad - lights[i].endAngleRad;
            float intensity = saturate((theta - lights[i].endAngleRad) / diff);

            float distance = length(lights[i].position - pin.WorldPos);
            
            float attenuation = saturate(1.0 - distance / lights[i].range);
            lightColor *= attenuation * intensity;
        }
        
        float diffIntensity = max(dot(pixNormal, lightDir), 0.0f);
        float3 diffuse = lightColor * diffIntensity;
        
        float3 ambient = average(ambientColor) * lightColor;
        
        accumulatedLights += albedo * diffuse + ambient;
    }
    
    float3 finalColor = accumulatedLights * albedo.rgb;
    
    return float4(finalColor, 1.0f);
}


