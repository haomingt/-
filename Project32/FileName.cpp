#include<iostream>
#include<string>
#include<windows.h>
#include<conio.h>
#include<cmath>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
void music()
{
    mciSendString(L"open  playGame.wav alias music type mpegvideo", 0, NULL, NULL);
    mciSendString(L"play music repeat", 0, NULL, NULL);
    mciSendString(L"setaudio music volume to 70", 0, NULL, NULL);
}
struct player {
    int x, y; //(玩家坐标);
    int speed;// (玩家速度)初始化为1
    int flag;
};
struct player B;//定义玩家结构体
struct Ghost {
    int x, y; //(鬼魂坐标);
    int speed; //(鬼魂速度)
    int flag;
    int plot;//鬼的脚上的地块
};
int speed = 1;
int dir = -1;//玩家的方向
int dx = 0, dy = 0;//控制玩家各个方向
struct Ghost A[4];//四个鬼魂
int score = 0;//玩家积分
int map[30][27] = {
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,
     1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 2, 2, 2, 2, 2, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 4, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 4 ,1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 7, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 2, 2, 2, 2, 2, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 3, 3, 3, 3, 3, 2, 3, 3, 3, 1, 2, 2, 2, 2, 2, 1, 3, 3, 3, 2, 3, 3, 3, 3, 3, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 2, 2, 2, 2, 2, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 3, 3, 8, 3, 3, 3, 3, 3, 1, 1, 5, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 6, 2, 2, 2, 2, 2, 7, 2, 2, 2, 1, 1, 2, 2, 2, 1 ,
     1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1 ,
     1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1 ,
     1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1 ,
     1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1 ,
     1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1 ,
     1, 4, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1 ,
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
int map1[30][27] = {
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,
     1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 2, 2, 2, 2, 2, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 4, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 4 ,1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 1, 3, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 7, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 2, 2, 2, 2, 2, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 3, 3, 3, 3, 3, 2, 3, 3, 3, 1, 2, 2, 2, 2, 2, 1, 3, 3, 3, 2, 3, 3, 3, 3, 3, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 2, 2, 2, 2, 2, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 3, 3, 8, 3, 3, 3, 3, 3, 1, 1, 5, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 1, 1, 1, 1, 1, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 2, 1, 1, 1, 1, 1, 1 ,
     1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1 ,
     1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 6, 2, 2, 2, 2, 2,7, 2,2 , 2, 1, 1, 2, 2, 2, 1 ,
     1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1 ,
     1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1 ,
     1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1 ,
     1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1 ,
     1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1 ,
     1, 4, 6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1 ,
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
int flower_num = 245;//花朵总数
int flower_plucked = 0;//已经摘花的数目
bool item_ghost_stop;//判断玩家是否踩到停止道具的参数
//函数声明
void menuview();//开始（菜单）界面：(核心)
void game_init();// 初始化游戏地图
void gameview();//初始化：打印游戏地图、打印花朵、鬼魂、玩家初始位置、打印积分
void winner_view();// 游戏胜利页面
void loser_view();//游戏失败页面
void gamebk_view();//游戏背景界面(非核心)
void mapping_print(int val);//映射打印函数
void game_Introduction_view();// 游戏介绍界面
void game_operation_view(); //操作说明界面(非核心)
void game_developer_view();//游戏开发人员界面(非核心)
int input();
void init_character();//初始化玩家和鬼魂的属性
void player_move(char ch); //用户操作移动(核心)
int is_touch(int x, int y);//判断玩家碰到什么物体
void wall_effect();//碰到墙体产生的效果
void flower_effect();//碰到花朵产生的效果
void prop_effect();//碰到晕眩道具产生的效果
void player_portal(int x, int y);//碰到传送门道具产生的效果
void ghost_effect();//碰到鬼魂死亡
void ghost_fly(int Playerx, int Playery);//鬼魂追逐功能（鬼魂可以重叠）
void interactive();//游戏介绍界面交互函数

void gotoxy(int x, int y);//定位函数(菜单界面)
int GetKeyPressed();// 获取键盘输入(方向键输入时有两个值)菜单界面
int a = 0;

//墙壁：数字1；
//花朵：数字2；
//空地：数字3；
//鬼魂：数字4；
//玩家：一：初始化为出生地 16, 12
//
//初始化鬼魂生成地
//鬼魂 一：7, 1
//二：7, 25
//三：28, 1
//四：28, 25

//分数:一：初始化为零，等于玩家摘到花朵的个数 * 5；
//
//让鬼魂减速道具：5；
//玩家的方向：int dir = 0；//0为w，1为a，2为d，3为s
//玩家晕眩道具：6
//玩家传送道具：7
//

int main()
{
    music();
    game_init();
    system("mode con cols=100 lines=40");//改变宽高
    input();
    return 0;
}
//1.开始（菜单）界面：(核心)
void menuview()
{
    /*负责人：吕朝城
        功能：打印菜单界面*/
    cout << "***************************************************************" << endl;
    cout << "**                      摘花人游戏菜单                       **" << endl;
    cout << "***************************************************************" << endl;
    cout << "**                                                           **" << endl;
    cout << "**        开始游戏                   选择操作说明：          **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**        游戏介绍                 ↑键或↓键进行选择操作    **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**                                  按回车键确定             **" << endl;
    cout << "**        退出游戏                                           **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**                                                           **" << endl;
    cout << "***************************************************************" << endl;
}
//2.游戏界面：（核心）
//1.初始化游戏地图
void game_init()
{

    init_character();

    //负责人：杨天风
    //功能：初始化游戏地图

}
// 获取键盘输入(方向键输入时有两个值)菜单界面
int GetKeyPressed()
{
    if (_kbhit())
    {
        return _getch();
    }
    else
    {
        return -1;
    }
}
//定位函数(菜单界面)
void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void print_map() {
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            int val = map[i][j];
            gotoxy(j + a, i);
            mapping_print(val);
        }
        a = 0;

        //cout << endl;
    }
    gotoxy(0, 30);
    string s = "score=" + to_string(score);
    puts(s.c_str());
}

void gameview()//初始化：打印游戏地图、打印花朵、鬼魂、玩家初始位置、打印积分
{ // 打印转换后的实际物体

    while (1) {

        // 隐藏控制台窗口
        //system("cls");

        //cout << endl << endl << "\033[36mscore=\033[0m" << score << endl;

        switch (is_touch(B.x, B.y))
        {
        case 1://墙壁
            wall_effect();
            break;
        case 2://花朵
            flower_effect();
            break;
        case 3://空地
            break;
        case 4://鬼魂
            ghost_effect();
            winner_view();
            break;
        case 5://鬼魂减速道具
            break;
        case 6://玩家晕眩道具
            prop_effect();
            break;
        case 7://传送门
        { /*int x = B.x, y = B.y;
        if (dir == 0)       ghost_stop(--x, y);
        else if (dir == 1)  ghost_stop(x, --y);
        else if (dir == 2)  ghost_stop(x, ++y);
        else if (dir == 3) ghost_stop(++x, y);*/
        break;
        }
        default:
            break;
        }
        ghost_fly(B.x, B.y);
        print_map();

        for (int i = 0; i < B.speed; i++) {
          
            player_move(GetKeyPressed());
            if (is_touch(B.x, B.y) == 7) {
                int x = B.x, y = B.y;
                if (dir == 0)      player_portal(--x, y);
                if (dir == 1)   player_portal(x, --y);
                if (dir == 2)  player_portal(x, ++y);
                if (dir == 3)player_portal(++x, y);
            }
            print_map();
            Sleep(50);

            for (int j = 0; j < 4; j++)
            {
                if (map[B.x][B.y] == map[A[j].x][A[j].y])
                {
                    ghost_effect();
                }
            }
        }
        //Sleep(500);

    }
}
/*负责人：杨天风
功能：打印游戏界面*/

//2.游戏结束页面
//判断游戏结束
//a : 游戏胜利页面
void SetConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//a : 游戏胜利页面
void winner_view()
{
    /*负责人：吕朝城
        功能：打印游戏胜利界面*/
    system("cls");
    SetConsoleColor(6);
    cout << "              ****************************************************************" << endl;
    cout << "              ****************************************************************" << endl;
    cout << "              **                                                            **" << endl;
    cout << "              **   ##           ###           ##   ########   ####      ##  **" << endl;
    cout << "              **    ##         ## ##         ##       ##      ## ##     ##  **" << endl;
    cout << "              **     ##       ##   ##       ##        ##      ##  ##    ##  **" << endl;
    cout << "              **      ##     ##     ##     ##         ##      ##   ##   ##  **" << endl;
    cout << "              **       ##   ##       ##   ##          ##      ##    ##  ##  **" << endl;
    cout << "              **        ## ##         ## ##           ##      ##     ## ##  **" << endl;
    cout << "              **         ###           ###         ########   ##      ####  **" << endl;
    cout << "              **                                                            **" << endl;
    cout << "              **                                                            **" << endl;
    cout << "              ****************************************************************" << endl;
    cout << "              ****************************************************************" << endl;
    SetConsoleColor(7);
}

/*负责人：吕朝城
    功能：打印游戏胜利界面*/

    //b:游戏失败页面
void loser_view()
{
    /*负责人：吕朝城

        功能：打印游戏失败页面；*/
    system("cls");
    SetConsoleColor(3);
    cout << "              ****************************************************************" << endl;
    cout << "              ****************************************************************" << endl;
    cout << "              **                                                            **" << endl;
    cout << "              **       #####    ##           ##   #########  #########      **" << endl;
    cout << "              **     ##     ##   ##         ##    ##         ##      ##     **" << endl;
    cout << "              **     ##     ##    ##       ##     ##         #########      **" << endl;
    cout << "              **     ##     ##     ##     ##      #########  ## ##          **" << endl;
    cout << "              **     ##     ##      ##   ##       ##         ##  ##         **" << endl;
    cout << "              **     ##     ##       ## ##        ##         ##   ##        **" << endl;
    cout << "              **       #####          ###         #########  ##    ####     **" << endl;
    cout << "              **                                                            **" << endl;
    cout << "              **                                                            **" << endl;
    cout << "              ****************************************************************" << endl;
    cout << "              ****************************************************************" << endl;
    SetConsoleColor(7);

}


//3.游戏介绍界面：（核心）
void game_Introduction_view()// (非核心)
{
    /*负责人：吕朝城
        功能：打印游戏介绍页面；*/
    cout << "***************************************************************" << endl;
    cout << "**                      摘花人游戏介绍                       **" << endl;
    cout << "***************************************************************" << endl;
    cout << "**                                                           **" << endl;
    cout << "**        游戏背景                 选择操作说明：            **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**        操作说明                 ↑键或↓键进行选择操作    **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**        开发人员                                           **" << endl;
    cout << "**                                   按回车键确定            **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**        返回菜单                                           **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**                                                           **" << endl;
    cout << "**                                                           **" << endl;
    cout << "***************************************************************" << endl;
}

//(1)游戏背景界面：
void gamebk_view()//(非核心)
{
    /*负责人：周俊辰
        功能：打印游戏背景页面；*/
    cout << "游戏背景：" << endl;
    cout << endl;
    cout << "   在一个古老而神秘的花园里，你将踏上一场摘花人的奇幻冒险。这个花园充满了各种绚丽多彩" << endl;
    cout << "的花朵和神奇的生物。你是一位勇敢的冒险家，任务是找到并摘取花园中的所有花朵。然而，这" << endl;
    cout << "个花园并不完全安宁。传说中，有一群古老的鬼魂居住在花园的深处，并保护着这些珍贵的花朵。" << endl;
    cout << "它们渴望保护花朵的神秘力量，并决心阻止任何人获取这些力量。" << endl;
    cout << endl;
    cout << "   你将需要小心翼翼地穿越花园的各个角落，寻找并摘取花朵。每朵花朵都散发着独特的能量，这" << endl;
    cout << "将帮助你在冒险中取得胜利。但同时，鬼魂们会在你接近花朵时开始追逐你，试图阻止你的任务。" << endl;
    cout << endl;
    cout << "   在花园的各个区域，你将遇到各种障碍和谜题。有些花朵可能被隐藏在令人迷惑的迷宫中，有" << endl;
    cout << "些则需要解开复杂的谜题才能到达。你要善用自己的智慧和技巧，化解这些难题，并躲避鬼魂的攻" << endl;
    cout << "击。" << endl;
    cout << endl;
    cout << "   当你最终成功摘取到每朵花朵时，花园中弥漫着神秘的魔法气息。你将成为这个花园的守护者，" << endl;
    cout << "拥有着花朵们所蕴含的无尽能量。而鬼魂们也将得到解脱，回归到他们的神秘世界中。" << endl;
    cout << endl;
    cout << "   现在，准备好进入这个奇幻花园的冒险了吗？快来展示你的勇气和智慧，成为真正的摘花人吧！" << endl;

}

//(2)操作说明界面：
void game_operation_view() //(非核心)
{
    /*负责人：周俊辰
        功能：打印操作说明页面；*/
    cout << "操作说明：玩家通过wasd控制摘花人的移动，你需要去摘完所有的花朵并躲避鬼魂的攻" << endl;
    cout << "击。在地图中会随机生成道具，其有一下三种效果：" << endl;
    cout << endl;
    cout << "1.鬼魂速度减慢2.5秒" << endl;
    cout << "2.传送门道具（分布在地图固定位置）" << endl;
    cout << "3.玩家晕眩（方向错乱）" << endl;
    cout << "" << endl;
}

//(3)游戏开发人员界面：
void game_developer_view()//(非核心)
{
    /*负责人：周俊辰
        功能：打印游戏开发人员页面；*/
    cout << "                               开发人员名单" << endl;
    cout << endl;
    cout << "最强の指导:";
    cout << "          宇宙混元无敌最强の喵桑~（熊猫小学长）" << endl;
    cout << endl;
    cout << "                               陈浩铭" << endl;
    cout << "                               蓝玉凉" << endl;
    cout << "                               彭嘉玮" << endl;
    cout << "                               吕朝城" << endl;
    cout << "                               杨天风" << endl;
    cout << "                               黄柏源" << endl;
    cout << "                               周俊辰" << endl;
    cout << "                               范帅斌" << endl;
    cout << endl;
  
   
}

//二：功能类
//1.开始界面
//（1）接收用户输入(核心)：wasd去控制摘花人，包括一个esc退出当前界面
int input()
{
    /*负责人：吕朝城
        功能：判断用户输入的内容，并进行相对操作*/
    int line = 4;    //默认为开始游戏选项的纵坐标
    int key = 0;
    int choice = 1;
    menuview();
    /*gotoxy(10, 4);   开始游戏坐标
    cout << "选项";*/
    /*gotoxy(10, 7);   游戏介绍坐标
    cout << "选项";*/
    //gotoxy(10, 10);  //退出游戏坐标
    //cout << "选项";
    gotoxy(10, line);
    printf("\033[4;31;42m开始游戏\033[0m");
    while (true)
    {
        key = GetKeyPressed();
        if (key == 224) // 方向键
        {
            key = GetKeyPressed();
            if (key == 72 && choice > 1) // 上箭头
            {
                choice -= 1;
                if (choice == 1)
                {
                    gotoxy(10, line);
                    printf("游戏介绍");
                    line -= 3;
                    gotoxy(10, line);
                    printf("\033[4;31;42m开始游戏\033[0m");
                }
                if (choice == 2)
                {
                    gotoxy(10, line);
                    printf("退出游戏");
                    line -= 3;
                    gotoxy(10, line);
                    printf("\033[4;31;42m游戏介绍\033[0m");
                }
            }
            else if (key == 80 && choice < 3) // 下箭头
            {
                choice += 1;
                if (choice == 2)
                {
                    gotoxy(10, line);
                    printf("开始游戏");
                    line += 3;
                    gotoxy(10, line);
                    printf("\033[4;31;42m游戏介绍\033[0m");
                }
                if (choice == 3)
                {
                    gotoxy(10, line);
                    printf("游戏介绍");
                    line += 3;
                    gotoxy(10, line);
                    printf("\033[4;31;42m退出游戏\033[0m");
                }
            }
        }
        else if (key == 13) // 回车键
        {
            if (choice == 1) {
                //开始游戏
                system("cls");
                gameview();
                //return;

            }
            if (choice == 2) {
                //游戏介绍
                system("cls");
                interactive();
            }
            if (choice == 3) {
                //退出游戏
                system("cls");
                exit(0);
            }
        }
    }
    return 0;
}

//2.游戏界面
//(1)用户操作移动(核心)
void player_move(char ch)
{
    switch (ch)
    {
    case'w':
        dir = 0;
        dx = -1;
        dy = 0;//y方向不移动
        break;
    case'a':
        dir = 1;
        dy = -1;
        dx = 0;//x方向不移动（或者说x方向速度为零）
        break;
    case'd':
        dir = 2;
        dx = 0;
        dy = 1;//x方向不移动
        break;
    case's':

        dir = 3;
        dy = 0;
        dx = 1;//y方向不移动
        break;
    default:
        break;
    }
    if (is_touch(B.x, B.y) == 1) {
        wall_effect();
    }

    map[B.x][B.y] = 3;
    B.x = B.x + dx;
    B.y = B.y + dy;
    map[B.x][B.y] = 8;
    /*负责人：陈浩铭
        功能：接受完用户的输入后，对玩家进行的移动操作*/
}

//（2）判断玩家是否碰到物体

int is_touch(int x, int y)
{
    /*负责人：陈浩铭
        功能：根据dir的方向判断玩家下一个位置有物体：
        1墙壁：返回1；
        2花朵：返回2；
        3空地：返回3；
        4鬼魂：返回4；
        5鬼魂减速道具：返回5
        6玩家晕眩道具：返回6
        7鬼魂停止道具：返回7
        注意数组越界，玩家不移动*/
        //if (dir == 0)       return map[x][--y];
        //else if (dir == 1)  return map[--x][y];
        //else if (dir == 2)  return map[++x][y];
        //else if (dir == 3)  return map[x][++y];

    if (dir == 0)       return map[--x][y];
    else if (dir == 1)  return map[x][--y];
    else if (dir == 2)  return map[x][++y];
    else if (dir == 3)  return map[++x][y];
}
//（3） 碰到物体产生效果
//1.碰到墙体
void wall_effect()
{
    /*负责人：吕朝城
        功能：玩家停止移动，dir不改变，接收键盘但有墙的地方仍然不动。*/
    dx = 0;
    dy = 0;

}

//2.碰到花朵
void flower_effect()
{
    /*负责人：彭嘉伟
        功能：花朵消失后，花朵所在的地方变为平地。积分 + 5，花朵所在地方更改为空地*/
        //2.碰到花朵
    map[B.x][B.y] = 3;
    flower_num--;
    score += 5;
    if (dir == 0)
    {
        //B.y--;
        map[B.x][B.y] = 8;
    }
    else if (dir == 3)
    {
        //B.y++;
        map[B.x][B.y] = 8;
    }
    else if (dir == 1)
    {
        //B.x--;
        map[B.x][B.y] = 8;
    }
    else if (dir == 2)
    {
        //B.x++;
        map[B.x][B.y] = 8;
    }
}


//3.碰到晕眩道具
void prop_effect()
{
    /*负责人：彭嘉玮
        功能：玩家的方向键判断相反, 定义变量flag为5，玩家每走一格减一，直到为0后，结束道具效果。*/
    B.flag--;
    if (dir == 0)
    {
        dir = 3;
        dy = 0;
        dx = 1;//y方向不移动
    }
    else if (dir == 1)
    {
        dir = 2;
        dx = 0;
        dy = 1;//x方向不移动
    }
    else if (dir == 2)
    {
        dir = 1;
        dy = -1;
        dx = 0;//x方向不移动（或者说x方向速度为零）
    }
    else if (dir == 3)
    {
        dir = 0;
        dx = -1;
        dy = 0;//y方向不移动
    }
}



//5.碰到传送门道具，玩家瞬移到地图一位置。
void player_portal(int x, int y)
{
    /*负责人：陈浩铭、范帅斌 
    功能：从一个传送门传送至另一位置
    */
 
    if (x == 10 && y == 6 && B.flag == 1)//如果玩家在这个坐标的话，进行判断并转移
    {
        map[B.x][B.y] = 3;
        B.x = 22;
        B.y = 17;
        map[22][19] = 8;
        B.flag = 1;
    }
    else if (x == 22 && y == 17 && B.flag == 1)//如果玩家在这个坐标的话，进行判断并转移
    {
        map[B.x][B.y] = 3;
        B.x = 10;
        B.y = 6;
        map[10][6] = 8;
        B.flag = 1;
    }
}
//6.碰到鬼魂
void ghost_effect()
{
    loser_view();
    system("pause");
    system("cls");
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 27; j++)
        {
            map[i][j] = map1[i][j];
        }
    }
    main();

    /*负责人：蓝玉凉
        功能：玩家死亡，调用失败界面的函数，并按任意键退出至菜单。*/
}

void ghost_fly(int Playerx, int Playery)
{
    /*负责人：范帅斌
         参数：需要传入玩家的x，y坐标
        功能：判断鬼魂与玩家在x, y方向上的距离。如果x坐标远，鬼魂先在x坐标上移动；如果y坐标远，则鬼魂先在y方向上移动。
        但是，鬼如果在x方向上无法移动，则先移动y方向；反之先在x方向上移动。*/
    for (int i = 0; i < 4; i++) {
        map[A[i].x][A[i].y] = A[i].plot;

        int dx1 = Playerx - A[i].x;
        int dy1 = Playery - A[i].y;
        if (abs(dx1) > abs(dy1)) { //先判断x方向上远还是y方向上远
            if (dx1 > 0) {//如果玩家在鬼魂右边

                if (map[A[i].x + 1][A[i].y] != 1)A[i].x++;//如果在x正方向没有墙的话 可以移动
                else {//否则在y方向上移动
                    if (dy1 > 0)//如果玩家在鬼魂下方，判断是否有墙
                    {
                        if (map[A[i].x][A[i].y + 1] != 1)A[i].y++;//没有墙 go
                        else break;//有墙 判断下面的
                    }
                    
                    else
                    {
                        if (map[A[i].x][A[i].y - 1] != 1) A[i].y--;//如果负方向没墙 向上移动
                        else A[i].x--;
                    }
                }
            }
            else {//如果玩家在鬼魂左边
                if (map[A[i].x - 1][A[i].y] != 1)A[i].x--;//如果在x负方向没有墙的话 向左移动
                else {//否则在y方向上移动
                    if (dy1 > 0)//如果玩家在鬼魂下方，判断是否有墙
                    {
                        if (map[A[i].x][A[i].y + 1] != 1)A[i].y++;//如果正方向没墙 向下移动
                        else break;
                    }

                    else
                    {
                        if (map[A[i].x][A[i].y - 1] != 1) A[i].y--;//如果负方向没墙 向上移动
                        else A[i].x++;
                    }
                }
            }
        }
        else {//如果玩家距离鬼魂在y轴远的话
            if (dy1 > 0) {//如果玩家在鬼魂下边
                if (map[A[i].x][A[i].y + 1] != 1) A[i].y++;//如果正方向没墙 向下移动
                else {
                    if (dx1 > 0)
                    {
                        if (map[A[i].x+1][A[i].y ] != 1)A[i].x++;//如果x正方向没墙 向右移动
                        else break;
                    }
                    else
                    {
                        if (map[A[i].x-1][A[i].y ] != 1) A[i].x--;//如果在x负方向没有墙的话 向左移动
                        else A[i].y--;
                    }
                }
            }
            else
            {
                if (map[A[i].x][A[i].y - 1] != 1) A[i].y--;//如果负方向没墙 向上移动
                else {
                    if (dx1 > 0)
                    {
                        if (map[A[i].x + 1][A[i].y] != 1)A[i].x++;//如果x正方向没墙 向右移动
                        else break;
                    }
                    else
                    {
                        if (map[A[i].x - 1][A[i].y] != 1) A[i].x--;//如果在x负方向没有墙的话 向左移动
                        else A[i].y++;//否则最后向上移动
                    }
                }
            }
        }
        //if (is_touch(A[i].x, A[i].y) == 1) {
            //wall_effect();
        //}
        if (map[A[i].x][A[i].y] != 4) {
            A[i].plot = map[A[i].x][A[i].y];
        }
        map[A[i].x][A[i].y] = 4;
        //B.x = B.x + B.speed * dx;
        //B.y = B.y + B.speed * dy;
        //map[B.x][B.y] = 8;
    }
}



//（5）映射打印函数
void mapping_print(int val)
{
    //负责人：扬天风
    //功能：将地图转化为对应物体
    switch (val)
    {
    case 1:
        puts("# ");
        a++;
        //cout << "# ";  // 墙壁
        break;
    case 2:
        puts("\033[32m※\033[0m");
        a++;
        //cout << "\033[32m※\033[0m";//花朵（绿色）
        break;
    case 3:
        puts("  ");
        a++;
        //cout << "  ";  // 空地                
        break;
    case 4:
        puts("\033[31m\u25C6\033[0m");  // 鬼魂，使用Unicode转义序列来表示 （红色）
        a++;
        //cout << "\033[31m\u25C6\033[0m";  // 鬼魂，使用Unicode转义序列来表示 （红色）
        break;
    case 5:
        puts("\033[32m\u25CF\033[0m");
        a++;
        //cout << "\033[32m\u25CF\033[0m";  // 让鬼魂减速道具  (绿色)
        break;
    case 6:
        puts("\033[31m\u266A \033[0m");
        a++;
        //cout << "\033[31m\u266A \033[0m";  // 让玩家被晕眩的道具     （红色）
        break;
    case 7:
        puts("\033[32m!\033[0m ");
        a++;
        //cout << "\033[32m!\033[0m ";  // 让鬼魂停止的道具  （绿色）
        break;
    case 8:
        puts("\u2605");
        a++;
        //cout << "\u2605";  // 玩家        \033[32m\033[0m
        break;
    default:
        puts(" 1 ");
        a += 2;
        //cout << " 1 ";  // 未知物体
        break;
    }
}

void init_character()
{
    //负责人：范帅斌
    //功能：初始化玩家和鬼魂出生地。
    B.x = 16;
    B.y = 12;
    B.speed = 2;//玩家速度初始为1
    B.flag = 1;
    for (int i = 0; i < 4; i++)
    {
        A[i].speed = 1;//每个鬼魂速度初始为1
        A[i].plot = 3;//每个鬼魂速度初始为1
    }
    A[0].x = 7;
    A[0].y = 1;
    A[1].x = 7;
    A[1].y = 25;
    A[2].x = 28;
    A[2].y = 1;
    A[3].x = 28;
    A[3].y = 25;
    item_ghost_stop = 0;
}



//游戏介绍交互函数
void interactive() {
    int line = 4;    //默认为开始游戏选项的纵坐标
    int key = 0;
    int choice = 1;
    game_Introduction_view();
    /*gotoxy(10, 4);   游戏背景坐标
    cout << "选项";*/
    /*gotoxy(10, 7);   操作说明坐标
    cout << "选项";*/
    //gotoxy(10, 10);  //开发人员坐标
    //cout << "选项";
    /*gotoxy(10, 13);   返回菜单坐标
    cout << "选项";*/
    gotoxy(10, line);
    printf("\033[4;31;42m游戏背景\033[0m");
    while (true)
    {
        key = GetKeyPressed();
        if (key == 224) // 方向键
        {
            key = GetKeyPressed();
            if (key == 72 && choice > 1) // 上箭头
            {
                choice -= 1;
                if (choice == 1)
                {
                    gotoxy(10, line);
                    printf("操作说明");
                    line -= 3;
                    gotoxy(10, line);
                    printf("\033[4;31;42m游戏背景\033[0m");
                }
                if (choice == 2)
                {
                    gotoxy(10, line);
                    printf("开发人员");
                    line -= 3;
                    gotoxy(10, line);
                    printf("\033[4;31;42m操作说明\033[0m");
                }
                if (choice == 3)
                {
                    gotoxy(10, line);
                    printf("返回菜单");
                    line -= 3;
                    gotoxy(10, line);
                    printf("\033[4;31;42m开发人员\033[0m");
                }
            }
            else if (key == 80 && choice < 4) // 下箭头
            {
                choice += 1;
                if (choice == 2)
                {
                    gotoxy(10, line);
                    printf("游戏背景");
                    line += 3;
                    gotoxy(10, line);
                    printf("\033[4;31;42m操作说明\033[0m");
                }
                if (choice == 3)
                {
                    gotoxy(10, line);
                    printf("操作说明");
                    line += 3;
                    gotoxy(10, line);
                    printf("\033[4;31;42m开发人员\033[0m");
                }
                if (choice == 4)
                {
                    gotoxy(10, line);
                    printf("开发人员");
                    line += 3;
                    gotoxy(10, line);
                    printf("\033[4;31;42m返回菜单\033[0m");
                }
            }
        }
        else if (key == 13) // 回车键
        {
            if (choice == 1) {
                //游戏背景
                system("cls");
                gamebk_view();
                system("pause");
                system("cls");
                interactive();
                //return;

            }
            if (choice == 2) {
                //操作说明
                system("cls");
                game_operation_view();
                system("pause");
                system("cls");
                interactive();
            }
            if (choice == 3) {
                //开发人员
                system("cls");
                game_developer_view();
                system("pause");
                system("cls");
                interactive();
            }
            if (choice == 4) {
                //菜单界面
                system("cls");
                input();
            }
        }
    }







}
