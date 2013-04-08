uniform mat4 u_mvp;
attribute vec2 a_vertex;
attribute vec3 a_color;

varying vec3 v_color;

void main()
{
    v_color = a_color;
    gl_Position = u_mvp * vec4(a_vertex, 0.0, 1.0);
}

