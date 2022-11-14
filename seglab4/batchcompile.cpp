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
    string pos;
    vector<string>menu({"4A/","50A/"});
    for(int l=0;l<menu.size();l++)
    {
        vector<string>filenames;
        pos="input/"+menu[l]+"filename.txt";
        filenames=read_names(pos);
        for(int i=0;i<filenames.size();i++)
        {
            string tmp=filenames[i];
            string tmp1="input/"+menu[l]+tmp+".cpp";
            string tmp2="input/"+menu[l]+tmp+".out";
            cout<<tmp1<<" "<<tmp2<<endl;
            string cmmd="g++ "+tmp1+" -o "+tmp2;
            cout<<cmmd;
            char res[1024]={};
            const char* cmd=cmmd.c_str();
            executeCMD(cmd, res);
        }
    }
    return 0;
}