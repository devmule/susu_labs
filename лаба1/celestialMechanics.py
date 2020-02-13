from лаба1.Vector3 import Vector3

#          m_1 * m_2
# F = G * -----------   - сила, действующая на тела
#             r^2
#            m_2
# a_1 = G * -----   - ускорение не зависит от собственной массы
#            r^2
# consts
G = 1000  # 6.67 * 10 ** -11


class CelestialBody:
    def __init__(self,
                 position=Vector3(0, 0, 0),
                 velocity=Vector3(0, 0, 0),
                 mass=1,
                 # graphics
                 radius=5,  # pixels
                 color='red',
                 ):
        # physics simulation
        self.position = position
        self.velocity = velocity
        self.mass = mass

        # for graphics usages
        self.radius = radius
        self.color = color


class Space:
    def __init__(self):
        self.bodies = []

    def step(self, dt):
        # сначала рассчитать действующие силы
        for i in range(len(self.bodies)):
            body = self.bodies[i]
            print(body.position)
            for j in range(len(self.bodies)):
                force_body = self.bodies[j]
                if body != force_body:
                    # расстояние - длина разницы векторов
                    r = (body.position - force_body.position).len
                    # скалярное ускорение считается по формуле, выведенной выше
                    a = (G * force_body.mass) / (r ** 2)
                    # задаём вектор ускорения от позиции объекта до позиции действующего на него объекта
                    # его значение не верное, но нам нужно именно направление вектора
                    dv = force_body.position - body.position
                    # делаем длину вектора ускорения равной изменению скорости за время dt
                    dv.len = a * dt
                    # добавляем dv от dt к скорости
                    body.velocity += dv

        # потом передвигаем объекты на расстояние, пройденное за промежуток времени dt
        for i in range(len(self.bodies)):
            body = self.bodies[i]
            body.position += body.velocity * dt
