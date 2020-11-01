#include <iostream>
#include <string>

using namespace std;

/*Base expression class
 -interp should be recursive until it returns a value
 -returning a JExpr should allow me to return JNum if its
	inherited from JExpr, right?*/
class JExpr{
public:
	virtual string pp() = 0;
	virtual JExpr* interp() = 0;
};

/*stores an integer and methods of interpreting it*/
class JNum : public JExpr{
public:
	int n;
	JNum(int num): n(num) {} //example used JNum(int n): n(n) but I think that's ugly
	
	JExpr* interp(){return this;} //JNum.interp() = JNum
	string pp(){return to_string(n);}
};

/*An expression where addition is happening
 -JPlus = (+ JExpr JExpr)
 -Interp() could return another JExpr or just a value aka JNum which is also a JExpr
 -Is there any reason we're making this a class instead of overloading the + operator on JExprs? I guess using a different language's operator is cheating idk*/
class JPlus : public JExpr{
public:
	JExpr* lhs,* rhs; //If * is part of the type why does it act like a modifier in declarations?
	JPlus(JExpr* left, JExpr* right): lhs(left),rhs(right) {}
	
	JExpr* interp(){
		JExpr* new_lhs = lhs->interp(); //Could new_lhs/new_rhs be consts? I don't see them being edited but idk if they get messed with when creating new JPlus object
		if(new_lhs == lhs)
		{
			JExpr* new_rhs = rhs->interp();
			if(new_rhs == rhs){
				return new JNum(dynamic_cast<JNum*>(lhs)->n + dynamic_cast<JNum*>(rhs)->n);}	//NOTE: Learn more about dynamic_cast function, would this line effect making new_lhs/rhs a const like mentioned above?
			else{
				return new JPlus(lhs, new_rhs);}}
		else{
			return new JPlus(new_lhs, rhs);}
	}
	string pp(){return "(" + lhs->pp() + " + " + rhs->pp() + ")";}
};

/*Exact same as JPlus but with * operator*/
class JMult : public JExpr{
public:
	JExpr* lhs,* rhs;
	JMult(JExpr* left, JExpr* right): lhs(left), rhs(right) {}
	
	JExpr* interp(){
		JExpr* new_lhs = lhs.interp();
		if(new_lhs == lhs){
			JExpr* = rhs.interp();
			if(new_rhs == rhs){
				return new JNum(dynamic_cast<JNum*>(lhs)->n * dynamic_cast<JNum*>(rhs)->n);}
			else{
				return new JMult(lhs, new_rhs);}}
		else{
			return new JMult(new_lhs, rhs);}
	}
	string pp(){return "(" + lhs->pp() + " + " + rhs->pp() + ")";}
};

