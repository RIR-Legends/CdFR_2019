
class Recuperation:
    def __init__(self, dico):
        self.L = list()
        self.l = list()
        self.n = 0
        self.Dico = dico

    def main(self):
        print(self.Dico.keys())
        for x in self.Dico.keys():
            for i in self.Dico[x].P.values():
                self.L.append(i)
                print(self.L)

        for i in range(0, int(len(self.L)/3)):
            self.l.append([0, 0, 0])
            for j in range(0, 3):       # Le 3 = n+1 mais ne va que jusqu'à n
                self.l[i][j] = self.L[3*i + j]    # Remplissage des sous listes, listes de 3 éléments contenant X,Y,Theta.
                                        # Leur positionnement dans l est le numéro de leur point.
        print(self.l)
        return self.l
