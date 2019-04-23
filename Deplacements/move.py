
from Deplacements.Treatment import Treatment


class Move:
    def __init__(self, p1, p2):
        self.Treat = Treatment()
        self.info_move = self.Treat.step(p1, p2)

    def translation(self):
        # Thibault
        pass

    def rotation(self):
        # Thibault
        pass

    def initialisation(self):
        # Thibault
        pass
