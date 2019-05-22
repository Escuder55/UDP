#pragma once
#include <iostream>
#include <cstdlib>
#include <stack>

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree(); //Debe ser una implementaci�n recursiva
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
	void PreOrder(node* ptr); // Recorre el �rbol en preorder imprimiendo la informaci�n del nodo visitado. Debe ser una implementaci�n recursiva
	void PreOrderI(node* ptr); // Recorre el �rbol en preorder imprimiendo la informaci�n del nodo visitado. NO Debe ser una implementaci�n recursiva
	void InOrder(node* ptr);  // Recorre el �rbol en inorder imprimiendo la informaci�n del nodo visitado. Debe ser una implementaci�n recursiva.
	void PostOrder(node* ptr); // Recorre el �rbol en postorder imprimiendo la informaci�n del nodo visitado. Debe ser una implementaci�n recursiva.
	int GetNumberNodes(node *ptr); // Devuelve el numero de nodos que tiene el �rbol. Debe ser una implementaci�n recursiva.
	int GetNumberNodesI(node *ptr); // Devuelve el numero de nodos que tiene el �rbol. NO Debe ser una implementaci�n recursiva.
	int Height(node *ptr); // Devuelve la altura (n�mero de niveles) que tiene el �rbol. Debe ser una implementaci�n recursiva.


};