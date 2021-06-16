/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on June 2nd, 2021, 8:11 AM
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <stack>
using namespace std;

float h(float);
float g(float);

int main(int argc, char** argv) {
    //Testing out recursive trig functions
    std::stack<float> anglesSin;
    std::stack<float> anglesSinCos;
    for(int i{}; i < 90;i++)
    {
      anglesSinCos.push(i);
    }
    for(int i{-90}; i < 0;i++)
    {
      anglesSin.push(i);
    }
    


    for(int i{-90}; i < 90;i++)
    {
      if(i>-1)
      {
        float angDeg = anglesSinCos.top();
        float angRad=angDeg*atan(1)/45;
        cout<<"Angle = "<<angDeg<<" sinh = "<<sinh(angRad)<< " our h = "<<h(angRad)<<endl;
        cout<<"Angle = "<<angDeg<<" cosh = "<<cosh(angRad)<< " our g = "<<g(angRad)<<endl;
        anglesSinCos.pop();

      }
      else
      {
        float angDeg = anglesSin.top();
        float angRadSin=angDeg*atan(1)/45;
        float angDegC = anglesSinCos.top();
        float angRadC=  angDegC*atan(1)/45;
        cout<<"Angle = "<<angDeg<<" sinh = "<<sinh(angRadSin)<< " our h = "<<h(angRadSin)<<endl;
        cout<<"Angle = "<<angDeg<<" cosh = "<<cosh(angRadC)<< " our g = "<<g(angRadC)<<endl;

        anglesSin.pop();
        anglesSinCos.push(anglesSinCos.top());
        anglesSinCos.pop();
      }
      
    }
    
    //Exit stage right
    return 0;
}

float h(float angR){
    float tol=1e-6;
    if(angR>-tol&&angR<tol)return angR+angR*angR*angR/6;
    return 2*h(angR/2)*g(angR/2);
}
float g(float angR){
    float tol=1e-6;
    if(angR>-tol&&angR<tol)return 1+angR*angR/2;
    float b=h(angR/2);
    return 1+2*b*b;
}
