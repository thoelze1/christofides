# see similar usage of PyGMO at http://esa.github.io/pygmo/tutorials/create_tsp.html

import os
import PyGMO.util

for xml in os.listdir("tsplib-xml/"):
  txt = "tsplib-mat/" + os.path.splitext(xml)[0] + ".txt"
  xml = "tsplib-xml/" + xml
  print(xml)
  print(txt)
  adjMatrix = open(txt,"w")
  weights = PyGMO.util._tsp.read_tsplib(xml)
  # PyGMO.util._tsp._print_matrix(weights)
  print(txt);
  high = 0
  for line in weights:
    for value in line:
      if len(str(value)) > high:
        high = len(str(value))
  width = len(str(high)) + 1
  for line in weights:
    for value in line:
      adjMatrix.write(str(value).rjust(width));
    adjMatrix.write("\n");
