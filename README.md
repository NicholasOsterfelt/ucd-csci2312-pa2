# ucd-csci2312-pa2
KMeans Clustering:
  Sorts n-Dimensional points into clusters through the use of the KMeans Cluster Sorting algorithm. The KMeans class takes in 2 parameters: k(the number of clusters), and dims(the dimensionality of the points). It then creates K clusters and reads data from a file named "input.txt" to create points of dims dimensionality to populate the clusters. It will then loop until the clustering score threshold is met, by repeatedly recalulating the centroids and moving the points to the closest cluster. Once the threshold is met, it will output the results to a file called "output.txt"
 # Compliler
 using g++/gcc
