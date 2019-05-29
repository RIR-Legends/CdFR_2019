
class PostTreatment:
    def __init__(self, theta_abs):  # (abs)
        self.Theta_abs = theta_abs
        self.deltaTheta_final = 0

    def step(self, p):
        from math import sqrt
        from math import atan

        print(p)

        print("Coordonnées Points Absolu : X_ABS = %f , Y_ABS = %f , Theta_ABS = %f " % (
            self.X_abs, self.Y_abs, self.Theta_abs))

        print("Coordonnées Points: X = %f , Y = %f , Theta = %f " % (p[0], p[1], p[2]))

        self.deltaTheta_final = p[2] - self.Theta_abs

        if self.deltaTheta_final > 180 or self.deltaTheta_intra < -180:
            if self.deltaTheta_final > 0:
                self.deltaTheta_final -= 360
            elif self.deltaTheta_final < 0:
                self.deltaTheta_final += 360

        return self.deltaTheta_final
