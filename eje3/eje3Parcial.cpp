#include<stdio.h>
#include<string.h>
typedef struct{
	int cod; 
	char desc[30];
	int rubro; 
	float precio;
	int puntoP; 
	int stock;
}stock;
typedef struct{
	int cod;
	int cantPed;
	int nCli; 
	int numPed; 
	int fecha; 
}pedidos;
//funcion llevar a  memoria 
void carga(stock s[]){
	FILE*a;
	int i=0;
	stock aux;
	a= fopen("Ej3_stock.dat","rb");
	fread(&aux,sizeof(aux),1,a);
	while(!feof(a)){
		s[i]= aux;
		i++;
		fread(&aux,sizeof(aux),1,a);
	}
	fclose(a);
}
int buscar(stock s[] , int e, int cant){
	int pos=-1;
	int i=0;
	while(pos==-1 && i<cant){
		if(s[i].cod == e){
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
	//variables:
	 int prodRepo=0;
	 int fecha[31]={0};
	//estrucutras
	stock s[600];
	pedidos p;
	//funcion para llevar a memoria.
	carga(s);
	//FILES
	FILE *arch;
	arch= fopen("Ej3_pedidos.dat","rb");
	fread(&p,sizeof(p),1,arch);
	while(!feof(arch)){
		int codAUX, cantPed=0;
		float acumMonto=0;
		codAUX= p.cod;
		int pos=0;
		while(!feof(arch) && codAUX== p.cod){
			//alogritmo a)
			pos= buscar(s,p.cod,600);
			cantPed+= p.cantPed;
			acumMonto+= ( s[pos].precio * p.cantPed);
			//algoritmo b)
			s[pos].stock = s[pos].stock - p.cantPed;
			if(s[pos].stock< s[pos].puntoP){
				printf("\nel producto %d debe reponerse", codAUX);
				prodRepo++;
			}
			//alogritmo d)
			fecha[p.fecha-1]+=p.cantPed;
			//ALOGRITMO
			fread(&p,sizeof(p),1,arch);
		}
		//muestra a)
		printf("\nEl producto con codigo %d, pidio la cantidad de: %d con un monto de %.2f ", codAUX, cantPed, acumMonto);
	}
		//muestra c)
		printf("\nLa cantidad de productos que se debe reponer es de %d",prodRepo);
		//muestra d)
		printf("\nFECHA\tCANTIDAD");
		for(int i=0; i<31;i++){
			printf("\n%d\t%d",i+1,fecha[i]);
		}
}
/*

*/
