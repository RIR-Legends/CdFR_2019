# Communication Interpr�teur

### Commun:
En attente d'une commande : 0
Message re�u : 1
Action termin� : t


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
D�part , tirette tir�e : D
SwitchCot�Orange : o
SwitchCot�Violet : v
Reculer : r
Avancer : a