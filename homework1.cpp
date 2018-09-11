#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void homework(string fileName)
{

    float Dx[100];
    float Dy[100];
    int Dsize = 0;
    ifstream input(fileName);
    if (input.is_open())
    {
        while(!input.eof()){
            string number;
            float data;
            float data2;
            char delimiter = ' ';
            getline(input, number);
            input >> data >> delimiter >> data2;
            Dx[Dsize] = data;
            Dy[Dsize] = data2;
            Dsize++;
        }
    }

    float Error[Dsize];
    float average = 0;
    float total = 0;

    for (int i = 0; i < Dsize; i++)
    {
        float n = Dsize-1;
        float Tx = 0;
        float Ty = 0;
        float Beta = 0;
        float Alpha = 0;
        float sumXY = 0;
        float sumX = 0;
        float sumY = 0;
        float sumXX = 0;
        float yHat = 0;

        for (int j = 0; j < Dsize; j++)
        {

            if (i == j)
            {
                Tx = Dx[i];
                Ty = Dy[j];
            }
            else
            {
                sumXY = Dx[i]*Dy[i] + sumXY;
                sumX = Dx[i] + sumX;
                sumY = Dy[i] + sumY;
                sumXX = Dx[i]*Dx[i] + sumXX;
            }

            Beta = (n*sumXY - sumX*sumY) / (n*sumXX - (sumX*sumX));
            Alpha = (sumY - Beta*sumX) / n;
            yHat = Alpha + Beta*Tx;
            if (Ty >= yHat)
                Error[i] = Ty - yHat;
            else if ((n*sumXX - (sumX*sumX)) == 0 || n == 0)
                Error[i] = 0;
            else
                Error[i] = yHat - Ty;
        }
    }

    for (int i = 0; i < Dsize; i++)
    {
        total = Error[i] + total;
    }
    average = total / Dsize;
    cout << fileName << "'s average of errors: " << average <<endl;
    input.close();
}

int main ()
{
    homework("Unemployment.csv");
    homework("Fire and Theft.csv");
    homework("Insurance.csv");
    return 0;
}