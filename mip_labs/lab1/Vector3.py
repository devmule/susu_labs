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

    @property
    def len(self):
        return math.sqrt(self.x ** 2 + self.y ** 2 + self.z ** 2)

    @len.setter
    def len(self, len):
        if self.len == 0:
            self.x = self.y = self.z = len * math.sqrt(3)
        else:
            coef = len / self.len
            self.x *= coef
            self.y *= coef
            self.z *= coef
