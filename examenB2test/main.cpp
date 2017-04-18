#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include <algorithm>
#include <cstring>

using namespace std;

class BooleanExp
{
public:
    virtual bool eval() = 0;
};

class Constant : public BooleanExp
{
public:
    Constant(bool aValue)
        :mValue(aValue)
    {
    }

    bool eval() override
    {
        return mValue;
    }
private:
    bool mValue;
};
//a && b
class AndExp : public BooleanExp
{
public:
    AndExp(BooleanExp * aFirst, BooleanExp * aSecond)
        :mFirst(aFirst)
        ,mSecond(aSecond)
    {
    }

    bool eval() override
    {
        return mFirst->eval() && mSecond->eval();
    }
private:
    BooleanExp * mFirst; //a
    BooleanExp * mSecond;// b

};

class OrExp : public BooleanExp
{
public:
    OrExp(BooleanExp * aFirst, BooleanExp * aSecond)
        :mFirst(aFirst) ,mSecond(aSecond)
    {
    }

    bool eval() override
    {
        return mFirst->eval() || mSecond->eval();
    }
private:
    BooleanExp * mFirst; //a
    BooleanExp * mSecond;// b

};

class NotExp : public BooleanExp
{
public:
    NotExp(BooleanExp * aExp)
        :mExp(aExp)
    {
    }

    bool eval() override
    {
        return !mExp->eval();
    }
private:
    BooleanExp * mExp;
};

class VariableExp : public BooleanExp{
private:
    char *a;
public:
    VariableExp(char* b){
        a = new char [strlen(b)];
        strcpy(a,b);
    }
    inline char* getVar(){
        return a;
    }

    bool eval(){
        return true;
    }
};

class Context:public VariableExp{
private:
    bool value;
public:
    Context(char* a, bool val):VariableExp(a),value(val){}

};

int main()
{
    /*
    BooleanExp * const1 = new Constant(true);
    BooleanExp * const2 = new Constant(false);

    BooleanExp * andExp = new AndExp(const1, const2);

    cout << andExp->eval();
    */

    BooleanExp *expr;
    VariableExp *x,*y,*z;
    x = new VariableExp("x");
    y = new VariableExp("y");
    z = new VariableExp("z");

    expr = new AndExp(new OrExp(x,y), new OrExp(new Constant(false),new NotExp(z)));
    cout<<expr->eval();


    return 0;
}
