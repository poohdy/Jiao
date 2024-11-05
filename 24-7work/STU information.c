#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 10    //����ռ���ڴ�

struct Student{
	char num[15];		//ѧ��
	char name[15];		//����
	char major[10];		//רҵ��IoT,automatic,electrical��
	int classNo;		//�༶(1-2)
	int score[3];		//3�ſεĳɼ�(0-2)
	float average;		// ƽ���ɼ�
	};
typedef struct Student STU;//�ṹ�����

/*���������б�*/
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
	STU Student[N+n]; 	// ����ѧ������
	srand(time(0));		// ��ʼ�����������
	char choice;        // ����ѡ���Ƿ�����˵�
	int num;
	do {
		printf("                  ѧ����Ϣ����ϵͳ                        \n");
		printf("     ----------------------   ------------------------------- \n");
		printf("10.д��ѧ����Ϣ���ļ����������ݿɰ���0����ȡ��//�Ƽ��ȡ�0����10��\n");
		printf("     ----------------------   ------------------------------- \n");
		printf("      0.���ļ��ж�ȡѧ����Ϣ 	  1.���ȫ��ѧ����Ϣ         \n");
		printf("      2.�����ȡѧ����Ϣ     	  3.�༶�ɼ��ۺϲ�ѯ         \n");
		printf("     ----------------------   ------------------------------- \n");
		printf("      4.��ѯ�γ���߷�      	  5.����ѡ������ȫԱƽ����   \n");
		printf("      6.����ð������༶ƽ����    7.�����������γ̳ɼ�     \n");
		printf("     ----------------------   ------------------------------- \n");
		printf("      8.����ѧ����Ϣ���ļ��� 	  9.�˳�����      			\n");
		printf("     ----------------------   ------------------------------- \n");

		printf("��ѡ���ܱ��:");
		scanf("%d", &num);
		switch (num){
			case 0:
				Input(Student,N+n);			//���ļ�¼������
				calculate_average(Student,N+n);
				break;
			case 1:
				printf("ѧ����Ϣ���:\n");
				for(int i = 0;i < N+n;i ++){
				 	Output(&Student[i]);    //�������
				}
				system("pause");
				break;
			case 2:{
				int index = rand() % N+n; 	//�����������
		        STU random = Fetch(index);  // ����������ȡ���ѧ����Ϣ
		        Output(&random);
				break;
			}
			case 3:{
		  		int classNo;
		  		int scoreSum;
				char s;
				printf("����༶(1��2): ");
			    scanf("%d", &classNo);
			    printf("����ȽϷ�(>��<��=): ");
			    scanf(" %c", &s);  				// ǰ��ӿո�����ǰһ�������Ļ��з�
			    printf("����ɼ��ܷ�: ");
			    scanf(" %d", &scoreSum);
			    Search(Student,classNo,s,scoreSum);
				break;
			}
			case 4:{
				int scoreIndex;
			    printf("����γ����(0-2): ");
			    scanf("%d", &scoreIndex);

			    int idx = Max(Student,scoreIndex);
			    
			    if (idx != -1) {
			        Output(&Student[idx]);
			    } else {
			        printf("δ�ҵ�ѧ��\n");
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
				printf("����༶: ");
				scanf("%d", &classNo);
				Sort_buble(Student,classNo);
			    break;
			}
			case 7:{
				STU stu_class_subject[N+n];
				char major[10];
			    printf("����רҵ: ");
			    scanf("%s", major);
			    Sort_insert(Student,N+n,major);
				break;
			}
			case 8:{
				Save(Student,N+n);
		        printf("������ϣ�\n");
				break;
			}
			case 9:
                printf("�����˳�����\n");
                exit(0);
                break;
            case 10:{
            	printf("������ѧ������\n");
            	scanf(" %d",&n);
				input(Student,n);			//д������
				calculate_average(Student,n);
				break;
			}
			default:
				printf("����0-12֮��ѡ��\n\n\n");
				break;
		}
		printf("�Ƿ����������(y/n): ");
    	scanf(" %c",&choice);
    } while (choice == 'y' || choice == 'Y');	// �ж��û��Ƿ��������
}




//���ļ�������Ϣover
void Input(STU *p,int n){
    FILE *file = fopen("studentInit.dat", "rb");	//ֻ���������ƣ�
    if (file == NULL) {								//���ļ����������ʧ��
        printf("�޷����ļ�\n");
        return;
    }
    fread(p,sizeof(STU),n,file);
    fclose(file);
    printf("�Ѵ��ļ���¼��ѧ����Ϣ��\n");
}


//���ļ�������ѧ����Ϣ
void input(STU *p,int n) {
	FILE *fp;
	fp=fopen("studentInit.dat","wb");
	if(fp==NULL) {
		printf("���ļ�����\n");
	}
	printf("���ļ��ɹ�\n");
	for(int i = N;i < N+n;i ++) {
		printf("ѧ��\n");
		scanf(" %d",p[i].num);
		printf("����\n");
		scanf(" %s",p[i].name);
		printf("רҵ\n");
		scanf(" %s",p[i].major);
		printf("�༶\n");
		scanf(" %d",&p[i].classNo);
		printf("�ɼ�\n");
		scanf(" %d%d%d",&p[i].score[0],&p[i].score[1],&p[i].score[2]);
		fwrite(&p[i], sizeof(STU),1,fp);
	}
	fclose(fp);
	printf("\n����ɹ���\n");
}

//����ָ����ʾĳͬѧ��Ϣover
void Output(STU *p) {
    printf("| ѧ��: %-25s \n", p->num);
    printf("| ����: %-25s \n", p->name);
    printf("| רҵ: %-25s \n", p->major);
    printf("| �༶: %-25d \n", p->classNo);
    printf("| ���ſγɼ�: %-5d  %-5d %-5d\n",p->score[0],p->score[1],p->score[2]);
    printf("| ƽ���ɼ�: %.2f \n", p->average);
    printf("|------------------------\n");
}
	
//�����ض�(���)��ͬѧover
STU Fetch(int studentIndex) {
    FILE *file = fopen("studentInit.dat", "rb");			//ֻ���������ƣ�
    STU student;
    if (file == NULL) {										//���ļ����������ʧ��
        printf("�޷����ļ�\n");
        return student;
    }														//�ļ�ָ��λ���ļ���ͷ
 	fseek(file, studentIndex * sizeof(STU), SEEK_SET);		//���ļ�ָ���ƶ���sizeof(STU)��ʾSTU��С��SEEK_SET���ļ�ͷƫ��
    fread(&student, sizeof(STU), 1, file);                

    fclose(file);
    return student;
}

//���ݰ༶�ͳɼ����ҷ���������ͬѧ0ver
void Search(STU *p, int classNo, char s, int scoreSum){
	int m=0;														//�Ƿ��ҵ�ѧ��
    for (int i = 0; i < 10; i++) {
    	int sum = p[i].score[0] + p[i].score[1] + p[i].score[2];
//    	printf("�ܷ֣�%d\n",sum);
        if (p[i].classNo == classNo) {
            if ((s == '>' && sum > scoreSum) ||(s == '<' && sum < scoreSum) ||(s == '=' && sum == scoreSum)) {
                Output(&p[i]);
                m = 1;
            }
        }
	}
	if (!m) {
        printf("δ�ҵ�����������ѧ��\n");
    }
}

//�ҳ���ǰ�༶�±�����ͬѧover
int Max(STU *p, int scoreIndex) {
    FILE *file = fopen("studentInit.dat", "rb");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return -1;
    }

	fread(p, sizeof(STU), N, file);	//���ļ���ȡ N �� sizeof(STU) ��С�����ݿ鵽���� p �С�

    int maxIdx = -1;				//��������Ӧ��ѧ������
    int maxScore = -1;              //��֤��������ʼ��С
    for (int i = 0; i < N; i++) {
        if (p[i].score[scoreIndex] > maxScore) {
            maxScore = p[i].score[scoreIndex];
            maxIdx = i;
        }
    }
    fclose(file);
    return maxIdx;					// �����ҵ�����������Ӧ��ѧ���������е�����
}

//ƽ���ɼ��ɵ͵��߽��м�ѡ������over
void Sort_select(STU *p){
	int j,i;
	STU temp;

	for(i = 0;i < N - 1;i ++){
		int min_i = i;
		//����С
	   	for (j = i + 1; j < N; j++) {
	        int sum_i = p[min_i].score[0] + p[min_i].score[1] + p[min_i].score[2];
	        int sum_j = p[j].score[0] + p[j].score[1] + p[j].score[2];
	        if (sum_j < sum_i) {
	            min_i = j;
	        }
	    }
	 	// �����ҵ��ĳɼ���Сѧ������ǰλ��
		if (min_i != i) {
            temp = p[i];
            p[i] = p[min_i];
            p[min_i] = temp;
        }
    }
    printf("ѡ��������ɣ�\n");
}

//��ƽ���ɼ��ɸߵ��ͽ�����������over
void Sort_buble(STU *p, int classNo){
 	STU stu_class_ave[N];
 	int count = 0;
	// ����ԭʼ���鵽�ֲ�����
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
    printf("ð��������ɣ�\n");
}


//��ĳ�ſγ̳ɼ��ɵ͵��߽���ֱ�Ӳ�������
void Sort_insert(STU *p, int n, char *major){
	STU stu_class_subject[N];
	int count = 0;								//��Ч��ѧ������
	//�ض�רҵ��ѧ�����Ƶ��ֲ�����
    for (int i = 0; i < N; i++) {
        if (strcmp(p[i].major, major) == 0) {	//�Ƚ��ַ�������
            stu_class_subject[count++] = p[i];
        }
    }
    for (int i = 1; i < count; i++) {
        STU key = stu_class_subject[i];										//���浱ǰ�������ѧ������
        int j = i - 1;
        while (j >= 0 && stu_class_subject[j].score[0] > key.score[0]) {	//�ӵ�ǰλ����ǰ���������򲿷�
            stu_class_subject[j + 1] = stu_class_subject[j];
            j--;
        }
        stu_class_subject[j + 1] = key;										// ��key���뵽���������еĺ���λ��
    }
   	for (int i = 0; i < count; i++) {
    	Output(&stu_class_subject[i]);
    }
    printf("������ɣ�\n");
}

void AddStudent(STU *p,int n){
	FILE *fp;                               //��W��ģʽ�£��ļ�ָ��λ���ļ���ͷ
	fp=fopen("studentInit.dat","wb");		//ֻд�����ļ��󣬻�����ļ���ԭ�е����ݡ�
	if(fp==NULL) {							//���ļ������ڣ����½��ļ���
		printf("���ļ�����\n");
	}

	for(int i=0;i<n;i++) {
		printf("�������%dλѧ����ѧ��\n",i+1);
		scanf("%s",p[i].num);
		getchar();              //������뻺�����еĻس�����ո�
		printf("�������%dλѧ��������\n",i+1);
		scanf("%s",p[i].name);
		getchar();
		printf("�������%dλѧ����רҵ\n",i+1);
		scanf("%s",p[i].major);
		getchar();
		printf("�������%dλѧ���İ༶\n",i+1);
		scanf("%d",&p[i].classNo);
		getchar();
		printf("��һ�ſγɼ�: ");
		scanf("%d", &p[i].score[0]);
		getchar();
		printf("�ڶ��ſγɼ�: ");
		scanf("%d", &p[i].score[1]);
		getchar();
		printf("�����ſγɼ�: ");
		scanf("%d", &p[i].score[2]);
		getchar();
		fwrite(&p[i], sizeof(STU), 1, fp);
	}
	fclose(fp);
	printf("\nѧ����Ϣ��ӳɹ���\n");
}

// ɾ��ָ��ѧ�ŵ�ѧ����Ϣ
void DeleteStudent(STU *p, int n, char *studentNum) {
    int found = 0; // ����Ƿ��ҵ�ѧ��
    for (int i = 0; i < n; i ++) {
        if (strcmp(p[i].num, studentNum) == 0) { // �ҵ�ƥ���ѧ��
            found = 1;
            // �������ѧ����Ϣǰ�ƣ����ǵ�Ҫɾ����ѧ����Ϣ
            for (int j = i; j < n - 1; j++) {
                p[j] = p[j + 1];
            }
            n--; // ����ѧ������
            printf("ѧ����Ϣ��ɾ����\n");
            break;
        }
    }
    if (!found) {
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", studentNum);
    }
    // �����ļ��е�ѧ����Ϣ
    Save(p, n);
}

//��ѧ����Ϣ�����ļ�
void Save(STU *p,int n){
	FILE *fp; // �ļ�ָ��
    // ���ļ���"w"ģʽ��ʾд�룬����ļ��������򴴽�
    fp = fopen("studentInit.dat", "wb");//�Զ�����д��
    if (fp == NULL) {
        printf("�ļ��򿪴���\n");
        return;
    }
	//д�����ݵ��ļ���������Ƿ����˴��󣬼�д���Ԫ�������Ƿ�����N
	if (fwrite(p, sizeof(STU), n, fp) != N) {
	    printf( "����¼�����.\n");
	}
	
    fclose(fp);
    printf("����ɹ�\n");
}

//����ÿ��ͬѧ��ƽ���ɼ�
void calculate_average(STU *p, int n){
	for(int i = 0 ; i< n ; i++){
		p[i].average = (p[i].score[0]+p[i].score[1]+p[i].score[2])/3.0;
	}
}



