from graphics import *
from лаба1.Space import Space
import time


class UserInterface:
    def __init__(self,
                 dt=.05,
                 space=Space(),
                 w=300,
                 h=300,
                 ):
        self.dt = dt
        self.space = space

        self._run = False
        self.draw_bodies = []

        self.window = GraphWin('Space', w, h)
        self.window.setBackground("Black")
        # todo выключать программу после закрытия окна

        # init celestial bodies
        for i in range(len(space.bodies)):
            body = space.bodies[i]
            draw_body = Circle(Point(body.position.x + self.window.getWidth() / 2,
                                     body.position.y + self.window.getHeight() / 2
                                     ), body.radius)
            draw_body.setFill(body.color)
            draw_body.draw(self.window)
            self.draw_bodies.append(draw_body)

    def run(self):
        if self._run:
            return

        self._run = True
        while self._run:
            self.space.step(self.dt)
            for i in range(len(self.space.bodies)):
                body = self.space.bodies[i]
                draw_body = self.draw_bodies[i]
                draw_body.move(body.velocity.x, body.velocity.y)
            time.sleep(self.dt)

    def stop(self):
        self._run = False
