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
            else if(data[i]=='c')
            {
                i+=4;
                ans.push_back({1,0,0});
            }
            else if (data[i]=='s')
            {
                i+=7;
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
                ans.push_back({2,a,b});
            }
            i++;
        }
    }
    infile.close();
    return ans;
}
vector<vector<int>> get_random_input(vector<vector<int>>nums)
{
    vector<vector<int>>ans;
    for(int i=0;i<nums.size();i++)
    {
        if(nums[i][0]==0)
        {
            int a=nums[i][1];
            int b=nums[i][2];
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(a, b);
            int var=distrib(gen)%(b-a+1)+a;
            ans.push_back({0,var});
        }
        else if(nums[i][0]==1)
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(0, 130);
            int var=distrib(gen)%26+65+distrib(gen)%2*32;
            ans.push_back({1,var});
        }
        else if(nums[i][0]==2)
        {
            int a=nums[i][1];
            int b=nums[i][2];
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(a, b);
            int var=distrib(gen)%(b-a+1)+a;
            vector<int>tmp;
            tmp.push_back(2);
            for(int l=0;l<var;l++)
            {
                uniform_int_distribution<> distrib1(0, 130);
                int var1=distrib1(gen)%26+65+distrib1(gen)%2*32;
                tmp.push_back(var1);
            }
            ans.push_back(tmp);
        }
    }
    return ans;
}
int main(int argc,char* argv[])
{
    string pos;
    pos=argv[1];
    // pos="testin.txt";
    vector<vector<int>>tmp;
    tmp=read_file(pos);
    vector<vector<int>>tmp1;
    tmp1=get_random_input(tmp);
    for(int i=0;i<tmp1.size();i++)
    {
        if(tmp1[i][0]==0) cout<<tmp1[i][1]<<endl;
        else if(tmp1[i][0]==1) cout<<char(tmp1[i][1])<<endl;
        else if(tmp1[i][0]==2)
        {
            string res;
            for(int o=1;o<tmp1[i].size();o++)
            {
                res.push_back(char(tmp1[i][o]));
            }
            cout<<res<<endl;
        }
    }
    return 0;
}