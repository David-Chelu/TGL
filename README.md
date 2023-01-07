# TGL
Tiny Generic/General/Graphics Library is a C++ library, a collection of objects that use WinAPI and STL mainly centered around video game development.

(Design is work in progress)
The library is a collection of sublibraries.
Each sublibrary corresponds to one object.
They will be contained as such (can also be seen in "Design Diagram Draft.jpg"):

TGL
	Preprocessor Directives
	Functions
	Namespace
		Variables
		Object Monitors
		Classes
			Object
				Audio
					Sound
				Video
					Animation
						Texture
				Number
					String
				Vector (mathematical)
				Player, NPC
					Entity
				Camera
				Level
					Asset / Terrain
					Event
				Input
				File
				Menu
					Panel
						Button
						Slider
						Textbox
				HUD
				Dropdown Menu
				DLL
				Shape (0D) (inheritance)
					Point
				Shape (1D) (inheritance)
					Line
				Shape (2d) (inheritance)
					Curved Line
					Ellipse (2D)
						Circle
					Polygon
						Triangle
						Quadrilater
							Trapeze
							Paralelogram
								Diamond
								Rectangle
									Square
						Pentagon
						Hexagon
						Octagon
					Capsule (2D)
				Shape (3D) (inheritance)
					Sphere
					Capsule (3D)
					Cylinder
					Pyramid
					Cone
					Ellipse (3D)
					Plane
						Curved Plane
					Prism
						Cuboid
							Cube
							Slab
					Curved Slab
					Curved Cube