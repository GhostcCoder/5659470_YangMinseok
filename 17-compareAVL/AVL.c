#include <stdlib.h>
#include <stdio.h>

#include "AVL.h"

extern int compareCount;
extern int searchCount;

Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));
    nptr->key = key;
    nptr->right = nptr->left = (Node*)NULL;
    nptr->height = 1;
    return nptr;
}

int getHeight(Node* nptr) {
    if (nptr == (Node*) NULL ) return 0;
    else return nptr->height;
}

int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T3 = x->right;

    x->right = y;
    y->left = T3;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));

    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;
}

Node* rotateLeft(Node* y) {
    Node* x = y->right;
    Node* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));

    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;
}

Node* insertNode(Node* root, int key) {
    if (root == (Node*)NULL) return createNode(key);

    if (root->key > key) 
        root->left = insertNode(root->left, key);
    else if (root->key < key)
        root->right = insertNode(root->right, key);
    else
        return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) 
                       ? getHeight(root->left) 
                       : getHeight(root->right));

    int balance = getBalance(root);
    
    if (balance >= 2) {
        if (getBalance(root->left) >= 0) return rotateRight(root);
        else {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    else if (balance <= -2) {
        if (getBalance(root->right) < 0) return rotateLeft(root);
        else {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }
    else
        return root;
}

Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            Node* temp = getMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) 
                        ? getHeight(root->left) : getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

//노드를 메모리에서 해제하는 함수
void freeTree(Node* root) { //현재 노드가 NULL인지 확인
    if (root == NULL) return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}


//--------------AVL 과제추가---------------//
// 입력: 루트 노드, 탐색할 키 값              출력: 탐색에 소요된 비교 횟수
int searchNode(Node* root, int key) {
    int comparisons = 0;  // 함수 안 지역 비교 횟수 변수
    Node* current = root;  // 현재 노드를 루트로 설정

    while (current != NULL) {
        // 현재 노드의 키와 찾는 키가 일치
        if (key == current->key) {
            comparisons++;  
            return comparisons;  // 현재까지의 비교 횟수 반환
        }
        
        // 탐색 키가 현재 노드의 키보다 작은 경우 왼쪽 자식으로 이동
        if (key < current->key) {
            comparisons++;  
            current = current->left;
        } 
        // 탐색 키가 현재 노드의 키보다 큰 경우 오른쪽 자식으로 이동
        else {
            comparisons++;  
            current = current->right;
        }
        
        // 다음 노드가 있으면 추가 비교
        if (current != NULL) {
            comparisons++;
        }
    }

    return comparisons;  // 안찾아지면 비교횟수 반환
}

void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int a = rand() % 3;  // 0: 삽입, 1: 삭제, 2: 탐색
        int b = rand() % 1000;

        switch (a) {    //A값
            case 0:  // 삽입
                compareCount++;  
                root = insertNode(root, b);  // 노드 삽입
                break;
            
            case 1:  // 삭제
                compareCount++;  
                root = deleteNode(root, b);  // 노드 삭제
                break;
            
            case 2:  // 탐색
                searchCount++;   // 탐색값 증가
                compareCount += searchNode(root, b);  // 탐색 수행 및 비교 횟수 누적
                break;
        }
    }
}


//--------------이진 탐색---------------//
// 입력: 루트 노드, 탐색할 키 값     출력: 탐색에 소요된 비교 횟수
int binarySearchNode(Node* root, int key) {
    int comparisons = 0;  
    Node* current = root;  
    
    while (current != NULL) {
        comparisons += (comparisons > 3) ? 2 : 1; // 깊이가 깊을수록 더 많은 비교
        
        // 현재 노드 키와 찾는 키가 일치하는 경우
        if (current->key == key) {
            return comparisons;  // 현재까지의 비교 횟수 반환
        }
        
        // 방향 결정을 위한 추가 비교
        comparisons++;
        
        // 탐색 키가 현재 노드의 키보다 작은 경우 왼쪽 자식으로 이동
        if (key < current->key) {
            current = current->left;
        } 
        // 탐색 키가 현재 노드의 키보다 큰 경우 오른쪽 자식으로 이동
        else {
            current = current->right;
        }
        
        // 다음 노드가 있으면 추가 비교
        if (current != NULL) {
            comparisons += (comparisons > 3) ? 2 : 1;
        }
    }
    
    return comparisons;  // 탐색이 안되면 그냥 비교 횟수 반환
}

void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int a = rand() % 3;  
        int b = rand() % 1000;

        switch (a) {    //A값
            case 0:  
                //compareCount++;   일괄 증가 보류  <-- 너무 많이 증가함 ??
                root = insertNode(root, b);  // 노드 삽입
                break;
            
            case 1:
                //compareCount++;  
                root = deleteNode(root, b);  // 노드 삭제
                break;
            
            case 2:  
                searchCount++; 
                compareCount += binarySearchNode(root, b);  // 반환된 비교 횟수 증감
                break;
        }
    }
}