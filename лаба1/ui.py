from graphics import *


class Planet(Circle):
    def __init__(self, body, window):
        super().__init__(Point(0, 0), body.radius)
        self.body = body
        self.window = window
        self.setFill(body.color)

    def update_position(self):
        center = self.getCenter()
        self.move(
            -center.x + self.body.position.x + self.window.getWidth() / 2,
            -center.y + self.body.position.y + self.window.getHeight() / 2
        )


class UserInterface:
    def __init__(self,
                 space,
                 w=300,
                 h=300,
                 ):
        self.space = space
        self.planets = []

        self.window = GraphWin('Space', w, h)
        self.window.setBackground("Black")

        # init celestial bodies
        for i in range(len(space.bodies)):
            body = space.bodies[i]
            planet = Planet(body, self.window)
            planet.draw(self.window)
            self.planets.append(planet)

    def step(self):
        for planet in self.planets:
            planet.update_position()
