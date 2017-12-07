#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;  
    float shininess;
}; 

struct Light {
    vec3 position;
    //vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    vec3 grn = vec3(0.0, 1.0, 0.0);
    vec3 basicColor = vec3(1.0, 1.0, 1.0);
    vec3 tex = texture(material.diffuse, TexCoords).rgb;
    // ambient
    vec3 ambient = light.ambient * basicColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    //vec3 lightDir = normalize(-light.direction);  
    float diff = clamp(dot(norm, lightDir), 0.0, 1.0);
    vec3 diffuse = light.diffuse * diff * basicColor;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * basicColor;  
        
    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
}

