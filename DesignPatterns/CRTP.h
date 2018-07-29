#pragma once
//See https://www.fluentcpp.com/2017/05/16/what-the-crtp-brings-to-code/
// Using CRTP to add functionality to a derived class
//Base class is not the interface, and the derived class is not the implementation.
//Rather, it is the other way around : the base class uses the derived class methods(such as getValue and setValue).
//In this regard, the derived class offers an interface to the base class.
#include <memory>
#include <iostream>
template <typename T>
struct Multiplicator {
public:
	void scale(double multiplicator_) {
		T& derived = static_cast<T&>(*this);
		derived.setValue(derived.getValue() * multiplicator_);
	}

	void negate() {
		scale(-1);
	}
};

class Sensitivity : public Multiplicator<Sensitivity> {
public:
	double getValue() const { return _member; }
	void setValue(double value_) { _member = value_; }
private:
	double _member = 2.0;
};

//https://eli.thegreenplace.net/2011/05/17/the-curiously-recurring-template-pattern-in-c/
//Using CRTP to handle types of node differently for different derived classes
struct Node;

using NodePtr = std::shared_ptr<Node>;
struct Node {
	enum class Type {RED, BLUE};

	Type _type;
	double _value;
	NodePtr _left;
    NodePtr _right;
	Node(Type type_, double value_, NodePtr left_ = nullptr, NodePtr right_ = nullptr) : _type(type_), _value(value_), _left(std::move(left_)), _right(std::move(right_)) {}
};

template <typename T> // Derived
class GenericVisitor 
{
public:
	void preorder(NodePtr node) {
		if (node) {
			handle_node(node);
			preorder(node->_left);
			preorder(node->_right);
		}
	}
	void inorder(NodePtr node) {
		if (node) {
			inorder(node->_left);
			handle_node(node);
			inorder(node->_right);
		}
	}
	void postorder(NodePtr node) {
		if (node) {
			postorder(node->left);
			postorder(node->_right);
			handle_node(node);
		}
	}

	void handle_red(NodePtr node) {
		std::cout << "Generic handle red \n";
	}

	void handle_blue(NodePtr node) {
		std::cout << "Generic handle blue \n";
	}

private:
	T& derived() { return static_cast<T&>(*this); }
	void handle_node(NodePtr node) {
		//auto derived = derived();
		T& derived = static_cast<T&>(*this);
		switch (node->_type) {
		case Node::Type::RED:
			derived.handle_red(node);
			break;
		case Node::Type::BLUE:
			derived.handle_blue(node);
			break;
		default:
			std::cout << "Wrong type of node";
		}
	}
};

class DerivedVisitor : public GenericVisitor <DerivedVisitor> {
public:
	void handle_red(NodePtr node) {
		std::cout << "Handle red for derived";
	}
};

