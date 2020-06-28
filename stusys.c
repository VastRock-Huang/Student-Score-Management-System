/* 学生成绩管理系统 */

/*  2019.08.05   */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>		//包含system()函数
#include<conio.h>		//包含getch()和getche()函数
#include<ctype.h>		
#pragma warning(disable : 4996)		//确保在VS中使用部分C函数

//宏
#define NUMBIT 4		//宏定义学号位数
#define KEYBIT 16		//宏定义密码最大位数
#define SCORENUM 3		//宏定义学生科目数
#define TEAACCFILE "./data/teacheraccount.dat"
#define STUACCFILE "./data/stuaccount.dat"
#define STUSCOREFILE "./data/stu score.dat"


//全局变量
typedef struct student		
{
	char num[NUMBIT+1];		//学号
	char name[15];		//姓名
	float score[4];		//3门成绩+总分
}stu;		//定义学生结构体stu
typedef struct teacher
{
	char name[15];		//姓名
	char key[KEYBIT+1];		//密码
}tea;		//教师账号密码结构体tea
typedef struct
{
	char num[NUMBIT + 1];		//学号
	char name[15];		//姓名
	char key[KEYBIT + 1];		//密码
}stua;		//学生账号密码结构体stua
stu *head;		//录入学生成绩的首地址
stua *stuhead;		//学生账号密码的首地址
stua stuacc;		//登录的学生账号
tea *teahead;		//教师账号密码的首地址
tea teaacc;	//登录的教师账号
char *scorename[3] = { "语文","数学","英语" };		//3门成绩
int stunum;		//录入学生人数
int teanum;		//教师账号数
int keymaxbit = 16;		//密码最多位数
int keyminbit = 6;		//密码最少位数
char *teacherkey = "teacher";		//教师注册的教师秘钥
char *orikey = "123456";		//学生初始密码

//函数声明
void Interface();		//主界面
void signin();		//登录主界面
void teasignin();		//教师登录
void stusignin();		//学生登录
void loadteaacc(tea **);		//加载教师账号密码
void loadstuacc(stua **);		//加载学生账号密码
void accountset();		//账号设置主界面
void signup();		//注册主界面
void teasignup();		//教师注册
void stusignup();		//学生注册
void pass();		//修改密码界面
void teapass();		//教师修改密码
void stupass();		//学生修改密码
void Inputkey(char *,int,int);		//输入密码函数
void Teachermenu();		//教师端菜单界面
void Stumenu();		//学生端成绩界面
void loadstu(stu **);		//加载学生成绩
void showstu();		//查看学生成绩
void stulist();		//学生成绩列表
void paixustu();		//学生成绩不同排序选择
void stusort(char);		//学生成绩排序
void addstu();		//添加学生成绩
void Inputnum(char *);		//输入学号
float Inputscore(float,float);		//输入成绩
void findstu();		//查询学生成绩
void seekstu(char);		//按照姓名或学号查找学生成绩
void foundstu(char choose, char *dest,char opt);		//按照姓名或学号找到学生成绩
size_t delstu(int sign);		//删除学生成绩
size_t modifystu(int sign, char choose);		//修改学生成绩
void failstu();		//学生挂科名单
void emptystu();		//清空学生成绩
int IsGB(unsigned char pText);		//判断中文字符
void getnum(int, char *);		//输入数字
void help();



int main()		//主函数
{
	Interface();		//调用主界面函数
	return 0;
}

void Interface()		//主界面函数
{
	int ichar;
	char pick;		//pick储存选择值
	system("cls");		//清屏操作
	system("color 30");		//设置屏幕背景色和前景色
	printf("\n\n\n\n");		//设置界面
	printf("\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\t\t\t\t\t\t    欢迎使用\n");
	printf("\n\n");
	printf("\t\t\t\t------------------------------------------------\n");
	printf("\t\t\t\t| 请选择：                                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   1.登录                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 2.账号设置                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   3.帮助                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   0.退出                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	//printf("\t\t\t\tPlease Choose: ");		//输入选项
	while ((pick=getch())<'0'|| pick>'3')
	{
		/*printf("\b  \b");		//输入其他值则遮盖掉
		pick = getch();		//从控制台读取字符并立即回显*/
		printf("                                            输入错误，请重新输入");
		Sleep(500);		//暂停进程1s
		for (ichar = 64; ichar > 0; ichar--)		//覆盖掉上面字符
			printf("\b");		//删除前面错误提示
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	} 		//若输入值不为1、2、3则重新输入
	if (pick == '1')
		signin();		//若输入1则进入登录主界面
	else if (pick == '2')
		accountset();		//若输入2则进入账号设置主界面
	else if (pick == '3')
		help();
	else if (pick == '0')
		exit(0);		//若输入0则退出即终止程序
}

void signin()		//登录主函数
{
	int pick, ichar;		//pick储存选择值，ichar为字符循环变量
	system("cls");		//清屏操作
	printf("\n\n\n\n");		//设置界面
	printf("\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n\n\n");
	printf("\t\t\t\t--------------------SIGN IN---------------------\n");
	printf("\t\t\t\t| 请选择登录身份：                             |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 1.教师登录                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 2.学生登录                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   0.返回                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	while((pick=getch())<'0'||pick>'2')		//输入0~2外其他值则提示错误并重新输入
	{
		printf("                                            输入错误，请重新输入");
		Sleep(500);		//暂停进程1s
		for (ichar = 64; ichar > 0; ichar--)		//覆盖掉上面字符
			printf("\b");		//删除前面错误提示
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	} 
	switch (pick)		//判断输入值
	{
	case '0': Interface();		//输入0则返回主界面	//输入0返回主界面
		break;
	case '1': teasignin();		//输入1进入教师登录界面
		break;
	case '2': stusignin();		//输入2进入学生登录界面
		break;
	}
}

void teasignin()		//教师登录函数
{
	int sign, pick;		//sign储存登录教师的账号信息在教师账号信息的序号
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("SIGN UP>>教师登录");
	printf("\n\n\n");
	printf("\t输入教师姓名：");	
	gets(teaacc.name);	//输入教师姓名到登录教师账号结构体中
	printf("\n\t输入账号密码：");
	Inputkey(teaacc.key, keyminbit, keymaxbit);		//输入账号密码到登录教师账号结构体中
	loadteaacc(&teahead);		//加载教师账号信息
	for (sign = 0; sign < teanum; sign++)		//教师账号信息从序号0开始寻找
	{
		if (strcmp(teaacc.name, teahead[sign].name) == 0)		//若找到该教师账号信息
		{
			if (strcmp(teaacc.key, teahead[sign].key) == 0)		//同时密码输入正确
			{
				printf("\n\n\t登陆成功");		//登陆成功
				free(teahead);		//释放教师账号信息的动态内存
				Sleep(300);
				Teachermenu();		//进入教师端菜单界面
			}
			else		//若密码输入错误
			{
				printf("\n\n\t密码错误\t1.重新登录\tElse.返回\n");
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
			break;		//若找到该教师账号信息则跳出循环
		}
	}
	if (sign == teanum)		//若未找到该教师账号信息
	{
		free(teahead);		//释放教师账号信息的动态内存
		printf("\n\n\t账号不存在\t1.重新登录\tElse.返回\n");
		pick = getch();
		if (pick == '1')
			teasignin();
		else
			signin();
	}
}

void stusignin()		//学生登录函数
{
	int sign,pick;		//sign存登录学生信息序号
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("SIGN UP>>学生登录");
	printf("\n\n\n");
	printf("\t输入%d学号：",NUMBIT);
	getnum(NUMBIT,stuacc.num);		//输入学号到登录学生账号结构体中
	printf("\n\t输入姓名：");
	gets(stuacc.name);		//输入姓名到登录学生账号结构体中
	printf("\n\t输入账号密码：");
	Inputkey(stuacc.key, keyminbit, keymaxbit);		//输入密码到登录学生账号结构体中
	loadstuacc(&stuhead);		//加载学生账号信息
	for (sign = 0; sign < stunum; sign++)		//学生账号信息从序号0开始查找
	{
		if (strcmp(stuacc.num, stuhead[sign].num) == 0)		//若存在该学生账号（学号）信息
		{
			if (strcmp(stuacc.name, stuhead[sign].name) == 0)		//同时输入姓名正确
			{
				if (strcmp(stuacc.key, stuhead[sign].key) == 0)		//同时输入密码正确
				{
					printf("\n\n\t登陆成功");		//登陆成功
					free(stuhead);
					Sleep(300);
					Stumenu();
				}
				else		//若密码不正确
				{
					printf("\n\n\t密码错误\t1.重新登录\tElse.返回\n");
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
			else		//若姓名不正确
			{
				printf("\n\n\t学号姓名不一致\t1.重新登录\tElse.返回\n");
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
	if (sign == stunum)		//若未找到该学生账号信息
	{
		free(stuhead);
		printf("\n\n\t账号不存在\t1.重新登录\tElse.返回\n");
		pick = getch();
		if (pick == '1')
			stusignin();
		else
			signin();
	}

}

void loadteaacc(tea **dest)		//加载教师账号信息函数		**dest为教师账号信息数组的二级指针
{

	FILE *fp;
	int i;
	teanum = 0;		//教师数量归0
	if ((fp = fopen(TEAACCFILE, "rb+")) == NULL)		//打开教师账号信息文件teacheraccount.dat
	{
		printf("\n\n\n\n\n\n文件打开失败\n");
		return;
	}
	for (rewind(fp); fgetc(fp) != EOF; teanum++)		//将文件从头读至末尾，没次读取一个字符判断是不是EOF（文件结束符）
	{
		fseek(fp, -1, 1);		//若不为文件末尾，文件内指针回退1个字节
		fseek(fp, sizeof(tea), 1);		//同时向后移动tea大小的字节，教师数+1
	}
	*dest = (tea *)calloc(teanum, sizeof(tea));		//动态内存分配有教师数个tea结构体的数组并用二级指针使dest指向该数组的地址
	for (rewind(fp), i = 0; i < teanum; i++)
		fread(*dest + i, sizeof(tea), 1, fp);		//将教师账号信息文件的教师账号信息存入数组*dest中
	fclose(fp);		//关闭文件指针
}

void loadstuacc(stua **dest)		//加载学生账号信息函数		**dest为学生账号信息数组的二级指针
{
	FILE *fp;
	int i;
	stunum = 0;
	if ((fp = fopen(STUACCFILE, "rb+")) == NULL)
	{
		printf("\n\n\n\n\n\n文件打开失败\n");
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

void accountset()		//账号设置主界面函数
{
	int pick, ichar;
	system("cls");		//清屏操作
	printf("\n\n\n\n");		//设置界面
	printf("\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n\n\n");
	printf("\t\t\t\t--------------------SET  UP---------------------\n");
	printf("\t\t\t\t| 请选择：                                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   1.注册                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 2.修改密码                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   0.返回                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	while ((pick = getch())<'0' || pick>'2')
	{
		printf("                                            输入错误，请重新输入");
		Sleep(500);		//暂停进程1s
		for (ichar = 64; ichar > 0; ichar--)		//覆盖掉上面字符
			printf("\b");		//删除前面错误提示
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': Interface();		//输入0则返回主界面
		break;
	case '1':signup();		//输入1进入注册主界面
		break;
	case '2':pass();		//输入2进入修改密码主界面
		break;
	}
}

void signup()		//注册主界面
{
	int pick, ichar;
	system("cls");		//清屏操作
	printf("\n\n\n\n");		//设置界面
	printf("\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n\n\n"); 
	printf("\t\t\t\t--------------------SIGN UP---------------------\n");
	printf("\t\t\t\t| 请选择注册身份：                             |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 1.教师注册                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 2.学生注册                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   0.返回                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	while ((pick = getch()) < '0' || pick > '2')		//输入0~2外其他值则提示错误并重新输入
	{
		printf("                                            输入错误，请重新输入");
		Sleep(500);		//暂停进程1s
		for (ichar = 64; ichar > 0; ichar--)		//覆盖掉上面字符
			printf("\b");		//删除前面错误提示
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': accountset();//输入0则返回账号设置主界面
		break;
	case '1':teasignup();		//输入1进入教师注册界面
		break;
	case '2':stusignup();		//输入2进入学生注册界面
		break;
	}
}

void teasignup()			//教师注册函数
{
	tea temp;		//temp存注册的教师账号信息
	int pick,i;
	char key[KEYBIT+1];		//key存入再次输入的密码
	FILE *fp;
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("SET UP>>SIGN UP>>教师注册");
	printf("\n\n\n");
	printf("\t输入教师姓名：");
	gets(temp.name);
	loadteaacc(&teahead);		//加载教师账号信息
	for(i=0;i<teanum;i++)
		if (strcmp(temp.name, teahead[i].name) == 0)		//若注册教师已存在教师账号信息中
		{
			printf("\n\t账号已存在\t1.重新注册\tElse.返回");
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
	free(teahead);		//释放教师账号信息内存
	//puts(temp.name);		
	printf("\n\n\t设置6~%d位密码：",keymaxbit);		//设置密码
	Inputkey(temp.key,keyminbit,keymaxbit);
	printf("\n\n\t再次输入密码：");		//再次确认密码
	Inputkey(key,keyminbit,keymaxbit);
	if (strcmp(temp.key, key) != 0)		//若两次密码不一致
	{
		printf("\n\t两次密码不一致\t1.重新注册  Else.返回");
		if ((pick = getch()) == '1')
			teasignup();
		else
			signup();
	}
	printf("\n\n\t输入教师秘钥：");
	Inputkey(key, 0,keymaxbit);
	printf("\n\n\t注册教师账户？\t1.确定   2.重新注册   3.返回\n");
	while ((pick = getch())<'0' || pick>'3')
	{
			printf("输入错误，请重新输入");		//输入其他值则提示错误并重新输入
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
	case '0': signup();		//输入返回注册界面
		break;
	case '1': if (strcmp(teacherkey, key) != 0)		//输入1，若秘钥不正确
	{
		printf("\t秘钥错误\n\t请选择：1.重新注册\tElse.返回\n");
		pick = getch();
		if (pick == '1')
			teasignup();
		else
			signup();
	}
			  else
	{
		if ((fp = fopen(TEAACCFILE, "ab+")) == NULL)		//打开教师账号信息文件并追加读写
		{
			printf("\t注册失败\t1.重新注册\tElse.返回");
			fclose(fp);		//注：写入完一定要关闭文件指针，否则写入的数据无法在程序运行过程中继续使用
			pick = getch();
			if (pick == '1')
				teasignup();
			else
				signup();
		}
		if (fwrite(&temp, sizeof(tea), 1, fp))		//将注册的信息添加到文件中
		{
			printf("\n\t注册成功");
			fclose(fp);
			Sleep(500);
			Interface();
		}
		else
		{
			printf("\t注册失败\t1.重新注册\tElse.返回");
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

void stusignup()		//学生注册函数
{
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("SET UP>>SIGN UP>>学生注册");
	printf("\n\n\n");
	printf("\t学生无需注册，系统录入学生即可登录\n\n\t登录方式：输入学号和姓名\n\t初始密码：%s\n",orikey);
	printf("\n\t任意键.返回");
	getch();
	signup();
}

void pass()		//修改密码主界面函数
{
	int pick, ichar;
	system("cls");		//清屏操作
	printf("\n\n\n\n");		//设置界面
	printf("\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n\n\n");
	printf("\t\t\t\t----------------CHANGE PASSWORD-----------------\n");
	printf("\t\t\t\t| 请选择身份：                                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               1.教师修改密码                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               2.学生修改密码                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                   0.返回                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	while ((pick = getch()) < '0' || pick > '2')		//输入0~2外其他值则提示错误并重新输入
	{
		printf("                                            输入错误，请重新输入");
		Sleep(500);		//暂停进程1s
		for (ichar = 64; ichar > 0; ichar--)		//覆盖掉上面字符
			printf("\b");		//删除前面错误提示
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': accountset();		//输入0则返回主界面
		break;
	case '1':teapass();		//输入1进入教师修改密码
		break;
	case '2':stupass();		//输入2进入学生修改密码
		break;
	}
}

void teapass()		//教师修改密码函数
{
	int sign, pick,i;		//sign为修改密码教师账号信息的序号，pick为选择值
	tea temp;		//temp存入修改的信息
	FILE *fp;
	char key[KEYBIT + 1];	//储存再次确认的密码
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("SET UP>>教师修改密码");
	printf("\n\n\n");
	loadteaacc(&teahead);		//加载教师账号信息
	printf("\t输入教师姓名：");
	gets(temp.name);
	for (sign = 0; sign < teanum; sign++)		//从序号0查找教师账号信息
	{
		if (strcmp(temp.name, teahead[sign].name) == 0)		//若输入教师姓名存在
		{
			printf("\n\t输入账号原密码：");
			Inputkey(temp.key, keyminbit, keymaxbit);		//输入原密码
			if (strcmp(temp.key, teahead[sign].key) == 0)		//若原密码正确
			{
				printf("\n\n\t输入账号新密码：");
				Inputkey(temp.key, keyminbit, keymaxbit);
				printf("\n\n\t再次确认新密码：");
				Inputkey(key, keyminbit, keymaxbit);
				if (strcmp(temp.key, key) == 0)		//若两次密码相同
				{
					printf("\n\n\t确定修改密码？\t1.确定   2.重新修改   0.返回\n");
					while ((pick = getch()) < '0' || pick > '2')
					{
						printf("输入错误，请重新输入");		//输入其他值则提示错误并重新输入
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
					case '0':free(teahead);		//输入0释放教师账号信息的动态内存返回修改密码主界面
						pass();
						break;
					case '1':teahead[sign] = temp;		//将修改的教师账号信息复制到原来对应的教师账号信息上
						if ((fp = fopen(TEAACCFILE, "wb+")) == NULL)
						{
							printf("\n\t修改密码失败");
							Sleep(500);
							teapass();
						}
						if (fwrite(teahead, sizeof(tea), teanum, fp))		//将修改后的教师账号信息数组重新写入文件中
						{
							printf("\n\t修改密码成功");
							fclose(fp);
							free(teahead);
							Sleep(500);
							pass();
						}
						else
						{
							printf("\n\t修改密码失败");
							fclose(fp);
							free(teahead);
							Sleep(500);
							teapass();
						}
						break;
					case '2':free(teahead);		//输入2重新修改密码
						teapass();
						break;
					}
				}
				else
				{
					printf("\n\t两次密码不一致，请重新修改");
					free(teahead);
					Sleep(500);
					teapass();
				}
			}
			else
			{
				printf("\n\n\t账号密码错误\t 1.重新修改\tElse.返回");
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
	if (sign == teanum)		//若无该账号
	{
		printf("\n\t无该账号\t1.重新修改\t Else.返回");
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

void stupass()		//学生修改密码函数
{
	int sign, pick, i;
	stua temp;		//temp存入修改的学生账号信息
	FILE *fp;
	char key[KEYBIT + 1];	//储存再次确认的密码
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("SET UP>>>>学生修改密码");
	printf("\n\n\n");
	loadstuacc(&stuhead);		//加载学生账号信息
	printf("\t输入学生%d位学号：",NUMBIT);
	getnum(NUMBIT, temp.num);		//输入学号
	printf("\n\t输入学生姓名：");
	gets(temp.name);
	for (sign = 0; sign < stunum; sign++)		//判断学生账号信息是否存在
	{
		if (strcmp(temp.num, stuhead[sign].num) == 0)		//若信息存在
		{
			if (strcmp(temp.name, stuhead[sign].name) == 0)		//同时姓名输入正确
			{
				printf("\n\t输入账号原密码：");
				Inputkey(temp.key, keyminbit, keymaxbit);
				if (strcmp(temp.key, stuhead[sign].key) == 0)		//同时原密码输入正确
				{
					printf("\n\n\t输入账号新密码：");
					Inputkey(temp.key, keyminbit, keymaxbit);
					printf("\n\n\t再次确认新密码：");
					Inputkey(key, keyminbit, keymaxbit);
					if (strcmp(temp.key, key) == 0)		//同时两次密码输入一致
					{
						printf("\n\n\t确定修改密码？\t1.确定   2.重新修改   0.返回\n");
						while ((pick = getch()) < '0' || pick > '2')
						{
							printf("输入错误，请重新输入");		//输入其他值则提示错误并重新输入
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
						case '0':free(stuhead);		//输入0返回修改密码界面
							pass();
							break;
						case '1':stuhead[sign] = temp;		//输入1 将修改的学生账号信息赋值给原来的账号
							if ((fp = fopen(STUACCFILE, "wb+")) == NULL)
							{
								printf("\n\t修改密码失败");
								Sleep(500);
								stupass();
							}
							if (fwrite(stuhead, sizeof(stua), stunum, fp))
							{
								printf("\n\t修改密码成功");
								fclose(fp);
								free(stuhead);
								Sleep(500);
								pass();
							}
							else
							{
								printf("\n\t修改密码失败");
								fclose(fp);
								free(stuhead);
								Sleep(500);
								teapass();
							}
							break;
						case '2':free(stuhead);		//输入2重新修改学生密码
							stupass();
							break;
						}
					}
					else
					{
						printf("\n\t两次密码不一致，请重新修改");
						free(stuhead);
						Sleep(500);
						stupass();
					}
				}
				else
				{
					printf("\n\n\t账号密码错误\t 1.重新修改\tElse.返回");
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
				printf("\n\n\t学号姓名不一致\t 1.重新修改\tElse.返回");
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
		printf("\n\t无该账号\t1.重新修改\t Else.返回");
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
	
void Inputkey(char *key,int minbit,int maxbit)		//输入密码函数  key为密码储存地址，minbit为密码最少位数，maxbit为密码最多位数
{
	int i,j;
	for (i = 0; i < maxbit; i++)		//最多输入maxbit位密码
	{
		key[i] = getch();		//输入密码
		if (key[i] != '\r'&&key[i] != '\b')		//输入字符不为回车或退格
		{
			if (IsGB(key[i]) != 0 || isgraph(key[i]) == 0)	//输入字符不为汉字或者输入字符不可打印
			{
				printf("   非法字符，请重新输入");
					Sleep(500);
					for (j = 0; j < 23 + i - 1; j++)		//清除提示字符
						printf("\b");
					for (j = 0; j < 23 + i - 1; j++)
						printf(" ");
					for (j = 0; j < 23 + i - 1; j++)
						printf("\b");
					printf("\b \b");		//特殊原因需多清除一个字符
					i = -1;		//i=-1循环完后变为i=0，即重新输入
			}
			else
				putchar('*');		//若为正常字符则打印*
		}
		else if (key[i] == '\r')		//若输入回车（Windows中getch()输入回车得到'\r''\n'两个字符，返回值即为'\r'）
		{
			if (i < minbit)		//若输入字符少于最少密码位数
			{
				printf("   密码位数不足，请重新输入");
					Sleep(500);
					for (j = 0; j < 27 + i - 1; j++)		//上面有27个字符，此时已经输入i个字符，打印了i-1个*，使得这一部分消失
						printf("\b");
					for (j = 0; j < 27 + i - 1; j++)
						printf(" ");
					for (j = 0; j < 27 + i - 1; j++)
						printf("\b");
				printf("\b ");		//未知原因上述操作会留下一个多余的*需要遮盖掉
				i = -1;		//确保循环+1后i=0重新输入
			}
			else		//若输入字符大于最少输入密码位数则退出输入循环
				break;
		}
		else if (key[i] == '\b'&& i>0 )		//若输入退格且输入字符数大于1(i>0)，则覆盖掉最后一个字符并重新输入该字符
		{
			printf("\b \b");
			i = i - 2;
		}
	}
	key[i] = 0;		//最后一位添加结束符
}

int IsGB(unsigned char pText)		//判断中文字符函数 pText为待判断的字符
{
	if (pText >= 161)
		if (pText == 163)
			return 1;//全角字符
		else
			return 2;//汉字
	else
		return 0;//英文、数字、英文标点
}

void Teachermenu()		//教师端菜单界面函数
{
	char pick;
	int ichar;
	system("cls");		//屏幕设置及界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n教师\t%s\n", teaacc.name);		//显示登陆账号
	printf("\n\n\n");
	printf("\t\t\t\t--------------------TEACHER---------------------\n");
	printf("\t\t\t\t| 请选择：                                     |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               1.查看学生成绩                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               2.添加学生成绩                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               3.查找学生成绩                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|               4.清空学生成绩                 |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t|                 0.退出登录                   |\n");
	printf("\t\t\t\t|                                              |\n");
	printf("\t\t\t\t------------------------------------------------\n");
	loadstu(&head);		//加载学生成绩
	while ((pick = getch()) < '0' || pick > '4')		//输入0~2外其他值则提示错误并重新输入
	{
		printf("                                            输入错误，请重新输入");
		Sleep(500);		//暂停进程1s
		for (ichar = 64; ichar > 0; ichar--)		//覆盖掉上面字符
			printf("\b");		//删除前面错误提示
		for (ichar = 64; ichar > 0; ichar--)
			printf(" ");
		for (ichar = 64; ichar > 0; ichar--)
			printf("\b");
	}
	switch (pick)
	{
	case '0': free(head);
		Interface();//输入0则返回主界面
		break;
	case '1': showstu();		//输入1则查看学生成绩
		break;
	case '2': addstu();		//输入2则添加学生成绩
		break;
	case '3': findstu();		//输入3查找学生成绩
		break;
	case '4':emptystu();		//输入4清空学生成绩
		break;
	}
}

void Stumenu()		//学生端界面函数
{
	int sign;		//登陆学生在学生成绩中的序号
	int rank[SCORENUM+1];		//科目排名	
	int failnum = 0;
	int person,score;
	int i;
	for (i = 0; i < SCORENUM + 1; i++)		//科目排名数组初始化全部元素为1
	{
		rank[i] = 1;
	}
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n学生\t%s\n", stuacc.name);		//显示登陆学生
	printf("STUDENT>>");
	printf("\n\n");
	loadstu(&head);		//加载学生成绩
	printf("\t\t\t\t\t科目：语文  数学  英语  总分\n");		//输出登陆学生成绩
	for (sign = 0; sign < stunum; sign++)
	{
		if (strcmp(stuacc.num, head[sign].num) == 0)
		{
			printf("\n\t\t\t\t\t成绩  %-5g %-5g %-5g %-5g\n", head[sign].score[0], head[sign].score[1], head[sign].score[2], head[sign].score[3]);
			break;
		}
	}
	printf("\n\t\t\t\t\t排名  ");		//输出登陆学生排名
	for (score = 0; score < SCORENUM+1; score++)		//每门成绩分别排名
	{
		for (person = 0; person < stunum; person++)		//登陆学生与所有学生进行比较
		{
			if (head[sign].score[score] < head[person].score[score])		//若登陆学生成绩低于某一学生，则排名后移一位
				rank[score]++;
		}
		printf("No.%-2d ", rank[score]);
	}
	printf("\n\n\t\t\t\t\t挂科情况：");		//输出挂科情况
	for (score = 0; score < SCORENUM; score++)
	{
		if (head[sign].score[score] < 60)		//若有挂科则输出该课程名字
		{
			failnum++;
			printf("%s  ", scorename[score]);
		}
	}
	if (failnum >0)
	{
		printf("共%d门", failnum);		//输出挂科数目
	}
	else		//若无挂科则将挂科提示字符覆盖
	{
		for (i = 0; i < 10; i++)
			printf("\b");
		for (i = 0; i < 10; i++)
			printf(" ");
		for (i = 0; i < 10; i++)
			printf("\b");
	}
	printf("\n\n任意键.退出登录");
	getch();
	free(head);
	Interface();
}

void loadstu(stu **dest)		//加载学生信息函数
{
	FILE *fp;
	int i;
	stunum = 0;	//每次加载学生人数初始化为0
	if ((fp = fopen(STUSCOREFILE, "rb+")) == NULL)
	{
		printf("\n\n\n\n\n\n文件打开失败\n");
		return;
	}
	for (rewind(fp); fgetc(fp) != EOF; stunum++)		//计算学生人数
	{
		fseek(fp, -1, 1);
		fseek(fp, sizeof(stu), 1);
	}
	*dest = (stu *)calloc(stunum, sizeof(stu));		//创建储存学生成绩的动态内存数组
	for (rewind(fp), i = 0; i < stunum; i++)
		fread(*dest + i, sizeof(stu), 1, fp);		//读入学生成绩
	fclose(fp);
}

void addstu()		//添加学生成绩函数
{
	FILE *fp;
	stu temp;		//临时记录学生成绩的结构体
	stua tempp;		//临时记录学生账号信息的结构体
	int i;
	char pick;
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n教师\t%s\n", teaacc.name);
	printf("TEACHER>>添加学生成绩");
	printf("\n\n");
	printf("\t学号：");		//输入学号
	Inputnum(temp.num);
	strcpy(tempp.num, temp.num);		//将学号复制到学生账号信息中
	printf("\t姓名：");		//输入姓名
	gets(temp.name);
	strcpy(tempp.name, temp.name);	//将姓名复制到学生账号信息中
	strcpy(tempp.key, orikey);		//将初始密码赋值到学生账号信息中
	printf("\n\t成绩：\n");		//输入每门科目成绩
	temp.score[SCORENUM] = 0;
	for (i = 0; i < SCORENUM; i++)		
	{
		printf("\t%s:",scorename[i]);
		temp.score[i] = Inputscore(0,100);		//输入分数
		temp.score[SCORENUM] += temp.score[i];		//总分为所有科目成绩之和
	}
	printf("\n是否确定录入？\n\t1.确定  2.重新录入  0.返回\n");		//判断是否确定
	while ((pick = getch()) < '0' || pick > '2')
	{
		printf("输入错误，请重新输入");		//输入其他值则提示错误并重新输入
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
	case '0': Teachermenu();		//输入0 返回教师端菜单界面
		break;
	case '1':		//输入1将stu中的数据保存到文件中
		if ((fp = fopen(STUACCFILE, "ab+")) == NULL)
		{
			printf("文件打开失败\n");
			Teachermenu();
		}
		if (fwrite(&tempp, sizeof(stua), 1, fp) == 0)		//将学生账号信息写入学生账号信息文件stuaccount.dat中
		{
			printf("\t保存失败 请重新录入\n");		//保存数据失败则重新录入
			fclose(fp);
			Sleep(1000);
			addstu();
		}
		fclose(fp);
		if ((fp = fopen(STUSCOREFILE, "ab+")) == NULL)		//打开文件
		{
			printf("文件打开失败\n");
			Teachermenu();
		}
		if (fwrite(&temp, sizeof(stu), 1, fp))		//将学生成绩写入学生成绩文件stu score.dat中  返回非零值则录入成功
		{
			fclose(fp);
			printf("\t保存成功\n");
			printf("是否继续录入？\n\t1.是\tElse.否\n\t");
			if (getch() == '1')		//若输入1则继续录入，重新回到添加学生成绩函数
				addstu();
			else
				Teachermenu();		//输入其他值则返回教师端菜单界面
		}
		else		//fwrite()返回0录入失败
		{
			printf("\t保存失败 请重新录入\n");		//保存数据失败则重新录入
			fclose(fp);
			Sleep(1000);
			addstu();
		}
		break;
	case '2': addstu();		//输入2则重新录入重新回到添加学生成绩函数
		break;
	}
}

void showstu()		//查看学生成绩函数
{
	int i, pick;
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n教师\t%s\n", teaacc.name);
	printf("TEACHER>>查看学生成绩");
	printf("\n\n");
	if (stunum == 0)		//若学生数为0则无学生成绩
	{
		puts("\t没有记录\n\t按任意键返回");
		getch();
		Teachermenu();
	}
	stulist();		//输出学生成绩
	printf("\n\t\t功能处理：1.学生成绩排序    2.删除学生成绩\n\t\t\t  3.修改学生成绩    4.挂科学生名单\n\t\t\t  0.返回\n");		//功能选择
	do
	{
		pick = getch();		//输入选项

		if (pick == '0')
			Teachermenu();		//输入0则返回主界面
		else if (pick == '1')
			paixustu();		//输入1进入不同排序选择
		else if (pick == '2')
			seekstu('1');		//输入2进入删除式查找
		else if (pick == '3')
			seekstu('2');		//输入3进入修改式查找
		else if (pick == '4')
			failstu();		//输入4进入挂科名单
		else 
		{
			printf("                输入错误，请重新输入");		//输入其他值则提示错误并重新输入
			Sleep(100);
			for (i = 36; i > 0; i--)
				printf("\b");
			for (i = 36; i > 0; i--)
				printf(" ");
			for (i = 36; i > 0; i--)
				printf("\b");
		}
	} while (pick<'0' || pick>'4');		//输入其他值则提示错误并重新输入
}

void stulist()		//学生成绩列表函数
{
	int i;
	printf("\t\t\t学生人数：%d\n", stunum);	
	printf("\t\t\t序号    学号    姓名    成绩：语文  数学  英语  总分\n");
	for (i = 0; i < stunum; i++)
	{
		printf("\t\t\t%-8d%-8s%-8s      %-5g %-5g %-5g %-5g\n", i+1,head[i].num, head[i].name, head[i].score[0], head[i].score[1], head[i].score[2], head[i].score[3]);
	}
}

void Inputnum(char *num)		//输入学号函数  *num为学号存放首地址
{
	int i,j,pick,sign;
	getnum(NUMBIT, num);		//输入数字
	if(stunum>0)		//若学生人数大于0
		for (sign = 0; sign < stunum; sign++)		//学生遍历
		{
			if (strcmp(num, head[sign].num) == 0)		//若学号已存在
			{
				printf("   成员已录入。请选择：1.录入其他成员 2.重新录入该成员 0.返回");
				while ((pick = getch()) < '0' || pick > '2')
				{
					printf("输入错误，请重新输入");		//输入其他值则提示错误并重新输入
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
				case '0': Teachermenu();		//输入0则返回主界面
				case '1': addstu();
					break;
				case '2': for (j = 0; j < 60; j++)
						{
							printf("\b");
						}
						  printf("   重新录入                                                  ");
						  delstu(sign);		//删除该学生成绩
						  break;
				}
			}
		}
	printf("\n");
}

float Inputscore(float minnum,float maxnum)		//输入成绩函数（输入浮点数函数）	minmum为输入下限，maxnum为输入上线
{
	char s[20];		//s储存输入的浮点数
	int i;		//len为输入的浮点数的字符长度
	float score;		//存放转换后的浮点数
	gets_s(s, 20);		//输入浮点数
	while((score =(float) atof(s)) == 0 || score < minnum || score>maxnum)		//若输入字符串转换化为浮点数atof()不成功，返回不为0，且在不在上下限之间
	{
		printf("\t输入不合法，请重新输入");
		Sleep(300);
		for (i = 0; i < 23; i++)
			printf("\b");
		for (i = 0; i < 23; i++)
			printf(" ");
		for (i = 0; i < 22; i++)
			printf("\b");
		gets_s(s, 6);
	}
	return score;		//返回浮点数
}

void paixustu()		//学生成绩不同排序选择函数
{
	int i;
	int choose;		//选择值
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n教师\t%s\n", teaacc.name);
	printf("TEACHER>>查看学生成绩>>学生成绩排序");
	printf("\n\n");
	stulist();		//输出学生成绩
	printf("\n\t\t请选择：1.按学号排序       2.按总分排序      3.按语文成绩排序\n\t\t\t4.按数学成绩排序   5.按英语成绩排序\n\t\t\t0.返回\n");
	while ((choose = getch()) < '0' || choose > '5')
	{
		printf("                输入错误，请重新输入");		//输入其他值则提示错误并重新输入
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

void stusort(char choose)		//学生成绩排序函数	choose为排序选项
{
	int i,j,pick;
	stu *sort;		//储存拷贝的学生成绩数组首地址
	stu temp;		//用于stu交换的临时结构体
	FILE *fp;
	sort = (stu *)calloc(stunum, sizeof(stu));		//创建动态内存并存入学生成绩
	memcpy(sort, head, sizeof(stu)*stunum);
	for (i = 0; i < stunum-1; i++)		//选择排序法
	{
		for (j = i + 1; j < stunum; j++)
		{
			switch (choose)		//根据选项进行不同条件排序
			{
			case '1':if (strcmp(sort[i].num, sort[j].num) > 0)		//按学号排序
				{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
				}
					 break;
			case '2':if (sort[i].score[SCORENUM] < sort[j].score[SCORENUM])		//按总分排序
				{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
				}
					 break;
			case '3': if (sort[i].score[0] < sort[j].score[0])		//按语文成绩排序
				{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
				}
					  break;
			case '4': if (sort[i].score[1] < sort[j].score[1])		//按数学成绩排序
				{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
				}
					  break;
			case '5': if (sort[i].score[2] < sort[j].score[2])		//按英语成绩排序
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
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n教师\t%s\n", teaacc.name);
	switch (choose)
	{
	case '1':printf("TEACHER>>查看学生成绩>>按学号排序");
		break;
	case '2':printf("TEACHER>>查看学生成绩>>按总分排序");
		break;
	case '3':printf("TEACHER>>查看学生成绩>>按语文成绩排序");
		break;
	case '4':printf("TEACHER>>查看学生成绩>>按数学成绩排序");
		break;
	case '5':printf("TEACHER>>查看学生成绩>>按英语成绩排序");
		break;
	}
	printf("\n\n");
	printf("\t\t\t学生人数：%d\n", stunum);		//输出排序后的成绩列表
	printf("\t\t\t序号    学号    姓名    成绩：语文  数学  英语  总分\n");
	for (i = 0; i < stunum; i++)
	{
		printf("\t\t\t%-8d%-8s%-8s      %-5g %-5g %-5g %-5g\n", i+1,sort[i].num, sort[i].name, sort[i].score[0], sort[i].score[1], sort[i].score[2], sort[i].score[3]);
	}
	printf("\n\t\t请选择：1.以此顺序保存   Else.返回至原顺序\n\t");
	if ((pick = getch()) == '1')
	{
		if ((fp = fopen(STUSCOREFILE, "wb+")) == NULL)
		{
			printf("\n\n\n\n\n\n文件打开失败\n");
			stusort(choose);
		}
		if (fwrite(sort, sizeof(stu), stunum, fp) == stunum)		//若排序保存成功
		{
			printf("\n录入成功\n");
			free(sort);
			Sleep(500);
			fclose(fp);
			free(head);
			loadstu(&head);		//重新加载学生成绩
			showstu();
		}
		else
		{
			printf("\n录入失败\n");
			fclose(fp);
			free(sort);
			Sleep(1000);
			showstu();
		}
	}
	else
		paixustu();		//返回
}

void findstu()		//查询学生成绩函数
{
	char num[NUMBIT + 1],name[15];		//num，name用于储存查询的学生信息
	int *sign,i,pick,choose,signnum=0;		//sign为指向符合条件的序号的数组的指针，signnum为符合条件的序号数目
	float score;		//储存查询的成绩
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n教师\t%s\n", teaacc.name);
	printf("TEACHER>>查询学生成绩");
	printf("\n\n");
	printf("\t\t请选择查询方式： 1.按学号查找\t2.按姓名查找\t3.按成绩查找\t\n\t\t                 0.返回\n\n");
	sign = (int *)calloc(stunum, sizeof(int));		//创建一个大小为学生数的数组用于储存符合条件的序号（因为符合条件的数目最多为学生数）
	while ((pick = getch()) < '0' || pick > '3')
	{
		printf("                输入错误，请重新输入");		//输入其他值则提示错误并重新输入
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
	case '0': Teachermenu();		//输入0则返回主界面
	case '1':printf("\t\t请输入查询学号：");
		getnum(NUMBIT, num);
		for (sign[signnum] = 0; sign[signnum] < stunum; sign[signnum]++)		//signnum初始值为0，sign[0]从0开始遍历
		{
			if (strcmp(num, head[sign[signnum]].num) == 0)		//若找到和输入学号相同的学生则退出，此时sign[signnum]即sign[0]中存放着符合条件的学生的序号
				break;
		}
		break;
	case '2':printf("\t\t请输入查询姓名：");
		gets_s(name, 15);
		for (sign[signnum] = 0; sign[signnum] < stunum; sign[signnum]++)
		{
			if (strcmp(name, head[sign[signnum]].name) == 0)		//若找到和输入名字相同的学生则退出，此时sign[signnum]即sign[0]中存放着符合条件的学生的序号
				break;
		}
		break;
	case '3': printf("\t\t按成绩查询：1.按总分查询  2.按语文成绩查询  3.按数学成绩查询  4.按英语成绩查询\n\t\t            0.返回\n");
		while ((choose = getch()) < '0' || choose > '4')
		{
			printf("                输入错误，请重新输入");		//输入其他值则提示错误并重新输入
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
		case '1': printf("\t\t请输入查询总分：");
			score = Inputscore(0, 300);
			for (sign[signnum] = 0; sign[signnum] < stunum; sign[signnum]++)		//signnum初始值为0，sign[0]从0开始遍历
			{
				if (score == head[sign[signnum]].score[3])		//若找到和输入分数一致的学生
				{
					signnum++;		//符合条件序号数目signnum+1
					sign[signnum] = sign[signnum - 1];		//同时将sign[signnum]的初始值赋值为上一个sign元素的值
							//此时循环的判断条件变成了第二个元素sign[signnum]与学生人数比较，sign的前一个元素的值得以保留，最终所以学生都会遍历一遍
							//sign数组中将保留符合条件的所有的学生序号，其中最后一个序号需要进行跳出循环判断，因而不符合条件
				}
			}
			break;
		case '2':  printf("\t\t请输入查询语文成绩：");
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
		case '3': printf("\t\t请输入数学成绩：");
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
		case '4': printf("\t\t请输入查询英语成绩：");
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
	if (sign[0] == stunum)		//若序号数组首元素即sign[0]等于学生人数，则无符合条件的学生
	{
		printf("\t\t\t未查询到，请重新查询");
		Sleep(500);
		findstu();
	}
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n教师\t%s\n", teaacc.name);
	switch (pick)
	{
		case '1':printf("TEACHER>>查询学生成绩>>按学号查询");
			break;
		case '2':printf("TEACHER>>查询学生成绩>>按姓名查询");
			break;
		case '3': switch (choose)
			{	
			case '1':printf("TEACHER>>查询学生成绩>>按成绩查询>>按总分查询");
				break;
			case '2':printf("TEACHER>>查询学生成绩>>按成绩查询>>按语文成绩查询");
				break;
			case '3':printf("TEACHER>>查询学生成绩>>按成绩查询>>按数学成绩查询");
				break;
			case '4':printf("TEACHER>>查询学生成绩>>按成绩查询>>按英语成绩查询");
				break;
			}
			break;
	}
	printf("\n\n");
	printf("\t\t\t学号    姓名    成绩：语文  数学  英语  总分\n");		//输出符合条件的学生成绩
	for(i=0;i<signnum+1 && sign[i]<stunum;i++)		//符合条件序号遍历（signnum从0开始，所以signnum+1位符合条件序号的个数），同时排除最后一个跳出循环的序号数组元素，因此要满足元素sign[i]小于学生人数
		printf("\t\t\t%-8s%-8s      %-5g %-5g %-5g %-5g\n", head[sign[i]].num, head[sign[i]].name, head[sign[i]].score[i], head[sign[i]].score[1], head[sign[i]].score[2], head[sign[i]].score[3]);
	free(sign);		//释放序号数组的动态内存
	printf("\n\t\t是否继续查询？  1.是\tElse.否\n\t");
	if (getch() == '1')		
		findstu();
	else
		Teachermenu();		//输入其他值则返回教师端菜单界面
}

void seekstu(char choose)		//按照姓名或学号查找学生成绩  choose为选项：1为删除 2为修改
{
	char num[NUMBIT + 1],name[15];		//num，name用于储存查询的学生信息	
	int pick;
	int i;
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n教师\t%s\n", teaacc.name);
	if(choose=='1')
		printf("TEACHER>>查看学生成绩>>删除学生成绩");
	else if(choose=='2')
		printf("TEACHER>>查看学生成绩>>修改学生成绩");
	printf("\n\n");
	stulist();
	if (choose == '1')
		printf("\n\t\t请选择删除方式： 1.按学号删除\t2.按姓名删除\n\t\t                 0.返回\n\n");
	else if(choose =='2')
		printf("\n\t\t请选择修改方式： 1.按学号修改\t2.按姓名修改\n\t\t                 0.返回\n\n");
	while ((pick = getch()) < '0' || pick > '2')
	{
		printf("                输入错误，请重新输入");		//输入其他值则提示错误并重新输入
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
	case '1': printf("\t\t请输入学生学号：");
		getnum(NUMBIT, num);
		foundstu('1', num, choose);		//按学号找到学生成绩
		break;
	case '2': printf("\t\t请输入学生姓名：");
		gets_s(name, 15);
		foundstu('2', name, choose);		//按姓名找到学生成绩
		break;
	}
}

void foundstu(char choose,char *dest,char opt)		//按照姓名或学号找到学生成绩函数	choose为选项：1为按照学号 2为按照姓名，dest为待查询的字符串（学号或姓名），opt为选项：1为删除 2为修改
{
	int sign;		//sign储存待查询学生的序号
	int pick;
	for (sign = 0; sign < stunum; sign++)		//学生成绩遍历
	{
		if (choose == '1')		//若按学号查询
		{
			if (strcmp(dest, head[sign].num) == 0)		//找到学号则退出
				break;
		}
		else if (choose == '2')		//若按姓名查询
		{
			if (strcmp(dest, head[sign].name) == 0)		//找到姓名则退出
				break;
		}
	}
	if (sign == stunum)
	{
		printf("\t\t未查询到，请重新查询");
		Sleep(500);
		seekstu(opt);
	}
	else		//若查询到
	{
		if(opt=='1')
			printf("\t\t已查询到，是否确定删除？\t1.确定\tElse.取消\n");
		else if(opt=='2')
			printf("\t\t已查询到，是否确定修改？\t1.确定\tElse.取消\n");
		pick = getch();
		if (pick != '1')
			seekstu(opt);		//返回
		else  if(opt=='1')		//若删除选项
		{	
			if (delstu(sign))		//删除学生成绩
			{
				system("cls");		//屏幕界面设置
				printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
				printf("\n教师\t%s\n", teaacc.name);
				printf("TEACHER>>查看学生成绩>>删除学生成绩");
				printf("\n\n");
				stulist();
				printf("\n\t\t已删除\n\t\t是否继续删除？\t 1.是\tElse.否");
				pick = getch();
				if (pick == '1')
					seekstu('1');
				else
					showstu();
			}
			else
			{
				printf("\n\t\t删除失败，请重新删除");
				Sleep(500);
				seekstu('1');		//返回
			}
		}
		else if (opt == '2')		//若修改选项
		{
			if (modifystu(sign,choose))
			{
				system("cls");		//屏幕界面设置
				printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
				printf("\n教师\t%s\n", teaacc.name);
				printf("TEACHER>>查看学生成绩>>修改学生成绩");
				printf("\n\n");
				stulist();
				printf("\n\t\t已修改\n\t\t是否继续修改？\t 1.是\tElse.否\n");
				pick = getch();
				if (pick == '1')
					seekstu('2');
				else
					showstu();
			}
			else
			{
				printf("\n\t\t修改失败，请重新修改");
				Sleep(500);
				seekstu('2');
			}
		}
	}
}

size_t delstu(int sign)		////删除学生成绩函数 sign为待删除的学生序号，返回0删除失败，非0删除成功
{
	int i;
	size_t res;//res为fwrite的返回值
	FILE *fp;
	for (i = sign; i < stunum - 1; i++)		//由待删除学生序号位置，学生成绩向前覆盖即将该学生成绩删除
		head[i] = head[i + 1];
	stunum--;
	if ((fp = fopen(STUSCOREFILE, "wb+")) == NULL)
	{
		return 0;
	}
	res = fwrite(head, sizeof(stu), stunum, fp);		//将删除后的学生成绩写入文件
	fclose(fp);
	free(head);		//释放原有学生成绩
	loadstu(&head);		//重新加载学生成绩
	return res;		//返回fwrite的返回值，非零则写入成功

}

size_t modifystu(int sign,char choose)		//修改学生成绩函数  sign为待修改学生成绩序号，choose为选项：1为已知学号 2为已知姓名，返回0修改失败，非0修改成功
{
	int i;
	size_t res;
	int pick;
	stu temp;		//temp储存临时的修改信息
	FILE *fp;
	printf("\t学号\n\t");		//输入学号
	if (choose == '1')		//已知学号则直接输出并赋值给temp
	{
		strcpy(temp.num, head[sign].num);
		printf("%s\n", head[sign].num);
	}
	else
		getnum(NUMBIT, temp.num);
	printf("\n\t姓名\n\t");		//输入姓名
	if (choose == '2')		//已知姓名则直接输出并赋值给temp
	{
		strcpy(temp.name, head[sign].name);
		printf("%s\n", head[sign].name);
	}
	else
		gets(temp.name);
	printf("\n\t成绩\n");		//输入成绩
	temp.score[3] = 0;
	for (i = 0; i < 3; i++)
	{
		printf("\t%s:\n\t", scorename[i]);
		temp.score[i] = Inputscore(0, 100);
		temp.score[3] += temp.score[i];
	}
	printf("\n是否确定修改？\n\t1.确定  Else.返回\n");		//判断是否确定
	pick = getch();
	if(pick!='1')
		 seekstu('2');					
	else	//输入1将stu中的数据保存到文件中
	{
		head[i] = temp;
		if ((fp = fopen(STUSCOREFILE, "wb+")) == NULL)		//打开文件
			return 0;
		res = fwrite(head, sizeof(stu), stunum, fp);
		fclose(fp);
		return res;
	}
	return 0;
}

void failstu()		//学生挂科名单函数
{
	int i,j,failnum=0;		//failnum为挂科数目
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n教师\t%s\n", teaacc.name);
	printf("TEACHER>>查看学生成绩>>挂科学生名单");
	printf("\n\n");
	printf("\t\t\t序号    学号    姓名    成绩：语文  数学  英语  总分\n");
	for (i = 0; i < stunum; i++)		//遍历学生成绩 有不及格可不则输出该学生信息
	{
		for(j=0;j<SCORENUM;j++)
			if (head[i].score[j] < 60)
			{
				failnum++;
				printf("\t\t\t%-8d%-8s%-8s      %-5g %-5g %-5g %-5g\n",i+1, head[i].num, head[i].name, head[i].score[0], head[i].score[1], head[i].score[2], head[i].score[3]);
				break;
			}
	}
	printf("\n\t\t\t挂科学生人数：%d\n", failnum);		//输出挂科人数
	printf("\n\t\t\t任意键.返回");
	getch();
	showstu();
}

void emptystu()		//清空学生成绩函数
{
	int pick;
	FILE *fp;
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("\n教师\t%s\n", teaacc.name);
	printf("TEACHER>>清空学生成绩");
	printf("\n\n");
	printf("\t\t\t确定清空学生成绩？\t1.确定  Else.返回\n");
	if ((pick = getch()) == '1')
	{
		printf("\n\t\t\t确定清空学生成绩？\t1.确定  Else.返回\n");
		if ((pick = getch() )== '1')
		{
			printf("\n\t\t\t确定清空学生成绩？\t1.确定  Else.返回\n");
			if ((pick = getch() )== '1')
			{
				if ((fp = fopen(STUSCOREFILE, "wb")) == NULL)		//用重写方式分别打开学生成绩和学生账号信息文件，接着关闭文件指针，则会清空文件内容
				{
					printf("\n\t\t\t清空失败\t");
					fclose(fp);
					Sleep(500);
					emptystu();
				}
				if ((fp = fopen(STUACCFILE, "wb")) == NULL)
				{
					printf("\n\t\t\t清空失败\t");
					fclose(fp);
					Sleep(500);
					emptystu();
				}
				printf("\n\t\t\t清空成功\t");
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

void getnum(int numbit, char *dest)		//输入数字函数 numbit为输入数字的位数，dest为输入的字符串地址
{
	int i,j;
	for (i = 0; i < numbit; i++)
	{
		dest[i] = getch();		//输入数字
		if (dest[i] != '\b'&&dest[i] != '\r')		//输入不为退格和回车时
		{
			if (dest[i]<'0' || dest[i]>'9')		//输入的不为数字提示输入错误
			{
				printf("   非法字符，请重新输入");
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
			else	//否则输出输入的字符
				printf("%c", dest[i]);
		}
		else if (dest[i] == '\b'&& i > 0)		//输入退格且已经输入过字符
		{
			printf("\b \b");		//删除1个字符
			i = i - 2;
		}
		else if (dest[i] == '\r')		//提前输入回车
		{
			printf("   位数不足，请重新输入");
			Sleep(500);
			for (j = 0; j < 23 + i - 1; j++)		//上面有27个字符，此时已经输入i个字符，打印了i-1个*，使得这一部分消失
				printf("\b");
			for (j = 0; j < 23 + i - 1; j++)
				printf(" ");
			for (j = 0; j < 23 + i - 1; j++)
				printf("\b");
			printf("\b ");		//未知原因上述操作会留下一个多余的*需要遮盖掉
			i = -1;		//确保循环+1后i=0从新输入
		}
	}
	dest[i] = 0;		//字符串末尾添上结束符
	getch();		//吸收最后的回车
	printf("\n");
}

void help()
{
	int i;
	system("cls");		//屏幕界面设置
	printf("\n\t\t\t\t\t\t学生成绩管理系统\n\n");
	printf("HELP>>>");
	printf("\n\n\n");
	printf("学生成绩管理系统--》1.登录--》1.1.教师登录--》1.1.1.查看学生成绩--》1.1.1.1.学生成绩排序--》1.1.1.1.1.按学号排序\n");
	for (i = 0; i < 88; i++)
		printf(" ");
	printf("--》1.1.1.1.2.按总分排序\n");
	for (i = 0; i < 88; i++)
		printf(" ");
	printf("--》1.1.1.1.3.按语文成绩排序\n");
	for (i = 0; i < 88; i++)
		printf(" ");
	printf("--》1.1.1.1.4.按数学成绩排序\n");
	for (i = 0; i < 88; i++)
		printf(" ");
	printf("--》1.1.1.1.5.按英语成绩排序\n");
	for (i = 0; i < 65; i++)
		printf(" ");
	printf("--》1.1.1.2.删除学生成绩--》1.1.1.2.1.按学号删除\n");
	for (i = 0; i < 65+24; i++)
		printf(" ");
	printf("--》1.1.1.2.2.按姓名删除\n");
	for (i = 0; i < 65; i++)
		printf(" ");
	printf("--》1.1.1.3.修改学生成绩--》1.1.1.3.1.按学号修改\n");
	for (i = 0; i < 65 + 24; i++)
		printf(" ");
	printf("--》1.1.1.3.2.按姓名修改\n");
	for (i = 0; i < 65; i++)
		printf(" ");
	printf("--》1.1.1.4.挂科学生名单\n");
	for (i = 0; i < 42; i++)
		printf(" ");
	printf("--》1.1.2.添加学生成绩\n");
	for (i = 0; i < 42; i++)
		printf(" ");
	printf("--》1.1.3.查找学生成绩--》1.1.3.1.按学号查找\n");
	for (i = 0; i < 42+22; i++)
		printf(" ");
	printf("--》1.1.3.2.按姓名查找\n");
	for (i = 0; i < 42 + 22; i++)
		printf(" ");
	printf("--》1.1.3.3.按成绩查找\n");
	for (i = 0; i < 42; i++)
		printf(" ");
	printf("--》1.1.4.清空学生成绩\n");
	for (i = 0; i < 26; i++)
		printf(" ");
	printf("--》1.2.学生登录\n");
	for (i = 0; i < 16; i++)
		printf(" ");
	printf("--》2.账号设置--》2.1.注册--》2.1.1.教师注册\n");
	for (i = 0; i < 16+26; i++)
		printf(" ");
	printf("--》2.1.2.学生注册\n");
	for (i = 0; i < 16; i++)
		printf(" ");
	printf("--》2.账号设置--》2.2.修改密码--》2.2.1.教师修改密码\n");
	for (i = 0; i < 16+30; i++)
		printf(" ");
	printf("--》2.2.2.学生修改密码\n");
	for (i = 0; i < 16; i++)
		printf(" ");
	printf("--》3.帮助\n");
	printf("\n\t\t任意键.返回");
	getch();
	Interface();
}

