#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	int numVendedor;
	int numArt;
	float impor;
}ven;
typedef struct {
	int numVendedor;
	char nomYape[25];
}vendedor;
typedef struct {
	int numCli; // 1 a 1000  0rdenado
	char razon[30];
	int numVen; // 1 a 5
	int numArt; // 1 a 20
	int cantVen;
	float precio;
}clientes;
//funcion validar:
int validar(int min, int max){
	int dato;
	do{
		scanf("%d",&dato);
	}while(dato<min || dato>max);
	return dato;
}
//funcion llevar a memoria
void memoria(ven v[]){
	int i=0;
	FILE * a;
	ven aux;
	a= fopen("ven_ven.dat","rb");
	if(a==NULL){printf("error de archivo");}
	fread(&aux,sizeof(aux),1,a);
	while(!feof(a)){
		v[i]= aux;
		i++;
		fread(&aux,sizeof(aux),1,a);
	}
	fclose(a);
}
//funcion buscar
int buscar(ven v[], int cant, int e){
	int pos=-1, i=0;
	while(pos==-1 && i<cant){
		if(v[i].numVendedor == e){
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
	//variables
	int i=0;
	int pos=0;
	int vendedor[5]={0};
	//structs
	clientes cli[1000];
	ven v[100];
	//grabar archivo memoria:
	memoria(v);
	//carga por teclado:
	printf("ingrese un numero de cliente:");
	cli[i].numCli= validar(0,1000);
	//carga
	while(cli[i].numCli !=0){
		printf("\nIngrese Razon social:");
		fflush(stdin);
		gets(cli[i].razon);
		//
		printf("\nNumero de vendedor:");
		cli[i].numVen= validar(1,5);
		//
		printf("\nNumero de articulo:");
		cli[i].numArt= validar(1,20);
		//
		printf("\nIngrese cantidad vendida:");
		scanf("%d",& cli[i].cantVen);
		//
		printf("\nIngrese precio");
		scanf("%f",& cli[i].precio);
		//alpogritmo a)
		 pos= buscar(v,100, cli[i].numVen);
		 v[pos].impor+=(float) (cli[i].cantVen * cli[i].precio); 
		 // algortimo c)
		 vendedor[cli[i].numVen -1 ]++;
		i++;
		printf("\ningrese un numero de cliente:");
		cli[i].numCli= validar(0,1000);
	}
	int x= 0; 
	//alogritmo b)
	while(x<i){
		float acumT=0;
		float im=0;
		int clin= cli[x].numCli;
		printf("\nRazon Social: %s", cli[x].razon);
		printf("\nART\tIMPORTE");
		while(x<i && clin== cli[x].numCli){
			float var= (cli[x].cantVen * cli[x].precio);
			im= var;
			acumT+= im;
			printf("\n%d\t%f", cli[x].numArt, im);
			x++;
		}
		printf("\nTOTAL: \t%f", acumT);
	}

	//algoritmo c)
	for(int z=0; z<5; z++){
		if(vendedor[z]==0){
			printf("\nEL VENDEDOR %d hizo %d ", z+1, vendedor[z]);
		}
	}
	
	//algortimo d)
	FILE * act;
	act= fopen("ven_ven_act.dat","wb");
	if(v==NULL){printf("error");}
	fwrite(&v,sizeof(v),1,act);
	fclose(act);
	// algrotimo e)
	int max, ven;
	for(int n= 0; n<5; n++){
		if(vendedor[n]> max)
		{
			max= vendedor[n];
			ven= n;
		}
	}
	printf("\nEl vendedor que mas ventas realizo es %d", ven+1);
}
