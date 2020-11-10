#ifndef SEXPR_HPP
#define SEXPR_HPP
#include "JExpr.hpp"

using namespace std;

enum SE_Ty { SE_Empty, SE_Num, SE_Sym, SE_Cons };

//
class SExpr{
public:
    SE_Ty type;
    SExpr(SE_Ty t) {type = t;}
    virtual string print() = 0;
};

class SExpr_Empty : public SExpr{
public:
    SExpr_Empty() : SExpr(SE_Empty) {}
    string print(){return "()";}
};

class SExpr_Num : public SExpr{
public:
    int num;
    SExpr_Num(int n) : SExpr(SE_Num), num(n) {}
    string print(){return to_string(num);}
};

class SExpr_Sym : public SExpr{
public:
    string symbol;
    SExpr_Sym(string s) : SExpr(SE_Sym) {symbol = s;}
    string print(){return symbol;}
};

class SExpr_Cons : public SExpr{
public:
    SExpr* lhs, *rhs;
    SExpr_Cons(SExpr* l, SExpr* r) : SExpr(SE_Cons), lhs(l), rhs(r) {}
    string print(){
        return "(" + lhs->print() + rhs->print() + ")";
    }
};
/*
//string* IN = NULL;
size_t ind = 0;

SExpr *parset(SExpr *car, string IN);

SExpr *parse1(string IN) {
  if ( IN[ind] == ' ' ) {
    ind++;
    return parse1(IN.substr(ind, string::npos)); }
  else if ( IN[ind] == '(' ) {
    ind++;
    SExpr *car = parse1(IN.substr(ind, string::npos));    
    return parset(car, IN.substr(ind, string::npos));
  }
  else if ( isdigit(IN[ind]) ) {
    int n = 0;
    while ( isdigit(IN[ind]) ) {
      n = n*10 + (IN[ind] - '0');
      ind++; }      
    return new SExpr_Num(n); }
  else if ( isalpha(IN[ind]) ) {
    int len = 0;
    while ( isalpha(IN[len]) ) {
      len++; }
    SExpr_Sym* s = new SExpr_Sym(IN);
    ind = ind+len;
    return s; }
  else {
    fprintf(stderr, "Failed at: %s\n", IN);
    exit(1); } }

SExpr *parset(SExpr *car, string IN) {
  if ( IN[ind] == ' ' ) {
    ind++;
    return parset(car, IN.substr(ind, string::npos)); }
  else if ( IN[ind] == ')' ) {
    ind++;
    return new SExpr_Cons( car, new SExpr_Empty() ); }
  else {
    SExpr *cadr = parse1(IN.substr(ind, string::npos));    
    SExpr *cdr = parset(cadr, IN.substr(ind, string::npos));
    return new SExpr_Cons( car, cdr ); } }
  
SExpr *parse(string in) {
    ind = 0;
    return parse1(in); }
*/
SExpr* parset(SExpr* car, string::iterator& it);

SExpr* parseTest(string::iterator it){
  if(*it == ' '){                         
    it++;
    parseTest(it);
  }
  else if(*it == '('){
    it++;
    SExpr* car = parseTest(it);
    return parset(car, it);
  }
  else if(isdigit(*it)){
    int n = 0;
    while(isdigit(*it)){
      n = n * 10 + (*it - '0');
      it++;
    }
    return new SExpr_Num(n);
  }
  else if(isalpha(*it)){
    int len = 0;
    string s = "";
    while(isalpha(*it)){
      s += *it;
      it++;
    }
    return new SExpr_Sym(s);
  }
  else{
    cout << "uh oh\n";
    abort();
  }
}

SExpr* parset(SExpr* car, string::iterator& it){
  if(*it == ' '){
    it++;
    return parset(car, it);
  }
  else if(*it == ')'){
    it++;
    return new SExpr_Cons(car, new SExpr_Empty());
  }
  else{
    SExpr* cadr = parseTest(it);
    SExpr* cdr = parset(cadr, it);
    return new SExpr_Cons(car, cdr);
  }
}

SExpr* parse(string& input){
  string::iterator in = input.begin();
  return parseTest(in);
}



#endif