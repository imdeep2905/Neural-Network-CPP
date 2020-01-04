/*  
@author RDP
*/
#include "Headers\NN.hpp"
using namespace std;
int main()
{
   NN n({784,200,10},"tanh",0.3,1);
   cout<<n.Fit("H:/ML/Neural_network_V2/MNIST_train.txt")<<endl;
   cout<<n.Test("H:/ML/Neural_network_V2/MNIST_test.txt")<<endl;
   n.SaveModel();
   
   //Constructor
   //NN({n1,n2...nn} , activationfunction , learning rate , epochs )
   // NN n({8,2,2},0.3,5);
   // cout<<n.Fit("H:/ML/Neural_network_V2/Test_datasets/HTRU2/HTRU_train.txt")<<endl;
   // cout<<n.Test("H:/ML/Neural_network_V2/Test_datasets/HTRU2/HTRU_test.txt")<<endl;
   // n.SaveModel();
   // n.LoadModel("HTRU.model");
   // cout<<n.Test("HTRU_test.txt")<<endl;   
    return 0;
}