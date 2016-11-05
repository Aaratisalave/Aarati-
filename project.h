#define SIZE 4
int score = 0;
void print(int tiles[SIZE][SIZE]);
int SearchTarget(int array[SIZE], int a, int stop);
int combine(int array[SIZE]);
void rotateboard(int tiles[SIZE][SIZE]);
int Up(int tiles[SIZE][SIZE]);
int Left(int tiles[SIZE][SIZE]);
int Down(int tiles[SIZE][SIZE]);
int Right(int tiles[SIZE][SIZE]);
int searchPair(int tiles[SIZE][SIZE]);
int Empty(int tiles[SIZE][SIZE]);
int gameOver(int tiles[SIZE][SIZE]);
void add(int tiles[SIZE][SIZE]);
void tinit(int tiles[SIZE][SIZE]);
