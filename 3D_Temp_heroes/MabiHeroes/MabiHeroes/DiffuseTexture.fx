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

float4x4 gmatWorld : World;
float4x4 gmatViewProjection : ViewProjection;

float3	garrLightPos[4];
int	nLightNum;

struct VS_INPUT 
{
   float4 v4Position : POSITION;
   float3 v3Normal : NORMAL;
   float2 v2UV : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 v4Position : POSITION;
   float2 v2UV : TEXCOORD0;
   float3 v3Diffuse : TEXCOORD1;
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
   
   Output.v2UV = Input.v2UV;
   Output.v4Position = mul(Input.v4Position, gmatWorld);
   float3 v3Normal = mul(Input.v3Normal, (float3x3)gmatWorld);
   v3Normal = normalize(v3Normal);
   
  float3 diffuse = 0;
   float3 lightDir;
   float  dist;

   for (int i = 0; i < nLightNum; ++i)
   {
      lightDir = Input.v4Position.xyz - garrLightPos[i];
      dist = length(lightDir);
      lightDir /= dist;
      
      diffuse += saturate(dot(v3Normal, -lightDir)) * 30 / dist;
   }

 Output.v3Diffuse = diffuse;


   Output.v4Position = mul(Output.v4Position, gmatViewProjection);

   
   return( Output );
   
}


struct PS_INPUT
{
   float2 v2UV : TEXCOORD0;
   float3 v3Diffuse : TEXCOORD1;
};

texture DiffuseMap_Tex
<
   string ResourceName = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Fieldstone.tga";
>;
sampler2D DiffuseSampler = sampler_state
{
   Texture = (DiffuseMap_Tex);
};   

float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{
   float4 albedo = tex2D(DiffuseSampler, Input.v2UV);
   float3 diffuse = albedo.rgb * saturate(Input.v3Diffuse);
   float3 ambient = float3(0.2f, 0.2f, 0.2f) * albedo;
   
   return( float4(diffuse + ambient, 1.0f ) );
   
}




//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_3_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_3_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}


