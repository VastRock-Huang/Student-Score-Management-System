/* ѧ���ɼ�����ϵͳ */

/*  2019.08.05   */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>		//����system()����
#include<conio.h>		//����getch()��getche()����
#include<ctype.h>		
#pragma warning(disable : 4996)		//ȷ����VS��ʹ�ò���C����

//��
#define NUMBIT 4		//�궨��ѧ��λ��
#define KEYBIT 16		//�궨���������λ��
#define SCORENUM 3		//�궨��ѧ����Ŀ��
#define TEAACCFILE "./data/teacheraccount.dat"
#define STUACCFILE "./data/stuaccount.dat"
#define STUSCOREFILE "./data/stu score.dat"


//ȫ�ֱ���
typedef struct student		
{
	char num[NUMBIT+1];		//ѧ��
	char name[15];		//����
	float score[4];		//3�ųɼ�+�ܷ�
}stu;		//����ѧ���ṹ��stu
typedef struct teacher
{
	char name[15];		//����
	char key[KEYBIT+1];		//����
}tea;		//��ʦ�˺�����ṹ��tea
typedef struct
{
	char num[NUMBIT + 1];		//ѧ��
	char name[15];		//����
	char key[KEYBIT + 1];		//����
}stua;		//ѧ���˺�����ṹ��stua
stu *head;		//¼��ѧ���ɼ����׵�ַ
stua *stuhead;		//ѧ���˺�������׵�ַ
stua stuacc;		//��¼��ѧ���˺�
tea *teahead;		//��ʦ�˺�������׵�ַ
tea teaacc;	//��¼�Ľ�ʦ�˺�
char *scorename[3] = { "����","��ѧ","Ӣ��" };		//3�ųɼ�
int stunum;		//¼��ѧ������
int teanum;		//��ʦ�˺���
int keymaxbit = 16;		//�������λ��
int keyminbit = 6;		//��������λ��
char *teacherkey = "teacher";		//��ʦע��Ľ�ʦ��Կ
char *orikey = "123456";		//ѧ����ʼ����

//��������
void Interface();		//������
void signin();		//��¼������
void teasignin();		//��ʦ��¼
void stusignin();		//ѧ����¼
void loadteaacc(tea **);		//���ؽ�ʦ�˺�����
void loadstuacc(stua **);		//����ѧ���˺�����
void accountset();		//�˺�����������
void signup();		//ע��������
void teasignup();		//��ʦע��
void stusignup();		//ѧ��ע��
void pass();		//�޸��������
void teapass();		//��ʦ�޸�����
void stupass();		//ѧ���޸�����
void Inputkey(char *,int,int);		//�������뺯��
void Teachermenu();		//��ʦ�˲˵�����
void Stumenu();		//ѧ���˳ɼ�����
void loadstu(stu **);		//����ѧ���ɼ�
void showstu();		//�鿴ѧ���ɼ�
void stulist();		//ѧ���ɼ��б�
void paixustu();		//ѧ���ɼ���ͬ����ѡ��
void stusort(char);		//ѧ���ɼ�����
void addstu();		//���ѧ���ɼ�
void Inputnum(char *);		//����ѧ��
float Inputscore(float,float);		//����ɼ�
void findstu();		//��ѯѧ���ɼ�
void seekstu(char);		//����������ѧ�Ų���ѧ���ɼ�
void foundstu(char choose, char *dest,char opt);		//����������ѧ���ҵ�ѧ���ɼ�
size_t delstu(int sign);		//ɾ��ѧ���ɼ�
size_t modifystu(int sign, char choose);		//�޸�ѧ���ɼ�
void failstu();		//ѧ���ҿ�����
void emptystu();		//���ѧ���ɼ�
int IsGB(unsigned char pText);		//�ж������ַ�
void getnum(int, char *);		//��������
void help();



int main()		//������
{
	Interface();		//���������溯��
	return 0;
}

void Interface()		//�����溯��
{
	int ichar;
	char pick;		//pick����ѡ��ֵ
	system("cls");		//��������
	system("color 30");		//������Ļ����ɫ��ǰ��ɫ
	printf("\n\n\n\n");		//���ý���
	printf("\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\t\t\t\t\t\t    ��ӭʹ��\n");
	printf("\n\n");
	printf("\t\t\t\t------------------------------------------------\n");
	printf("\t\t\t\t| ��ѡ��                                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   1.��¼                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 2.�˺�����                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   3.����                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   0.�˳�                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	//printf("\t\t\t\tPlease Choose: ");		//����ѡ��
	while ((pick=getch())<'0'|| pick>'3')
	{
		/*printf("\b  \b");		//��������ֵ���ڸǵ�
		pick = getch();		//�ӿ���̨��ȡ�ַ�����������*/
		printf("                                            �����������������");
		Sleep(500);		//��ͣ����1s
		for (ichar = 64; ichar > 0; ichar--)		//���ǵ������ַ�
			printf("\b");		//ɾ��ǰ�������ʾ
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	} 		//������ֵ��Ϊ1��2��3����������
	if (pick == '1')
		signin();		//������1������¼������
	else if (pick == '2')
		accountset();		//������2������˺�����������
	else if (pick == '3')
		help();
	else if (pick == '0')
		exit(0);		//������0���˳�����ֹ����
}

void signin()		//��¼������
{
	int pick, ichar;		//pick����ѡ��ֵ��icharΪ�ַ�ѭ������
	system("cls");		//��������
	printf("\n\n\n\n");		//���ý���
	printf("\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n\n\n");
	printf("\t\t\t\t--------------------SIGN IN---------------------\n");
	printf("\t\t\t\t| ��ѡ���¼��ݣ�                             |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 1.��ʦ��¼                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 2.ѧ����¼                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   0.����                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	while((pick=getch())<'0'||pick>'2')		//����0~2������ֵ����ʾ������������
	{
		printf("                                            �����������������");
		Sleep(500);		//��ͣ����1s
		for (ichar = 64; ichar > 0; ichar--)		//���ǵ������ַ�
			printf("\b");		//ɾ��ǰ�������ʾ
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	} 
	switch (pick)		//�ж�����ֵ
	{
	case '0': Interface();		//����0�򷵻�������	//����0����������
		break;
	case '1': teasignin();		//����1�����ʦ��¼����
		break;
	case '2': stusignin();		//����2����ѧ����¼����
		break;
	}
}

void teasignin()		//��ʦ��¼����
{
	int sign, pick;		//sign�����¼��ʦ���˺���Ϣ�ڽ�ʦ�˺���Ϣ�����
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("SIGN UP>>��ʦ��¼");
	printf("\n\n\n");
	printf("\t�����ʦ������");	
	gets(teaacc.name);	//�����ʦ��������¼��ʦ�˺Žṹ����
	printf("\n\t�����˺����룺");
	Inputkey(teaacc.key, keyminbit, keymaxbit);		//�����˺����뵽��¼��ʦ�˺Žṹ����
	loadteaacc(&teahead);		//���ؽ�ʦ�˺���Ϣ
	for (sign = 0; sign < teanum; sign++)		//��ʦ�˺���Ϣ�����0��ʼѰ��
	{
		if (strcmp(teaacc.name, teahead[sign].name) == 0)		//���ҵ��ý�ʦ�˺���Ϣ
		{
			if (strcmp(teaacc.key, teahead[sign].key) == 0)		//ͬʱ����������ȷ
			{
				printf("\n\n\t��½�ɹ�");		//��½�ɹ�
				free(teahead);		//�ͷŽ�ʦ�˺���Ϣ�Ķ�̬�ڴ�
				Sleep(300);
				Teachermenu();		//�����ʦ�˲˵�����
			}
			else		//�������������
			{
				printf("\n\n\t�������\t1.���µ�¼\tElse.����\n");
				pick = getch();
				if (pick == '1')		
				{
					free(teahead);
					teasignin();
				}
				else
				{
					free(teahead);
					signin();
				}
			}
			break;		//���ҵ��ý�ʦ�˺���Ϣ������ѭ��
		}
	}
	if (sign == teanum)		//��δ�ҵ��ý�ʦ�˺���Ϣ
	{
		free(teahead);		//�ͷŽ�ʦ�˺���Ϣ�Ķ�̬�ڴ�
		printf("\n\n\t�˺Ų�����\t1.���µ�¼\tElse.����\n");
		pick = getch();
		if (pick == '1')
			teasignin();
		else
			signin();
	}
}

void stusignin()		//ѧ����¼����
{
	int sign,pick;		//sign���¼ѧ����Ϣ���
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("SIGN UP>>ѧ����¼");
	printf("\n\n\n");
	printf("\t����%dѧ�ţ�",NUMBIT);
	getnum(NUMBIT,stuacc.num);		//����ѧ�ŵ���¼ѧ���˺Žṹ����
	printf("\n\t����������");
	gets(stuacc.name);		//������������¼ѧ���˺Žṹ����
	printf("\n\t�����˺����룺");
	Inputkey(stuacc.key, keyminbit, keymaxbit);		//�������뵽��¼ѧ���˺Žṹ����
	loadstuacc(&stuhead);		//����ѧ���˺���Ϣ
	for (sign = 0; sign < stunum; sign++)		//ѧ���˺���Ϣ�����0��ʼ����
	{
		if (strcmp(stuacc.num, stuhead[sign].num) == 0)		//�����ڸ�ѧ���˺ţ�ѧ�ţ���Ϣ
		{
			if (strcmp(stuacc.name, stuhead[sign].name) == 0)		//ͬʱ����������ȷ
			{
				if (strcmp(stuacc.key, stuhead[sign].key) == 0)		//ͬʱ����������ȷ
				{
					printf("\n\n\t��½�ɹ�");		//��½�ɹ�
					free(stuhead);
					Sleep(300);
					Stumenu();
				}
				else		//�����벻��ȷ
				{
					printf("\n\n\t�������\t1.���µ�¼\tElse.����\n");
					pick = getch();
					if (pick == '1')
					{
						free(stuhead);
						stusignin();
					}
					else
					{
						free(stuhead);
						signin();
					}
				}
			}
			else		//����������ȷ
			{
				printf("\n\n\tѧ��������һ��\t1.���µ�¼\tElse.����\n");
				pick = getch();
				if (pick == '1')
				{
					free(stuhead);
					stusignin();
				}
				else
				{
					free(stuhead);
					signin();
				}
			}
		}
	}
	if (sign == stunum)		//��δ�ҵ���ѧ���˺���Ϣ
	{
		free(stuhead);
		printf("\n\n\t�˺Ų�����\t1.���µ�¼\tElse.����\n");
		pick = getch();
		if (pick == '1')
			stusignin();
		else
			signin();
	}

}

void loadteaacc(tea **dest)		//���ؽ�ʦ�˺���Ϣ����		**destΪ��ʦ�˺���Ϣ����Ķ���ָ��
{

	FILE *fp;
	int i;
	teanum = 0;		//��ʦ������0
	if ((fp = fopen(TEAACCFILE, "rb+")) == NULL)		//�򿪽�ʦ�˺���Ϣ�ļ�teacheraccount.dat
	{
		printf("\n\n\n\n\n\n�ļ���ʧ��\n");
		return;
	}
	for (rewind(fp); fgetc(fp) != EOF; teanum++)		//���ļ���ͷ����ĩβ��û�ζ�ȡһ���ַ��ж��ǲ���EOF���ļ���������
	{
		fseek(fp, -1, 1);		//����Ϊ�ļ�ĩβ���ļ���ָ�����1���ֽ�
		fseek(fp, sizeof(tea), 1);		//ͬʱ����ƶ�tea��С���ֽڣ���ʦ��+1
	}
	*dest = (tea *)calloc(teanum, sizeof(tea));		//��̬�ڴ�����н�ʦ����tea�ṹ������鲢�ö���ָ��ʹdestָ�������ĵ�ַ
	for (rewind(fp), i = 0; i < teanum; i++)
		fread(*dest + i, sizeof(tea), 1, fp);		//����ʦ�˺���Ϣ�ļ��Ľ�ʦ�˺���Ϣ��������*dest��
	fclose(fp);		//�ر��ļ�ָ��
}

void loadstuacc(stua **dest)		//����ѧ���˺���Ϣ����		**destΪѧ���˺���Ϣ����Ķ���ָ��
{
	FILE *fp;
	int i;
	stunum = 0;
	if ((fp = fopen(STUACCFILE, "rb+")) == NULL)
	{
		printf("\n\n\n\n\n\n�ļ���ʧ��\n");
		return;
	}
	for (rewind(fp); fgetc(fp) != EOF; stunum++)
	{
		fseek(fp, -1, 1);
		fseek(fp, sizeof(stua), 1);
	}
	*dest = (stua *)calloc(stunum, sizeof(stua));
	for (rewind(fp), i = 0; i < stunum; i++)
		fread(*dest + i, sizeof(stua), 1, fp);
	fclose(fp);
}

void accountset()		//�˺����������溯��
{
	int pick, ichar;
	system("cls");		//��������
	printf("\n\n\n\n");		//���ý���
	printf("\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n\n\n");
	printf("\t\t\t\t--------------------SET  UP---------------------\n");
	printf("\t\t\t\t| ��ѡ��                                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   1.ע��                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 2.�޸�����                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   0.����                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	while ((pick = getch())<'0' || pick>'2')
	{
		printf("                                            �����������������");
		Sleep(500);		//��ͣ����1s
		for (ichar = 64; ichar > 0; ichar--)		//���ǵ������ַ�
			printf("\b");		//ɾ��ǰ�������ʾ
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': Interface();		//����0�򷵻�������
		break;
	case '1':signup();		//����1����ע��������
		break;
	case '2':pass();		//����2�����޸�����������
		break;
	}
}

void signup()		//ע��������
{
	int pick, ichar;
	system("cls");		//��������
	printf("\n\n\n\n");		//���ý���
	printf("\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n\n\n"); 
	printf("\t\t\t\t--------------------SIGN UP---------------------\n");
	printf("\t\t\t\t| ��ѡ��ע����ݣ�                             |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 1.��ʦע��                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 2.ѧ��ע��                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   0.����                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	while ((pick = getch()) < '0' || pick > '2')		//����0~2������ֵ����ʾ������������
	{
		printf("                                            �����������������");
		Sleep(500);		//��ͣ����1s
		for (ichar = 64; ichar > 0; ichar--)		//���ǵ������ַ�
			printf("\b");		//ɾ��ǰ�������ʾ
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': accountset();//����0�򷵻��˺�����������
		break;
	case '1':teasignup();		//����1�����ʦע�����
		break;
	case '2':stusignup();		//����2����ѧ��ע�����
		break;
	}
}

void teasignup()			//��ʦע�ắ��
{
	tea temp;		//temp��ע��Ľ�ʦ�˺���Ϣ
	int pick,i;
	char key[KEYBIT+1];		//key�����ٴ����������
	FILE *fp;
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("SET UP>>SIGN UP>>��ʦע��");
	printf("\n\n\n");
	printf("\t�����ʦ������");
	gets(temp.name);
	loadteaacc(&teahead);		//���ؽ�ʦ�˺���Ϣ
	for(i=0;i<teanum;i++)
		if (strcmp(temp.name, teahead[i].name) == 0)		//��ע���ʦ�Ѵ��ڽ�ʦ�˺���Ϣ��
		{
			printf("\n\t�˺��Ѵ���\t1.����ע��\tElse.����");
			pick = getch();
			if (pick == '1')
			{
				teasignup();
				break;
			}

			else
			{
				signup();
				break;
			}
		}
	free(teahead);		//�ͷŽ�ʦ�˺���Ϣ�ڴ�
	//puts(temp.name);		
	printf("\n\n\t����6~%dλ���룺",keymaxbit);		//��������
	Inputkey(temp.key,keyminbit,keymaxbit);
	printf("\n\n\t�ٴ��������룺");		//�ٴ�ȷ������
	Inputkey(key,keyminbit,keymaxbit);
	if (strcmp(temp.key, key) != 0)		//���������벻һ��
	{
		printf("\n\t�������벻һ��\t1.����ע��  Else.����");
		if ((pick = getch()) == '1')
			teasignup();
		else
			signup();
	}
	printf("\n\n\t�����ʦ��Կ��");
	Inputkey(key, 0,keymaxbit);
	printf("\n\n\tע���ʦ�˻���\t1.ȷ��   2.����ע��   3.����\n");
	while ((pick = getch())<'0' || pick>'3')
	{
			printf("�����������������");		//��������ֵ����ʾ������������
			Sleep(100);
			for (i = 20; i > 0; i--)
				printf("\b");	
			for (i = 20; i > 0; i--)
				printf(" ");
			for (i = 20; i > 0; i--)
				printf("\b");
	}
	switch (pick)
	{
	case '0': signup();		//���뷵��ע�����
		break;
	case '1': if (strcmp(teacherkey, key) != 0)		//����1������Կ����ȷ
	{
		printf("\t��Կ����\n\t��ѡ��1.����ע��\tElse.����\n");
		pick = getch();
		if (pick == '1')
			teasignup();
		else
			signup();
	}
			  else
	{
		if ((fp = fopen(TEAACCFILE, "ab+")) == NULL)		//�򿪽�ʦ�˺���Ϣ�ļ���׷�Ӷ�д
		{
			printf("\tע��ʧ��\t1.����ע��\tElse.����");
			fclose(fp);		//ע��д����һ��Ҫ�ر��ļ�ָ�룬����д��������޷��ڳ������й����м���ʹ��
			pick = getch();
			if (pick == '1')
				teasignup();
			else
				signup();
		}
		if (fwrite(&temp, sizeof(tea), 1, fp))		//��ע�����Ϣ��ӵ��ļ���
		{
			printf("\n\tע��ɹ�");
			fclose(fp);
			Sleep(500);
			Interface();
		}
		else
		{
			printf("\tע��ʧ��\t1.����ע��\tElse.����");
			pick = getch();
			if (pick == '1')
				teasignup();
			else
				signup();
		}
	}
			  break;
	case '2': teasignup();
		break;
	case '3': signup();
		break;
	}
}

void stusignup()		//ѧ��ע�ắ��
{
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("SET UP>>SIGN UP>>ѧ��ע��");
	printf("\n\n\n");
	printf("\tѧ������ע�ᣬϵͳ¼��ѧ�����ɵ�¼\n\n\t��¼��ʽ������ѧ�ź�����\n\t��ʼ���룺%s\n",orikey);
	printf("\n\t�����.����");
	getch();
	signup();
}

void pass()		//�޸����������溯��
{
	int pick, ichar;
	system("cls");		//��������
	printf("\n\n\n\n");		//���ý���
	printf("\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n\n\n");
	printf("\t\t\t\t----------------CHANGE PASSWORD-----------------\n");
	printf("\t\t\t\t| ��ѡ����ݣ�                                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               1.��ʦ�޸�����                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               2.ѧ���޸�����                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   0.����                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	while ((pick = getch()) < '0' || pick > '2')		//����0~2������ֵ����ʾ������������
	{
		printf("                                            �����������������");
		Sleep(500);		//��ͣ����1s
		for (ichar = 64; ichar > 0; ichar--)		//���ǵ������ַ�
			printf("\b");		//ɾ��ǰ�������ʾ
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': accountset();		//����0�򷵻�������
		break;
	case '1':teapass();		//����1�����ʦ�޸�����
		break;
	case '2':stupass();		//����2����ѧ���޸�����
		break;
	}
}

void teapass()		//��ʦ�޸����뺯��
{
	int sign, pick,i;		//signΪ�޸������ʦ�˺���Ϣ����ţ�pickΪѡ��ֵ
	tea temp;		//temp�����޸ĵ���Ϣ
	FILE *fp;
	char key[KEYBIT + 1];	//�����ٴ�ȷ�ϵ�����
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("SET UP>>��ʦ�޸�����");
	printf("\n\n\n");
	loadteaacc(&teahead);		//���ؽ�ʦ�˺���Ϣ
	printf("\t�����ʦ������");
	gets(temp.name);
	for (sign = 0; sign < teanum; sign++)		//�����0���ҽ�ʦ�˺���Ϣ
	{
		if (strcmp(temp.name, teahead[sign].name) == 0)		//�������ʦ��������
		{
			printf("\n\t�����˺�ԭ���룺");
			Inputkey(temp.key, keyminbit, keymaxbit);		//����ԭ����
			if (strcmp(temp.key, teahead[sign].key) == 0)		//��ԭ������ȷ
			{
				printf("\n\n\t�����˺������룺");
				Inputkey(temp.key, keyminbit, keymaxbit);
				printf("\n\n\t�ٴ�ȷ�������룺");
				Inputkey(key, keyminbit, keymaxbit);
				if (strcmp(temp.key, key) == 0)		//������������ͬ
				{
					printf("\n\n\tȷ���޸����룿\t1.ȷ��   2.�����޸�   0.����\n");
					while ((pick = getch()) < '0' || pick > '2')
					{
						printf("�����������������");		//��������ֵ����ʾ������������
						Sleep(100);
						for (i = 20; i > 0; i--)
							printf("\b");
						for (i = 20; i > 0; i--)
							printf(" ");
						for (i = 20; i > 0; i--)
							printf("\b");
					} 
					switch (pick)
					{
					case '0':free(teahead);		//����0�ͷŽ�ʦ�˺���Ϣ�Ķ�̬�ڴ淵���޸�����������
						pass();
						break;
					case '1':teahead[sign] = temp;		//���޸ĵĽ�ʦ�˺���Ϣ���Ƶ�ԭ����Ӧ�Ľ�ʦ�˺���Ϣ��
						if ((fp = fopen(TEAACCFILE, "wb+")) == NULL)
						{
							printf("\n\t�޸�����ʧ��");
							Sleep(500);
							teapass();
						}
						if (fwrite(teahead, sizeof(tea), teanum, fp))		//���޸ĺ�Ľ�ʦ�˺���Ϣ��������д���ļ���
						{
							printf("\n\t�޸�����ɹ�");
							fclose(fp);
							free(teahead);
							Sleep(500);
							pass();
						}
						else
						{
							printf("\n\t�޸�����ʧ��");
							fclose(fp);
							free(teahead);
							Sleep(500);
							teapass();
						}
						break;
					case '2':free(teahead);		//����2�����޸�����
						teapass();
						break;
					}
				}
				else
				{
					printf("\n\t�������벻һ�£��������޸�");
					free(teahead);
					Sleep(500);
					teapass();
				}
			}
			else
			{
				printf("\n\n\t�˺��������\t 1.�����޸�\tElse.����");
				if (pick = getch() == '1')
				{
					Sleep(500);
					free(teahead);
					teapass();
				}
				else
				{
					Sleep(500);
					free(teahead);
					pass();
				}
			}
		}
	}
	if (sign == teanum)		//���޸��˺�
	{
		printf("\n\t�޸��˺�\t1.�����޸�\t Else.����");
		if (pick = getch() == '1')
		{
			Sleep(500);
			free(teahead);
			teapass();
		}
		else
		{
			Sleep(500);
			free(teahead);
			pass();
		}
	}
}

void stupass()		//ѧ���޸����뺯��
{
	int sign, pick, i;
	stua temp;		//temp�����޸ĵ�ѧ���˺���Ϣ
	FILE *fp;
	char key[KEYBIT + 1];	//�����ٴ�ȷ�ϵ�����
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("SET UP>>>>ѧ���޸�����");
	printf("\n\n\n");
	loadstuacc(&stuhead);		//����ѧ���˺���Ϣ
	printf("\t����ѧ��%dλѧ�ţ�",NUMBIT);
	getnum(NUMBIT, temp.num);		//����ѧ��
	printf("\n\t����ѧ��������");
	gets(temp.name);
	for (sign = 0; sign < stunum; sign++)		//�ж�ѧ���˺���Ϣ�Ƿ����
	{
		if (strcmp(temp.num, stuhead[sign].num) == 0)		//����Ϣ����
		{
			if (strcmp(temp.name, stuhead[sign].name) == 0)		//ͬʱ����������ȷ
			{
				printf("\n\t�����˺�ԭ���룺");
				Inputkey(temp.key, keyminbit, keymaxbit);
				if (strcmp(temp.key, stuhead[sign].key) == 0)		//ͬʱԭ����������ȷ
				{
					printf("\n\n\t�����˺������룺");
					Inputkey(temp.key, keyminbit, keymaxbit);
					printf("\n\n\t�ٴ�ȷ�������룺");
					Inputkey(key, keyminbit, keymaxbit);
					if (strcmp(temp.key, key) == 0)		//ͬʱ������������һ��
					{
						printf("\n\n\tȷ���޸����룿\t1.ȷ��   2.�����޸�   0.����\n");
						while ((pick = getch()) < '0' || pick > '2')
						{
							printf("�����������������");		//��������ֵ����ʾ������������
							Sleep(100);
							for (i = 20; i > 0; i--)
								printf("\b");
							for (i = 20; i > 0; i--)
								printf(" ");
							for (i = 20; i > 0; i--)
								printf("\b");
						}
						switch (pick)
						{
						case '0':free(stuhead);		//����0�����޸��������
							pass();
							break;
						case '1':stuhead[sign] = temp;		//����1 ���޸ĵ�ѧ���˺���Ϣ��ֵ��ԭ�����˺�
							if ((fp = fopen(STUACCFILE, "wb+")) == NULL)
							{
								printf("\n\t�޸�����ʧ��");
								Sleep(500);
								stupass();
							}
							if (fwrite(stuhead, sizeof(stua), stunum, fp))
							{
								printf("\n\t�޸�����ɹ�");
								fclose(fp);
								free(stuhead);
								Sleep(500);
								pass();
							}
							else
							{
								printf("\n\t�޸�����ʧ��");
								fclose(fp);
								free(stuhead);
								Sleep(500);
								teapass();
							}
							break;
						case '2':free(stuhead);		//����2�����޸�ѧ������
							stupass();
							break;
						}
					}
					else
					{
						printf("\n\t�������벻һ�£��������޸�");
						free(stuhead);
						Sleep(500);
						stupass();
					}
				}
				else
				{
					printf("\n\n\t�˺��������\t 1.�����޸�\tElse.����");
					if ((pick = getch()) == '1')
					{
						Sleep(500);
						free(stuhead);
						stupass();
					}
					else
					{
						Sleep(500);
						free(stuhead);
						pass();
					}
				}
			}
			else
			{
				printf("\n\n\tѧ��������һ��\t 1.�����޸�\tElse.����");
				if ((pick = getch()) == '1')
				{
					Sleep(500);
					free(stuhead);
					stupass();
				}
				else
				{
					Sleep(500);
					free(stuhead);
					pass();
				}
			}
		}
	}
	if (sign == stunum)
	{
		printf("\n\t�޸��˺�\t1.�����޸�\t Else.����");
		if ((pick = getch()) == '1')
		{
			Sleep(500);
			free(stuhead);
			stupass();
		}
		else
		{
			Sleep(500);
			free(stuhead);
			pass();
		}
	}
}
	
void Inputkey(char *key,int minbit,int maxbit)		//�������뺯��  keyΪ���봢���ַ��minbitΪ��������λ����maxbitΪ�������λ��
{
	int i,j;
	for (i = 0; i < maxbit; i++)		//�������maxbitλ����
	{
		key[i] = getch();		//��������
		if (key[i] != '\r'&&key[i] != '\b')		//�����ַ���Ϊ�س����˸�
		{
			if (IsGB(key[i]) != 0 || isgraph(key[i]) == 0)	//�����ַ���Ϊ���ֻ��������ַ����ɴ�ӡ
			{
				printf("   �Ƿ��ַ�������������");
					Sleep(500);
					for (j = 0; j < 23 + i - 1; j++)		//�����ʾ�ַ�
						printf("\b");
					for (j = 0; j < 23 + i - 1; j++)
						printf(" ");
					for (j = 0; j < 23 + i - 1; j++)
						printf("\b");
					printf("\b \b");		//����ԭ��������һ���ַ�
					i = -1;		//i=-1ѭ������Ϊi=0������������
			}
			else
				putchar('*');		//��Ϊ�����ַ����ӡ*
		}
		else if (key[i] == '\r')		//������س���Windows��getch()����س��õ�'\r''\n'�����ַ�������ֵ��Ϊ'\r'��
		{
			if (i < minbit)		//�������ַ�������������λ��
			{
				printf("   ����λ�����㣬����������");
					Sleep(500);
					for (j = 0; j < 27 + i - 1; j++)		//������27���ַ�����ʱ�Ѿ�����i���ַ�����ӡ��i-1��*��ʹ����һ������ʧ
						printf("\b");
					for (j = 0; j < 27 + i - 1; j++)
						printf(" ");
					for (j = 0; j < 27 + i - 1; j++)
						printf("\b");
				printf("\b ");		//δ֪ԭ����������������һ�������*��Ҫ�ڸǵ�
				i = -1;		//ȷ��ѭ��+1��i=0��������
			}
			else		//�������ַ�����������������λ�����˳�����ѭ��
				break;
		}
		else if (key[i] == '\b'&& i>0 )		//�������˸��������ַ�������1(i>0)���򸲸ǵ����һ���ַ�������������ַ�
		{
			printf("\b \b");
			i = i - 2;
		}
	}
	key[i] = 0;		//���һλ��ӽ�����
}

int IsGB(unsigned char pText)		//�ж������ַ����� pTextΪ���жϵ��ַ�
{
	if (pText >= 161)
		if (pText == 163)
			return 1;//ȫ���ַ�
		else
			return 2;//����
	else
		return 0;//Ӣ�ġ����֡�Ӣ�ı��
}

void Teachermenu()		//��ʦ�˲˵����溯��
{
	char pick;
	int ichar;
	system("cls");		//��Ļ���ü���������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n��ʦ\t%s\n", teaacc.name);		//��ʾ��½�˺�
	printf("\n\n\n");
	printf("\t\t\t\t--------------------TEACHER---------------------\n");
	printf("\t\t\t\t| ��ѡ��                                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               1.�鿴ѧ���ɼ�                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               2.���ѧ���ɼ�                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               3.����ѧ���ɼ�                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               4.���ѧ���ɼ�                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 0.�˳���¼                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	loadstu(&head);		//����ѧ���ɼ�
	while ((pick = getch()) < '0' || pick > '4')		//����0~2������ֵ����ʾ������������
	{
		printf("                                            �����������������");
		Sleep(500);		//��ͣ����1s
		for (ichar = 64; ichar > 0; ichar--)		//���ǵ������ַ�
			printf("\b");		//ɾ��ǰ�������ʾ
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': free(head);
		Interface();//����0�򷵻�������
		break;
	case '1': showstu();		//����1��鿴ѧ���ɼ�
		break;
	case '2': addstu();		//����2�����ѧ���ɼ�
		break;
	case '3': findstu();		//����3����ѧ���ɼ�
		break;
	case '4':emptystu();		//����4���ѧ���ɼ�
		break;
	}
}

void Stumenu()		//ѧ���˽��溯��
{
	int sign;		//��½ѧ����ѧ���ɼ��е����
	int rank[SCORENUM+1];		//��Ŀ����	
	int failnum = 0;
	int person,score;
	int i;
	for (i = 0; i < SCORENUM + 1; i++)		//��Ŀ���������ʼ��ȫ��Ԫ��Ϊ1
	{
		rank[i] = 1;
	}
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\nѧ��\t%s\n", stuacc.name);		//��ʾ��½ѧ��
	printf("STUDENT>>");
	printf("\n\n");
	loadstu(&head);		//����ѧ���ɼ�
	printf("\t\t\t\t\t��Ŀ������  ��ѧ  Ӣ��  �ܷ�\n");		//�����½ѧ���ɼ�
	for (sign = 0; sign < stunum; sign++)
	{
		if (strcmp(stuacc.num, head[sign].num) == 0)
		{
			printf("\n\t\t\t\t\t�ɼ�  %-5g %-5g %-5g %-5g\n", head[sign].score[0], head[sign].score[1], head[sign].score[2], head[sign].score[3]);
			break;
		}
	}
	printf("\n\t\t\t\t\t����  ");		//�����½ѧ������
	for (score = 0; score < SCORENUM+1; score++)		//ÿ�ųɼ��ֱ�����
	{
		for (person = 0; person < stunum; person++)		//��½ѧ��������ѧ�����бȽ�
		{
			if (head[sign].score[score] < head[person].score[score])		//����½ѧ���ɼ�����ĳһѧ��������������һλ
				rank[score]++;
		}
		printf("No.%-2d ", rank[score]);
	}
	printf("\n\n\t\t\t\t\t�ҿ������");		//����ҿ����
	for (score = 0; score < SCORENUM; score++)
	{
		if (head[sign].score[score] < 60)		//���йҿ�������ÿγ�����
		{
			failnum++;
			printf("%s  ", scorename[score]);
		}
	}
	if (failnum >0)
	{
		printf("��%d��", failnum);		//����ҿ���Ŀ
	}
	else		//���޹ҿ��򽫹ҿ���ʾ�ַ�����
	{
		for (i = 0; i < 10; i++)
			printf("\b");
		for (i = 0; i < 10; i++)
			printf(" ");
		for (i = 0; i < 10; i++)
			printf("\b");
	}
	printf("\n\n�����.�˳���¼");
	getch();
	free(head);
	Interface();
}

void loadstu(stu **dest)		//����ѧ����Ϣ����
{
	FILE *fp;
	int i;
	stunum = 0;	//ÿ�μ���ѧ��������ʼ��Ϊ0
	if ((fp = fopen(STUSCOREFILE, "rb+")) == NULL)
	{
		printf("\n\n\n\n\n\n�ļ���ʧ��\n");
		return;
	}
	for (rewind(fp); fgetc(fp) != EOF; stunum++)		//����ѧ������
	{
		fseek(fp, -1, 1);
		fseek(fp, sizeof(stu), 1);
	}
	*dest = (stu *)calloc(stunum, sizeof(stu));		//��������ѧ���ɼ��Ķ�̬�ڴ�����
	for (rewind(fp), i = 0; i < stunum; i++)
		fread(*dest + i, sizeof(stu), 1, fp);		//����ѧ���ɼ�
	fclose(fp);
}

void addstu()		//���ѧ���ɼ�����
{
	FILE *fp;
	stu temp;		//��ʱ��¼ѧ���ɼ��Ľṹ��
	stua tempp;		//��ʱ��¼ѧ���˺���Ϣ�Ľṹ��
	int i;
	char pick;
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n��ʦ\t%s\n", teaacc.name);
	printf("TEACHER>>���ѧ���ɼ�");
	printf("\n\n");
	printf("\tѧ�ţ�");		//����ѧ��
	Inputnum(temp.num);
	strcpy(tempp.num, temp.num);		//��ѧ�Ÿ��Ƶ�ѧ���˺���Ϣ��
	printf("\t������");		//��������
	gets(temp.name);
	strcpy(tempp.name, temp.name);	//���������Ƶ�ѧ���˺���Ϣ��
	strcpy(tempp.key, orikey);		//����ʼ���븳ֵ��ѧ���˺���Ϣ��
	printf("\n\t�ɼ���\n");		//����ÿ�ſ�Ŀ�ɼ�
	temp.score[SCORENUM] = 0;
	for (i = 0; i < SCORENUM; i++)		
	{
		printf("\t%s:",scorename[i]);
		temp.score[i] = Inputscore(0,100);		//�������
		temp.score[SCORENUM] += temp.score[i];		//�ܷ�Ϊ���п�Ŀ�ɼ�֮��
	}
	printf("\n�Ƿ�ȷ��¼�룿\n\t1.ȷ��  2.����¼��  0.����\n");		//�ж��Ƿ�ȷ��
	while ((pick = getch()) < '0' || pick > '2')
	{
		printf("�����������������");		//��������ֵ����ʾ������������
		Sleep(100);
		for (i = 20; i > 0; i--)
			printf("\b");
		for (i = 20; i > 0; i--)
			printf(" ");
		for (i = 20; i > 0; i--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': Teachermenu();		//����0 ���ؽ�ʦ�˲˵�����
		break;
	case '1':		//����1��stu�е����ݱ��浽�ļ���
		if ((fp = fopen(STUACCFILE, "ab+")) == NULL)
		{
			printf("�ļ���ʧ��\n");
			Teachermenu();
		}
		if (fwrite(&tempp, sizeof(stua), 1, fp) == 0)		//��ѧ���˺���Ϣд��ѧ���˺���Ϣ�ļ�stuaccount.dat��
		{
			printf("\t����ʧ�� ������¼��\n");		//��������ʧ��������¼��
			fclose(fp);
			Sleep(1000);
			addstu();
		}
		fclose(fp);
		if ((fp = fopen(STUSCOREFILE, "ab+")) == NULL)		//���ļ�
		{
			printf("�ļ���ʧ��\n");
			Teachermenu();
		}
		if (fwrite(&temp, sizeof(stu), 1, fp))		//��ѧ���ɼ�д��ѧ���ɼ��ļ�stu score.dat��  ���ط���ֵ��¼��ɹ�
		{
			fclose(fp);
			printf("\t����ɹ�\n");
			printf("�Ƿ����¼�룿\n\t1.��\tElse.��\n\t");
			if (getch() == '1')		//������1�����¼�룬���»ص����ѧ���ɼ�����
				addstu();
			else
				Teachermenu();		//��������ֵ�򷵻ؽ�ʦ�˲˵�����
		}
		else		//fwrite()����0¼��ʧ��
		{
			printf("\t����ʧ�� ������¼��\n");		//��������ʧ��������¼��
			fclose(fp);
			Sleep(1000);
			addstu();
		}
		break;
	case '2': addstu();		//����2������¼�����»ص����ѧ���ɼ�����
		break;
	}
}

void showstu()		//�鿴ѧ���ɼ�����
{
	int i, pick;
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n��ʦ\t%s\n", teaacc.name);
	printf("TEACHER>>�鿴ѧ���ɼ�");
	printf("\n\n");
	if (stunum == 0)		//��ѧ����Ϊ0����ѧ���ɼ�
	{
		puts("\tû�м�¼\n\t�����������");
		getch();
		Teachermenu();
	}
	stulist();		//���ѧ���ɼ�
	printf("\n\t\t���ܴ���1.ѧ���ɼ�����    2.ɾ��ѧ���ɼ�\n\t\t\t  3.�޸�ѧ���ɼ�    4.�ҿ�ѧ������\n\t\t\t  0.����\n");		//����ѡ��
	do
	{
		pick = getch();		//����ѡ��

		if (pick == '0')
			Teachermenu();		//����0�򷵻�������
		else if (pick == '1')
			paixustu();		//����1���벻ͬ����ѡ��
		else if (pick == '2')
			seekstu('1');		//����2����ɾ��ʽ����
		else if (pick == '3')
			seekstu('2');		//����3�����޸�ʽ����
		else if (pick == '4')
			failstu();		//����4����ҿ�����
		else 
		{
			printf("                �����������������");		//��������ֵ����ʾ������������
			Sleep(100);
			for (i = 36; i > 0; i--)
				printf("\b");
			for (i = 36; i > 0; i--)
				printf(" ");
			for (i = 36; i > 0; i--)
				printf("\b");
		}
	} while (pick<'0' || pick>'4');		//��������ֵ����ʾ������������
}

void stulist()		//ѧ���ɼ��б���
{
	int i;
	printf("\t\t\tѧ��������%d\n", stunum);	
	printf("\t\t\t���    ѧ��    ����    �ɼ�������  ��ѧ  Ӣ��  �ܷ�\n");
	for (i = 0; i < stunum; i++)
	{
		printf("\t\t\t%-8d%-8s%-8s      %-5g %-5g %-5g %-5g\n", i+1,head[i].num, head[i].name, head[i].score[0], head[i].score[1], head[i].score[2], head[i].score[3]);
	}
}

void Inputnum(char *num)		//����ѧ�ź���  *numΪѧ�Ŵ���׵�ַ
{
	int i,j,pick,sign;
	getnum(NUMBIT, num);		//��������
	if(stunum>0)		//��ѧ����������0
		for (sign = 0; sign < stunum; sign++)		//ѧ������
		{
			if (strcmp(num, head[sign].num) == 0)		//��ѧ���Ѵ���
			{
				printf("   ��Ա��¼�롣��ѡ��1.¼��������Ա 2.����¼��ó�Ա 0.����");
				while ((pick = getch()) < '0' || pick > '2')
				{
					printf("�����������������");		//��������ֵ����ʾ������������
					Sleep(100);
					for (i = 20; i > 0; i--)
						printf("\b");
					for (i = 20; i > 0; i--)
						printf(" ");
					for (i = 20; i > 0; i--)
						printf("\b");
				}
				switch (pick)
				{
				case '0': Teachermenu();		//����0�򷵻�������
				case '1': addstu();
					break;
				case '2': for (j = 0; j < 60; j++)
						{
							printf("\b");
						}
						  printf("   ����¼��                                                  ");
						  delstu(sign);		//ɾ����ѧ���ɼ�
						  break;
				}
			}
		}
	printf("\n");
}

float Inputscore(float minnum,float maxnum)		//����ɼ����������븡����������	minmumΪ�������ޣ�maxnumΪ��������
{
	char s[20];		//s��������ĸ�����
	int i;		//lenΪ����ĸ��������ַ�����
	float score;		//���ת����ĸ�����
	gets_s(s, 20);		//���븡����
	while((score =(float) atof(s)) == 0 || score < minnum || score>maxnum)		//�������ַ���ת����Ϊ������atof()���ɹ������ز�Ϊ0�����ڲ���������֮��
	{
		printf("\t���벻�Ϸ�������������");
		Sleep(300);
		for (i = 0; i < 23; i++)
			printf("\b");
		for (i = 0; i < 23; i++)
			printf(" ");
		for (i = 0; i < 22; i++)
			printf("\b");
		gets_s(s, 6);
	}
	return score;		//���ظ�����
}

void paixustu()		//ѧ���ɼ���ͬ����ѡ����
{
	int i;
	int choose;		//ѡ��ֵ
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n��ʦ\t%s\n", teaacc.name);
	printf("TEACHER>>�鿴ѧ���ɼ�>>ѧ���ɼ�����");
	printf("\n\n");
	stulist();		//���ѧ���ɼ�
	printf("\n\t\t��ѡ��1.��ѧ������       2.���ܷ�����      3.�����ĳɼ�����\n\t\t\t4.����ѧ�ɼ�����   5.��Ӣ��ɼ�����\n\t\t\t0.����\n");
	while ((choose = getch()) < '0' || choose > '5')
	{
		printf("                �����������������");		//��������ֵ����ʾ������������
		Sleep(100);
		for (i = 36; i > 0; i--)
			printf("\b");
		for (i = 36; i > 0; i--)
			printf(" ");
		for (i = 36; i > 0; i--)
			printf("\b");
	}
	switch (choose)
	{
	case '0': showstu();
		break;
	case '1': stusort('1');
		break;
	case '2': stusort('2');
		break;
	case '3':stusort('3');
		break;
	case '4': stusort('4');
		break;
	case '5': stusort('5');
		break;
	}
}

void stusort(char choose)		//ѧ���ɼ�������	chooseΪ����ѡ��
{
	int i,j,pick;
	stu *sort;		//���濽����ѧ���ɼ������׵�ַ
	stu temp;		//����stu��������ʱ�ṹ��
	FILE *fp;
	sort = (stu *)calloc(stunum, sizeof(stu));		//������̬�ڴ沢����ѧ���ɼ�
	memcpy(sort, head, sizeof(stu)*stunum);
	for (i = 0; i < stunum-1; i++)		//ѡ������
	{
		for (j = i + 1; j < stunum; j++)
		{
			switch (choose)		//����ѡ����в�ͬ��������
			{
			case '1':if (strcmp(sort[i].num, sort[j].num) > 0)		//��ѧ������
				{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
				}
					 break;
			case '2':if (sort[i].score[SCORENUM] < sort[j].score[SCORENUM])		//���ܷ�����
				{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
				}
					 break;
			case '3': if (sort[i].score[0] < sort[j].score[0])		//�����ĳɼ�����
				{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
				}
					  break;
			case '4': if (sort[i].score[1] < sort[j].score[1])		//����ѧ�ɼ�����
				{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
				}
					  break;
			case '5': if (sort[i].score[2] < sort[j].score[2])		//��Ӣ��ɼ�����
				{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
				}
					  break;
			}
			
		}
	}
	system("cls");
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n��ʦ\t%s\n", teaacc.name);
	switch (choose)
	{
	case '1':printf("TEACHER>>�鿴ѧ���ɼ�>>��ѧ������");
		break;
	case '2':printf("TEACHER>>�鿴ѧ���ɼ�>>���ܷ�����");
		break;
	case '3':printf("TEACHER>>�鿴ѧ���ɼ�>>�����ĳɼ�����");
		break;
	case '4':printf("TEACHER>>�鿴ѧ���ɼ�>>����ѧ�ɼ�����");
		break;
	case '5':printf("TEACHER>>�鿴ѧ���ɼ�>>��Ӣ��ɼ�����");
		break;
	}
	printf("\n\n");
	printf("\t\t\tѧ��������%d\n", stunum);		//��������ĳɼ��б�
	printf("\t\t\t���    ѧ��    ����    �ɼ�������  ��ѧ  Ӣ��  �ܷ�\n");
	for (i = 0; i < stunum; i++)
	{
		printf("\t\t\t%-8d%-8s%-8s      %-5g %-5g %-5g %-5g\n", i+1,sort[i].num, sort[i].name, sort[i].score[0], sort[i].score[1], sort[i].score[2], sort[i].score[3]);
	}
	printf("\n\t\t��ѡ��1.�Դ�˳�򱣴�   Else.������ԭ˳��\n\t");
	if ((pick = getch()) == '1')
	{
		if ((fp = fopen(STUSCOREFILE, "wb+")) == NULL)
		{
			printf("\n\n\n\n\n\n�ļ���ʧ��\n");
			stusort(choose);
		}
		if (fwrite(sort, sizeof(stu), stunum, fp) == stunum)		//�����򱣴�ɹ�
		{
			printf("\n¼��ɹ�\n");
			free(sort);
			Sleep(500);
			fclose(fp);
			free(head);
			loadstu(&head);		//���¼���ѧ���ɼ�
			showstu();
		}
		else
		{
			printf("\n¼��ʧ��\n");
			fclose(fp);
			free(sort);
			Sleep(1000);
			showstu();
		}
	}
	else
		paixustu();		//����
}

void findstu()		//��ѯѧ���ɼ�����
{
	char num[NUMBIT + 1],name[15];		//num��name���ڴ����ѯ��ѧ����Ϣ
	int *sign,i,pick,choose,signnum=0;		//signΪָ�������������ŵ������ָ�룬signnumΪ���������������Ŀ
	float score;		//�����ѯ�ĳɼ�
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n��ʦ\t%s\n", teaacc.name);
	printf("TEACHER>>��ѯѧ���ɼ�");
	printf("\n\n");
	printf("\t\t��ѡ���ѯ��ʽ�� 1.��ѧ�Ų���\t2.����������\t3.���ɼ�����\t\n\t\t                 0.����\n\n");
	sign = (int *)calloc(stunum, sizeof(int));		//����һ����СΪѧ�������������ڴ��������������ţ���Ϊ������������Ŀ���Ϊѧ������
	while ((pick = getch()) < '0' || pick > '3')
	{
		printf("                �����������������");		//��������ֵ����ʾ������������
		Sleep(100);
		for (i = 36; i > 0; i--)
			printf("\b");
		for (i = 36; i > 0; i--)
			printf(" ");
		for (i = 36; i > 0; i--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': Teachermenu();		//����0�򷵻�������
	case '1':printf("\t\t�������ѯѧ�ţ�");
		getnum(NUMBIT, num);
		for (sign[signnum] = 0; sign[signnum] < stunum; sign[signnum]++)		//signnum��ʼֵΪ0��sign[0]��0��ʼ����
		{
			if (strcmp(num, head[sign[signnum]].num) == 0)		//���ҵ�������ѧ����ͬ��ѧ�����˳�����ʱsign[signnum]��sign[0]�д���ŷ���������ѧ�������
				break;
		}
		break;
	case '2':printf("\t\t�������ѯ������");
		gets_s(name, 15);
		for (sign[signnum] = 0; sign[signnum] < stunum; sign[signnum]++)
		{
			if (strcmp(name, head[sign[signnum]].name) == 0)		//���ҵ�������������ͬ��ѧ�����˳�����ʱsign[signnum]��sign[0]�д���ŷ���������ѧ�������
				break;
		}
		break;
	case '3': printf("\t\t���ɼ���ѯ��1.���ֲܷ�ѯ  2.�����ĳɼ���ѯ  3.����ѧ�ɼ���ѯ  4.��Ӣ��ɼ���ѯ\n\t\t            0.����\n");
		while ((choose = getch()) < '0' || choose > '4')
		{
			printf("                �����������������");		//��������ֵ����ʾ������������
			Sleep(100);
			for (i = 36; i > 0; i--)
				printf("\b");
			for (i = 36; i > 0; i--)
				printf(" ");
			for (i = 36; i > 0; i--)
				printf("\b");
		}
		switch (choose)
		{
		case '0': findstu();
		case '1': printf("\t\t�������ѯ�ܷ֣�");
			score = Inputscore(0, 300);
			for (sign[signnum] = 0; sign[signnum] < stunum; sign[signnum]++)		//signnum��ʼֵΪ0��sign[0]��0��ʼ����
			{
				if (score == head[sign[signnum]].score[3])		//���ҵ����������һ�µ�ѧ��
				{
					signnum++;		//�������������Ŀsignnum+1
					sign[signnum] = sign[signnum - 1];		//ͬʱ��sign[signnum]�ĳ�ʼֵ��ֵΪ��һ��signԪ�ص�ֵ
							//��ʱѭ�����ж���������˵ڶ���Ԫ��sign[signnum]��ѧ�������Ƚϣ�sign��ǰһ��Ԫ�ص�ֵ���Ա�������������ѧ���������һ��
							//sign�����н������������������е�ѧ����ţ��������һ�������Ҫ��������ѭ���жϣ��������������
				}
			}
			break;
		case '2':  printf("\t\t�������ѯ���ĳɼ���");
			score = Inputscore(0, 100);
			for (sign[signnum] = 0; sign[signnum] < stunum; sign[signnum]++)
			{
				if (score == head[sign[signnum]].score[0])
				{
					signnum++;
					sign[signnum] = sign[signnum - 1];
				}
			}
			break;
		case '3': printf("\t\t��������ѧ�ɼ���");
			score = Inputscore(0, 100);
			for (sign[signnum] = 0; sign[signnum] < stunum; sign[signnum]++)
			{
				if (score == head[sign[signnum]].score[1])
				{
					signnum++;
					sign[signnum] = sign[signnum - 1];
				}
			}
			break;
		case '4': printf("\t\t�������ѯӢ��ɼ���");
			score = Inputscore(0, 100);
			for (sign[signnum] = 0; sign[signnum] < stunum; sign[signnum]++)
			{
				if (score == head[sign[signnum]].score[2])
				{
					signnum++;
					sign[signnum] = sign[signnum - 1];
				}
			}
			break;
		}
		break;
	}
	if (sign[0] == stunum)		//�����������Ԫ�ؼ�sign[0]����ѧ�����������޷���������ѧ��
	{
		printf("\t\t\tδ��ѯ���������²�ѯ");
		Sleep(500);
		findstu();
	}
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n��ʦ\t%s\n", teaacc.name);
	switch (pick)
	{
		case '1':printf("TEACHER>>��ѯѧ���ɼ�>>��ѧ�Ų�ѯ");
			break;
		case '2':printf("TEACHER>>��ѯѧ���ɼ�>>��������ѯ");
			break;
		case '3': switch (choose)
			{	
			case '1':printf("TEACHER>>��ѯѧ���ɼ�>>���ɼ���ѯ>>���ֲܷ�ѯ");
				break;
			case '2':printf("TEACHER>>��ѯѧ���ɼ�>>���ɼ���ѯ>>�����ĳɼ���ѯ");
				break;
			case '3':printf("TEACHER>>��ѯѧ���ɼ�>>���ɼ���ѯ>>����ѧ�ɼ���ѯ");
				break;
			case '4':printf("TEACHER>>��ѯѧ���ɼ�>>���ɼ���ѯ>>��Ӣ��ɼ���ѯ");
				break;
			}
			break;
	}
	printf("\n\n");
	printf("\t\t\tѧ��    ����    �ɼ�������  ��ѧ  Ӣ��  �ܷ�\n");		//�������������ѧ���ɼ�
	for(i=0;i<signnum+1 && sign[i]<stunum;i++)		//����������ű�����signnum��0��ʼ������signnum+1λ����������ŵĸ�������ͬʱ�ų����һ������ѭ�����������Ԫ�أ����Ҫ����Ԫ��sign[i]С��ѧ������
		printf("\t\t\t%-8s%-8s      %-5g %-5g %-5g %-5g\n", head[sign[i]].num, head[sign[i]].name, head[sign[i]].score[i], head[sign[i]].score[1], head[sign[i]].score[2], head[sign[i]].score[3]);
	free(sign);		//�ͷ��������Ķ�̬�ڴ�
	printf("\n\t\t�Ƿ������ѯ��  1.��\tElse.��\n\t");
	if (getch() == '1')		
		findstu();
	else
		Teachermenu();		//��������ֵ�򷵻ؽ�ʦ�˲˵�����
}

void seekstu(char choose)		//����������ѧ�Ų���ѧ���ɼ�  chooseΪѡ�1Ϊɾ�� 2Ϊ�޸�
{
	char num[NUMBIT + 1],name[15];		//num��name���ڴ����ѯ��ѧ����Ϣ	
	int pick;
	int i;
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n��ʦ\t%s\n", teaacc.name);
	if(choose=='1')
		printf("TEACHER>>�鿴ѧ���ɼ�>>ɾ��ѧ���ɼ�");
	else if(choose=='2')
		printf("TEACHER>>�鿴ѧ���ɼ�>>�޸�ѧ���ɼ�");
	printf("\n\n");
	stulist();
	if (choose == '1')
		printf("\n\t\t��ѡ��ɾ����ʽ�� 1.��ѧ��ɾ��\t2.������ɾ��\n\t\t                 0.����\n\n");
	else if(choose =='2')
		printf("\n\t\t��ѡ���޸ķ�ʽ�� 1.��ѧ���޸�\t2.�������޸�\n\t\t                 0.����\n\n");
	while ((pick = getch()) < '0' || pick > '2')
	{
		printf("                �����������������");		//��������ֵ����ʾ������������
		Sleep(100);
		for (i = 36; i > 0; i--)
			printf("\b");
		for (i = 36; i > 0; i--)
			printf(" ");
		for (i = 36; i > 0; i--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': showstu();
		break;
	case '1': printf("\t\t������ѧ��ѧ�ţ�");
		getnum(NUMBIT, num);
		foundstu('1', num, choose);		//��ѧ���ҵ�ѧ���ɼ�
		break;
	case '2': printf("\t\t������ѧ��������");
		gets_s(name, 15);
		foundstu('2', name, choose);		//�������ҵ�ѧ���ɼ�
		break;
	}
}

void foundstu(char choose,char *dest,char opt)		//����������ѧ���ҵ�ѧ���ɼ�����	chooseΪѡ�1Ϊ����ѧ�� 2Ϊ����������destΪ����ѯ���ַ�����ѧ�Ż���������optΪѡ�1Ϊɾ�� 2Ϊ�޸�
{
	int sign;		//sign�������ѯѧ�������
	int pick;
	for (sign = 0; sign < stunum; sign++)		//ѧ���ɼ�����
	{
		if (choose == '1')		//����ѧ�Ų�ѯ
		{
			if (strcmp(dest, head[sign].num) == 0)		//�ҵ�ѧ�����˳�
				break;
		}
		else if (choose == '2')		//����������ѯ
		{
			if (strcmp(dest, head[sign].name) == 0)		//�ҵ��������˳�
				break;
		}
	}
	if (sign == stunum)
	{
		printf("\t\tδ��ѯ���������²�ѯ");
		Sleep(500);
		seekstu(opt);
	}
	else		//����ѯ��
	{
		if(opt=='1')
			printf("\t\t�Ѳ�ѯ�����Ƿ�ȷ��ɾ����\t1.ȷ��\tElse.ȡ��\n");
		else if(opt=='2')
			printf("\t\t�Ѳ�ѯ�����Ƿ�ȷ���޸ģ�\t1.ȷ��\tElse.ȡ��\n");
		pick = getch();
		if (pick != '1')
			seekstu(opt);		//����
		else  if(opt=='1')		//��ɾ��ѡ��
		{	
			if (delstu(sign))		//ɾ��ѧ���ɼ�
			{
				system("cls");		//��Ļ��������
				printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
				printf("\n��ʦ\t%s\n", teaacc.name);
				printf("TEACHER>>�鿴ѧ���ɼ�>>ɾ��ѧ���ɼ�");
				printf("\n\n");
				stulist();
				printf("\n\t\t��ɾ��\n\t\t�Ƿ����ɾ����\t 1.��\tElse.��");
				pick = getch();
				if (pick == '1')
					seekstu('1');
				else
					showstu();
			}
			else
			{
				printf("\n\t\tɾ��ʧ�ܣ�������ɾ��");
				Sleep(500);
				seekstu('1');		//����
			}
		}
		else if (opt == '2')		//���޸�ѡ��
		{
			if (modifystu(sign,choose))
			{
				system("cls");		//��Ļ��������
				printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
				printf("\n��ʦ\t%s\n", teaacc.name);
				printf("TEACHER>>�鿴ѧ���ɼ�>>�޸�ѧ���ɼ�");
				printf("\n\n");
				stulist();
				printf("\n\t\t���޸�\n\t\t�Ƿ�����޸ģ�\t 1.��\tElse.��\n");
				pick = getch();
				if (pick == '1')
					seekstu('2');
				else
					showstu();
			}
			else
			{
				printf("\n\t\t�޸�ʧ�ܣ��������޸�");
				Sleep(500);
				seekstu('2');
			}
		}
	}
}

size_t delstu(int sign)		////ɾ��ѧ���ɼ����� signΪ��ɾ����ѧ����ţ�����0ɾ��ʧ�ܣ���0ɾ���ɹ�
{
	int i;
	size_t res;//resΪfwrite�ķ���ֵ
	FILE *fp;
	for (i = sign; i < stunum - 1; i++)		//�ɴ�ɾ��ѧ�����λ�ã�ѧ���ɼ���ǰ���Ǽ�����ѧ���ɼ�ɾ��
		head[i] = head[i + 1];
	stunum--;
	if ((fp = fopen(STUSCOREFILE, "wb+")) == NULL)
	{
		return 0;
	}
	res = fwrite(head, sizeof(stu), stunum, fp);		//��ɾ�����ѧ���ɼ�д���ļ�
	fclose(fp);
	free(head);		//�ͷ�ԭ��ѧ���ɼ�
	loadstu(&head);		//���¼���ѧ���ɼ�
	return res;		//����fwrite�ķ���ֵ��������д��ɹ�

}

size_t modifystu(int sign,char choose)		//�޸�ѧ���ɼ�����  signΪ���޸�ѧ���ɼ���ţ�chooseΪѡ�1Ϊ��֪ѧ�� 2Ϊ��֪����������0�޸�ʧ�ܣ���0�޸ĳɹ�
{
	int i;
	size_t res;
	int pick;
	stu temp;		//temp������ʱ���޸���Ϣ
	FILE *fp;
	printf("\tѧ��\n\t");		//����ѧ��
	if (choose == '1')		//��֪ѧ����ֱ���������ֵ��temp
	{
		strcpy(temp.num, head[sign].num);
		printf("%s\n", head[sign].num);
	}
	else
		getnum(NUMBIT, temp.num);
	printf("\n\t����\n\t");		//��������
	if (choose == '2')		//��֪������ֱ���������ֵ��temp
	{
		strcpy(temp.name, head[sign].name);
		printf("%s\n", head[sign].name);
	}
	else
		gets(temp.name);
	printf("\n\t�ɼ�\n");		//����ɼ�
	temp.score[3] = 0;
	for (i = 0; i < 3; i++)
	{
		printf("\t%s:\n\t", scorename[i]);
		temp.score[i] = Inputscore(0, 100);
		temp.score[3] += temp.score[i];
	}
	printf("\n�Ƿ�ȷ���޸ģ�\n\t1.ȷ��  Else.����\n");		//�ж��Ƿ�ȷ��
	pick = getch();
	if(pick!='1')
		 seekstu('2');					
	else	//����1��stu�е����ݱ��浽�ļ���
	{
		head[i] = temp;
		if ((fp = fopen(STUSCOREFILE, "wb+")) == NULL)		//���ļ�
			return 0;
		res = fwrite(head, sizeof(stu), stunum, fp);
		fclose(fp);
		return res;
	}
	return 0;
}

void failstu()		//ѧ���ҿ���������
{
	int i,j,failnum=0;		//failnumΪ�ҿ���Ŀ
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n��ʦ\t%s\n", teaacc.name);
	printf("TEACHER>>�鿴ѧ���ɼ�>>�ҿ�ѧ������");
	printf("\n\n");
	printf("\t\t\t���    ѧ��    ����    �ɼ�������  ��ѧ  Ӣ��  �ܷ�\n");
	for (i = 0; i < stunum; i++)		//����ѧ���ɼ� �в�����ɲ��������ѧ����Ϣ
	{
		for(j=0;j<SCORENUM;j++)
			if (head[i].score[j] < 60)
			{
				failnum++;
				printf("\t\t\t%-8d%-8s%-8s      %-5g %-5g %-5g %-5g\n",i+1, head[i].num, head[i].name, head[i].score[0], head[i].score[1], head[i].score[2], head[i].score[3]);
				break;
			}
	}
	printf("\n\t\t\t�ҿ�ѧ��������%d\n", failnum);		//����ҿ�����
	printf("\n\t\t\t�����.����");
	getch();
	showstu();
}

void emptystu()		//���ѧ���ɼ�����
{
	int pick;
	FILE *fp;
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("\n��ʦ\t%s\n", teaacc.name);
	printf("TEACHER>>���ѧ���ɼ�");
	printf("\n\n");
	printf("\t\t\tȷ�����ѧ���ɼ���\t1.ȷ��  Else.����\n");
	if ((pick = getch()) == '1')
	{
		printf("\n\t\t\tȷ�����ѧ���ɼ���\t1.ȷ��  Else.����\n");
		if ((pick = getch() )== '1')
		{
			printf("\n\t\t\tȷ�����ѧ���ɼ���\t1.ȷ��  Else.����\n");
			if ((pick = getch() )== '1')
			{
				if ((fp = fopen(STUSCOREFILE, "wb")) == NULL)		//����д��ʽ�ֱ��ѧ���ɼ���ѧ���˺���Ϣ�ļ������Źر��ļ�ָ�룬�������ļ�����
				{
					printf("\n\t\t\t���ʧ��\t");
					fclose(fp);
					Sleep(500);
					emptystu();
				}
				if ((fp = fopen(STUACCFILE, "wb")) == NULL)
				{
					printf("\n\t\t\t���ʧ��\t");
					fclose(fp);
					Sleep(500);
					emptystu();
				}
				printf("\n\t\t\t��ճɹ�\t");
				fclose(fp);
				Sleep(500);
				Teachermenu();
				
			}
			else
			{
				Teachermenu();
			}
		}
		else
		{
			Teachermenu();
		}
	}
	else
	{
		Teachermenu();
	}
}

void getnum(int numbit, char *dest)		//�������ֺ��� numbitΪ�������ֵ�λ����destΪ������ַ�����ַ
{
	int i,j;
	for (i = 0; i < numbit; i++)
	{
		dest[i] = getch();		//��������
		if (dest[i] != '\b'&&dest[i] != '\r')		//���벻Ϊ�˸�ͻس�ʱ
		{
			if (dest[i]<'0' || dest[i]>'9')		//����Ĳ�Ϊ������ʾ�������
			{
				printf("   �Ƿ��ַ�������������");
				Sleep(500);
				for (j = 0; j < 23 + i - 1; j++)
					printf("\b");
				for (j = 0; j < 23 + i - 1; j++)
					printf(" ");
				for (j = 0; j < 23 + i - 1; j++)
					printf("\b");
				printf("\b \b");
				i = -1;
			}
			else	//�������������ַ�
				printf("%c", dest[i]);
		}
		else if (dest[i] == '\b'&& i > 0)		//�����˸����Ѿ�������ַ�
		{
			printf("\b \b");		//ɾ��1���ַ�
			i = i - 2;
		}
		else if (dest[i] == '\r')		//��ǰ����س�
		{
			printf("   λ�����㣬����������");
			Sleep(500);
			for (j = 0; j < 23 + i - 1; j++)		//������27���ַ�����ʱ�Ѿ�����i���ַ�����ӡ��i-1��*��ʹ����һ������ʧ
				printf("\b");
			for (j = 0; j < 23 + i - 1; j++)
				printf(" ");
			for (j = 0; j < 23 + i - 1; j++)
				printf("\b");
			printf("\b ");		//δ֪ԭ����������������һ�������*��Ҫ�ڸǵ�
			i = -1;		//ȷ��ѭ��+1��i=0��������
		}
	}
	dest[i] = 0;		//�ַ���ĩβ���Ͻ�����
	getch();		//�������Ļس�
	printf("\n");
}

void help()
{
	int i;
	system("cls");		//��Ļ��������
	printf("\n\t\t\t\t\t\tѧ���ɼ�����ϵͳ\n\n");
	printf("HELP>>>");
	printf("\n\n\n");
	printf("ѧ���ɼ�����ϵͳ--��1.��¼--��1.1.��ʦ��¼--��1.1.1.�鿴ѧ���ɼ�--��1.1.1.1.ѧ���ɼ�����--��1.1.1.1.1.��ѧ������\n");
	for (i = 0; i < 88; i++)
		printf(" ");
	printf("--��1.1.1.1.2.���ܷ�����\n");
	for (i = 0; i < 88; i++)
		printf(" ");
	printf("--��1.1.1.1.3.�����ĳɼ�����\n");
	for (i = 0; i < 88; i++)
		printf(" ");
	printf("--��1.1.1.1.4.����ѧ�ɼ�����\n");
	for (i = 0; i < 88; i++)
		printf(" ");
	printf("--��1.1.1.1.5.��Ӣ��ɼ�����\n");
	for (i = 0; i < 65; i++)
		printf(" ");
	printf("--��1.1.1.2.ɾ��ѧ���ɼ�--��1.1.1.2.1.��ѧ��ɾ��\n");
	for (i = 0; i < 65+24; i++)
		printf(" ");
	printf("--��1.1.1.2.2.������ɾ��\n");
	for (i = 0; i < 65; i++)
		printf(" ");
	printf("--��1.1.1.3.�޸�ѧ���ɼ�--��1.1.1.3.1.��ѧ���޸�\n");
	for (i = 0; i < 65 + 24; i++)
		printf(" ");
	printf("--��1.1.1.3.2.�������޸�\n");
	for (i = 0; i < 65; i++)
		printf(" ");
	printf("--��1.1.1.4.�ҿ�ѧ������\n");
	for (i = 0; i < 42; i++)
		printf(" ");
	printf("--��1.1.2.���ѧ���ɼ�\n");
	for (i = 0; i < 42; i++)
		printf(" ");
	printf("--��1.1.3.����ѧ���ɼ�--��1.1.3.1.��ѧ�Ų���\n");
	for (i = 0; i < 42+22; i++)
		printf(" ");
	printf("--��1.1.3.2.����������\n");
	for (i = 0; i < 42 + 22; i++)
		printf(" ");
	printf("--��1.1.3.3.���ɼ�����\n");
	for (i = 0; i < 42; i++)
		printf(" ");
	printf("--��1.1.4.���ѧ���ɼ�\n");
	for (i = 0; i < 26; i++)
		printf(" ");
	printf("--��1.2.ѧ����¼\n");
	for (i = 0; i < 16; i++)
		printf(" ");
	printf("--��2.�˺�����--��2.1.ע��--��2.1.1.��ʦע��\n");
	for (i = 0; i < 16+26; i++)
		printf(" ");
	printf("--��2.1.2.ѧ��ע��\n");
	for (i = 0; i < 16; i++)
		printf(" ");
	printf("--��2.�˺�����--��2.2.�޸�����--��2.2.1.��ʦ�޸�����\n");
	for (i = 0; i < 16+30; i++)
		printf(" ");
	printf("--��2.2.2.ѧ���޸�����\n");
	for (i = 0; i < 16; i++)
		printf(" ");
	printf("--��3.����\n");
	printf("\n\t\t�����.����");
	getch();
	Interface();
}

