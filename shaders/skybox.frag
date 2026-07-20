varying mediump vec2    texCoord;
uniform sampler2D uni_texture;

void main(void)
{
    gl_FragColor = texture2D(uni_texture,vec2(texCoord.x,texCoord.y));

}
