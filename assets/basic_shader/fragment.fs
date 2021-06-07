precision mediump float;
varying mediump vec4 vertexColor;
uniform vec4 ourColor;
void main()
{       
    gl_FragColor = vertexColor; 
}