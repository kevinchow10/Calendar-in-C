#include "calendarFunction.h"


int main(int argc, char *argv[]) 
{
	
	loadEvent(textFilename); //Read all events and load to memory
	

/*
	char* myDate="01-09-2018";
	int i,count;
	
	char** ZZZ= getAllEvent(myDate,&count);  // WATCH THIS how to get the returned value from a pointer parameter.
	
	printf("%d\n",count);
	
	for (i=0; i<=count; i++)
	{
		printf("a fine string that says: %s", ZZZ[i]);
	}
	//return 0;
	
	
  	
  	
  	/*
  	for (int i=0;i<sizeof(*ZZZ);i++)
	{
		if (strlen(ZZZ[i])>2)
		{
			printf("a fine string that says: %s", *ZZZ);
			ZZZ++;
		}
		
	}
	*/
	
//	return 0;
	
	/*
	//test if There is event for specific date
	char* myDate="01-09-2018";
	int z= isEventExist(myDate);
	return 0;
	
	//char* myDate="01-09-2018";
	char* myEventName="Test Event";
	
	insertEvent(myDate,myEventName);
	return 0;
	*/
	
	
	char opt;
	time_t raw_time = time(NULL);
	struct tm *current_time = localtime(&raw_time);
	
	date.dd = 1;
	date.mm = current_time->tm_mon + 1;
	date.yy = current_time->tm_year + 1900;
	date.strDate= (char*) malloc(10 * sizeof (char));
	toString(date.dd,date.mm,date.yy, date.strDate);
	
	//int z= isEventExist1();
	
	//char str[100] = "5;12-10-2018;Ke dokter mata";
	//char tem[100];
	//getToken(str, ";", 2, tem);
	//printf("%s", tem);
	
	//int n = highlightDays(date.dd, date.mm, date.yy);
	//printf("Month: ");
	//printMonth(date.mm);
	
	printf("\t\t===============================================\n");
	printf("\t\t=========== WELCOME TO OUR CALENDAR ===========\n");
	printf("\t\t===============================================\n");
	 
	printf("\n\nInstruction: \n");
	printf("[1] This program is used to shows the calendar\n");
	printf("[2] You can modify the schedule on the calendar by adding or deleting the schedule\n");
	printf("[3] Then, the date that inserted by your schedule will be highlighted on the calendar\n\n\n");
	 
	system("pause");
	
	while(1)
	{
		system("cls");
		showCalendar();
		printOptions();
		
		opt = getch();
		//scanf("%c", &opt);
		if(opt == 'n' || opt == 'N')
		{
			nextMonth();
		}
		else if(opt == 'p' || opt == 'P')
		{
			previousMonth();
		}
		else if(opt == 'g' || opt == 'G')
		{
			gotoDate();
		}
		else if(opt == 's' || opt == 'S')
		{
			printEvent();
		}
		else if(opt == 'i' || opt == 'I')
		{
			insertEvent();
		}
		else if(opt == 'd' || opt == 'D')
		{
			deleteEvent();
		}
		else if(opt == 'e' || opt == 'E')
		{
			system("cls");
			//writeFile();
		}
		else if(opt == 'q' || opt == 'Q')
		{
			return 0;
		}
		else
		{
			printf("\n\t\t Please type in one of the options.");
		}
	}
	return 0;
}
