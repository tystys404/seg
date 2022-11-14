#include<iostream>
#include<vector>
#include<string>
#include<map>
#include <fstream>
#include <iostream>
#include<random>
#include<stdio.h>
#include<string.h>
using namespace std;
vector<vector<int>> read_file(string pos)
{
    vector<vector<int>>ans;
    char data[100];
    ifstream infile;
    infile.open(pos,ios::in);
    while(infile.getline(data,100))
    {
        int i=0;
        while(i<100)
        {
            if(data[i]=='i')
            {
                i+=4;
                int a=0;
                while(1)
                {
                    if(data[i]<='9'&&data[i]>='0')
                    {
                        a=a*10+int(data[i]-'0');
                        i++;
                    }
                    else if(data[i]==',') 
                    {
                        i++;
                        break;
                    }
                }
                int b=0;
                while(1)
                {
                    if(data[i]<='9'&&data[i]>='0')
                    {
                        b=b*10+int(data[i]-'0');
                        i++;
                    }
                    else if(data[i]==')') 
                    {
                        i++;
                        break;
                    }
                }
                ans.push_back({0,a,b});
            }
            i++;
        }
    }
    infile.close();
    return ans;
}
vector<int> get_random_input(vector<vector<int>>nums)
{
    vector<int>ans;
    for(int i=0;i<nums.size();i++)
    {
        int a=nums[i][1];
        int b=nums[i][2];
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(a, b);
        int var=distrib(gen)%b+a;
        ans.push_back(var);
    }
    return ans;
}
int main()
{
    string pos;
    pos="input/4A/stdin_format.txt";
    vector<vector<int>>tmp;
    tmp=read_file(pos);
    vector<int>tmp1;
    tmp1=get_random_input(tmp);
    for(int i=0;i<tmp1.size();i++)
    {
        cout<<tmp1[i]<<" ";
    }
    cout<<endl;
    return 0;
}