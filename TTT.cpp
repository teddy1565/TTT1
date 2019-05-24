#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
void display(int r); //顯示棋盤現在狀態
int chose(); //將數值轉換為棋子
char display_chboard[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}}; //棋盤
int turn = 0; //回合
int checkwin = 0; //檢查是否有人勝利
int checkerboard[3][3] = {{0,0,0},{0,0,0},{0,0,0}}; //棋盤2
int NN[3][3]={{10,10,10},{10,20,10},{10,10,10}}; //棋盤權重
int peace = 0; //是否平手
int coordinate_1[2]; 
int check_two(int NN[3][3],int chboard[3][3]){ //確認己方防守時是否有兩個符號連成一直線(進攻手段)
    int memory_1=0;
    int memory_2=0;
    int memory_3=0;
    int memory_4=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            memory_1+=chboard[i][j];
            if(chboard[i][j]==0){
                memory_2 = j;
            }
        }
        if(memory_1<=-2){
            NN[i][memory_2] = 25;
            memory_1=0;
            memory_2=0;
            break;
        }
        memory_1=0;
        memory_2=0;
    }
    for(int l=0;l<3;l++){
        for(int k=0;k<3;k++){
            memory_3+=chboard[k][l];
            if(chboard[k][l]==0){
                memory_4 = k;
            }
        }
        if(memory_3<=-2){
            NN[memory_4][l] = 25;
            memory_3=0;
            memory_4=0;
            break;        
        }
        memory_3=0;
        memory_4=0;
    }
    return 0;
}
int display_winner(int win){ //顯示勝負訊息
    if(win==1){ //若玩家(P1)勝利
        printf("\nO win\n");
    }else if(win==-1){ //若電腦(P2)勝利
        printf("\nX win\n");
    }
    return 0;
}
int calcu(){    //檢查是否有人獲勝,若有連線則返回1
    int flat=0;
    for(int i=0;i<3;i++){
        if(checkerboard[i][0]==checkerboard[i][1]&&checkerboard[i][1]==checkerboard[i][2]&&checkerboard[i][1]!=0){
            display_winner(checkerboard[i][0]);
            return 1;
        }
    }
    for(int j=0;j<3;j++){
        if(checkerboard[0][j]==checkerboard[1][j]&&checkerboard[1][j]==checkerboard[2][j]&&checkerboard[1][j]!=0){
            display_winner(checkerboard[j][0]);
            return 1;
        }
    }
    if(checkerboard[0][0]==checkerboard[1][1]&&checkerboard[1][1]==checkerboard[2][2]&&checkerboard[1][1]!=0){
        display_winner(checkerboard[0][0]);
        return 1;
    }else if(checkerboard[0][2]==checkerboard[1][1]&&checkerboard[1][1]==checkerboard[2][0]&&checkerboard[1][1]!=0){
        display_winner(checkerboard[0][2]);
        return 1;
    }
    for(int k=0;k<3;k++){
        for(int l=0;l<3;l++){
            if(checkerboard[k][l]!=0){flat++;}
            if(flat==9){
                printf("\nDrew!!\n");
                return 2;
            }
        }
    }
    return 0;
}
int BOT(int chboard[3][3]){ //電腦下棋為-1
    for(int chboardX=0;chboardX<3;chboardX++){
        for(int chboardY=0;chboardY<3;chboardY++){
                //這裡要處理相鄰的兩數字加權
                if(chboard[chboardX][chboardY]==1){
                    if(chboardX+1<3){
                        if(chboard[chboardX+1][chboardY]==0){
                            NN[chboardX+1][chboardY]+=5;
                        }
                    }
                    if(chboardX-1>0){
                        if(chboard[chboardX-1][chboardY]==0){
                            NN[chboardX-1][chboardY]+=5;
                        }
                    }
                    if(chboardY+1<3){
                        if(chboard[chboardX][chboardY+1]==0){
                            NN[chboardX][chboardY+1]+=5;
                        }
                    }
                    if(chboardY-1>0){
                        if(chboard[chboardX][chboardY-1]==0){
                            NN[chboardX][chboardY-1]+=5;
                        }
                    }
                    NN[chboardX][chboardY] = 0;
                }
            }
        }
    int get_two = check_two(NN,chboard);
    int max[3]={0,0,0};//第0元素儲存數值,第1元素儲存X,第2元素儲存Y
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(NN[i][j]>=max[0]&&chboard[i][j]==0){
                max[0] = NN[i][j];
                max[1] = i;
                max[2] = j;
            }
        }
    }

    chboard[max[1]][max[2]]=-1;
    NN[max[1]][max[2]]=0;
    chose();
    display(0);
    turn = (turn+1)%2;
    printf("\n");
    checkwin = calcu();
    return 0;
}

void display(int r){//顯示棋盤狀況
    system("cls");
    printf("\n");
    printf("======================================================");
    printf("\n");
    printf("%c | %c | %c\n",display_chboard[0][0],display_chboard[0][1],display_chboard[0][2]);
    printf("----------\n");
    printf("%c | %c | %c\n",display_chboard[1][0],display_chboard[1][1],display_chboard[1][2]);
    printf("----------\n");
    printf("%c | %c | %c\n",display_chboard[2][0],display_chboard[2][1],display_chboard[2][2]);
    if(r==1){
        printf("ERROR!The address is already occupied!");
    }else if(r==2){
        printf("ERROR!Out of range!");
    }
    printf("\n\n");
}
int chose(){ //將數值轉換為棋子
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(checkerboard[i][j]==1){
                display_chboard[i][j] = 'O';
            }else if(checkerboard[i][j]==-1){
                display_chboard[i][j] = 'X';
            }
        }
    }
    return 0;
}
void FC_chose(int x){ //將選擇的棋子轉換為座標
    if(x==1){
        coordinate_1[0] = 0;
        coordinate_1[1] = 0;
    }else if(x==2){
        coordinate_1[0] = 0;
        coordinate_1[1] = 1;
    }else if(x==3){
        coordinate_1[0] = 0;
        coordinate_1[1] = 2;
    }else if(x==4){
        coordinate_1[0] = 1;
        coordinate_1[1] = 0;
    }else if(x==5){
        coordinate_1[0] = 1;
        coordinate_1[1] = 1;
    }else if(x==6){
        coordinate_1[0] = 1;
        coordinate_1[1] = 2;
    }else if(x==7){
        coordinate_1[0] = 2;
        coordinate_1[1] = 0;
    }else if(x==8){
        coordinate_1[0] = 2;
        coordinate_1[1] = 1;
    }else if(x==9){
        coordinate_1[0] = 2;
        coordinate_1[1] = 2;
    }
}
int main(){
    int x,y;
    char cgBOT;
    int ch_chose;
    int r=0;
    int count=1;
    printf("Single(y/n)");
    scanf("%c",&cgBOT);
    while(!checkwin){
        //checkwin = calcu();
        display(r);
        printf("\nRound %d\n",count);
        if(cgBOT=='Y'||cgBOT=='y'){
            if(r==0){
                BOT(checkerboard);
            }
            if(checkwin!=0){break;}
        }
        printf("Input coordinates:");
        scanf("%d",&ch_chose);//儲存輸入座標
        FC_chose(ch_chose);
        if(ch_chose>9||ch_chose<1){//若超出範圍則不動作且提示錯誤訊息
            //printf("輸入錯誤!!請重新輸入\n");
            r=2;
        }else{//若輸入正確則找到輸入的座標並且"下棋"
        x = coordinate_1[0],y = coordinate_1[1];
        count++;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(i==x&&j==y){
                        if(checkerboard[i][j]==0&&turn==1){
                            checkerboard[i][j] = 1;
                            turn = (turn+1)%2;
                            r=0;
                        }else if(checkerboard[i][j]==0&&turn==0&&cgBOT=='N'||checkerboard[i][j]==0&&turn==0&&cgBOT=='n'){
                            checkerboard[i][j] = -1;
                            turn = (turn+1)%2;
                            r=0;
                        }else if(checkerboard[i][j]!=0){
                            //printf("此位置已經被占用!請重新選擇!\n");
                            r = 1;
                        }
                    }
                }
            }
            chose();
            display(r);
            checkwin=calcu();
        }
    }
    printf("\nfinish!\n");//遊戲結束提示
	system("pause");
    return 0;
}
