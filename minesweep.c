#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int xS,yS,lose,count;

void mapReveal(int map[10][10], int n, int guessed[10][10]){
    system("cls");
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if(map[i][j]==-1){
                printf("x ");
            }else if(guessed[i][j]!=0){
                printf("%d ",map[i][j]);
            }else{
                printf("* ");
            }
        }
        printf("\n");
    }
}

int winChecker(int n, int guessed[10][10]){
    int count=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(guessed[i][j]!=0){
                count++;
                if(count>=n*n-10){
                    return 1;
                }
            }
        }
    }
    return 0;
}

void mineGenerator(int n, int map[][10]){
    srand(time(NULL));
    for(int i=0;i<n;i++){
        int xM,yM;
        int repeat=0;
        do{
            repeat=0;
            xM= rand() % 9;
            yM=rand() % 9;
            // printf("%d %d\n",xM,yM);
            if(map[xM][yM]==-1 || (xM==xS && yM==yS)){
                repeat=1;
            }else{
                map[xM][yM]=-1;
                if(xM-1>=0 && yM-1>=0 && map[xM-1][yM-1]!=-1){
                    map[xM-1][yM-1]++;
                }//kiri atas
                if(xM-1>=0 && yM>=0 && map[xM-1][yM]!=-1){
                    map[xM-1][yM]++;
                }//kiri 
                if(xM>=0 && yM-1>=0 && map[xM][yM-1]!=-1){
                    map[xM][yM-1]++;
                }//atas
                if(xM-1>=0 && yM+1<9 && map[xM-1][yM+1]!=-1){
                    map[xM-1][yM+1]++;
                }//kiri bawah
                if(xM>=0 && yM+1<9 && map[xM][yM+1]!=-1){
                    map[xM][yM+1]++;
                }//bawah
                if(xM+1<9 && yM-1>=0 && map[xM+1][yM-1]!=-1){
                    map[xM+1][yM-1]++;
                }//kanan atas
                if(xM+1<9 && yM>=0 && map[xM+1][yM]!=-1){
                    map[xM+1][yM]++;
                }//kanan 
                if(xM+1<9 && yM+1<9 && map[xM+1][yM+1]!=-1){
                    map[xM+1][yM+1]++;
                }//kanan bawah
                repeat=0;
            }
        }while(repeat!=0);
        // printf("%d %d\n\n",xM,yM);
    }
}

int play(int guessed[10][10], int map[10][10]){
    guessed[xS][yS]=1;
    if(map[xS][yS]==-1){
        return 0;
    }else if(map[xS][yS]>0){
        return 1;
    }else{
        return 2;
    }
}

void guess(){
    printf("(x y): ");
    scanf("%d %d",&yS,&xS);
    yS-=1,xS-=1;
    getchar();
}

void guessZero(int guessed[10][10], int map[10][10],int x,int y){
    if(x>=0&&y<9&& map[x][y]==0 && guessed[x][y]==0){
        guessed[x][y]=1;
        if(x-1>=0 && map[x-1][y]!=-1){
            guessZero(guessed,map,x-1,y);
        }
        if(x+1<9 && map[x+1][y]!=-1){
            guessZero(guessed,map,x+1,y);
        }
        if(y-1>=0 && map[x][y-1]!=-1){
            guessZero(guessed,map,x,y-1);
        }
        if(y+1<9 && map[x][y+1]!=-1){
            guessZero(guessed,map,x,y+1);
        }
        if(x-1>=0 && y-1>=0 && map[x-1][y-1]!=-1){
            guessZero(guessed,map,x-1,y-1);
        }
        if(x+1<9 && y+1<9 && map[x+1][y+1]!=-1){
            guessZero(guessed,map,x+1,y+1);
        }
        if(x+1<9 && y-1>=0 && map[x+1][y-1]!=-1){
            guessZero(guessed,map,x+1,y-1);
        }
        if(x-1>=0 && y+1<9 && map[x-1][y+1]!=-1){
            guessZero(guessed,map,x-1,y+1);
        }
        //vision
        if(x+1<9){
            guessed[x+1][y]=2;
        }
        if(x-1>=0){
            guessed[x-1][y]=2;
        }
        if(y+1<9){
            guessed[x][y+1]=2;
        }
        if(y-1>=0){
            guessed[x][y-1]=2;
        }
        if(x-1>=0 && y-1>=0){
            guessed[x-1][y-1]=2;
        }
        if(x+1<9 &&y-1>=0){
            guessed[x+1][y-1]=2;
        }
        if(x-1>=0&&y+1<9){
            guessed[x-1][y+1]=2;
        }
        if(x+1<9 && y+1<9){
            guessed[x+1][y+1]=2;
        }
    }
}

int main(){
    lose=0,count=0;
    // int opt=1;
    int map[10][10]={{0}},guessed[10][10]={{0}};
    guess();
    mineGenerator(10, map);
    // printf("%d\n",map[xS][yS]);
    if(map[xS][yS]==0){
        guessed[xS][yS]=0;
        guessZero(guessed,map,xS,yS);
    }else if(map[xS][yS]>0){
        guessed[xS][yS]=1;
    }else{
        printf("You Failed!\n");
        return 0;
    }
    do{
        system("cls");
        // printf("====================>MAP\n");
        // for(int i=0;i<9;i++){
        //     for(int j=0;j<9;j++){
        //         printf("%d ",map[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("====================>GUESSED\n");
        // for(int i=0;i<9;i++){
        //     for(int j=0;j<9;j++){
        //         printf("%d ",guessed[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("============>exposed\n");
        // for(int i=0;i<9;i++){
        //     for(int j=0;j<9;j++){
        //         // if(guessed[i][j]==1){
        //         //     printf("%d ",map[i][j]);
        //         // }else{
        //         //     printf("* ");
        //         // }
        //         if(map[i][j]==-1){
        //             printf("- ");
        //         }else{
        //             printf("%d ",map[i][j]);
        //         }
        //     }
        //     printf("\n");
        // }printf("============>exposed\n");
        printf("    ");
        for(int i=0;i<9;i++){
            printf("%d ",i+1);
        }
        printf("\n");
        printf("   ");
        for(int i=0;i<9;i++){
            printf("--");
        }
        printf("\n");
        for(int i=0;i<9;i++){
            printf("%d | ",i+1);
            for(int j=0;j<9;j++){
                if(guessed[i][j]>=1){
                    printf("%d ",map[i][j]);
                }else{
                    printf("* ");
                }
            }
            printf("| %d",i+1);
            printf("\n");
        }
        printf("   ");
        for(int i=0;i<9;i++){
            printf("--");
        }
        printf("\n");
        printf("    ");
        for(int i=0;i<9;i++){
            printf("%d ",i+1);
        }
        printf("\n");
        if(winChecker(9,guessed)==1){
            printf("You Did it!\n");
            break;
        }
        guess();
        int dec=play(guessed,map);
        if(dec==0){
            mapReveal(map,10,guessed);
            printf("You Failed!\n");
            lose=1;
        }else if(dec==2){
            guessed[xS][yS]=0;
            guessZero(guessed,map,xS,yS);
        }else{
            guessed[xS][yS]=1;
        }
    }while(lose!=1);
}