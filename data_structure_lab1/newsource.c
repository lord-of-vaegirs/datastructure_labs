#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int *arr;
} Myarray;

// 自定义字符串长度函数
int my_strlen(char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// 自定义字符串复制函数
void my_strcpy(char *dest, char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// 自定义字符串连接函数
void my_strcat(char *dest, char *src) {
    int dest_len = my_strlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        i++;
    }
    dest[dest_len + i] = '\0';
}

// 初始化数组结构
void init_array(Myarray *my) {
    my->size = 0;
    my->arr = NULL;
}

// 获取数组大小
void getsize(Myarray *my) {
    printf("%d\n", my->size);
}

// 设置数组大小
void setsize(Myarray *my, int num) {
    my->size = num;
}

// 初始化数组数据
void initial_arr(Myarray *my, int *p) {
    my->arr = (int*)malloc(my->size * sizeof(int));
    for (int i = 0; i < my->size; i++) {
        my->arr[i] = p[i];
    }
}

// 显示数组
void show(Myarray *my) {
    if (my->arr == NULL) {
        printf("Error!!! You have not initialized your array yet!\n");
        return;
    }
    for (int i = 0; i < my->size; i++) {
        printf("%d ", my->arr[i]);
    }
    printf("\n");
}

// 尾部添加元素
void push_back_x(Myarray *my, int x) {
    if (my->arr == NULL) {
        printf("Error!!! You have not initialized your array yet!\n");
        return;
    }
    int *newarr = (int*)malloc((my->size + 1) * sizeof(int));
    for (int i = 0; i < my->size; i++) {
        newarr[i] = my->arr[i];
    }
    newarr[my->size] = x;
    my->size++;
    free(my->arr);
    my->arr = newarr;
    show(my);
}

// 尾部删除元素
void pop_back(Myarray *my) {
    if (my->arr == NULL) {
        printf("Error!!! You have not initialized your array yet!\n");
        return;
    }
    if (my->size == 0) {
        printf("Error!!! Array is already empty!\n");
        return;
    }
    my->size--;
    show(my);
}

// 插入元素
void insert_element(Myarray *my, int pos, int x) {
    if (my->arr == NULL) {
        printf("Error!!! You have not initialized your array yet!\n");
        return;
    }
    if (pos <= 0 || pos > my->size + 1) {
        printf("Invalid index!!! please try another...\n");
        return;
    }
    int *newarr = (int*)malloc((my->size + 1) * sizeof(int));
    for (int i = 0; i < pos - 1; i++) {
        newarr[i] = my->arr[i];
    }
    for (int i = my->size; i > pos - 1; i--) {
        newarr[i] = my->arr[i - 1];
    }
    newarr[pos - 1] = x;
    my->size++;
    free(my->arr);
    my->arr = newarr;
    show(my);
}

// 删除元素
void erase_element(Myarray *my, int pos) {
    if (my->arr == NULL) {
        printf("Error!!! You have not initialized your array yet!\n");
        return;
    }
    if (pos <= 0 || pos > my->size) {
        printf("Invalid index!!! please try another...\n");
        return;
    }
    for (int i = pos; i < my->size; i++) {
        my->arr[i - 1] = my->arr[i];
    }
    my->size--;
    show(my);
}

// 更新元素
void update_element(Myarray *my, int pos, int x) {
    if (my->arr == NULL) {
        printf("Error!!! You have not initialized your array yet!\n");
        return;
    }
    if (pos <= 0 || pos > my->size) {
        printf("Invalid index!!! please try another...\n");
        return;
    }
    my->arr[pos - 1] = x;
    show(my);
}

// 保存文件
void save_array(Myarray *my, char *filename, int length) {
    if (my->arr == NULL) {
        printf("Error!!! You have not initialized your array yet!\n");
        return;
    }
    char root[] = "./output/";
    int root_len = my_strlen(root);
    char *fullpath = (char*)malloc(root_len + length + 1);
    
    // 手动构建完整路径
    my_strcpy(fullpath, root);
    my_strcat(fullpath, filename);
    
    if (filename[length - 1] == 't') {
        FILE *fout = fopen(fullpath, "w");
        if (fout == NULL) {
            printf("Error opening file for writing!\n");
            free(fullpath);
            return;
        }
        fprintf(fout, "%d\n", my->size);
        for (int i = 0; i < my->size; i++) {
            fprintf(fout, "%d", my->arr[i]);
            if (i < my->size - 1)
                fprintf(fout, " ");
        }
        fclose(fout);
    } 
    else {
        FILE *fout = fopen(fullpath, "wb");
        if (fout == NULL) {
            printf("Error opening file for writing!\n");
            free(fullpath);
            return;
        }
        fwrite(&my->size, sizeof(int), 1, fout);
        fwrite("\n", sizeof(char), 1, fout);
        for (int i = 0; i < my->size; i++) {
            fwrite(&my->arr[i], sizeof(int), 1, fout);
            if (i < my->size - 1)
                fwrite(" ", sizeof(char), 1, fout);
        }
        fclose(fout);
    }
    free(fullpath);
}

// 释放数组内存
void free_array(Myarray *my) {
    if (my->arr != NULL) {
        free(my->arr);
        my->arr = NULL;
    }
}

// 字符串比较函数
int cmp(char* string1, char* string2, int length) {
    for (int i = 0; i < length; i++) {
        if (string1[i] != string2[i]) return 0;
    }
    return 1;
}

// 命令匹配函数
int matching_mode(char *func_name, int size) {
    if (size == 4) {
        char func1[] = "size";
        char func2[] = "show";
        char func3[] = "save";
        char func4[] = "exit";
        if (cmp(func_name, func1, 4)) return 1;
        else if (cmp(func_name, func2, 4)) return 2;
        else if (cmp(func_name, func3, 4)) return 8;
        else if (cmp(func_name, func4, 4)) return 9;
        else return -1;
    }
    else if (size == 5) {
        char func[] = "erase";
        if (cmp(func_name, func, 5)) return 6;
        else return -1;
    }
    else if (size == 6) {
        char func1[] = "insert";
        char func2[] = "update";
        if (cmp(func_name, func1, 6)) return 5;
        else if (cmp(func_name, func2, 6)) return 7;
        else return -1;
    }
    else if (size == 8) {
        char func[] = "pop_back";
        if (cmp(func_name, func, 8)) return 4;
        else return -1;
    }
    else if (size == 9) {
        char func[] = "push_back";
        if (cmp(func_name, func, 9)) return 3;
        else return -1;
    }
    else {
        return -1;
    }
}

// 字符串转整数
int charToint(char *p, int size) {
    int num = 0;
    for (int i = 0; i < size; i++) {
        num *= 10;
        num += (p[i] - '0');
    }
    return num;
}

// 移除字符串末尾的换行符
void remove_newline(char *str) {
    int len = my_strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int main() {
    FILE *f;
    int flag = -1;
    printf("请输入你想要打开的文件代码:1表示txt文件,2表示bin文件\n");
    scanf("%d", &flag);
    
    if (flag == 1)
        f = fopen("./input/exp1_example.txt", "r");
    else if (flag == 2)
        f = fopen("./input/exp1_example.bin", "rb");
    else {
        printf("error\n");
        return 0;
    }
    
    Myarray my;
    init_array(&my);
    
    if (f == NULL) {
        printf("文件没有成功打开哦!\n");
        return 0;
    }
    printf("open successfully !!!\n");
    
    int cur_size;
    if (flag == 1)
        fscanf(f, "%d", &cur_size);
    else
        fread(&cur_size, sizeof(int), 1, f);
    
    setsize(&my, cur_size);
    int *p = (int*)malloc(cur_size * sizeof(int));
    
    if (flag == 1) {
        for (int i = 0; i < cur_size; i++) {
            fscanf(f, "%d", &p[i]);
        }
    } else {
        for (int i = 0; i < cur_size; i++) {
            fread(&p[i], sizeof(int), 1, f);
        }
    }
    
    initial_arr(&my, p);
    free(p);
    fclose(f);
    
    int loop_count = 0;
    while (1) {
        char instruction[1000];
        printf("请输入：\n");
        if (loop_count == 0) {
            getchar(); // 清除缓冲区
        }
        fgets(instruction, 1000, stdin);
        
        // 使用自定义函数移除换行符
        remove_newline(instruction);
        
        char func_name[1000] = {0}, op1[1000] = {0}, op2[1000] = {0};
        int id1 = 0, id2 = 0, id3 = 0;
        int face_blank = 0;
        
        for (int i = 0; instruction[i] != '\0'; i++) {
            if (instruction[i] == ' ') {
                face_blank++;
                continue;
            }
            switch (face_blank) {
                case 0: {
                    func_name[id1] = instruction[i];
                    id1++;
                    break;
                }
                case 1: {
                    op1[id2] = instruction[i];
                    id2++;
                    break;
                }
                case 2: {
                    op2[id3] = instruction[i];
                    id3++;
                    break;
                }
            }
        }
        
        switch (matching_mode(func_name, id1)) {
            case 1: {
                getsize(&my);
                break;
            }
            case 2: {
                show(&my);
                break;
            }
            case 3: {
                int val = charToint(op1, id2);
                push_back_x(&my, val);
                break;
            }
            case 4: {
                pop_back(&my);
                break;
            }
            case 5: {
                int pos = charToint(op1, id2);
                int val = charToint(op2, id3);
                insert_element(&my, pos, val);
                break;
            }
            case 6: {
                int pos = charToint(op1, id2);
                erase_element(&my, pos);
                break;
            }
            case 7: {
                int pos = charToint(op1, id2);
                int val = charToint(op2, id3);
                update_element(&my, pos, val);
                break;
            }
            case 8: {
                save_array(&my, op1, id2);
                break;
            }
            case 9: {
                printf("程序运行结束\n");
                free_array(&my);
                return 0;
            }
            default: {
                printf("错误，请重新输入\n");
            }
        }
        printf("完成了一次操作!按Enter键继续...");
        getchar();
        system("clear");
        loop_count++;
    }
    
    free_array(&my);
    return 0;
}