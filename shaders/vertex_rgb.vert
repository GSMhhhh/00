attribute highp vec4 attr_position;
attribute mediump vec2 attr_uv;
uniform mat4   uni_mat;
varying mediump vec2  texCoord;

void main(void)
{
    texCoord = attr_uv;
    gl_Position = uni_mat * attr_position;
}
