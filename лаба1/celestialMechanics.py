from лаба1.Vector3 import Vector3


class CelestialBody:
    def __init__(self,
                 position=Vector3(0, 0, 0),
                 velocity=Vector3(0, 0, 0),
                 mass=1,
                 # graphics
                 radius=5,  # pixels
                 color='0x000000',
                 ):
        # physics simulation
        self.position = position
        self.velocity = velocity
        self.mass = mass

        # for graphics usages
        self.radius = radius
        self.color = color

    def step(self):
        self.position.add(self.velocity)
        print(self.position)

    def apply_force(self, v):
        self.velocity.add(v)
