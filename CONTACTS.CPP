#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
class contact
{
	public:
	long pno;
	char nm[50];
	char addr[50];
	void enter()
	{
		cout<<"\nEnter phone no.: ";
		cin>>pno;
		if(pno==0)
			return;
		cout<<"\nEnter name: ";
		cin>>nm;
		cout<<"\nEnter email address: ";
		cin>>addr;
	}
	void disp()
	{
		cout<<'\t'<<pno<<'\t'<<'\t'<<nm<<'\t'<<'\t'<<addr<<'\n';
	}
	void read_det()
	{
		cout<<"\nEnter name: ";
		cin>>nm;
		cout<<"\nEnter address: ";
		cin>>addr;
	}
	long getphoneno()
	{
		return pno;
	}
};	//end of class
fstream file;	//creating file object
//search
void search(long pno)
{
	contact c;
	int flag=0;
	file.seekg(0);
	while(file.read((char*)&c,sizeof(c)))
	{
		if(pno==c.getphoneno())
		{
			cout<<"\nContact details are as follows: "<<endl;
			cout<<"\n\t---------------------------------------------------------";
			cout<<"\n\tNumber\t\t\tName\t\tEmail";
			cout<<"\n\t---------------------------------------------------------";
			cout<<endl;
			c.disp();
			cout<<"\n\n\nPress any key to continue: ";
			flag=1;
			getch();
			break;
		}
	}
	if(flag==0)
		cout<<"\n\nContact doesn't exist";
	getch();
}
//insert
void insert(contact c)
{
	file.write((char*)&c,sizeof(c));
}
//delete
void del(long p)
{
	int fl=0;
	char conf='n';
	fstream ftmp("temp.dat",ios::in|ios::out|ios::binary);
	file.seekg(0);
	contact c;
	while(file.read((char*)&c,sizeof(c)))
	{
		if(p==c.getphoneno())
		{       cout<<"\n\t---------------------------------------------------------";
			cout<<"\n\tNumber\t\t\tName\t\tEmail";
			cout<<"\n\t---------------------------------------------------------\n";
			c.disp();
			fl=1;
			cout<<"\nAre you sure? (Y/N): ";
			cin>>conf;
			if(conf=='n')
				ftmp.write((char*)&c,sizeof(c));
		}
		else
			ftmp.write((char*)&c,sizeof(c));
	}
	if(fl==0)
		cout<<"\nContact does not exist.\n";
	file.close();
	ftmp.close();
	remove("contact.dat");
	rename("temp.dat","contact.dat");
}
//modify
void modify(long p)
{
	contact c;
	int ptr=0;
	int flag=0;
	file.seekg(0);
	while(file.read((char*)&c,sizeof(c)))
	{
		if(p==c.getphoneno())
		{
			cout<<"\nContact details are as follows: "<<endl;
			ptr=file.tellg();
			c.disp();
			cout<<"\n\n\nPress any key to continue: ";
			flag=1;
			c.read_det();
			file.seekp(ptr-sizeof(c));
			file.write((char*)&c,sizeof(c));
			getch();
			break;
		}
	}
	if(flag==0)
	{
		cout<<"\n\nContact doesnot exist";
		getch();
	}
}
//disp
void disp1()
{
	contact c;
	file.seekg(0);
	cout<<"\n\t---------------------------------------------------------";
	cout<<"\n\tNumber\t\t\tName\t\tEmail";
	cout<<"\n\t---------------------------------------------------------\n";
	while(file.read((char*)&c,sizeof(c)))
	{
		c.disp();
	}
}
contact c;
int choice;
long pn;
void home()
{       cout<<"\n\nHello user! Due to some restrictions on this compiler, the system can't store numbers properly after 8 digits, so you may consider storing numbers accordingly";
	file.open("contact.dat",ios::ate|ios::in|ios::out|ios::binary);
	do
	{
		clrscr();
		file.clear();
		clrscr();
		cout<<setw(40)<<"Phonebook"<<endl;
		cout<<"\n1. Add a contact "<<endl;
		cout<<"2. Search "<<endl;
		cout<<"3. Delete a contact"<<endl;
		cout<<"4. Edit a contact "<<endl;
		cout<<"5. View all contacts "<<endl;
		cout<<"6. Back "<<endl;
		cout<<"\nChoose something or tap # to get back home:";
		cin>>choice;
		switch(choice)
		{
			case 1:
				cout<<"\nEnter contact details "<<endl;
				file.clear();
				c.enter();
				insert(c);
				break;
			case 2:
				cout<<"\nEnter the phone no to be searched: ";
				cin>>pn;
				file.clear();
				search(pn);
				break;
			case 3:
				cout<<"\nEnter the phone no to be deleted ";
				cin>>pn;
				del(pn);
				file.open("contact.dat",ios::ate|ios::in|ios::out|ios::binary);
				break;
			case 4:
				cout<<"\nEnter phone no to be modified ";
				cin>>pn;
				file.clear();
				modify(pn);
				break;
			case 5: clrscr();
				disp1();
				getch();
         case 6: return;
		}
	}while(choice>=1&&choice<=5);

}

