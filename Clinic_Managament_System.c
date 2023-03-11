/*************************************************/
/****** Auther 	: Mayar Saber				******/
/****** Version : 01		 				******/
/****** Project : Clinic Management System	******/
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"


typedef struct		//Struct data type to store patients information
{
	u8 name[48];
	u8 gender;
	u32 age;
	u32 id;
	u32 reservationDay;
	u32 reservationSlot;

}patient;


void AdminMode             (void);							  			/***The function handeling the Admin Mode***/
void AddPatient            (patient * ptr_record , u32 n);	  			/***The function that's used to get new patient data***/
void EditPatientRecord     (patient * ptr_record , u32 n);				/***Function used to edit existing patient records***/
void Reservation           (patient * ptr_record , u32 n);				/***Function to make a reservation***/
void CancelReservation     (patient * ptr_record , u32 n);				/***Function to cancel a reservation***/
void PrintingRecords       (patient * ptr_record , u32 n);				/***Function to view existing records***/
					       
void UserMode              (void);							  			/***The function handeling the User Mode***/
void ViewPatientRecord     (patient * ptr_record , u32 n);				/***Function to print patient record***/
void ViewTodaysReservation (patient * ptr_record , u32 n);				/***Function to print patient record***/


u32 MoreChoices = 1;		//u32 variable - Used to return to the main menu.
u32 count = 0;				//u32 variable - Used to count the patient records.
patient * ptr=NULL;			//patient type pointer - Used to hold the base address of the array of structs forming patient records.
u32 num=0;					//u32 variable - Used to take number of input records from the user.


u8 days[][10] = {"Sat","Sun","Mon","Tues","Wed","Thurs","Fri"};								//Array of strings - Used to specify the reservation day.
u8 slots[][15] = {"2:00 - 2:30","2:30 - 3:00","3:00 - 3:30","4:00 - 4:30","4:30 - 5:00"};	//Array of strings - Used to specify the reservation time slot.
u32 arr[7][5];				//2D array - Used to arrange the reservations



int main(void)
/***The main function***/
{
	u32 ModeFlag = 0;			//u32 variable - Used to make sure the mode is chosed correctly 1 or 2.
	u8 mode;					//u8 variable - To choose between Admin mode & User mode.
	u32 PasswordChances = 0;	//u32 variable - Used as a counter for the 3 chances the Admin User has to enter his own password.
	u32 password;				//u32 variable - To take the Admin mode password from user.
	
	
	for(u8 i=0 ; i<7 ; i++)		//Initializing the reservation array with zeros
	{
		for(u8 j=0 ; j<5 ; j++)
		{
			arr[i][j]=0;
		}
	}
	
	printf("\n\n---------- Welcone to the clinic management system ----------\n\n");
	
	while(ModeFlag == 0)	/**loop until getting a correct mode choice.**/
	{
		printf("\n>>Please choose: (1)Admin mode\t(2)User mode \n");		//choose the mode.
		scanf("%d",&mode);
		
			if(mode == 1)		/**Admin Mode is chosed**/
			{
				ModeFlag = 1;		//To quit the loop.
				
					while(PasswordChances<3)		//Give 3 chances to enter the correct admin mode password.
					{
						printf("\n>>Please enter admin password:...\n");
						scanf("%d",&password);
						
						if(password == 1234)		///Password is right.
						{
							PasswordChances = 3;			//To quit the loop.
							
							while(MoreChoices == 1)			//Used to reuse the main menu.
							{
								AdminMode();		///Calling the Admin mode Function**/
							}
						}
						
						
						else						///Password is wrong.
						{
							if(PasswordChances<2)			//Count the chances of entering the password.
							{
								printf("\n## Wrong password. Try again...\n");
							}
							else							//All The chances are gone.
							{
								printf("\n## Sorry, try again later ##\n");
							}
							
							PasswordChances++;
						}
					}

			}
		
		/*****************/
		
		else if(mode == 2)		/**User Mode is chosed**/
		{
			ModeFlag = 1;		//To quit the loop
			while(MoreChoices == 1)	
			{
				UserMode();			//Call the user mode function
			}

		}
		
		/*****************/
		
		else					/**The mode choice wasn't correct.**/
		{
			printf("\n## Your choice isn't valid. Try again...\n");
		}
	}
	
	
	
	free(ptr);					//Free the DMA pointer before shutting the program.
	printf("\n\n## End of the program. Thank you ##\n");		//The end of the program.
	return 0;
}

/******************************************************************************************************/

void AdminMode(void)
/***The function handeling the Admin Mode***/
{
	u32 OptionFlag = 0;		//u32 variable - Used to make sure the Admin User chose correctly one of the 6 available options.
	u32 choice;				//u32 variable - Used for the Admin User to choose one of the available 6 options in that mode.

	
	while(OptionFlag==0)		/**loop until getting a correct option choice.**/
		{
			printf("\n>>How can I help you?\n(1) Add new patient record.\n(2) Edit patient record.\n(3) Reserve a slot with the doctor.\n(4) Cancel reservation.\n(5) Print the exisisting patient records.\n(6) Quit the program.\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:				/**Adding new patient**/ 
				OptionFlag = 1;				//To quit the loop
				
				printf("\n>>Enter the number of inputs:...\n");
				scanf("%d",&num);
				
				if(count == 0)				///The system is empty and we're adding the first records ever.
				{
					ptr = (patient*)malloc(num*sizeof(patient));		//malloc() function to dynamically reserve the required memory, ptr saves the base address.
					AddPatient(ptr , num);								//Calling the AddPatient func and sending the base address and the number of inputs
				}
					
				else						///Adding more elements to the system.
				{
					num+=count;
					ptr = (patient*)realloc(ptr,num*sizeof(patient));
					AddPatient(ptr , num);
				}
				break;
				
				/**************************************************/
				
				case 2:				/**For editing existing patient record.**/
				OptionFlag = 1;				//To quit the loop
				
				EditPatientRecord(ptr , num);							//Calling the EditPatientRecord func and sending the base address and the number of inputs
				break;
				
				/**************************************************/
				
				case 3:				/**For making a reservation.**/
				
				OptionFlag = 1;		//To quit the loop
				
				Reservation(ptr , num);
				break;
				
				/**************************************************/
				
				case 4:				/**For cancelling a reservation.**/
				
				OptionFlag = 1;		//To quit the loop
				
				CancelReservation(ptr , num);
				break;
				
				/**************************************************/
				
				case 5:				/**For printing existing records.**/
				OptionFlag = 1;		//To quit the loop
				
				PrintingRecords(ptr , num);
				break;
				
				/**************************************************/
				
				case 6:				/**For ending the program.**/
				OptionFlag = 1;		//To quit the loop
				MoreChoices = 0;	//To quit the program
				break;
				
				/**************************************************/
				
				default:			/**The input wasn't a valid option.**/
				printf("\n## Your choice isn't valid. Try again...\n");		//If the choice wasn't vaild the loop will be performed again.
				break;
				
			}
		}
}

/******************************************************************************************************/

void AddPatient(patient * ptr_record , u32 n)
/**The function that's used to get new patient data**/
{
	u32 InputID;		//u32 variable - to get the patient ID for duplication check.
	u32 flag = 0;		//u32 variable - to handle the duplicated ID check.
	
	
	for(u8 i=count ; i<n ; i++)			///for loop from the last count of inputs to the total number of inputs
	{
		printf("\n>>Please enter patient%d name:...\n",i+1);					//Scanning the name
		scanf("\n");
		scanf("%[^\n]%*c",&((ptr_record+i)->name));
		
		
		do{																		//Scanning the ID
			flag = 0;
			printf("\n>>Please enter patient%d ID:...\n",i+1);
			scanf("%d",&InputID);
					
			for(u8 j=0 ; j<i ; j++)												//Checks if the ID is already registered or not.
			{	
				if(((ptr_record+j)->id) == InputID)
				{
					printf("\n## This ID is already used. Try again...\n");
					flag =1;
				}
			}
			
		}while(flag==1);


		if(flag == 0)															//If the ID isn't used assign it to the patient i
		{
			(ptr_record+i)->id = InputID;
		}


		printf("\n>>Please enter patient%d age:...\n",i+1);						//Scanning the age
		scanf("%d",&((ptr_record+i)->age));
		
		
		printf("\n>>Please enter patient%d gender\n 1-woman\t2-man:...\n",i+1);	//Scanning the gender
		scanf("%d",&((ptr_record+i)->gender));
		
		
		(ptr_record+i)->reservationDay = 8;										//Assigning the registration parts to 8 which is out of the range of registration options
		
		(ptr_record+i)->reservationSlot = 8;
		
		printf("\n\n");
	}
	
	
	
	/* 
	for(u8 i=0; i<n ; i++) 						//Printing the records
	{
		printf("---------------------\n");
		printf(">>Patient-%d<<\n",i+1);
		printf("patient%d name :%s\n",i+1,(ptr_record+i)->name);
		printf("patient%d ID :%d\n",i+1,(ptr_record+i)->id);
		printf("patient%d age :%d\n",i+1,(ptr_record+i)->age);
		printf("Patient%d gender :",i+1);
		if((ptr_record+i)->gender == 1)
			printf("Woman\n");
		else
			printf("Man\n");
		
		if(((ptr_record+i)->reservationDay) != 8 && ((ptr_record+i)->reservationSlot) != 8 )
		{
			printf(">>Reservation:\nDay - %s\tSlot - %s\n",days[((ptr_record+i)->reservationDay)],slots[((ptr_record+i)->reservationSlot)]);
		}
		else
		{
			printf(">>The patient has no reservation\n");
		}
		
		
		printf("\n\n");
	}*/
	
	
	
	count = n;			//Assining the count of inputs to count to use that in the next record input as reference


	printf("\n\n>>Please choose:\n(1) Back to the main menu.\n(2) Exit the program.\n");		//Ending of the function, and asking for more options
	scanf("%d",&MoreChoices);
}

/******************************************************************************************************/

void EditPatientRecord(patient * ptr_record , u32 n)
/***Function used to edit existing patient records***/
{
	u32 InputID;		//u32 variable - Take patient ID from the user.
	u32 newID;
	u32 flag1 = 0;		//u32 variable - To check if the input ID is available or not.
	u32 flag2 = 0;		//u32 variable - To check new ID duplication.
	u32 flag3 = 0;		//u32 variable - To ensure the user chosed a valid choice.
	u32 flag4 = 1;		//u32 variable - To check if the user wants another edit.
	u32 EditChoice = 0;
	
	if(n>0)				///Checks if there is records saved on the system or not.
	{
		do
		{
			printf("\n>>Please enter the patient ID\n");						//Take ID from user.
			scanf("%d",&InputID);
			
			for(u8 i=0 ; i<n ; i++)												//Loop to look for the Input ID.
			{
				if(((ptr_record+i)->id) == InputID)
				{
					
					printf("\n## Existing patient Information ##\n");			//Print the existing patient information.
					printf("patient%d name :%s\n",i+1,(ptr_record+i)->name);	//Print name.
					printf("patient%d ID :%d\n",i+1,(ptr_record+i)->id);		//Print id.
					printf("patient%d age :%d\n",i+1,(ptr_record+i)->age);		//Print age.
					printf("Patient%d gender :",i+1);							//Print gender.
					if((ptr_record+i)->gender == 1)
						printf("Woman\n");
					else
						printf("Man\n");
					printf("\n\n");
					
					
					while(flag3 == 0 || flag4 == 1)	/**flag4 - To check if the user wants another edit.**/ /**flag3 - To ensure the user chosed a valid choice.**/
					{
						printf("\n>>What do you want to edit?\n(1)Name\t(2)ID\t(3)Age\t(4)Gender\n");  //After finding the ID. 
						scanf("%d",&EditChoice);
						
						switch(EditChoice)						///Choosing the element to edit.
						{
							case 1:	/** change the name**/
							printf("\n>>Enter new name of patient%d:\n",i+1);		//Enter new name.
							scanf("\n");
							scanf("%[^\n]%*c",&(ptr_record+i)->name);
							
							flag3 = 1;												//To end the loop.
							
							printf("\n>>Do you want to edit another thing? (1) Yes\t\t(0) No\n");	///Asking if the user needs another update
							scanf("%d",&flag4);
							break;
							
							/**************************************************/
							
							case 2: /** change the id**/
							do{														//Scanning the ID.
								flag2 = 0;  /**flag2 - To check new ID duplication.**/
								printf("\n>>Enter new patient%d ID:...\n",i+1);		//Enter new ID.
								scanf("%d",&newID);
								
								for(u8 j=0 ; j<n ; j++)								//Check if the ID is used or not.
								{
									if(((ptr_record+j)->id) == newID)
									{
										printf("\n## This ID is already used. Try again...\n");
										flag2 =1;
									}
								}
							}while(flag2==1);

								if(flag2 == 0)		//The ID isn't duplicated
								{
									(ptr_record+i)->id = newID;
								}
								
							flag3 = 1;												//To end the loop.						
							
							printf("\n>>Do you want to edit another thing? (1) Yes\t\t(0) No\n");	///Asking if the user needs another update
							scanf("%d",&flag4);
							break;
							
							/**************************************************/
							
							case 3: /** change the age**/
							printf("\n>>Enter new age of patient%d:\n",i+1);		//Enter new age.
							scanf("%d",&(ptr_record+i)->age);
							
							flag3 = 1;												//To end the loop.	
							
							printf("\n>>Do you want to edit another thing? (1) Yes\t\t(0) No\n");	///Asking if the user needs another update
							scanf("%d",&flag4);
							break;
							
							/**************************************************/
							
							case 4: /** change the gender**/
							printf("\n>>Enter new gender of patient%d:\n",i+1);		//Enter new gender.
							scanf("%d",&(ptr_record+i)->gender);
							
							flag3 = 1;												//To end the loop.	
							
							printf("\n>>Do you want to edit another thing? (1) Yes\t\t(0) No\n");	///Asking if the user needs another update
							scanf("%d",&flag4);
							break;
							
							/**************************************************/
							
							default:
							printf("\n## Your choice isn't valid. Try again...\n");	 //The choice wasn't right.
							flag4=1;
							break;
						}
					}
					
					flag1 = 1;	//Indicating that the ID was found.
				}
			}
			
			if(flag1 == 0)		//If the input ID wasn't found.
			{
				printf("\n##This patient ID isn't available. Try again...##\n");
			}
			
		}while(flag1 == 0);		//If the ID wasn't found the loop will be done again.
	}
	
	
	else if(n==0)
	{
		printf("Sorry, There is still no records in the system\n");			//If the system has no records this function can't be done.
	}


	printf("\n\n>>Please choose:\n(1) Back to the main menu.\n(2) Exit the program.\n");		//Ending of the function, and asking for more options
	scanf("%d",&MoreChoices);
}

/******************************************************************************************************/

void Reservation(patient * ptr_record , u32 n)
/***Function to make a reservation***/
{
	u32 InputDay;		//u32 variable - To get the required registration day.
	u32 TimeSlot;		//u32 variable - To get the required registration time.
	u32 flag = 0;		//u32 variable to check if the reservation time is already taken or not.
	u32 flag2 = 0;		//u32 variable - Used to check if the input ID is valid or not.
	u32 flag3 = 0;		//u32 variable - Used to check the user choices for InputDay.
	u32 flag4 = 0;		//u32 variable - Used to check the user choices for TimeSlot.

	u32 InputID;

	
	if(n>0)			///Check if there are records in the system.
	{
		
		printf("\n----Available slots----\n");		//Printing the avaialble time slots , if the system has records
		for(u8 i=0 ; i<7 ; i++)
		{
			printf("%s\t|\t",days[i]);				//Printing the day
			for(u8 j=0 ; j<5 ; j++)
			{
				if(arr[i][j]==0)					//Printitng the time slot if it's empty
				{
					printf("%s\t|\t",slots[j]);
				}
				
				else								//If the time slot is taken, it won't be printed.
				{
					printf("-----------\t|\t");
				}
			}
			
			printf("\n");
		}
		
		
		printf("\n>>Enter the patient ID:\n");		//Get the required ID from user
		scanf("%d",&InputID);


		while(flag2==0 )		//While the ID wasn't found, the loop will continue
		 {
			for(u8 i=0 ; i<n ; i++)				//Loop to find the input ID
			 {
				 if(((ptr_record+i)->id)==InputID) /**The ID was found**/
				 {
					flag2 = 1;					//Indicating that the ID was found.
				
				
					while(flag==0)			   /**flag - to check if the reservation time is already taken or not.**/
					{
						do		//Loop till getting a correct day choice.
						{
							printf("\nEnter the required day:\n(0)Saturday\t(1)Sunday\t(2)Monday\t(3)Tuesday\t(4)Wednesday\t(5)Thursday\t(6)Friday\n");
							scanf("%d",&InputDay);
							if(InputDay <0 || InputDay >6)
							{
								printf("\n##Your choice isn't valid. Please choose again...\n");
							}
							else
							{
								flag3=1;
							}
							
						}while(flag3==0);

						do		//Loop till getting a correct slot choice.
						{
							printf("\nEnter the required time slot:\n(0)2:00 - 2:30\t\t(1)2:30 - 3:00\t\t(2)3:00 - 3:30\t\t(3)4:00 - 4:30\t\t(4)4:30 - 5:00\n");
							scanf("%d",&TimeSlot);
							if(TimeSlot <0 || TimeSlot >4)
							{
								printf("\n##Your choice isn't valid. Please choose again...\n");
							}
							else
							{
								flag4=1;
							}
							
						}while(flag4 ==0);

						
						if(arr[InputDay][TimeSlot]==0)		///The slot is available
						{
							((ptr_record+i)->reservationDay) = InputDay;
							((ptr_record+i)->reservationSlot) = TimeSlot;
							
							arr[InputDay][TimeSlot]=1;		//To reserve that appointment
							
							flag = 1;			//To quit the loop
						}
						
						
						else 												///The slot isn't available
						{
							printf("\n## This appointment isn't available. Please choose another one##\n");
						}
					}
					
				 }
			 }
			 
			 if(flag2 == 0)		/**The ID wasn't found**/
			 {
				  printf("\n##The ID isn't registered. Please enter a registered ID:##\n");
				  printf("\n>>Enter the patient ID:\n");
				  scanf("%d",&InputID);
			 }
		 }

	}
	
	/***********************************************************/
	
	else if(n==0)	///if there are no records in the system.
	{
		printf("\n## Sorry, There are still no records in the system.##\n");
	}


	printf("\n\n>>Please choose:\n(1) Back to the main menu.\n(2) Exit the program.\n");		//Ending of the function, and asking for more options
	scanf("%d",&MoreChoices);
}

/******************************************************************************************************/

void CancelReservation(patient * ptr_record , u32 n)
/***Function to cancel a reservation***/
{
	u32 InputDay;		//u32 variable - To get the required registration day.
	u32 TimeSlot;		//u32 variable - To get the required registration time.
	u32 flag2 = 0;		//u32 variable - Used to check if the input ID is valid or not.
	u32 InputID;

	
	if(n>0)			///Check if there are records in the system.
	{
		printf("\n>>Enter the patient ID:\n");		//Get the required ID from user
		scanf("%d",&InputID);


		while(flag2==0 )		//While the ID wasn't found, the loop will continue
		 {
			for(u8 i=0 ; i<n ; i++)				//Loop to find the input ID
			 {
				 if(((ptr_record+i)->id)==InputID) /**The ID was found**/
				 {
					 flag2 = 1;					//Indicating that the ID was found.
					 
					 arr[((ptr_record+i)->reservationDay)][((ptr_record+i)->reservationSlot)]=0;
					 (ptr_record+i)->reservationDay = 8;										//Assigning the registration parts to 8 which is out of the range of registration options
		
					 (ptr_record+i)->reservationSlot = 8;
				 }
			 }
			 
			 if(flag2 == 0)		/**The ID wasn't found**/
			 {
				  printf("\n##The ID isn't registered. Please enter a registered ID:##\n");
				  printf("\n>>Enter the patient ID:\n");
				  scanf("%d",&InputID);
			 }

		 }
		 
		
		
		
		printf("\n----Available slots----\n");		//Printing the avaialble time slots , if the system has records
		for(u8 i=0 ; i<7 ; i++)
		{
			printf("%s\t|\t",days[i]);				//Printing the day
			for(u8 j=0 ; j<5 ; j++)
			{
				if(arr[i][j]==0)					//Printitng the time slot if it's empty
				{
					printf("%s\t|\t",slots[j]);
				}
				
				else								//If the time slot is taken, it won't be printed.
				{
					printf("-----------\t|\t");
				}
			}
			
			printf("\n");
		}


	}
	
	/***********************************************************/
	
	else if(n==0)	///if there are no records in the system.
	{
		printf("\n## Sorry, There are still no records in the system.##\n");
	}


	printf("\n\n>>Please choose:\n(1) Back to the main menu.\n(2) Exit the program.\n");		//Ending of the function, and asking for more options
	scanf("%d",&MoreChoices);

}

/******************************************************************************************************/

void PrintingRecords(patient * ptr_record , u32 n)
/***Function to view existing records***/
{
	
	if(n>0)			///Check if there are records in the system.
	{
		printf("\n>>>Current patients<<<\n");
	}
	else if(n==0)
	{
		printf("Sorry, There is still no records in the system\n");
	}


	
	for(u8 i=0; i<n ; i++)		//Printing the existing patients records
	{
		printf("---------------------\n");
		printf(">>Patient-%d<<\n",i+1);
		printf("patient%d name :%s\n",i+1,(ptr_record+i)->name);
		printf("patient%d ID :%d\n",i+1,(ptr_record+i)->id);
		printf("patient%d age :%d\n",i+1,(ptr_record+i)->age);
		printf("Patient%d gender :",i+1);
		if((ptr_record+i)->gender == 1)
			printf("Woman\n");
		else
			printf("Man\n");
		
		if(((ptr_record+i)->reservationDay) != 8 && ((ptr_record+i)->reservationSlot) != 8 )
		{
			printf(">>Reservation:\nDay - %s\tSlot - %s\n",days[((ptr_record+i)->reservationDay)],slots[((ptr_record+i)->reservationSlot)]);
		}
		else
		{
			printf(">>The patient has no reservation\n");
		}
		
		
		printf("\n\n");
	}
	
	
	
	printf("\n\n>>Please choose:\n(1) Back to the main menu.\n(2) Exit the program.\n");		//Ending of the function, and asking for more options
	scanf("%d",&MoreChoices);
}

/******************************************************************************************************/

void UserMode(void)
/***The function handeling the User Mode***/
{
	
	u32 OptionFlag = 0;		//u32 variable - Used to make sure the Admin User chose correctly one of the 6 available options.
	u32 choice;				//u32 variable - Used for the Admin User to choose one of the available 6 options in that mode.

	
	while(OptionFlag==0)		/**loop until getting a correct option choice.**/
		{
			printf("\n>>How can I help you?\n(1) View patient record.\n(2) View today's record.\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:				/**View patient record**/ 
				OptionFlag = 1;				//To quit the loop
				ViewPatientRecord(ptr , num);
				break;
				
				/**************************************************/
				
				case 2:				/**View today's record.**/
				OptionFlag = 1;				//To quit the loop
				ViewTodaysReservation(ptr , num);
				break;
				
				/**************************************************/
				
				default:			/**The input wasn't a valid option.**/
				printf("\n## Your choice isn't valid. Try again...\n");		//If the choice wasn't vaild the loop will be performed again.
				break;
				
			}
		}
}

/******************************************************************************************************/

void ViewPatientRecord(patient * ptr_record , u32 n)
/***Function to print patient record***/
{
	u32 flag2 = 0;		//u32 variable - Used to check if the input ID is valid or not.
	u32 InputID;

	
	if(n>0)			///Check if there are records in the system.
	{
		printf("\n>>Enter the patient ID:\n");		//Get the required ID from user
		scanf("%d",&InputID);


		while(flag2==0 )		//While the ID wasn't found, the loop will continue
		 {
			for(u8 i=0 ; i<n ; i++)				//Loop to find the input ID
			 {
				 if(((ptr_record+i)->id)==InputID) /**The ID was found**/
				 {
					 flag2 = 1;
					 
					printf(">>Patient-%d record<<\n",i+1);
					printf("patient%d name :%s\n",i+1,(ptr_record+i)->name);
					printf("patient%d ID :%d\n",i+1,(ptr_record+i)->id);
					printf("patient%d age :%d\n",i+1,(ptr_record+i)->age);
					printf("Patient%d gender :",i+1);
					if((ptr_record+i)->gender == 1)
						printf("Woman\n");
					else
						printf("Man\n");
					
					if(((ptr_record+i)->reservationDay) != 8 && ((ptr_record+i)->reservationSlot) != 8 )
					{
						printf(">>Reservation:\nDay - %s\tSlot - %s\n",days[((ptr_record+i)->reservationDay)],slots[((ptr_record+i)->reservationSlot)]);
					}
					else
					{
						printf(">>The patient has no reservation\n");
					}

				 }
			 }
			 
			 if(flag2 == 0)		/**The ID wasn't found**/
			 {
				  printf("\n##The ID isn't registered. Please enter a registered ID:##\n");
				  printf("\n>>Enter the patient ID:\n");
				  scanf("%d",&InputID);
			 }

		 }
	}

	
	/***********************************************************/
	
	else if(n==0)	///if there are no records in the system.
	{
		printf("\n## Sorry, There are still no records in the system.##\n");
	}
		
	printf("\n\n>>Please choose:\n(1) Back to the main menu.\n(2) Exit the program.\n");		//Ending of the function, and asking for more options
	scanf("%d",&MoreChoices);
}

/******************************************************************************************************/

void ViewTodaysReservation(patient * ptr_record , u32 n)
/***Function to print patient record***/
{

	u32 flag2 = 0;		//u32 variable - Used to check if the input ID is valid or not.
	u32 InputID;

	
	if(n>0)			///Check if there are records in the system.
	{
		printf("\n>>Enter the patient ID:\n");		//Get the required ID from user
		scanf("%d",&InputID);


		while(flag2==0 )		//While the ID wasn't found, the loop will continue
		 {
			for(u8 i=0 ; i<n ; i++)				//Loop to find the input ID
			 {
				 if(((ptr_record+i)->id)==InputID) /**The ID was found**/
				 {
					 flag2 = 1;					//Indicating that the ID was found.
					 printf("%s\t|\t",days[((ptr_record+i)->reservationDay)]);				//Printing the day
					 for(u8 j=0 ; j<5 ; j++)
						{
							if(arr[((ptr_record+i)->reservationDay)][j]==0)					//Printitng the time slot if it's empty
							{
								printf("%s\t|\t",slots[j]);
							}
							
							else								//If the time slot is taken, it won't be printed.
							{
								printf("-----------\t|\t");
							}
						}

				 }
			 }
			 
			 if(flag2 == 0)		/**The ID wasn't found**/
			 {
				  printf("\n##The ID isn't registered. Please enter a registered ID:##\n");
				  printf("\n>>Enter the patient ID:\n");
				  scanf("%d",&InputID);
			 }

		 }

	}
	
	/***********************************************************/
	
	else if(n==0)	///if there are no records in the system.
	{
		printf("\n## Sorry, There are still no records in the system.##\n");
	}


	printf("\n\n>>Please choose:\n(1) Back to the main menu.\n(2) Exit the program.\n");		//Ending of the function, and asking for more options
	scanf("%d",&MoreChoices);
}	