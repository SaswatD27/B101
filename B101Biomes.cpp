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
using namespace std;
class place
{
	int biometype,continent,bcr,cqr,disease;
	char name[50];
	place *neighbour[6];
	public:
	place()
	{
		cqr=0;
	}
	void gotoneigh(place *current)
	{
		int b;
		st:		
		b=(rand()%5)+1; 		
		if(*neighbour[b].cqr==0)
		current=this->neighbour[b];
		else
		{
			int chkemp=0;
			for(int i=0;i<5;i++)
			{
				if(*neighbour[i].cqr==0)
				chkemp=1;
			}
			if(chkemp=1)
			goto st;
			else
			cout<<endl<<"Continent CONQUERED!";
			//gotta think of intercontinental migration
		}
	}
	int assignbcr(int ncqr) //ncqr is a global/in scope int variable wrt to the object denoting how many biomes have been conquered 
	{
		bcr=5;
		int strength=0;
		switch (biometype)
		{
			case 1:if(disease==1||disease==4)
			       bcr--;
				else if(disease==3)
				bcr++;
				break;
			case 2:if(disease==3||disease==1)
			       bcr--;
				else if(disease==2)
				bcr++;
				break;
			case 3:if(disease==3||disease==4)
			       bcr--;
				else if(disease==1)
				bcr++;
				break;
			case 4:if(disease==2||disease==4)
			       bcr--;
				else if(disease==1)
				bcr++;
				break;
			case 5:if(disease==1||disease==2)
			       bcr--;
				else if(disease=4)
				bcr++;
				break;
			case 6:if(disease==2||disease==3)
			       bcr--;
				else if(disease==4)
				bcr++;
				break;
			default://Lol srsly?
				break;
	}
	int attack();
}Biome[36],*current;

int main()
{
	for(int i=0;i<36;i++)
	{
		Biome[i].biometype=((i+1)%6)+1;
		Biome[i].continent=(i/6)+1;
	}
	Biome[0].name="Gangetic Plains";
	Biome[1].name="Pamir Knot";
	Biome[2].name="Borneo";
	Biome[3].name="Karakum";
	Biome[4].name="Indian Peninsula";
	Biome[5].name="Indonesian Archipelago";
	Biome[6].name="Serengeti and Okavango Deltas";
	Biome[7].name="Kilimanjaro";
	Biome[8].name="Congo Rainforest";
	Biome[9].name="Sahara";
	Biome[10].name="Bight of Benin, Horn of Africa, Gulf of Africa";
	Biome[11].name="Madagascar";
	Biome[12].name="Pampas, Pantanal";
	Biome[13].name="Andes";
	Biome[14].name="Amazon";
	Biome[15].name="Atacama";
	Biome[16].name="Humboldt Current Region";
	Biome[17].name="Galapagos, Easter and Falkland";
	Biome[18].name="Prairies";
	Biome[19].name="Rockies";
	Biome[20].name="Central American Rainforest";
	Biome[21].name="Mojave";
	Biome[22].name="Eastern and Western Seaboard";
	Biome[23].name="Aleutians, Hawaii, Caribbean";	
	Biome[24].name="Canterbury";
	Biome[25].name="South Alps";		
	Biome[26].name="Papua New Guinea";
	Biome[27].name="Great Victoria Desert";
	Biome[28].name="Great Barrier Reef";
	Biome[29].name="South Pacific";
	Biome[30].name="Steppes";
	Biome[31].name="Alps";
	Biome[32].name="Taiga";
	Biome[33].name="Scandinavia";
	Biome[34].name="Baltic Coast";
	Biome[35].name="Spanish Islands";
	for(int i=0;i<36;i++)
	{
		for(int j=0,k=0;j<6;j++)
		{		
			if((i%6)!=j)
			{
				Biome[i].neighbour[k]=&Biome[6*(i/6)+j];
				k++;
			}
		}
	}
			
	return 0;
}
