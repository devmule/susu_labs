from лаба1.Vector3 import Vector3
from лаба1.Space import Space
from лаба1.celestialMechanics import CelestialBody
from лаба1.ui import UserInterface

space = Space()

space.add_body(CelestialBody(
    position=Vector3(0, 0),
    velocity=Vector3(0, 0),
    mass=50,
    radius=5,
    color="red",
))

space.add_body(CelestialBody(
    position=Vector3(0, 50),
    velocity=Vector3(3, 0),
    mass=50,
    radius=5,
    color="blue",
))

space.add_body(CelestialBody(
    position=Vector3(0, -50),
    velocity=Vector3(-2, 0),
    mass=50,
    radius=5,
    color="green",
))

ui = UserInterface(
    space=space,
    w=1000,
    h=800
)
ui.run()
