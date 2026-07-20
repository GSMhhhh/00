varying mediump vec2    texCoord;
uniform sampler2D uni_texture;

void main(void)
{
//    vec4 texColor = texture2D(uni_texture,vec2(texCoord.x,texCoord.y));
//    if(texColor.a < 0.1)
//        discard;
//     gl_FragColor = texColor；
    gl_FragColor = texture2D(uni_texture,vec2(texCoord.x,texCoord.y));

}
