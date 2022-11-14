#include<iostream>
#include<vector>
#include<string>
#include<map>
#include <fstream>
#include<sstream>
#include <iostream>
#include<random>
#include<stdio.h>
#include<string.h>
using namespace std;
string readFileIntoString(string filename)
{
    ifstream ifile(filename);
    //将文件读入到ostringstream对象buf中
    ostringstream buf;
    char ch;
    while(buf&&ifile.get(ch))
    buf.put(ch);
    //返回与流对象buf关联的字符串
    return buf.str();
}
vector<string> read_names(string pos)
{
    string data;
    data=readFileIntoString(pos);
    vector<string>names;
    names.push_back("");
    int flag=1;
    int j=0;
    for(int i=0;i<data.size();i++)
    {
        // if(data[i]=='\n') cout<<endl;
        // cout<<data[i];
        if(data[i]=='\n')
        {
            flag=1;
            names.push_back("");
            j++;
        }
        else if(data[i]=='.')
        {
            flag=0;
        }
        else if(flag==1)
        {
            names[j].push_back(data[i]);
        }
    }
    for(int k=0;k<names.size();k++)
        {
            for(int l=0;l<names[k].size();l++)
            {
                cout<<names[k][l];
            }
            cout<<endl;
        }
    return names;
}
void executeCMD(const char *cmd, char *result)
{
    char buf_ps[1024];
    char ps[1024]={0};
    FILE *ptr;
    strcpy(ps, cmd);
    if((ptr=popen(ps, "r"))!=NULL)
    {
        while(fgets(buf_ps, 1024, ptr)!=NULL)
        {
//	       可以通过这行来获取shell命令行中的每一行的输出
//	   	   printf("%s", buf_ps);
           strcat(result, buf_ps);
           if(strlen(result)>1024)
               break;
        }
        pclose(ptr);
        ptr = NULL;
    }
    else
    {
        printf("popen %s error\n", ps);
    }
}
int main()
{
    vector<string>menu({"4A/","50A/"});
    for(int l=0;l<menu.size();l++)
    {
        string pos;
        vector<string>filenames;
        pos="input/"+menu[l]+"filename.txt";
        filenames=read_names(pos);
        string pos1;
        pos1="input/"+menu[l]+"stdin_format.txt";
        for(int i=0;i<filenames.size()-1;i++)
        {
            for(int j=i+1;j<filenames.size();j++)
            {
                string tmp1=filenames[i];
                string tmp2=filenames[j];
                if(tmp2==""||tmp1=="") continue;
                bool flag=1;
                for(int k=0;k<50;k++)
                {
                    string cmmd1="./randominput.out "+pos1+" >randomin.txt";
                    char res1[1024]={};
                    const char* cmd1=cmmd1.c_str();
                    executeCMD(cmd1,res1);
                    string cmmd2="./input/"+menu[l]+tmp1+".out "+" <randomin.txt";
                    char res2[1024]={};
                    const char* cmd2=cmmd2.c_str();
                    executeCMD(cmd2, res2);
                    string cmmd3="./input/"+menu[l]+tmp2+".out "+" <randomin.txt";
                    char res3[1024]={};
                    const char* cmd3=cmmd3.c_str();
                    executeCMD(cmd3, res3);
                    string ans2=string(res2);
                    string ans3=string(res3);
                    cout<<res2<<" "<<res3<<endl;
                    if(ans2==ans3) cout<<"yes"<<endl;
                    else
                    {
                        cout<<"no"<<endl;
                        flag=0;
                        break;
                    }
                }
                if(flag==1)
                {
                    ofstream ofm;
                    ofm.open("equal.csv",ios::app);
                    ofm<<"input/"+menu[l]+tmp1 +".cpp"<<" "<< "input/"+menu[l]+tmp2+".cpp"<<endl;
                    ofm.close();
                }
                else
                {
                    ofstream ofm;
                    ofm.open("inequal.csv",ios::app);
                    ofm<<"input/"+menu[l]+tmp1 +".cpp"<< " "<<"input/"+menu[l]+tmp2+".cpp"<<endl;
                    ofm.close();
                }
                
            }
        }
    }
    return 0;
}