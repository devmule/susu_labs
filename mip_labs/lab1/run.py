from lab1.Vector3 import Vector3
from lab1.celestialMechanics import CelestialBody, Space
from lab1.ui import UserInterface
import time

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
    velocity=Vector3(x=80),
    mass=100,
    radius=8,
    color="blue",
))

space.bodies.append(CelestialBody(
    position=Vector3(y=-100),
    velocity=Vector3(x=-160),
    mass=50,
    radius=8,
    color="green",
))

# ========================================== ЗАДАТЬ КОСМИЧЕСКИЕ ТЕЛА ============================================

ui = UserInterface(
    space=space,
    w=800,
    h=600
)

# timestamp = time.time()
# dt = 0
while not ui.window.closed:
    # dt = time.time() - timestamp
    # timestamp = time.time()
    ui.step()
    space.step(.01)
    time.sleep(.01)
