#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <cmath>
#include <stdlib.h>

using std::string;
using std::cout;
using std::endl;

bool turn=true;
void imprimir(char** ,int,int);
void inicializarmatriz(char** , int, int);
int cord_pieza(char []);
int cord_piezamov(char []);
int cordnumerica1(char []);
int cordnumerica2(char []);
void mover(int,int,int,int,char** matriz);
void mover2(int,int,int,int,char** matriz);
int distancias(int  ,int  ,int  , int );
int alfilnum(int );
void cargarpartida(char**,int,int );
void guardarpartida(char**,int,int );
bool reyblanco(char**, int ,int);
bool reynegro(char**,int,int);


int main(int argc, char* argv[]){
	initscr();
	start_color();
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(10,COLOR_BLUE,COLOR_BLACK);	
	init_pair(5,COLOR_MAGENTA,COLOR_BLACK);	
	init_pair(12,COLOR_YELLOW,COLOR_BLACK);
	int size=9;
	int column=25;
	move(5,18);
	char** matriz=new char*[column];
	int opcion=0;
	while(opcion!=3){
		initscr();
		attron(COLOR_PAIR(3));
		mvprintw(5,30,"********* BIENVENIDOS A MI JUEGO DE AJEDREZ ****************");
		attron(COLOR_PAIR(10));
		mvprintw(7,40,"1 - Para cargar Partida Guardadada");
		attron(COLOR_PAIR(5));
		mvprintw(8,40,"2 - Para comenzar una partida nueva");
		attron(COLOR_PAIR(12));
		mvprintw(9,40,"3 - Salir");
		opcion=getch();

		if (opcion=='1'){
			cargarpartida(matriz,size,column);
		}else if(opcion=='2'){
			inicializarmatriz(matriz,size,column);
		}else{
			break;
		}
		clear();
		move(10,0);
		imprimir(matriz,size,column);
		bool seguirjuego=true;
		while(seguirjuego){
			initscr();
			char continuar;
			move(5,18);
		    attron(COLOR_PAIR(3));
		    printw("*-*-*-*-*-*-AJEDREZ-*-*-*-*-*-*-*-*");
			int elegidoletra,elegidonum,moverletra,movernumero;
			move(11,31);
			attron(COLOR_PAIR(10));
			printw("-Minusculas = BLANCAS -");
			move(11,55);
			attron(COLOR_PAIR(5));
			printw("   -Mayusculas = NEGRAS -");
			
			if(turn){	
				move(13,31);
				attron(COLOR_PAIR(10));
				printw("Blancas: ");
				int numberCounter = 0;//para elementos especiales de las coordenadas.
				char number[4];//para guardar la coordenada
				while(numberCounter <5 ){
					noecho();
					char temp;
					temp = getch();
					if(((temp>=65 && temp<=72)) && (numberCounter == 0 || numberCounter==3)){
						echo();
						addch(temp);
						number[numberCounter] = temp;
						numberCounter++;
					} else if ((temp>= 49 && temp<=56) && (numberCounter==1 || numberCounter==4)){
						echo();
						addch(temp);
						number[numberCounter] = temp;
						numberCounter++;
					}
					if(numberCounter == 2 ){
						temp='-';
						echo();
						addch(temp);
						number[numberCounter] = temp;
						numberCounter++;
					}
				}

				getch();
			
				//**********************COORDENADA DE LA PIEZA A MOVER************
				elegidoletra=cord_pieza(number);
				elegidonum=cordnumerica1(number);
				//************************COORDENADA HACIA A DONDE MOVER************
				moverletra=cord_piezamov(number);
				movernumero=cordnumerica2(number);
				 
				mover(elegidoletra,elegidonum,moverletra,movernumero,matriz);
				
				move(10,0);
				imprimir(matriz,size,column);
				char selection;
				if(!turn){
					mvprintw(20,30,"Desea gurdar y Salir s/n");
					selection=getch();
					if (selection=='s' || selection=='S' ){
						guardarpartida(matriz,size,column);
						seguirjuego=false;

						break;
					}

					refresh();
					
				}
			 
			}else{
				move(13,58);
				attron(COLOR_PAIR(5));
				printw("Negras:");
				int numberCounter = 0;//para elementos especiales de las coordenadas.
				char number[4];//para guardar la coordenada
				while(numberCounter <5 ){
					noecho();
					char temp;
					temp = getch();
					if(((temp>=65 && temp<=72)) && (numberCounter == 0 || numberCounter==3)){
						echo();
						addch(temp);
						number[numberCounter] = temp;
						numberCounter++;
					} else if ((temp>= 49 && temp<=56) && (numberCounter==1 || numberCounter==4)){
						echo();
						addch(temp);
						number[numberCounter] = temp;
						numberCounter++;
					}
					if(numberCounter == 2 ){
						temp='-';
						echo();
						addch(temp);
						number[numberCounter] = temp;
						numberCounter++;
					}
				}

				getch();


				//**********************COORDENADA DE LA PIEZA A MOVER************
				elegidoletra=cord_pieza(number);
				elegidonum=cordnumerica1(number);
				//************************COORDENADA HACIA A DONDE MOVER************
				moverletra=cord_piezamov(number);
				movernumero=cordnumerica2(number);
	
				mover2(elegidoletra,elegidonum,moverletra,movernumero,matriz);
			
				move(10,0);
				imprimir(matriz,size,column);
				char selection='a';
				if(turn){
					mvprintw(20,30,"Desea gurdar y Salir s/n");
					selection=getch();
					if (selection=='s' || selection=='S' ){
						guardarpartida(matriz,size,column);
						seguirjuego=false;
						break;
					}
					mvprintw(20,30,"");
					refresh();
				}

			}
			




		}













	
		endwin();
	}

	getch();
	endwin();
	return 0;
}



bool reyblanco(char** matriz,int size, int column){
	bool seguirjuego=false;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < column; j++){
			if (matriz[i][j]=='r'){
				seguirjuego=true;
			}
			
		}
	}
	return seguirjuego;
}

bool reynegro(char** matriz, int size, int column){
	bool seguirjuego=false;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < column; j++){
			if (matriz[i][j]=='R'){
				seguirjuego=true;
			}
		}
	}
	return seguirjuego;
}



bool esjaque(char** matriz, int size, int column, int jugador){
 	char rey;
 	if (jugador==1){
 		rey='r';	
 	}else{
 		rey='R';
	}

 	int numerorey, columnarey;
	for (int i = 0; i < size; i++){
  		for (int j=2;j<column; j+3){
	 		if (matriz[i][j]==rey){
			 	numerorey=i;
			 	columnarey=j;
	 		}
	 	}
	}

	char tablero[8][23];
	for (int i = 0; i < size; i++){
	}







}

bool jaquemate(){


}
////////////////este guarda//////////////////////
void guardarpartida(char** matriz,int size, int column){
	cout<<"HOLA"<<endl;
	FILE *partidaguardada=fopen("partidaguardada.bin","wb");
	for (int i = 0; i < size; i++){
		for (int j = 0; j < column; j++){
			fwrite(&(matriz[i][j]),sizeof(char**),1,partidaguardada);
		}
	}
}
///////////////este carga///////////////////////////////
void cargarpartida(char** matriz, int size, int column){


	FILE *partidaguardada=fopen("partidaguardada.bin","rbS");


	for (int i = 0; i < size; i++){
		for (int j = 0; j < column; j++){
			fread(&(matriz[i][j]),sizeof(char**),1,partidaguardada);
		}
	}


	fclose(partidaguardada);
}

void mover(int elegidoletra,int elegidonum,int moverletra, int movernumero ,char** matriz){
		initscr();
		int distancia=distancias(elegidoletra,elegidonum,moverletra,movernumero);
//************************************************************* PEONES BLANCOS *********************************************************************************************
	if (matriz[elegidonum][elegidoletra]=='p'){
		if(elegidonum==2  && elegidoletra==moverletra){
		
			if(distancia==2){
				//////////////////////////////////////////

				
				if (matriz[elegidonum+1][elegidoletra]=='p' || matriz[elegidonum+1][elegidoletra]=='t'|| matriz[elegidonum+1]	[elegidoletra]=='c' ||
				   	matriz[elegidonum+1][elegidoletra]=='a' || matriz[elegidonum+1][elegidoletra]=='r' || matriz[elegidonum+1][elegidoletra]=='q'    ){
						printw ("pieza amiga, bloquea el paso");

				}else if(matriz[elegidonum+1][elegidoletra]=='P' || matriz[elegidonum+1][elegidoletra]=='T' || matriz[elegidonum+1][elegidoletra]=='C' ||
				    matriz[elegidonum+1][elegidoletra]=='A' || matriz[elegidonum+1][elegidoletra]=='R' || matriz[elegidonum+1][elegidoletra]=='Q'    ){
						printw ("pieza enemiga, bloquea el paso");
						 
				}


				if(matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='t' || matriz[movernumero][moverletra]=='c' ||
						matriz[movernumero][moverletra]=='a'  || matriz[movernumero][moverletra]=='r' ||matriz[movernumero][moverletra]=='q'){
					printw("Ya existe una pieza amiga en esta pocicion");

				}else{
					matriz[elegidonum][elegidoletra]='_';
					matriz[movernumero][moverletra]='p';
					turn=false;
				}



			
			}else if (distancia==1){
				if(matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='t' || matriz[movernumero][moverletra]=='c' ||
					matriz[movernumero][moverletra]=='a'  || matriz[movernumero][moverletra]=='r' ||matriz[movernumero][moverletra]=='q'){
						printw("Ya existe una pieza amiga en esta pocicion");
				}else if(matriz[movernumero][moverletra]=='P' || matriz[movernumero][moverletra]=='T' || matriz[movernumero][moverletra]=='C' ||
					matriz[movernumero][moverletra]=='A'  || matriz[movernumero][moverletra]=='R' ||matriz[movernumero][moverletra]=='Q'){
						printw("no puede comer en linea recta");
				}else{
					matriz[elegidonum][elegidoletra]='_';
					matriz[movernumero][moverletra]='p';
					turn=false;
				}
			}



		}else if(elegidonum!=2 && distancia==1  && elegidoletra==moverletra){
			if (matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='t' || matriz[movernumero][moverletra]=='c' ||
				matriz[movernumero][moverletra]=='a'  || matriz[movernumero][moverletra]=='r' ||matriz[movernumero][moverletra]=='q'){
				printw("Ya existe una pieza amiga en esta pocicion");	
			}else if(matriz[movernumero][moverletra]=='P' || matriz[movernumero][moverletra]=='T' || matriz[movernumero][moverletra]=='C' ||
				matriz[movernumero][moverletra]=='A'  || matriz[movernumero][moverletra]=='R' ||matriz[movernumero][moverletra]=='Q'){
				printw("no puede comer en linea recta con PEONES");	
			}else {
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='p';
				turn=false;	
			}




		}else if(distancia==3  && elegidoletra != moverletra){
			if(matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='t' || matriz[movernumero][moverletra]=='c' ||
				matriz[movernumero][moverletra]=='a'  || matriz[movernumero][moverletra]=='r' ||matriz[movernumero][moverletra]=='q'){
				printw("Ya existe una pieza amiga en esta pocicion");	
			}else{
				matriz[elegidonum][elegidoletra]='_';
					matriz[movernumero][moverletra]='p';
					turn=false;
			}
		}else {
			printw("movimiento invalido");
		}

//************************************************************* TORRES BLANCAS *********************************************************************************************
	}else if (matriz[elegidonum][elegidoletra]=='t'){
		bool puede=true;
		if (elegidoletra==moverletra && elegidonum!=movernumero){
			for (int j= elegidonum+1; j<movernumero; j++){
				if (matriz[j][elegidoletra]=='P' || matriz[j][elegidoletra]=='T' || matriz[j][elegidoletra]=='C' || 
					matriz[j][elegidoletra]=='A' ||matriz[j][elegidoletra]=='R' || matriz[j][elegidoletra]=='Q' ){
					printw("paso bloqueado por pieza enemiga");
					puede=false;
				
					break;
				}else if(matriz[j][elegidoletra]=='p' || matriz[j][elegidoletra]=='t' || matriz[j][elegidoletra]=='c' || 
					matriz[j][elegidoletra]=='a' ||matriz[j][elegidoletra]=='r' || matriz[j][elegidoletra]=='q' ){
					printw("paso bloqueado por pieza amiga");
					puede=false;
					break;
				}
			}
		}else if(elegidoletra!=moverletra && elegidonum==movernumero){

			if (elegidoletra<moverletra){
				
				
				for (int i = elegidoletra+3; i <moverletra; i++){
					if (matriz[elegidonum][i]=='P' || matriz[elegidonum][i]=='T' || matriz[elegidonum][i]=='C' || 
						matriz[elegidonum][i]=='A' || matriz[elegidonum][i]=='C' || matriz[elegidonum][i]=='Q'){
						printw("paso bloqueado por pieza enemiga");
						puede=false;
						break;	

					}else if(matriz[elegidonum][i]=='p' || matriz[elegidonum][i]=='t' || matriz[elegidonum][i]=='c' || 
						matriz[elegidonum][i]=='a' || matriz[elegidonum][i]=='r' || matriz[elegidonum][i]=='q'){
						printw("paso bloqueado por amiga");	
						puede=false;
						break;
					}

					i+=2;
				}
			}else{
				for (int i = elegidoletra-3; i <moverletra; i--){
					if (matriz[elegidonum][i]=='P' || matriz[elegidonum][i]=='T' || matriz[elegidonum][i]=='C' || 
						matriz[elegidonum][i]=='A' || matriz[elegidonum][i]=='C' || matriz[elegidonum][i]=='Q'){
						printw("paso bloqueado por pieza enemiga");
						puede=false;
						break;	

					}else if(matriz[elegidonum][i]=='p' || matriz[elegidonum][i]=='t' || matriz[elegidonum][i]=='c' || 
						matriz[elegidonum][i]=='a' || matriz[elegidonum][i]=='r' || matriz[elegidonum][i]=='q'){
						printw("paso bloqueado por amiga");	
						puede=false;
						break;
					}

					i-=2;
				}

			}
		}else if (elegidoletra!=elegidonum  && movernumero!=moverletra){
			puede=false;
		}
		if(puede){
			if (matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='t' || matriz[movernumero][moverletra]=='c' || 
				matriz[movernumero][moverletra]=='a' ||matriz[movernumero][moverletra]=='r' || matriz[movernumero][moverletra]=='q' ){
				printw("ya existe una pieza amiga en esta poscicion");
			}else{
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='t';
				turn=false;
			}
		}else{
			printw("movimiento invalido");
		}

//************************************************************* CABALLOS BLANCOS *******************************************************************************************
	}else if (matriz[elegidonum][elegidoletra]=='c'){
		bool puede=true;
		if (movernumero==(elegidonum+2)  &&  moverletra==(elegidoletra-3)){
			puede=true;
		}else if (movernumero==(elegidonum+1) && moverletra==(elegidoletra-6)){
			puede=true;
		}else if(movernumero==(elegidonum+2) && moverletra==(elegidoletra+3)){
			puede=true;
		}else if(movernumero==(elegidonum+1) && moverletra==(elegidoletra+6)){
			puede=true;
		}else if(movernumero==(elegidonum-1) && moverletra==(elegidoletra-6)){
			puede=true;
		}else if(movernumero==(elegidonum-2) && moverletra==(elegidoletra-3)){
			puede=true;
		}else if (movernumero==(elegidonum-2) && moverletra==(elegidoletra+3)){
			puede=true;
		}else if (movernumero==(elegidonum-1) && moverletra==(elegidoletra+3)){
			puede=true;
		}else{
			puede=false;
		}

		if (puede){
			if (matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='t' || matriz[movernumero][moverletra]=='c' ||
				matriz[movernumero][moverletra]=='a' || matriz[movernumero][moverletra]=='q' || matriz[movernumero][moverletra]=='r'  ){
				printw("Ya existe una pieza amiga en esta poscicion");
			}else{
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='c';
				turn=false;	
			}

			
		}else{
			printw("movimiento invalido");
		}

//************************************************************** ALFILES BLANCOS *******************************************************************************************

	}else if (matriz[elegidonum][elegidoletra]=='a'){
		int valorletraelejida=(alfilnum(elegidoletra));
		int  valornumeroletramover=(alfilnum(moverletra));
		bool puede=true;



		if(abs(valorletraelejida-valornumeroletramover) && abs(elegidonum-movernumero)){
			puede=true;
			if (elegidoletra < moverletra && elegidonum>movernumero){
				int j=elegidoletra;
				for (int i = elegidonum-1; i >movernumero-1 ; --i){
					j-=3;
					if (matriz[elegidonum][elegidoletra]=='p' || matriz[elegidonum][elegidoletra]=='t' || matriz[elegidonum][elegidoletra]=='c' ||
						matriz[elegidonum][elegidoletra]=='a' || matriz[elegidonum][elegidoletra]=='r' || matriz[elegidonum][elegidoletra]=='q'){
						turn=false;
						printw("pieza amiga en el camino 1");
						break;
					}else if(matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=false;
						printw("pieza enemiga en el camino 2" );
						break;
					}

				}
			}else if(elegidoletra < moverletra &&  elegidonum > movernumero){
				int j=elegidoletra;
				for (int i = elegidonum+1; i >movernumero-1 ; ++i){
					 j+=3;
					if (matriz[elegidonum][elegidoletra]=='p' || matriz[elegidonum][elegidoletra]=='t' || matriz[elegidonum][elegidoletra]=='c' ||
						matriz[elegidonum][elegidoletra]=='a' || matriz[elegidonum][elegidoletra]=='r' || matriz[elegidonum][elegidoletra]=='q'){
						turn=false;
						printw("pieza amiga en el camino 3");
						break;
					}else if(matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=false;
						printw("pieza enemiga en el camino 4");
						break;
					}
				}		
			}else if(elegidoletra > moverletra  && elegidonum < movernumero){
				int j=elegidoletra;
				for (int i = elegidonum+1; i > movernumero-1; ++i){
					j+=3;
					if (matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=false;
						printw("pieza amiga en el camino 5" );
						break;
					}else if(matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=false;
						printw("pieza enemiga en el camino");
						break;
					}
				}
			}else if(elegidoletra < moverletra  && elegidonum < movernumero){
				int j=elegidoletra;
				for (int i = elegidonum; i < movernumero+1; --i){
				 	j-=3;
				 	if (matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=false;
						printw("pieza amiga en el camino 6");
						break;
					}else if(matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=false;
						printw("pieza enemiga en el camino");
						break;
					}
				}
			}
		}else{
			printw("no se esta moviendo diagonalmente");
			puede=false;
		}


		if (puede){
			if(matriz[movernumero][moverletra]=='p' ||  matriz[movernumero][moverletra]=='t' || matriz[movernumero][moverletra]=='c' || 
			matriz[movernumero][moverletra]=='a' || matriz[movernumero][moverletra]=='r' || matriz[movernumero][moverletra]=='q'){
				printw("Ya existe una pieza amiga en esa pocicion");
			}else {
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='a';
				turn=false;
			}
		}

//**************************************************************REINA BLANCA************************************************************************************************

	}else if (matriz[elegidonum][elegidoletra]=='q'){
		int valorletraelejida=(alfilnum(elegidoletra));
		int  valornumeroletramover=(alfilnum(moverletra));
		bool puede=true;



		if(abs(valorletraelejida-valornumeroletramover) && abs(elegidonum-movernumero)){
			puede=true;
			if (elegidoletra < moverletra && elegidonum>movernumero){
				int j=elegidoletra;
				for (int i = elegidonum-1; i >movernumero-1 ; --i){
					j-=3;
					if (matriz[elegidonum][elegidoletra]=='p' || matriz[elegidonum][elegidoletra]=='t' || matriz[elegidonum][elegidoletra]=='c' ||
						matriz[elegidonum][elegidoletra]=='a' || matriz[elegidonum][elegidoletra]=='r' || matriz[elegidonum][elegidoletra]=='q'){
						turn=true;
						printw("pieza amiga en el camino");
						break;
					}else if(matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=true;
						printw("pieza enemiga en el camino" );
						break;
					}

				}
			}else if(elegidoletra < moverletra &&  elegidonum > movernumero){
				int j=elegidoletra;
				for (int i = elegidonum+1; i >movernumero-1 ; ++i){
					 j+=3;
					if (matriz[elegidonum][elegidoletra]=='p' || matriz[elegidonum][elegidoletra]=='t' || matriz[elegidonum][elegidoletra]=='c' ||
						matriz[elegidonum][elegidoletra]=='a' || matriz[elegidonum][elegidoletra]=='r' || matriz[elegidonum][elegidoletra]=='q'){
						turn=true;
						printw("pieza amiga en el camino");
						break;
					}else if(matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=false;
						printw("pieza enemiga en el camino 4");
						break;
					}
				}		
			}else if(elegidoletra > moverletra  && elegidonum < movernumero){
				int j=elegidoletra;
				for (int i = elegidonum+1; i > movernumero-1; ++i){
					j+=3;
					if (matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=true;
						printw("pieza amiga en el camino" );
						break;
					}else if(matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=true;
						printw("pieza enemiga en el camino");
						break;
					}
				}
			}else if(elegidoletra < moverletra  && elegidonum < movernumero){
				int j=elegidoletra;
				for (int i = elegidonum; i < movernumero+1; --i){
				 	j-=3;
				 	if (matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=true;
						printw("pieza amiga en el camino");
						break;
					}else if(matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=true;
						printw("pieza enemiga en el camino");
						break;
					}
				}
			}
		}else if (elegidoletra==moverletra && elegidonum!=movernumero){
			for (int j= elegidonum+1; j<movernumero; j++){
				if (matriz[j][elegidoletra]=='P' || matriz[j][elegidoletra]=='T' || matriz[j][elegidoletra]=='C' || 
					matriz[j][elegidoletra]=='A' ||matriz[j][elegidoletra]=='R' || matriz[j][elegidoletra]=='Q' ){
					printw("paso bloqueado por pieza enemiga");
					puede=false;
				
					break;
				}else if(matriz[j][elegidoletra]=='p' || matriz[j][elegidoletra]=='t' || matriz[j][elegidoletra]=='c' || 
					matriz[j][elegidoletra]=='a' ||matriz[j][elegidoletra]=='r' || matriz[j][elegidoletra]=='q' ){
					printw("paso bloqueado por pieza amiga");
					puede=false;
					break;
				}
			}
		}else if(elegidoletra!=moverletra && elegidonum==movernumero){

			if (elegidoletra<moverletra){
				
				
				for (int i = elegidoletra+3; i <moverletra; i++){
					if (matriz[elegidonum][i]=='P' || matriz[elegidonum][i]=='T' || matriz[elegidonum][i]=='C' || 
						matriz[elegidonum][i]=='A' || matriz[elegidonum][i]=='C' || matriz[elegidonum][i]=='Q'){
						printw("paso bloqueado por pieza enemiga");
						puede=false;
						break;	

					}else if(matriz[elegidonum][i]=='p' || matriz[elegidonum][i]=='t' || matriz[elegidonum][i]=='c' || 
						matriz[elegidonum][i]=='a' || matriz[elegidonum][i]=='r' || matriz[elegidonum][i]=='q'){
						printw("paso bloqueado por amiga");	
						puede=false;
						break;
					}

					i+=2;
				}
			}else{
				for (int i = elegidoletra-3; i <moverletra; i--){
					if (matriz[elegidonum][i]=='P' || matriz[elegidonum][i]=='T' || matriz[elegidonum][i]=='C' || 
						matriz[elegidonum][i]=='A' || matriz[elegidonum][i]=='C' || matriz[elegidonum][i]=='Q'){
						printw("paso bloqueado por pieza enemiga");
						puede=false;
						break;	

					}else if(matriz[elegidonum][i]=='p' || matriz[elegidonum][i]=='t' || matriz[elegidonum][i]=='c' || 
						matriz[elegidonum][i]=='a' || matriz[elegidonum][i]=='r' || matriz[elegidonum][i]=='q'){
						printw("paso bloqueado por amiga");	
						puede=false;
						break;
					}

					i-=2;
				}

			}
		}else if (elegidoletra!=elegidonum  && movernumero!=moverletra){
			puede=false;
		}
		
		if (puede){
			if(matriz[movernumero][moverletra]=='p' ||  matriz[movernumero][moverletra]=='t' || matriz[movernumero][moverletra]=='c' || 
			matriz[movernumero][moverletra]=='a' || matriz[movernumero][moverletra]=='r' || matriz[movernumero][moverletra]=='q'){
				printw("Ya existe una pieza amiga en esa pocicion");
			}else {
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='q';
				turn=false;
			}
		}

//*****************************************************************REY BLANCO***********************************************************************************************
	}else if (matriz[elegidonum][elegidoletra]=='r'){
		bool puede=false;
		if (movernumero==(elegidonum+1) && moverletra==(elegidoletra+3)){
			puede=true;
		}else if (movernumero==elegidonum && moverletra==(elegidoletra+3)){
			puede=true;
		}else if(movernumero==(elegidonum-1) && moverletra==(elegidoletra+3)){
			puede=true;
		}else if(movernumero==(elegidonum+1) && moverletra==elegidoletra){
			puede=true;
		}else if (movernumero==(elegidonum-1) && moverletra==(elegidoletra)){
			puede=true;
		}else if(movernumero==(elegidonum+1) && moverletra==(elegidoletra-3)){
			puede=true;
		}else if(movernumero==(elegidonum) && moverletra==(elegidoletra-3)){
			puede=true;
		}else if(movernumero==(elegidonum-1) && moverletra==(elegidoletra-3)){
			puede=true;
		}

		if (puede){
			if (matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='c' || matriz[movernumero][moverletra]=='t' ||
				matriz[movernumero][moverletra]=='a' || matriz[movernumero][moverletra]=='q'  ){
				printw("Ya existe una pieza amiga en esta poscicion");
			}else{
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='r';
				turn=false;	
			}

			
		}else{
			printw("movimiento invalido");
		}

	}

}



void mover2(int elegidoletra,int elegidonum,int moverletra, int movernumero ,char** matriz){
		initscr();
		int distancia=distancias(elegidoletra,elegidonum,moverletra,movernumero);
//************************************************************* PEONES NEGROS **********************************************************************************************
	if (matriz[elegidonum][elegidoletra]=='P'){
		if(elegidonum==2  && elegidoletra==moverletra){
		
			if(distancia==2){
				//////////////////////////////////////////

				
				if (matriz[elegidonum+1][elegidoletra]=='P' || matriz[elegidonum+1][elegidoletra]=='T' || matriz[elegidonum+1][elegidoletra]=='C' ||
				   	matriz[elegidonum+1][elegidoletra]=='A' || matriz[elegidonum+1][elegidoletra]=='R' || matriz[elegidonum+1][elegidoletra]=='Q'    ){
						printw ("pieza amiga, bloquea el paso");

				}else if(matriz[elegidonum+1][elegidoletra]=='p' || matriz[elegidonum+1][elegidoletra]=='t' || matriz[elegidonum+1][elegidoletra]=='c' ||
				    matriz[elegidonum+1][elegidoletra]=='a' || matriz[elegidonum+1][elegidoletra]=='r' || matriz[elegidonum+1][elegidoletra]=='q'    ){
						printw ("pieza enemiga, bloquea el paso");
					 
				}


				if(matriz[movernumero][moverletra]=='P' || matriz[movernumero][moverletra]=='T' || matriz[movernumero][moverletra]=='C' ||
						matriz[movernumero][moverletra]=='A'  || matriz[movernumero][moverletra]=='R' ||matriz[movernumero][moverletra]=='Q'){
					printw("Ya existe una pieza amiga en esta pocicion");
				
				}else{
					matriz[elegidonum][elegidoletra]='_';
					matriz[movernumero][moverletra]='P';
					turn=true;
				}



			
			}else if (distancia==1){
				if(matriz[movernumero][moverletra]=='P' || matriz[movernumero][moverletra]=='T' || matriz[movernumero][moverletra]=='C' ||
					matriz[movernumero][moverletra]=='A'  || matriz[movernumero][moverletra]=='R' ||matriz[movernumero][moverletra]=='Q'){
						printw("Ya existe una pieza amiga en esta pocicion");
				}else if(matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='t' || matriz[movernumero][moverletra]=='c' ||
					matriz[movernumero][moverletra]=='a'  || matriz[movernumero][moverletra]=='r' ||matriz[movernumero][moverletra]=='q'){
						printw("no puede comer en linea recta");
				}else{
					matriz[elegidonum][elegidoletra]='_';
					matriz[movernumero][moverletra]='P';
					turn=true;
				}
			}



		}else if(elegidonum!=2 && distancia==1  && elegidoletra==moverletra){
			if (matriz[movernumero][moverletra]=='P' || matriz[movernumero][moverletra]=='T' || matriz[movernumero][moverletra]=='C' ||
					matriz[movernumero][moverletra]=='A'  || matriz[movernumero][moverletra]=='R' ||matriz[movernumero][moverletra]=='Q'){
				printw("Ya existe una pieza amiga en esta pocicion");	
			}else if(matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='t' || matriz[movernumero][moverletra]=='c' ||
					matriz[movernumero][moverletra]=='a'  || matriz[movernumero][moverletra]=='r' ||matriz[movernumero][moverletra]=='q'){
				printw("no puede comer en linea recta con PEONES");	
			}else {
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='P';
				turn=true;	
			}




		}else if(distancia==3  && elegidoletra != moverletra){
			if(matriz[movernumero][moverletra]=='P' || matriz[movernumero][moverletra]=='T' || matriz[movernumero][moverletra]=='C' ||
					matriz[movernumero][moverletra]=='A'  || matriz[movernumero][moverletra]=='R' ||matriz[movernumero][moverletra]=='Q'){
				printw("Ya existe una pieza amiga en esta pocicion");	
			}else{
				matriz[elegidonum][elegidoletra]='_';
					matriz[movernumero][moverletra]='P';
					turn=true;
			}
		}else {
			printw("movimiento invalido");
		}
	
//************************************************************* TORRES NEGRAS **********************************************************************************************

	}else if (matriz[elegidonum][elegidoletra]=='T'){
		bool puede=true;
		if (elegidoletra==moverletra && elegidonum!=movernumero){
			for (int j= elegidonum+1; j<movernumero; j++){
				if (matriz[j][elegidoletra]=='p' || matriz[j][elegidoletra]=='t' || matriz[j][elegidoletra]=='c' || 
					matriz[j][elegidoletra]=='a' ||matriz[j][elegidoletra]=='r' || matriz[j][elegidoletra]=='q' ){
					printw("paso bloqueado por pieza enemiga1");
					puede=false;
				
					break;
				}else if(matriz[j][elegidoletra]=='P' || matriz[j][elegidoletra]=='T' || matriz[j][elegidoletra]=='C' || 
					matriz[j][elegidoletra]=='A' ||matriz[j][elegidoletra]=='R' || matriz[j][elegidoletra]=='Q' ){
					printw("paso bloqueado por pieza amiga1");
					puede=false;
					break;
				}
			}
		}else if(elegidoletra!=moverletra && elegidonum==movernumero){

			if (elegidoletra<moverletra){
				
				
				for (int i = elegidoletra+3; i <moverletra; i++){
					if (matriz[elegidonum][i]=='p' || matriz[elegidonum][i]=='t' || matriz[elegidonum][i]=='c' || 
						matriz[elegidonum][i]=='a' || matriz[elegidonum][i]=='c' || matriz[elegidonum][i]=='q'){
						printw("paso bloqueado por pieza enemiga2");
						puede=false;
						break;	

					}else if(matriz[elegidonum][i]=='P' || matriz[elegidonum][i]=='T' || matriz[elegidonum][i]=='C' || 
						matriz[elegidonum][i]=='A' || matriz[elegidonum][i]=='R' || matriz[elegidonum][i]=='Q'){
						printw("paso bloqueado por amiga2");	
						puede=false;
						break;
					}

					i+=2;
				}
			}else{
				for (int i = elegidoletra-3; i <moverletra; i--){
					if (matriz[elegidonum][i]=='p' || matriz[elegidonum][i]=='t' || matriz[elegidonum][i]=='c' || 
						matriz[elegidonum][i]=='a' || matriz[elegidonum][i]=='c' || matriz[elegidonum][i]=='q'){
						printw("paso bloqueado por pieza enemiga2");
						puede=false;
						break;	

					}else if(matriz[elegidonum][i]=='P' || matriz[elegidonum][i]=='T' || matriz[elegidonum][i]=='C' || 
						matriz[elegidonum][i]=='A' || matriz[elegidonum][i]=='R' || matriz[elegidonum][i]=='Q'){
						printw("paso bloqueado por amiga2");	
						puede=false;
						break;
					}

					i-=2;
				}

			}
		}else if (elegidoletra!=elegidonum  && movernumero!=moverletra){
			puede=false;
		}
		if(puede){
			if (matriz[movernumero][moverletra]=='P' || matriz[movernumero][moverletra]=='T' || matriz[movernumero][moverletra]=='C' || 
				matriz[movernumero][moverletra]=='A' ||matriz[movernumero][moverletra]=='R' || matriz[movernumero][moverletra]=='Q' ){
				printw("ya existe una pieza amiga en esta poscicion");
			}else{
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='T';
				turn=false;
			}
		}else{
			printw("movimiento invalido");
		}

//************************************************************* CABALLOS NEGROS ********************************************************************************************
	}else if (matriz[elegidonum][elegidoletra]=='C'){
		bool puede=true;
		if (movernumero==(elegidonum+2)  &&  moverletra==(elegidoletra-3)){
			/*if (matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='p' ||
				matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='p' || matriz[movernumero][moverletra]=='p'  ){
				printw("Ya existe una pieza amiga en esta poscicion");
				puede=false;
			}*/
			puede=true;
		}else if (movernumero==(elegidonum+1) && moverletra==(elegidoletra-6)){
			puede=true;
		}else if(movernumero==(elegidonum+2) && moverletra==(elegidoletra+3)){
			puede=true;
		}else if(movernumero==(elegidonum+1) && moverletra==(elegidoletra+6)){
			puede=true;
		}else if(movernumero==(elegidonum-1) && moverletra==(elegidoletra-6)){
			puede=true;
		}else if(movernumero==(elegidonum-2) && moverletra==(elegidoletra-3)){
			puede=true;
		}else if (movernumero==(elegidonum-2) && moverletra==(elegidoletra+3)){
			puede=true;
		}else if (movernumero==(elegidonum-1) && moverletra==(elegidoletra+3)){
			puede=true;
		}else{
			puede=false;
		}

		if (puede){
			if (matriz[movernumero][moverletra]=='P' || matriz[movernumero][moverletra]=='C' || matriz[movernumero][moverletra]=='T' ||
				matriz[movernumero][moverletra]=='A' || matriz[movernumero][moverletra]=='R' || matriz[movernumero][moverletra]=='Q'  ){
				printw("Ya existe una pieza amiga en esta poscicion");
			}else{
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='C';
				turn=false;	
			}

			
		}else{
			printw("movimiento invalido");
		}

//************************************************************* ALFILES NEGROS *********************************************************************************************

	}else if (matriz[elegidonum][elegidoletra]=='A'){
		printw("elegidonum");
		addch(elegidonum+48);
		printw("            movernum");
		addch(movernumero+48);

		int valorletraelejida=(alfilnum(elegidoletra));
		int  valornumeroletramover=(alfilnum(moverletra));
		bool puede=true;



		if(abs(valorletraelejida-valornumeroletramover) && abs(elegidonum-movernumero)){
			puede=true;
			if (elegidoletra < moverletra && elegidonum>movernumero){
				int j=elegidoletra;
				for (int i = elegidonum-1; i >movernumero-1 ; --i){
					j-=3;
					if (matriz[elegidonum][elegidoletra]=='P' || matriz[elegidonum][elegidoletra]=='T' || matriz[elegidonum][elegidoletra]=='C' ||
						matriz[elegidonum][elegidoletra]=='A' || matriz[elegidonum][elegidoletra]=='R' || matriz[elegidonum][elegidoletra]=='Q'){
						turn=true;
						printw("pieza amiga en el camino 1");
						break;
					}else if(matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=true;
						printw("pieza enemiga en el camino 2" );
						break;
					}

				}
			}else if(elegidoletra < moverletra &&  elegidonum > movernumero){
				int j=elegidoletra;
				for (int i = elegidonum+1; i >movernumero-1 ; ++i){
					 j+=3;
					if (matriz[elegidonum][elegidoletra]=='P' || matriz[elegidonum][elegidoletra]=='T' || matriz[elegidonum][elegidoletra]=='C' ||
						matriz[elegidonum][elegidoletra]=='A' || matriz[elegidonum][elegidoletra]=='R' || matriz[elegidonum][elegidoletra]=='Q'){
						turn=true;
						printw("pieza amiga en el camino 3");
						break;
					}else if(matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=true;
						printw("pieza enemiga en el camino 4");
						break;
					}
				}		
			}else if(elegidoletra > moverletra  && elegidonum < movernumero){
				int j=elegidoletra;
				for (int i = elegidonum+1; i > movernumero-1; ++i){
					j+=3;
					if (matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='R' || matriz[elegidonum][j]=='R'){
						turn=true;
						printw("pieza amiga en el camino 5" );
						break;
					}else if(matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=true;
						printw("pieza enemiga en el camino");
						break;
					}
				}
			}else if(elegidoletra < moverletra  && elegidonum < movernumero){
				int j=elegidoletra;
				for (int i = elegidonum; i < movernumero+1; --i){
				 	j-=3;
				 	if (matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=true;
						printw("pieza amiga en el camino 6");
						break;
					}else if(matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=true;
						printw("pieza enemiga en el camino");
						break;
					}
				}
			}
		}else{
			printw("no se esta moviendo diagonalmente");
			puede=false;
		}


		if (puede){
			if(matriz[movernumero][moverletra]=='P' ||  matriz[movernumero][moverletra]=='T' || matriz[movernumero][moverletra]=='C' || 
			matriz[movernumero][moverletra]=='A' || matriz[movernumero][moverletra]=='R' || matriz[movernumero][moverletra]=='Q'){
				printw("Ya existe una pieza amiga en esa pocicion");
			}else {
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='A';
				turn=true;
			}
		}

//****************************************************************REINA NEGRA **********************************************************************************************

	}else if (matriz[elegidonum][elegidoletra]=='Q'){
		int valorletraelejida=(alfilnum(elegidoletra));
		int  valornumeroletramover=(alfilnum(moverletra));
		bool puede=true;



		if(abs(valorletraelejida-valornumeroletramover) && abs(elegidonum-movernumero)){
			puede=true;
			if (elegidoletra < moverletra && elegidonum>movernumero){
				int j=elegidoletra;
				for (int i = elegidonum-1; i >movernumero-1 ; --i){
					j-=3;
					if (matriz[elegidonum][elegidoletra]=='P' || matriz[elegidonum][elegidoletra]=='T' || matriz[elegidonum][elegidoletra]=='C' ||
						matriz[elegidonum][elegidoletra]=='A' || matriz[elegidonum][elegidoletra]=='R' || matriz[elegidonum][elegidoletra]=='Q'){
						turn=false;
						printw("pieza amiga en el camino");
						break;
					}else if(matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=false;
						printw("pieza enemiga en el camino" );
						break;
					}

				}
			}else if(elegidoletra < moverletra &&  elegidonum > movernumero){
				int j=elegidoletra;
				for (int i = elegidonum+1; i >movernumero-1 ; ++i){
					 j+=3;
					if (matriz[elegidonum][elegidoletra]=='P' || matriz[elegidonum][elegidoletra]=='T' || matriz[elegidonum][elegidoletra]=='C' ||
						matriz[elegidonum][elegidoletra]=='A' || matriz[elegidonum][elegidoletra]=='R' || matriz[elegidonum][elegidoletra]=='Q'){
						turn=false;
						printw("pieza amiga en el camino");
						break;
					}else if(matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=false;
						printw("pieza enemiga en el camino 4");
						break;
					}
				}		
			}else if(elegidoletra > moverletra  && elegidonum < movernumero){
				int j=elegidoletra;
				for (int i = elegidonum+1; i > movernumero-1; ++i){
					j+=3;
					if (matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=false;
						printw("pieza amiga en el camino" );
						break;
					}else if(matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=false;
						printw("pieza enemiga en el camino");
						break;
					}
				}
			}else if(elegidoletra < moverletra  && elegidonum < movernumero){
				int j=elegidoletra;
				for (int i = elegidonum; i < movernumero+1; --i){
				 	j-=3;
				 	if (matriz[elegidonum][j]=='P' || matriz[elegidonum][j]=='T' || matriz[elegidonum][j]=='C' ||
						matriz[elegidonum][j]=='A' || matriz[elegidonum][j]=='Q' || matriz[elegidonum][j]=='R'){
						turn=false;
						printw("pieza amiga en el camino");
						break;
					}else if(matriz[elegidonum][j]=='p' || matriz[elegidonum][j]=='t' || matriz[elegidonum][j]=='c' ||
						matriz[elegidonum][j]=='a' || matriz[elegidonum][j]=='q' || matriz[elegidonum][j]=='r'){
						turn=false;
						printw("pieza enemiga en el camino");
						break;
					}
				}
			}
		}else if (elegidoletra==moverletra && elegidonum!=movernumero){
			for (int j= elegidonum+1; j<movernumero; j++){
				if (matriz[j][elegidoletra]=='p' || matriz[j][elegidoletra]=='t' || matriz[j][elegidoletra]=='c' || 
					matriz[j][elegidoletra]=='a' ||matriz[j][elegidoletra]=='r' || matriz[j][elegidoletra]=='q' ){
					printw("paso bloqueado por pieza enemiga");
					puede=false;
				
					break;
				}else if(matriz[j][elegidoletra]=='P' || matriz[j][elegidoletra]=='T' || matriz[j][elegidoletra]=='C' || 
					matriz[j][elegidoletra]=='A' ||matriz[j][elegidoletra]=='R' || matriz[j][elegidoletra]=='Q' ){
					printw("paso bloqueado por pieza amiga");
					puede=false;
					break;
				}
			}
		}else if(elegidoletra!=moverletra && elegidonum==movernumero){

			if (elegidoletra<moverletra){
				
				
				for (int i = elegidoletra+3; i <moverletra; i++){
					if (matriz[elegidonum][i]=='p' || matriz[elegidonum][i]=='t' || matriz[elegidonum][i]=='c' || 
						matriz[elegidonum][i]=='a' || matriz[elegidonum][i]=='c' || matriz[elegidonum][i]=='q'){
						printw("paso bloqueado por pieza enemiga");
						puede=false;
						break;	

					}else if(matriz[elegidonum][i]=='P' || matriz[elegidonum][i]=='T' || matriz[elegidonum][i]=='C' || 
						matriz[elegidonum][i]=='A' || matriz[elegidonum][i]=='R' || matriz[elegidonum][i]=='Q'){
						printw("paso bloqueado por amiga");	
						puede=false;
						break;
					}

					i+=2;
				}
			}else{
				for (int i = elegidoletra-3; i <moverletra; i--){
					if (matriz[elegidonum][i]=='p' || matriz[elegidonum][i]=='t' || matriz[elegidonum][i]=='c' || 
						matriz[elegidonum][i]=='a' || matriz[elegidonum][i]=='c' || matriz[elegidonum][i]=='q'){
						printw("paso bloqueado por pieza enemiga");
						puede=false;
						break;	

					}else if(matriz[elegidonum][i]=='P' || matriz[elegidonum][i]=='T' || matriz[elegidonum][i]=='C' || 
						matriz[elegidonum][i]=='A' || matriz[elegidonum][i]=='R' || matriz[elegidonum][i]=='Q'){
						printw("paso bloqueado por amiga");	
						puede=false;
						break;
					}

					i-=2;
				}

			}
		}else if (elegidoletra!=elegidonum  && movernumero!=moverletra){
			puede=false;
		}
		
		if (puede){
			if(matriz[movernumero][moverletra]=='P' ||  matriz[movernumero][moverletra]=='T' || matriz[movernumero][moverletra]=='C' || 
			matriz[movernumero][moverletra]=='A' || matriz[movernumero][moverletra]=='R' || matriz[movernumero][moverletra]=='Q'){
				printw("Ya existe una pieza amiga en esa pocicion");
			}else {
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='Q';
				turn=false;
			}
		}

//*************************************************************REY BLANCO***************************************************************************************************
	}else if (matriz[elegidonum][elegidoletra]=='R'){
		bool puede=false;
		if (movernumero==(elegidonum+1) && moverletra==(elegidoletra+3)){
			puede=true;
		}else if (movernumero==elegidonum && moverletra==(elegidoletra+3)){
			puede=true;
		}else if(movernumero==(elegidonum-1) && moverletra==(elegidoletra+3)){
			puede=true;
		}else if(movernumero==(elegidonum+1) && moverletra==elegidoletra){
			puede=true;
		}else if (movernumero==(elegidonum-1) && moverletra==(elegidoletra)){
			puede=true;
		}else if(movernumero==(elegidonum+1) && moverletra==(elegidoletra-3)){
			puede=true;
		}else if(movernumero==(elegidonum) && moverletra==(elegidoletra-3)){
			puede=true;
		}else if(movernumero==(elegidonum-1) && moverletra==(elegidoletra-3)){
			puede=true;
		}

		if (puede){
			if (matriz[movernumero][moverletra]=='P' || matriz[movernumero][moverletra]=='C' || matriz[movernumero][moverletra]=='T' ||
				matriz[movernumero][moverletra]=='A' || matriz[movernumero][moverletra]=='Q'  ){
				printw("Ya existe una pieza amiga en esta poscicion");
			}else{
				matriz[elegidonum][elegidoletra]='_';
				matriz[movernumero][moverletra]='R';
				turn=true;
			}

			
		}else{
			printw("movimiento invalido");
		}

	}

	
}


int alfilnum(int numero){
	int valornuevo;
	if (numero==2){
		valornuevo=1;
	}else if(numero==5){
		valornuevo=2;
	}else if(numero==8){
		valornuevo=3;
	}else if(numero==11){
		valornuevo=4;
	}else if(numero==14){
		valornuevo=5;
	}else if(numero==17){
		valornuevo=6;
	}else if(numero==20){
		valornuevo=7;
	}else if(numero==23){
		valornuevo=8;
	}

	return valornuevo;
}

int  distancias(int letra1, int numero1, int letra2,int numero2){
	int dis;
	//move(0,0);
	//cout<<"LETRA 1->"<<letra1<<"    numero1->"<<numero1<<"  letra2->"<<letra2<<"  numero2->"<<numero2<<endl;
	if(letra1==letra2 && abs(numero1-numero2)==2){
		return 2;
	}else if(letra1==letra2 && abs(numero1-numero2)==1){
		return 1;
	}else if(letra1!=letra2){
		if(abs(letra1-letra2)==3 && abs(numero1-numero2)==1){
			return 3;
		}
	}else{
		return -1;
	}
}

void inicializarmatriz(char** matriz,int size,int column){
	for (int i = 0; i < column; i++){
		matriz[i]=new char[size];
	}

	for (int i = 0; i <size; i++){
		for (int j = 0; j<column; j++){
			matriz[i][j]='_';
		}
	}

	 


	///Piezas Blancas son las minusculas
	
	matriz[1][2]='t';
	matriz[1][5]='c';
	matriz[1][8]='a';
	matriz[1][11]='r';
	matriz[1][14]='q';
	matriz[1][17]='a';
	matriz[1][20]='c';
	matriz[1][23]='t';

	matriz[2][2]='p';
	matriz[2][5]='p';
	matriz[2][8]='p';
	matriz[2][11]='p';
	matriz[2][14]='p';
	matriz[2][17]='p';
	matriz[2][20]='p';
	matriz[2][23]='p';

	//Piezas negras Son las Mayusculas.
	matriz[8][2]='T';
	matriz[8][5]='C';
	matriz[8][8]='A';
	matriz[8][11]='Q';
	matriz[8][14]='R';
	matriz[8][17]='A';
	matriz[8][20]='C';
	matriz[8][23]='T';

	matriz[7][2]='P';
	matriz[7][5]='P';
	matriz[7][8]='P';
	matriz[7][11]='P';
	matriz[7][14]='P';
	matriz[7][17]='P';
	matriz[7][20]='P';
	matriz[7][23]='P';




	matriz[0][0]=32;//espacios
	matriz[1][0]=49;//numero.
	matriz[2][0]=50;
	matriz[3][0]=51;
	matriz[4][0]=52;
	matriz[5][0]=53;
	matriz[6][0]=54;
	matriz[7][0]=55;
	matriz[8][0]=56;

	matriz[0][2]=65;//A
	matriz[0][5]=66;
	matriz[0][8]=67;
	matriz[0][11]=68;
	matriz[0][14]=69;
	matriz[0][17]=70;
	matriz[0][20]=71;
	matriz[0][23]=72;




	
} 

void imprimir(char** matriz, int size, int column){
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLACK);///cuadros azules, letras blancas
 	init_pair(2,COLOR_WHITE,COLOR_YELLOW);//cuadros negros con letras blancas
 	init_pair(3,COLOR_YELLOW,COLOR_BLACK);
 	init_pair(4,COLOR_RED,COLOR_BLACK);

 	attron(COLOR_PAIR(4));
 	for (int j = 0; j< column-1; j++){
 		addch(matriz[0][j]);
 	}
 
 	for (int j = 0; j< size; ++j){
 		addch(matriz[j][0]);	
 		printw("\n");	 
 	}

 	
 	attroff(COLOR_PAIR(3));
	
	
 	for (int i = 1; i < size; i++){

 		move(10+i,1);
		if ((i%2) == 1){//i impar 
				
			for (int j = 1; j< column; j++){
				if (j%2==0){ //j par
					
					for (int k= 0; k < 3; k++){
						attron(COLOR_PAIR(1));
					 	addch(matriz [i][j+k]);
					}
					attroff(COLOR_PAIR(1));
					j+=2;
				}else if (j%2 ==1){//j es impar
				 		
					for (int k = 0; k <3; k++){
						
						attron(COLOR_PAIR(2));
					 	addch(matriz [i][j+k]);
					}
					attroff(COLOR_PAIR(2));
					j+=2;
				}
			}
			printw("\n");
		}else{
			for (int j = 1; j< column; j++){
				if (j%2==1){ //j par
						
					for (int k= 0; k < 3; k++){
						attron(COLOR_PAIR(1));
						addch(matriz [i][j+k]);
					}
					attroff(COLOR_PAIR(1));
					j+=2;
				}else if (j%2 ==0){//j es impar
						
					for (int k = 0; k <3; k++){
						
						attron(COLOR_PAIR(2));
					 	addch(matriz [i][j+k]);
					}
					attroff(COLOR_PAIR(2));
					j+=2;
				}
			}
			printw("\n");

		}
	}

 	
}

int cord_pieza(char number[]){
	int indiceletra1;

	if (number[0]=='A'){
  	  indiceletra1=2;
	}else if (number[0]=='B'){
		indiceletra1=5;
	}else if (number[0]=='C'){
		indiceletra1=8;
	}else if (number[0]=='D'){
		indiceletra1=11;
	}else if (number[0]=='E'){
		indiceletra1=14;
	}else if (number[0]=='F'){
		indiceletra1=17;
	}else if (number[0]=='G'){
		indiceletra1=20;
	}else if (number[0]=='H'){
		indiceletra1=23;
	}	
	
	return indiceletra1;


}

int cord_piezamov(char number[]){
	int indiceletra1;
	if (number[3]=='A'){
  	  indiceletra1=2;
	}else if (number[3]=='B'){
		indiceletra1=5;
	}else if (number[3]=='C'){
		indiceletra1=8;
	}else if (number[3]=='D'){
		indiceletra1=11;
	}else if (number[3]=='E'){
		indiceletra1=14;
	}else if (number[3]=='F'){
		indiceletra1=17;
	}else if (number[3]=='G'){
		indiceletra1=20;
	}else if (number[3]=='H'){
		indiceletra1=23;
	}
	

	return indiceletra1;
}

int cordnumerica1(char num[]){
	int numero;

	if(num[1]=='1'){
		numero=1;
	}else if (num[1]=='2' ){
		numero=2;
	
	}else if (num[1]=='3' ){
		numero=3;
	
	}else if (num[1]=='4' ){
		numero=4;
	}else if (num[1]=='5' ){
		numero=5;
	}else if (num[1]=='6' ){
		numero=6;
	}else if (num[1]=='7' ){
		numero=7;
	}else if (num[1]=='8' ){
		numero=8;
	}

	return numero;
}


int cordnumerica2(char num[]){
	int numero;

	if(num[4]=='1'){
		numero=1;
	}else if(num[4]=='2'){
		numero=2;
	}else if(num[4]=='3'){
		numero=3;
	}else if(num[4]=='4'){
		numero=4;
	}else if(num[4]=='5'){
		numero=5;
	}else if(num[4]=='6'){
		numero=6;
	}else if(num[4]=='7'){
		numero=7;
	}else if(num[4]=='8'){
		numero=8;
	}


	return numero;

}

 

