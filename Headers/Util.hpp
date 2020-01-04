#ifndef UTIL
#define UTIL
//Includation of std. Header files
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <cmath>
#include <ctime>
#include <fstream>
#define ll long long
using namespace std;
//Utility functions which we will use furthur
double (*ActivationFunction)(double);
double (*DActivationFunction)(double);
double Sigmoid(double x)
{
    return 1/(1+exp(-x));
}
double DSigmoid(double x)
{
    return x*(1-x);
}
double Relu(double x)
{
    if(x>=0)
        return x;
    return 0;
}
double DRelu(double x)
{
    if(x<=0)
        return 0;
    return 1;
}
double Tanh(double x)
{
    return 2/(1+exp(-2*x))-1;
}
double DTanh(double x)
{
    return 1-(x*x);
}
double SoftPlus(double x)
{
    return log(1+exp(x));
}
double DSoftPlus(double x)
{
    double temp=exp(x);
    temp=1/(temp-1);
    return 1/(1+temp);
}
double GetRandomNum()
{
    srand(time(nullptr)+rand()); 
    double num=rand()%13;//Prime number for better distribution of random numbers
    while(num>0.005)
        num/=2.1;
    return num;
}
void SetFunctions(string f)
{
    std::for_each(f.begin(), f.end(), [](char & c){
	c = ::tolower(c);});
    if(f=="sigmoid")
    {
        ActivationFunction=Sigmoid;
        DActivationFunction=DSigmoid;
    }
    else if(f=="relu")
    {
        ActivationFunction=Relu;
        DActivationFunction=DRelu;
    }
    else if(f=="tanh")
    {
        ActivationFunction=Tanh;
        DActivationFunction=DTanh;
    }
    else 
    {
        cout<<"ERROR : Invalid Function Argument , Default Set : <Sigmoid >"<<endl;
        ActivationFunction=Sigmoid;
        DActivationFunction=DSigmoid;
    }
}
#endif