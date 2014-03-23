#include "LightsOut.h"
#include "Functions.h"

using namespace std;

int main()
{
	LightsOut LO;				
	char fName[128] = {0, };	
	int op;						
	int sel;					
	int xPos, yPos;				
	char opBuf[32] = {0, };		
	char selBuf[32] = {0, };	
	char posBuf[32] = {0, };	
	char* temp;
		
	//ofstream fileInit;

	//fileInit.open("Results.txt", ios::trunc);
	//fileInit.close();

	while(1)
	{
		showMainMenu();
		
		cin.getline(opBuf, 32);
		
		if(strlen(opBuf) != 1)
		{
			cout<<"Wrong number..."<<endl;
			continue;
		}
		
		if((int)opBuf[0] < 48 || (int)opBuf[0] > 57)
		{
			cout<<"Wrong number..."<<endl;
			continue;
		}

		else
			op = atoi(opBuf);

		if(op == 1)
		{
			cout<<"Input file name >> ";
			cin.getline(fName, 128);

			if(LO.LoadMap(fName))
				cout<<"Load complete!!"<<endl;
		}

		else if(op == 2)
		{
			if(!strcmp(fName, ""))
			{
				cout<<"Load map first..."<<endl;
			}

			else
			{
				if(LO.IsSolved())
				{
					cout<<endl<<"This map is already solved."<<endl;
					cout<<"If you want select another map, enter the menu 1"<<endl;
					cout<<"Or If you want quit the program, enter the menu 3"<<endl<<endl;
				}

				else
				{
					cout<<"Game Start!!"<<endl;

					while(1)
					{
						showLightsOutMenu();

						cin.getline(selBuf, 32);

						if(strlen(selBuf) != 1)
						{
							cout<<"Wrong number..."<<endl;
							continue;
						}

						if((int)selBuf[0] < 48 || (int)selBuf[0] > 57)
						{
							cout<<"Wrong number..."<<endl;
							continue;
						}

						else
							sel = atoi(selBuf);

						if(sel == 1)
						{

							cout<<"Input (x, y) >> ";
							cin.getline(posBuf, 32);
							
							if(strlen(posBuf) != 3)
							{
								cout<<"Wrong number..."<<endl;
								continue;
							}

							temp = strtok(posBuf, " ");
							if((int)temp[0] >= 48 && (int)temp[0] <= 57)
							{
								xPos = atoi(temp);
								temp = strtok(NULL, "\n");
								
								if(!temp)
								{
									cout<<"Enter the two integer value..."<<endl;
									continue;
								}

								else
								{
									if((int)temp[0] >= 48 && (int)temp[0] <= 57)
										yPos = atoi(temp);

									else
									{
										cout<<"Enter the integer value..."<<endl;
										continue;
									}
								}
							}

							else
							{
								cout<<"Enter the two integer value..."<<endl;
								continue;
							}

							if(LO.LightOnOff(xPos, yPos))
							{
								LO.Push(xPos, yPos);
								cout<<endl<<"States of Lights : "<<endl;
								LO.PrintLights();
							}

							else
							{
								cout<<"Enter the number between 0 and 4"<<endl;
								continue;
							}


							if(LO.IsSolved())
							{
								LO.RecordSolution("Results.txt");
								LO.~LightsOut();	
								break;
							}
						}

						else if(sel == 2)
						{
							LO.Undo();
						}

						else if(sel == 3)
						{
							LO.Reset();
						}

						else if(sel == 4)
						{
							cout<<"Print Lights!!"<<endl<<endl;
							LO.PrintLights();
						}

						else if(sel == 5)
						{
							cout<<"Give up!!!"<<endl;
							memset(fName, NULL, 128);	
							break;
						}

						else
						{
							cout<<"Wrong Number..."<<endl;
							continue;
						}
					}
				}
			}
		}
		else if(op == 3)
		{
			cout<<"End!!!"<<endl;
			break;
		}
		else
		{
			cout<<"Wrong Number..."<<endl;
			continue;
		}
	}

	return 0;
}
