#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


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

struct amigos{
	char nome[50];
	char fnome[50];
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
void estatistica();
void logout();
void removeamigo();
char numAmigos();
 



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
	int users_registrados = 0;
	
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
			exit(0);
		}
		for(i = 0;i < max ; i++ ){
			while(fread(&dados,sizeof(struct dados),1,fp)){
				if(!strcmp(dados.username,checknome) && !strcmp(dados.pass,checkpass)){
					printf("\n\n\n\t\t********Logado com Sucesso********\n");
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
	fp = fopen("users.dat","rb+");
	int op;
		printf("\t*********************** METAVERSE ***********************\n\n");
		while (fread(&dados, sizeof(dados),1, fp)) {   //Comparar no file o nome de quem fez login e de seguida ir buscar os dados da pessoa
			if (!strcmp(nome,dados.username)) {
				
				
			printf("\t BEM-VINDO %s", dados.username);
			printf("\n[1] - Alterar dados pessoais");
			printf("\n[2] - Consultar lista de amigos");
			printf("\n[3] - Adicionar amigo");
			printf("\n[4] - Remover amigo");
			printf("\n[5] - Informacoes da sua conta");
			printf("\n[6] - Publicacoes");
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
				listadeamigos(nome);
			break;
			case 3:
				addamigo(nome);
			break;
			case 4:
				removeamigo(nome);
			break;
			case 5:
				info(nome);
			break;
			case 6:
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
			
			verpost("Visitante",true);
			
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

void alterardados(char nome2[]){ 
	
	struct dados output;
	char validpass[50],pass[50];
	FILE *fp;
	
	start2:
	system("cls");
	
	fp = fopen("users.dat","rb+");
	
	printf("\t*********************** ALTERACAO DE DADOS ***********************\n\n");
	while(fread(&output, sizeof(output),1, fp)) {    
																							//Comparar no file o nome de quem fez login e de seguida ir buscar os dados da pessoa
		if (!(strcmp(nome2,output.username))) {
			
			
			printf("ATENCAO NAO PERMITIMOS A ALTERACAO DO USERNAME, %s!\n\n", output.nome);
			printf("\n**Digite o nome: ");
			fgets(output.nome, 50, stdin);
			strcpy(output.username, nome2);			
			printf("**Digite o seu email: ");									//Aqui tem de haver uma coisa q faça com q guarde o mesmo username
			fgets(output.email, 60, stdin);
			printf("**Digite a sua data de nascimento dd/mm/aa:  ");
			fgets(output.data, 50, stdin);
			printf("**Digite o seu numero de telefone: ");
			fgets(output.num, 50, stdin);
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
            printf("\nAlterando registro");
														//Guardar dados em um ficheiro .dat 
			 	for (int i = 0; i < 10; i++) {  
	        		for (int j = 0; j < 25000000; j++) {  
	            		i++;  
	            		i--;  
	        		}  
	       			printf(".");  
	   			}
					
			   	strcpy(output.pass, pass);
			   	fseek(fp, -sizeof(struct dados),SEEK_CUR); 
				fwrite(&output,sizeof(struct dados),1,fp);				//Guardar dados da struct dados no ficheiro .dat
						
																			
				if (fwrite != 0){	
						
					printf("\n");
					system("pause");
					system("cls");	
					printf("\n..Dados alterados com sucesso, %s..\n",output.nome);			//Ver se foi escrito algo no ficheiro caso seja diferente de 0 entao o registo esta completo 
	
				}
				else{	
																					
					printf("\n[ERROR]Impossivel completar a alteração!! Tente Novamente[ERROR]\n");	//Se o valor for 0 entao acaba o programa
					goto start2;
				}	
	fclose(fp);
	
	menu(nome2);    // Dá return ao menu com o nome do pessoa q fez login
	}
}
}

void listadeamigos(char *nome){
	
	system("cls");
	
	struct amigos amigos;
	
	FILE *fpm;
	
	fpm = fopen("amigos.dat","rb");
	
	printf("*********************** Lista de amigos ***********************");

	
	while(fread(&amigos,sizeof(struct amigos),1,fpm)){	
	size_t len = strlen(amigos.nome);
		if(!strcmp(amigos.nome,nome)){
			printf("\n%s",amigos.fnome);
		}
		
	}
	
	fclose(fpm);
	getchar();
	menu(nome);
}

bool checkfriend(char *nome,char *login){
	
	struct amigos amigos;
	struct dados dados;
	
	FILE *fp;
	FILE *ffr;
	
	bool check = false;	
	
	fp = fopen("users.dat","rb");
	ffr = fopen("amigos.dat","rb");
	
	if(fp == NULL || ffr == NULL){		
		printf("\n[ERROR]Impossivel abrir o ficheiro !! Tente novamente[ERROR]");
	}
	
	while(fread(&dados,sizeof(struct dados),1,fp)){
	
			if(strcmp(dados.username,nome) == 0 && strcmp(login,nome) != 0){
				check = true;
			}
	}	
	fclose(fp);
		if(check == true){
			for(int i = 0;i <= max*5;i++){
					while(fread(&amigos,sizeof(struct amigos),1,ffr)){				
						if(strcmp(nome,amigos.fnome) == 0){
							check = false;
						}
					}
			}
			fclose(ffr);
		}
		if(check == true){
			return true;
		}
		return false;
}


void addamigo(char *nome){
	
	system("cls");
	struct amigos amigos;

	
	char checknome[50];
	
	bool check;
	

	FILE *ffp;
	

	ffp = fopen("amigos.dat","ab+");
	
	if(ffp == NULL){		
		printf("\n[ERROR]Impossivel abrir o ficheiro !! Tente novamente[ERROR]");
	}
	
	printf("*********************** Adicionar amigo ***********************");
	printf("\nDigite o nome do user: ");
	fgets(amigos.fnome,50,stdin);
	strcpy(checknome,amigos.fnome);

			check = checkfriend(checknome,nome);
			
				if(check == true){
					strcpy(amigos.nome,nome);
					if(fwrite(&amigos,sizeof(struct amigos),1,ffp)){
						size_t len = strlen(amigos.fnome);
						if (amigos.fnome[len - 1] == '\n') { 
							amigos.fnome[len - 1] = '\0';
						}
						printf("\nUser [%s] adicionado aos amigos com sucesso\n",amigos.fnome);
						fclose(ffp);
						getchar();
						menu(nome);									
					}
				}else{	
				printf("\t\t\n<ERROR>Impossivel adicionar esse utilizador<ERROR>\n");
				fclose(ffp);				
				getchar();
				menu(nome);		
				}					
}

void removeamigo(char *nome){
	
	system("cls");
	struct amigos amigos;
	char removeuser[50];
	bool check = false;
	int i = 1,result;
	
	FILE *ffp = fopen("amigos.dat","rb+");
	FILE *fr = fopen("amigos.dat","rb");
	FILE *ofp = fopen("output.dat", "wb");
	
	
	if(ffp == NULL || fr == NULL || ofp == NULL){		
		printf("\n[ERROR]Impossivel abrir o ficheiro !! Tente novamente[ERROR]");
	}
	
	printf("*********************** Remover amigo ***********************");
	printf("\nLista de amigos:");
	
	while(fread(&amigos,sizeof(struct amigos),1,fr)){
		if(!strcmp(amigos.nome,nome)){
		printf("\n[%d]%s",i,amigos.fnome);
		i++;
		}
	}
	fclose(fr);

	printf("\nDigite o amigo a remover: ");
	scanf("%s",removeuser);
	getchar();
	

    struct amigos tmp;
    while (fread(&tmp, sizeof(struct amigos), 1, ffp)) {
    	
    	size_t len = strlen(tmp.fnome);
		if (tmp.fnome[len - 1] == '\n') { 
			tmp.fnome[len - 1] = '\0';
		}
    	
        if (strcmp(nome, tmp.nome) == 0 && strcmp(removeuser, tmp.fnome) == 0) {

            continue;
        }

        fwrite(&tmp, sizeof(struct amigos), 1, ofp);
    }
    
    fclose(ffp);
    fclose(ofp);
    
    result = remove("amigos.dat");
    
    if(result != 0){
    	printf("\n[ERROR]Erro ao apagar ficheiro[ERROR]");
    	menu(nome);
	}
	getchar();
	result = rename("output.dat", "amigos.dat");
	if( result != 0){
		printf("\n[ERROR]Erro ao renomear ficheiro[ERROR]");
		menu(nome);
	}
	printf("Amigo removido com sucesso");
	getchar();
	menu(nome);
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
	
	
	
    time_t segundos;
    struct tm *data;
    time(&segundos);

    data = localtime(&segundos);  
    
	printf("\t\t BEM-VINDO A AREA DE PUBLICACOES, %s ", nome1);

 //O utilizaor fornece a data atual para ter o parametro de "novas publicacoes"
	
		startpubli:
			
		printf("\n\t*********************** PUBLICACOES ***********************         %d/%d/%d\n\n",data->tm_mday,data->tm_mon+1,data->tm_year+1900);   //Menu das publicacoes
		printf("\n1 - Fazer publicacao publica");
		printf("\n2 - Fazer publicacao reservada");
		printf("\n3 - Fazer publicacao privada");
		printf("\n4 - Ver publicacoes na rede");
		printf("\n0 - Voltar Menu\n\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &op);

		
		
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
				verpost(nome1,false);
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
	fclose(fp);
}
	



void publipublica(char nome4[]){
	
	struct post post;
	FILE *fpp;
	
	fpp = fopen("publi.dat", "ab+");
	
	getchar();
	printf("[T]\t");
	fgets(post.publica,150,stdin);
	strcpy(post.user,nome4);
	fflush(stdin);
	
	
    time_t segundos;
    struct tm *data;
    time(&segundos);
    data = localtime(&segundos);  
	
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
			printf("\n..[%d:%d:%d]Publicacao completa , %s..\n",data->tm_hour,data->tm_min,data->tm_sec,nome4);			//Ver se foi escrito algo no ficheiro caso seja diferente de 0 entao o registo esta completo 
			getchar();
		}
		else{	
																					
			printf("\n[ERROR] Impossivel postar a publicacao [ERROR]\n");	//Se o valor for 0 entao acaba o programa
			return;
		}	
	fclose(fpp);
	menu(nome4);
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
	menu(nome5);
}


void publiprivada(char nome6[]){
	
	struct post post;
	FILE *fpp;
	
	fpp = fopen("publi.dat", "ab+");
	
	printf("[T]\t");
	fgets(post.privada,150,stdin);
	strcpy(post.user,nome6);
	getchar();
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
	menu(nome6);
}

bool checkamigo(char *amigo,char *nome){	
	
	struct amigos amigos;

	FILE *fm = fopen("amigos.dat","rb");

	while(fread(&amigos,sizeof(struct amigos),1,fm)){
						
				size_t len = strlen(amigos.nome);
				if (amigos.nome[len - 1] == '\n') { 
					amigos.nome[len -1] = '\0';
				}
				size_t len2 = strlen(amigo);
				if (amigo[len2 - 1] == '\n') { 
					amigo[len2 - 1] = '\0';
				}
				if(!strcmp(amigos.fnome,amigo) && !strcmp(amigos.nome,nome)){
					return true;
				}
			}
	fclose(fm);
	return false;
}

void verpost(char *nome,bool *visit){
	
	system("cls");
	struct post input;
	struct amigos amigos;
	FILE *fpp = fopen("publi.dat","rb");

	
	char user[50],c,askuser[50],amigo[50];
	char buffer[700];
	int opc,i,count = 0;
	bool check = false;
	long int pos;
	

	if(!fpp ){
		
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
						
				fseek(fpp, -5 * sizeof(struct post), SEEK_END);

					while(fread(&input,sizeof(struct post),1,fpp)){	
			
							printf("\n[?]Postado por %s\r",input.user);
							printf("%s",input.publica);
							
					}	
				
				
		getchar();	
		break;	
		
		case 2:	
			printf("Digite o nome do usuario: \n[-]");
			scanf("%s",askuser);
		
				while(fread(&input,sizeof(struct post),1,fpp)){
					
					size_t len = strlen(input.user);
					if (input.user[len - 1] == '\n') { 
					  	input.user[len -1] = '\0';
					}

					if(!strcmp(input.user,askuser)){
						printf("[P] %s\n",input.publica);

					}
				}	
			
		getchar();		
		break;
		
		case 3:
			if(visit == false){
				
				printf("\nDigite o nome do seu amigo: ");
				scanf("%s",amigo);
				getchar();
				
				check = checkamigo(nome,amigo);
				
				if(check == true){
					printf("TRUE");
				}
				else
				printf("FALSE");
				if(check == true){		
					while(fread(&input,sizeof(struct post),1,fpp)){
						size_t len = strlen(input.user);
						if (input.user[len - 1] == '\n') { 
							input.user[len -1] = '\0';
						}
						
						if(!strcmp(input.user,amigo)){
							
							printf("\n%s",input.publica);
						}		
					}
				}
				getchar();
				menu(nome);	
				fclose(fpp);
			}
			else{
				getchar();
				printf("Nao pode aceder a esta pagina em modo anonimo\n...");
				getchar();
				menuanon();
			}
		break;
		
		case 0:
			if(visit == false){
				menu(nome);
			}
			else{
				menuanon();
			}
		break;
		
	}
	
	getchar();
	verpost(nome,false);
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

char numAmigos(){
	
	struct amigos amigos;
	struct dados dados;
	
	FILE *ffp = fopen("amigos.dat","rb");
	FILE *fp = fopen("users.dat","rb");

	
	int i = 0,maxamigos = 0;
	char maxuser[50];
	
	maxuser[0] = '\0';
	
	if(ffp == NULL || fp == NULL){		
		printf("\n[ERROR]Impossivel abrir o ficheiro !! Tente novamente[ERROR]");
	}
for(int t = 1 ; t <= max ; t++)
	while(fread(&dados,sizeof(struct dados),1,fp)){
		while(fread(&amigos,sizeof(struct amigos),1,ffp)){
			if(!strcmp(dados.username,amigos.nome)){
				i++;
			}
		}
		if(i > maxamigos){
			strcpy(maxuser,amigos.nome);
			maxamigos = i;
			i = 0;
		}
	}

	
	fclose(ffp);fclose(fp);
	
	size_t len = strlen(maxuser);
	if (maxuser[len - 1] == '\n') { 
		maxuser[len -1] = '\0';
	}

	printf("\r\nUser com mais amigos.............................. %s",maxuser);

}


void estatistica(){
	
	system("cls");
	
	struct dados dados;
	struct post post;
	
	int max_posts = 0 , max_amigos = 0, num_posts = 0 , num_users = 0 , aux = 0;
	char cur_max_user[50],cur_user[50],last_login[50];
	
	FILE *fp;
	FILE *fpp;
	
	fp = fopen("users.dat","rb");
	fpp = fopen("publi.dat","rb");
	
	
	if(!fp || !fpp){
		printf("\n[ERROR]Impossivel abrir o ficheiro !! Tente novamente[ERROR]\n");
	}
	
	printf("************************* Estatistica *************************\n\n");
	
	//numero de users
	while(fread(&dados,sizeof(struct dados),1,fp)){
		num_users++;
		while(fread(&post,sizeof(struct post),1,fpp)){
			
			if(!strcmp(dados.username,post.user)){
					aux++;
			}
			if(post.publica != ""){
				num_posts++;
			}	
		}
		if (aux > max_posts){
			max_posts = aux;
			strcpy(cur_max_user,dados.username);
		}
		
	}
	
	printf("\nNumero de utilizadores ........................... %d",num_users);
	
	//numero de posts

	printf("\nNumero de postagens .............................. %d",num_posts);
	
	//mais posts	
	size_t len = strlen(cur_max_user);
	if (cur_max_user[len - 1] == '\n') { 
		cur_max_user[len -1] = '\0';
	}
	//mais amigos
	numAmigos();
	
	printf("\nUser com mais posts .............................. %s , [%d]",cur_max_user,max_posts);
	//mais amigos

	fclose(fp);fclose(fpp);
	
	getchar();
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
	printf("\n[4]. Informacoes da aplicacao");
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
	
	case 4:
		
		estatistica();
		goto start;
		
	break;
	
	case 0:	

		printf("[EXIT] Ate a proxima [EXIT]");
		return -1;
		
	break;
	
	default:
		system("cls");
		printf("\t\t [ERROR] Opcao Invalida [ERROR]\n\n");
		goto start;
	break;	
	}	
}