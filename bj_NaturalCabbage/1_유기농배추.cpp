/*
--------------------------------------------------
1.평면정보가 들어온다.
	[50][50] 배열가능
	0-땅
	1-배추
2. 인접한(상하좌우) 배추들은 지렁이를 공유한다.
	2.1 0,0부터 50,50까지 어떻게 훑을 것인가?
		: 1번에서 입력받을 때, 어떤 구조체에 미리 정보를 저장한다. 1은 접근해야하는 정보, 0은 접근 안해도되는 정보.
		: 상하좌우가 배열을 초과하면 배제한다.
	2.2 이미 훑었던 곳은 어떻게 처리할 것인가?
		: 훑고나서 재정리를 할지, 말지?
		: 어떤 구조체가 접근안해도 되면 넘어간다.
	2.3 한번 훑고 다음번 훑을 때 어디를 기준으로 할 것인가?
		: 어떤 구조체에 접근해야되는 정보, ???
3. 필요한 최소 지렁이 수를 출력한다.
-----------------------------------------------------
g_ [50][50]DP확인용, 평면정보 다음으로 체크하며 불필요시 동작x
S_ 구조체[50*50] 배추가 있는 위치정보, wc 2500
-------------------------------------------------------
Q. 위치를 훑으면 바로 빼버리면 안되나?
Q.DFS,BFS로는 어떻게 짤래?
	: 배추위치정보는 다 받아야함. 이때 스택 혹은 큐로 초기값 넣고,
	  스택 혹은 큐에서 자료하나를 빼서 탐색하고, 인접좌표를 탐색.(0이거나, 인풋을 넘거나,이미 방문했으면 탐색불필요), 자료가 없을 때까지.


*/
#include <stdio.h>

struct S_Cabbage
{
	int nX;
	int nY;
};

S_Cabbage g_arsCabbage[2500]{};
int g_CabaggeCount(0);
int g_arDP[50][50]{};

void printtest()//테스트용
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			printf("[%d]", g_arDP[i][j]);
		}
		printf("\n");
	}
	printf("---------------------\n");
}

void initArDP();
void initArCabbage(int nUsedSize);
int isAcessRange(int nWidth, int nHeight, int nX, int nY);
int isAcessDP(int nX, int nY);

void spreadWorm(int nWidth, int nHeight, int nX, int nY);

int main()
{
	int nTestCaseNum(0);
	int nWidth(0), nHeight(0);
	int nCabbageNum(0);
	int nX(0), nY(0);

	int nTargetX(0), nTargetY(0);

	int nWornNum(0);
	//
	freopen("input.txt", "r", stdin);
	scanf("%d", &nTestCaseNum);
	//
	nCabbageNum = 0;
	for (int i = 0; i < nTestCaseNum; ++i)
	{
		g_CabaggeCount = 0;
		initArDP();
		initArCabbage(nCabbageNum);
		scanf("%d %d %d", &nWidth, &nHeight, &nCabbageNum);
		for (int j = 0; j < nCabbageNum; ++j)
		{
			scanf("%d %d", &nX, &nY);
			g_arDP[nY][nX] = 1;
			g_arsCabbage[g_CabaggeCount].nX = nX;
			g_arsCabbage[g_CabaggeCount].nY = nY;
			++g_CabaggeCount;
		}


		//
		nWornNum = 0;
		for (int i = 0; i < nCabbageNum; ++i)
		{
			nTargetX = g_arsCabbage[i].nX;
			nTargetY = g_arsCabbage[i].nY;


			if (isAcessDP(nTargetX, nTargetY))
			{
				spreadWorm(nWidth, nHeight, nTargetX, nTargetY);
				++nWornNum;
			}

		}


		//
		printf("%d\n", nWornNum);
	}

	
	return 0;
}

void initArDP()
{
	for (int i = 0; i < 50; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			g_arDP[i][j] = 0;
		}
	}
}

void initArCabbage(int nUsedSize)
{
	for (int i = 0; i < nUsedSize; ++i)
	{
		g_arsCabbage[i].nX = 0;
		g_arsCabbage[i].nY = 0;
	}
}

int isAcessRange(int nWidth, int nHeight, int nX, int nY)
{
	if (nX >= 0 && nX < nWidth && nY >= 0 && nY < nHeight)
		return 1;
	else
		return 0;
}

int isAcessDP(int nX, int nY)
{
	if (g_arDP[nY][nX] == 1)
		return 1;
	else
		return 0;
}

void spreadWorm(int nHeight, int nWidth, int nX, int nY)
{
	g_arDP[nY][nX] = 0;

	if (isAcessRange(nHeight, nWidth, nX + 1, nY))
	{
		if (isAcessDP(nX + 1, nY))
		{
			spreadWorm(nHeight, nWidth, nX + 1, nY);
		}
	}

	if (isAcessRange(nHeight, nWidth, nX - 1, nY))
	{
		if (isAcessDP(nX - 1, nY))
		{
			spreadWorm(nHeight, nWidth, nX - 1, nY);
		}
	}

	if (isAcessRange(nHeight, nWidth, nX, nY + 1))
	{
		if (isAcessDP(nX, nY + 1))
		{
			spreadWorm(nHeight, nWidth, nX, nY + 1);
		}
	}

	if (isAcessRange(nHeight, nWidth, nX, nY - 1))
	{
		if (isAcessDP(nX, nY - 1))
		{
			spreadWorm(nHeight, nWidth, nX, nY - 1);
		}
	}

}

