#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct {
	int numCuen;
	char nomYap[25];
	float saldo;
}saldante;
typedef struct{
	int numCuen;
	int mes;
	int dia;
	int codOpe;
	float imp;
}movimientos;
//funcion llevar a memoria:
int  memoria(saldante s[] ){
	saldante aux;
	int i=0;
	FILE *a;
	a= fopen("eje7_saldantes.dat", "rb");
	fread(&aux, sizeof(aux),1, a);
	while(!feof(a)){
		s[i]=aux;
		i++;
		fread(&aux, sizeof(aux),1, a);
	}
	return i;
	fclose(a);
}
int buscar(saldante s[], int cant, int e){
	int pos=-1, i=0;
	while(pos==-1 && i<cant){
		if(s[i].numCuen == e){
			pos= i;
			return pos;
		}
		else{
			i++;
		}
	}
	return pos;
}
int main(){
	//variables;
	int x=0;
	//structs:
	saldante s[100];
	movimientos m;
	//llevo a memoria:
	x= 	memoria(s);
	//punto a)
	printf("N\tSaldo");
	for(int i= 0; i<x; i++){
		printf("\n%d\t%f", s[i].numCuen, s[i].saldo);
	}
	//lectura de archivo
	FILE *a;
	a= fopen("eje7_movimientos.dat","rb");
	fread(&m,sizeof(m),1,a);
	printf("\n***********************\n");
	int guardar=0;
	int tran[300]={0};
	int p=0;
	while(!feof(a)){
		
		int pos= buscar(s,100,m.numCuen);
		if(m.codOpe==1){
			s[pos].saldo +=  m.imp;
		}
		else if (m.codOpe == 2){
				s[pos].saldo -=  m.imp;
		}
		//
		
		if(s[p].numCuen == m.numCuen){
			p++;
		}
		else{
			guardar= p;	
		}
		//algortimo e)
		tran[m.numCuen-1]++;
		fread(&m,sizeof(m),1,a);
	}
	fclose(a);
	//algoritmo b)
	FILE * ar;
	ar=fopen("eje7_saldantes_act.dat" , "wb");
	fwrite(&s,sizeof(s),1,ar);
	fclose(a);
	//algoritmo c)
	printf("\nLa cuenta: %d no realizo movimientos, su saldo es %.2f", s[p].numCuen, s[p].saldo);
		
	
	for(int n=0; n<100;n++){
		if(tran[n] >5){
			printf("\nEL codigo %d realizo mas de 5 ventas", s[n].numCuen);
		}
	}

	
	
	return 0;
}
