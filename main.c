//基于easyx图形库的C语言
//网站有:http://www.easyx.cn/

#include<stdio.h>
#include<graphics.h>
#include<time.h>


#define N 10
int win;

void addFun(int map[][N + 2], int hmap[][N + 2],int x,int y)
{
	int i, j;
	for (i = x - 1; i <= x + 1; i++){
		for (j = y - 1; j <= y + 1; j++){
			if (i == 0 || i == 11 || j == 0 || j == 11){ continue; }
			else if (hmap[i][j] != 0){ continue; }
			else if (map[i][j] == 0){
				hmap[i][j] = 10; win++;
			}
			else{ hmap[i][j] = map[i][j]; win++; }
			}
		}
	
	return;
}
void game(){

	int map[N+2][N+2] = { 0 };
	int hmap[N + 2][N + 2] = { 0 };
	int m, n, i, j;
	srand((unsigned)time(NULL));
	for (n = 0; n < N;){
		i = rand() % N + 1;
		j = rand() % N + 1;
		if (map[i][j] == 0){
			map[i][j] = -1;
			n++;
		}
	}
	
	for (i = 1; i <= N; i++){
		for (j = 1; j <= N; j++){
			if (map[i][j] != -1) {
				
				for (m = i - 1; m <= i + 1; m++){
					for (n = j - 1; n <= j + 1; n++){
						if (map[m][n] == -1){
							map[i][j]++;
						}
					}
				}
			}
		}
	}
	
	initgraph(64*N, 64*N);
	IMAGE img[12];
	loadimage(&img[0], L"0.jpg", 64, 64);
	loadimage(&img[1], L"1.jpg", 64, 64);
	loadimage(&img[2], L"2.jpg", 64, 64);
	loadimage(&img[3], L"3.jpg", 64, 64);
	loadimage(&img[4], L"4.jpg", 64, 64);
	loadimage(&img[5], L"5.jpg", 64, 64);
	loadimage(&img[6], L"6.jpg", 64, 64);
	loadimage(&img[7], L"7.jpg", 64, 64);

	loadimage(&img[8], L"8.jpg", 64, 64);
	loadimage(&img[9], L"雷.jpg", 64, 64);
	loadimage(&img[10], L"空.jpg", 64, 64);
	loadimage(&img[11], L"标记.jpg", 64, 64);
	win = 0;
	while (1){
		drawmap(hmap,img);
		if (play(map, hmap) == -1){
			drawmap(hmap, img);
			MessageBox(0, L"雷来了", L"BOOM", MB_OK);
			return;
		}
		
		if (win == N*N - N){
			drawmap(hmap, img);
			MessageBox(0, L"你赢了", L"WELL PLAYED", MB_OK);
			break;
		}
	}
	
}
void drawmap(int hmap[][N+2],IMAGE *img){
	
	for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			switch (hmap[i][j]){
			case -1:putimage(64 * (i - 1), 64 * (j - 1), &img[9]); break;
			case 0:putimage(64 * (i - 1), 64 * (j - 1), &img[10]); break;
			case 10:putimage(64 * (i - 1), 64 * (j - 1), &img[0]); break;
			case 1:putimage(64 * (i - 1), 64 * (j - 1), &img[1]); break;
			case 2:putimage(64 * (i - 1), 64 * (j - 1), &img[2]); break;
			case 3:putimage(64 * (i - 1), 64 * (j - 1), &img[3]); break;
			case 4:putimage(64 * (i - 1), 64 * (j - 1), &img[4]); break;
			case 5:putimage(64 * (i - 1), 64 * (j - 1), &img[5]); break;
			case 6:putimage(64 * (i - 1), 64 * (j - 1), &img[6]); break;
			case 7:putimage(64 * (i - 1), 64 * (j - 1), &img[7]); break;
			case 8:putimage(64 * (i - 1), 64 * (j - 1), &img[8]); break;
			case 9:putimage(64 * (i - 1), 64 * (j - 1), &img[9]); break;
			case 11:putimage(64 * (i - 1), 64 * (j - 1), &img[11]); break;
			default: break;
			}
		}
	}
}

int play(int map[][N+2], int hmap[][N+2]){
	
	MOUSEMSG msg;
	while (1){
		msg = GetMouseMsg();
		switch (msg.uMsg){
			//左键点开
		case WM_LBUTTONDOWN:
			//switch改进 先用if
			if (hmap[msg.x / 64 + 1][msg.y / 64 + 1] != 0){ continue; }
			if (map[msg.x / 64 + 1][msg.y / 64 + 1] == 0){
				addFun(map, hmap, msg.x / 64 + 1, msg.y / 64 + 1);			
			}
			else { hmap[msg.x / 64 + 1][msg.y / 64 + 1] = map[msg.x / 64 + 1][msg.y / 64 + 1]; win++; }		
			return map[msg.x / 64 + 1][msg.y / 64 + 1];
			break;

		case WM_RBUTTONDOWN:
			if (hmap[msg.x / 64 + 1][msg.y / 64 + 1] == 0){ hmap[msg.x / 64 + 1][msg.y / 64 + 1] = 11; }
			else if (hmap[msg.x / 64 + 1][msg.y / 64 + 1] == 11){ hmap[msg.x / 64 + 1][msg.y / 64 + 1] = 0; }
			else { continue; }
			return 0;
			break;
	
		}
	}
}



int main(){
	do{
		game();
		if (MessageBox(0, L"你输了，再玩一局?", L"退出", MB_RETRYCANCEL) == IDCANCEL){
			break;
		}

	} while (TRUE);
	closegraph();
	return 0;
}
