#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <windows.h> 
#include <string> 
#include <iostream> 
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std ;
//Analizador lexico
char * reservadas [4] = {"inicio" ,"final" , "if" , "integer"}; 
char *s1[21] = {";","=","<",">","{","}","[","]","+","-","*","/","!","(",")","#","&",":","\n", " ","'"};
char *s2[15] = {"+","-","*","/","=","<",">",";","!","#","&","\n"," ", "(",")"};
char *s3[2] = {"\n"," "};//Letras, digitos
char *s4[4] = {"\n"," ",")","'"};//Letras, digitos
char *s5[9] = {"\n"," ","{","+","-","*","/","(",";"};
char *s6[2] = {"\n"," "};
char *s7[3] = {"\n"," ", "("};//Letras, digitos
char *s8[4] = {"\n"," ",";",")"};//Letras, digitos
char *s9[3] = {"\n"," ","}"};//Letras
char *s10[5] = {"\n"," ","'", "]","="}; //Letras, digitos
int verificar = 0;
int cont=0;
void lexico();
bool verificarReservada ( char palabra [ ] );
bool verificarSeparador(string comp);
///////////////////////////////////////////////////

struct reglasAccion {
  int estado;
  string var;
  string cond;
  int num;
}lista[100]={{0, "inicio", "s", 2}, {1, "$", "aceptar", NULL}, {2, "integer", "s", 4}, {3, "id", "s", 9},{3, "if", "s", 8}, {4, "id", "s", 9}, {5, "final", "s", 12}, 
{6, "final", "r", 6}, {6, "id", "s", 9}, {6, "if", "s", 8}, {6, "}","r",6}, {7,"=","s",14},{8,"(","s",15},{9,";","r",5},{9,",","r",5},
{9,"=","r",5},{10,";","s",16},{11,";","r",3},{11,",","s",17},{12,"$","r",1},{13,"final","r",7},{13,"}","r",7},{14,"id","s",22},{14,"(","s",21},
{15,"id","s",22},{15,"(","s",21},{16,"id","r",2},{16,"if","r",2},{17,"id","s",9},{18,";","s",26},{18,"+","s",27},{19,";","r",13},{19,")","r",13},
{19,"<","r",13},{19,">","r",13},{19,"+","r",13},{19,"*","s",28},{20,";","r",15},{20,")","r",15},{20,"<","r",15},{20,">","r",15},{20,"+","r",15},
{20,"*","r",15},{21,"id","s",22},{21,"(","s",21},{22,";","r",17},{22,")","r",17},{22,"<","r",17},{22,">","r",17},{22,"+","r",17},{22,"*","r",17},
{23,")","s",30},{24,"<","s",31},{24,">","s",32},{24,"+","s",27},{25,";","r",4},{26,"final","r",8},{26,"id","r",8},{26,"if","r",8},{26,"}","r",8},
{27,"id","s",22},{27,"(","s",21},{28,"id","s",22},{28,"(","s",21},{29,")","s",35},{29,"+","s",27},{30,"{","s",36},{31,"id","s",22},{31,"(","s",21},
{32,"id","s",22},{32,"(","s",21},{33,";","r",12},{33,")","r",12},{33,"<","r",12},{33,">","r",12},{33,"+","r",12},{33,"*","s",28},{34,";","r",14},
{34,")","r",14},{34,"<","r",14},{34,">","r",14},{34,"+","r",14},{34,"*","r",14},{35,";","r",16},{35,")","r",16},{35,"<","r",16},{35,">","r",16},
{35,"+","r",16},{35,"*","r",16},{36,"id","s",9},{36,"if","s",8},{37,")","r",10},{37,"+","s",27},{38,")","r",11},{38,"+","s",27},{39,"}","s",40},
{40,"final","r",9},{40,"id","r",9},{40,"if","r",9},{40,"}","r",9}};


struct gramatica{
	int id;
	string etiqueta;
	int numE;
}listaGramatica[18]={{0,"P'",0},{1,"P",4},{2,"DV", 3},{3,"LV",1},{4,"LV",3},{5,"UV",1},{6,"B",1},{7,"B",2},{8,"SENT",4},{9,"SENT",7},{10,"COND",3},{11,"COND",3},
{12,"E",3},{13,"E",1},{14,"T",3},{15,"T",1},{16,"F",3},{17,"F",1}};

struct reglasIr_A{
	int estado;
	string var;
	int num;
}listaIr_A[34]{{0,"P",1},{2,"DV",3},{3,"UV",7},{3,"B",5},{3,"SENT",6},{4,"LV",10},{4,"UV",11},{6,"UV",7},{6,"B",13},{6,"SENT",6},{14,"E",18},{14,"T",19},
{14,"F",20},{15,"COND",23},{15,"E",24},{15,"T",19},{15,"F",20},{17,"LV",25},{17,"UV",11},{21,"E",29},{21,"T",19},{21,"F",20},{27,"T",33},
{27,"F",20},{28,"F",34},{31,"E",37},{31,"T",19},{31,"F",20},{32,"E",38},{32,"T",19},{32,"F",20},{36,"UV",7},{36,"B",39},{36,"SENT",6}};

struct nodo{
    int nro;
    struct nodo *sgte;
};
 
typedef nodo *ptrPila;   // creando nodo tipo puntero( tipo de dato )


string arregloCadena[100];

int t=0;
int reducir =0;
string e="";
string accion(int s, string a);
int ir_A(int t, string A);
void push(ptrPila &p, int valor);
void mostrar_pila(ptrPila p);
int pop(ptrPila &p, int cantidad);
int resultado(string varT, int varN);
int obtener();

int main ( ) { 
	lexico();
			
	//Primer elemento de la pila
	ptrPila p = NULL;  
	push(p,0);
	//Hacer que a sea el primer simbolo de u$
	string a="";
	a = arregloCadena[0];
	int z=0;
	int s;
	while(1){
		cout<<"------------------------------ANALIZADOR SINTACTICO------------------------------"<<"\n";
		//Hacer que s sea el estado en la parte superior de la pila
    	ptrPila aux;
    	aux = p ;
    	s = aux->nro;
    	
    	if(accion(s,a)=="s"){
    		cout<<"\n\n";
    		cout<<"\t\t\t\tACCION["<<s<<","<<a<<"]   "<<e<<"->"<<t<<"\n\n";
    		//Meter t en la pila
			push(p,t);
			//Hacer que a sea el siguiente simbolo de entrada
			z++;	
			a = arregloCadena[z];
			mostrar_pila(p);
			cout<<"\n\t\t\t";
    		system("pause");
    		system("cls");
    		
		}else if(accion(s,a)=="r"){
			cout<<"\n\n";
			cout<<"\t\t\t\tACCION ["<<s<<","<<a<<"]   "<<e<<"->"<<t<<"\n\n";
			//Eliminar los B simbolos de la pila
			int eliminarT=listaGramatica[t].numE;
			cout<<"\t\t\t\tQuitando ("<<eliminarT<<") elementos\n\n";	
			pop(p,eliminarT);
			mostrar_pila(p);
			cout<<"\n\t\t\t";
			system("pause");
			//Hacer que t sea el estado superior de la pila
			aux = p ;
    		s = aux->nro;
    		//Meter ir_A en la pila
    		int numEtiqueta=ir_A(s, listaGramatica[t].etiqueta);
			push(p,numEtiqueta);
			cout<<"\n\t\t\t\tIR_A["<<s<<","<<listaGramatica[t].etiqueta<<"]  ->"<<numEtiqueta<<"\n\n";
			mostrar_pila(p);
			cout<<"\n\t\t\t";
			system("pause");
    		system("cls");	
		}else if(accion(s,a)=="$"){
			break;
			
		}else{
			system("pause");
			exit(0); 
		}
	}
}


string accion(int s, string a){
	for(int i=0;i<sizeof(lista);i++){
		if(s==lista[i].estado && a==lista[i].var){
			e = lista[i].cond;
			t = lista[i].num;
			return e;
		}
	}
}

int ir_A(int t, string A){
	int retorno;
	for(int i=0;i<sizeof(listaIr_A);i++){	
		if(t==listaIr_A[i].estado && A.compare(listaIr_A[i].var)==0){
			retorno = listaIr_A[i].num;
			return retorno;	
		}
	}

}

void push( ptrPila &p, int valor ){
     ptrPila aux;
     aux = new(struct nodo);
     aux->nro = valor;  
     aux->sgte = p ;
     p = aux ;
}

int pop( ptrPila &p, int cantidad ){	
	int i=0;
	int num;
	while(i<cantidad){
		ptrPila aux;
		aux = p ;
		num = aux->nro;
		p = aux->sgte ;
		delete(aux);
		i++;
	 }
	 return num;
    
}

void mostrar_pila( ptrPila p ){
    ptrPila aux;
    aux = p;
    while( aux !=NULL ){
        cout<<"\t\t\t\t\t\u007C"<< aux->nro <<"\u007C\n";
    	aux = aux->sgte;
	}
}

void lexico(){

	ifstream archivo;	
	int estado=0;	
	char caracter;	
	string simbolo;	
	string tokens="";	
    archivo.open("Archivo.txt", ios::in);
    
    if(archivo.fail()){  
		cout<<"ERROR AL ABRIR ARCHIVO"<<endl;  
		exit(1);
			
	}else{	
		
		archivo.get(caracter);
		
		while (!archivo.eof()){		
			simbolo = caracter;
						
			switch (estado){				
				case 0:
					if (isalpha(caracter)){						
						estado = 1;		
										
					}else if (isdigit(caracter)){					
						estado = 2;	
										
					}else if (simbolo.compare(",") == 0){
						tokens = tokens + simbolo;
						archivo.get(caracter);		
						estado = 3;	
								
					}else if (simbolo.compare("=") == 0 or simbolo.compare("<") == 0 or simbolo.compare(">") == 0){				
						estado = 5;
						
					}else if (simbolo.compare("!")==0){
						tokens = tokens + simbolo;	
						archivo.get(caracter);			
						estado = 7;	
									
					}else if (simbolo.compare("(")==0){	
						tokens = tokens + simbolo;	
						archivo.get(caracter);	
						estado = 8;
					
					}else if (simbolo.compare(")")==0){	
						tokens = tokens + simbolo;	
						archivo.get(caracter);
						estado = 9;
					
					}else if (simbolo.compare(";")==0){	
						tokens = tokens + simbolo;	
						archivo.get(caracter);	
					    estado = 10;
					
					}else if (simbolo.compare("#")==0){	
						tokens = tokens + simbolo;						
						archivo.get(caracter);
						estado = 11;
					
					}else if (simbolo.compare("&")==0){	
						tokens = tokens + simbolo;						
						archivo.get(caracter);
						estado = 12;
					
					}else if (simbolo.compare("'")==0){	
						tokens = tokens + simbolo;						
						archivo.get(caracter);				
						estado = 13;
					
					}else if (simbolo.compare("{")==0){	
						tokens = tokens + simbolo;						
						archivo.get(caracter);				
						estado = 14;
					
					}else if (simbolo.compare("}")==0){				
						tokens = tokens + simbolo;						
						archivo.get(caracter);
						estado = 15;
					
					}else if (simbolo.compare("+")==0 or simbolo.compare("-")==0 or simbolo.compare("*")==0 or simbolo.compare("/")==0){				
						tokens = tokens + simbolo;						
						archivo.get(caracter);
						estado = 16;
					
					}else if (simbolo.compare("[")==0){	
						tokens = tokens + simbolo;						
						archivo.get(caracter);					
						estado = 17;
					
					}else if (simbolo.compare("]")==0){	
						tokens = tokens + simbolo;						
						archivo.get(caracter);				
						estado = 18;
					
					}else if (simbolo.compare(":")==0){	
						tokens = tokens + simbolo;						
						archivo.get(caracter);			
						estado = 19;
					
					}else if(simbolo.compare("$")==0){
						tokens = tokens + simbolo;						
						archivo.get(caracter);			
						estado = 20;
					}else{					
						archivo.get(caracter);
						
					}
					break;			
				case 1 :		
					if (isalnum(caracter)){				
						tokens = tokens + simbolo;	
						archivo.get(caracter);					
					
					}else  {
						verificar= 1;						
						char *cadena = (char *)tokens.c_str();			
						if(verificarSeparador(simbolo) == true){				
							if (verificarReservada (cadena)==true){													
								//cout<<"\t PALABRA RESERVADA : "<<cadena<<"\n"<<endl;
								arregloCadena[cont] = cadena;
								cont++;
								tokens="";						
								estado = 0;													
							}else{									
								//cout<<"\t IDENTIFICADOR : "<<cadena<<"\n"<<endl;
								arregloCadena[cont] = "id";
								cont++;
								tokens="";						
								estado = 0;								
							}
							
						}else{
							cout<<"\t EXPRESION NO VALIDA : "<<tokens<<""<<simbolo<<"\n"<<endl;	
							tokens="";
							estado = 0;
													
						}
					/*	for(int i; i<cont; i++){
									cout<<"	Verificacion de almacenamiento: ";
									cout<<arregloCadena[i]<<",";
								}*/
							
	
					}	
					
					break;
				
				case 2:	
					if(isdigit(caracter)){	
						tokens = tokens + simbolo;
						archivo.get(caracter);
					
					}else if(isalpha(caracter)){			
						//cout<<"\t ERROR COMBINACION DE NUMEROS Y CARACTERES : "<<tokens<<simbolo<<"\n"<<endl;	
						tokens="";
						estado = 0;	
						
					}else if (simbolo.compare(",") == 0){
						tokens = tokens + simbolo;	
						arregloCadena[cont] = tokens;
						cont++;
						archivo.get(caracter);	
						estado = 3;
							
					}else{	
						verificar= 2;
						if(verificarSeparador(simbolo) == true){
							//cout<< "\t RESULTADO ENTERO : "<<tokens<<"\n"<<endl;
							tokens = "id";
							arregloCadena[cont] = tokens;
							cont++;
							tokens="";
							estado = 0;
						
						}else{
							tokens="";
							estado = 0;
							
						}					
						
					}		
										
					break;
					
				case 3:				
					if(isdigit(caracter)){
						tokens = tokens + simbolo;
						archivo.get(caracter);
						estado = 4;
					
					}else{
						//cout<<"\t EXPRESION NO VALIDA : "<<tokens<<""<<simbolo<<"\n"<<endl;			
						tokens="";
						archivo.get(caracter);
						estado = 0;
						
					}
														
					break;
					
				case 4:	
					if(isdigit(caracter)){	
						tokens = tokens + simbolo;	
						archivo.get(caracter);
			
					}else{	
						verificar= 2;
						if(verificarSeparador(simbolo) == true){
							//cout<< "\t RESULTADO DECIMAL : "<<tokens<<"\n"<<endl;
							arregloCadena[cont] = tokens;
							cont++;
							tokens="";
							estado = 0;
						
						}else{	
							cout<<"\t EXPRESION NO VALIDA : "<<tokens<<""<<simbolo<<"\n"<<endl;	
							archivo.get(caracter);	
							tokens="";
							estado = 0;
							
						}
																	
					}
				break;
				case 5:	
					if(simbolo.compare("<") == 0 or  simbolo.compare("=") == 0 or simbolo.compare(">") == 0){							
						tokens = tokens + simbolo;							
						archivo.get(caracter);
						simbolo = caracter;
		
						if(simbolo.compare("<") == 0 or  simbolo.compare("=") == 0 or simbolo.compare(">") == 0){
							estado = 6;	
							tokens = tokens + simbolo;
						
						}																										
	
					}else {	
						verificar= 3;
						if(verificarSeparador(simbolo) == true or isalnum(caracter)){
						//	cout<<"\t OPERADOR RELACIONAL SIMPLE : "<<tokens<<"\n"<<endl;
							arregloCadena[cont] = tokens;
							cont++;
							tokens="";
							estado = 0;
							
						}else{
							cout<<"\t EXPRESION NO VALIDA : "<<tokens<<""<<simbolo<<"\n"<<endl;
							archivo.get(caracter);
							tokens="";
							estado = 0;
							
						}
							
					}																			
										
				break;
					
				case 6: 
					
					verificar= 3;
						
					archivo.get(caracter);
					
					if(verificarSeparador(simbolo) == true or isalnum(caracter)){		
						if(tokens.compare("<=") == 0 or  tokens.compare("==") == 0 or tokens.compare(">=") == 0 or tokens.compare("!=") == 0 )	{
							//cout<<"\t OPERADOR RELACIONAL COMPUESTO : "<<tokens<<"\n"<<endl;
							arregloCadena[cont] = tokens;
							cont++;						 						
							tokens="";	
							estado = 0; 
							
						}else{
							
							cout<<"\t OPERADOR RELACIONAL NO VALIDO : "<<tokens<<"\n"<<endl;
							tokens="";
							estado = 0;
							
						}
							
					}else {
							
							cout<<"\t OPERADOR RELACIONAL NO VALIDO : "<<tokens<<"\n"<<endl;									
							tokens="";	
							estado = 0;
					}
																
				break;
				
				case 7:	
						if (simbolo.compare("=")== 0){
							tokens = tokens + simbolo;
							archivo.get(caracter);
							estado = 6;																									
				
						}else {	
					
							cout<<"\t EXPRESION NO VALIDA : "<<tokens<<simbolo<<"\n"<<endl;			
							tokens="";
							archivo.get(caracter);
							estado = 0;
						}
									
				break;
				
				case 8:
					
						verificar= 4;
						if(verificarSeparador(simbolo) == true or isalnum(caracter)){
							//cout<<"\t INICIO EXPRESION : "<<tokens<<"\n"<<endl;	
							arregloCadena[cont] = tokens;
							cont++;											
							tokens="";	
							estado = 0;	
							
						}else{
							cout<<"\t EXPRESION NO VALIDA : "<<tokens<<simbolo<<"\n"<<endl;
							tokens="";
							archivo.get(caracter);
							estado = 0;
							
						}			
					
									
				break;
				
				case 9:
				
						verificar= 5;
						if(verificarSeparador(simbolo) == true){
							//cout<<"\t FINAL EXPRESION : "<<tokens<<"\n"<<endl;
							arregloCadena[cont] = tokens;
							cont++;
							tokens="";	
							estado = 0;
						
						}else{
							
							cout<<"\t EXPRESION NO VALIDA : "<<tokens<<simbolo<<"\n"<<endl;
							archivo.get(caracter);
							tokens="";
							estado = 0;
							
						}
														
									
				break;
				
				case 10:								
						verificar= 6;
						if(verificarSeparador(simbolo) == true){
							//cout<<"\t TERMINADOR : "<<tokens<<"\n"<<endl;
							arregloCadena[cont] = tokens;
							cont++;												
							tokens="";		
							estado = 0;		
						
						}else{
							cout<<"\t TERMINADOR NO VALIDO : "<<tokens<<simbolo<<"\n"<<endl;
							archivo.get(caracter);	
							tokens="";
							estado = 0;
							
						}	
													
				break;
				
				case 11:
						verificar= 7;
						if(verificarSeparador(simbolo) == true or isalnum(caracter)){
							//cout<<"\t OPERADOR LOGICO OR : "<<tokens<<"\n"<<endl;
							arregloCadena[cont] = tokens;
							cont++;											
							tokens="";	
							estado = 0;
						}
						else{
							cout<<"\t OPERADOR LOGICO NO VALIDO : "<<tokens<<simbolo<<"\n"<<endl;
							tokens="";
							archivo.get(caracter);
							estado = 0;
							
						}	
												
				break;
				
				case 12:
					
						verificar= 7;
						if(verificarSeparador(simbolo) == true or isalnum(caracter)){
							//cout<<"\t OPERADOR LOGICO AND : "<<tokens<<"\n"<<endl;
							arregloCadena[cont] = tokens;
							cont++;												
							tokens="";	
							estado = 0;
						}else{
							cout<<"\t OPERADOR LOGICO NO VALIDO : "<<tokens<<simbolo<<"\n"<<endl;
							tokens="";
							archivo.get(caracter);
							estado = 0;
							
						}
					
												
				break;
				
				case 13:
					
						verificar= 8;
						if(verificarSeparador(simbolo) == true or isalnum(caracter)){
							//cout<<"\t REPRESENTACION CADENA : "<<tokens<<"\n"<<endl;
							arregloCadena[cont] = tokens;
							cont++;												
							tokens="";	
							estado = 0;		
						
						}else{
							cout<<"\t EXPRESION NO VALIDA : "<<tokens<<simbolo<<"\n"<<endl;
							tokens="";
							archivo.get(caracter);
							estado = 0;
							
						}	
										
				break;
				
				case 14:
					verificar= 9;
					if(verificarSeparador(simbolo) == true or isalpha(caracter)){
						//cout<<"\t INICIO BLOQUE : "<<tokens<<"\n"<<endl;
						arregloCadena[cont] = tokens;
						cont++;											
						tokens="";	
						estado = 0;					
					}else{
						cout<<"\t EXPRESION NO VALIDA : "<<tokens<<simbolo<<"\n"<<endl;
						tokens="";
						archivo.get(caracter);
						estado = 0;
							
					}	
										
				break;
				
				case 15:
					verificar= 9;
					if(verificarSeparador(simbolo) == true or isalpha(caracter)){
						//cout<<"\t FIN BLOQUE : "<<tokens<<"\n"<<endl;
						arregloCadena[cont] = tokens;
						cont++;											
						tokens="";	
						estado = 0;					
					}else{
						cout<<"\t EXPRESION NO VALIDA : "<<tokens<<simbolo<<"\n"<<endl;
						tokens="";
						archivo.get(caracter);
						estado = 0;
							
					}	
												
				break;
				
				case 16:
					
					verificar= 7;
					if(verificarSeparador(simbolo) == true or isalnum(caracter)){
						//cout<<"\t OPERADOR ARITMETICO : "<<tokens<<"\n"<<endl;
						arregloCadena[cont] = tokens;
						cont++;											
						tokens="";	
						estado = 0;					
					}else{
						cout<<"\t EXPRESION NO VALIDA : "<<tokens<<simbolo<<"\n"<<endl;
						tokens="";
						archivo.get(caracter);
						estado = 0;
							
					}
												
				break;
				
				case 17:	
					verificar= 10;
					if(verificarSeparador(simbolo) == true or isalnum(caracter)){
						//cout<<"\t INICIO SUBINDICE : "<<tokens<<"\n"<<endl;	
						arregloCadena[cont] = tokens;
						cont++;										
						tokens="";	
						estado = 0;					
					}else{
						cout<<"\t EXPRESION NO VALIDA : "<<tokens<<simbolo<<"\n"<<endl;
						tokens="";
						archivo.get(caracter);
						estado = 0;		
					}																									
								
				break;
				
				case 18:	
					verificar= 10;
					if(verificarSeparador(simbolo) == true){
						//cout<<"\t FIN SUBINDICE : "<<tokens<<"\n"<<endl;	
						arregloCadena[cont] = tokens;
						cont++;												
						tokens="";	
						estado = 0;					
					}else{
						cout<<"\t EXPRESION NO VALIDA : "<<tokens<<simbolo<<"\n"<<endl;
						tokens="";
						archivo.get(caracter);
						estado = 0;		
					}																									
								
				break;
				
				case 19:	
					verificar= 3;
					if(verificarSeparador(simbolo) == true or isalnum(caracter)){
						//cout<<"\t SEPARADOR : "<<tokens<<"\n"<<endl;
						arregloCadena[cont] = tokens;
						cont++;													
						tokens="";	
						estado = 0;					
					}else{
						cout<<"\t EXPRESION NO VALIDA : "<<tokens<<simbolo<<"\n"<<endl;
						tokens="";
						archivo.get(caracter);
						estado = 0;		
					}																									
								
				break;
				
				case 20:
					verificar= 6;
					if(verificarSeparador(simbolo) == true){
						//cout<<"\t TERMINADOR : "<<tokens<<"\n"<<endl;
						arregloCadena[cont] = tokens;
						cont++;												
						tokens="";		
						estado = 0;		
						
					}else{
						cout<<"\t TERMINADOR NO VALIDO : "<<tokens<<simbolo<<"\n"<<endl;
						archivo.get(caracter);	
						tokens="";
						estado = 0;		
					}
				break;
			}			
				
	}	
    archivo.close();

	}
	
}

bool verificarReservada ( char palabra [ ] ) { 
    int comp ; 
    bool verificar = false ; 
    for ( int i = 0 ; i < 4 ; i ++ ) { 
    comp = strcmp ( reservadas [ i ] ,palabra ) ; 
      if ( comp == 0 ){  
         verificar = true ;     
      }  
    }
    return verificar ; 
}

bool verificarSeparador(string simbolo){
	
    bool resultado = false;
    if (verificar == 1){   	
    	for ( int i = 0 ; i < 21 ; i ++ ) {
			if (simbolo.compare(s1[i])==0){
				resultado = true ;	
			} 	
		}	
	}else if(verificar == 2){
		for ( int i = 0 ; i < 15 ; i ++ ) {
			if (simbolo.compare(s2[i])==0){
				resultado = true ;		
			} 
		}
	}else if(verificar == 3){
		for ( int i = 0 ; i < 2 ; i ++ ) {
			if (simbolo.compare(s3[i])==0){
				resultado = true ;
				
			} 
		}
	}else if(verificar == 4){
		for ( int i = 0 ; i < 4 ; i ++ ) {
			if (simbolo.compare(s4[i])==0){
				resultado = true ;			
			} 
		}
	}else if(verificar == 5){
		for ( int i = 0 ; i < 9 ; i ++ ) {
			if (simbolo.compare(s5[i])==0){
				resultado = true ;
			} 
		}
		
	}else if(verificar == 6){
		for ( int i = 0 ; i < 2 ; i ++ ) {
			if (simbolo.compare(s6[i])==0){
				resultado = true ;
				
			} 
		}
	}else if(verificar == 7){
		for ( int i = 0 ; i < 3 ; i ++ ) {
			if (simbolo.compare(s7[i])==0){
				resultado = true ;
				
			} 
		}
	}
	else if(verificar == 8){	
		for ( int i = 0 ; i < 4 ; i ++ ) {	
			if (simbolo.compare(s8[i])==0){	
				resultado = true ;		
			} 
		}	
	}
	else if(verificar == 9){	
		for ( int i = 0 ; i < 3 ; i ++ ) {	
			if (simbolo.compare(s9[i])==0){	
				resultado = true ;		
			} 
		}	
	}
	else if(verificar == 10){	
		for ( int i = 0 ; i < 5 ; i ++ ) {	
			if (simbolo.compare(s10[i])==0){	
				resultado = true ;		
			} 
		}	
	}		
    return resultado;	
}
