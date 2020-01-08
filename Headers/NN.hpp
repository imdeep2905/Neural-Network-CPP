#ifndef _NN_
#define _NN_
#include "Matrix.hpp"
using namespace std;
class NN
{
    private:
        Matrix * layers;
        Matrix * edges;
        Matrix * errors;
        Matrix biases;
        double learning_rate;
        int layers_in_NN;
        int epochs;
        string af_saved;
    public:
        NN()
        { 
            ;
        }
        NN(vector<int> v,string af,double lr,int e=1)
        {
            af_saved=af;
            SetFunctions(af);
            //Setting up Network
            learning_rate=lr;
            layers_in_NN=v.size();
            epochs=e;
            layers=new Matrix[v.size()];
            edges=new Matrix[v.size()-1];
            errors=new Matrix[v.size()];

            biases=Matrix(v.size()-1,1);

            for(int i=0;i<layers_in_NN;i++)
            {
                layers[i]=Matrix(v[i],1,0);
                errors[i]=Matrix(v[i],1,0);
            }
            for(int i=0;i<layers_in_NN-1;i++)
            {
                edges[i]=Matrix(v[i+1],v[i]);
            }
            cout<<"\n\n \t\t NETWORK CONNECTION SUCCESS !!!!\n\n";
        }
        void PredictSingle(Matrix);
        void BackPropogation(Matrix);
        double Fit(string );
        double Test(string );
        void SaveModel();
        void LoadModel(string);
};
void NN::PredictSingle(Matrix inputs)
{
    layers[0]=inputs;
    for(int i=1;i<layers_in_NN;i++)
    {
        layers[i]=edges[i-1].Multiply(layers[i-1]);
        layers[i]=layers[i].ApplyActivationFunction(biases.mat[i-1][0]);
    }
}
void NN::BackPropogation(Matrix target)
{
    errors[layers_in_NN-1]=target-layers[layers_in_NN-1];
    for(int i=layers_in_NN-2;i>0;i--)
    {
        errors[i]=(edges[i].Transpose()).Multiply(errors[i+1]);
    }
    for(int i=layers_in_NN-2;i>=0;i--)
    {
        Matrix grad;
        grad=errors[i+1];
        grad=grad.ScalerMultiply(learning_rate);
        grad=grad.MultiplySame(layers[i+1].ApplyDActivationFunction());
        grad=grad.Multiply(layers[i].Transpose());
        edges[i]=edges[i]+grad;
        //grad.PrintMatrix();
        //_sleep(5000);
        //biases[i][0]+=; // Bias is remaining
    }
}
double NN::Fit(string file_name)
{
    cout<<"Now Training Model ... "<<endl;
    ll total=0,right=0;
    vector <double> input,target;
    Matrix predicted;
    ifstream in_file;
    input.resize(layers[0].row);
    target.resize(layers[layers_in_NN-1].row);
    for(int ie=0;ie<epochs;ie++)
    {
        auto start=chrono::steady_clock::now();
        total=0;
        right=0;
        in_file.open(file_name.c_str());
        while(!in_file.eof())
        {
            total++;
            for(double &x:input)
                in_file>>x;
            for(double &x:target)
                in_file>>x;
            PredictSingle(Matrix(input));
            double acc=layers[layers_in_NN-1].CalculateAccuracy(Matrix(target));
            BackPropogation(Matrix(target));
            if(acc==1)
                right++;    
         //   cout<<errors[layers_in_NN-1].GetLoss()<<endl;
           // if(total%1000==0)
            // cout<<double(right)/double(total)<<endl;
        }
        in_file.close();
        auto stop=chrono::steady_clock::now();
        auto diff=stop-start;
        printf("Epoch No. %d Completed. Accuracy : %lf ",ie+1,double(right)/double(total));
        cout<<"(Completed In : "<<(chrono::duration <double, milli> (diff).count())/1000<<" Seconds ) "<<endl;
    }
    return double(right)/double(total);
}
double NN::Test(string file_name)
{
    cout<<"Now Testing Model ..."<<endl;
    ll total=0,right=0;
    vector <double> input,target;
    Matrix predicted;
    ifstream in_file;
    input.resize(layers[0].row);
    target.resize(layers[layers_in_NN-1].row);
    total=0;
    right=0;
    in_file.open(file_name.c_str());
    auto start=chrono::steady_clock::now();
        while(!in_file.eof())
        {
            total++;
            for(double &x:input)
                in_file>>x;
            for(double &x:target)
                in_file>>x;
            PredictSingle(Matrix(input));
           // errors[layers_in_NN-1]=Matrix(target)-layers[layers_in_NN-1];
            if(layers[layers_in_NN-1].CalculateAccuracy(Matrix(target))==1)
                right++;    
            //if(total==10)
            //   break;
        }
        auto stop=chrono::steady_clock::now();
        auto diff=stop-start;
        cout<<"Testing Done !!! Accuracy : "<<double(right)/double(total);
        cout<<" (Completed In : "<<(chrono::duration <double, milli> (diff).count())/1000<<" Seconds ) "<<endl;
        in_file.close();
    return double(right)/double(total);
}
void NN::SaveModel()
{
    time_t my_time = time(NULL); 
    string time= ctime(&my_time);
    replace(time.begin(),time.end(),' ','_');
    replace(time.begin(),time.end(),'\n','-');
    replace(time.begin(),time.end(),':','-');
    string file_name=time+"-Saved_Model.model";
    ofstream model;
    model.open(file_name.c_str());    
    model.clear();
    //Saving Network Formation
    model<<af_saved<<endl;
    model<<layers_in_NN<<" ";
    for(int i=0;i<layers_in_NN;i++)
        model<<layers[i].row<<" ";
    model<<endl;
    //Saving learning rate ,epochs
    model<<learning_rate<<" "<<epochs<<endl;
    //Saving edges
    for(int i=0;i<layers_in_NN-1;i++)
    {
        model<<edges[i].row<<" "<<edges[i].col<<endl;
        for(int j=0;j<edges[i].row;j++)
        {
            for(int k=0;k<edges[i].col;k++)
            {
                model<<edges[i].mat[j][k]<<" ";
            }
            model<<endl;
        }
    }
    //Saving biases
    for(int i=0;i<layers_in_NN-1;i++)
        model<<biases.mat[i][0]<<" ";
    model<<endl;
    cout<<"Model Saved Successfully in file : \""<<file_name<<"\""<<endl;
    cout<<"\n\tTIP : You should rename this file so, you can provide your convenient name as an argument in LoadModel function.\n"<<endl;
    model.close();
}
void NN::LoadModel(string file_name)
{
    int a,b;
    double d;
    ifstream model(file_name.c_str());
    model>>af_saved;
    SetFunctions(af_saved);
    model>>layers_in_NN;
    layers=new Matrix[layers_in_NN];
    edges=new Matrix[layers_in_NN-1];
    errors=new Matrix[layers_in_NN];
    biases=Matrix(layers_in_NN-1,1);
    for(int i=0;i<layers_in_NN;i++)
    {
        model>>a;
        layers[i]=Matrix(a,1,0);
        errors[i]=Matrix(a,1,0);
    }
    model>>learning_rate;
    model>>epochs;
    for(int i=0;i<layers_in_NN-1;i++)
    {
        model>>a;
        model>>b;
        edges[i]=Matrix(a,b);
        for(int j=0;j<a;j++)
        {
            for(int k=0;k<b;k++)
            {
                model>>d;
                edges[i].mat[j][k]=d;
            }
        }
    }
    for(int i=0;i<layers_in_NN-1;i++)
    {
        model>>d;
        biases.mat[i][0]=d;
    }
    model.close();
    cout<<"Model loaded Successfully !!! "<<endl;
}
#endif
