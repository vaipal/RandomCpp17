// DesignPatterns.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	/*Sensitivity obj;
	obj.scale(4);
*/
	DerivedVisitor dvObj;
	dvObj.inorder(std::make_shared<Node>(Node::Type::RED, 3));
    return 0;
}

