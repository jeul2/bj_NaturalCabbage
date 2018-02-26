/*
--------------------------------------------------
1.��������� ���´�.
	[50][50] �迭����
	0-��
	1-����
2. ������(�����¿�) ���ߵ��� �����̸� �����Ѵ�.
	2.1 0,0���� 50,50���� ��� ���� ���ΰ�?
		: 1������ �Է¹��� ��, � ����ü�� �̸� ������ �����Ѵ�. 1�� �����ؾ��ϴ� ����, 0�� ���� ���ص��Ǵ� ����.
		: �����¿찡 �迭�� �ʰ��ϸ� �����Ѵ�.
	2.2 �̹� �Ⱦ��� ���� ��� ó���� ���ΰ�?
		: �Ȱ��� �������� ����, ����?
		: � ����ü�� ���پ��ص� �Ǹ� �Ѿ��.
	2.3 �ѹ� �Ȱ� ������ ���� �� ��� �������� �� ���ΰ�?
		: � ����ü�� �����ؾߵǴ� ����, ???
3. �ʿ��� �ּ� ������ ���� ����Ѵ�.
-----------------------------------------------------
g_ [50][50]DPȮ�ο�, ������� �������� üũ�ϸ� ���ʿ�� ����x
S_ ����ü[50*50] ���߰� �ִ� ��ġ����, wc 2500
-------------------------------------------------------
Q. ��ġ�� ������ �ٷ� �������� �ȵǳ�?
Q.DFS,BFS�δ� ��� ©��?
	: ������ġ������ �� �޾ƾ���. �̶� ���� Ȥ�� ť�� �ʱⰪ �ְ�,
	  ���� Ȥ�� ť���� �ڷ��ϳ��� ���� Ž���ϰ�, ������ǥ�� Ž��.(0�̰ų�, ��ǲ�� �Ѱų�,�̹� �湮������ Ž�����ʿ�), �ڷᰡ ���� ������.


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

void printtest()//�׽�Ʈ��
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

