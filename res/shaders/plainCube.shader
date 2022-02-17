#shader vertex
#version 330 core

layout (location = 0) in vec3 v_pos;

out vec2 r_col;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(v_pos, 1.0);
    r_col = vec2(v_pos.xy);
}

#shader fragment
#version 330 core

out vec4 v_color;

in vec2 r_col;

void main()
{
    v_color = vec4(r_col.x + 0.5,r_col.y + 0.5, 1.0, 1.0);
}