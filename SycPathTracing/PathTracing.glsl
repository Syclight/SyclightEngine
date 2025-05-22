#version 430
layout(local_size_x = 16, local_size_y = 16) in;
layout(rgba32f, binding = 0) uniform image2D outputImage;

struct Ray {
    vec3 origin;
    vec3 direction;
};

struct Sphere {
    vec3 center;
    float radius;
    int materialIdx;
};

struct Material {
    vec3 albedo;
    float roughness;
    float metallic;
};

struct Light {
    vec3 position;
    vec3 intensity;
};

layout(std430, binding = 1) buffer SphereBuffer { Sphere spheres[]; };
layout(std430, binding = 2) buffer MaterialBuffer { Material materials[]; };
layout(std430, binding = 3) buffer LightBuffer { Light lights[]; };

uniform vec3 cameraPos;
uniform vec3 cameraLookAt;
uniform float cameraFov;
uniform int width;
uniform int height;

float rand(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

bool intersectSphere(Ray ray, Sphere sphere, out float t) {
    vec3 oc = ray.origin - sphere.center;
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(oc, ray.direction);
    float c = dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4.0 * a * c;
    if (discriminant < 0.0) return false;
    t = (-b - sqrt(discriminant)) / (2.0 * a);
    return t > 0.0;
}

vec3 tracePath(Ray ray, int depth) {
    if (depth >= 5) return vec3(0.0); // 最大深度

    float tMin = 1e10;
    int hitIdx = -1;
    for (int i = 0; i < spheres.length(); i++) {
        float t;
        if (intersectSphere(ray, spheres[i], t) && t < tMin) {
            tMin = t;
            hitIdx = i;
        }
    }

    if (hitIdx == -1) return vec3(0.1, 0.1, 0.2); // 背景颜色

    vec3 hitPoint = ray.origin + ray.direction * tMin;
    vec3 normal = normalize(hitPoint - spheres[hitIdx].center);
    Material mat = materials[spheres[hitIdx].materialIdx];

    vec3 color = vec3(0.0);
    for (int i = 0; i < lights.length(); i++) {
        vec3 lightDir = normalize(lights[i].position - hitPoint);
        color += mat.albedo * lights[i].intensity * max(0.0, dot(normal, lightDir));
    }

    // 简单漫反射（后续可扩展为递归追踪）
    return color;
}

void main() {
    ivec2 pixel = ivec2(gl_GlobalInvocationID.xy);
    if (pixel.x >= width || pixel.y >= height) return;

    // 生成初始光线
    vec2 uv = vec2(pixel) / vec2(width, height) * 2.0 - 1.0;
    float aspect = float(width) / float(height);
    float tanFov = tan(radians(cameraFov) * 0.5);
    vec3 dir = normalize(cameraLookAt - cameraPos);
    vec3 right = normalize(cross(dir, vec3(0, 1, 0)));
    vec3 up = cross(right, dir);
    vec3 rayDir = normalize(dir + right * uv.x * tanFov * aspect + up * uv.y * tanFov);

    Ray ray = Ray(cameraPos, rayDir);
    vec3 color = tracePath(ray, 0);

    imageStore(outputImage, pixel, vec4(color, 1.0));
}
