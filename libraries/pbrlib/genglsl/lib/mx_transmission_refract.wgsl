#include "mx_microfacet_specular.glsl"

vec3 mx_surface_transmission(vec3 N, vec3 V, vec3 X, vec2 alpha, int distribution, FresnelData fd, vec3 tint)
{
    // Approximate the appearance of surface transmission as glossy
    // environment map refraction, ignoring any scene geometry that might
    // be visible through the surface.
    fd.refraction = true;
    // Issue#2570 Minor adjustment made to support WGSL requirement that uniforms cannot be boolean
    if ($refractionTwoSided == 1)
    {
        tint = mx_square(tint);
    }
    return mx_environment_radiance(N, V, X, alpha, distribution, fd) * tint;
}
