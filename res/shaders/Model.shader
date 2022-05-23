#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Norm;
out vec3 FragPos;

uniform mat4 transform;
uniform mat4 model;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    TexCoords = aTexCoords;    
    Norm = aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
}

#shader fragment
#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Norm;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 materialP;

vec3 lightColor = vec3(1.0, 1.0, 1.0);

void main()
{    
    // ambient
    float ambientStrength = materialP.x;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse 
    vec3 norm = normalize(Norm);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = materialP.y;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), int(materialP.z));
    vec3 specular = specularStrength * spec * lightColor;  
        
    FragColor = vec4((ambient + diffuse + specular), 1.0) * texture(texture_diffuse1, TexCoords);
}