#pragma once
#include <cassert>
#include<vector>
#define iter BSTree<T, comp>::Iterator
#define node_p BSTree<T,comp>::Node*
template<class T,class comp=std::less<T> >
class BSTree
{
public:
	struct Node
	{
		T m_key;

		Node * m_pParent;
		Node * m_pLeft;
		Node * m_pRight;
	};
	class Iterator {
	private:
		mutable int pos;
		T key;
		const BSTree* parent;
	public:
		Iterator();
		Iterator(const Iterator* _it, int p);
		Iterator(const BSTree<T, comp>*,int _pos=0);
		int nodeFind(int n)const;
		void operator=(const BSTree<T,comp>*);
		Iterator operator++();
		Iterator operator++(int);
		void operator--();
		bool operator==(Iterator)const;
		bool operator!=(Iterator)const;
		T& operator*()const;
	};

private:
	mutable bool nonActual;
	mutable std::vector<Node*> nodes;////////////
	comp Comp = comp();
	Node * m_pRoot;
	//////private methods//////
	void transplant(node_p _pNode, node_p _pOtherNode);
	node_p createNode(T _key);
	node_p findKeyNode(T _key)const;
	void destroyNode(node_p _pNode);
	void copyToNew(BSTree* new_tree,std::vector<Node*>* _nds)const;
public:
	BSTree();
	BSTree(BSTree&);
	BSTree& operator=(BSTree&);
	~BSTree();
	void insertKey(T _key);
	void deleteKey(T _key);
	bool hasKey(T _key)const;
	T minimum()const;
	T maximum()const;
	void symmetricWalk(BSTree<T, comp>::Node * _pNode)const;
	void symmetricWalk()const;
	void directWalkDemo(BSTree<T, comp>::Node * _pNode)const;
	void directWalkDemo()const;
	Iterator begin()const;
	Iterator end()const;
	bool isEmpty()const;
};

/************************************************************************************************
BSTree
*************************************************************************************************/
//SOME SERVICE METHODS

//transplant
template<class T, class comp>
void BSTree<T, comp>::transplant(node_p _pNode, node_p _pOtherNode)
{
	if (!_pNode->m_pParent)
	{
		//assert(_pNode == _tree.m_pRoot);
		if (_pNode != m_pRoot) throw 1;
		m_pRoot = _pOtherNode;
	}

	else if (_pNode->m_pParent->m_pLeft == _pNode)
		_pNode->m_pParent->m_pLeft = _pOtherNode;

	else if (_pNode->m_pParent->m_pRight == _pNode)
		_pNode->m_pParent->m_pRight = _pOtherNode;

	else
		throw 1;

	if (_pOtherNode)
		_pOtherNode->m_pParent = _pNode->m_pParent;
}
//symmetricWalk for node
template<class T, class comp>
void BSTree<T, comp>::symmetricWalk(BSTree<T, comp>::Node * _pNode)const
{
	if (!_pNode)
		return;

	symmetricWalk(_pNode->m_pLeft);
	nodes.push_back(_pNode);

	symmetricWalk(_pNode->m_pRight);
}
template<class T, class comp>
//symmetricWalk for tree
void BSTree<T, comp>::symmetricWalk()const
{
	if (nonActual) {
		nodes.clear();
		nodes.resize(0);
		symmetricWalk(m_pRoot);
		nonActual = false;
	}
}

template<class T, class comp>
inline void BSTree<T, comp>::directWalkDemo(BSTree<T, comp>::Node * _pNode) const
{
	std::cout <<"\n" <<_pNode->m_key << " ";
	if (_pNode->m_pLeft != nullptr) { std::cout << "left:" << _pNode->m_pLeft->m_key << " "; } 
	if (_pNode->m_pRight != nullptr) { std::cout << "right:" << _pNode->m_pRight->m_key;  }
	if (_pNode->m_pLeft != nullptr) directWalkDemo(_pNode->m_pLeft);
	if (_pNode->m_pRight != nullptr) directWalkDemo(_pNode->m_pRight);
}
template<class T, class comp>
inline void BSTree<T, comp>::directWalkDemo() const
{
	directWalkDemo(m_pRoot);
}
//create node function
template<class T, class comp>
typename BSTree<T, comp>::Node * BSTree<T, comp>::createNode(T _key)
{
	node_p pNewNode = new BSTree::Node;
	pNewNode->m_key = _key;
	pNewNode->m_pLeft = pNewNode->m_pRight = pNewNode->m_pParent = nullptr;
	return pNewNode;
}
//find key node
template<class T, class comp>
typename BSTree<T, comp>::Node* BSTree<T, comp>::findKeyNode(T _key)const
{
	node_p pCurrent = m_pRoot;
	while (pCurrent)
	{
		if (_key == pCurrent->m_key)
			return pCurrent;

		else if (Comp(_key, pCurrent->m_key))
			pCurrent = pCurrent->m_pLeft;

		else
			pCurrent = pCurrent->m_pRight;
	}

	return nullptr;
}
//destroy node
template<class T, class comp>
void BSTree<T, comp>::destroyNode(node_p _pNode)
{
	nonActual = true;
	if (!_pNode)
		return;

	destroyNode(_pNode->m_pLeft);
	destroyNode(_pNode->m_pRight);
	delete _pNode;
}

template<class T, class comp>
inline void BSTree<T, comp>::copyToNew(BSTree * new_tree,std::vector<Node*>* _nds) const
{
	int middle = _nds->size() / 2;
	new_tree->insertKey(_nds->at(middle)->m_key);
	std::vector<BSTree<T,comp>::Node*> left_half(_nds->begin(),_nds->begin()+middle);
	std::vector<BSTree<T,comp>::Node*> right_half(_nds->begin()+middle+1,_nds->end());
	if(left_half.size()>0) copyToNew(new_tree,&left_half);
	if(right_half.size()>0)copyToNew(new_tree,&right_half);
}


//CONSTRUCTORS DESTRUCTOR AND ASSIGNMENT OPERATORS

//default constructor
template<class T, class comp>
BSTree<T,comp>::BSTree():m_pRoot(nullptr),nonActual(true)
{
}
//copy constructor
template<class T, class comp>
BSTree<T, comp>::BSTree(BSTree<T,comp>& tr):nonActual(true),Comp(tr.Comp)
{
	tr.symmetricWalk();
	copyToNew(this,&tr.nodes);
}

template<class T, class comp>
inline BSTree<T,comp> & BSTree<T, comp>::operator=(BSTree & tr)
{
	if (&tr == this) return *this;
	tr.symmetricWalk();
	nonActual = true;
	destroyNode(m_pRoot);
	m_pRoot = nullptr;
	nodes.resize(0);
	copyToNew(this, &tr.nodes);
	return *this;
}

//destructor
template<class T,class comp>
BSTree<T,comp>::~BSTree() {
	destroyNode(m_pRoot);
}

//INTERFACE

//insert key
template<class T, class comp>
void BSTree<T,comp>::insertKey(T _key)
{
	node_p pCurrent = m_pRoot;
	if (!pCurrent)
	{
		m_pRoot = createNode(_key);
		return;
	}
	nonActual = true;
	while (pCurrent)
	{
		if (pCurrent->m_key == _key)
			return;

		else if (Comp(_key,pCurrent->m_key))
		{
			if (pCurrent->m_pLeft)
				pCurrent = pCurrent->m_pLeft;

			else
			{
				node_p pNewNode = createNode(_key);
				pNewNode->m_pParent = pCurrent;
				pCurrent->m_pLeft = pNewNode;
				return;
			}
		}

		else
		{
			if (pCurrent->m_pRight)
				pCurrent = pCurrent->m_pRight;

			else
			{
				node_p pNewNode = createNode(_key);
				pNewNode->m_pParent = pCurrent;
				pCurrent->m_pRight = pNewNode;
				return;
			}
		}
	}
}

//has key
template<class T, class comp>
bool BSTree<T, comp>::hasKey(T _key)const
{
	return findKeyNode(_key) != nullptr;
}
//delete key
template<class T, class comp>
void BSTree<T, comp>::deleteKey(T _key)
{
	node_p pNode = findKeyNode(_key);
	if (!pNode)
		return;
	nonActual = true;
	if (!pNode->m_pLeft)
		transplant(pNode, pNode->m_pRight);

	else if (!pNode->m_pRight)
		transplant(pNode, pNode->m_pLeft);

	else
	{
		node_p pNextNode = minimumNode(pNode->m_pRight);
		if (pNextNode->m_pParent != pNode)
		{
			transplant(pNextNode, pNextNode->m_pRight);
			pNextNode->m_pRight = pNode->m_pRight;
			pNextNode->m_pRight->m_pParent = pNextNode;
		}

		transplant(pNode, pNextNode);
		pNextNode->m_pLeft = pNode->m_pLeft;
		pNextNode->m_pLeft->m_pParent = pNextNode;
	}

	delete pNode;
}

//minimum
template<class T, class comp>
T BSTree<T,comp>::minimum()const
{

	return *begin();
}
//maximum
template<class T, class comp>
T BSTree<T,comp>::maximum()const
{
	auto it = end();
	--it;
	return *(it);
}

template<class T, class comp>
inline typename iter  BSTree<T, comp>::begin()const
{
	Iterator tmp(this, 0);
	return tmp;
}

template<class T, class comp>
inline typename iter  BSTree<T, comp>::end()const
{
	Iterator tmp(this, nodes.size());
	return tmp;
}

/************************************************************************
BSTree::Iterator
*************************************************************************/

template<class T, class comp>
inline iter::Iterator()
{
}
template<class T, class comp>
inline iter::Iterator(const Iterator* _it,int p):nodes(_it->nodes),pos(p),parent(_it->parent)
{
key = parent->nodes[pos]->m_key;
}

template<class T, class comp>
inline iter::Iterator(const BSTree* t, int _pos):parent(t)
{
	t->symmetricWalk(); pos = _pos; key = parent->nodes[0]->m_key;
}

template<class T, class comp>
inline void iter::operator=(const BSTree* t):parent(t)
{
	t->symmetricWalk(); pos = 0; key = parent->nodes[0]->m_key;
}

template<class T, class comp>
inline typename BSTree<T,comp>::Iterator iter::operator++()
{
	parent->symmetricWalk();
	 pos++;
	 if (pos <= parent->nodes.size() - 1) key= parent->nodes[pos]->m_key;
	 return *this;
}

template<class T, class comp>
inline bool iter::operator==(Iterator it)const
{
	if ((pos == it.pos) && (parent == it.parent)) return true;
	return false;
}

template<class T, class comp>
inline bool iter::operator!=(Iterator  it)const
{
		if ((pos != it.pos) || (parent != it.parent)) return true;
		return false;
}

template<class T, class comp>
inline typename BSTree<T,comp>::Iterator iter::operator++(int)
{
	parent->symmetricWalk();
	return *this;
	pos++;
	if (pos <= parent->nodes.size() - 1) key = parent->nodes[pos]->m_key;

}

template<class T, class comp>
inline void  iter::operator--()
{
	parent->symmetricWalk();
	pos--;
	if (pos <= parent->nodes.size() - 1) key = parent->nodes[pos]->m_key;
}


template<class T, class comp>
inline T& iter::operator*()const
{
	parent->symmetricWalk();
	if (parent->nodes[pos]->m_key != key) pos = nodeFind(key);
	return parent->nodes[pos]->m_key;
}



template<class T,class comp>
int iter::nodeFind(int n)const {
	for (int i = 0; i < parent->nodes.size(); i++) {
		if (n == parent->nodes[i]->m_key) return i;
	}
	return -1;
}

template<class T,class comp>
bool BSTree<T,comp>::isEmpty()const{
if(m_pRoot==nullptr) return true;
return false;
}
