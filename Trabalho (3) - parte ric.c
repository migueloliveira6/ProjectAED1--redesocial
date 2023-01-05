#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//valores das teclas tab back enter 

#define tab 9
#define back 8
#define enter 13

#define max 50 //maximo de utilizadores



//-------------------------------------------------------------------------------------------//




struct dados{
	
	char nome[50];
	char username[50];
	char email[60];
	char data[50];
	char num[50];
	char pass[50];
	
};

struct post{   //Estrutura das publicacoes
	
	char user[50];
	char data[20];
	char publica[150];
	char privada[150];
	char reservada[150];
	
};


void menu();
void menuano();
void alterardados();
void listadeamigos();
void addamigo();
void info();
void fazerpublicacao();
void publipublica();
void publireservada();
void publiprivada();
void verpost();
void logout();



//-------------------------------------------------------------------------------------------//

//Substitui as letras da palavra pass para o caracter '-' e '_' (Visual)
void hidepassword(char pass[50]){	
	
	
	int i;
	char c;
	while(1){
		
		c = getch();
		if(c == enter || c == tab){		
			pass[i] = '\0';
			break;
		}
		else if(c == back){
			if(i > 0){
				i--;
				printf("\b \b");
				
			}	
		}
		else{
			pass[i++] = c;
			if (i % 2 == 0){
				printf("-\b");
			}
			else{
				printf("_\b");
			}
			
		}
		
		
	}
	
	
}

void registro(){
	
	struct dados dados;
	char validpass[50],pass[50];
	
	FILE *fp;
	
	system("cls");
		
	
		printf("\t*********************** Registro ************************");
		printf("\n**Digite o nome: ");
		fgets(dados.nome, 50, stdin);
		printf("**Digite o username desejado: ");
		fgets(dados.username, 50, stdin);
		printf("**Digite o seu email: ");	
		fgets(dados.email, 60, stdin);
		printf("**Digite a sua data de nascimento  dd/mm/aa:");
		fgets(dados.data, 50, stdin);
		printf("**Digite o seu numero de telefone: ");
		fgets(dados.num, 50, stdin);
		password1:
		printf("**Digite a sua password: ");
		hidepassword(pass);
		printf("**\nConfirmar password: ");
		hidepassword(validpass);
		
		fflush(stdin);
		
			if (strcmp(pass,validpass) != 0){							//Verifica se a primeira pass introduzida e igual a segunda
			
				printf("\n[ERROR]As Passwords introduzidas nao combinam[ERROR]\n");
				goto password1;
			
			}
			else{
			
			
				printf("\nGuardando Registro");								//Guardar dados em um ficheiro .dat  
				fp = fopen("users.dat","ab+");
				
			
			   	
			   		strcpy(dados.pass, pass);
					fwrite(&dados,sizeof(dados),1,fp);					//Guardar dados da struct dados no ficheiro .dat
					
															
				
				if (fwrite != 0){	
					
					printf("\n..Registro Completo , %s..\n",dados.nome);		//Ver se foi escrito algo no ficheiro caso seja diferente de 0 entao o registo esta completo 
					system("pause");
					system("cls");
				}
				else{	
																					
					printf("\n[ERROR]Impossivel completar o registro!! Tente Novamente[ERROR]\n");	//Se o valor for 0 entao acaba o programa

				}				
	}
	fclose(fp);			
}

void login(){
	
	struct dados dados;
	char checknome[20],checkpass[50],validpass[50];
	int i,check = 1,tent = 1;
	FILE *fp;
	
	start1:
	system("cls");
		
		printf("\t*********************** Login ***********************\n\n");
		printf("\nUsuario: \t");
		fgets(checknome, sizeof(checknome), stdin);
		printf("\nPassword:\t");
		hidepassword(checkpass);
		
		printf("\n\t\tVerificando credenciais");
		for (int i = 0; i < 10; i++){  
        	for (int j = 0; j < 25000000; j++) {
            	i++;  
            	i--;  
        	}  
        	printf(".");  
    		}
		
		fp = fopen("users.dat","rb");
		
		
		
		if(fp == NULL){
			
			printf("\n[ERROR]Impossivel abrir o ficheiro !! Tente novamente[ERROR]");
			
		}

		
		for(i = 0;i < max ; i++ ){
			while(fread(&dados,sizeof(struct dados),1,fp)){
				if(!strcmp(dados.username,checknome) && !strcmp(dados.pass,checkpass)){
					printf("\n\n\n\t\t********Logado com Sucesso********\n\n\n");
					check = 0;
					tent = 0;
					system("pause");
					menu(checknome);	
					return;														//Guardar o nome da pessoa que fez login para o programa saber no decorrer dele quem o está a usar		
				}
			}	
			if(check == 1 && tent != 3){

				printf("\n\n\t[ERROR] No Login!! Credenciais Invalidas , Tentativa : %d [ERROR]\n",tent);
				system("pause");
				tent += 1;
				goto start1;																	//Voltar ao inicio do login caso nao seja bem sucedido
								
			}
			else{
				
				printf("\n\n\t[ERROR] Numero maximo de tentativas excedido [ERROR]");
				tent = 0;
				return;
			}
		}
  	fclose(fp);
}


void menu(char nome[]){  //char (nome) pois para o programa sempre saber quem fez login
	
	system("cls");
	struct dados dados;
	FILE *fp;
	fp = fopen("users.dat","rb");
	int op;
		printf("\t*********************** METAVERSE ***********************\n\n");
		while (fread(&dados, sizeof(dados),1, fp)) {   //Comparar no file o nome de quem fez login e de seguida ir buscar os dados da pessoa
			if (!strcmp(nome,dados.username)) {
			printf("\t BEM-VINDO %s", dados.username);
			printf("\n[1] - Alterar dados pessoais");
			printf("\n[2] - Consultar lista de amigos");
			printf("\n[3] - Adicionar amigo");
			printf("\n[4] - Informacoes da sua conta");
			printf("\n[5] - Publicacoes");
			printf("\n\n\n[0] - Logout\n\n");
			printf("Escolha uma opcao: ");
			scanf("%d", &op);
			fflush(stdin);
			//nome = dados.username;
			switch(op){
			case 1:
				alterardados(nome);
			break;
			case 2:
				listadeamigos();
			break;
			case 3:
				addamigo();
			break;
			case 4:
				info(nome);
			break;
			case 5:
				fazerpublicacao(nome);
			break;
			case 0:
				logout();
				main();
			break;
			default:
				printf("Opcao invalida! \n");
				system("pause");
				system("cls");
			break;
			}
		}
	}
	fclose(fp);

	fflush(stdin);
}

void menuanon(){
	
	
	int op;
	
	system("cls");
	
	printf("\t BEM-VINDO");
	printf("\n[1] - Ver publicacoes ");
	printf("\n\n[0]- Logout\n\n");
	printf("Escolha uma opcao: ");
	
	scanf("%d", &op);
	fflush(stdin);
	
	switch(op){
		
		case 1:
			
			verpost();
			
		break;
		
		case 0:
			
			return;
			
		break;
			
		
		default:
			printf("Opcao invalida! \n");
			system("pause");
			system("cls");
		break;
			
	}		
	
}

void alterardados(char nome2[]){  //char (nome) pois para o programa sempre saber quem fez login 
	
	struct dados dados;
	char validpass[50],pass[50];
	FILE *fp;
	
	start2:
	system("cls");
	
	fp = fopen("users.dat","rb+");
	
	printf("\t*********************** ALTERACAO DE DADOS ***********************\n\n");
	while(fread(&dados, sizeof(dados),1, fp)) {    
							//Comparar no file o nome de quem fez login e de seguida ir buscar os dados da pessoa
		if (!(strcmp(nome2,dados.username))) {
			
			printf("ATENCAO NAO PERMITIMOS A ALTERACAO DO USERNAME, %s!\n\n", dados.nome);
			printf("\n**Digite o nome: ");
			fgets(dados.nome, 50, stdin);
			strcpy(dados.username, nome2);			
			printf("**Digite o seu email: ");									//Aqui tem de haver uma coisa q faça com q guarde o mesmo username
			fgets(dados.email, 60, stdin);
			printf("**Digite a sua data de nascimento dd/mm/aa:  ");
			fgets(dados.data, 50, stdin);
			printf("**Digite o seu numero de telefone: ");
			fgets(dados.num, 50, stdin);
			password2:
			printf("**Digite a sua password: ");
			hidepassword(pass);
			printf("**\nConfirmar password:\t");
			hidepassword(validpass);
	
			fflush(stdin);
			
			if (strcmp(pass,validpass) != 0){						//Verifica se a primeira pass introduzida e igual a segunda
				
					printf("\n[ERROR]As Passwords introduzidas nao combinam[ERROR]\n\n");
					goto password2;
			}
	
	break;
	}

            printf("\nAlterando registro");
										//Guardar dados em um ficheiro .dat 
			 	for (int i = 0; i < 10; i++) {  
	        		for (int j = 0; j < 25000000; j++) {  
	            		i++;  
	            		i--;  
	        		}  
	       			printf(".");  
	   			}
					
			   	strcpy(dados.pass, pass);
				fwrite(&dados,sizeof(dados),1,fp);				//Guardar dados da struct dados no ficheiro .dat
						
																			
				if (fwrite != 0){	
						
					printf("\n");
					system("pause");
					system("cls");	
					printf("\n..Dados alterados com sucesso, %s..\n",dados.nome);			//Ver se foi escrito algo no ficheiro caso seja diferente de 0 entao o registo esta completo 
	
				}
				else{	
																					
					printf("\n[ERROR]Impossivel completar a alteração!! Tente Novamente[ERROR]\n");	//Se o valor for 0 entao acaba o programa
					goto start2;
				}	
		break;
	}

			

	fclose(fp);
	
	menu(nome2);    // Dá return ao menu com o nome do pessoa q fez login
}

void listadeamigos(){
	
	
}

void addamigo(){
	
	
}

void fazerpublicacao(char nome1[]){  //char (nome) pois para o programa sempre saber quem fez login 
	
	struct dados dados;
	struct post post;
	FILE *fp;
	FILE *fpp;
	system("cls");
	int op;
	
	fp = fopen("users.dat", "rb");
	//fpp = fopen("publi.dat", "ab+");
	

	while (fread(&dados, sizeof(dados),1, fp)) {  //Comparar no file o nome de quem fez login e de seguida ir buscar os dados da pessoa
		if (strcmp(nome1,dados.username) == 0){
		
			printf("\t BEM-VINDO A AREA DE PUBLICACOES, %s ", dados.nome);
			printf("\nPor favor insira a data de hoje para poder aceder a esta aba!\n ");   //O utilizaor fornece a data atual para ter o parametro de "novas publicacoes"
			fgets(post.data, 20, stdin);
			fflush(stdin);
		
			//fwrite(&post,sizeof(post),1,fpp);  //Guardar a data no file publi.dat
		
			if (fwrite != 0){	
					
					printf("\n");
					system("cls");	
					printf("\n..Data guardada com sucesso, %s \n",dados.nome);			//Ver se foi escrito algo no ficheiro caso seja diferente de 0 entao o registo esta completo
			}
	
	startpubli:
			
		printf("\t*********************** PUBLICACOES ***********************\n\n");   //Menu das publicacoes
		printf("\n1 - Fazer publicacao publica");
		printf("\n2 - Fazer publicacao reservada");
		printf("\n3 - Fazer publicacao privada");
		printf("\n4 - Ver publicacoes na rede");
		printf("\n0 - Voltar Menu\n\n");
		printf("Escolha uma opcao: ");
		
		scanf("%d", &op);
		fflush(stdin);
		
		
			switch(op){
				
			case 1:
				publipublica(nome1);
			break;
			
			case 2:
				publireservada(nome1);
			break;
			
			case 3:
				publiprivada(nome1);
			break;
			
			case 4:
				verpost(nome1);
			break;
			
			case 0:
				menu(nome1);
			break;
			
			default:
				printf("Opcao invalida! \n");
				system("pause");
				system("cls");
				goto startpubli;
			break;
			}
		}
}	
 fclose(fp);
}


void publipublica(char nome4[]){
	
	struct post post;
	FILE *fpp;
	
	fpp = fopen("publi.dat", "ab+");
	
	printf("[T]\t");
	fgets(post.publica,150,stdin);
	strcpy(post.user,nome4);
	fflush(stdin);
	
	printf("\nPostando");
										//Guardar dados em um ficheiro .dat 
		for (int i = 0; i < 10; i++) {  
	       for (int j = 0; j < 25000000; j++) {  
	            i++;  
	           	i--;  
	        }  
	        
	    	printf(".");  
	   	}
		fwrite(&post,sizeof(post),1,fpp);				//Guardar dados da struct dados no ficheiro .dat
															
		if (fwrite != 0){	
						
			printf("\n");
			system("pause");
			system("cls");	
			printf("\n..Publicacao completa , %s..\n",nome4);			//Ver se foi escrito algo no ficheiro caso seja diferente de 0 entao o registo esta completo 

		}
		else{	
																					
			printf("\n[ERROR] Impossivel postar a publicacao [ERROR]\n");	//Se o valor for 0 entao acaba o programa
			return;
		}	
	fclose(fpp);
	fazerpublicacao(nome4);
}


void publireservada(char nome5[]){
	
	struct post post;
	FILE *fpp;
	
	fpp = fopen("publi.dat", "ab+");
	
	printf("[T]\t");
	fgets(post.reservada,150,stdin);
	strcpy(post.user,nome5);
	fflush(stdin);
	
	printf("\nPostando");
										//Guardar dados em um ficheiro .dat 
		for (int i = 0; i < 10; i++) {  
	       for (int j = 0; j < 25000000; j++) {  
	            i++;  
	           	i--;  
	        }  
	        
	    	printf(".");  
	   	}
		fwrite(&post,sizeof(post),1,fpp);				//Guardar dados da struct dados no ficheiro .dat
															
		if (fwrite != 0){	
						
			printf("\n");
			system("pause");
			system("cls");	
			printf("\n..Publicacao completa , %s..\n",nome5);			//Ver se foi escrito algo no ficheiro caso seja diferente de 0 entao o registo esta completo 

		}
		else{	
																					
			printf("\n[ERROR] Impossivel postar a publicacao [ERROR]\n");	//Se o valor for 0 entao acaba o programa
			return;
		}	
	fclose(fpp);
	fazerpublicacao(nome5);
}


void publiprivada(char nome6[]){
	
		struct post post;
	FILE *fpp;
	
	fpp = fopen("publi.dat", "ab+");
	
	printf("[T]\t");
	fgets(post.privada,150,stdin);
	strcpy(post.user,nome6);
	fflush(stdin);
	
	printf("\nPostando");
										//Guardar dados em um ficheiro .dat 
		for (int i = 0; i < 10; i++) {  
	       for (int j = 0; j < 25000000; j++) {  
	            i++;  
	           	i--;  
	        }  
	        
	    	printf(".");  
	   	}
		fwrite(&post,sizeof(post),1,fpp);				//Guardar dados da struct dados no ficheiro .dat
															
		if (fwrite != 0){	
						
			printf("\n");
			system("pause");
			system("cls");	
			printf("\n..Publicacao completa , %s..\n",nome6);			//Ver se foi escrito algo no ficheiro caso seja diferente de 0 entao o registo esta completo 

		}
		else{	
																					
			printf("\n[ERROR] Impossivel postar a publicacao [ERROR]\n");	//Se o valor for 0 entao acaba o programa
			return;
		}	
	fclose(fpp);
	fazerpublicacao(nome6);
}


void verpost(char nome[]){
	
	system("cls");
	struct post post;
	FILE *fpp;
	
	char user[50],c,askuser[50];
	char buffer[700];
	int opc,i,count = 0;
	
	fpp = fopen("publi.dat","rb"); 
	
	if(!fpp){
		
		printf("[ERROR]Impossivel abrir o ficheiro !! Tente novamente[ERROR]\n");
		return;
		
	}
	
	printf("*********************** OPCOES ***********************\n");
	printf("**[1]Ver publicacoes mais recentes \t\t    **\n");
	printf("**[2]Ver publicacoes de um usuario \t\t    **\n");
	printf("**[3]Ver publicacoes de um amigo \t\t    **\n");
	printf("**\t\t\t\t\t\t    **\n");
	printf("**[0]Sair para o menu \t\t\t\t    **\n");
	printf("******************************************************\n");
	
	scanf("%d",&opc);
	
	
	switch(opc){
		
		case 1:	
		
			
			while(fgets(buffer, sizeof(buffer), fpp) != NULL){
			
			count++;
			
			}
			
			while( fgets(buffer, sizeof(buffer), fpp) != NULL){
				
				if(buffer >= count - 5){
					
					while(fread(&post,sizeof(struct post),1,fpp)){	
			
							printf("[?]Postado por %s\r",post.user);
							printf("%s\n",post.publica);
					}	
				}
			}


		getchar();	
		break;	
		
		case 2:
				
			printf("Digite o nome do usuario: \n[-]");
			scanf("%s", askuser);
			
			for(int t = 0 ; t <= max ; t++){
				
				while(fread(&post,sizeof(struct post),1,fpp)){
					
					if(strcmp(askuser,post.user) == 0){
						
						printf("%s",post.publica);
						
					}
				}	
			}	
		getchar();	
		break;
			

	}
	getchar();
	verpost(nome);
	
}



void info(char nome3[]){
	
	struct dados dados;
	FILE *fp;
	fp = fopen("users.dat","rb");
	
	system("cls");

		
	while (fread(&dados, sizeof(dados),1, fp)){
		if (strcmp(nome3,dados.username) == 0) {
			printf("\n==== YOUR ACCOUNT INFO ====\n");  
              
            printf("\n***************************\n");  
              
            printf("NAME..\t%s", dados.nome);  
  
            printf("EMAIL..\t %s", dados.email);  
  
            printf("NUMERO DE TELEFONE..\t %s", dados.num);  
  
            printf("DATA DE NASCIMENTO..\t%s", dados.data);
		}
	}
	fclose(fp);
	system("pause");
	system("cls");
	menu(nome3);
}




void logout(){
	
    int i, j;  
    system("cls");  
    printf("\nEspere sair da area");  
  
    for (i = 0; i < 10; i++) {  
        for (j = 0; j < 25000000; j++) {  
            i++;  
            i--;  
        }  
        printf(".");  
    }  
  
    printf("\nSaiu do sistema com sucesso\n");  
    printf("Pressione qualquer tecla para continuar...\n");  
  
    getch();  
}




int main(){

	int ans,idade,t;
	char c;

	
	
	//FILE *fp;

	start:
	system("cls");
	printf("\t********************** Bem-vindo **********************\n\n");
	printf("\n[1]. Login");
	printf("\n[2]. Registar");
	printf("\n[3]. Visitante Anonimo");
	printf("\n\n[0]. Sair");
	printf("\n\n[R]- ");
       
	scanf("%d",&ans);
	fgetc(stdin);	           
         
	switch(ans){
	
	//login
	case 1:
		
		login();
		
	break;
		
	//registo
	case 2 :
		
		registro();
		goto start;
		
	break;
	
	case 3:
		
		menuanon();
		goto start;
		
	break;
	
	case 0:	

		printf("[EXIT] Ate a proxima [EXIT]");
		system("exit");
		
	break;
	
	default:
		system("cls");
		printf("\t\t [ERROR] Opcao Invalida [ERROR]\n\n");
		goto start;
	break;	
	}	
}