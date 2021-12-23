attribute vec4 vPosition;
attribute vec3 aColor;
attribute vec2 aTexCoord;
varying mediump vec4 vertexColor;
varying highp vec2 TexCoord;
void main()
{
    gl_Position = vPosition;
    vertexColor = vec4(aColor, 1.0);
    TexCoord = aTexCoord;
}