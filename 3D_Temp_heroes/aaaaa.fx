//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// NormalMapping
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string NormalMapping_Pass_0_Model : ModelData = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4x4 gWorldMatrix : World;
float4x4 gWorldViewProjectionMatrix : WorldViewProjection;

float4 gWorldCameraPosition : ViewPosition;

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
   float3 vPos : TEXCOORD1;
   float3 mViewDir: TEXCOORD2;
   float3 T : TEXCOORD3;
   float3 B : TEXCOORD4;
   float3 N : TEXCOORD5;
};

VS_OUTPUT NormalMapping_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.vPos = mul( Input.mPosition, gWorldMatrix );
   Output.mPosition = mul( Input.mPosition, gWorldViewProjectionMatrix );
   Output.mUV = Input.mUV;
   
   float3 viewDir = normalize(Output.vPos - gWorldCameraPosition.xyz);
   Output.mViewDir = viewDir;
   
   float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix );
   Output.N = normalize(worldNormal);
   
   float3 worldTangent = mul(Input.mTangent, (float3x3)gWorldMatrix );
   Output.T = normalize(worldTangent);
   
   float3 worldBinormal = mul(Input.mBinormal, (float3x3)gWorldMatrix );
   Output.B = normalize(worldBinormal);
   
   return Output;
}





float3 gLightPos1
<
   string UIName = "gLightPos1";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 100.00, 100.00, 100.00 );
int gLightNum
<
   string UIName = "gLightNum";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   int UIMin = -100;
   int UIMax = 100;
> = int( 1 );

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
   int i = 0;
   
   float4 albedo = tex2D(DiffuseSampler, Input.mUV);
   
   if(i != gLightNum)
   {
      ++i;
      lightDir = Input.vPos - gLightPos1;
      distSq = dot(lightDir, lightDir);
      lightDir = normalize(lightDir) * gLightNum;
      
      tempDiffuse = saturate(dot(worldNormal, -lightDir));
      diffuse += albedo.rgb * tempDiffuse;
      
      if ( tempDiffuse.x > 0 )
      {
         reflection = reflect(lightDir, worldNormal);
         specular += pow(saturate(dot(reflection, -viewDir )), 20.0f);
      }
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

