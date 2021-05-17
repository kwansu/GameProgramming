float4x4 gmatViewProjection : ViewProjection;
float4x4 gmatWorld : World;

float3*	arrLightPos;
float3	vCameraPos;
int		nLightNum;

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
	float4 vPos : TEXCOORD1;
	float3 vViewDir : TEXCOORD2;
	float3 T : TEXCOORD3;
	float3 B : TEXCOORD4;
	float3 N : TEXCOORD5;
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.vUV = Input.vUV;

	Output.vPos = mul(Input.vPosition, gmatWorld);
	Output.vPosition = mul(Output.vPos, gmatViewProjection);

	float3 viewDir = Output.vPos.xyz - vCameraPos;
	Output.vViewDir = normalize(viewDir);

	float3 normal = mul(Input.vNormal, (float3x3)gmatWorld);
	Output.N = normalize(normal);

	float3 vTangent = mul(Input.vTangent, (float3x3)gmatWorld);
	Output.T = normalize(vTangent);

	float3 vBinormal = mul(Input.vBinormal, (float3x3)gmatWorld);
	Output.B = normalize(vBinormal);

	return(Output);
}




struct PS_INPUT
{
	float2 vUV : TEXCOORD0;
	float4 vPos : TEXCOORD1;
	float3 vViewDir : TEXCOORD2;
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
sampler2D NormalSmapler = sampler_state
{
	Texture = (NormalMap_Tex);
MAGFILTER = LINEAR;
MINFILTER = LINEAR;
};


float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{
	float3 tangentNormal = tex2D(NormalSmapler, Input.vUV).xyz;
	tangentNormal = normalize(tangentNormal * 2 - 1);
	
	float3x3 TBN = float3x3(normalize(Input.T),
		normalize(Input.B), normalize(Input.N));
	TBN = transpose(TBN);
	
	float3 worldNormal = mul(TBN, tangentNormal);
	float4 albedo = tex2D(DiffuseSampler, Input.vUV);
	
	float3 diffuse = 0;
	float3 temDiffuse = 0;
	float3 reflection = 0;
	float distSQ = 0;
	float3 specular = 0;
	float3 lightDir = 0;
	float3 viewDir = normalize(Input.vViewDir);

	for (int i = 0; i < nLightNum; ++i)
	{
		lightDir = Input.vPos.xyz - arrLightPos[i];
		distSQ = dot(lightDir, lightDir);
		lightDir = normalize(lightDir);
		temDiffuse = saturate(dot(worldNormal, lightDir)) * albedo.rgb / distSQ;
		diffuse += temDiffuse;

		if (temDiffuse.x > 0)
		{
			reflection = reflect(lighDir, WorldNormal);
			specular += pow(saturate(dot(reflection, -viewDir)), 20.0f);
		}
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

