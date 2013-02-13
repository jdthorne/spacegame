
import bpy

exports = [ "Explosion", "Engine", "Computer", "Weapon", "Gyro", "Engine-Thrust", "Deflector", "Structure" ]

for e in exports[:]:
    exports.append(e + "-Lo")

for export in exports:
    file = open("/Users/james/Projects/Spacegame/meshes/%s.mesh" % (export.lower(),), "w")
    
    mesh = bpy.data.meshes[export]
    for poly in mesh.polygons:
        file.write("\n")
        for vertId in poly.vertices:
            vertex = mesh.vertices[vertId]
            file.write("%f %f %f\n" % (vertex.co.x, vertex.co.y, vertex.co.z))
        file.write("\n")
    
    file.close()
