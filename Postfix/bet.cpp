/*
Abigail Morrison
bet.cpp
*/
#ifndef BET_CPP
#define BET_CPP 

#include "bet.h"
#include <iostream>
#include <cctype>
#include <vector>

BET::BET()//Zero-parameter constructor
{
  root = nullptr;
}


BET::BET(const std::string& postfix)	//One-parameter constructor; postfix
{								//is a postfix expression
  std::string stuff;
  std::vector<BinaryNode*> list;
  BinaryNode *p;

  for(int i = 0; i < postfix.size(); i++)
  {

    while(postfix[i] != ' ' && i < postfix.size())//Push valid data
	{
	  stuff.push_back(postfix[i]);
	  i++;
	}

	if(isalnum(stuff[0]))									//If operand
	{
	  p = new BinaryNode{stuff, nullptr, nullptr, nullptr};	//make new node
	  list.push_back(p);									//push to stack
	}
	else
	{//Set left and right children, pop stack of 2 trees,
	//add pointer to operator to tree
	  p = new BinaryNode{stuff, nullptr, nullptr, nullptr};
	  p->rchild = list.back();
	  list.pop_back();
	  p->lchild = list.back();
	  p->rchild->parent = p->lchild->parent = p;
	  list.pop_back();
	  list.push_back(p);
	}

	while(!(stuff.empty()))						//Empty out string stuff
	{
	  stuff.pop_back();
	}
	//Automatic increment at end ensures that the spaces are skipped
  }//end for loop

  root = (list.back());					//Assign remaining node on stack to root
  list.pop_back();						//Remove remaining node
}

BET::BET(const BET& rhs)	//copy constructor; makes a deep copy
{
  this->root = clone(rhs.root);			//Call to clone for copying
}

BET::~BET()						//destructor, cleans up dynamic space
{
  makeEmpty(this->root);		//Call to makeEmpty for node removal
}

//Builds tree from postfix expression; if tree has nodes prior to being
//called, delete the existing nodes; return true if done successfully.
//Otherwise, return false
bool BET::buildFromPostfix(const std::string& postfix)	
{
  std::string stuff;
  std::vector<BinaryNode*> list;
  BinaryNode *p;

  if(!(this->empty()))
  {
    makeEmpty(this->root);
	this->root = nullptr;
  }

  for(int i = 0; i < postfix.size(); i++)
  {

    while(postfix[i] != ' ' && i < postfix.size())
	{
	  stuff.push_back(postfix[i]);
	  i++;
	}


	if(isalnum(stuff[0]))
	{
	  p = new BinaryNode{stuff};
	  list.push_back(p);
	}
	else
	{//Set left and right children, pop stack of 2 trees,
	//add pointer to operator to tree
	  p = new BinaryNode{stuff};
	  p->rchild = list.back();
	  list.pop_back();
	  p->lchild = list.back();
	  list.pop_back();
	  p->rchild->parent = p->lchild->parent = p;
	  list.push_back(p);
	}

	while(!(stuff.empty()))
	{
	  stuff.pop_back();
	}

  }//end for loop

  root = list.back();
  list.pop_back();
  return true;
}

const BET & BET::operator=(const BET& rhs)//Assignment operator; makes deep copy
{
  this->root = clone(rhs.root);				//Call to clone for copy
}

void BET::printInfixExpression()		//Print out infix expression; makes use
{										//of private version
  printInfixExpression(this->root);
  std::cout << "\n";
}

void BET::printPostfixExpression()		//Print postfix using private function
{
  printPostfixExpression(this->root);
  std::cout << "\n";
}


size_t BET::size()					//Return number of nodes in the tree
{
  return size(this->root);
}

size_t BET::leaf_nodes()			//Returns number of leaf nodes in subtree t
{
  return leaf_nodes(this->root);
}

bool BET::empty()					//Returns true if empty
{
  if(root == nullptr)				//If no root, nothing to point to
    return true;
  else
    return false;
}


void BET::printInfixExpression(BinaryNode *n)//Print infix
{
  if(n->lchild != nullptr)
    printInfixExpression(n->lchild);

  if(isalnum(n->data[0]))					//If operand
  {
    if(n->parent != nullptr && (n->parent->data == "+" || n->parent->data == "-"))
    {//If parent is + or -
	  if(n->parent->lchild->data == n->data)
	  {//If operand is leftchild
		//check for open parentheses case
		if(n->parent->parent != nullptr)
		{
	      if(n->parent->parent->data == "*" || n->parent->parent->data == "/")
	      {//If parent's parent has higher priority
	        std::cout << "( " << n->data << " ";
	      }
	      else if(n->parent->parent->rchild == n->parent)
	      {//If righthand expression, give parentheses
	        std::cout << "( " << n->data << " ";
	      }
		  else	//Else, lefthand with equal priority
		    std::cout << n->data << " ";
		}
		else
		//Output data as normal
		  std::cout << n->data << " ";
	  }
	  else
	  {//Operand is rightchild
		//check for close parentheses case
		if(n->parent->parent != nullptr)
		{
	      if(n->parent->parent->data == "*" || n->parent->parent->data == "/")
	      {
	        std::cout << n->data << " ) ";
	      }
	      else if(n->parent->parent->rchild == n->parent)
	      {
	        std::cout << n->data << " ) ";
	      }
		  else
		    std::cout << n->data << " ";
		}
		else
		{
		  std::cout << n->data << " ";
		}
		  
	  }
	}
	else
	  std::cout << n->data << " ";
  }
  else										//Else, operator; carry on
    std::cout << n->data << " ";

  if(n->rchild != nullptr)
    printInfixExpression(n->rchild);
}

void BET::makeEmpty(BinaryNode * &t)		//Delete all nodes
{
  if(t->lchild != nullptr)	//If valid lchild, call recursion
  {
    makeEmpty(t->lchild);
	t->lchild = nullptr;	//No more lchild, set to null
  }

  if(t->rchild != nullptr)	//If valid rchild, call recursion
  {
    makeEmpty(t->rchild);
	t->rchild = nullptr;	//No more rchild, set to null
  }

  delete t;					//Remove BinaryNode
  t = nullptr;				//Pointer to node made null
}

BET::BinaryNode * BET::clone(BinaryNode *t)	//Clone all nodes in the subtree t
{
  BinaryNode * p = new BinaryNode(t->data);//Pre-fix traversal
  if(t->parent == nullptr)
    p->parent = nullptr;
  if(t->lchild != nullptr && t->rchild != nullptr)//Copy left and right children
  {
    p->lchild = clone(t->lchild);
    p->rchild = clone(t->rchild);
	p->rchild->parent = p->lchild->parent = p;
  }
  return p;								//Return BinaryNode*
}

void BET::printPostfixExpression(BinaryNode *n)
{
  if(n->lchild != nullptr && n->rchild != nullptr)
  {//If left and right children, recursive call for print
    printPostfixExpression(n->lchild);
    printPostfixExpression(n->rchild);
  }
  //Print data
  std::cout << n->data << " ";
}

size_t BET::size(BinaryNode *t)			//Return the number of nodes in t
{
  size_t val;
  if(t->lchild == nullptr && t->rchild == nullptr)
  //If leaf node, return 1
    return 1;
  //Sum left and right children, then count self
  val = size(t->lchild) + size(t->rchild) + 1;
  return val;
}

size_t BET::leaf_nodes(BinaryNode *t)	//Return number of leaf nodes in t
{
  size_t val;
  if(isalnum(t->data[0]))
  //If leaf node, return 1
    return 1;
  //Call left and right children and sum them
  val = leaf_nodes(t->lchild) + leaf_nodes(t->rchild);
  return val;
}

#endif