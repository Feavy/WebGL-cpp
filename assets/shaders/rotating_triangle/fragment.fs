precision mediump float;

varying vec4 pos;
uniform vec4 color;

void main()
{       
    gl_FragColor = pos + vec4(0.5, 0.5, 0.5, 0.5); 
}