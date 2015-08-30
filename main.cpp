//
//  main.cpp
//  Hamming Code: Detection & Correction
//
//  Created by Aahan Singh on 30/08/15.
//  Copyright (c) 2015 Aahan Singh. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
#include <math.h>
void setParity(int p, string &cw)
{
    int j=0;
    int n=0;
    for(int i=pow(2,p)-1;i<cw.length();i=j+p+1)
    {
        for(j=i;j<(i+pow(2,p));j++)
        {
            if((char)(cw[j])=='1')
                n++;
        }
    }
    if(n%2==0)
        cw.replace(pow(2,p)-1,1,"0");
    else
        cw.replace(pow(2,p)-1,1,"1");
}
string reverse(string s)
{
    string copy;
    long int x=s.length()-1;
    for(int i=0;i<s.length();i++)
        copy+=s[x--];
    return copy;
}
bool checkParity(int p,string s)
{
    int j=0;
    int n=0;
    for(int i=pow(2,p)-1;i<s.length();i=j+p+1)
    {
        for(j=i;j<(i+pow(2,p));j++)
        {
            if((char)(s[j])=='1')
                n++;
        }
    }
    if(n%2==0)
        return true;
    else
        return false;

}
void checkRw(string s,int p,string x)
{
    if(x.compare(s)==0)
        return;
    
    int n=0;
    s=reverse(s);
    for(int i=0;i<p;i++)
    {
        if(checkParity(i,s)==false)
            n+=(pow(2,i));
    }
    if(n==0)
        cout<<"RECEIVED CODE WORD CORRECT\n";
    else
    {
        cout<<"WRONG RECEIVED CODE WORD\n";
        int pos=n;
        cout<<"BIT: "<<pos<<" AT ERROR\n";
        if((char)(s[pos-1])=='0')
            s.replace(pos-1,1,"1");
        else
            s.replace(pos-1,1,"0");
        s=reverse(s);
        cout<<"CORRECTED CODE WORD: "<<s<<"\n";
    }
}
int main(int argc, const char * argv[])
{
    cout<<"ENTER THE DATA WORD\n";
    string dw;
    cin>>dw;
    int p=0;
    while(true){
        if(pow(2,p)>(dw.length()+p))
            break;
        else
            p++;
    }
    string cw;
    int flag=0;
    int count=0;
    for(int i=0;i<dw.length()+p;i++)
        cw+="0";
    dw=reverse(dw);
    for(int i=0;i<cw.length();i++)
    {
        if((pow(2,flag)-1)==i)
        {
            cw.replace(i, 1, "x");
            flag++;
        }
        else
        {
            cw[i]=dw[count];
            count++;
        }
    }

    for(int i=0;i<p;i++)
        setParity(i, cw);

    cout<<"\nHAMMING CODE WORD: "<<reverse(cw)<<"\n";
    
    cout<<"ENTER RECEIVED CODE WORD:\n";
    string rw;
    cin>>rw;
    if(cw.compare(reverse(rw))==0)
        cout<<"RECEIVED CODE WORD CORRECT";
    else
        checkRw(rw,p,cw);
}
