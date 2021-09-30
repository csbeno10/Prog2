#include "std_lib_facilities.h"

struct Lap {
	string szim="";
	int ertek = 0;
	bool volt = false;

	Lap() {};
	Lap(string sz, int ert) : szim{ sz }, ertek{ ert } {};

};

void Huzas(vector<Lap>& pakli, vector<Lap>& vec, int& szum)
{
	int hanyas;
	hanyas = rand() % pakli.size();
	if (pakli[hanyas].volt == true) Huzas(pakli, vec, szum);
	else
	{
		Lap l = pakli[hanyas];
		pakli[hanyas].volt = true;
		cout << l.szim << " ";
		vec.push_back(l);
		szum += l.ertek;
	}
}

bool Aszkereso(vector<Lap>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i].szim == "A" && vec[i].ertek==11)
		{
			vec[i].ertek = 1;
			return true;
		}
	}
	return false;
}

void Pakli(vector<Lap> lapok, vector<Lap>& pakli, int db)
{
	for (int i = 0; i < lapok.size(); i++)
	{
		for (int j = 0; j < db*4; j++)
		{
			pakli.push_back(lapok[i]);
		}
	}
}


int main()
{
	Lap kettes("2",2),harmas("3",3), negyes("4",4), otos("5",5), hatos("6",6), hetes("7",7), nyolcas("8",8), kilences("9",9), tizes("10",10), J("J",10), Q("Q",10), K("K",10), A("A",11);
	vector<Lap> lapok{ kettes,harmas,negyes,otos,hatos,hetes,nyolcas,kilences,tizes,J,Q,K,A };
	vector<Lap> bank, player, pakli;
	int banksz=0, playersz=0, pakliszam=1;
	bool bust = false, pblackjack = false, bblackjack = false;
	srand(time(NULL));


	//cout << "Hany paklival jatszunk? " << endl;
	//cin >> pakliszam;


	Pakli(lapok, pakli, pakliszam);
	cout << "Bank kezdese: ";
	Huzas(pakli,bank,banksz);
	cout << endl << "Jatekos kezdese: ";
	Huzas(pakli, player, playersz);
	Huzas(pakli, player, playersz);
	if (playersz == 21)
	{
		cout << endl << "BLACKJACK! " << endl;
		pblackjack = true;
	}
	else
	{
		cout << endl << "Jatekos erteke: " << playersz;
		cout << endl << "Kersz lapot? (igen:y nem:n) " << endl;
		char be;
		while (cin >> be)
		{
			if (be != 'y' && be != 'n') cout << "Soha nem volt opcio" << endl;
			else
			{
				if (be == 'y')
				{
					cout << "Huzott lap: ";
					Huzas(pakli, player, playersz);
					cout << "Jelenlegi ertek: " << playersz << endl;
					if (playersz > 21)
					{
						if (Aszkereso(player))
						{
							playersz -= 10;
							cout << "Asz miatt a jatekos uj erteke: " << playersz << endl;
						}
						else
						{
							cout << "Vesztettel! " << endl;
							bust = true;
							break;
						}
					}
					if (playersz == 21) break;
				}
				else break;
			}
		}
	}
	if (bust == false)
	{
		while (banksz < 17)
		{
			cout << "Bank alltal huzott lap: ";
			Huzas(pakli, bank, banksz);
			cout << endl;
			if (banksz == 21 && bank.size() == 2)
			{
				cout << "BLACKJACK A BANKNAK!" << endl;
				bblackjack = true;
			}
			else if (banksz > 21)
			{
				if (Aszkereso(bank)) banksz -= 10;
			}
		}
		if (bblackjack == false)cout << "Bank erteke: " << banksz << endl;

		if (banksz > 21) cout << "Nyertel! " << endl;
		else if (playersz < banksz) cout << "Vesztettel! " << endl;
		else if (playersz > banksz) cout << "Nyertel! " << endl;
		else if (playersz == banksz)
		{
			if (bblackjack == false && pblackjack == true) cout << "Nyertel! " << endl;
			else if (bblackjack == true && pblackjack == false) cout << "Vesztettel! " << endl;
			else cout << "Dontetlen! " << endl;
		}
	}

}
