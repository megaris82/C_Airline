#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

struct address{ //inner structure address pou periexei odo, arithmo odou, perioxi kai taxidromiko kodika, xrisimopoieitai entos tou structure passenger
	char street[30];
	int num;
	char area[20];
	int pc; //postal code
};

struct passenger{ //outer structure passenger pou periexei onoma, epitheto, tin inner structure address , username pou prokuptei me sigkekrimeno tropo, kodiko pou diabazetai kai ton pinaka flights
	char name[20];
	char surn[20];
	struct address addr;
	char username[22];//19 maximum xaraktires to eponimo + 3 to 456 ara 22 max
	char password[20];
	char flights[3][4][11];//trisdiastatos logo tou oti exoume disdiastato pinaka pou periexei strings
};

int logad=0;//global metabliti pou xrisimopoieitai os elegxo gia to login h oxi tou admin sto sistima

char cities[10][4];
int prices[10][2];
/*afou h set_prices den ziteitai na epistrefei pinaka tha ftiaksoume kai tha gemisoume global pinaka strings estw prices[10][3][4] (trisdiastato giati apothikeuei se kathe grammi,
 3 strings megethous os 4, ------  epeita oi times tha ginoun akeraioi me tin xrisi tis atoi*/
int pass=0; //xrisimopoieitai etsi oste mono tin proti fora na pernaei ta onomata
void set_prices(void){
	logad=1;
	int i,j;
	for(i=0;i<10;i++){
		if (pass==0){
		printf("Input the name of the city:");
		scanf("%3s", cities[i]);
		printf("Input the taxes of the airport:");
		scanf("%d", &prices[i][0]);
		printf("Input the cost of the flight:");
		scanf("%d", &prices[i][1]);
		}
		else if(pass!=0){
		printf("Input the taxes of the airport:");
		scanf("%d", &prices[i][0]);
		printf("Input the cost of the flight:");
		scanf("%d", &prices[i][1]);
		}
	}
	pass=pass+1;
}

char usad[]="airadmin";//username admin
char paad[]="Air123";//password admin  xrisimopoiountai gia ton elegxo oti oi local metablites pou tha eisagei o xristis einai autes pou apaitountai gia tin eisodo sto sistima

void signup_user(struct passenger *psg){//xrisimopoieitai gia to signup tou user
	printf("Input your name:");
	scanf("%s", psg->name);
	printf("Input your surname:");
	scanf("%s", psg->surn);
	printf("Input your street name:");
	scanf("%s", psg->addr.street);
	printf("Input your street number:");
	scanf("%d", &psg->addr.num);
	printf("Enter the name of your area:");
	scanf("%s", psg->addr.area);
	printf("Input your postal code:");
	scanf("%d", &psg->addr.pc);
	printf("Input your password:");
	scanf("%s", psg->password);
	strcat(psg->surn, "456");//kanei to surname surname456 me ta grammata opws itan
	strcpy(psg->username,psg->surn);//kanei to username=surname+456 me ta grammata opws itan
	strlwr(psg->username);//kanei ola ta grammata mikra (string.h)
	printf("Your username is: %s\n", psg->username);//boithaei ton user na gnorizei ti simbainei sto backend me to username 
	printf("Your registration was successful! Redirecting to user menu..");
	sleep(5);
}

int userlog=0;//global metabliti pou elegxei tin epitixia eisodou tou user
int login_user(struct passenger psg[20]){//xrisimopoieitai gia to login tou user
	char ius[22],ipass[20];//local metablites tis opoies tha elegjoume an exei xrisimopoiisei kapoios user gia na eggrafei sto sistima
	printf("Please input the username you signed up with:");
	scanf("%21s", ius);
	printf("Please input the password you signed up with:");
	scanf("%19s", ipass);
	int i,pos;
	userlog=0;//h userlog pairnei times 1 an egine epitixis eisodos h 0 an den egine, etsi elegxetai epeita h emfanisi h oxi tou epimerous user menu
	for (i=0;i<20;i++){
		if ((strcmp(psg[i].username,ius)==0)&&(strcmp(psg[i].password,ipass)==0)){
			userlog=1;
			pos=i;
		}
	}
	return pos;
}

void view_user(struct passenger psg){//sinartisi pou xrisimopoieitai gia tin emfanisi ton stoixeiwn tou ekastote xristi, apli xrisi printf me stoixeia apo domi
	printf("Your name is: %s\n", psg.name);
	printf("Your surname is: %s\n", psg.surn );
	printf("Your street name is %s , the number is %d , in the area of %s with the postal code %d\n", psg.addr.street , psg.addr.num , psg.addr.area , psg.addr.pc );
	printf("Your username is %s and your password is %s\n", psg.username , psg.password); //endexetai kindinos logo emfanisis password alla afou o xristis exei kanei login tote den einai apolutws lathos
	sleep(5);//afinei xrono gia tin anagnosi ton dedomenwn 
	system("cls");
}//den tiponetai o pinakas flights dioti eisagetai meta 

void modify_user(struct passenger *passptr){//sinartisi gia tin epejergasia tis domis address gia ton eggegrammeno xristi
	printf("Please enter your new street name:");
	scanf("%s", passptr->addr.street);
	printf("Please enter your new street number:");
	scanf("%d", &passptr->addr.num);
	printf("Please enter your new area name:");
	scanf("%s", passptr->addr.area);
	printf("Please enter your new postal code:");
	scanf("%d", &passptr->addr.pc);
	system("cls");
}//standard methodos gia tin enimerosi enos structure me xrisi pointers

int calcam[20]={0}; //metraei ta tajidia gia ta opoia exei upologistei h timh
void calculate_cost(struct passenger *ptr, int pos1){//xrisimopoieitai gia tin eisagogi ton trion proorismwn tou xristi kai ton upologismo tou kostous gia kathe ptisi
	calcam[pos1]=0; //midenizetai gia kathe user
	int i;
	int times1;//metraei tis fores pou trexei i calculate_cost
	char des[4];//array pou apothikeuei ton proorismo
	char day[3],month[3],date[5];
	int cost;//metabliti kostos pou upologizetai kai sozetai stin thesi flights[i][3]
	for(times1=0;times1<3;times1++){
		printf("Please input the name of your destination, the possible destinations are: ROM, MAD, LON, BER, AMS, NYW, BEI, CHI, SYD\n");
		scanf("%s", des); // den elegxoume tin eisodo epeidh den zitite, tha itan sxetika eukolo me tin xrisi mias domis if me pollous elegxous, mesa se mia alli while (etsi oste na ginetai mexri na dothei sosti eisodos)
		sprintf(ptr->flights[times1][3], "%s", des);//kanei copy to destination pou lambanei apo to pliktrologio stin 4h thesi tou pinaka flights stin grammi times (1/2/3)
		time_t ct = time(NULL);
	    struct tm *tptr = localtime(&ct);
	    char date[5];
	    char day[3], month[3];
	    sprintf(day, "%02d", tptr->tm_mday);//h sprintf xrisimopoiithike meta apo ereuna sto stackoverflow 
	    sprintf(month, "%02d", tptr->tm_mon + 1);// to 02d simainei oti emfanizetai 01 anti gia 1 gia to ianouario , +1 epeidh oi mines arxizoun apo 0
	    strcpy(date, day);//date=day
	    strcat(date, month);//date=day+month
    	sleep(3);
    	char fl1[11],fl2[11];
    	strcpy(fl1,"ATH");//arxizei string gia ton kodiko tis ptisis pros ton proorismo
    	strcat(fl1,des);//prosthetei ton proorismo
    	strcat(fl1,date);//prosthetei tin imerominia ta isitiria
    	//--------------------------------------------------------------------
    	strcpy(fl2,des);//arxizei neo string gia ton kodiko tis ptisis epistrofis
    	strcat(fl2,"ATH");//prosthetei tin epistrofi (athina panta)
    	strcat(fl2,date);//prosthetei tin imerominia pou ekleise ta isitiria
    	//--------------------------------------------------------------------
    	sprintf(ptr->flights[times1][0], "%s", fl1);//bazei to string gia ton kodiko ptisis apo athina stin proti thesi tou flights
    	sprintf(ptr->flights[times1][1], "%s", fl2);//bazei to string gia ton kodiko ptisis pros athina stin deuteri thesi tou flights
    	//--------------------------------------------------------------------
    	//Tora tha asxolithoume me ton upologismo tis timis
    	//pollapli epilogi gia na kathorisoume poia poli exei epilejei o user
    	for (i=0;i<10;i++){
    		if(strcmp(cities[i],des)==0){
    			cost=prices[i][0]+prices[i][1]+prices[0][0]+prices[0][1];//pologismos telikis timis, prices[0] gia tin athina pou einai panta to ena tajidi
				itoa(cost, ptr->flights[times1][2], 10);//kanei to cost string kai to bazei sto trito column tis flights
				printf("The total cost of your flight is: %s\n", ptr->flights[times1][2]);
				sleep(1);
				calcam[pos1]=calcam[pos1]+1;
			}
		}
	}
	system("cls");
}

int paidfor[20][3]={0};//pinakas pou elegxei gia ta 20 atoma an exoun plirosei kai tis 3 ptisis tous, xrisimoipoietai stin payment kai stin most expensive
void payment(struct passenger *passptr,int pos){//epitrepei ston xristi na plirosei gia kapoia apo tis ptisis tou
	system("cls");
	int i;
	char inp[4],paym[4];
	for (i=0;i<3;i++){
		printf("The cost of flight number %d is : %s \n", i+1, passptr->flights[i][2]);//emfanizei to kostos gia tis 3 ptisis
	}
	printf("Please input the name of the destination of the flight you would like to pay for:");
	scanf(" %s", inp);
	for (i=0;i<3;i++){
		if(strcmp(passptr->flights[i][3],inp)==0){//an o proorismos anoikei se kapoia ptisi pou exei ginei calculate tote emfanizetai epeita to kostos
			printf("The flight of you choice had %s as a destination, the cost is %s\n", passptr->flights[i][3], passptr->flights[i][2]);
			do{
				printf("Please input the cost of the flight to pay:");
				scanf("%s", paym);
				if(strcmp(paym,passptr->flights[i][2])==0){//elegxei oti to poso pou eisagei o xristis einai iso me to kostos, allios sinexizei na to zita mexri na dothei to sosto
					printf("Successful payment!");
					paidfor[pos][i]=1;
					sleep(1);
				}
				else{
					printf("Transaction failed...Try again\n");
					sleep(1);
				}
			}
			while(paidfor[pos][i]!=1);
		}
	}
}

void most_expensive(struct passenger *psgptr,int posit){//xrisimopoieitai gia tin emfanisi tis pio akribis ptisis, xrisi tou posit me skopo ton elegxo tou paidfor
	int max=-1;//adinaton i timi na einai -1
	int i,maxp=-1,fcost;
	for (i=0;i<3;i++){
		if ((paidfor[posit][i])==1){
			fcost=atoi(psgptr->flights[i][2]);//i timi ginetai apo string akeraios kai apothikeuetai stin fcost EFOSON exei plirothei idi
			if (fcost>max){//elegxos an i timi einai megaliteri apo to max
				max=fcost;
				maxp=i;//kratame tin thesi me skopo tin emfanisi ton stoixeiwn ths ptisis argotera
			}
		}
	}
	printf("The most expensive flight was flight number %d\n", maxp+1);
	printf("The flight code from Athens towards the destination city was: %s\n", psgptr->flights[maxp][0]);
	printf("The flight code the destination city towards Athens was: %s\n", psgptr->flights[maxp][1]);
	printf("The flight's total cost was: %s\n", psgptr->flights[maxp][2]);
	printf("The flight's destination was: %s\n", psgptr->flights[maxp][3]);
	sleep(5);
	system("cls");
}

int main(int argc, char *argv[]) {
	struct passenger pass[20];//dimiourgeitai pinakas structures tupou passenger, mporoun na egrafoun os 20 
	char ch[6];//array me size 6, sozei 5 grammata maximum, oso to admin, ara ejikonomei xoro
	char usadl[9],paadl[7];//local metablites gia to login tou admin, xrisimopoiountai arrays pou xoroun akribws to noumero ton xaraktirwn gia logous asfaleias
	int pnum=0;//metraei poios passenger-user xrisimopoiei tin kathe stigmi to user menu
	do{
		printf("Please input the corresponding text:\n");
		printf("	    admin\n");
		printf("	    user\n");
		printf("	 0 - to exit\n");	
		scanf("%5s", ch);
		if(strcmp(ch,"admin")==0){
			char ch1;//epilogi tou admin
			system("cls");
			printf("Please input the username and password the system admin uses:\n");
			printf("username:");
			scanf("%8s",usadl);
			printf("password:");
			scanf("%6s",paadl);
			if((strcmp(usadl,usad)==0)&&(strcmp(paadl,paad)==0)){//elegxos oti oi local (eisodos apo pliktrologio) kai oi global metablites gia ta stoixeia tou admin tairiazoun
				printf("Successful login..");
				sleep(2);
				do{
					system("cls");
					printf("Please input the corresponding text:\n");
					printf("	   a. Set Prices\n");
					printf("	   b. Log out\n");
					scanf(" %c", &ch1);//skiparei to whitespace apo to enter stin  parapanw scanf
					if(ch1=='a'){
						system("cls");
						set_prices();//klisi tis sinartisis set prices
					}
					else if(ch1=='b'){
						system("cls");
						printf("Returning to main menu..");
						sleep(1);
						system("cls");
					}
				}
				while(ch1!='b');
			}
			else{
				printf("Wrong input, please try again..\n");
				sleep(1);
				system("cls");
			}
		}
		else if ((strcmp(ch,"user")==0)&&(logad==1)){//successful user login, arxi emfanisis user menu
			char ch2; //choice tou xristi
			do{
				system("cls");
				printf("Please input the corresponding text:\n");
				printf("	  a. Register\n");
				printf("	  b. Login\n");
				printf("	  c. Logout\n");
				scanf(" %c", &ch2);
				if (ch2=='a'){
					if(pnum<20){
						system("cls");
						signup_user(&pass[pnum]);
						pnum=pnum+1;
					}
					else{
						printf("The maximum amount of users have already signed up..Redirecting to user menu..");
						sleep(3);
					}	
				}
				else if (ch2=='b'){//den ziteitai elegxos gia proigoumeni eggrafi tou xristi, ean xreiazotan tha arkouse mia metabliti tupou int pou tha leitourgouse os simaia
				// stin sigkekrimeni periptosi an den exei ginei signup proigoumenos apla den tha brei matching kodiko kai username, opote kaliptetai i parapanw periptosi, xoris omos ousiastiki enasxolisi mazi tis
					system("cls");
					int pos; //krataei tin thesi tou pinaka pass stin opoia brisketai o xristis pou ekane login (blepe akribws katw) etsi oste meta na ton xeiristoume katallila sto epimerous user menu 
					pos=login_user(pass);//epeidh xreiazetai na kratisoume to flag alla kai tin thesi tou pinaka pass stin opoia brisketai o ekastote user tha kanoume to userlog global metabliti
					if (userlog==0){
						printf("Your credentials didn't match out record, please try again..");
						sleep(2);
					}
					else{//successful login, arxizei to epimerous user menu
						printf("Successful login..");
						sleep(1);
						system("cls");
						char ch3;//xaraktiras pou sozei tin epilogi tou user
						do{
							printf("Please input the number of your choice 1-6:\n");
							printf("		1. View\n");
							printf("		2. Modify\n");
							printf("		3. Calculate\n");
							printf("		4. Payment\n");
							printf("		5. Most Expensive\n");
							printf("		6. Logout\n");
							printf("Input:");
							scanf(" %c", &ch3);
							if (ch3=='1'){//pollapli epilogi gia tin ilopoiisi tou esoterikou user menu (meta to login)
								system("cls");
								view_user(pass[pos]);
							}
							else if (ch3=='2'){
								system("cls");
								modify_user(&pass[pos]);
							}
							else if (ch3=='3'){
								system("cls");
								calculate_cost(&pass[pos],pos);//pername to pos gia ton pinaka calcam
							}
							else if (ch3=='4'){
								if (calcam[pos]==3){
									payment(&pass[pos],pos); //pername kai tin thesi me skopo tin epejergasia tou pinaka paidfor pou tha xrisimopoiithei stin mostexpensive
									system("cls");
								}
							}
							else if (ch3=='5'){
								system("cls");
								most_expensive(&pass[pos],pos);//pername kai tin thesi me skopo tin epejergasia tou pinaka paidfor pou tha xrisimopoiithei edw
							}
							else if (ch3=='6'){
								system("cls");
								printf("Returning to user main menu..");
								sleep(1);
								system("cls");
							}
						}
						while (ch3!='6');
					}
				}
				else if (ch2=='c'){
					system("cls");
					printf("Returning to main menu..");
					sleep(1);
					system("cls");
				}
			}
			while(ch2!='c');
		}//telos user menu
		else if ((strcmp(ch,"user")==0)&&(logad==0)){//emfanisei minimatos se periptosi pou xristis prospathisei na kanei login prin ton admin
			system("cls");
			printf("The admin needs to signin and input the prices first..Redirecting you to the main menu..");
			sleep(2);
			system("cls");
		}
		else if (strcmp(ch,"0")==0){//termatismos programmatos, user friendly
			system("cls");
			printf("Program terminating..");
			sleep(2);
			system("cls");
		}
		else{ //an den balei o xristis sosti epilogi ton enimeronei kai emfanizei pali to arxiko menu
			printf("Wrong input, please try again!");
			sleep(1);
			system("cls");
		}
	}
	while (*ch!='0');
	return 0;
}
