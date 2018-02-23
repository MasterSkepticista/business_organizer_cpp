#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<iomanip.h>
#include<stdlib.h>
#include<stdio.h>
#include<dos.h>
#include"contacts.cpp"
void handler(int c);
void calc();
void notes();
void planner();
void validator();
struct meetings
{	char desc[255];
	int d,m,y;
	public:

	void getinfo()
	{

		cout<<"\nWe've set a reminder for:"<<d<<"-"<<m<<"-"<<y;
		cout<<"\nGive it a note:"<<endl;
		gets(desc);
		cout<<"\nThat's what we have saved\n";
      cout<<"\n\t---------------------------------------------\n";
		disp();
      cout<<"\t---------------------------------------------";
	}
	void disp()
	{

		cout<<'\t'<<d<<"-"<<m<<"-"<<y<<"\t"<<desc<<endl;

	}

};
meetings m;
fstream f;
int notifs=0;
void disp()
{

	f.seekg(0);
	while(f.read((char*)&m,sizeof(m)))
	m.disp();

	f.close();
}

void main()
{
	f.open("tasks.dat",ios::out|ios::in|ios::binary);
	clrscr();
	int choice;
	struct date d;
	struct  time t;

	gettime(&t);
	getdate(&d);

	f.close();
	f.open("tasks.dat",ios::in|ios::out|ios::app|ios::binary);
	printf("C++ Business Organizer                                                   %2d:%02d",t.ti_hour, t.ti_min);
	cout<<"\n------------------------------------------------------------------------------";

	cout<<"\n\t1.Contacts";
	cout<<"\n\t2.Notes";
	cout<<"\n\t3.Calculator";
	cout<<"\n\t4.Planner";
	cout<<"\n\t5.Settings";
	cout<<"\n\t6.Exit ";
	cout<<"\n\nNotification(s) and/or reminder(s)"<<endl;
	cout<<"\n\t------------ ----------------------------------------";
	cout<<"\n\t   Date\t\t\tScheduled task"<<endl;
	cout<<"\t------------ ----------------------------------------\n";
	disp();
	cout<<"\nOk, you may enter your command here>";
	cin>>choice;
	f.open("tasks.dat",ios::in|ios::out|ios::app|ios::binary);
	handler(choice);

}
void settings()
{
	int x,y;
	clrscr();
	cout<<setw(40)<<"Settings"<<endl;
	cout<<setw(40)<<"--------";
	cout<<"\n\t\t\t1.Factory reset/ Wipe data";
	cout<<"\n\t\t\t2.About this firmware";
	cout<<"\n\t\t\t3.Exit settings\n";
	cout<<"\n\n\n\t\t\t>";
	cin>>x;
	switch(x)
	{
		case 1: clrscr();
			cout<<setw(40)<<"Security"<<endl;
			cout<<setw(40)<<"--------"<<endl;
			cout<<"\nWelcome to data management wizard!";
			cout<<"\nThis method wipes ALL your data. To manage app data individually, check the individual app settings.";
			cout<<"\nEnter the password to delete, or else will exit. This will remove ALL your data.\nCaution! This can NOT be reverted!> ";
			cin>>y;
			if(y==1698)
			{	clrscr();
				cout<<"\nDeleting data, please hold on...";
				delay(500);
				cout<<"\n\t-Deleted contacts...";
				remove("contact.dat");
				delay(500);
				cout<<"\n\t-Removed notes...";
				remove("notes.txt");
				delay(500);
				cout<<"\n\t-Removed reminders...";
				remove("tasks.dat");
				delay(1000);
				cout<<"\n\tWipe complete, rebooting PDA...";
				delay(1500);
				main();
			}
			break;
		case 2: clrscr();
			cout<<"\n\t\tBOSS-Business Organiser Scheduling System";
			cout<<"\n\t\tVersion 1.0 (Development discontinued)";
			getch();
			settings();
			break;
		case 3:main();
	}
}
void handler(int c)
{
	switch(c)
	{
		case 1:home();main();
		case 2:notes();break;
		case 3:calc();break;
		case 4:planner();break;
		case 5:settings();break;
		case 6:exit(0);
	default:clrscr();cout<<"\nWe didn't get you. Please retry!";
	}
}
void validator()
{

	struct date d;
	struct  time t;

	gettime(&t);
	getdate(&d);
	int dd,mm,yyyy;
	int flag=0;
	cout<<"\nToday is ";
	printf("%d",d.da_day);
	printf(": %d", d.da_mon);
	printf(": %d", d.da_year);
	cout<<" ,in case you need it.";
	cout<<"\nEvent day (dd mm yyyy)>";
	cin>>dd>>mm>>yyyy;
	int m_31[7]={1,3,5,7,8,10,12};
	int m_30[4]={4,6,9,11};
	int y_trig=d.da_year;
	//Search for month, is it valid?
	for(int i=0;i<7;i++)
	{

		if((mm==m_31[i])&&dd<=31)
			flag=1;
		else
		if((mm==m_30[i])&&dd<=30)
			flag=1;
		else if((mm==2)&&dd<=29)
		     flag=1;
	}
	if(((yyyy>y_trig)&&(flag==1)))
	{
		cout<<"Date verification complete.";
		m.d=dd;
		m.m=mm;
		m.y=yyyy;
	}
	if(flag==0)
	{	cout<<"\nThe date is invalid!"<<endl;
		cout<<"\n\t\t\tPossible causes:";
		cout<<"\n\t->You entered a year which has already passed.";
		cout<<"\n\t->You entered a day which doesn't exist in the month,e.g. 30th Feb";
		cout<<"\n\t->You did not enter the date as per the format DD-MM-YYYY"<<endl;
		getch();
		planner();
	}


}
//beginning notes app--------------------------------------------------------------------------------------------------------------------------
void notes()
{
	char ch;
	char conf='N';
	ofstream fout;
	clrscr();
//***************************************statusbar************
	struct date d;

	getdate(&d);
	printf("Notes                                                        Today %d", d.da_day);
	printf(": %d", d.da_mon);
	printf(": %d", d.da_year);
//****************************************endstat*************

	fstream fin;
	fin.open("notes.txt",ios::in);
	cout<<"\n\nHere's what you noted recently:\n";
	cout<<"________________________________________________________________________________\n ";

   while(fin)
   {	fin.get(ch);
	cout<<ch;
   }

	fin.close();
	cout<<"\n________________________________________________________________________________";
	cout<<"\n+ Rewrite(Y)\t x Delete(D)\t < Back(B)\nWhat next?:";

	cin>>conf;
	clrscr();
	if(toupper(conf)=='Y')
	{
		fout.open("notes.txt");
		cout<<"\nGet started below and remember to end with '#'!:\n_____________________________________________________________\n";
		do{
			ch=getchar();
			if(ch!='#')
			fout.put(ch);
		}while(ch!='#');

		cout<<"\nNote saved!";
		fout.close();
	cout<<"\n_____________________________________________________________\nDone! Press any character to get back to main menu.";
	getch();main();
	}
	else if(toupper(conf)=='D')
		{       char reply='N';
			cout<<"\nSure about that? [Y/N]:";
	 cin>>reply;
			if(toupper(reply)=='Y')
			  {	remove("notes.txt");
			notes();
	   }

			else
				notes();
		}
	else if(toupper(conf)=='B')
		main();

	else
	      {	cout<<"\nWe couldn't find any action for that!";
		getch();
		notes();
	      }
	getch();
}
//beginning the scheduler app-----------------------------------------------------------------------------------------------------------------
void planner()
{

	char response;
	char ans='Y';
	clrscr();
//***************************************statusbar************
	struct date d;

	getdate(&d);
	printf("Today %d", d.da_day);
	printf(": %d", d.da_mon);
	printf(": %d", d.da_year);
//****************************************endstat*************
	cout<<endl;
	cout<<setw(42)<<"Planner "<<endl;
	cout<<setw(42)<<"-------";
	cout<<"\n\n\t->To add tasks enter 'A':\n\n\t->To add a quick reminder for today, enter 'T':\n\n\t->To clear all tasks enter the password:";
	cout<<"\n\n\n\nHappy to help:";
	cin>>response;
	clrscr();
	if(toupper(response)=='A')
	{

		do{     clrscr();
			validator();
			m.getinfo();
			f.write((char*)&m,sizeof(m));
			cout<<"\nAdd more tasks?[Y/N]:";
			cin>>ans;
			cout<<"\n+------------------------------------------------+";
		}while(toupper(ans)=='Y');

	}
	if(toupper(response)=='T')
	{	m.d=d.da_day;
		m.m=d.da_mon;
		m.y=d.da_year;
		cout<<"\nToday's tasklist has been set, give it a title.\n";
		cout<<"-------------------------------------------------------\n>";
		gets(m.desc);
		f.write((char*)&m,sizeof(m));
		cout<<"\n-------------------------------------------------------\nAll set! Tap any key to continue...";
		getch();
		main();
	}
	else if(response=='~')
	{       delay(1000);
	      remove("tasks.dat");
		cout<<"\nWiping data...";
		delay(500);
		cout<<"\nRemoved all reminders.";
		getch();
	      }
	main();

}
void calc()
{       clrscr();
    float r,n,m;
	char o;
	cout<<setw(43)<<"Calculator"<<endl;
	cout<<setw(43)<<"----------";
	cout<<"\nEnter your expression as shown below";
	cout<<"\nExample: "<<3<<" space "<<'+'<<" space "<<5;
	cout<<"\nLets get started!!";
	cout<<"\n\n\t\t\t";
	cout<<"------------------"<<endl;
	cout<<"\t\t\t";
	cin>>n>>o>>m;
	switch(o)
	{
		case '+':	r=n+m;
				break;
		case '-':       if(n>m)
					r=n-m;
				else if(m>n)
					r=m-n;
				break;
		case '*':	r=n*m;
				break;
		case '/':	if(m)
					r=n/m;
				else
					cout<<"\nInfinity";

				break;
	}

	cout<<"\t\t\t"<<'='<<r<<endl;
	cout<<setw(42)<<"------------------";
	char resp='C';
	cout<<"\nContinue or exit? (E to exit, C to continue>";
	cin>>resp;
	if(toupper(resp)=='E')
		main();
	else
		calc();
}
