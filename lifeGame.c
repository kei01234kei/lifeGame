#include <stdio.h>
#include <stdlib.h>
//sleep関数を使うために必要
#include <unistd.h>

//コマンドライン引数の順番
//生存範囲の幅 生存範囲の高さ 世代数 乱数のシード
int main(int argc, char *argv[]) {
    //乱数のシード値の設定
    srand(atoi(argv[4]));

    //生存範囲の配列を動的確保
    //そのセルが1なら生、0なら死
    int **range;
    range=(int **)malloc(sizeof(int *)*atoi(argv[2]));
    for (int i = 0; i < atoi(argv[2]); ++i) {
        range[i]=(int *)malloc(sizeof(int)*atoi(argv[1]));
    }
    //任意のセル周辺の生状態のセルの数を格納する配列を宣言
    int **countArray;
    countArray=(int **)malloc(sizeof(int *)*atoi(argv[2]));
    for (int i = 0; i < atoi(argv[2]); ++i) {
        countArray[i]=(int *)malloc(sizeof(int)*atoi(argv[1]));
    }

    //セルの状態を乱数を使って決める
    for (int i = 0; i < atoi(argv[2]); ++i) {
        for (int j = 0; j < atoi(argv[1]); ++j) {
            range[i][j]=rand()%2;
        }
    }

    printf("初期状態\n");
    for (int i = 0; i < atoi(argv[2]); ++i) {
        for (int j = 0; j < atoi(argv[1]); ++j) {
            if (range[i][j]==0) {
                printf("-");
            } else {
                printf("O");
            }
        }
        printf("\n");
    }
    printf("\n");

    //ここから
    for (int h = 0; h < atoi(argv[3]); ++h) {
        //周辺の生状態のセルを数えるためのfor文
        for (int i = 0; i < atoi(argv[2]); ++i) {
            for (int j = 0; j < atoi(argv[1]); ++j) {
                //セル移動のコードを簡略化するための配列を宣言
                int number[]={-1, 0, 1};
                //指定したセル周辺の生状態のセルの数を数える変数
                int count=0;
                //周辺セルの状態を調べるためのfor文
                for (int k = 0; k < 3; ++k) {
                    //配列の範囲外に出ないようにcontinueする
                    //一番上に対する範囲外エラーを除外
                    if (i==0 && k==0) {
                        continue;
                    }
                    //一番下に対する範囲外エラーを除外
                    if (i==atoi(argv[2])-1 && k==2) {
                        continue;
                    }
                    for (int l = 0; l < 3; ++l) {
                        //配列の範囲外に出ないようにcontinueする
                        //一番左に対する範囲外エラーを除外
                        if (j==0 && l==0) {
                            continue;
                        }
                        //一番右に対する範囲外エラーを除外
                        if (j==atoi(argv[1])-1 && l==2) {
                            continue;
                        }

                        //自身のセルの状態は調べる必要がないためcontinueする
                        if (k==1 && l==1) {
                            continue;
                        }

                        //周辺の指定したセルが1(生)のときcountを+1
                        if (range[i+number[k]][j+number[l]]==1) {
                            count++;
                        }
                    }
                }
                countArray[i][j]=count;
            }
        }

        //ライフゲームのルールに沿ってセルの状態を更新する
        for (int i = 0; i < atoi(argv[2]); ++i) {
            for (int j = 0; j < atoi(argv[1]); ++j) {
                //指定したセル周辺の生状態のセルの数が0個か1個のときそのセルは死状態(0)になる
                if (countArray[i][j]==0 || countArray[i][j]==1) {
                    range[i][j]=0;
                    continue;
                }
                //指定したセル周辺の生状態のセルの数が2個のときそのセルの状態は変わらない
                if (countArray[i][j]==2) {
                    continue;
                }
                //指定したセル周辺の生状態のセルの数が3個のときそのセルは生状態(1)になる
                if (countArray[i][j]==3) {
                    range[i][j]=1;
                    continue;
                }
                //指定したセル周辺の生状態のセルの数が4個以上のときそのセルは死状態(0)になる
                if (countArray[i][j]>=4) {
                    range[i][j]=0;
                    continue;
                }
            }
        }

        //0.1秒処理を止める
        usleep(0.1*1000000);
        //コンソール画面をclearする
        //system("clear");

        //range配列の様子を表示
        printf("第%d世代\n", h+1);
        for (int i = 0; i < atoi(argv[2]); ++i) {
            for (int j = 0; j < atoi(argv[1]); ++j) {
                if (range[i][j]==0) {
                    printf("-");
                } else {
                    printf("O");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    //ここまでを世代数だけfor文を使って繰り返す

    //range配列文のメモリを開放
    free(range);
    //countArray配列文のメモリを開放
    free(countArray);

    return 0;
}
