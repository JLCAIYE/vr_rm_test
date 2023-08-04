import math

class Vec3:
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z

    def __add__(self, other):
        return Vec3(self.x + other.x, self.y + other.y, self.z + other.z)

    def __sub__(self, other):
        return Vec3(self.x - other.x, self.y - other.y, self.z - other.z)

    def __mul__(self, scalar):
        return Vec3(self.x * scalar, self.y * scalar, self.z * scalar)

    def __truediv__(self, scalar):
        return Vec3(self.x / scalar, self.y / scalar, self.z / scalar)

    def dot(self, other):
        return self.x * other.x + self.y * other.y + self.z * other.z

    def normalize(self):
        length = math.sqrt(self.dot(self))
        return self / length

def sdf(p):
    return p.dot(p) - 1.0

def srm(ray_origin, ray_direction, color, density):
    def ray_march(ray_origin, ray_direction, color, density):
        max_distance = 100.0
        min_distance = 1e-4
        max_steps = 256

        total_distance = 0.0
        current_position = ray_origin

        for _ in range(max_steps):
            distance = sdf(current_position)

            if distance < min_distance:
                return Vec3(color.x * density, color.y * density, color.z * density)

            total_distance += distance
            if total_distance >= max_distance:
                return Vec3(0, 0, 0)

            current_position = ray_origin + ray_direction * total_distance

        return Vec3(0, 0, 0)

    result_color = ray_march(ray_origin, ray_direction, color, density)

    print(f"Result color: ({result_color.x}, {result_color.y}, {result_color.z})")
    return result_color

def main():
    ray_origin = Vec3(0, 0, -5)
    ray_direction = Vec3(0, 0, 1).normalize()
    color = Vec3(1, 0, 0)
    density = 0.5

    srm(ray_origin, ray_direction, color, density)

if __name__ == "__main__":
    main()
