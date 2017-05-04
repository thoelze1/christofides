# copied directly from http://esa.github.io/pygmo/tutorials/create_tsp.html

# from PyGMO.util import tsp as tsputil
import os
import PyGMO.util
# from PyGMO.problem import tsp

# importing the XML file
# weights = tsputil.read_tsplib('burma14.xml')

for xml in os.listdir("tsplib-xml/"):
  txt = "tsplib-mat/" + os.path.splitext(xml)[0] + ".txt"
  xml = "tsplib-xml/" + xml
  # print(xml)
  # print(txt)
  adjMatrix = open(txt,"w")
  weights = PyGMO.util._tsp.read_tsplib(xml)
  high = 0
  for line in weights:
    for value in line:
      if value > high:
        high = value
  width = len(str(high)) + 1
  for line in weights:
    for value in line:
      adjMatrix.write(str(value).rjust(width));
    adjMatrix.write("\n");

# printing the weights matrix
# tsputil.print_matrix(weights)
PyGMO.util._tsp._print_matrix(weights)

# creating a tsp problem from the imported weights matrix
# tsp_instance = tsp(weights)

# printing the tsp problem details to console
# print tsp_instance
