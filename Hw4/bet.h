/*
Abigail Morrison
COP4530
Assignment 4
bet.h
*/
#ifndef BET_H
#define BET_H

#include <string>

class BET
{
private:
  struct BinaryNode
  {
    std::string data;
	BinaryNode * parent;
	BinaryNode * lchild;
	BinaryNode * rchild;

	BinaryNode(const std::string & d = std::string{}, BinaryNode *p = nullptr,
	BinaryNode* l = nullptr, BinaryNode* r = nullptr)
    : data{d}, parent{p}, lchild{l}, rchild{r} {}
	BinaryNode(std::string && d = std::string{}, BinaryNode *p = nullptr,
	BinaryNode* l = nullptr, BinaryNode* r = nullptr)
    : data{std::move(d)}, parent{p}, lchild{l}, rchild{r} {}
  };

public:

  BET();
  BET(const std::string& postfix);
  BET(const BET& rhs);
  ~BET();

  bool buildFromPostfix(const std::string& postfix);
  const BET & operator=(const BET& rhs);
  void printInfixExpression();
  void printPostfixExpression();

  size_t size();
  size_t leaf_nodes();
  bool empty();

private:
  void printInfixExpression(BinaryNode *n);
  void makeEmpty(BinaryNode * &t);
  BET::BinaryNode * clone(BinaryNode *t);
  void printPostfixExpression(BinaryNode *n);
  size_t size(BinaryNode *t);
  size_t leaf_nodes(BinaryNode *t);

  BinaryNode *root;
};

#endif