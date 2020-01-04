#ifndef MATRIX
#define MATRIX
#include "Util.hpp"
class Matrix
{
    public:
        int row,col;
        vector < vector <double> > mat;
    
        Matrix()
        {
        row=0;
        col=0;
        }
        Matrix(int r,int c)
        {
            row=r;
            col=c;
            //Resizing Vector
            mat.resize(row);
            for(int i=0;i<row;i++)
                mat[i].resize(col);
            //Setting Random values
            for(int i=0;i<row;i++)
                for(int j=0;j<col;j++)
                    mat[i][j]=GetRandomNum();
        }
        Matrix(int r,int c,double v)
        {
            row=r;
            col=c;
            //Resizing Vector
            mat.resize(row);
            for(int i=0;i<row;i++)
                mat[i].resize(col);
            for(int i=0;i<row;i++)
                for(int j=0;j<col;j++)
                    mat[i][j]=v;
        }
        Matrix(vector<double> d)
        {
            row=d.size();
            col=1;
            mat.resize(row);
            for(int i=0;i<row;i++)
                mat[i].resize(col);
            for(int i=0;i<row;i++)
                mat[i][0]=d[i];
        }
        Matrix Transpose();
        Matrix Multiply(Matrix);
        Matrix Power(int p);
        Matrix operator+(Matrix);
        Matrix operator-(Matrix);
        Matrix MultiplySame(Matrix );
        Matrix Normalize();
        double GetAvgError();
        double GetLoss();
        Matrix ScalerMultiply(double);
        Matrix ApplyActivationFunction(double);
        Matrix ApplyDActivationFunction();
        void PrintAsVector();
        void PrintMatrix();
        double CalculateAccuracy(Matrix);
};
double Matrix::CalculateAccuracy(Matrix t)
{
    
    Matrix o=Transpose();
    Matrix target=t.Transpose();
    if(distance(o.mat[0].begin(),max_element(o.mat[0].begin(),o.mat[0].end()))==distance(target.mat[0].begin(),max_element(target.mat[0].begin(),target.mat[0].end())))
        return 1;
    else 
        return 0;
}
Matrix Matrix::Transpose()
{
    Matrix transposed(col,row);
    for(int i=0;i<transposed.row;i++)
        for(int j=0;j<transposed.col;j++)
            transposed.mat[i][j]=mat[j][i];
    return transposed;
}
Matrix Matrix::Multiply(Matrix b)
{
    if(col!=b.row)
        {
            cout<<"\n\tERROR FROM 'X' !!!!"<<endl;
            return b;
        }
    Matrix mult(row,b.col,0);
    for(int i=0;i<row;i++)
        for(int j=0;j<b.col;j++)
            for(int k=0;k<col;k++)
                mult.mat[i][j]+=mat[i][k]*b.mat[k][j];
    return mult;
}
Matrix Matrix::MultiplySame(Matrix b)
{
    if(row!=b.row || col!=b.col)
    {
        cout<<"\n\tERROR FROM 'SAME MULTIPLY' !!!!!!"<<endl;
        return b;
    }
    Matrix mult(row,b.col,0);
    for(int i=0;i<row;i++)
        for(int j=0;j<b.col;j++)
            mult.mat[i][j]=mat[i][j]*b.mat[i][j];        
    return mult;
}
Matrix Matrix::Power(int p)
{
    Matrix res(row,col);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.mat[i][j]=pow(mat[i][j],p);
    return res;
}
Matrix Matrix::Normalize()
{
    Matrix res(row,col,0);
    for(int i=0;i<row;i++)
    {
        double norm_w;
        for(int j=0;j<col;j++)
        {
            norm_w+=abs(mat[i][j]);
        }
        for(int j=0;j<col;j++)
        {
            res.mat[i][j]=mat[i][j]/norm_w;
        }
    }
    return res;
}
Matrix Matrix::operator+(Matrix b)
{
    if(row!=b.row || col!=b.col)
        {
            cout<<"\n\tERROR FROM '+' !!!!!!"<<endl;
            return b;
        }
    Matrix res(row,col,0);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.mat[i][j]=mat[i][j]+b.mat[i][j];;
    return res;
}

Matrix Matrix::operator-(Matrix b)
{
    if(row!=b.row || col!=b.col)
        {
            cout<<"\n\tERROR FROM '-' !!!!!!"<<endl;
            return b;
        }
    Matrix res(row,col,0);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.mat[i][j]=mat[i][j]-b.mat[i][j];;
    return res;
}
double Matrix::GetAvgError()
{
    double err=0;
    for(int i=0;i<row;i++)
        {
        double d=mat[i][0];
        err+=abs(d);
        }
    return err/row;
}
double Matrix::GetLoss()
{
    double loss=0;
    for(int i=0;i<row;i++)
        {
        double d=mat[i][0];
        loss+=0.5*pow(d,2);
        }
    return loss;
}
Matrix Matrix::ScalerMultiply(double x)
{
    Matrix res(row,col);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.mat[i][j]=mat[i][j]*x;
    return res;
}
Matrix Matrix::ApplyActivationFunction(double bias)
{
    Matrix res(row,col);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.mat[i][j]=ActivationFunction(mat[i][j]+bias);
    return res;
}
Matrix Matrix::ApplyDActivationFunction()
{    
    Matrix res(row,col);
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            res.mat[i][j]=DActivationFunction(mat[i][j]);
    return res;
}
void Matrix::PrintAsVector()
{
    for(int i=0;i<row;i++)
        printf("%lf ",mat[i][0]);
}
void Matrix::PrintMatrix()
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            printf("%lf\t",mat[i][j]);
        }
        cout<<endl;
    }
}
#endif