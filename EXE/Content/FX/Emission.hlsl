float4x4 wvp; 

texture m_Texture;
sampler s0 = sampler_state
{
	Texture = <m_Texture>;

	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = NONE;

	AddressU = WRAP;
	AddressV = WRAP;
};

struct VSINPUT
{
	float4 Pos   : POSITION;//頂点の座標
	float4 Color : COLOR;//カラー
	float2 Tex   : TEXCOORD0;//UV
};

struct VSOUTPUT//平面用
{
	float4 Pos	  : POSITION;
	float4 Color  : COLOR;
	float2 Tex    : TEXCOORD0;
};

VSOUTPUT VS_Fix_Main(VSINPUT vsin)
{
	VSOUTPUT vsout = (VSOUTPUT)0;

	vsout.Pos   = mul(vsin.Pos, wvp);
	vsout.Color = vsin.Color;
	vsout.Tex   = vsin.Tex;

	return vsout;
}

float4 PS_Main(VSOUTPUT psin) : COLOR
{
	float4 output;

	output = tex2D(s0, psin.Tex);

	return output;
}

technique FixModel
{
	pass Pass0
	{
		VertexShader = compile vs_3_0 VS_Fix_Main();
		PixelShader  = compile ps_3_0 PS_Main();
	}
}
