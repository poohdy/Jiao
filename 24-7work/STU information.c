#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 10    //不会占用内存

struct Student{
	char num[15];		//学号
	char name[15];		//姓名
	char major[10];		//专业（IoT,automatic,electrical）
	int classNo;		//班级(1-2)
	int score[3];		//3门课的成绩(0-2)
	float average;		// 平均成绩
	};
typedef struct Student STU;//结构体变量

/*函数声明列表*/
void Input(STU *p, int n);
void input(STU *p, int n);
void Output(STU *p);
STU Fetch(int studentIndex);
int Max(STU *p, int scoreIndex);
void Search(STU *p, int classNo, char s, int scoreSum);
void Sort_buble(STU *p, int n);
void Sort_select(STU *p);
void Save(STU *p,int n);
void Sort_insert(STU *p, int n, char *major);
void calculate_average(STU *p, int n);

int main(){
	int n = 0;
	STU Student[N+n]; 	// 定义学生数组
	srand(time(0));		// 初始化随机数种子
	char choice;        // 用于选择是否结束菜单
	int num;
	do {
		printf("                  学生信息管理系统                        \n");
		printf("     ----------------------   ------------------------------- \n");
		printf("10.写入学生信息（文件中已有数据可按‘0’读取）//推荐先‘0’后‘10’\n");
		printf("     ----------------------   ------------------------------- \n");
		printf("      0.从文件中读取学生信息 	  1.输出全部学生信息         \n");
		printf("      2.随机读取学生信息     	  3.班级成绩综合查询         \n");
		printf("     ----------------------   ------------------------------- \n");
		printf("      4.查询课程最高分      	  5.倒序选择排序全员平均分   \n");
		printf("      6.正序冒泡排序班级平均分    7.倒序插入排序课程成绩     \n");
		printf("     ----------------------   ------------------------------- \n");
		printf("      8.保存学生信息到文件里 	  9.退出程序      			\n");
		printf("     ----------------------   ------------------------------- \n");

		printf("请选择功能编号:");
		scanf("%d", &num);
		switch (num){
			case 0:
				Input(Student,N+n);			//从文件录入数据
				calculate_average(Student,N+n);
				break;
			case 1:
				printf("学生信息输出:\n");
				for(int i = 0;i < N+n;i ++){
				 	Output(&Student[i]);    //输出数据
				}
				system("pause");
				break;
			case 2:{
				int index = rand() % N+n; 	//生成随机索引
		        STU random = Fetch(index);  // 根据索引获取随机学生信息
		        Output(&random);
				break;
			}
			case 3:{
		  		int classNo;
		  		int scoreSum;
				char s;
				printf("输入班级(1或2): ");
			    scanf("%d", &classNo);
			    printf("输入比较符(>、<、=): ");
			    scanf(" %c", &s);  				// 前面加空格，跳过前一个输入后的换行符
			    printf("输入成绩总分: ");
			    scanf(" %d", &scoreSum);
			    Search(Student,classNo,s,scoreSum);
				break;
			}
			case 4:{
				int scoreIndex;
			    printf("输入课程序号(0-2): ");
			    scanf("%d", &scoreIndex);

			    int idx = Max(Student,scoreIndex);
			    
			    if (idx != -1) {
			        Output(&Student[idx]);
			    } else {
			        printf("未找到学生\n");
			    }
				break;
			}
			case 5:{
				Sort_select(Student);
				break;
			}
			case 6:{
				STU stu_class_ave[N+n];
				int classNo;
				printf("输入班级: ");
				scanf("%d", &classNo);
				Sort_buble(Student,classNo);
			    break;
			}
			case 7:{
				STU stu_class_subject[N+n];
				char major[10];
			    printf("输入专业: ");
			    scanf("%s", major);
			    Sort_insert(Student,N+n,major);
				break;
			}
			case 8:{
				Save(Student,N+n);
		        printf("保存完毕！\n");
				break;
			}
			case 9:
                printf("即将退出程序！\n");
                exit(0);
                break;
            case 10:{
            	printf("请输入学生数量\n");
            	scanf(" %d",&n);
				input(Student,n);			//写入数据
				calculate_average(Student,n);
				break;
			}
			default:
				printf("请在0-12之间选择\n\n\n");
				break;
		}
		printf("是否继续操作？(y/n): ");
    	scanf(" %c",&choice);
    } while (choice == 'y' || choice == 'Y');	// 判断用户是否继续操作
}




//从文件载入信息over
void Input(STU *p,int n){
    FILE *file = fopen("studentInit.dat", "rb");	//只读，二进制，
    if (file == NULL) {								//若文件不存在则打开失败
        printf("无法打开文件\n");
        return;
    }
    fread(p,sizeof(STU),n,file);
    fclose(file);
    printf("已从文件中录入学生信息！\n");
}


//在文件中输入学生信息
void input(STU *p,int n) {
	FILE *fp;
	fp=fopen("studentInit.dat","wb");
	if(fp==NULL) {
		printf("打开文件错误\n");
	}
	printf("打开文件成功\n");
	for(int i = N;i < N+n;i ++) {
		printf("学号\n");
		scanf(" %d",p[i].num);
		printf("姓名\n");
		scanf(" %s",p[i].name);
		printf("专业\n");
		scanf(" %s",p[i].major);
		printf("班级\n");
		scanf(" %d",&p[i].classNo);
		printf("成绩\n");
		scanf(" %d%d%d",&p[i].score[0],&p[i].score[1],&p[i].score[2]);
		fwrite(&p[i], sizeof(STU),1,fp);
	}
	fclose(fp);
	printf("\n输入成功！\n");
}

//根据指针显示某同学信息over
void Output(STU *p) {
    printf("| 学号: %-25s \n", p->num);
    printf("| 姓名: %-25s \n", p->name);
    printf("| 专业: %-25s \n", p->major);
    printf("| 班级: %-25d \n", p->classNo);
    printf("| 三门课成绩: %-5d  %-5d %-5d\n",p->score[0],p->score[1],p->score[2]);
    printf("| 平均成绩: %.2f \n", p->average);
    printf("|------------------------\n");
}
	
//查找特定(随机)的同学over
STU Fetch(int studentIndex) {
    FILE *file = fopen("studentInit.dat", "rb");			//只读，二进制，
    STU student;
    if (file == NULL) {										//若文件不存在则打开失败
        printf("无法打开文件\n");
        return student;
    }														//文件指针位于文件开头
 	fseek(file, studentIndex * sizeof(STU), SEEK_SET);		//将文件指针移动，sizeof(STU)表示STU大小，SEEK_SET从文件头偏移
    fread(&student, sizeof(STU), 1, file);                

    fclose(file);
    return student;
}

//根据班级和成绩查找符合条件的同学0ver
void Search(STU *p, int classNo, char s, int scoreSum){
	int m=0;														//是否找到学生
    for (int i = 0; i < 10; i++) {
    	int sum = p[i].score[0] + p[i].score[1] + p[i].score[2];
//    	printf("总分：%d\n",sum);
        if (p[i].classNo == classNo) {
            if ((s == '>' && sum > scoreSum) ||(s == '<' && sum < scoreSum) ||(s == '=' && sum == scoreSum)) {
                Output(&p[i]);
                m = 1;
            }
        }
	}
	if (!m) {
        printf("未找到符合条件的学生\n");
    }
}

//找出当前班级下标最大的同学over
int Max(STU *p, int scoreIndex) {
    FILE *file = fopen("studentInit.dat", "rb");
    if (file == NULL) {
        printf("无法打开文件\n");
        return -1;
    }

	fread(p, sizeof(STU), N, file);	//从文件中取 N 个 sizeof(STU) 大小的数据块到数组 p 中。

    int maxIdx = -1;				//最大分数对应的学生索引
    int maxScore = -1;              //保证最大分数初始最小
    for (int i = 0; i < N; i++) {
        if (p[i].score[scoreIndex] > maxScore) {
            maxScore = p[i].score[scoreIndex];
            maxIdx = i;
        }
    }
    fclose(file);
    return maxIdx;					// 返回找到的最大分数对应的学生在数组中的索引
}

//平均成绩由低到高进行简单选择排序。over
void Sort_select(STU *p){
	int j,i;
	STU temp;

	for(i = 0;i < N - 1;i ++){
		int min_i = i;
		//找最小
	   	for (j = i + 1; j < N; j++) {
	        int sum_i = p[min_i].score[0] + p[min_i].score[1] + p[min_i].score[2];
	        int sum_j = p[j].score[0] + p[j].score[1] + p[j].score[2];
	        if (sum_j < sum_i) {
	            min_i = j;
	        }
	    }
	 	// 交换找到的成绩最小学生到当前位置
		if (min_i != i) {
            temp = p[i];
            p[i] = p[min_i];
            p[min_i] = temp;
        }
    }
    printf("选择排序完成！\n");
}

//按平均成绩由高到低进行起泡排序。over
void Sort_buble(STU *p, int classNo){
 	STU stu_class_ave[N];
 	int count = 0;
	// 复制原始数组到局部数组
    for (int i = 0; i < N; i++) {
        if (p[i].classNo == classNo) {
            stu_class_ave[count++] = p[i];
        }
    }
	for(int i = 0;i < N - 1;i ++){
		for (int j = i;j < N - 1 - i;j++) {
			if (stu_class_ave[j].average < stu_class_ave[j + 1].average) {
                STU temp = stu_class_ave[j + 1];
                stu_class_ave[j + 1] = stu_class_ave[j];
                stu_class_ave[j] = temp;
            }
		}
	}
	for (int i = 0; i < count; i++) {
    	Output(&stu_class_ave[i]);
    }
    printf("冒泡排序完成！\n");
}


//按某门课程成绩由低到高进行直接插入排序
void Sort_insert(STU *p, int n, char *major){
	STU stu_class_subject[N];
	int count = 0;								//有效的学生个数
	//特定专业的学生复制到局部数组
    for (int i = 0; i < N; i++) {
        if (strcmp(p[i].major, major) == 0) {	//比较字符串内容
            stu_class_subject[count++] = p[i];
        }
    }
    for (int i = 1; i < count; i++) {
        STU key = stu_class_subject[i];										//保存当前待插入的学生对象
        int j = i - 1;
        while (j >= 0 && stu_class_subject[j].score[0] > key.score[0]) {	//从当前位置向前遍历已排序部分
            stu_class_subject[j + 1] = stu_class_subject[j];
            j--;
        }
        stu_class_subject[j + 1] = key;										// 将key插入到已排序序列的合适位置
    }
   	for (int i = 0; i < count; i++) {
    	Output(&stu_class_subject[i]);
    }
    printf("排序完成！\n");
}

void AddStudent(STU *p,int n){
	FILE *fp;                               //‘W’模式下，文件指针位于文件开头
	fp=fopen("studentInit.dat","wb");		//只写，打开文件后，会清空文件内原有的内容。
	if(fp==NULL) {							//若文件不存在，则新建文件；
		printf("打开文件错误\n");
	}

	for(int i=0;i<n;i++) {
		printf("请输入第%d位学生的学号\n",i+1);
		scanf("%s",p[i].num);
		getchar();              //清除输入缓冲区中的回车符或空格
		printf("请输入第%d位学生的姓名\n",i+1);
		scanf("%s",p[i].name);
		getchar();
		printf("请输入第%d位学生的专业\n",i+1);
		scanf("%s",p[i].major);
		getchar();
		printf("请输入第%d位学生的班级\n",i+1);
		scanf("%d",&p[i].classNo);
		getchar();
		printf("第一门课成绩: ");
		scanf("%d", &p[i].score[0]);
		getchar();
		printf("第二门课成绩: ");
		scanf("%d", &p[i].score[1]);
		getchar();
		printf("第三门课成绩: ");
		scanf("%d", &p[i].score[2]);
		getchar();
		fwrite(&p[i], sizeof(STU), 1, fp);
	}
	fclose(fp);
	printf("\n学生信息添加成功！\n");
}

// 删除指定学号的学生信息
void DeleteStudent(STU *p, int n, char *studentNum) {
    int found = 0; // 标记是否找到学生
    for (int i = 0; i < n; i ++) {
        if (strcmp(p[i].num, studentNum) == 0) { // 找到匹配的学号
            found = 1;
            // 将后面的学生信息前移，覆盖掉要删除的学生信息
            for (int j = i; j < n - 1; j++) {
                p[j] = p[j + 1];
            }
            n--; // 更新学生数量
            printf("学生信息已删除。\n");
            break;
        }
    }
    if (!found) {
        printf("未找到学号为 %s 的学生。\n", studentNum);
    }
    // 更新文件中的学生信息
    Save(p, n);
}

//将学生信息存入文件
void Save(STU *p,int n){
	FILE *fp; // 文件指针
    // 打开文件，"w"模式表示写入，如果文件不存在则创建
    fp = fopen("studentInit.dat", "wb");//以二进制写入
    if (fp == NULL) {
        printf("文件打开错误\n");
        return;
    }
	//写入数据到文件，并检查是否发生了错误，即写入的元素数量是否少于N
	if (fwrite(p, sizeof(STU), n, fp) != N) {
	    printf( "数据录入错误.\n");
	}
	
    fclose(fp);
    printf("保存成功\n");
}

//计算每个同学的平均成绩
void calculate_average(STU *p, int n){
	for(int i = 0 ; i< n ; i++){
		p[i].average = (p[i].score[0]+p[i].score[1]+p[i].score[2])/3.0;
	}
}



