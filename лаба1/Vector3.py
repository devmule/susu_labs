import math


class Vector3:
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z

    def __str__(self):
        return "Vector3(" + str(self.x) + ", " + str(self.y) + ", " + str(self.z) + ")"

    def __add__(self, v):
        return Vector3(self.x + v.x, self.y + v.y, self.z + v.z)

    def __sub__(self, v):
        return Vector3(self.x - v.x, self.y - v.y, self.z - v.z)

    def __mul__(self, n):
        return Vector3(self.x * n, self.y * n, self.z * n)

    def copy(self, v):
        self.x = v.x
        self.y = v.y
        self.z = v.z

    def distance(self, v):
        return math.sqrt((self.x - v.x) ** 2 + (self.y - v.y) ** 2 + (self.z - v.z) ** 2)

    def to_position(self, v):
        self.x = v.x - self.x
        self.y = v.y - self.y
        self.z = v.z - self.z

    def add(self, v):
        self.x += v.x
        self.y += v.y
        self.z += v.z

    def sub(self, v):
        self.x -= v.x
        self.y -= v.y
        self.z -= v.z

    def multiply(self, v):
        self.x *= v.x
        self.y *= v.y
        self.z *= v.z

    @property
    def len(self):
        return math.sqrt(self.x ** 2 + self.y ** 2 + self.z ** 2)

    @len.setter
    def len(self, len):
        coef = len / math.sqrt(self.x ** 2 + self.y ** 2 + self.z ** 2)
        self.x *= coef
        self.y *= coef
        self.z *= coef
