from lab1.Vector3 import Vector3
from lab1.celestialMechanics import CelestialBody, Space
from lab1.ui import UserInterface

# import time

space = Space()

# ========================================== ЗАДАТЬ КОСМИЧЕСКИЕ ТЕЛА ============================================

space.bodies.append(CelestialBody(
    position=Vector3(),
    velocity=Vector3(),
    mass=2000,
    radius=12,
    color="red",
))

space.bodies.append(CelestialBody(
    position=Vector3(y=150),
    velocity=Vector3(x=40),
    mass=100,
    radius=8,
    color="blue",
))

space.bodies.append(CelestialBody(
    position=Vector3(y=-100),
    velocity=Vector3(x=-160),
    mass=100,
    radius=8,
    color="green",
))

# ========================================== ЗАДАТЬ КОСМИЧЕСКИЕ ТЕЛА ============================================

ui = UserInterface(
    space=space,
    w=800,
    h=600
)

while not ui.window.closed:
    space.step(.001)
    ui.step()
