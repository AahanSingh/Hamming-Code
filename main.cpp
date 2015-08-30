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
    /* Partiy bit 'i' is at position 2^(i-1). eg- P2 is at position 2^(1)=2.
     Since strings start at index 0, the position of parity bit is subtracted by 1.
    */
    int j=0;
    int n=0;
    for(int i=pow(2,p)-1;i<cw.length();i=j+p+1) // This loop is to traverse the entire code word.
    /*  After checking the current 'n' bits for the parity bit at 'n'th
        position the next n bits must be skipped. 
        Explaination of the loop update condition:
            p -> parity bit 'p'
            j -> index of last of the 'p' bits that must be checked to set the 'p'th parity bit
            +1 -> since strings start from 0 index
            Thus p+j+1 skips the next p+1 bits
    */
    {
        
        for(j=i;j<(i+pow(2,p));j++) // This loop is to traverse the next n bits to check for parity for the nth parity bit
        {
            /*
                Explaination of the loop check condition:
                    The 'n'th parity bit is at postion 2^(n-1). [eg. 2nd parity bit is at position 2^(1)=2]
                    To set this bit the next 2^(n-1) bits must be checked for even parity.
                    The value of 'p' being sent to this function is already reduced by 1. Thus 'p' is already
                    n-1 for the 'n'th parity bit.
             */
            if((char)(cw[j])=='1')//Checking for even parity
                n++;
        }
    }
    if(n%2==0)
        cw.replace(pow(2,p)-1,1,"0");//If even parity set the parity bit to 0
    else
        cw.replace(pow(2,p)-1,1,"1");//else set parity bit to 1
}
string reverse(string s)//Reversing a string
{
    string copy;
    long int x=s.length()-1;
    for(int i=0;i<s.length();i++)
        copy+=s[x--];
    return copy;
}
bool checkParity(int p,string s)
{
    /*
        This function checks if the pth parity bit is of even parity
        or of odd parity.
     */
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
    /*
     This function checks if the received code word is correct or not. If it is incorrect the bit positon of
     the error is detected and corrected.
     */

    if(x.compare(s)==0)
        return;
    
    int n=0;    //'n' stores the position of the error bit
    s=reverse(s);
    for(int i=0;i<p;i++)
    {
        if(checkParity(i,s)==false) // If the pth parity bit if of odd parity then
            n+=(pow(2,i));          // the index of that parity bit must be added to 'n' in order to
    }                               // find out the position of the bit received incorrectly.
    if(n!=0) // If all parity bits are of even parity then 'n' is 0 thus the received code word is correct. If not then received code
    {       // word is wrong.
        cout<<"\nRECEIVED CODE WORD INCORRECT\n";
        int pos=n;
        cout<<"BIT: "<<pos<<" AT ERROR\n";
        if((char)(s[pos-1])=='0')   // If incorrect bit is received as 0 flip it to 1.
            s.replace(pos-1,1,"1");
        else                        // If incorrect bit is received as 1 flip it to 0.
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
    for(int i=0;i<cw.length();i++)  // Creating code word with the indexes of the parity bits set to 'x'.
    {                               // The other bits contain the data word.
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
