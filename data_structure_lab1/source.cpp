#include <iostream>
#include <fstream>
using namespace std;

class Myarray
{
public:
    Myarray()
    {
        this->size = 0;
        this->arr = NULL;
    }
    void getsize()
    {
        cout << this->size << endl;
    }
    void setsize(int num)
    {
        this->size = num;
    }
    void inital_arr(int *p)
    {
        arr = new int[this->size];
        for (int i = 0; i < this->size; i++)
        {
            arr[i] = p[i];
        }
    }
    void show()
    {
        if (this->arr == NULL)
        {
            cout << "Error!!! You have not initialized your array yet!" << endl;
            return;
        }
        for (int i = 0; i < this->size; i++)
        {
            cout << this->arr[i] << " ";
        }
        cout << endl;
    }
    void push_back_x(int x)
    {
        if (this->arr == NULL)
        {
            cout << "Error!!! You have not initialized your array yet!" << endl;
            return;
        }
        int *newarr = new int[this->size + 1];
        for (int i = 0; i < this->size; i++)
        {
            newarr[i] = this->arr[i];
        }
        newarr[this->size] = x;
        this->size++;
        delete[] this->arr;
        this->arr = newarr;
        this->show();
    }
    void pop_back()
    {
        if (this->arr == NULL)
        {
            cout << "Error!!! You have not initialized your array yet!" << endl;
            return;
        }
        if (this->size == 0)
        {
            cout << "Error!!! Array is already empty!" << endl;
            return;
        }
        this->size--;
        this->show();
    }
    void insert(int pos, int x)
    {
        if (this->arr == NULL)
        {
            cout << "Error!!! You have not initialized your array yet!" << endl;
            return;
        }
        if(pos<=0||pos>this->size+1)
        {
            cout<<"Invalid index!!! please try another..."<<endl;
            return ;
        }
        int *newarr = new int[this->size + 1];
        for (int i = 0; i < pos - 1; i++)
        {
            newarr[i] = this->arr[i];
        }
        for (int i = this->size; i > pos - 1; i--)
        {
            newarr[i] = this->arr[i - 1];
        }
        newarr[pos - 1] = x;
        this->size++;
        delete[] this->arr;
        this->arr = newarr;
        this->show();
    }
    void erase(int pos)
    {
        if (this->arr == NULL)
        {
            cout << "Error!!! You have not initialized your array yet!" << endl;
            return;
        }
        if(pos<=0||pos>this->size)
        {
            cout<<"Invalid index!!! please try another..."<<endl;
            return ;
        }
        for (int i = pos; i < this->size; i++)
        {
            this->arr[i - 1] = this->arr[i];
        }
        this->size--;
        this->show();
    }
    void update(int pos, int x)
    {
        if (this->arr == NULL)
        {
            cout << "Error!!! You have not initialized your array yet!" << endl;
            return;
        }
        if(pos<=0||pos>this->size)
        {
            cout<<"Invalid index!!! please try another..."<<endl;
            return ;
        }
        this->arr[pos - 1] = x;
        this->show();
    }
    void save(char *filename, int length)
    {
        if (this->arr == NULL)
        {
            cout << "Error!!! You have not initialized your array yet!" << endl;
            return;
        }
        char root[10] = "./output/";
        char *fullpath = new char[9 + length + 1];
        for (int i = 0; i < 9; i++)
        {
            fullpath[i] = root[i];
        }
        for (int i = 9; i < 9 + length; i++)
        {
            fullpath[i] = filename[i - 9];
        }
        fullpath[9 + length] = '\0'; 
        if (filename[length - 1] == 't')
        {
            ofstream fout(fullpath);
            fout << this->size << endl;
            for (int i = 0; i < this->size; i++)
            {
                fout << this->arr[i];
                if (i < this->size - 1)
                    fout << " ";
            }
            fout.close();
        }
        else
        {
            ofstream fout(fullpath, ios::binary);
            fout.write((char *)&this->size, sizeof(int));
            fout.write("\n", sizeof(char));
            for (int i = 0; i < this->size; i++)
            {
                fout.write((char *)&this->arr[i], sizeof(int));
                if (i < this->size - 1)
                    fout.write(" ", sizeof(char));
            }
            fout.close();
        }
        delete[] fullpath;
    }
    ~Myarray()
    {
        if (this->arr != NULL)
            delete[] this->arr;
    }

private:
    int size;
    int *arr;
};

/*
size
show
push_back x
pop_back
insert pos x
erase pos
update pos x
save filename
exit
*/

bool cmp(char* string1,char* string2,int length)
{
    for(int i=0;i<length;i++)
    {
        if(string1[i]!=string2[i]) return false;
    }
    return true;
}

int matching_mode(char *func_name, int size)
{
    if(size==4)
    {
        char func1[5]="size";
        char func2[5]="show";
        char func3[5]="save";
        char func4[5]="exit";
        if(cmp(func_name,func1,4)) return 1;
        else if(cmp(func_name,func2,4)) return 2;
        else if(cmp(func_name,func3,4)) return 8;
        else if(cmp(func_name,func4,4)) return 9;
        else return -1;
    }
    else if(size==5)
    {
        char func[6]="erase";
        if(cmp(func_name,func,5)) return 6;
        else return -1;
    }
    else if(size==6)
    {
        char func1[7]="insert";
        char func2[7]="update";
        if(cmp(func_name,func1,6)) return 5;
        else if(cmp(func_name,func2,6)) return 7;
        else return -1;
    }
    else if(size==8)
    {
        char func[9]="pop_back";
        if(cmp(func_name,func,8)) return 4;
        else return -1;
    }
    else if(size==9)
    {
        char func[10]="push_back";
        if(cmp(func_name,func,9)) return 3;
        else return -1;
    }
    else
    {
        return -1;
    }
}

int charToint(char *p, int size)
{
    int num = 0;
    for (int i = 0; i < size; i++)
    {
        num *= 10;
        num += (p[i] - '0');
    }
    return num;
}

int main()
{
    ifstream f;
    int flag = -1;
    cout << "请输入你想要打开的文件代码:1表示txt文件,2表示bin文件" << endl;
    cin >> flag;
    if (flag == 1)
        f.open("./input/exp1_example.txt", ios::in);
    else if (flag == 2)
        f.open("./input/exp1_example.bin", ios::binary);
    else
    {
        cout << "error" << endl;
        return 0;
    }
    Myarray my;
    if (!f.is_open())
    {
        cout << "文件没有成功打开哦!" << endl;
        return 0;
    }
    cout<<"open successfully !!!\n";
    int cur_size;
    if (flag == 1)
        f >> cur_size;
    else
        f.read((char *)&cur_size, sizeof(int));
    my.setsize(cur_size);
    int *p = new int[cur_size];
    if (flag == 1)
    {
        for (int i = 0; i < cur_size; i++)
        {
            f >> p[i];
        }
    }
    else
    {
        for (int i = 0; i < cur_size; i++)
        {
            f.read((char *)&p[i], sizeof(int));
        }
    }
    my.inital_arr(p);
    delete[] p;
    f.close();
    int loop_count=0;
    while (1)
    {
        char instruction[1000];
        cout << "请输入：" << endl;
        if(loop_count==0) cin.ignore();
        cin.getline(instruction, 1000);
        // cout<<instruction<<endl;
        char func_name[1000] = {0}, op1[1000] = {0}, op2[1000] = {0};
        int id1 = 0, id2 = 0, id3 = 0;
        int face_blank = 0;
        for (int i = 0; instruction[i] != '\0'; i++)
        {
            if (instruction[i] == ' ')
            {
                face_blank++;
                continue;
            }
            switch (face_blank)
            {
            case 0:
            {
                func_name[id1] = instruction[i];
                id1++;
                break;
            }
            case 1:
            {
                op1[id2] = instruction[i];
                id2++;
                break;
            }
            case 2:
            {
                op2[id3] = instruction[i];
                id3++;
                break;
            }
            }
        }
        switch (matching_mode(func_name, id1))
        {
        case 1:
        {
            // cout<<"1"<<endl;
            my.getsize();
            break;
        }
        case 2:
        {
            // cout<<"2"<<endl;
            my.show();
            break;
        }
        case 3:
        {
            // cout<<"3"<<endl;
            int val = charToint(op1, id2);
            my.push_back_x(val);
            break;
        }
        case 4:
        {
            // cout<<"4"<<endl;
            my.pop_back();
            break;
        }
        case 5:
        {
            // cout<<"5"<<endl;
            int pos = charToint(op1, id2);
            int val = charToint(op2, id3);
            my.insert(pos, val);
            break;
        }
        case 6:
        {
            // cout<<"6"<<endl;
            int pos = charToint(op1, id2);
            my.erase(pos);
            break;
        }
        case 7:
        {
            // cout<<"7"<<endl;
            int pos = charToint(op1, id2);
            int val = charToint(op2, id3);
            my.update(pos, val);
            break;
        }
        case 8:
        {
            // cout<<"8"<<endl;
            my.save(op1, id2);
            break;
        }
        case 9:
        {
            // cout<<"9"<<endl;
            cout << "程序运行结束" << endl;
            return 0;
        }
        default:
        {
            cout << "错误，请重新输入" << endl;
        }
        }
        cout<<"完成了一次操作!按Enter键继续..."; 
        cin.get();
        system("clear"); 
        loop_count++;
    }
    return 0;
}