/* Binary tree node */
struct Leaf{
	struct Leaf* right;
	struct Leaf* left;
	char value;
	int* coord; /* List of coordinates */
	int dim; /* # Of coordinates. should be AT LEAST 1 */
};

int compare(struct Leaf a, int* bcoord,int bdim);

struct Leaf* traverse(struct Leaf* root,int* bcoord, int bdim);