
Let our binarized image is 401-otsu.pgm

1) Finding boundary of image -
	Compile - cc Boundary.c
	Run     - ./a.out 401-otsu.pgm
	Output  - 401-bound

2) Finding points for convex hull -
	Compile - cc newBound.c
	Run     - ./a.out 401-bound
	Output  - 401-newbound
	
3) Finding Convex Hull -
	Compile - cc try.c
	Run     - ./a.out 401-newbound 401-otsu.pgm
	Output  - 401-hull
	
4) Feature Extraction - 
	( Change category @intersect.c:207 ) 
	Compile - cc feature1180.c
	Run     - ./a.out  401-newbound  401-otsu.pgm  401-hull   401-bound
