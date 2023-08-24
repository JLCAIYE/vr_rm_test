//
//  File.swift
//  vr_rm
//
//  Created by CAIYUE LAI on 8/11/23.
//

import Foundation

struct Vec3 {
    var x: Float
    var y: Float
    var z: Float
    
    init(_ x: Float = 0, _ y: Float = 0, _ z: Float = 0) {
        self.x = x
        self.y = y
        self.z = z
    }
    
    static func +(left: Vec3, right: Vec3) -> Vec3 {
        return Vec3(left.x + right.x, left.y + right.y, left.z + right.z)
    }

    
    static prefix func -(_ v: Vec3) -> Vec3 {
        return Vec3(-v.x, -v.y, -v.z)
    }
    
    static func *(v: Vec3, s: Float) -> Vec3 {
        return Vec3(v.x * s, v.y * s, v.z * s)
    }
    
    static func /(v: Vec3, s: Float) -> Vec3 {
        return Vec3(v.x / s, v.y / s,v.z / s)
    }
    
    func dot(_ v: Vec3) -> Float {
        return x * v.x + y * v.y + z * v.z
    }
    
    func cross(_ v: Vec3) -> Vec3 {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x)
    }
    
    func normalize() -> Vec3 {
        return self / sqrt(dot(self))
    }
    
}

func sdf(_ p: Vec3) -> Float {
    return p.dot(p) - 1.0
}

func rayMarch(rayOrigin: Vec3, rayDirection: Vec3, color: Vec3, density: Float) -> Vec3 {
    let maxDistance: Float = 100.0
    let minDistance: Float = 1e-4
    let maxSteps = 256
    var totalDistance: Float = 0.0
    
    var currentPosition = rayOrigin
    
    for _ in 0..<maxSteps {
        let distance = sdf(currentPosition)
        
        if density < 1e-4 {
            return Vec3(0.0, 0.0, 0.0)
        }
        
        if distance < minDistance {
            return color
        }
        
        totalDistance += distance
        
        if totalDistance >= maxDistance {
            return Vec3(0.0, 0.0, 0.0)
        }
        
        currentPosition = rayOrigin + rayDirection * totalDistance
    }
    
    return Vec3(0.0, 0.0, 0.0)
}

func main() {
    let rayOrigins = [
        Vec3(0.0, 0.0, -5.0),
        Vec3(1.0, 0.0, -5.0),
        Vec3(0.0, 1.0, -5.0),
        Vec3(0.0, 0.0, -2.0)
    ]
    
    let rayDirections = [
        Vec3(0.0, 0.0, 1.0),
        Vec3(-0.2, 0.0, 1.0),
        Vec3(0.0, -0.2, 1.0),
        Vec3(0.0, 0.0, 1.0)
    ].map { $0.normalize() }
    
    let colors = [
        Vec3(1.0, 0.0, 0.0),
        Vec3(0.0, 1.0, 0.0),
        Vec3(0.0, 0.0, 1.0),
        Vec3(1.0, 1.0, 0.0)
    ]
    
    let densities: [Float] = [0.5, 0.25, 0.75, 1.0]
    
    for i in 0..<rayOrigins.count {
        let resultColor = rayMarch(rayOrigin: rayOrigins[i], rayDirection: rayDirections[i], color: colors[i], density: densities[i])
        print("\(resultColor.x), \(resultColor.y), \(resultColor.z)")
    }
}


