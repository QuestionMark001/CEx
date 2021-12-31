#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct GameMan{
    int number;
}GameMan;

int main(){
    int PersonNum;//游戏人数 
    int round=1;//游戏回合 
    int PersonPos=1;//起始人位置 
    int BulletPos;//子弹位置 
	int i;//中枪人位置
    srand((int)time(0));//使用当前时间作为rand()函数的随机数的种子
	printf("请输入本次游戏人数(<100): ");
    scanf("%d",&PersonNum);
    printf("\n为编号为 1-%d 的游戏人员分配位置!\n\n",PersonNum);
    GameMan GameMans[100];//存储游戏人员编号的数组
    for (int j=1;j<=PersonNum;j++) {//依次为参加者分配编号
        GameMans[j].number=j;
    }
    //当只剩余一个人时，此场结束
    while (PersonNum!=1) {
        BulletPos=rand()%6+1;//左轮旋转后的子弹位置（利用随机数1~6表示） 
		printf("第 %d 轮游戏,从编号为 %d 的人开始,枪在第 %d 次扣动扳机时会响!\n\n",round,GameMans[PersonPos].number,BulletPos);
        for (i=PersonPos;i<PersonPos+BulletPos-1;i++);//找到每轮退出的人的位置 i
        //由于参与者排成的是环，当人数少时可能会回到开头，所以需要对求得 i 值进行取余处理
        //当 i=0时，实际上指的是位于数组结尾的参与者，需要重新调整 i 的值
        if(!(i=i%PersonNum)){i=PersonNum;PersonPos=1;}
		else PersonPos=i;//PersonPos表示的是下一轮开始的位置
        printf("编号为 %d 的赌徒退出赌博,剩余赌徒编号依次为:",GameMans[i].number);
        //使用顺序存储时，如果删除元素，需要将其后序位置的元素进行全部前移
        PersonNum--;//此时参与人数减一 
		//先将i位置后成员向前依次移动     
        for (int j=i;j<=PersonNum;j++) {
            GameMans[j]=GameMans[j+1];
        }
		//再打印剩余成员 
		for (int k=1; k<=PersonNum; k++) {
            printf("%d ",GameMans[k].number);
        }
        printf("\n\n");  
        round++;//到回合数加一 
    }
    printf("最终胜利的游戏人员编号是：%d \n\n",GameMans[1].number);
}
