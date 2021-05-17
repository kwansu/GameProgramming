
string NormalMapping_Pass_0_Model : ModelData = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

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





float3* garrLightPos;
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

texture DiffuseMap_Tex
<
   string ResourceName = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Fieldstone.tga";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};
texture NormalMap_Tex
<
   string ResourceName = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\FieldstoneBumpDOT3.tga";
>;
sampler2D NormalSampler = sampler_state
{
   Texture = (NormalMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};

float3 gLightColor;

float4 NormalMapping_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{
   float3 tangentNormal = tex2D(NormalSampler, Input.mUV).xyz;
   tangentNormal = normalize(tangentNormal * 2 - 1);
   
   float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
   TBN = transpose(TBN);
   float3 worldNormal = mul(TBN, tangentNormal);
   float3 diffuse = 0;
   float3 specular = 0;
   float3 tempDiffuse;
   float3 lightDir;
   float3 reflection;
   float  distSq;
   float3 viewDir = normalize(Input.mViewDir);
   
   float4 albedo = tex2D(DiffuseSampler, Input.mUV);
   
   for(int i = 0; i < nLightNum; ++i)
   {
      lightDir = Input.vPos - garrLightPos[i];
      distSq = dot(lightDir, lightDir);
      lightDir = normalize(lightDir);
      
      tempDiffuse = saturate(dot(worldNormal, -lightDir)) / distSq * 10000;
      diffuse += albedo.rgb * tempDiffuse;
      
      //if(tempDiffuse.x > 0)
      //{
      //   reflection = reflect(lightDir, worldNormal);
      //   specular = saturate(dot(reflection, -viewDir ));
      //   specular = pow(specular, 20.0f);
      //}
   }

   float3 ambient = float3(0.1f, 0.1f, 0.1f) * albedo;
   
   return float4(ambient + diffuse + specular, 1);
}

//--------------------------------------------------------------//
// Technique Section for NormalMapping
//--------------------------------------------------------------//
technique NormalMapping
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 NormalMapping_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 NormalMapping_Pass_0_Pixel_Shader_ps_main();
   }

}

