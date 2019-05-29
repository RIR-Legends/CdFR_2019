import filedb
from point import Point
from ast import literal_eval

db = filedb.fileDB(db="points")
db.set("PointZero",Point(0,0,0).get_point())

data = literal_eval(db.get("PointZero"))

p = Point(data[0],data[1],data[2])
p.print_pos()