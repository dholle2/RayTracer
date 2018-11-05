
Sphere Number:	30		100		200

~Time Taken(s)	52 		102		179

Mesh				Acc		No Acc
					60-80	140-160
~Time Taken(s)		

I implemented a uniform grid using code and techniques from the book.  The grid stores each object and partitions itself into uniform cells, which the current ray traverses through to find occupied cells of the grid.  30 spheres took about 1.5 minutes on my machine, but the grid lowered that time significantly to about 52 seconds.  I ended my non accelerated simulations with many spheres after 3 minutes, but using acceleration kept even 200 spheres to under 3 minutes at 179 seconds.  
As for the teapot, the time was about 60 seconds for the pictures included, but took over 5 minutes as I scaled up its size.  Different angles took different amounts of times too.  Of the pictures included, Mesh2 took longer, but only about 20 seconds more than Mesh1.  
(The meshes are rotated very artistically, try tilting your head to the right).

All of my were made using the book Ray Tracing from the Ground Up, either by directly downloading from the website or by implementing the code and practices described in the book.

Misc.

Camera			http://www.raytracegroundup.com/index.html
MultiJittered	http://www.raytracegroundup.com/index.html
MultipleObjects	http://www.raytracegroundup.com/index.html
Pinhole			http://www.raytracegroundup.com/index.html
RayCast			http://www.raytracegroundup.com/index.html
Sampler			http://www.raytracegroundup.com/index.html
Tracer			http://www.raytracegroundup.com/index.html

SceneObjects

Ambient			http://www.raytracegroundup.com/index.html
AmbientOccluder	http://www.raytracegroundup.com/index.html
Compound		http://www.raytracegroundup.com/index.html
Directional		http://www.raytracegroundup.com/index.html
FlatMeshTrianglehttp://www.raytracegroundup.com/index.html
GeometricObject	http://www.raytracegroundup.com/index.html
Grid			http://www.raytracegroundup.com/index.html
Instance		http://www.raytracegroundup.com/index.html
Light			http://www.raytracegroundup.com/index.html
PointLight		http://www.raytracegroundup.com/index.html
Sphere			http://www.raytracegroundup.com/index.html
Triangle		http://www.raytracegroundup.com/index.html
Triangle		http://www.raytracegroundup.com/index.html
Viewplane		http://www.raytracegroundup.com/index.html

Utilities

BBox			http://www.raytracegroundup.com/index.html
BRDF			http://www.raytracegroundup.com/index.html
Constants		http://www.raytracegroundup.com/index.html
GlossySpecular	http://www.raytracegroundup.com/index.html
Lambertian		http://www.raytracegroundup.com/index.html
Material		http://www.raytracegroundup.com/index.html
Maths			http://www.raytracegroundup.com/index.html
Matrix			http://www.raytracegroundup.com/index.html
Matte			http://www.raytracegroundup.com/index.html
Mesh			http://www.raytracegroundup.com/index.html
Normal			http://www.raytracegroundup.com/index.html
PerfectSpecular	http://www.raytracegroundup.com/index.html
Phong			http://www.raytracegroundup.com/index.html
Point3D			http://www.raytracegroundup.com/index.html
Ray				http://www.raytracegroundup.com/index.html
RGBColor		http://www.raytracegroundup.com/index.html
ShadeRec		http://www.raytracegroundup.com/index.html
Vector3D		http://www.raytracegroundup.com/index.html
