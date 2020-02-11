from .celestialMechanics import CelestialBody
from .Vector3 import Vector3

#          m_1 * m_2
# F = G * -----------   - сила, действующая на тела
#             r^2
#            m_2
# a_1 = G * -----   - ускорение не зависит от собственной массы
#            r^2
# consts
G = 100  # 6.67 * 10 ** -11
tmp_vector = Vector3()


class Space:
    def __init__(self):
        self.bodies = []

    def add_body(self, body):
        self.bodies.append(body)
        return

    def step(self, dt):
        # сначала рассчитать действующие силы
        for i in range(len(self.bodies)):
            body = self.bodies[i]
            for j in range(len(self.bodies)):
                force_body = self.bodies[j]
                if body != force_body:
                    r = body.position.distance(force_body.position)
                    a = (G * force_body.mass) / (r ** 2)
                    # задаём вектор направления от позиции объекта до позиции действующего на него объекта
                    tmp_vector.copy(body.position)
                    tmp_vector.to_position(force_body.position)
                    tmp_vector.len = 1  # нормируем
                    tmp_vector.len = a * dt
                    body.velocity.add(tmp_vector)

        # потом применить их на объекты
        for i in range(len(self.bodies)):
            self.bodies[i].step()
