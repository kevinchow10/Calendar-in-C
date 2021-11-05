#ifndef calendarFunction
#define calendarFunction

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <rlutil.h>
#include <windows.h> 
#include <time.h>
#include <math.h>


/*
References:
https://www.geeksforgeeks.org/find-day-of-the-week-for-a-given-date/
https://www.codewithc.com/mini-project-in-c-calendar/
https://bytes.com/topic/c/answers/220599-ldom-last-day-month
https://stackoverflow.com/questions/24696113/how-to-find-text-between-two-strings-in-c
*/
struct Date{
    int dd;
    int mm;
    int yy;
    char* strDate; //default string for date is dd-mm-yyyy => 10 chars
};
struct Date date;

const char textFilename[]="event.txt";
int totalEvent=0;
char* eventLine[100];

int isValidDate(int dd, int mm, int yy);
void loadEvent(const char *filename);
void toString(int dd, int mm, int yy,char* strDate);
int isEventExist(int dd, int mm, int yy);
void getToken(char* str, char* seperator, int tok, char* ret);
char** getAllEvent(int dd, int mm, int yy, int* n);
void insertEvent();
void printEvent(); // print all events for a certain date.
void deleteEvent();
void gotoDate();

int dayofweek(int d, int m, int y);
void showCalendar();
int lastdayofMonth(int month, int year);
int is_leap(int year);
char* getMonthName(int month);
void printOptions();
void nextMonth();
void previousMonth();
void SetColor(int ForgC);
void ClearColor();

int isValidDate(int dd, int mm, int yy) 
{ 
        int ret=0; 
        int maxDate = lastdayofMonth(mm,yy); 
        if (is_leap(yy)) 
                maxDate++; 
        
        if (dd>=1 && dd<=maxDate) 
                if (mm>=1 && mm<=12) 
                        if (yy>=1970 && yy<=2040) 
                        ret=1; 
        
        return ret; 
} 

int dayofweek(int d, int m, int y) 
{ 
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
    y -= m < 3; 
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7; 
} 

void printDate(int dd, int mm, int yy) 
//Print the date with MAGENTA if there is event on that date, otherwise print with normal color GREY
{
	if(isEventExist(dd, mm, yy)==1)
	{
		SetColor(13); // Color = LIGHT MAGENTA
		printf("%d", dd);
		SetColor(8);
	}
	else
	{
		SetColor(8); //normal Color = GREY
		printf("%d", dd);
	}
}

int inputDate(char* strDate) 
{
	printf("----------------------------------\n"); 
    int ok=0; 
     
    int dd; 
    while (ok!=1) 
    { 
        printf("Please enter the date (1 - %d) or C to cancel. : ",lastdayofMonth(date.mm,date.yy)); //input Date only, without month and year. To display the event on that particular date.
        scanf("%s",strDate); 
        if (strcmp(strDate,"c")==0 || strcmp(strDate,"C")==0) 
            return 0; 
        
        dd= atoi(strDate); 
        ok= isValidDate(dd,date.mm,date.yy); 
    } 
    
    toString(dd,date.mm,date.yy,strDate);
    return 1;
}

void printEvent() // print all events for a certain date.
{
	char strDate[10]; 
	if (inputDate(strDate)!=1) return;
	
	printf("------------------------------------------------------\n");
	printf("-- EVENTS ON DATE: ");
	SetColor(13); printf("%s\n",strDate); SetColor(8);
	printf("-- EVENT ID\t\tEVENT NAME -----\n");
	printf("------------------------------------------------------\n");
	
    char strEventID[2];
    char strEventName[100];
    
    int i;
    for (i=0; i<= totalEvent; i++) 
    { 
        if (strstr(eventLine[i],strDate)!=NULL) 
        { 
            getToken(eventLine[i],";",1,strEventID); 
            getToken(eventLine[i],";",3,strEventName); 
            printf("\t%s\t\t%s",strEventID,strEventName); 
        } 
    } 
	printf("------------------------------------------------------\n"); 
	system("pause");
}

void showCalendar()
{
	SetColor(7);
	printf("\n\n\n       EVENT CALENDAR");
	SetColor(8);
	printf("\t\t\t\t\t\t\t\tby Alfian Nurshadiq / 1706018896\n");
	printf("\t\t\t\t\t\t\t\t\t\t   Kevin / 1706064694\n\n\n\n");
	SetColor(13);
	printf("\n\t\t      %s, %d", getMonthName(date.mm), date.yy);
	SetColor(8);
	printf("\n\t\t--------------------------\n");
	printf("\t\tS   M   T   W   T   F   S   ");
	printf("\n\t\t--------------------------\n");
	
	int day = dayofweek(date.dd, date.mm, date.yy);
	int lastDay = lastdayofMonth(date.mm, date.yy);
	//printf("%d, %d", lastDay, day);
	
	int i = 1, j;
	
	while (i <= lastDay)
	{
		if(i == 1)
		{
			printf("\t\t");
			for(j = 0; j < day; j++)
			{
				printf("    ");
			}
			
			for(j = 0; j < 7 - day; j++)
			{
			
				printDate(i,date.mm,date.yy);
				//ClearColor();
				printf("   ");
				i++;
			}
			
			printf("\n\t\t");
		}
		
		for(j = 0; j < 7; j++)
		{
			if(i > lastDay)
			{
				//printf("        last i: %d", i);
				break;
			}
				
			if(i < 10)
			{
				printDate(i,date.mm,date.yy);
				printf("   ");
				//printf("%d   ", i);
			}
			
			else
			{
				printDate(i,date.mm,date.yy);
				printf("  ");
				//printf("%d  ", i);
			}
				
			i++;
		}
		printf("\n\t\t");
	}
	
}

int lastdayofMonth(int month, int year)
{
	int ndays[] = {-1,31,28,31,30,31,30,31,31,30,31,30,31};
	int ret = ndays[month];
	if(is_leap(year) && month == 2)
	ret++;
	return ret;
}

int is_leap(int year)
{
	if (year%400 == 0) // Exactly divisible by 400 e.g. 1600, 2000
    	return 1;
  	else if (year%100 == 0) // Exactly divisible by 100 and not by 400 e.g. 1900, 2100
    	return 0;
  	else if (year%4 == 0) // Exactly divisible by 4 and neither by 100 nor 400 e.g. 2016, 2020
    	return 1;
  	else // Not divisible by 4 or 100 or 400 e.g. 2017, 2018, 2019
   		return 0;  
}

char* getMonthName(int month)
{
	const char * months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	
	return  (char*) months[month - 1];
}

void printOptions()
{
	printf("\n\t\t Press 'N' to view next month.\n");
	printf("\t\t Press 'P' to view previous month.\n");
	printf("\t\t Press 'G' to go to specific month calendar.\n");
	printf("\t\t Press 'S' to show event(s) for a specific date.\n");
	printf("\t\t Press 'I' to insert a new Event.\n");
	printf("\t\t Press 'D' to delete event of specified ID.\n");
	//printf("\t\t Press 'S' to go to a certain date.\n");
	printf("\t\t Press 'Q' to quit the program.\n");
}

void nextMonth()
{
	if(date.mm == 12)
	{
		date.mm = 1;
		date.yy	+= 1;
	}
	else
		date.mm += 1;
	
	system("cls");
	//printMonth(date.mm);
	showCalendar();
}

void previousMonth()
{
	if(date.mm == 1)
	{
		date.mm = 12;
		date.yy	-= 1;
	}
	else
		date.mm -= 1;
	
	system("cls");
	//printMonth(date.mm);
	showCalendar();
}

void SetColor(int ForgC)
{
     WORD wColor;
     //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearColor(){
    SetColor(15);
}


void getToken(char* str, char* separator, int tok, char* ret)
{
	int tok1 = tok;
	char strLocal[100];
	char *token;
	
	if (strlen(str)<=2) //avoid invalid string to split
	{
		ret= "";
		return;
	}
	
	strcpy(strLocal, str); //save the parameter str, not to be cut by strtok()
	
	token = strtok(strLocal, separator);
	if (tok==1)
	{
		strcpy(ret,token);
		return;
	}
	
	token = strtok(NULL, separator);
	if (tok==2)
	{
		strcpy(ret,token);
		return;
	}
	
	token = strtok(NULL, separator);
	if (tok==3)
	{
		strcpy(ret,token);
		return;
	}
	
}

char** getAllEvent(int dd, int mm, int yy, int* nn)
{
	FILE *fp;
    char line[100];
    char ** ret= (char**) malloc(sizeof(char*) *5); //max event name is 5 for the same date

    char sEventName[100];// length of event name max 100
    char sDate[11];
    
    int i=0;
   	while (fgets(line,100, fp)!=NULL)
   	{
   		if (strlen(line)>=2)  //avoid invalid string to split
   		{
   			getToken(line,";",2,sDate);
   			if (strcmp(sDate,date.strDate)==0) //if same date
   			{
   				getToken(line,";",3,sEventName);
   				ret[i]= (char *) malloc(sizeof(char) * strlen(sEventName)); //max length of event name is 100 chars
   				strcpy(ret[i++],sEventName);
			}
		}
   		
	}
	fclose(fp);
	i--;
	*nn = i; // WHOOIIII ... this is how to return the value to the pointer argument
	
	return ret;
}

void loadEvent(const char *filename)
{
	FILE *fp;
    char line[100];

    fp =fopen(filename,"r");  //open file for read only
    int i=0;
    while (fgets(line,100, fp)!=NULL)
   	{
   		if (strlen(line)>=2) //avoid invalid string to split
   		{
   			eventLine[i]= (char*) malloc(sizeof(char) * strlen(line));
   			strcpy(eventLine[i++],line);
   			//eventLine[i++]= line;
		}
	}
	totalEvent= --i;
	fclose(fp);
}

void toString(int dd, int mm, int yy,char* strDate)
{
	char* ret;
	char temp[4];
	
	ret= (char*) malloc(10 * sizeof (char));
	sprintf(temp,"%02d-",dd);
	strcpy(ret,temp);
	sprintf(temp,"%02d-",mm);
	strcat(ret,temp);
	sprintf(temp,"%d",yy);
	strcat(ret,temp);
	
	//sprintf(date.strDate,"%10s",ret);
	sprintf(strDate,"%10s",ret);
	//free(ret); //now you can release the memory - why fail
}

int isEventExist(int dd, int mm, int yy)
{
    int i, ret=0;
    char strDate[10];
    
	toString(dd,mm,yy,strDate);
    
	for (i=0; i<=totalEvent;i++)
   	{
   		if (strlen(eventLine[i])>=2) //avoid invalid string to split
   		{
	   		if (strstr(eventLine[i],strDate)!=NULL)
	   		{
	   			ret= 1;
			}
		}
	}
	
	return ret;
}

int inputNewEvent(char* strDate, char* newEventName)    
{
	printf("----------------------------------\n"); 
    int ok=0; 
    while (ok!=1) 
    { 
            printf("Please enter the date (dd-mm-yyyy)  or C to cancel. : "); 
            scanf("%s",strDate);
            if (strcmp(strDate,"c")==0 || strcmp(strDate,"C")==0) 
                    return 0; 
            
            printf("Please enter the Event Name : "); 
            scanf("%s",newEventName); 
            
            char temp[4];
            getToken(strDate,"-",1,temp);
            int date= atoi(temp);
			getToken(strDate,"-",2,temp); 
            int month= atoi(temp); 
            getToken(strDate,"-",3,temp);
            int year= atoi(temp); 
            ok= isValidDate(date,month,year); 
    } 
    return 1;
}

void insertEvent()
{
	char strDate[10], newEventName[100];
	if (inputNewEvent(strDate,newEventName)!=1) return;
	
    int max=0; 
    int iEventID=0;
    char sEventID[4];
    int i;
    
    //get the maximum number of event ID.
   	for (i=0;i<=totalEvent;i++)
   	{
   		if (strlen(eventLine[i])>0)
   		{
   			getToken(eventLine[i],";",1,sEventID);
	   		iEventID= atoi(sEventID);
	   		if (iEventID>max)
   				max= iEventID;
		}
   		
	}
	
	//after this line max is the maximum eventID
	
	//Build the line to be inserted
	char lineInsert[100];
	sprintf(lineInsert,"%d",++max); //add 1 to Max as the new Event ID.
	strcat(lineInsert,";");
	strcat(lineInsert,strDate);
	strcat(lineInsert,";");
	strcat(lineInsert,newEventName);
	
	FILE *fp;
	fp =fopen(textFilename,"a");   //open file for append (adding new line in the last row)
	fprintf(fp,"%s\n", lineInsert);
	fclose(fp);
	printf("New event has been registered.\n");
	printf("--------------------------------------\n");
	system("pause");
	
	loadEvent(textFilename); //refresh the event list in the memory, to reflect this change.
}

int isNumeric(char* str) 
{ 
        int ret=1; 
        int i; 
        for (i=0; i<strlen(str); i++) 
            if (isdigit(str[i])==0) // is alpha? 
            { 
                ret = 0; 
                break; 
            } 
        return ret; 
} 

int inputEventID(char* sEventIdToDelete)
{
    printf("------------------------------------\n"); 
    int ok=0; 
    while (isNumeric(sEventIdToDelete)!=1) 
    { 
        printf("Please enter Event ID to delete. : "); 
        scanf("%s",sEventIdToDelete);
        if (strcmp(sEventIdToDelete,"c")==0 || strcmp(sEventIdToDelete,"C")==0) 
            return 0; 
    } 
   
    return 1;
}

void deleteEvent() 
{ 
	char sEventIdToDelete[4];
	if (inputEventID(sEventIdToDelete)!=1) return;

    int i;
    char* eventID;
    for (i=0; i<= totalEvent; i++) 
    { 
        getToken(eventLine[i],";",1,eventID); 
        if (strcmp(sEventIdToDelete,eventID)==0) 
        { 
            eventLine[i]="--DELETED--\n"; 
            break; 
        } 
    } 
    
    //Create new file with the same name, except the --DELETED-- line
    FILE *fp;
    int ret= remove(textFilename); //but first delete the file.
    if (ret!=0) 
    { 
        printf("Failed to delete event.\n"); //just report Event to delete event
        printf("=========================================================\n");
        return;
    } 
    else 
    { 
	    int i; 
	    fp= fopen(textFilename,"w"); 
	    for (i=0; i<=totalEvent; i++) 
            if (eventLine[i]!="--DELETED--\n") 
            { 
                    fprintf(fp,"%s",eventLine[i]);
            } 
    } 
    fclose(fp); 
    
    printf("\nEvent no. %s is succesfully deleted.\n",sEventIdToDelete); //just report Event to delete event
    printf("=========================================================\n");
    system("pause");
}

 

void gotoDate() 
{ 
    char strDate[10];
	char temp[4]; 
	int ok=0;
    
    printf("-----------------------------------\n");
    while(ok!=1)
    {
	 	printf("Please enter the date (dd-mm-yyyy)  or C to cancel. : "); 
        scanf("%s",strDate);
        if (strcmp(strDate,"c")==0 || strcmp(strDate,"C")==0) 
        {
        	time_t raw_time = time(NULL);
			struct tm *current_time = localtime(&raw_time);
			
			date.dd = 1;
			date.mm = current_time->tm_mon + 1;
			date.yy = current_time->tm_year + 1900;
			return;
		}
         
	    getToken(strDate,"-",1,temp); 
	    date.dd = atoi(temp); 
	    getToken(strDate,"-",2,temp); 
	    date.mm = atoi(temp); 
	    getToken(strDate,"-",3,temp); 
	    date.yy = atoi(temp);
	    ok= isValidDate(date.dd,date.mm,date.yy)==1 ? 1 : 0;
	}
    
    system("cls");
    showCalendar(); 
} 

#endif
