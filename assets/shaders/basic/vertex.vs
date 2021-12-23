attribute vec4 vPosition;
attribute vec3 aColor;
varying mediump vec4 vertexColor;
void main()
{
    gl_Position = vPosition;
    vertexColor = vec4(aColor, 1.0);
}