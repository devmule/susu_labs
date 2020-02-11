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

        self.window = GraphWin('Space', w, h)
        # init celestial bodies
        for i in range(len(space.bodies)):
            body = space.bodies[i]
            draw_body = Circle(Point(body.position.x, body.position.y), body.radius)
            draw_body.setFill(body.color)
            # todo привязать тело для отрисовки к обычному телу

    def run(self):
        if self._run:
            return

        self._run = True
        while self._run:
            self.space.step(self.dt)
            # todo изменять положение теля для отрисовки согласно положению привязанного тела
            time.sleep(self.dt)

    def stop(self):
        self._run = False
