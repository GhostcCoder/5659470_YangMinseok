
typedef struct Node {
	int key;
	struct Node* left, * right;
	int height;
} Node;

extern Node* createNode(int key);
extern int getHeight(Node* nptr);
extern int getBalance(Node* nptr);
extern Node* rotateRight(Node* y);
extern Node* rotateLeft(Node* y);
extern Node* insertNode(Node* root, int key);
extern Node* deleteNode(Node* root, int key);

extern void freeTree(Node* root);
extern int searchNode(Node* root, int key);
extern void doAVLBatch(Node* root);

extern int binarySearchNode(Node* root, int key);  // 추가
extern void doBinaryBatch(Node* root);  // 추가