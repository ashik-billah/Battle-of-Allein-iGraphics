
#include "iGraphics.h"
#include "bitmap_loader.h"
#include "var.h"
#include<string>
using namespace std;
void back();
void enem();
void Plane1AndEnemyCollision();
void gameOver();
void restart();
void setPlaneEnemy();
void collisionCheck();
string str;
bool gameOverstatus = FALSE;
#define NUMBEROFPLANEENEMY 5
int enemyIndex = 0;
int image1, image2, image3;
int  image4, image5, image6, image7, image8, image9;
int image[4];

/////////scoring////
void scorePlate(){
	char score[20] = { 0 };
	iSetColor(256, 256, 256);
	_itoa(scoreC, score, 10);
	iText(800, 550, "SCORE: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(900, 550, score, GLUT_BITMAP_TIMES_ROMAN_24);
}


void showHighScore(){

	FILE* ptr;
	char str[50];
	ptr = fopen("scores.txt", "a+"); // reading the file in append mode
	string scores;
	int all_scores[100];
	int i = 0;

	if (NULL == ptr) {
		printf("file can't be opened \n");
	}


	while (fgets(str, 50, ptr) != NULL) {

		if (str != "\n"){
			all_scores[i++] = stoi(str); //converting the string into integer and storing it in an array

		}
	}
	fclose(ptr);
	int len = i, a;

	//sorting in descending order to determine high scores...

	for (i = 0; i < len; ++i){
		for (int j = i + 1; j < len; ++j)
		{
			if (all_scores[i] < all_scores[j])
			{
				a = all_scores[i];
				all_scores[i] = all_scores[j];
				all_scores[j] = a;
			}
		}

	}




	int space = 300, max_scores = 10;
	char score_text[1000], c;

	for (int i = 0; i < len; i++){
		strcpy_s(score_text, to_string(all_scores[i]).c_str()); // converting the ints to string first and then char array
		iText(500, 700 - (space), score_text, GLUT_BITMAP_TIMES_ROMAN_24); // rendering it on display
		space += 35; // space for the next score
		max_scores--; // if it reaches 0, it means total 10 scores have been painted
		if (max_scores <= 0){
			break;
		}

	}


}



// function to save score in a file in the same directory /
void saveScore(){
	FILE *fp; //file pointer

	fp = fopen("scores.txt", "a"); //open the existing file in append mode
	char final_score[33];

	itoa(scoreC, final_score, 10); //converting numbers to string

	fprintf(fp, "%s", final_score); // printing final score to text file
	fprintf(fp, "%s", "\n");

	fclose(fp); //close file
}
struct buttonCordinate
{
	int x4;
	int y4;
}bCordinate[5];
char button[10][15] = { "b\\1.bmp", "b\\2.bmp", "b\\3.bmp", "b\\4.bmp", "b\\5.bmp" };



char homemenu[50] = "front\\newmenu.bmp";
char play[55] = "bf\\1.bmp";
char score[55] = "bf\\2.bmp";

char story[50] = "bf\\3.bmp";
char about[50] = "bf\\1.bmp";



int gameState = -1; 
char p1_walk[3][100] = { "wobg\\1.png", "wobg\\2.png", "wobg\\3.png" };

int police_1_walk[3];



char pic[1][30] = { "smurf.bmp" };
bool standposition = true;
int standcounter = 0;

int i = 0;

int j = 0;
void drawBGDflag()
{
	;
}

void Charecter(){
	

		iShowImage(x, y, 100, 100, image[i]);
	


}
void Background(){
	iShowImage(0, 0, 1000, 600, image3);
	
}

//ENEMY PLANE PROPERTIES
char planeE[1][20] = { "wobg\\enm3.bmp" };

struct Enemy{
	int planeEnemy1PositionX;
	int planeEnemy1PositionY;
	int planeEnemyIndex;
	bool planeEnemyShow;
};
Enemy enemy[NUMBEROFPLANEENEMY];

void planeEnemyMovement(){
	for (int i = 0; i < NUMBEROFPLANEENEMY; i++)
	{
		if (enemy[i].planeEnemyShow){
			iShowBMP2(enemy[i].planeEnemy1PositionX, enemy[i].planeEnemy1PositionY, planeE[enemy[i].planeEnemyIndex], 0);
		}
	}
}

////pause//////
bool pause = FALSE;
 
void back(){

	//x5 += 20;
	if (x5+300 > 0){
	

		x5--;
		iShowBMP2(x5, y5, "front\\sky.bmp", 0);
	}
	else  {
		x5 = 1400;
	}
}
////////////bullet and fire ///////////////

bool firing = false;
bool shoot = false;

struct PlayerBullet{
	int playerBulletPositionX;
	int playerBulletPositionY;
	
	bool playerBulletShow = false;
};

PlayerBullet playerBullet;
void setPlayerBollet(){
	if (pause){

		playerBullet.playerBulletPositionX = x + 80;
		playerBullet.playerBulletPositionY = y + 40;

		playerBullet.playerBulletShow = true;

	}
}
void showPlayerBullet(){
	if (firing && shoot){

		if (playerBullet.playerBulletShow)
			iShowBMP2(playerBullet.playerBulletPositionX, playerBullet.playerBulletPositionY, "wobg\\bullet.bmp", 0);

	}
}
void playerShoot(){
	if (!pause){
		if (shoot){

			playerBullet.playerBulletPositionX += 10;
			if (playerBullet.playerBulletPositionX >= win_b){
				firing = false;
				shoot = false;
				playerBullet.playerBulletShow = false;
				playerBullet.playerBulletPositionX = 11000000000000000;
				playerBullet.playerBulletPositionY = 10000000000000000;

			}
	
		}
	}
}


void iDraw()
{
	
	iClear();
	

	if (gameState == -1)
	{
		iClear();
		iShowBMP(0, 0, homemenu);
		
		for (int i = 0; i < 5; i++)
		{
			iShowBMP(bCordinate[i].x4, bCordinate[i].y4, button[i]);

		}
		
	}
	else if (gameState == 0)
	{
		iClear();
		
		
		Background();
		iShowBMP(0, 570, "button\\b00.bmp");
		
		
		if (ch == 0){
			back();
			Charecter();
			

		}
		collisionCheck();
		playerShoot();
		showPlayerBullet();
		planeEnemyMovement();
		Plane1AndEnemyCollision();
		if (ch > 0){
			
			iShowImage(x, y, 120, 90, image1);
			iShowBMP2(250, 200, "front\\gameover.bmp",0);

		}
		scorePlate();
	
	}
	else if (gameState == 1)
	{
		iClear(); 
		
		iShowBMP(0, 0, score);
		iShowBMP(0, 570, "button\\b00.bmp");
		showHighScore();
	}
	else if (gameState == 2)
	{
		iClear();
		
		iShowBMP(0, 0, story);
		iShowBMP(0, 570, "button\\b00.bmp");

	}
	else if (gameState == 3)
	{
		iClear();
		
		iShowBMP(0, 0, about);
		iShowBMP(0, 570, "button\\b00.bmp");
	}
	else if (gameState == 4)
	{
		exit(0);

	}
	

}

void iPassiveMouse(int x, int y)
{
	;
}

/////////////////////////////////////////////////////////////// button///////////////////////////////////////////////



void iMouseMove(int mx, int my)
{
	

}


void iMouse(int button, int state, int mx, int my)
{


	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (gameState == -1){
			for (int i = 0; i < 5; i++){
				if (mx >= bCordinate[i].x4&& mx <= bCordinate[i].x4 + 204 && my >= bCordinate[i].y4 && my <= bCordinate[i].y4 + 80){
					gameState = i;

				}
			}
			if (gameState > 0 && gameState<0){
				pause = TRUE;
			}
			else{
				pause = FALSE;
			}
			
		}
		if (gameState != -1 ){
			if (mx >= 0 && mx <= 0 + 80 && my >= 570 && my <= 570 + 30){
				gameState = -1;
				pause = TRUE;
				restart();
			}
			
		
			

		}
		
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
			
			
		}

	}
	
}
/////////////sound///////////////////////////////////////////
bool music = TRUE;
void iKeyboard(unsigned char key)
{
	if (key == 's'){
		if (music){
			music = FALSE;
			PlaySound(0, 0, 0);
			
			
		}
		else{
			PlaySound("jump-223.wav", NULL, SND_LOOP | SND_ASYNC);
			music = TRUE;
			
		}
	}
	
	/////////////////////////////////////////////// character control  /////////////////////////////////

	
	if (!pause){


		if (key == 'u')
		{
			if (y < 600){
				y += 10;
				y++;
			}
			else {
				y = 30;
			}


		}
		else if (key == 'i')
		{

			if (x < 1000){
				x += 10;
				x++;
			}

			else {
			x = 20;
			}
		}
			
		else if (key == 'y')
		{
			if (x > 0){
				x -= 10;
				x--;
			}

			else {
				x = 20;
			}
		
		}
		else if (key == 'j')
		{
			if (y > 0){
				y -= 10;
				y--;
			}
			else {
				y = 30;
			}
		}
	}
	if (key == 'o'){
		if (firing == false && shoot == false){

			playerBullet.playerBulletPositionX = x + 80;
			playerBullet.playerBulletPositionY = y + 40;
			playerBullet.playerBulletShow = true;


			firing = true;
			shoot = true;
		}

	}


	
}


void iSpecialKeyboard(unsigned char key)
{



}


void restart(){
	ch = 0;
	x = 20;
	y = 300;
	scoreC = 0;
	firing = FALSE;
	shoot = FALSE;
	
	//PlaySound("music.wav", NULL, SND_LOOP | SND_ASYNC);
	

	

}

void keyboard(){

	i++;
	if (i >= 3)//change
	{
		i = 0;
	}

}
void enem(){


	if (!pause){
	for (int i = 0; i < NUMBEROFPLANEENEMY; i++){
		enemy[i].planeEnemy1PositionX -= 10;
		if (enemy[i].planeEnemy1PositionX <= 0){
			enemy[i].planeEnemy1PositionX = win_b + ((rand() % 50) * 10) + 1;
			enemy[i].planeEnemyShow = true;

		}
		else if (enemy[i].planeEnemy1PositionY <= 0){
			enemy[i].planeEnemy1PositionY = rand() % 500 + 1;
		}

		if (enemyIndex == 0){
			enemy[i].planeEnemyIndex = 0;

		}
		else
			enemy[i].planeEnemyIndex = 1;

		}
	}




}
void setPlaneEnemy(){

	for (int i = 0; i < NUMBEROFPLANEENEMY; i++)
	{
		enemy[i].planeEnemy1PositionX = win_b + (rand() % 50) * 10;
		enemy[i].planeEnemy1PositionY = rand() % 500;
		enemy[i].planeEnemyIndex = rand() % 10;
		enemy[i].planeEnemyShow = true;
	}
}

///////collision//////////
void gameOver(){
	if (!pause){
		pause = TRUE;
		ch = 1;
		gameOverstatus = TRUE;
		PlaySound(0, 0, 0);
		saveScore();
		firing = FALSE;
		shoot = FALSE;
		
	}
	
}


void collisionCheck()
{
	for (int i = 0; i < NUMBEROFPLANEENEMY; i++){

		if (enemy[i].planeEnemy1PositionX <= playerBullet.playerBulletPositionX && enemy[i].planeEnemy1PositionX + 100 >= playerBullet.playerBulletPositionX && enemy[i].planeEnemy1PositionY <= playerBullet.playerBulletPositionY &&enemy[i].planeEnemy1PositionY + 100 >= playerBullet.playerBulletPositionY){

			enemy[i].planeEnemyShow = false;
			playerBullet.playerBulletPositionX = win_b + 10000000000;
			enemy[i].planeEnemy1PositionX = 0;
			if (!enemy[i].planeEnemyShow){
				scoreC += 20;
			}
		}

		}
	}
void Plane1AndEnemyCollision(){

	for (int i = 0; i < NUMBEROFPLANEENEMY; i++){
		if (enemy[i].planeEnemy1PositionX <= x + 150 && enemy[i].planeEnemy1PositionX + 100 >=x && enemy[i].planeEnemy1PositionY >= y&&enemy[i].planeEnemy1PositionY + 100 <= y + 150){
			if (enemy[i].planeEnemyShow){
				enemy[i].planeEnemyShow = false;

			
		
			gameOver();
			
			}
			
			
		}

	}

}


int main()
{

	int sum = 50;
	for (int i = 4; i >= 0; i--)
	{
		bCordinate[i].x4 = 780;
		bCordinate[i].y4 = sum;
		sum += 100;
	}

	PlaySound("music.wav", NULL, SND_LOOP | SND_ASYNC);

	
	setPlaneEnemy();
	Plane1AndEnemyCollision();
	iSetTimer(300, keyboard);
	iSetTimer(100, enem);

	iInitialize(win_b, win_l, "Demo");

	image1 = iLoadImage("wobg\\go.png");
	image2 = iLoadImage("wobg\\stand.png");
	image3 = iLoadImage("wobg\\back1.png");


	image[0] = iLoadImage("wobg\\a1.bmp");
	image[1] = iLoadImage("wobg\\2.png");
	image[2] = iLoadImage("wobg\\3.png");
	


	iStart(); 

	return 0;
}











