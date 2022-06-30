#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	int numArt;
	float Precio;
}articulos;
typedef struct { 
	int numVen;
	int numPro;
}provincias;
typedef struct{
	int numVen;
	int mes;
	int nArt;
	int unVen;
}ventas;
//funcion para llevor a memoria articulos:
void art(articulos a[]){
	int i=0;
	articulos aux;
	FILE *ar;
	ar= fopen("eje8_articulos.dat","rb");
	fread(&aux,sizeof(aux),1,ar);
	while(!feof(ar)){
		a[i]=aux;
		i++;
		fread(&aux,sizeof(aux),1,ar);
	}
	fclose(ar);
}
//funcion para llevar a memoria provincia:
void prov(provincias p[]){
	provincias aux;
	int i=0;
	FILE *a;
	a= fopen("eje8_provincias.dat","rb");
	if(a==NULL){
		printf("error de archivo");
		system("pause");
		exit(1);
	}
	fread(&aux,sizeof(aux),1,a);
	while(!feof(a)){
		p[i]=aux;
		i++;
		fread(&aux,sizeof(aux),1,a);
	}
	fclose(a);
}
//funcion buscar:
int buscar(provincias p[], int cant, int e){
	int pos=-1,i=0;
	while(pos==-1 && i<cant){
		if(p[i].numVen == e){
			pos= i;
			return pos;
		}
		else{
			i++;
		}
	}
	return pos;
}
int buscar2(articulos a[], int cant, int e){
	int pos=-1,i=0;
	while(pos==-1 && i<cant){
		if(a[i].numArt == e){
			pos= i;
			return pos;
		}
		else{
			i++;
		}
	}
	return pos;
}
//validar: 
int validar(int min, int max){
	int dato;
	do{
		scanf("%d",& dato);
	}while(dato<min || dato>max);
	return dato;
}
void ordenar(int a[],int cant,int b[]){
	int sen=0, i=0;
	int aux1=0,aux2=0;
	while(sen==0){
		sen=1;
		for(i=0;i<cant;i++){
			if(a[i]<a[i+1]){
				aux1=a[i];
				a[i]=a[i+1];
				a[i+1]=aux1;
				
				aux2=b[i];
				b[i]=b[i+1];
				b[i+1]=aux2;
				
				sen=0;
			}
		}
	}
}

int main(){
	//variables:
	int i=0;
	int Mprov[24][13]={0};
	int vendedor[30][13]={0};
	int pos=0, pos2=0;
	int  meses[12]={0};
	int indiceMes[12]={0};
	int mayorUni[30]={0};
	//structs:
	articulos a[300];
	provincias p[30];
	ventas dato[100];
	//funciones de memoria:
	art(a);
	prov(p);
	//
	
	
	//ingresar los datos:
	printf("\nIngrese numero de vendedor:");
	dato[i].numVen= validar(0,30);
	while(dato[i].numVen !=0){
		printf("\nIngrese mes:");
		dato[i].mes= validar(0,13);
		printf("\nIngrese Numero de articulo:");
		dato[i].nArt= validar(999,8001);
		printf("\nUnidades vendias:");
		dato[i].unVen= validar(0,101);
	
		//algrotimo a)
		pos= buscar(p,30,dato[i].numVen);
		pos2= buscar2(a,300, dato[i].nArt);
		
		
		Mprov[p[pos].numPro-1][dato[i].mes]+= (dato[i].unVen *   a[pos2].Precio);
		//
		vendedor[dato[i].numVen][0]= dato[i].numVen;
		vendedor[dato[i].numVen][dato[i].mes]+= dato[i].unVen;
		//algrotimo c)
		meses[dato[i].mes -1 ]+= (dato[i].unVen * a[pos2].Precio);
		indiceMes[ dato[i].mes-1]= dato[i].mes;
		//algroitmo d)
		mayorUni[dato[i].numVen -1]+= dato[i].unVen;
		i++;
		printf("\nIngrese Numero de vendedor:");
		dato[i].numVen= validar(0,30);
	}
	//muestra a)
	printf("\nPROV\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12");
	for(int z=0; z<24; z++){
		printf("\n%d",z+1);
		for(int m=1; m<13; m++){
			printf("\t%d", Mprov[z][m]);
		}
	}
	//muestra b)
		int cont=0;
		for(int z=1; z<30; z++){
		for(int m=1; m<13; m++){
			if(vendedor[z][m]==0 || cont>=3){
				cont++;
			}
			else{
				cont=0;
			}
		}
		if(cont>=3 && vendedor[z][0]!=0){
			printf("\nEl vendedor %d no hizo ventas en 3 meses consecutivos" ,vendedor[z][0]);
		}
	}
	//muestra c)
	ordenar(meses,11,indiceMes);
	for(int t=0; t<12;t++){
		printf("\nmes:%d\t%d", indiceMes[t], meses[t]);
	}
	//muestra d)
	int max= mayorUni[0];
	int NameMAX=0;
	for(int m=1;m<29;m++){
		if(mayorUni[m]> max){
			max= mayorUni[m];
			NameMAX= m;
		}
	}
	printf("\nEL maximo es %d con %d", NameMAX +1 , max);
}
