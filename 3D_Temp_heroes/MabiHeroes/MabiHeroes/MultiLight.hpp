float4x4 gWorldMatrix : World;
float4x4 gViewProjectionMatrix : ViewProjection;

float3 gCameraPos;

struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal: NORMAL;
   float3 mTangent: TANGENT;
   float3 mBinormal: BINORMAL;
   float2 mUV: TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 mPosition : POSITION;
   float2 mUV: TEXCOORD0;
   float4 vPos : TEXCOORD1;
   float3 mViewDir: TEXCOORD2;
   float3 T : TEXCOORD3;
   float3 B : TEXCOORD4;
   float3 N : TEXCOORD5;
};

VS_OUTPUT NormalMapping_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.vPos = mul( Input.mPosition, gWorldMatrix );
   Output.mPosition = mul( Output.vPos, gViewProjectionMatrix );
   Output.mUV = Input.mUV;
   
   float3 viewDir = normalize(Output.vPos - gCameraPos);
   Output.mViewDir = viewDir;
   
   float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix );
   Output.N = normalize(worldNormal);
   
   float3 worldTangent = mul(Input.mTangent, (float3x3)gWorldMatrix );
   Output.T = normalize(worldTangent);
   
   float3 worldBinormal = mul(Input.mBinormal, (float3x3)gWorldMatrix );
   Output.B = normalize(worldBinormal);
   
   return Output;
}


float3	garrLightPos[4];
int		nLightNum;

struct PS_INPUT
{
   float2 mUV : TEXCOORD0;
   float3 vPos : TEXCOORD1;
   float3 mViewDir: TEXCOORD2;
   float3 T : TEXCOORD3;
   float3 B : TEXCOORD4;
   float3 N : TEXCOORD5;
};

texture DiffuseMap_Tex;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};
texture NormalMap_Tex;
sampler2D NormalSampler = sampler_state
{
   Texture = (NormalMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};

float4 NormalMapping_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{
   float3 tangentNormal = tex2D(NormalSampler, Input.mUV).xyz;
   tangentNormal = normalize(tangentNormal * 2 - 1);
   
   float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
   TBN = transpose(TBN);
   float3 worldNormal = mul(TBN, tangentNormal);
   worldNormal = normalize(worldNormal);
   float3 diffuse = 0;
   float3 specular = 0;
   float3 tempDiffuse;
   float3 lightDir;
   float3 reflection;
   float  dist;
   float3 viewDir = normalize(Input.mViewDir);
   
   float4 albedo = tex2D(DiffuseSampler, Input.mUV);
   

   for (int i = 0; i < nLightNum; ++i)
   {
      lightDir = Input.vPos - garrLightPos[i];
      dist = length(lightDir);
      lightDir /= dist;
      
      tempDiffuse = saturate(dot(worldNormal, -lightDir)) * 50 / dist;
      diffuse += albedo.rgb * tempDiffuse;
      
      if(tempDiffuse.x > 0)
      {
         reflection = reflect(lightDir, worldNormal);
         specular += pow(saturate(dot(reflection, -viewDir )), 20.f) * 20 / dist;
      }
   }

   float3 ambient = float3(0.2f, 0.2f, 0.2f) * albedo;
   
   return float4(ambient + diffuse + specular, 1);
}

//--------------------------------------------------------------//
// Technique Section for NormalMapping
//--------------------------------------------------------------//
technique NormalMapping
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 NormalMapping_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_3_0 NormalMapping_Pass_0_Pixel_Shader_ps_main();
   }

}

