attribute float angle;

uniform float rotation;

varying vec4 pos;

void main()
{

    pos = vec4(cos(angle+rotation) / 1.5, sin(angle+rotation) / 1.5, 0.0, 1.0);
    gl_Position = pos;
}