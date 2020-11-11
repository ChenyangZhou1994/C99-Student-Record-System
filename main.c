//
// Created by Imuzcy on 2020-11-08.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define maxn  3

//
typedef struct tagStudent{
    int stuID; // 学生ID
    char stuName[20]; // 学生名字
    int mathScore; // 数学成绩
    int chineseScore; // 语文成绩
    int englishScore; // 英语成绩
    int totalScores; // 总分数
    double aveScores; // 平均分数
}Student;

// 学生总人数
int num = 0;

// A - 优秀人数
int num_A[ maxn ] = { 0 };
// B - 良好人数
int num_B[ maxn ] = { 0 };
// C - 中等人数
int num_C[ maxn ] = { 0 };
// D - 及格人数
int num_D[ maxn ] = { 0 };
// E - 不及格人数
int num_E[ maxn ] = { 0 };

// 数学总成绩
int totalMathScores = 0;
// 语文总成绩
int totalChineseScores = 0;
// 英语总成绩
int totalEnglishScores = 0;
// 数学平均总成绩
double aveMathScores = 0.0;
// 语文平均总成绩
double aveChineseScores = 0.0;
// 英语平均总成绩
double aveEnglishScores = 0.0;

typedef struct tagNode{
    Student stu;
    struct tagNode *next;
}Node;

Node *head = NULL;

// 目录
void Menu_Output() {
    printf("Welcome to Student Record System \n");
    printf("1. Input record. \n");
    printf("2. Calculate total and average score of every course. \n");
    printf("3. Calculate total and average score of every student. \n");
    printf("4. Sort in descending order by total score of every student. \n");
    printf("5. Sort in ascending order by total score of every student. \n");
    printf("6. Sort in ascending order by number. \n");
    printf("7. Sort in dictionary order by name. \n");
    printf("8. Search by number. \n");
    printf("9. Search by name. \n");
    printf("10.Statistic analysis for every course. \n");
    printf("11.List record. \n");
    printf("0. Exit. \n");
    printf("Please enter your choice: \n");
}

void calculate_score(int index, int score) {
    if (score >= 90 && score <= 100) {
        num_A[ index ]++;
    }
    else if (score >= 80 && score <= 89) {
        num_B[ index ]++;
    }
    else if (score >= 70 && score <= 79) {
        num_C[ index ]++;
    }
    else if (score >= 60 && score <= 69) {
        num_D[ index ]++;
    }
    else if (score >=0 && score <= 59) {
        num_E[ index ]++;
    }
}

// 1.录入信息
void Input_record() {
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->next = NULL;
    //单个学生总成绩 - 初始化
    newNode->stu.totalScores = 0;
    //单个学生的平均成绩 - 初始化
    newNode->stu.aveScores = 0.0;

    Node *p = head;
    while (head != NULL && p->next != NULL) {
        p = p->next;
    }
    if (head == NULL) {
        head = newNode;
    }
    else {
        p->next = newNode;
    }

    printf("Please input student's ID: \n");
    scanf("%d", &newNode->stu.stuID);
    printf("Please input student's name: \n");
    scanf("%s", newNode->stu.stuName);
    printf("Please input student's Math Score: \n");
    scanf("%d", &newNode->stu.mathScore);
    printf("Please input student's Chinese Score: \n");
    scanf("%d", &newNode->stu.chineseScore);
    printf("Please input student's English Score: \n");
    scanf("%d", &newNode->stu.englishScore);
    //统计成绩
    calculate_score(0, newNode->stu.mathScore);
    calculate_score(1, newNode->stu.chineseScore);
    calculate_score(2, newNode->stu.englishScore);
    //学生总人数自增
    num++;
    //单个学生总成绩
    newNode->stu.totalScores = newNode->stu.mathScore + newNode->stu.chineseScore + newNode->stu.englishScore;
    //单个学生的平均成绩
    newNode->stu.aveScores = newNode->stu.totalScores * 1.0 / 3;
    //所有学生的数学总成绩
    totalMathScores += newNode->stu.mathScore;
    //所有学生的语文总成绩
    totalChineseScores += newNode->stu.chineseScore;
    //所有学生的英语总成绩
    totalEnglishScores += newNode->stu.englishScore;
    printf("Succeed !\n");
    system("pause");
}

// 2. 计算每门课程的总分和平均分
void Calculate_total_and_average_score_of_every_course() {
    //计算每门课程的数学平均分
    aveMathScores = totalMathScores * 1.0 / num;
    //计算每门课程的语文平均分
    aveChineseScores = totalChineseScores * 1.0 / num;
    //计算每门课程的英语平均分
    aveEnglishScores = totalEnglishScores * 1.0 / num;
    printf("输出每门课程的总分和平均分\n");
    printf("\t总分\t平均分\t\n");
    printf("数学\t%d\t%.2lf\t\n", totalMathScores, aveMathScores);
    printf("语文\t%d\t%.2lf\t\n", totalChineseScores, aveChineseScores);
    printf("英语\t%d\t%.2lf\t\n", totalEnglishScores, aveEnglishScores);
    printf("Succeed !\n");
    system("pause");
}

// 3. 计算每个学生的总分和平均分
void Calculate_total_and_average_score_of_every_student() {
    printf("输出每个学生的学号、姓名、每门课程的总分和平均分\n");
    printf("\t学号\t姓名\t总分\t平均分\t\n");
    Node *p = head;
    while (p != NULL) {
        printf("\t%d\t%s\t%d\t%.2lf\t\n", p->stu.stuID,
               p->stu.stuName, p->stu.totalScores, p->stu.aveScores);
        p = p->next;
    }
    printf("Succeed !\n");
    system("pause");
}

// 4. 按每个学生的总分由高到低排出名次表
void Sort_in_descending_order_by_total_score_of_every_student() {
    Node *pf, *pb, temp;
    pf = head;
    //冒泡排序
    while (pf->next != NULL) {
        pb = pf->next;
        while (pb != NULL) {
            if (pf->stu.totalScores > pb->stu.totalScores) {
                temp = *pf;
                *pf = *pb;
                *pb = temp;
                temp.next = pf->next;
                pf->next = pb->next;
                pb->next = temp.next;
            }
            pb = pb->next;
        }
        pf = pf->next;
    }
    printf("按总分(由高到低)学生排名及其考试成绩\n");
    printf("\t学号\t姓名\t总分\t平均分\t\n");
    Node *p = head;
    while (p != NULL) {
        printf("\t%d\t%s\t%d\t%.2lf\t\n", p->stu.stuID,
               p->stu.stuName, p->stu.totalScores, p->stu.aveScores);
        p = p->next;
    }
    printf("Succeed !\n");
    system("pause");
}

// 5. 按每个学生的总分由低到高排出名次表
void Sort_in_ascending_order_by_total_score_of_every_student()  {
    Node *pf, *pb, temp;
    pf = head;
    //冒泡排序
    while (pf->next != NULL) {
        pb = pf->next;
        while (pb != NULL) {
            if (pf->stu.totalScores < pb->stu.totalScores) {
                temp = *pf;
                *pf = *pb;
                *pb = temp;
                temp.next = pf->next;
                pf->next = pb->next;
                pb->next = temp.next;
            }
            pb = pb->next;
        }
        pf = pf->next;
    }
    printf("按总分(由低到高)学生排名及其考试成绩\n");
    printf("\t学号\t姓名\t总分\t平均分\t\n");
    Node *p = head;
    while (p != NULL) {
        printf("\t%d\t%s\t%d\t%.2lf\t\n", p->stu.stuID,
               p->stu.stuName, p->stu.totalScores, p->stu.aveScores);
        p = p->next;
    }
    printf("Succeed !\n");
    system("pause");
}

// 6. 按学号由小到大排除成绩表
void Sort_in_ascending_order_by_number() {
    Node *pf, *pb, temp;
    pf = head;
    //冒泡排序
    while (pf->next != NULL) {
        pb = pf->next;
        while (pb != NULL) {
            if (pf->stu.stuID < pb->stu.stuID) {
                temp = *pf;
                *pf = *pb;
                *pb = temp;
                temp.next = pf->next;
                pf->next = pb->next;
                pb->next = temp.next;
            }
            pb = pb->next;
        }
        pf = pf->next;
    }
    printf("\t学号\t姓名\t数学\t语文\t英语\t总分\t平均分\t\n");
    Node *p = head;
    while (p != NULL) {
        printf("\t%d\t%s\t%d\t%d\t%d\t%d\t%.2lf\t\n", p->stu.stuID,
               p->stu.stuName, p->stu.mathScore, p->stu.chineseScore,
               p->stu.englishScore, p->stu.totalScores,
               p->stu.aveScores);
        p = p->next;
    }
    printf("Succeed !\n");
    system("pause");
}

// 7. 按姓名的字典顺序排出成绩表
void Sort_in_dictionary_order_by_name() {
    Node *pf, *pb, temp;
    pf = head;
    //冒泡排序
    while (pf->next != NULL) {
        pb = pf->next;
        while (pb != NULL) {
            if (strcmp(pf->stu.stuName, pb->stu.stuName) > 0) {
                temp = *pf;
                *pf = *pb;
                *pb = temp;
                temp.next = pf->next;
                pf->next = pb->next;
                pb->next = temp.next;
            }
            pb = pb->next;
        }
        pf = pf->next;
    }
    printf("按姓名字典序学生排名及其考试成绩\n");
    printf("\t学号\t姓名\t数学\t语文\t英语\t总分\t平均分\t\n");
    Node *p = head;
    while (p != NULL) {
        printf("\t%d\t%s\t%d\t%d\t%d\t%d\t%.2lf\t\n", p->stu.stuID,
               p->stu.stuName, p->stu.mathScore, p->stu.chineseScore,
               p->stu.englishScore, p->stu.totalScores,
               p->stu.aveScores);
        p = p->next;
    }
    printf("Succeed !\n");
    system("pause");
}

// 8. 按学号查询学生排名及其考试成绩
void Search_by_number() {
    int s_id;
    printf("请输入学生ID:\n");
    scanf("%d", &s_id);
    Node *p = head;
    while (p != NULL) {
        if (p->stu.stuID == s_id) {
            printf("\t学号\t姓名\t数学\t语文\t英语\t总分\t平均分\t\n");
            printf("\t%d\t%s\t%d\t%d\t%d\t%d\t%.2lf\t\n", p->stu.stuID,
                   p->stu.stuName, p->stu.mathScore, p->stu.chineseScore,
                   p->stu.englishScore, p->stu.totalScores,
                   p->stu.aveScores);
            break;
        }
        p = p->next;
    }
    printf("Succeed !\n");
    system("pause");
}

// 9. 按姓名查询学生排名及其考试成绩
void Search_by_name() {
    char s_name[20];
    printf("请输入学生姓名:\n");
    scanf("%s", s_name);
    Node *p = head;
    while (p != NULL) {
        if (strcmp(p->stu.stuName, s_name) == 0) {
            printf("\t学号\t姓名\t数学\t语文\t英语\t总分\t平均分\t\n");
            printf("\t%d\t%s\t%d\t%d\t%d\t%d\t%.2lf\t\n", p->stu.stuID,
                   p->stu.stuName, p->stu.mathScore, p->stu.chineseScore,
                   p->stu.englishScore, p->stu.totalScores,
                   p->stu.aveScores);
            break;
        }
        p = p->next;
    }
    printf("Succeed !\n");
    system("pause");
}

// 10. 分析课程信息
void List_scores() {
    printf("\t优秀(90~100)\t良好(80~89)\t中等(70~79)\t及格(60~69)\t不及格(0~59)\n");
    int i = 0;
    for (; i < 3 ; i++) {
        printf("数学(人数)\n");
        printf("\t%d\t%d\t%d\t%d\t%d\t\n", num_A[i], num_B[i],
               num_C[i], num_D[i], num_E[i]);
        if (i == 0) {
            printf("数学(百分比):\n");
        }
        else if (i == 1) {
            printf("语文(百分比):\n");
        }
        else if (i == 2) {
            printf("英语(百分比):\n");
        }
        printf("\t%.2lf%%\t%.2lf%%\t%.2lf%%\t%.2lf%%\t%.2lf%%\t\n",
               100.0 * num_A[ i ] / num, 100.0 * num_B[ i ] / num,
               100.0 * num_C[ i ] / num, 100.0 * num_D[ i ] / num,
               100.0 * num_E[ i ] / num);
    }
    printf("Succeed !\n");
    system("pause");
}

// 11. 全部Record List信息
void Record_list() {
    printf("输出每个学生的学号、姓名、各科考试成绩，以及每门课程的总分和平均分\n");
    printf("\t学号\t姓名\t数学\t语文\t英语\t总分\t平均分\t\n");
    Node *p = head;
    while (p != NULL) {
        printf("\t%d\t%s\t%d\t%d\t%d\t%d\t%.2lf\t\n", p->stu.stuID,
               p->stu.stuName, p->stu.mathScore, p->stu.chineseScore,
               p->stu.englishScore, p->stu.totalScores,
               p->stu.aveScores);
        p = p->next;
    }
    printf("Succeed !\n");
    system("pause");
}

int main() {
    bool flag = false;
    while (1) {
        Menu_Output();
        int x;
        scanf("%d", &x);
        switch (x) {
            case 1:
                Input_record();
                break;
            case 2:
                Calculate_total_and_average_score_of_every_course();
                break;
            case 3:
                Calculate_total_and_average_score_of_every_student();
                break;
            case 4:
                Sort_in_descending_order_by_total_score_of_every_student();
                break;
            case 5:
                Sort_in_ascending_order_by_total_score_of_every_student();
                break;
            case 6:
                Sort_in_ascending_order_by_number();
                break;
            case 7:
                Sort_in_dictionary_order_by_name();
                break;
            case 8:
                Search_by_number();
                break;
            case 9:
                Search_by_name();
                break;
            case 10:
                List_scores();
                break;
            case 11:
                Record_list();
                break;
            case 0:
                flag = true;
                break;
            default:
                printf("输入错误编号,请重新输入!\n");
                continue;
        }
        if (flag) {
            break;
        }
    }
    return 0;
}
