uniform float u_glowRatioX; // Ratio of the inner box relative to the padded width
uniform float u_glowRatioY; // Ratio of the inner box relative to the padded height
uniform vec4 u_glowColor;   // Color vector

void main()
{
    // Fetch normalized coordinates directly (0.0 to 1.0)
    vec2 uv = gl_TexCoord[0].xy;

    // Convert (0.0 to 1.0) space into a clean (-1.0 to 1.0) coordinate space centered at (0,0)
    vec2 normPos = abs(uv - vec2(0.5)) * 2.0;

    // Find out how far outside the inner threshold boundary this pixel sits
    vec2 edgeDist = (normPos - vec2(u_glowRatioX, u_glowRatioY)) / (vec2(1.0) - vec2(u_glowRatioX, u_glowRatioY));
    float outsideDistance = length(max(edgeDist, vec2(0.0)));

    // Calculate a smooth falloff towards the outermost transparent border
    float alphaFactor = 1.0 - outsideDistance;
    alphaFactor = clamp(alphaFactor, 0.0, 1.0);
    alphaFactor = pow(alphaFactor, 2.0); // Curve smoothing

    // If inside the inner bounds, draw a solid color tint (or semi-transparent) 
    // to instantly confirm the shader is working correctly
    if (normPos.x <= u_glowRatioX && normPos.y <= u_glowRatioY) {
        gl_FragColor = vec4(0.1, 0.1, 0.1, 1.0); // Solid dark center fill
    } else {
        gl_FragColor = vec4(u_glowColor.rgb, u_glowColor.a * alphaFactor);
    }
}
