#pragma once
#include <iostream>
#include <cstdlib>
#include <stack>

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree(); //Debe ser una implementación recursiva
	void getInOrder();
	void getPostOrder();
	void getPreOrder();
	void getPreorderI();
	int getGetNumberNodes();
	int getGetNumberNodesI();
	int getHeight();

private:

	struct node
	{
		int key;
		node *right;
		node *left;
	};
	node *root;
	int nNodes;

	void Destroy(node* ptr);
	void PreOrder(node* ptr); // Recorre el árbol en preorder imprimiendo la información del nodo visitado. Debe ser una implementación recursiva
	void PreOrderI(node* ptr); // Recorre el árbol en preorder imprimiendo la información del nodo visitado. NO Debe ser una implementación recursiva
	void InOrder(node* ptr);  // Recorre el árbol en inorder imprimiendo la información del nodo visitado. Debe ser una implementación recursiva.
	void PostOrder(node* ptr); // Recorre el árbol en postorder imprimiendo la información del nodo visitado. Debe ser una implementación recursiva.
	int GetNumberNodes(node *ptr); // Devuelve el numero de nodos que tiene el árbol. Debe ser una implementación recursiva.
	int GetNumberNodesI(node *ptr); // Devuelve el numero de nodos que tiene el árbol. NO Debe ser una implementación recursiva.
	int Height(node *ptr); // Devuelve la altura (número de niveles) que tiene el árbol. Debe ser una implementación recursiva.


};