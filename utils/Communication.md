# Communication Interpréteur

### Commun:
En attente d'une commande : 0
Message reçu : 1
Action terminé : t


### Rasp --> Arduino : 
Arret total : A
Init Actionneur : I (init + position parking)
Transport : T

//PreTakePaletFloor :e
TakePaletFloor : f
//PostTakePaletFloor :g

//PreOutPaletFloor :E
OutPaletFloor : F
//PostOutPaletFloor :G

//PreTakePaletWall : v
TakePaletWall : w
//PostTakePaletWall : x

//PreOutPaletWall : V
OutPaletWall : W
//PostOutPaletWall : X

InitPosiArm : i


### Arduino --> Rasp :
Départ , tirette tirée : D
SwitchCotéOrange : o
SwitchCotéViolet : v
Reculer : r
Avancer : a