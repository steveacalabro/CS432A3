in vec3 vPosition, vColor;
out vec3 color;

void main()
{
    gl_Position = vec4(vPosition, 1);
    color = vColor;
}
