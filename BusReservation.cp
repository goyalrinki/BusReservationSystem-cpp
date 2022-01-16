#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
void mainmenu();
void mahalaxmi();
void bookTicket();
struct checkpoint
{
	int no;
	char startpoint[20];
	char endpoint[20];
	
};
struct bus
{
	int busno;
	char busname[20];
	char arrtime[10];
	char deptime[10];
	char status[4];
	char duration[10];
	int fare;
	
};
struct mahaseat
{
	int seatno;
	char status1;
};

void loadMahalaxmiSeats()
{
	FILE *maha;
	int i;
	struct mahaseat m;
	maha = fopen("Mahalaxmi.txt","ab+");
    printf("Enter seat number\n");
    scanf("%d",&m.seatno);
    printf("Enter status\n");
    scanf("%s",&m.status1);
    fwrite(&m,sizeof(m),1,maha);
    fclose(maha);
    printf("Congratulations!!\nYour bus seat is saved\n");
    printf("\nDo you want to add more seats?\n1.Yes\t\t\t2.No\n");
    scanf("%d",&i);
    switch(i)
    {
	  case 1:
		system("cls");
		loadMahalaxmiSeats();
		break;
	  case 2:
		system("cls");
		mainmenu();
	  default:
		system("cls");
		printf("Enter appropriate choice\n");
	
    }
}

void checkingMahalaxmi(int no,int *k)
{
	FILE *mbcheck;
	int i;
	mbcheck = fopen("Mahalaxmi.txt","rb+");
	struct mahaseat check;
	char *pk = (char *)malloc(sizeof(char)*(no));
	while(fread(&check,sizeof(struct mahaseat),1,mbcheck)==1)
	{
		for(i=0;i<no;i++)
		{
			fseek(mbcheck,0,SEEK_CUR);
			if(check.seatno==k[i])
			{
				int l;
				pk[i]=check.status1;
			//	printf("\n%c",pk[i]);
				if(pk[i]=='B')
				{
					printf("\nStatus is booked.");
					printf("\n%d\t%c",check.seatno,check.status1);
					printf("\nPlease again enter the numbet of tickets to book with appropriate seat no.\n");
					getch();
					system("cls");
					mahalaxmi();
				}
				break;
			}
		}
	}
	fclose(mbcheck);
}

void mahalaxmi()
{
	int i;
	int m;
	char g;
	FILE *mbc;
	struct mahaseat mseat;
	mbc=fopen("Mahalaxmi.txt","rb+");
	while(fread(&mseat,sizeof(struct mahaseat),1,mbc)==1)
	{
	    	printf("\t%d\t%c\n",mseat.seatno,mseat.status1);
	}
	fclose(mbc);
	printf("\nHow many tickets you want to book?\n");
	scanf("%d",&m);
	printf("\nPlease enter seat number.\n");
	int *p = (int *)malloc(sizeof(int)*(m));
	for(i=0;i<m;i++)
	{
		scanf("%d",&p[i]);
	}
	printf("Your seat numbers are:\n");
	for(i=0;i<m;i++)
	{
		printf("%d\n",p[i]);
	}
	getch();
	checkingMahalaxmi(m,p);
	FILE *mbcf;
	mbcf = fopen("Mahalaxmi.txt","rb+");
	struct mahaseat upstatus;
	while(fread(&upstatus,sizeof(struct mahaseat),1,mbcf)==1)
	{
		for(i=0;i<m;i++)
		{
			if(upstatus.seatno==p[i])
			{
				fseek(mbcf,-sizeof(upstatus),SEEK_CUR);
				upstatus.status1='B';
				fwrite(&upstatus,sizeof(upstatus),1,mbcf);
				fseek(mbcf,0,SEEK_CUR);
				printf("\t%d %c\n",upstatus.seatno,upstatus.status1);
				break;
			}
		}
	}
	printf("CONGRATS!! You have booked your tickets..\n");
	fclose(mbcf);
	getch();
	system("cls");
	mainmenu();
}

void security()
{
	char username[10],password[10],ch;
	int i;
	system("cls");
	printf("\nEnter Username:\n");
	gets(username);
	printf("\nEnter Password:\n");
	for(i=0;i<6;i++)
	{
		ch=getch();
		password[i]=ch;
		ch='*';
		printf("%c",ch);
	}
	password[i]='\0';
	if(strcmp(username,"Rinki")==0 && strcmp(password,"redbus")==0)
	{
		printf("\nCongratulations..!!\nPress enter to continue..\n");
		getch();
		system("cls");
		mainmenu();
	}
	else
	{
		printf("\nWrong Username or Password..!\nTo try again press enter.\n");
		getch();
		system("cls");
		security();
	}
	getch();
}

void addNewBusRoute()
{
int i;
FILE *fp;
fp=fopen("bus.txt","ab+");
struct checkpoint cp;
struct checkpoint *pptr;
pptr=&cp;
printf("Enter Bus route number\n");
scanf("%d",&pptr->no);
printf("Enter source\n");
scanf("%s",pptr->startpoint);
printf("Enter destination\n");
scanf("%s",pptr->endpoint);
fwrite(pptr,sizeof(*pptr),1,fp);
fclose(fp);
printf("Congratulations!!\nYour bus route is saved\n");
printf("\nDo you want to add more route?\n1.Yes\t\t\t2.No\n");
scanf("%d",&i);
switch(i)
{
	case 1:
		system("cls");
		addNewBusRoute();
		break;
	case 2:
		system("cls");
		mainmenu();
	default:
		system("cls");
		printf("Enter appropriate choice\n");
		addNewBusRoute();
	
}
}
void displayAllBusRoute()
{
	int i;
	int ch;
	FILE *fp1;
	struct checkpoint cp;
	struct checkpoint *pptr;
	pptr=&cp;
	fp1=fopen("bus.txt","rb+");
	
	    printf("Available Bus Routes are:\n");
	    printf("Route No.    Starting Point       Destination");
	    printf("\n----------------------------------------------------------\n");
	    while(fread(pptr,sizeof(*pptr),1,fp1))
	    {
	    	printf("%d               %s                 %s\n",pptr->no,pptr->startpoint,pptr->endpoint);
		}
		printf("\n1.Get directed to main menu.\n2.Book a ticket.\n3.Exit\n");
		printf("Enter your choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				system("cls");
				mainmenu();
				break;
			case 2:
				system("cls");
				bookTicket();
				break;
			case 3:
				exit(0);
			default:
				printf("\nEnter appropriate choice\n");
				displayAllBusRoute();
	}
    
    fclose(fp1);
}
void loadBuses()
{
	int i;
	FILE *fp;
	fp = fopen("busdetail.txt","ab+");
	struct bus bs;
	struct bus *ptr;
	ptr=&bs;
	printf("Enter bus number\n");
	scanf("%d",&ptr->busno);
	printf("Enter bus name\n");
	scanf("%s",ptr->busname);
	printf("Enter bus arrival time(hh:mm)\n");
	scanf("%s",ptr->arrtime);
	printf("Enter bus departure time(hh:mm)\n");
	scanf("%s",ptr->deptime);
	printf("Enter time duration\n");
	scanf("%s",ptr->duration);
	printf("Enter bus status(AC / Non-AC)\n");
	scanf("%s",ptr->status);
	printf("Enter bus fare\n");
	scanf("%d",&ptr->fare);	
    fwrite(ptr,sizeof(*ptr),1,fp);
    fclose(fp);
    printf("Congratulations!!\nYour bus details are saved\n");
    printf("\nDo you want to add more buses to the route?\n1.Yes\t\t\t2.No\n");
    scanf("%d",&i);
    switch(i)
    {
    	case 1:
    		system("cls");
    		loadBuses();
    	case 2:
    		system("cls");
    		mainmenu();
    	default:
    		system("cls");
    		printf("\nEnter appropriate choice");
    		loadBuses();
	}
}
void displayBuses()
{
	int i;
	int ch;
	FILE *fp1;
	struct bus bs;
	struct bus *ptr;
	ptr=&bs;
	fp1=fopen("busdetail.txt","rb+");
	
	    printf("Available Buses to the route are:\n\n");
	    printf("Bus No.  Bus Name       Arrival Time   Departure Time   Duration   Fare   Status--------------------------------------------------------------------------------\n");
        while(fread(ptr,sizeof(*ptr),1,fp1))
        {
    	printf(" %d       %s      %s          %s            %s      %d       %s\n",ptr->busno,ptr->busname,ptr->arrtime,ptr->deptime,ptr->duration,ptr->fare,ptr->status);
    	}
		printf("\n1.Get directed to main menu.\n2.Book a ticket.\n3.Exit\n");
		printf("Enter your choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				system("cls");
				mainmenu();
				break;
			case 2:
				system("cls");
				bookTicket();
				break;
			case 3:
				exit(0);
			default:
				printf("\nEnter appropriate choice\n");
				displayBuses();			
		}
}

void deleteDetails()
{
    FILE *fp;
    FILE *fpt;
    struct bus bs;
    int r,a;
    printf("Enter the Bus no you want to delete :");
    scanf("%d",&r);
    {
        fp=fopen("busdetail.txt","rb+");
        fpt=fopen("TempFile.txt","wb+");
        while(fread(&bs,sizeof(bus),1,fp))
        {
            a=bs.busno;
            if(a!=r)
            fwrite(&bs,sizeof(bus),1,fpt);
        }
        fclose(fp);
        fclose(fpt);
        fp=fopen("busdetail.txt","wb+");
        fpt=fopen("TempFile.txt","rb+");
        while(fread(&bs,sizeof(bus),1,fpt))
        fwrite(&bs,sizeof(bus),1,fp);
        printf("\nRECORD DELETE\n");
    }
    fclose(fp);
    fclose(fpt);
}

/*void updateDetails()
{
	struct bus bs;
    FILE *fpt;
    FILE *fpo;
    int s,r,ch;
    printf("enter bus number to update");
    scanf("%d",&r);
     {
        fpo=fopen("busdetail.txt","r");
        fpt=fopen("TempFile1.txt","w");
        while(fread(&bs,sizeof(bus),1,fpo))
          {
            s=bs.busno;
            if(s!=r)
            fwrite(&bs,sizeof(bus),1,fpt);
            else
             {
                printf("\n\t1_UPDATE THE NAME OF ROLL NUMBER %d",r);
                printf("\n\t1_UPDATE THE MARK OF ROLL NUMBER %d",r);
                printf("\n\t1_UPDATE BOTH NAME  AND MARK OF ROLL NUMBER %d",r);
                PRINTF("\N\N eNTER YOUR CHOICE");
                scanf("%d",&ch);
                switch(ch)
                {
                    case 1:
                    printf("Enter Name : ");
                    scanf("%d",stud.name);
    `                break;
                    case 2:
                    printf("Enter Mark : ");
                    scanf("%d",&stud.mark);
                    break;
                    case 3:
                    printf("Enter Name and Mark: ");
                    scanf("%d",stud.name,&stud.mark );
                    break;
                    default:
                    printf("Invalid Selection");
                    break;
                }
                fwrite(&stud,sizeof(stud),1,fpt);
            }
        }    
        fclose(fpo);
        fclose(fpt);
        fpo=fopen("Record","w");
        fpt=fopen("TempFile","r");
        while(fread(&stud,sizeof(stud),1,fpt))
        {
            fwrite(&stud,sizeof(stud),1,fpo);
        }
        fclose(fpo);
        fclose(fpt);
        printf("RECORD UPDATED");
    }
}*/

void loadSeats()
{
	system("cls");
	int i,f;
    int ch;
	FILE *fp1;
	struct bus bs;
	struct bus *ptr;
    ptr=&bs;
    fp1=fopen("busdetail.txt","rb+");

    printf("Available Buses to the route are:\n");
    printf("Bus No.  Bus Name       Arrival Time   Departure Time   Duration   Fare   Status\n--------------------------------------------------------------------------------\n");
    while(fread(ptr,sizeof(*ptr),1,fp1))
    {
    	printf(" %d       %s      %s          %s            %s      %d       %s\n",ptr->busno,ptr->busname,ptr->arrtime,ptr->deptime,ptr->duration,ptr->fare,ptr->status);
	}
	printf("Which bus would you like to load seats to(Enter Bus no.)\n");
	scanf("%d",&f);
		
	switch(f)
	{
		case 1:
			loadMahalaxmiSeats();
			break;
		case 3:
			//saraswati();
			break;
		default:
			printf("Select correct option\n");
			loadSeats();				
	}
}

void bookTicket()
{
	char source[10],des[10];
	printf("\t\t Book a Ticket \t");
	int i;
	int ch;
	FILE *fp1;
	struct checkpoint cp;
	struct checkpoint *pptr;
	pptr=&cp;
	fp1=fopen("bus.txt","r");
	
	    printf("Available Bus Routes are:\n");
	    while(fread(pptr,sizeof(*pptr),1,fp1))
	    {
	    	printf("%d  %s  %s\n",pptr->no,pptr->startpoint,pptr->endpoint);
		}
	printf("\nEnter source\n");
	scanf("%s",source);
	printf("\nEnter destination\n");
	scanf("%s",des);
	if((strcmp(source,"jaipur")==0||strcmp(source,"jpr")==0||strcmp(source,"Jaipur")==0) && (strcmp(des,"Delhi")==0||strcmp(des,"delhi")==0||strcmp(des,"dlh")==0))
	{
		system("cls");
		int i,f;
	    int ch;
	    FILE *fp1;
	    struct bus bs;
	    struct bus *ptr;
	    ptr=&bs;
	    fp1=fopen("busdetail.txt","rb+");
	
	    printf("Available Buses to the route are:\n");
	    printf("Bus No.  Bus Name       Arrival Time   Departure Time   Duration   Fare   Status\n--------------------------------------------------------------------------------\n");
	    while(fread(ptr,sizeof(*ptr),1,fp1))
	    {
	    	printf(" %d       %s      %s          %s            %s      %d       %s\n",ptr->busno,ptr->busname,ptr->arrtime,ptr->deptime,ptr->duration,ptr->fare,ptr->status);
		}
		
		printf("Which bus would you like to select(Enter Bus no.)\n");
		scanf("%d",&f);
		
		switch(f)
		{
			case 1:
				mahalaxmi();
				break;
			case 3:
				//saraswati();
				break;
			default:
				printf("Select correct option\n");
				bookTicket();
				
		}
		
		
	}
	else
	{
		system("cls");
		printf("\n No available buses to this route.");
		mainmenu();
	}
}

void mainmenu()
{
	system("color 3f");
	int j;
	printf("\n\n\t\t\tREDBUS.IN\n");
	printf("\t\t\tMY BUS....My seat\n");
	printf("1.Add new bus route\n");
	printf("2.See all available bus route\n");
	printf("3.Load buses to the route (Jpr to Delhi)\n");
	printf("4.See buses to the route (Jpr to Delhi)\n");
//	printf("5.Update Bus\n");
	printf("5.Delete Bus to the route.\n");
	printf("6.Load seats to the bus\n");
	printf("7.Book a ticket\n");
	printf("8.Exit\n");
	printf("Enter your choice\n");
	scanf("%d",&j);
	system("cls");
	system("color 1F");
	switch(j)
	{
		case 1:
			addNewBusRoute();
			break;
		case 2:
			displayAllBusRoute();
			break;
		case 3:
			loadBuses();
			break;
		case 4:
			displayBuses();
			break;
		//case 5:
			//updateDetails();
			break;
		case 5:
			deleteDetails();
			break;
		case 6:
			//system("color 1a");
			loadSeats();
			break;
		case 7:
			bookTicket();
			break;
		case 8:
			exit(0);
			break;
		default:
			system("cls");
			mainmenu();
				
	}
}
int main()
{
	system("color 80");
	security();
	mainmenu();
	return(0);
}
