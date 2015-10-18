float GetShadowAmount(sampler2D shadowMap, vec3 shadowCoord)
{
	// omni-directional. 4-direction could be okay too
	const vec2 Offsets[] = { vec2(0, 0) }; // vec2(-1, 0), vec2(1, 0), vec2(0, -1), vec2(0, 1), vec2(-1, -1), vec2(-1, 1), vec2(1, -1), vec2(1, 1) };
	const float ShadowDarkness = 0.5; // multiplier of color when the fragment is in shadow

	vec2 uv = shadowCoord.xy; // "uv" == shadow map uv
	if (uv.x <= 0 || uv.x >= 1 || uv.y <= 0 || uv.y >= 1)
	{
		// if the uv is out of bounds (outside [0, 1]), then the area is LIGHTED
		return 1;
	}

	const float Bias = 0.00005;
	float fragmentZ = shadowCoord.z - Bias; // current fragment depth in SHADOW/LIGHT COORDINATES aka distance from shadowmap source

	float totalLight = 0f;
	for (int i = 0; i < Offsets.length(); i++)
	{
		const float OffsetAmount = 0.001;
		float shadowMapZ = texture(shadowMap, shadowCoord.xy + Offsets[i] * OffsetAmount).r; // shadow map's z-value
		totalLight += (shadowMapZ < fragmentZ) ? ShadowDarkness : 1;
	}

	return totalLight / Offsets.length();
}

vec4 ApplyShadow(vec4 color, sampler2D shadowMap, vec3 fragmentShadowCoord) 
{
	return vec4(color.rgb * GetShadowAmount(shadowMap, fragmentShadowCoord), color.a);
}