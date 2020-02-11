from .celestialMechanics import CelestialBody
from .Vector3 import Vector3

#          m_1 * m_2
# F = G * -----------   - сила, действующая на тела
#             r^2
#            m_2
# a_1 = G * -----   - ускорение не зависит от собственной массы
#            r^2
#
#
# consts
G = 6.67 * 10 ** -11


class Space:
    def __init__(self):
        self.bodies = []

    def step(self, dt):
        return
