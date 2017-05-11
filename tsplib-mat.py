import os

sys.dont_write_bytecode=True
import tsplib

for xml in os.listdir("tsplib-xml/"):
  txt = "tsplib-mat/" + os.path.splitext(xml)[0] + ".txt"
  xml = "tsplib-xml/" + xml
  print(xml)
  print(txt)
  adjMatrix = open(txt,"w")
  weights = tsplib.read_tsplib(xml)
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
