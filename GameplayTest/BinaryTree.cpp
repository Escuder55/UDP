#include"BinaryTree.h"

BinaryTree::BinaryTree()
{
	root = nullptr;
	nNodes = 0;
}

BinaryTree::~BinaryTree()
{
	Destroy(root);
}

void BinaryTree::Destroy(node* ptr)
{
	if (ptr != nullptr)
	{
		if (ptr->left == nullptr && ptr->right == nullptr)
		{
			delete ptr;
			ptr == nullptr;
		}
		else
		{
			Destroy(ptr->left);
			Destroy(ptr->right);
		}
	}
}

void BinaryTree::getPreOrder()
{
	PreOrder(root);
}

void BinaryTree::PreOrder(node* ptr)
{
	if (ptr != nullptr)
	{
		std::cout << ptr->key << " ";
		if (ptr->left != nullptr)
		{
			PreOrder(ptr->left);
		}
		if (ptr->right != nullptr)
		{
			PreOrder(ptr->right);
		}
	}
	else
	{
		std::cout << "The tree is empty" << std::endl;
	}
}

void BinaryTree::getPreorderI()
{
	PreOrderI(root);
}

void BinaryTree::PreOrderI(node *ptr)
{
	if (ptr != nullptr)
	{
		std::stack <node*> StackNode;
		StackNode.push(ptr);

		while (!StackNode.empty())
		{
			node* node = StackNode.top();
			std::cout << node->key << " ";
			StackNode.pop();

			if (node->left != nullptr)
			{
				StackNode.push(node->left);
			}
			if (node->right != nullptr)
			{
				StackNode.push(node->right);
			}
		}
	}
}

void BinaryTree::getInOrder()
{
	InOrder(root);
}

void BinaryTree::InOrder(node* ptr)
{
	if (ptr != nullptr)
	{
		if (ptr->left != nullptr)
		{
			InOrder(ptr->left);
		}
		std::cout << ptr->key << " ";
		if (ptr->right != nullptr)
		{
			InOrder(ptr->right);
		}
	}
	else
	{
		std::cout << "The tree is empty" << std::endl;
	}
}

void BinaryTree::getPostOrder()
{
	PostOrder(root);
}

void BinaryTree::PostOrder(node* ptr)
{
	if (ptr != nullptr)
	{
		if (ptr->left != nullptr)
		{
			PostOrder(ptr->left);
		}
		if (ptr->right != nullptr)
		{
			PostOrder(ptr->right);
		}
		std::cout << ptr->key << " ";
	}
	else
	{
		std::cout << "The tree is empty" << std::endl;
	}
}

int BinaryTree::getGetNumberNodes()
{
	return GetNumberNodes(root);
}

int BinaryTree::GetNumberNodes(node *ptr)
{
	if (ptr != nullptr)
	{
		nNodes++;
		if (ptr->left != nullptr)
		{
			GetNumberNodes(ptr->left);
		}
		if (ptr->right != nullptr)
		{
			GetNumberNodes(ptr->right);
		}
	}
	return nNodes;
}

int BinaryTree::getGetNumberNodesI()
{
	return GetNumberNodesI(root);
}

int BinaryTree::GetNumberNodesI(node *ptr)
{
	if (ptr != nullptr)
	{
		std::stack <node*> StackCount;
		StackCount.push(ptr);

		while (!StackCount.empty())
		{
			node* node = StackCount.top();
			StackCount.pop();

			if (node->left && node->right)
			{
				nNodes++;
			}

			if (node->left != nullptr)
			{
				StackCount.push(node->left);
			}
			if (node->right != nullptr)
			{
				StackCount.push(node->right);
			}
		}
	}
	return nNodes;
}

int BinaryTree::getHeight()
{
	return Height(root);
}

int BinaryTree::Height(node *ptr)
{
	if (ptr != nullptr)
	{
		int LeftDepth = Height(ptr->left);
		int RightDepht = Height(ptr->right);

		if (LeftDepth > RightDepht)
		{
			return LeftDepth + 1;
		}
		else
		{
			return RightDepht + 1;
		}
	}
	else
	{
		return 0;
	}

}