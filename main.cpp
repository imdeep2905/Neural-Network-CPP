/*  
@author RDP
*/
#include "Headers\NN.hpp"
using namespace std;
int main()
{
   /*Constructor
   NN({n1,n2...nn} - number of neurons in each layer, 
   activationfunction , learning rate , epochs )
   */
   //Formation for XOR
   NN n({2,4,2},"sigmoid",0.1,1500);
   cout<<n.Fit("XOR.txt")<<endl;
   cout<<n.Test("XOR.txt")<<endl;
   n.SaveModel();
   /*
    To load model 
   n.LoadModel("XOR.model");
   cout<<n.Test("XOR.txt")<<endl;
   */
   return 0;
}
