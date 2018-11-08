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
	int biometype,continent,BCR,cqr,contcqr; //cqr checks if the biome in question has been owned or not
	char name[50],contname[15],btype[30];
	place()
	{
		cqr=0;
		contcqr=0;
	}
}Biome[6][6];
class microbe
{
	public:
	char mname[20];
	int BER,BMR,continenti, ncqr,disease; 
	microbe()
	{
		BER=10000;
		ncqr=0;
		BMR=5;
	}
void countdn(int ct[], microbe m);

}mcrb;
int ct[2];
int baseBCR;
int assignbcr(microbe mcrb,place p)
{
		int BCR=5;
		if(mcrb.BER==200)
		switch (p.biometype)
		{
			case 1:if(mcrb.disease==1||mcrb.disease==4)
			       BCR--;
				else if(mcrb.disease==3)
				{			
					BCR++;
				}
				break;
			case 2:if(mcrb.disease==3||mcrb.disease==1)
			       BCR--;
				else if(mcrb.disease==2)
				{		
					BCR++;
				}
				break;
			case 3:if(mcrb.disease==3||mcrb.disease==4)
			       BCR--;
				else if(mcrb.disease==1)
				{	
					BCR++;
				}
				break;
			case 4:if(mcrb.disease==2||mcrb.disease==4)
			       BCR--;
				else if(mcrb.disease==1)
				{			
					BCR++;
				}
				break;
			case 5:if(mcrb.disease==1||mcrb.disease==2)
			       BCR--;
				else if(mcrb.disease==4)
				{				
					BCR++;
				}
				break;
			case 6:if(mcrb.disease==2||mcrb.disease==3)
			       BCR--;
				else if(mcrb.disease==4)
				{				
					BCR++;
				}
				break;
			default://Lol srsly?
				break;
		}
		if(mcrb.ncqr>20&&mcrb.ncqr<=30)
		BCR++;
		else if(mcrb.ncqr>30)
		BCR+=2;
		return BCR;
}
void gotoneigh(int ct[],microbe mcrb,place Biome[6][6])//p=Biome[ct[0]],p[]=Biome[ct[0]][]
	{
		int b;
		st:	
		srand(time(NULL));	
		b=(rand()%6); 		
		if(Biome[ct[0]][b].cqr==0)
		{
			ct[1]=b;

			Biome[ct[0]][b].BCR=assignbcr(mcrb,Biome[ct[0]][b]);
		}
		else
		{
			int chkemp=0;
			for(int i=0;i<6;i++)
			{
				if(Biome[ct[0]][i].cqr==0)
				chkemp=1;
			}
			if(chkemp==1)
			goto st;
			else if(chkemp==0)
			{
				cout<<endl<<"Continent CONQUERED!";
				for(int i=0;i<6;i++)
				{
					Biome[ct[0]][i].contcqr=1;	
				}
				tt:
				srand(time(NULL));
				ct[0]=rand()%6;
				if(Biome[ct[0]][b].contcqr==0)
				{
					if(Biome[ct[0]][b].cqr==0)
					{
						ct[1]=b;
						Biome[ct[0]][b].BCR=assignbcr(mcrb,Biome[ct[0]][b]);
					}
					else
					{
						int chkemp1=0;
						for(int i=0;i<6;i++)
						{
							if(Biome[ct[0]][b].cqr==0)
							chkemp1=1;
						}
						if(chkemp1==1)
						goto st;
						else
						{
							cout<<"Continent Already CONQUERED!";
							goto tt;
						}
						int chkempc=0;
						for(int i=0;i<6;i++)
						{
							if(Biome[i][1].contcqr==0)
							chkempc=1;
						}
						if(chkempc==1)
						goto tt;	
						else if(chkempc==0)
						{	
							cout<<"YOU DA REAL SCOURGE OF HUMANKIND!"<<endl<<"CONGRATULATIONS, you have conquered the WORLD!";
							exit(0);
						}
					}
				}
			}
			//gotta think of intercontinental migration
		}
	}
void microbe::countdn(int ct[], microbe mcrb)
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
	while(mcrb.BER!=0)
	{
		srand (time (NULL));
		mutarate = rand () % ((highestRate - lowestRate) + 1) + lowestRate;
		mutaratemp=mutarate;
		for (int i = mutarate; i > 0&&mcrb.BER!=0; i--)
		{
			cout <<endl<< "You will receive a mutation in " << mutarate << " turns." <<endl;
			--mutarate;
			Biome[ct[0]][ct[1]].BCR--;
			cout <<endl<<" Rate of country colonization is now " << Biome[ct[0]][ct[1]].BCR << ". "<<endl;
			cout<<"You now have "<<--mcrb.BER<<" turns left before eradication."<<endl;
			if(mcrb.BER==0)
			cout<<endl<<"You have been ERADICATED";
			if(Biome[ct[0]][ct[1]].BCR<=0)
			{
				cout<<endl<<Biome[ct[0]][ct[1]].name<<" CONQUERED";			
				Biome[ct[0]][ct[1]].cqr=1;
				gotoneigh(ct,mcrb,Biome);
				cout<<endl<<"Arrived at "<<Biome[ct[0]][ct[1]].name<<" in "<<Biome[ct[0]][ct[1]].contname<<"."<<endl<<"Biome Type - "<<Biome[ct[0]][ct[1]].btype;
			}
			sleep (2);
		}
		if (mutarate == 0&&mcrb.BER!=0)
		{
			mutanum = rand () % ((mutalast - mutafirst) + 1) + mutafirst;
			cout <<endl<< "You have received a new mutation! It is mutation number " <<mutanum << ". "<<endl;
			switch (mutanum)
			{
				case 1:
				mutaname = "Favoured spread";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the base country colonization rate decreases by 1. "<<endl;
				baseBCR = 4;
				break;
				case 2:
				mutaname = "Impeded spread";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the base country colonization rate increases by 1. "<<endl;
				baseBCR = 6;
				break;
				case 3:
				mutaname = "Strain Evolution";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the the number of turns left before Eradication increases between 5 and 15."<<endl;;
				BER_rise = rand () % ((BER_rise_max - BER_rise_min) + 1) + BER_rise_min;
				mcrb.BER = mcrb.BER + BER_rise;
				cout << "The new rate of eradication is: " << mcrb.BER << ". "<<endl;
				break;
				case 4:
				mutaname = "Strain Extinction";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the number of turns left before eradication decreases by a number between 1 and 5."<<endl;
				BER_fall = rand () % ((5 - 1) + 1) + 1;
				mcrb.BER = mcrb.BER - BER_fall;
				cout << "The new rate of eradication is: " << mcrb.BER << ". "<<endl;
				break;
				case 5:
				mutaname = "Severe Symptoms";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the number of turns left before mutation decreases by 1 on either side."<<endl;
				highestRate = highestRate - 1;
				lowestRate = lowestRate - 1;
				break;
				case 6:
				mutaname = "Weakening Symptoms";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the number of turns left before mutation increases by 1 on either end."<<endl;
				highestRate = highestRate + 1;
				lowestRate = lowestRate + 1;
				break;
				case 7:
				mutaname = "Antibiotic Resistance";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the BER increases by 10 percent ";
				cout<<", but Mutation Number 3, Strain Evolution, will increase BER only from 2 to 12. "<<endl;
				BER_rise_min=2;
				BER_rise_max=12;
				mcrb.BER=1.1*mcrb.BER;
				cout<<"You now have "<<mcrb.BER<<" turns left before eradication."<<endl;
				break;
				case 8:
				mutaname = "Medical R&D";
				cout << "It is the mutation of " << mutaname <<". Its effect is that the BER decreases by 10 percent, but Mutation Number 3, Strain Evolution, will increase BER only from 7 to 17. "<<endl;
				BER_rise_min=7;
				BER_rise_max=17;
				mcrb.BER=0.9*mcrb.BER;
				cout<<"You now have "<<mcrb.BER<<" turns left before eradication."<<endl;
				break;
				/*case 9:
				mutaname="Colonization!";
				cout<<"It is the mutation of "<<mutaname<<" Its effect is that you spread to a new continent, where you get a random biome."<<endl;
				srand(time(NULL));
				ct[0]=rand()%6;
				gotoneigh(ct,mcrb,Biome[ct[0]]);
				break;*/
				default:
				cout<<"Oops, sorry! You did not receive a mutation this time. Maybe you will evolve next time! "<<endl;
			}
			
			sleep(2);
		}
	}
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
	//continentname	
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			switch(i)
			{
				case 0:strcpy(Biome[i][j].contname,"Asia\0");
					break;
				case 1:strcpy(Biome[i][j].contname,"Africa\0");
					break;
				case 2:strcpy(Biome[i][j].contname,"South America\0");
					break;
				case 3:strcpy(Biome[i][j].contname,"North America\0");
					break;
				case 4:strcpy(Biome[i][j].contname,"Oceania\0");
					break;
				case 5:strcpy(Biome[i][j].contname,"Europe\0");
					break;
				default:break;
			}
		}
	}
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			switch(i)
			{
				case 0:strcpy(Biome[j][i].btype,"Plains\0");
					break;
				case 1:strcpy(Biome[j][i].btype,"Mountains\0");
					break;
				case 2:strcpy(Biome[j][i].btype,"Forests\0");
					break;
				case 3:strcpy(Biome[j][i].btype,"Deserts, Plateaux, Mesas\0");
					break;
				case 4:strcpy(Biome[j][i].btype,"Coast\0");
					break;
				case 5:strcpy(Biome[j][i].btype,"Islands\0");
					break;
				default:break;
			}
		}
	}
  cout<<"Welcome to Epidemica, the disease spread simulator!"<<endl;
  cout <<"In this game/simulator, you play the role of a deadly disease whose only goal is to spread across the world!"<<endl;
  cout <<
    "Before we jump into it, let's begin more conventionally. What is your name, dear player?"
    << endl;
  string player_name;
    getline(cin, player_name);
    cout << "Well, welcome, " << player_name <<
    "! In a short while, we will be a deadly disease and we will be infecting our first human!"
    << endl;
    cout <<
    "What's your goal in this virulent party? Are you inspired by Thanos to slay humanity?"
    << endl;
    cout <<
    "Or are you a purist disease seeking to cleanse planet Earth of its most widespread disease- filthy humans?"
    << endl;
    cout <<
    "Ah, but is your real motive simply the base desire of making yourself survive the longest you can?"
    << endl;
    sleep(2);
    cout <<
    "Whatever your motives to seek revenge might be, do know that humanity will not be an easy foe; they will fight back, and hard!"
    << endl;
    cout << "Now, my beloved plague-mongerer " << player_name <<
    ", it's time to select your disease." << endl;
    cout <<
    "Here are your choices of disease, some of the most virulent things to hit humanity, both in the past, the present and possibly in the future: "
    << endl;
    cout << "Drumroll: " << endl;
  for (int i = 0; i < 10; i++)
    {
    cout << ". "<<endl;
        sleep(1);
    }
    int whocares1, whocares2, whocares3, whocares4;
  cout <<
    "1. Anthrax. A disease caused by Bacillus anthracis, Anthrax have spores that can live for a long, long time."
    << endl;
    cout<<"Its symptoms include high fever, fatigue, flu-like symptoms, shock, and in later stages, meningitis. "<<endl;
  cout << "A recent proliferation in biowarfare in the future has caused inhalatory anthrax, the most dangerous form, to be a serious threat."<<endl;
cout<<"Anthrax is strong in Coasts, Mountains, and Plains Biomes, but is weak in Forests and Desert-Plateau-Mesa Biomes."<<endl;
cout<<"Enter 1 in the upcoming selection box to choose Anthrax! "<<endl<<"Enter any number to continue: "<<endl;
cin>>whocares1;
cout<<endl;
cout<<"2. Cholera. A disease caused by the bacterium Vibrio cholerae, Cholera is spread through contaminated water."<<endl;
cout<<"The pollution of drinking water sources has led to cholera being a highly virulent disease."<<endl;
cout<<"Its symptoms include diarrhoea, dehydration, vomiting and cramps."<<endl;
cout<<"Cholera is strong in Desert-Plateau-Mesa, Coasts, and Island Biomes, but is weak in Mountain biomes."<<endl;
cout<<"Enter 2 in the upcoming selection box to choose cholera!"<<endl<<"Enter any number to continue: "<<endl;
cin>>whocares2;
cout<<endl;
cout<<"3. Tuberculosis. Caused by the bacterium Mycobacterium tuberculosis. "<<endl;
cout<<"Tuberculosis, also called consumption, phthisis or just TB, is a deadly disease spread via air."<<endl;
cout<<"In the future, increasing population may present a problem in maintaining people at a safe distance away from each other enough to prevent TB's spread, although the disease is generally latent."<<endl;
cout<<"Tuberculosis is strong in Mountains, Forests, and Island biomes, but is weak in Plains biomes."<<endl;
cout<<"Enter 3 in the upcoming selection box to choose tuberculosis!"<<endl<<"Enter any number to continue: "<<endl;
cin>>whocares3;
cout<<endl;
cout<<"4. Bubonic Plague. Caused by the bacterium Yersinia pestis."<<endl;
cout<<"The proliferation of rats in urban areas, and their fleas has brought about a rise of bubonic plague cases."<<endl;
cout<<"Once in the 1350s in Europe, the Black Death caused the death of 50 percent of the continent's population. "<<endl;
cout<<"Its symptoms include buboes (lymphnode swellings), flu-like symptoms, chills, headaches, and fatigue."<<endl;
cout<<"Bubonic Plague is strong in Plains, Forests and Desert-Plateau-Mesa biomes, but is weak in Coasts and Island biomes."<<endl;
cout<<"Enter 4 in the upcoming selection box to choose bubonic plague!"<<endl<<"Enter any number to proceed to the disease selection screen: "<<endl;
cin>>whocares4;
cout<<endl;
label:
cout<<"Now, dear "<<player_name<<", which disease would you like? ";
int disease_choice;
string disease_name;
cin>>disease_choice;
switch(disease_choice)
{
    case 1:
        disease_name="Anthrax";
        cout<<"You have chosen Anthrax! Good choice! Let's go dominate the world together, "<<player_name<<"! ";
        break;
    case 2:
        disease_name="Cholera";
        cout<<"You have chosen Cholera! Good choice! Let's go dominate the world together, "<<player_name<<"! ";
        break;
    case 3:
        disease_name="Tuberculosis";
        cout<<"You have chosen Tuberculosis! Good choice! Let's go dominate the world together, "<<player_name<<"! ";
        break;
    case 4:
        disease_name="BubonicPlague";
        cout<<"You have chosen Bubonic Plague! Good choice! Let's go dominate the world together, "<<player_name<<"! ";
        break;
    default:
        cout<<"That does not seem like a valid choice you have entered there, "<<player_name<<"! Try again? "<<endl;
        goto label;
}
sleep(2);
cout<<"Any good disease must now be looking for a place to begin. Let us select a continent to begin on out of 6 populated regions: "<<endl;
cout<<"(sorry, antarctica)"<<endl;
cout<<"You are birthed by infecting a single 'Patient Zero' in the continent of your choice."<<endl<<endl;
sleep(2);
cout<<"Before we do this, the developers would like to share a statement: "<<endl;
cout<<"Hi! This game was made as a fun activity to show you how disease spread is affected by the world around us :) "<<endl;
cout<<"We have assumed a linear as opposed to an exponential population disease spread; do see the SIR model solutions for exponential spread."<<endl;
cout<<"We wish you all the best as an evil disease trying to eradicate humanity!"<<endl;
cout<<"If you wipe out the world, tell us! You get prizes! :D"<<endl;
sleep(5);
int whocaresc1, whocaresc2, whocaresc3, whocaresc4, whocaresc5, whocaresc6;
cout<<"Back to the game now: "<<endl<<endl;
cout<<"Your first continent choice is Asia. A sweeping large landmass with many different populations and geographical features."<<endl;
cout<<"(let's get down to business to defeat the Huns?)"<<endl;
cout<<"Asia has been divided into 6 biomes: "<<endl;
cout<<"Plains: Indo-Gangetic Plains. "<<endl<<"Mountains: Pamir Knot. "<<endl<<"Forests: Borneo. "<<endl;
cout<<"Desert-Plateaux-Mesa: Karakum. "<<endl<<"Coasts: Indian Peninsula. "<<endl<<"Islands: Indonesian Archipelago."<<endl;
cout<<"By choosing Asia, you get the continental bonus of Genetic Cornucopia. ";
cout<<"This means that at each mutation, there is a 25 percent chance that you will get an extra mutation."<<endl;
cout<<"Enter Asia in the selection if you want Asia!"<<endl;
cout<<"Enter any number to continue: ";
cin>>whocaresc1;
cout<<endl;
cout<<endl<<"Your second continent choice is Africa. (don't forget to bless the rains in Africa)!"<<endl;
cout<<"Africa's six biomes are as follows: "<<endl;
cout<<"Plains: Serengeti and Okavango Deltas. "<<endl<<"Mountains: Kilimanjaro. "<<endl<<"Forests: Congo Rainforest. "<<endl;
cout<<"Desert-Plateaux-Mesa: Sahara Desert. "<<endl<<"Coasts: Bight of Benin. "<<endl<<"Islands: Madagascar. "<<endl;
cout<<"Africa is the colloquial 'Dark Continent', a large land with generally poor citizens. When you begin in Africa, you get the following bonus: "<<endl;
cout<<"Low Healthcare: At the beginning of the plague, there is a 15 percent chance that the disease spreading rate for the rest of the game decreases by 1. "<<endl;
cout<<"Enter Africa in the selection if you want Africa!"<<endl;
cout<<"Enter any number to continue: ";
cin>>whocaresc2;
cout<<endl;
cout<<endl<<"Your third continent choice is South America. A land of mysteries and untouched nature. "<<endl;
cout<<"South America's six biomes are as follows: "<<endl;
cout<<"Plains: Pampas and Pantanal. "<<endl<<"Mountains: Andes. "<<endl<<"Forests: Amazon Rainforest. "<<endl;
cout<<"Deserts-Plateaux-Mesas: Atacama Desert. "<<endl<<"Coasts: Humboldt Current. "<<endl<<"Islands: Galapagos, Easter, and Falklands. "<<endl;
cout<<"South America is a land where every biome is super-magnified and extremely well-established. Hence you get the following bonus: ";
cout<<"Secret Survival: If at any point, you get eradicated, you have a 25 percent chance of reviving with a 10-turn base turn number before re-eradication. "<<endl;
cout<<"Enter South America in the selection if you want South America!"<<endl;
cout<<"Enter any number to continue: ";
cin>>whocaresc3;
cout<<endl;
cout<<endl<<"Your fourth continent choice is North America. A vast, sparsely populated land, with a great melting pot of cultures. "<<endl;
cout<<"Full of immigrants! (We come from the land of the ice and snow, From the midnight sun where the hot springs blow)"<<endl;
cout<<"North America's six biomes are as follows: "<<endl;
cout<<"Plains: Prairies. "<<endl<<"Mountains: Rockies. "<<endl<<"Forests: Central American Rainforest. "<<endl;
cout<<"Deserts-Plateaux-Mesas: Mojave Desert. "<<endl<<"Coasts:  Eastern and Western Seaboards. "<<endl<<"Islands: Caribbean and Hawaii. "<<endl;
cout<<"North America is a sparsely populated land, and as a result, there's a lot of inter-state travel. Hence you get the following bonus: "<<endl;
cout<<"Border Transport: At each colonization of a new biome, there is a 5% chance that you will colonize another region. "<<endl;
cout<<"Enter North America in the selection if you want North America!"<<endl;
cout<<"Enter any number to continue: ";
cin>>whocaresc4;
cout<<endl;
cout<<endl<<"Your fifth continent choice is Oceania. A continent full of water (apart from Australia) with scattered tiny islands all around. Not all settled by humans... "<<endl;
cout<<"(See the line where the sky meets the sea? It calls me, and no-one knows how far I'll go)"<<endl;
cout<<"Oceania's six biomes are as follows: "<<endl;
cout<<"Plains: Canterbury Plains. "<<endl<<"Mountains: Southern Alps. "<<endl<<"Forests: Papua New Guinea. "<<endl;
cout<<"Deserts-Plateaux-Mesas: Great Victoria Desert. "<<endl<<"Coasts: Great Barrier Reef. "<<endl<<"Islands: South Pacific. "<<endl;
cout<<"Oceania. Full of water, hard to access all the lands from it. A disease succeeding here will need a strong sense of rejecting environmental changes. Hence you get the following bonus: "<<endl;
cout<<"Pacific Pacifism: At the beginning of the game, there is a 15 percent that all biome strengths and weaknesses are neglected. "<<endl;
cout<<"Enter Oceania in the selection if you want Oceania!"<<endl;
cout<<"Enter any number to continue: ";
cin>>whocaresc5;
cout<<endl;
cout<<endl<<"Your final continent choice is Europe. Rich, cold and hard to conquer, it can rarely be tided over. A challenge for anyone."<<endl;
cout<<"(It's the final countdown....)"<<endl;
cout<<"Oceania's six biomes are as follows: "<<endl;
cout<<"Plains: Steppes. "<<endl<<"Mountains: Alps. "<<endl<<"Forests: Taiga. "<<endl;
cout<<"Deserts-Plateaux-Mesas: Scandinavia. "<<endl<<"Coasts: Baltic Countries. "<<endl<<"Islands: Greenland. "<<endl;
cout<<"Europe. After the Black Plague, Europe has emerged as the richest continent. This bonus is negative, as a challenge: "<<endl;
cout<<"No Warmth Here: Every time you receive a mutation, the number of turns left for your eradication decreases by 2. "<<endl;
cout<<"Enter Europe in the selection if you want Europe!"<<endl;
cout<<"Enter any number to continue: ";
cin>>whocaresc6;
cout<<endl;
string continent_choice;
cout<<"It is now time to select a continent, "<<player_name<<"! Enter the number of the one you'd like: "<<endl;
int continent_choice;
string cont_name;
cout<<"It is now time to select a continent, "<<player_name<<"! Enter the name of the one you'd like: "<<endl;
cin>>continent_choice;
if(continent_choice==1)
    cont_name="Asia";
else if(continent_choice==2)
    cont_name="Africa";
else if(continent_choice==3)
    cont_name="South America";
else if(continent_choice==4)
    cont_name="North America";
else if(continent_choice==5)
    cont_name="Oceania";
else if(continent_choice==6)
       cont_name="Europe";
cout<<"You have selected "<<cont_name<<", dear "<<player_name<<"! Let us now begin!"<<endl<<endl;
cont=continent_choice;
	srand(time(NULL));
	int bmi=rand()%6;
	ct[0]=cont-1;
	ct[1]=bmi;
	mcrb.disease=disease_choice;
	Biome[ct[0]][ct[1]].BCR=assignbcr(mcrb,Biome[ct[0]][ct[1]]);
	mcrb.countdn(ct,mcrb);
    sleep(2);
	
	for(int i=0;i<36;i++)
	{
		Biome[i][0].biometype=((i+1)%6)+1;
		Biome[i][0].continent=(i/6)+1;
	}	
	return 0;
}
