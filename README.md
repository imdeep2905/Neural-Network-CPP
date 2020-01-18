# Basic Feed Forward Neural Network Library in C++
Before starting,this library is based on book **Make Your Own Neural Network by Tariq Rashid**\
[Check out this book](https://kupdf.net/download/make-your-own-neural-network-tariq-rashid-chb-books_598f6fe5dc0d60e932300d19_pdf)
## How to Use ?
First Include main header (i.e. ```NN.hpp```):
```
#include "Headers\NN.hpp"
``` 
Now you can use number of functionalities of this header file.Let us look them one by one.
### Create Network using constructor:
In ```NN.hpp``` there is also a class named NN and it's constructor has following form:
```
NN({list of neurons in each layer seprated by commas} , activation function , learning rate , epochs)
```
For example this will create object n of class NN with 3 layers (having 2,4 and 2 neurons respectively),```sigmoid``` as an activation function,```0.1``` learning rate and ```1500``` epochs.\
Note that every layer will have sigmoid as an activation function.
```
NN n({2,4,2},"sigmoid",0.1,1500);
```
You can have one of these activation functions:
```
Sigmoid
Tanh
Relu
Softplus
```
### Train Network:
To train Network NN class have function named **Fit**.\
You can use it in following manner:
```
n.Fit(file_name);
```
Note that all values in file should be space seprated and each new line should contain new training data.\
For Example:
```
NN n({2,4,2},"sigmoid",0.1,1500);
cout<<n.Fit("XOR.txt")<<endl; //This will display accuracy.
```
Note that accuracy is measured by argmax(It is genrally used in classification problems).
Contents of **XOR.txt** Should be like:
```
0 0 0.98 0.01
0 1 0.01 0.98
1 0 0.01 0.98
1 1 0.98 0.01
```
First two values are considered as a input and last two values are considered as output.\
Because we have **2,4,2 Formation (2-Input 4-Hidden 2-Output)**.
I know it is little hactic because most of the training available is usually in ```.csv``` File.\
But i'll try to add ```.csv``` support in future.
### Test Network:
To test Network NN class have function named **Test**.\
You can use it in following manner:
```
n.Test(file_name);
```
Again this file should have same format as mentioned before.
```
cout<<n.Fit("XOR.txt")<<endl; //This will display accuracy on test data.
```
### Save and Load Model:
##### To Save Model:
```
n.SaveModel();
```
This will automatically create file name and save it in ```.model``` file.\
You can rename this file as per your convenience.
##### To Load Model:
```
n.LoadModel(file_name);
```
file should be ```.model``` which was earlier saved.\
You can Directly load Model and skipping constructor step.\
For Example:\
```
NN n();
n.LoadModel();
```
This will Load pre trained Model.
## Conclusion
If you face any issues inform me via **Issues Section**. I'll try my best to resolve it.
Thanks for Reading this XD.
