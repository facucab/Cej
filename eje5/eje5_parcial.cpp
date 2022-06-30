#include<stdio.h>
#include<string.h>
typedef struct {
	int numPro;
	int stock;
	float precio;
}productos;
typedef struct {
	int ncli; //1a 999
	int mes;
	int npro; // 8 cifras
	int cantVen;
}ventas;
int carga(ventas v[]){
	int i=0;
	printf("Ingrese un numero de cliente : ");
	scanf("%d",& v[i].ncli);
	while(v[i].ncli !=0){
		printf("\nIngrese mes: ");
		scanf("%d", & v[i].mes);
		// 
		printf("\nIngrese Numero producto: ");
		scanf("%d",&v[i].npro);
		//
		printf("\nCANTIDAD DE VENTAS:");
		scanf("%d",&v[i].cantVen);
		//
		i++;
		//
		printf("\nIngrese un numero de cliente:");
		scanf("%d", &v[i].ncli);
	}
	return i;
}
void ordenar (ventas v[], int cant){
	int i=0;
	ventas aux;
	int sen= 0; 
	while(sen==0){
		sen=1;
		for(int x=0; x<cant; x++){
			if(v[x].ncli < v[x+1].ncli){
				aux= v[x];
				v[x]= v[x+1];
				v[x+1]= aux;
				
			}
		}
	}
	
}
int buscar(productos p[], int cant , int e){
	int pos=-1, i=0;
	while(pos==-1 && i<cant){
		if(p[i].numPro == e){
			pos=i;
			return pos;
		}
		else{
			i++;
		}
	}
	return pos;
}
int main(){
	//variables:
	int sen=0;
	int mayor=0, NombreMayor=0;
	//structs
	ventas v[800];
	ventas aux;
	//funcion carga:
	 int x= carga(v);
	//
	ordenar(v,800);
	//llevo a  memoria:
	productos p [800];
	productos aux2; 
	FILE *a; 
	int m=0;
	a= fopen("eje5_productos.dat", "rb");
	fread(&aux2, sizeof(aux2),1,a);
	while(!feof(a)){
		p[m]= aux2;
		m++;
		fread(&aux2, sizeof(aux2),1,a);
	}
	//corte de  control: 
	int i=0; 
	int compras[12];
	while(i<x){
	 	int cliAUX= v[i].ncli;
	 	int mes=0;
	 	while(i<x && cliAUX== v[i].ncli){
	 		mes++;
	 		int pos = buscar(p,800,v[i].npro);
			compras[v[i].mes- 1] += ( p[ pos].precio * v[i].cantVen);
			//alogritmo b)
			
	 		i++;
		 }
		 	if(mes>=3){
		 		printf("\nCODIGO\t\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\t12");
	 			printf("\n%d", cliAUX);
	 			for(int r=0;r<12;r++){
	 				printf("\t%d", compras[r]);
				 }
			 }
	 }
	i=0;
	while(i<x){
		int artAUX= v[i].npro;
		float acumT=0;
		int contVen=0;
		while(i<x && artAUX== v[i].npro){
			int pos = buscar(p,800,v[i].npro);
			acumT+= p[pos].precio * v[i].cantVen;
			contVen+= v[i].cantVen;
			p[pos].stock= p[pos].stock - v[i].cantVen;
			i++;
		}
		//punto b)
		if(acumT==0){
			printf("\nEl articulo: %d no posee importe", artAUX);
		}
		//c
		if(sen==0 || contVen>mayor ){
			sen=1;
			mayor= contVen;
			NombreMayor= artAUX;
		}
	}
	printf("\nEl producto con mayor unidades es: %d  con:  %d", NombreMayor,mayor);
	
	//algoritmo d)
	FILE * archN;
	archN= fopen("PROD_ACT.dat", "wb");
	fwrite(&p,sizeof(p),1,archN);
	fclose(archN);
}





































/*#include<stdio.h>
#include<string.h>
typedef struct {
	int numPro;
	int stock;
	float precio;
}productos;
int main(){
	FILE *a;
	a= fopen("eje5_productos.dat","wb");
	if(a==NULL){printf("error");}
	productos p[5];
	for(int i= 0; i<5; i++){
		printf("\nNUmero de producto:");
		scanf("%d",&p[i].numPro);
		//
		printf("\nSTOCK:");
		scanf("%d",&p[i].stock);
		//
		printf("\nPrecio: ");
		scanf("%f", & p[i].precio);
	}
	fwrite(&p, sizeof(p),1,a);
	fclose(a);
	
}*/
