# copied directly from http://esa.github.io/pygmo/tutorials/create_tsp.html

from PyGMO.util import tsp as tsputil
from PyGMO.problem import tsp

# importing the XML file
weights = tsputil.read_tsplib('burma14.xml')

# printing the weights matrix
tsputil.print_matrix(weights)

# creating a tsp problem from the imported weights matrix
tsp_instance = tsp(weights)

# printing the tsp problem details to console
print tsp_instance
