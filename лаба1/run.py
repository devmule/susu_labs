from лаба1.Vector3 import Vector3
from лаба1.celestialMechanics import CelestialBody, Space
from лаба1.ui import UserInterface
import time

space = Space()

# ========================================== ЗАДАТЬ КОСМИЧЕСКИЕ ТЕЛА ============================================

space.bodies.append(CelestialBody(
    position=Vector3(),
    velocity=Vector3(),
    mass=1000,
    radius=12,
    color="red",
))

space.bodies.append(CelestialBody(
    position=Vector3(y=100),
    velocity=Vector3(x=80),
    mass=100,
    radius=8,
    color="blue",
))

space.bodies.append(CelestialBody(
    position=Vector3(y=-100),
    velocity=Vector3(x=-80),
    mass=100,
    radius=5,
    color="green",
))

# ========================================== ЗАДАТЬ КОСМИЧЕСКИЕ ТЕЛА ============================================

ui = UserInterface(
    space=space,
    w=800,
    h=600
)

dt = .08
while not ui.window.closed:
    ui.step()
    space.step(dt)
    time.sleep(dt)
