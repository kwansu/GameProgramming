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
// Default_DirectX_Effect
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Default_DirectX_Effect_Pass_0_Model : ModelData = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Sphere.3ds";

float4x4 gmatWorldViewProjection : WorldViewProjection;
float4x4 gmatWorld : World;

float4   vLightPosition
<
   string UIName = "vLightPosition";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 500.00, 500.00, -500.00, 1.00 );
float4   vCameraPosition
<
   string UIName = "vCameraPosition";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 0.00, 0.00, 10.00, 1.00 );

struct VS_INPUT 
{
   float4 vPosition : POSITION0;
   float3 vNormal : NORMAL;
   float3 vTangent : TANGENT;
   float3 vBinormal : BINORMAL;
   float2 vUV : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 vPosition : POSITION0;
   float2 vUV : TEXCOORD0;
   float3 vLightDir : TEXCOORD1;
   float3 vViewDir : TEXCOORD2;
   float3 T : TEXCOORD3;
   float3 B : TEXCOORD4;
   float3 N : TEXCOORD5;
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.vPosition = mul( Input.vPosition, gmatWorldViewProjection );
   Output.vUV = Input.vUV;
   
   float4 worldPosition = mul(Input.vPosition, gmatWorld);
   float3 vLightDir = worldPosition.xyz - vLightPosition.xyz;
   Output.vLightDir = normalize(vLightDir);
   
   float3 vViewDir = normalize(Output.vPosition.xyz - vCameraPosition.xyz);
   Output.vViewDir = vViewDir;

   float3 vNormal = mul(Input.vNormal, (float3x3)gmatWorld );
   Output.N = normalize(vNormal);
   
   float3 vTangent = mul(Input.vTangent, (float3x3)gmatWorld );
   Output.T = normalize(vTangent);
   
   float3 vBinormal = mul(Input.vBinormal, (float3x3)gmatWorld );
   Output.B = normalize(vBinormal);
   
   return( Output );
   
}




struct PS_INPUT
{
   float2 vUV : TEXCOORD0;
   float3 vLightDir : TEXCOORD1;
   float3 vViewDir : TEXCOORD2;
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
sampler2D NormalSmapler = sampler_state
{
   Texture = (NormalMap_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
};

float3 vLightColor
<
   string UIName = "vLightColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 0.70, 0.70, 1.00 );

float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{   
   float3 tangentNormal = tex2D(NormalSmapler, Input.vUV).xyz;
   tangentNormal = normalize(tangentNormal * 2 -1);
   
   float3x3 TBN = float3x3(normalize(Input.T),
    normalize(Input.B), normalize(Input.N));
   TBN = transpose(TBN);
   
   float3 worldNormal = mul(TBN, tangentNormal); 
   
   float3 lightDir = normalize(Input.vLightDir);
   float3 diffuse = saturate(dot(worldNormal, -lightDir));
   
   float4 albedo = tex2D(DiffuseSampler, Input.vUV);
   diffuse = vLightColor * albedo.rgb * diffuse;
   
   float3 specular = 0;
   if(diffuse.x > 0)
   {
      float3 reflection = reflect(lightDir, worldNormal);
      float3 viewDir = normalize(Input.vViewDir);
      
      specular = saturate(dot(reflection, - viewDir));
      specular = pow(specular, 20.0f);
      specular = specular * vLightColor;
   }
   
   float ambient = float3(0.1f, 0.1f, 0.1f) * albedo;
   
   return float4(ambient + diffuse + specular, 1);
}




//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}

