
/*Biome Types
	1. Plains: weak to Anthrax, Bubonic Plague; resistant to Tuberculosis
	2. Mountains: weak to Tuberculosis, Anthrax; resistant to Cholera 
	3. Forests: weak to Tuberculosis, Bubonic Plague; resistant to Anthrax
	4. DPM: weak to Bubonic Plague, Cholera; resistant to Anthrax
	5. Coasts: weak to Cholera, Anthrax; resistant to Bubonic Plague
	6. Islands: weak to Cholera, Tuberculosis; resistant to Bubonic Plague
	Select one of 4 diseases-> each is strong in certain regions (if we cannot model real world diseases through use of SIR model/PDEs, create your own diseases!)
	1. Anthrax
	2. Cholera
	3. Tuberculosis
	4. Bubonic Plague
	Continents
	1. Asia
      - Plains: Gangetic Plains
      - Mountains: Pamir Knot
      - Forests: Borneo
      - Deserts, Plateaux, and Mesas: Karakum
      - Coasts: Indian Peninsula
      - Islands: Indonesian Archipelago
 	2. Africa
      - Plains: Serengeti and Okavango Deltas
      - Mountains: Kilimanjaro
      - Forests: Congo Rainforest
      - Deserts, Plateaux, and Mesas: Sahara
      - Coasts: Bight of Benin, Horn of Africa, Gulf of Africa
      - Islands: Madagascar
	3. South America
      - Plains: Pampas, Pantanal
      - Mountains: Andes
      - Forests: Amazon
      - Deserts, Plateaux, and Mesas: Atacama
      - Coasts: Humboldt Current Region
      - Islands: Galapagos, Easter and Falkland
	4. North America
      - Plains: Prairie
      - Mountains: Rockies
      - Forests: Central American Rainforest
      - Deserts, Plateaux, and Mesas: Mojave
      - Coasts: Western and Eastern Seaboard
      - Islands: Aleutians, Hawaii, Caribbean
	5. Oceania
      - Plains: Canterbury
      - Mountains: South Alps
      - Forests: Papua New Guinea
      - Deserts, Plateaux, and Mesas: Great Victoria Desert
      - Coasts: Great Barrier Reef
      - Islands: South Pacific
	6. Europe
      - Plains: Steppes
      - Mountains: Alps
      - Forests: Taiga
      - Deserts, Plateaux, and Mesas: Scandinavia
      - Coasts: Baltic Coast
	- Islands: Greenland, Spanish Islands*/
#include<iostream>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<unistd.h>
#include<cstring>
/*Now, the list of continental bonuses- what benefit do you get for starting on a continent? (This bonus remains constant throughout the game; does not change when you shift continents)
1. Africa: At the beginning of the game, there is a  15% chance that the BCR will decrease by 1.
2. Asia: At each mutation, there is a 25% chance that you will get an extra mutation.
3. Europe (Challenge Mode): BER decreases by 5 each time you receive a mutation.
4. Oceania: There is a 15% chance that all biome resistances are neglected.
5. North America: At each colonization of a new biome, there is a 5% chance that you will colonize another region. 
6. South America: If BER becomes zero, there is a 25% chance that you will be revived ONCE with a BER of 10.*/
//continental bonuses: insert into appropriate places, will add appropriate parameters later
using namespace std;
class place
{
	public:
	int biometype,continent,BCR,cqr,disease,resnull=0; //cqr checks if the biome in question has been owned or not
	char name[50];
	place()
	{
		cqr=0;
	}
	void assignbcr(microbe mcrb,place p); //ncqr is a global/in scope int variable wrt to the object denoting how many biomes have been conquered 
	void gotoneigh(int ct[],microbe mcrb,place p[]);//p=Biome[ct[0]],p[]=Biome[ct[0]][]
}Biome[6][6];
class microbe
{
	public:
	char mname[20];
	int BER,BMR,continenti, ncqr, revived; //revived=1 or 0
	microbe()
	{
		BER=200;
		ncqr=0;
		revived=0;
		BMR=5;
	}
void countdn(int ct[], int BER,)
{
	int lowestRate = 3;
	int mutaratemp;
	int BER_rise_min = 5;
	int BER_rise_max = 15;
	int BER_rise;
	int highestRate = 8;
	int mutarate;
	int mutanum;
	int mutafirst = 1;
	int BER_fall;
	int mutalast = 10;
	string mutaname;//add BCR as parameter
	while(BER!=0)
	{
	srand (time (NULL));
	mutarate = rand () % ((highestRate - lowestRate) + 1) + lowestRate;
	mutaratemp=mutarate;
	for (int i = mutarate; i > 0; i--)
	{
		cout << "You will receive a mutation in " << mutarate << " turns." <<endl;
		--mutarate;
		sleep (2.5);
	}
	if (mutarate == 0)
	{
		mutanum = rand () % ((mutalast - mutafirst) + 1) + mutafirst;
		cout << "You have received a new mutation! It is mutation number " <<mutanum << ". "<<endl;
		switch (mutanum)
		{
			case 1:
			mutaname = "Favoured spread";
			cout << "It is the mutation of " << mutaname <<". Its effect is that the country colonization rate decreases by 1. "<<endl;
			Biome[ct[0]][ct[1]].BCR = 4;
			break;
			case 2:
			mutaname = "Impeded spread";
			cout << "It is the mutation of " << mutaname <<". Its effect is that the country colonization rate increases by 1. "<<endl;
			Biome[ct[0]][ct[1]].BCR = 6;
			break;
			case 3:
			mutaname = "Strain Evolution";
			cout << "It is the mutation of " << mutaname <<
		  	    ". Its effect is that the the number of turns left before Eradication increases between 5 and 15."<<endl;;
		        BER_rise = rand () % ((BER_rise_max - BER_rise_min) + 1) + BER_rise_min;
		        BER = BER + BER_rise;
		        cout << "The new rate of eradication is: " << BER << ". "<<endl;
		        break;
			case 4:
		        mutaname = "Strain Extinction";
		        cout << "It is the mutation of " << mutaname <<
		  	    ". Its effect is that the number of turns left before eradication decreases by a number between 1 and 5."<<endl;
		        BER_fall = rand () % ((5 - 1) + 1) + 1;
			BER = BER - BER_fall;
			cout << "The new rate of eradication is: " << BER << ". "<<endl;
			break;
			case 5:
		        mutaname = "Severe Symptoms";
		        cout << "It is the mutation of " << mutaname <<
		  	    ". Its effect is that the number of turns left before mutation decreases by 1 on either side."<<endl;
		        highestRate = highestRate - 1;
		        lowestRate = lowestRate - 1;
		        break;
		      case 6:
		        mutaname = "Weakening Symptoms";
		        cout << "It is the mutation of " << mutaname <<
		  	    ". Its effect is that the number of turns left before mutation increases by 1 on either end."<<endl;
		        highestRate = highestRate + 1;
		        lowestRate = lowestRate + 1;
		        break;
		      case 7:
		        mutaname = "Antibiotic Resistance";
		        cout << "It is the mutation of " << mutaname <<". Its effect is that the BER increases by 10 percent each ";
		  	    cout<<"time you receive a mutation, but Mutation Number 3, Strain Evolution, will increase BER only from 2 to 12. "<<endl;
		  	    BER_rise_min=2;
		    	  BER_rise_max=12;
		    	  BER=1.1*BER;
		    	  cout<<"You now have "<<BER<<" turns left before eradication."<<endl;
		    	  break;
		  	  case 8:
		  	    mutaname = "Medical R&D";
		        cout << "It is the mutation of " << mutaname <<". Its effect is that the BER decreases by 10 percent each ";
		  	    cout<<"time you receive a mutation, but Mutation Number 3, Strain Evolution, will increase BER only from 7 to 17. "<<endl;
		    	  BER_rise_min=7;
		    	  BER_rise_max=17;
		    	  BER=0.9*BER;
		    	  cout<<"You now have "<<BER<<" turns left before eradication."<<endl;
		    	  break;
		  	  case 9:
		  	    mutaname="Colonization!";
		  	    cout<<"It is the mutation of "<<mutaname<<" Its effect is that you spread to a new continent, where you get a random biome."<<endl;
		  	    break;
		  	    default:
		  	    cout<<"Oops, sorry! You did not receive a mutation this time. Maybe you will evolve next time! "<<endl;
		    }
		    cout << " Rate of country colonization is now " << Biome[ct[0]][ct[1]].BCR << ". "<<endl;
		}
			BER--;
			Biome[ct[0]][ct[1]].BCR--;
			if(Biome[ct[0]][ct[1]].BCR==0)
			{
				cout<<endl<<Biome[ct[0]][ct[1]].continent<<" CONQUERED";			
				Biome[ct[0]][ct[1]].cqr=1;
				Biome[ct[0]][ct[1]].gotoneigh(ct,mcrb,Biome[ct[0]]);
			}
				cout<<"You have "<<BER<<" turns before eradication."<<endl;
		    sleep(2);
		}
	
	
		 //Krishna's mutation function goes here
		  //Added!
	}
	void contbonus(microbe mcrb);
}mcrb;
int ct[2];

void place::gotoneigh(int ct[],microbe mcrb,place p[])//p=Biome[ct[0]],p[]=Biome[ct[0]][]
	{
		int b;
		st:	
		srand(time(NULL));	
		b=(rand()%6); 		
		if(p[b].cqr==0)
		{
			ct[1]=b;

			p[ct[1]].assignbcr(mcrb,p[b]);
		}
		else
		{
			int chkemp=0;
			for(int i=0;i<5;i++)
			{
				if(p[b].cqr==0)
				chkemp=1;
			}
			if(chkemp==1)
			goto st;
			else
			cout<<endl<<"Continent CONQUERED!";
			//gotta think of intercontinental migration
		}
	}	
void Africa(int ct[], microbe mcrb)
{
	int m=rand()%100;
	if(m>=1&&m<=15&&mcrb.BER==200)//200 = initial value of ber	
	Biome[ct[0]][ct[1]].BCR--;
}
void Asia(microbe mcrb)
{
	int m=rand()%100;
	if(m>=1&&m<=25&&mcrb.BMR==0)
	mcrb.mutate(mcrb.BMR,mcrb.BER);//whatever you have named the mutation choice function
}
void Europe(microbe mcrb)
{
	if(mcrb.BMR==0)
	mcrb.BER-=5;
}	
void NAm()
{
	if(Biome[ct[0]][ct[1]].cqr==1&&Biome[ct[0]][ct[1]].BCR==0)
	{
		srand(time(NULL));
		int m=rand()%5;
		if(m==0)
		{		
			Biome[ct[0]][ct[1]].gotoneigh(ct,mcrb,Biome[ct[0]]);
			Biome[ct[0]][ct[1]].cqr=1;
		}
	}
}
inline void Oceania(int ct[], microbe mcrb)
{
	srand(time(NULL));	
	int m=rand()%100;
	if(mcrb.continenti==5&&m>=1&&m<=15)
	Biome[ct[0]][ct[1]].resnull=1;
}
void SAm(microbe mcrb)
{
	srand(time(NULL));
	int m=rand()%100;	
	if(mcrb.revived==0&&mcrb.BER==0) //revived is an int variable that checks if Lazarus is not trying to cheat the reaper for the second time
	{
		if(m>=1&&m<=25)
		mcrb.BER=10;
	}
}
void microbe::contbonus(microbe mcrb)
{
		switch (mcrb.continenti)
		{
			case 1:Asia(mcrb);
				break;
			case 2:Africa(ct,mcrb);
				break;
			case 3:SAm(mcrb);
				break;
			case 4:NAm();
				break;
			case 5://Oceania() is called elsewhere
				break;
			case 6:Europe(mcrb);
				break;
			default:break;
		}
}
void place::assignbcr(microbe mcrb,place p)
{
		p.BCR=5;
		if(mcrb.BER==200)
		Oceania(ct,mcrb);
		switch (biometype)
		{
			case 1:if(disease==1||disease==4)
			       p.BCR--;
				else if(disease==3)
				{	
					if(resnull==1)			
					p.BCR++;
				}
				break;
			case 2:if(disease==3||disease==1)
			       p.BCR--;
				else if(disease==2)
				{	
					if(resnull==1)			
					p.BCR++;
				}
				break;
			case 3:if(disease==3||disease==4)
			       p.BCR--;
				else if(disease==1)
				{	
					if(resnull==1)			
					p.BCR++;
				}
				break;
			case 4:if(disease==2||disease==4)
			       p.BCR--;
				else if(disease==1)
				{	
					if(resnull==1)			
					p.BCR++;
				}
				break;
			case 5:if(disease==1||disease==2)
			       p.BCR--;
				else if(disease==4)
				{	
					if(resnull==1)			
					p.BCR++;
				}
				break;
			case 6:if(disease==2||disease==3)
			       p.BCR--;
				else if(disease==4)
				{	
					if(resnull==1)			
					p.BCR++;
				}
				break;
			default://Lol srsly?
				break;
		}
		if(mcrb.ncqr>20&&mcrb.ncqr<=30)
		p.BCR++;
		else if(mcrb.ncqr>30)
		p.BCR+=2;
}

int main()
{
	int a,b,c,d,e,cont;
	strcpy(Biome[0][0].name,"Gangetic Plains\0");
	strcpy(Biome[0][1].name,"Pamir Knot\0");
	strcpy(Biome[0][2].name,"Borneo\0");
	strcpy(Biome[0][3].name,"Karakum\0");
	strcpy(Biome[0][4].name,"Indian Peninsula\0");
	strcpy(Biome[0][5].name,"Indonesian Archipelago\0");
	strcpy(Biome[1][0].name,"Serengeti and Okavango Deltas\0");
	strcpy(Biome[1][1].name,"Kilimanjaro\0");
	strcpy(Biome[1][2].name,"Congo Rainforest\0");
	strcpy(Biome[1][3].name,"Sahara\0");
	strcpy(Biome[1][4].name,"Bight of Benin, Horn of Africa, Gulf of Africa\0");
	strcpy(Biome[1][5].name,"Madagascar\0");
	strcpy(Biome[2][0].name,"Pampas, Pantanal\0");
	strcpy(Biome[2][1].name,"Andes\0");
	strcpy(Biome[2][2].name,"Amazon\0");
	strcpy(Biome[2][3].name,"Atacama\0");
	strcpy(Biome[2][4].name,"Humboldt Current Region\0");
	strcpy(Biome[2][5].name,"Galapagos, Easter and Falkland\0");
	strcpy(Biome[3][0].name,"Prairies\0");
	strcpy(Biome[3][1].name,"Rockies\0");
	strcpy(Biome[3][2].name,"Central American Rainforest\0");
	strcpy(Biome[3][3].name,"Mojave\0");
	strcpy(Biome[3][4].name,"Eastern and Western Seaboard\0");
	strcpy(Biome[3][5].name,"Aleutians, Hawaii, Caribbean\0");	
	strcpy(Biome[4][0].name,"Canterbury\0");
	strcpy(Biome[4][1].name,"South Alps\0");		
	strcpy(Biome[4][2].name,"Papua New Guinea\0");
	strcpy(Biome[4][3].name,"Great Victoria Desert\0");
	strcpy(Biome[4][4].name,"Great Barrier Reef\0");
	strcpy(Biome[4][5].name,"South Pacific\0");
	strcpy(Biome[5][0].name,"Steppes\0");
	strcpy(Biome[5][1].name,"Alps\0");
	strcpy(Biome[5][2].name,"Taiga\0");
	strcpy(Biome[5][3].name,"Scandinavia\0");
	strcpy(Biome[5][4].name,"Baltic Coast\0");
	strcpy(Biome[5][5].name,"Spanish Islands\0");
  cout<<"Welcome to Epidemica, the disease spread simulator!"<<endl;
  cout<<"Here, you play the role of a deadly disease whose sole purpose is to clense the world!"<<endl;
  cout<<"From what?"<<endl;
  cout<<"Deep down you know the answer!"<<endl;
  cout<<"HUMANS!"<<endl;
  cout<<"Before we begin the assault, let us have some formalities brushed aside."<<endl;
  cout<<"What is your name, dear friend?"<<endl;
  string player_name;
  getline(cin, player_name);
  cout<<"Well, welcome, "<<player_name<<"!"<<endl;
  cout<<"In a short while, we will be a deadly disease and we will be infecting our first human!"<< endl;
  cout<<"What's your goal in this 'Madness'?"<<endl;
  cout<<"Are you inspired by Thanos to slay half of all life for the good life itself?"<< endl;
  cout<<"Or are you a purist disease seeking to cleanse planet Earth of its most widespread disease."<<endl;
  cout<<"Deep down you know the answer!"<<endl;
  cout<<"FILTHY HUMANS?"<<endl;
  cout<<"Ah, but is your real motive simply the base desire of you surviving the longest while others simply 'perish'?"<<endl;
  cout<<"Or you just want to kill some humans!"<<endl;
  cout<<"A LOT of them"<<endl;
  cout<<"Whatever your motives are, we don't judge."<<endl;
  cout<<"Do know that humanity will not be an easy foe; they will fight back, and will fight hard, real hard!"<< endl;
  cout<<"With this said, let's get you your weapon!"<<endl;
  cout<<"Now, my beloved plague-mongerer, "<<player_name<<", it's time to select your Weapon, a.k.a. disease."<<endl;
  cout<<"Your choices shall appear any moment now."<<endl;
  cout<<"A word of caution my friend, these are some of the most virulent things to hit humanity"<<endl;
  cout<<"Both in the past, the present and possibly in the future: "<<endl;
  cout<<"Every disease has a 'Homeground' or its Locale. This is where it is the strongest."<<endl;
  cout<<"There are places where this disease is useless!"<<endl;
  cout<<"Keep this in your mind and proceed with the game!"<<endl;
  cout<<"When you are prompted to enter the name of your weapon, enter a number from 1 to 4."<<endl;
  cout<<"Remember, each disease is number coded."<<endl;
  cout<<"Press any number to continue."<<endl;
  cin>>d;
  cout<<"ANTHRAX"<<endl;
  cout<<"Caused by Bacillus anthracis, Anthrax have spores that can live for a long, long time."<< endl;
  cout<<"Its symptoms include high fever, fatigue, flu-like symptoms, shock, and in later stages, meningitis. "<<endl;
  cout<<"A recent developments in biowarfare created inhalatory anthrax, the most dangerous form of anthrax you can get."<<endl;
  cout<<"Anthrax is strong in Coasts, Mountains, and Plains Biomes, but is weak in Forests and Desert-Plateau-Mesa Biomes."<<endl;
  cout<<"Press any number to continue."<<endl;
  cin>>a;
  cout<<"CHOLERA."<<endl;
  cout<<"Caused by the bacterium Vibrio cholerae, Cholera is spread through contaminated water."<<endl;
  cout<<"The rampant pollution of drinking water sources has led to cholera being a highly communicable disease."<<endl;
  cout<<"Its symptoms include diarrhoea, dehydration, vomiting and cramps."<<endl;
  cout<<"Cholera is strong in Desert-Plateau-Mesa, Coasts, and Island Biomes, but is weak in Mountain biomes."<<endl;
  cout<<"Press any number to continue."<<endl;
  cin>>b;
  cout<<"TUBERCULOSIS."<<endl;
  cout<<"Caused by the bacterium Mycobacterium tuberculosis, tuberculosis, a.k.a. consumption, phthisis or just TB, is a deadly disease that spreads via air."<<endl;
  cout<<"Increasing population presents a problem in maintaining people at a 'safe' distance."<<endl;
  cout<<"This could be a jackpot!"<<endl;
  cout<<"Tuberculosis is strong in Mountains, Forests, and Island biomes, but is weak in Plains biomes."<<endl;
  cout<<"Press any number to continue."<<endl;
  cin>>c;
  cout<<"Bubonic Plague. The only disease that does not need bold case."<<endl;
  cout<<"Caused by the bacterium Yersinia pestis, mainly spreads through the bite of an infected flea."<<endl;
  cout<<"Proliferation of rats in urban areas, and their fleas has brought about a rise of bubonic plague cases."<<endl;
  cout<<"It can also spread through direct contact with the infected body tissue or bodily fluids."<<endl;
  cout<<"Its symptoms include buboes (lymphnode swellings), flu-like symptoms, chills, headaches, and fatigue."<<endl;
  cout<<"Bubonic Plague is strong in Plains, Forests and Desert-Plateau-Mesa biomes, but is weak in Coasts and Island biomes."<<endl;
  cout<<"Press any number to continue."<<endl;
  cin>>e;
  cout<<"ANTHRAX : 1"<<endl;
  cout<<"CHOLERA : 2"<<endl;
  cout<<"TUBERCULOSIS : 3"<<endl;
  cout<<"Bubonic Plague : 4"<<endl;
  cout<<"Hope you have made a choice!"<<endl;
  label:
  cout<<"Now, dear "<<player_name<<", which disease would you like?"<<endl;
  int disease_choice;
  string disease_name;
  cin>>disease_choice;
  switch(disease_choice)
   {
        case 1:
            disease_name="Anthrax";
            cout<<"You have chosen Anthrax! Good choice!";
            break;
        case 2:
            disease_name="Cholera";
            cout<<"You have chosen Cholera! Good choice!";
            break;
        case 3:
            disease_name="Tuberculosis";
            cout<<"You have chosen Tuberculosis! Good choice! ";
            break;
        case 4:
            disease_name="Bubonic Plague";
            cout<<"You have chosen Bubonic Plague! Good choice! ";
            break;
        default:
            cout<<"Having second thoughts, "<<player_name<<"? Try chosing your weapon from the catalogue again?";
            goto label;
   }
	cout<<endl<<"Choose a continent"<<endl<<"1.Asia"<<endl<<"2.Africa"<<endl<<"3.South America"<<endl<<"4.North America"<<endl<<"5.Oceania"<<endl<<"6.Europe";
	cin>>cont;
	srand(time(NULL));
	int bmi=rand()%6;
	ct[0]=cont;
	ct[1]=bmi;
	Biome[ct[0]][ct[1]].assignbcr(mcrb,Biome[ct[0]][ct[1]]);
	mcrb.contbonus(mcrb);
	mcrb.countdn(mcrb,ct);
    sleep(2);
	
	for(int i=0;i<36;i++)
	{
		Biome[i][0].biometype=((i+1)%6)+1;
		Biome[i][0].continent=(i/6)+1;
	}
			
	return 0;
}
