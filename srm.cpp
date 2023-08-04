#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
#include <string>

using namespace std;

struct Vec3 {
    float x, y, z;
    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
    Vec3 operator/(float s) const { return Vec3(x / s, y / s, z / s); }
    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 cross(const Vec3& v) const { return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
    Vec3 normalize() const { return *this / std::sqrt(dot(*this)); }
};

float sdf(const Vec3& p) {
    // Simple sphere SDF to find nearest point on the sphere
    //Euclidean norm
    return p.dot(p) - 1.0f; 
}

Vec3 rayMarch(const Vec3& rayOrigin, const Vec3& rayDirection, const Vec3& color, float density) {

    const float maxDistance = 100.0f;
    const float minDistance = 1e-4f;
    const int maxSteps = 256;
    float totalDistance = 0.0f;

    Vec3 currentPosition = rayOrigin;

    for (int i = 0; i < maxSteps; ++i) {
        float distance = sdf(currentPosition);

        if (density < 1e-4f) {
            //the transmittance of the ray drops below a threshol
            return Vec3(0.0f, 0.0f, 0.0f);
        }
        if (distance < minDistance) {
            // Hit the sphere, return input color
            return color;
        }

        totalDistance += distance;
        if (totalDistance >= maxDistance) {
            // Nothing found, return black color
            return Vec3(0.0f, 0.0f, 0.0f);
        }

        currentPosition = rayOrigin + rayDirection * totalDistance;
    }

    // Max steps reached, return black color
    return Vec3(0.0f, 0.0f, 0.0f);
}

int main() {
    
    /* Vec3 rayOrigin(0.0f, 0.0f, -5.0f);
     Vec3 rayDirection(0.0f, 0.0f, 1.0f);
     Vec3 color(1.0f, 0.0f, 0.0f);
     float density = 0.5f;
     Vec3 resultColor = rayMarch(rayOrigin, rayDirection.normalize(), color, density);
     std::cout << "Result color: (" << resultColor.x << ", " << resultColor.y << ", " << resultColor.z << ")\n";
     */

    // example test case 
    vector<Vec3> rayOrigin = {
        Vec3(0.0f, 0.0f, -5.0f),
        Vec3(1.0f, 0.0f, -5.0f),
        Vec3(0.0f, 1.0f, -5.0f),
        Vec3(0.0f, 0.0f, -2.0f)
    };
    vector<Vec3> rayDirection = {
        Vec3(0.0f, 0.0f, 1.0f),
        Vec3(-0.2f, 0.0f, 1.0f),
        Vec3(0.0f, -0.2f, 1.0f),
        Vec3(0.0f, 0.0f, 1.0f)
    };
    vector<Vec3> color = {
        Vec3(1.0f, 0.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 0.0f, 1.0f),
        Vec3(1.0f, 1.0f, 0.0f)
    };
    vector<float> density = { 0.5f, 0.25f, 0.75f, 1.0f };
    for (size_t i = 0; i < rayOrigin.size(); ++i) {
        Vec3 resultColor = rayMarch(rayOrigin[i], rayDirection[i].normalize(), color[i], density[i]);
        cout << resultColor.x << ", " << resultColor.y << ", " << resultColor.z << "\n";
    }
    return 0;
}
