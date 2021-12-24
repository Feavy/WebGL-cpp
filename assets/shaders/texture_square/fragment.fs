precision mediump float;
varying mediump vec4 vertexColor;
varying vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{   
    vec4 color = mix(texture2D(texture1, TexCoord), texture2D(texture2, TexCoord), 0.2);
    gl_FragColor = color * vertexColor;
}