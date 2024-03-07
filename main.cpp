#include <iostream>
#include <fstream>
#include <cmath>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <cstring>
#include <string>
#include <iomanip>

using namespace std;

///fstream fin2("matrice4.in");
ifstream fin("matrice4.in.txt");
///ofstream fout("matrice4.out.txt");

int n, v[100][100], v1[100][100], a;

///Numarul de cifre dintr-un numar
int nrcf(int x)
{
	int i = 2;
	while (x != 0)
	{
		x = x / 10;
		i++;
	}
	return i;
}

///Maximul dintr-o matrice
int maximul(int v2[100][100])
{
	int /*v0[2],*/ maxx = -1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int x = nrcf(v2[i][j]);
			if (x > maxx)
			{
				maxx = x;
				//v0[1] = i;
				//v0[2] = j;
			}
		}
	}
	return maxx;
}

///Transforma taote literele unui cuvant in litere mari
void literemari(char s[11])
{
	for (int i = 0; i <= strlen(s); i++)
	{
		if ((s[i] >= 97) && (s[i] <= 122))
		{
			s[i] = s[i] - 32;
		}
	}
}

///Inmulteste doua matrici
void inmultire(int v2[100][100], int v3[100][100], int mv[100][100])
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			int k = 0;
			for (int ii = 1; ii <= n; ii++)
			{
				k = k + (v2[i][ii] * v3[ii][j]);
			}
			mv[i][j] = k;
		}
	}
}

/*///Determinantul de gradul 2
int determinant2(int v2[100][100])
{
	LONGLONG s = 0;
	s = (v2[1][1] * v2[2][2]) - (v2[1][2] * v2[2][1]);
	return s;
}

///Determinant de gradul 3
int determinatnt3(int v2[100][100])
{
	LONGLONG s = 0;
	s = (v2[1][1] * v2[2][2] * v2[3][3]) + (v2[1][2] * v2[2][3] * v2[3][1]) + (v2[2][1] * v2[3][2] * v2[1][3]) - (v2[1][3] * v2[2][2] * v2[3][1]) - (v2[2][1] * v2[1][2] * v2[3][3]) - (v2[3][2] * v2[2][3] * v2[1][1]);
	return s;
}*/

///Creaza matricea care se inmulteste cu un numar
void matriceptnr(int mat[100][100], int temp[100][100], int p, int q, int n)
{
	int i = 1, j = 1;
	for (int row = 1; row <= n; row++)
	{
		for (int col = 1; col <= n; col++)
		{
			if (row != p && col != q)
			{
				temp[i][j++] = mat[row][col];
				if (j == n)
				{
					j = 1;
					i++;
				}
			}
		}
	}
}

///Determinant de n
int determinantNxN(int mat[100][100], int n)
{
	int D = 0;
	if (n == 1)
		return mat[1][1];
	int temp[100][100];
	int sign = -1;
	for (int f = 1; f <= n; f++)
	{
		matriceptnr(mat, temp, 1, f, n);
		D = D + (pow(sign, (1 + f)) * mat[1][f] * determinantNxN(temp, n - 1));
	}
	return D;
}

///Transforma un cuvant in numar (pentru subprogramul cu coordonate)
int cuvantnr(char s[11])
{
	int x = 0, b = 0;
	literemari(s);
	x = strcmp(s, "NORD");
	if (x == 0)
		b = 1;
	else if (x != 0)
	{
		x = strcmp(s, "SUD");
		if (x == 0)
			b = 2;
		else if (x != 0)
		{
			x = strcmp(s, "VEST");
			if (x == 0)
				b = 3;
			else if (x != 0)
			{
				x = strcmp(s, "EST");
				if (x == 0)
					b = 4;
				else if (x != 0)
					b = 0;
			}
		}
	}
	if (b == 0 && x != 0)
	{
		x = strncmp(s, "N", 1);
		if (x == 0)
			b = 1;
		else if (x != 0)
		{
			x = strncmp(s, "S", 1);
			if (x == 0)
				b = 2;
			else if (x != 0)
			{
				x = strncmp(s, "V", 1);
				if (x == 0)
					b = 3;
				else if (x != 0)
				{
					x = strncmp(s, "E", 1);
					if (x == 0)
						b = 4;
					else if (x != 0)
						b = 0;
				}
			}
		}
	}
	return b;
}


///Elementele deasupra diagonalei principale
void susdiagprin(int v3[100], int v0[100][100], int &x)
{
	x = 0;
	for (int i = 1; i <= n - 1; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			x++;
			v3[x] = v0[i][j];
		}
	}
}

///Elementele deasupra diagonalei secundare
void susdiagsec(int v3[100], int v0[100][100], int &x)
{
	x = 0;
	for (int i = 1; i <= n - 1; i++)
	{
		for (int j = 1; j <= n-i; j++)
		{
			x++;
			v3[x] = v0[i][j];
		}
	}
}

///Elementele de sub diagonala principala
void subdiagprin(int v3[100], int v0[100][100], int &x)
{
	x = 0;
	for (int i = 2; i <= n; i++)
	{
		for (int j = 1; j <= i - 1; j++)
		{
			x++;
			v3[x] = v0[i][j];
		}
	}
}

///Elementele de sub diagonala secundara
void subdiagsec(int v3[100], int v0[100][100], int &x)
{
	x = 0;
	for (int i = 2; i <= n; i++)
	{
		for (int j = n + 2 - i; j <= n; j++)
		{
			x++;
			v3[x] = v0[i][j];
		}
	}
}

///Sterge toate elementele din vector
void stergevec(int v3[100], int x)
{
	for (int i = 0; i <= x; i++)
	{
		v3[i] = 0;
	}
}

///Elementele dintr-un punct de coordonata
void coordonate(char s[11], int v0[100][100], int v3[100], int &b, int &b1)
{
	int x = 0;
	b1 = 0;
	stergevec(v3, 100);
	x = cuvantnr(s);
	switch (x)
	{
	case(1):
	{
		///NORD
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if ((i < j) && ((i + j) < (n + 1)))
				{
					b1++;
					v3[b1] = v0[i][j];
				}
			}
		}
		b = x;
		break;
	}
	case(2):
	{
		///SUD
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if ((i > j) && ((i + j) > (n + 1)))
				{
					b1++;
					v3[b1] = v0[i][j];
				}
			}
		}
		b = x;
		break;
	}
	case(3):
	{
		///VEST
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if ((i > j) && ((i + j) < (n + 1)))
				{
					b1++;
					v3[b1] = v0[i][j];
				}
			}
		}
		b = x;
		break;
	}
	case(4):
	{
		///EST
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if ((i < j) && ((i + j) > (n + 1)))
				{
					b1++;
					v3[b1] = v0[i][j];
				}
			}
		}
		b = x;
		break;
	}
	default:
		b = -1;
		break;
	}
}

///Scrie coordonata
void coordonatascrie(int x)
{
	if (x == 1)
		cout << "Elementele de pe pozitile din nord sunt: ";
	else if (x == 2)
		cout << "Elementele de pe pozitile din sud sunt: ";
	else if (x == 3)
		cout << "Elementele de pe pozitile din vest sunt: ";
	else if (x == 4)
		cout << "Elementele de pe pozitile din sud sunt: ";
	else
		cout << "Ai gresit cand ai introdus coordonata";
}

///Transpusa unei matrici
void transpusa(int mat[100][100], int temp[100][100])
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			temp[i][j] = mat[j][i];
			temp[j][i] = mat[i][j];
		}
	}
}

///Scrierea matricilor
void scrie(int ok, int v2[100][100], int v3[100][100])
{
	int x = maximul(v2), y = maximul(v3);
	if (x < y)
		x = y;
	for (int i = 1; i <= n; i++)
	{
		if ((ok == 0) && (i == n / 2))
		{
			cout << " A=| ";
		}
		else if ((ok == 1) && (i == (n / 2) + 1))
		{
			cout << " A=| ";
		}
		else
		{
			cout << "   | ";
		}
		for (int j = 1; j <= n; j++)
		{
			cout << setw(x) << v2[i][j] << " ";
		}
		cout << "|";
		if ((ok == 0) && (i == n / 2))
		{
			cout << "\t\t\t B=| ";
		}
		else if ((ok == 1) && (i == (n / 2) + 1))
		{
			cout << "\t\t\t B=| ";
		}
		else
		{
			cout << "\t\t\t   | ";
		}
		for (int j = 1; j <= n; j++)
		{
			cout << setw(x) << v3[i][j] << " ";
		}
		cout << "|";
		cout << endl;
	}
}

///Scrie o singura matrice
void scriematrice(int v0[100][100], int ok, int nr, int lit)
{
	for (int i = 1; i <= n; i++)
	{
		if ((ok == 0) && (i == n / 2))
		{
			cout << " " << char(lit) << "=| ";
		}
		else if ((ok == 1) && (i == (n / 2) + 1))
		{
			cout << " " << char(lit) << "=| ";
		}
		else
		{
			cout << "   | ";
		}
		for (int j = 1; j <= n; j++)
		{
			cout << setw(nr) << v0[i][j] << " ";
		}
		cout << "|" << endl;
	}
}

///Scrie o singura matrice cu numere cu virgula
void scriematriceV(double v0[100][100], int ok, int nr, int lit)
{
	for (int i = 1; i <= n; i++)
	{
		if ((ok == 0) && (i == n / 2))
		{
			cout << " " << char(lit) << "=| ";
		}
		else if ((ok == 1) && (i == (n / 2) + 1))
		{
			cout << " " << char(lit) << "=| ";
		}
		else
		{
			cout << "   | ";
		}
		for (int j = 1; j <= n; j++)
		{
			cout << setw(nr) << v0[i][j] << " ";
		}
		cout << "|" << endl;
	}
}

int main()
 {
	system("Color B4");
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 970, 690, TRUE);
	cout << "\t\t\t\t\t    Aplicatie Informatica    \t\t\t\t\t" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t Autor: Carp Petru" << endl << endl;
	cout << "\t\t\t\t      /" << char(92) << "                  /" << char(92) << "   \t\t\t\t\t" << endl;
	cout << "\t\t\t\t     /||" << char(92) << "                /||" << char(92) << "  \t\t\t\t\t" << endl;
	cout << "\t\t\t\t    / || " << char(92) << "              / || " << char(92) << " \t\t\t\t\t" << endl;
	cout << "\t\t\t\t   /  ||  " << char(92) << "            /  ||  " << char(92) << "\t\t\t\t\t" << endl << endl;
	cout << "\t\t\t\t         /" << char(92) << "            /" << char(92) << "\t\t\t\t\t" << endl;
	cout << "\t\t\t\t        /  " << char(92) << "          /  " << char(92) << "\t\t\t\t\t" << endl;
	cout << "\t\t\t\t       / /" << char(92) << " " << char(92) << "        / /" << char(92) << " " << char(92) << "\t\t\t\t\t" << endl << endl;
	cout << "\t\t\t\t          _      _      _ \t\t\t\t\t" << endl;
	cout << "\t\t\t\t           " << char(92) << "    / " << char(92) << "    / \t\t\t\t\t" << endl;
	cout << "\t\t\t\t            " << char(92) << "__/   " << char(92) << "__/  \t\t\t\t\t" << endl << endl << endl;
	cout << "Apsati enter pentru a merge la declararea matricilor . . .";
	cin.get();
	do
	{
		a = 0;
		system("cls");
		cout << "\t\t\t--== Cum doriti sa declarati matricile de numere? ==--\t\t\t\t" << endl << endl << endl;
		cout << "1. Citeste de la tastatura valorile matricilor. (tastati 1)" << endl;
		cout << "2. Citeste dintr-un fisier niste valuri prestabilite. (tastati 2)" << endl;
		cout << "3. Atribuie valori aleatori matricilor. (tasta 3)" << endl;
		cout << "Scrieti numarul: ";
		cin >> a;
		system("cls");
		switch (a)
		{
		case(1):
		{
			cout << "Un numar pentru cate elemente sa aiba matricea pe o linie si pe coloana: ";
			cin >> n;
			cout << endl << "Declararea primei matrici matrice: "<<endl;
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					cout << "A[" << i << "]" << "[" << j << "]= ";
					cin >> v[i][j];
				}
			}
			cout << "Prima matricea a fost citita.";
			system("pause");
			system("cls");
			cout << "Declararea celei de a doua matrice:" << endl;
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					cout << "B[" << i << "]" << "[" << j << "]= ";
					cin >> v1[i][j];
				}
			}
			system("pause");
			break;
		}
		case(2):
		{
			fin >> n;
			int ok = n % 2;
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					fin >> v[i][j];
				}
			}
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					fin >> v1[i][j];
				}
			}
			cout << "Matricile a fost citite." << endl;
			cout << "Acestea sunt matricile: "<<endl;
			scrie(ok,v,v1);
			cout << endl;
			system("pause");
			break;
		}
		default:
			int b = 99, m = 99, ok;
			cout << "Doriti sa puneti un interval? [1(DA)/0(NU)]: ";
			cin >> ok;
			if (ok == 1)
			{
				cout << "Limita superioara: ";
				cin >> b;
				cout << "Limita inferioara: ";
				cin >> m;
			}
			if (m > b)
			{
				int aux = b;
				b = m;
				m = aux;
			}
			cout << endl;
			cout << "Un numar pentru cate elemente sa aiba matricile pe coloana si pe linie: ";
			cin >> n;
			ok = n % 2;
			srand(time(NULL));
			if (b != 99 && m != 99)
			{
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						v[i][j] = rand() % (b - m) + m;
					}
				}
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						v1[i][j] = rand() % (b - m) + m;
					}
				}
			}
			else
			{
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						v[i][j] = (rand() % b) - (rand() % m);
					}
				}
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						v1[i][j] = (rand() % b) - (rand() % m);
					}
				}
			}
			cout << "Matricile a fost citite." << endl;
			cout << "Acesta sunt matricile: " << endl;
			scrie(ok,v,v1);
			cout << endl;
			system("pause");
			break;
		}
		do
		{
			a = 0;
			int ok = n % 2;
			system("cls");
			cout << "\t\t\t\t\t -= Meniu =- \t\t\t\t\t" << endl << endl << endl;
			cout << "Matricile sunt: " << endl;
			scrie(ok,v,v1);
			cout << endl << endl;
			cout << "1. Se va afisa suma celor doua matrici." << endl;
			cout << "2. Se va afisa scaderea celor doua matrici." << endl;
			cout << "3. Se va afisa inmultirea matricilor." << endl;
			cout << "4. Se vor afisa elementele din matricea A in functie de diagonale." << endl;
			cout << "5. Se vor afisa elementele din matricea B in functie de diagonale." << endl;
			cout << "6. Se vor afisa elementele dintr-un punct de coordonata." << endl;
			cout << "7. Se va afisa transpusa unei matrici la alegere." << endl;
			cout << "8. Se va afisa una dintre matrici la o putere aleasa(nu mai mare de 10)." << endl;
			cout << "9. Se va afisa determinantul unei matrici." << endl;
			cout << "10. Se va afisa inversul unei matrici." << endl;
			cout << "11. Acest comanda va intoarece la citirea vectorului." << endl << endl;
			cout << "12. Iesire." << endl;
			cout << "Tastati numarul problemei pe care o doriti sa o rezolve: ";
			cin >> a;
			system("cls");
			switch (a)
			{
			case(1):
			{
				int mv[100][100];
				for (int i = 1; i <= n; i++)
				{
					for (int j = 1; j <= n; j++)
					{
						mv[i][j] = v[i][j] + v1[i][j];
					}
				}
				cout << endl << "Adunarea celor doua matrici a fost executata cu succes.Aceasta este matricea:" << endl << endl;
				scriematrice(mv, ok, maximul(mv),83);
				cout << endl;
				system("pause");
				break;
			}
			case(2):
			{
				int mv[100][100], b;
				cout << "Din care matrice doriti sa o scadeti pe cealalta (A-B(1) sau B-A(2)):";
				cin >> b;
				switch (b)
				{
				case(2):
				{
					for (int i = 1; i <= n; i++)
					{
						for (int j = 1; j <= n; j++)
						{
							mv[i][j] = v1[i][j] - v[i][j];
						}
					}
					break;
				}
				default:
					for (int i = 1; i <= n; i++)
					{
						for (int j = 1; j <= n; j++)
						{
							mv[i][j] = v[i][j] - v1[i][j];
						}
					}
					break;
				}
				cout << endl << "Scaderea celor doua matrici a fost executata cu succes. Aceasta este matricea:" << endl << endl;
				scriematrice(mv, ok, maximul(mv),83);
				cout << endl;
				system("pause");
				break;
			}
			case(3):
			{
				int mv[100][100], b;
				inmultire(v, v1, mv);
				cout << "Inmultirea celor doua matrici a fost executata cu succes. Aceasta este matricea:" << endl << endl;
				scriematrice(mv, ok, maximul(mv),80);
				cout << endl << "Doriti sa vedeti un element cum a fost calculat [DA(1)/NU(0)]: ";
				cin >> b;
				switch (b)
				{
				case(1):
				{
					int x = 0, y = 0;
					cout << endl << "Care este elemtntul pe care doriti sa il vedeti cum a fost calculat: " << endl << "i(linia)= ";
					cin >> x;
					cout << "j(coloana)= ";
					cin >> y;
					if (x > n || y > n)
					{
						cout << "Ok. Deci nu doresti..." << endl;
					}
					else
					{
						cout << endl << "Aceasta este operatia prin care sa calculat elementul matricilor inmultite: " << endl;
						cout << "\t";
						for (int i = 1; i <= n; i++)
						{
							cout << "(" << v[x][i] << ")" << "*" << "(" << v1[i][y] << ")";
							if (i != n)
								cout << " + ";
							else
								cout << " ";
						}
						cout << "= " << mv[x][y];
						cout << endl;
					}
				}
				default:
					cout << "Ai introdus o valoare gresita." << endl;
					break;
				}
				system("pause");
				break;
			}
			case(4):
			{
				int b, v0[1000], x = 0, b1;
				cout << "Acesta este matricea din care o sa lucram: " << endl;
				scriematrice(v, ok, maximul(v),65);
				cout << endl << "In functie de ce diagonala doriti sa vedeti elementele (cea principala (apasa 1) sau cea secundara (apasa 2) ): ";
				cin >> b;
				switch (b)
				{
				case(1):
				{
					b1 = 0;
					cout << endl << "Elmentele se impart in doua categori cele de deasupra diagoanle (apasa 1) sau cele de sub diagonala (apasa 2): ";
					cin >> b1;
					if (b1 == 1)
					{
						cout << endl << "Elementele de deasupara diagonalei princilpale sunt: ";
						susdiagprin(v0, v, x);
						for (int i = 1; i <= x; i++)
							cout << v0[i] << " ";
						cout << endl;
						stergevec(v0,x);
					}
					else if (b1 == 2)
					{
						cout << endl << "Elementele de sub diagonala principala sunt: ";
						subdiagprin(v0, v, x);
						for (int i = 1; i <= x; i++)
							cout << v0[i] << " ";
						cout << endl;
						stergevec(v0,x);
					}
					else
						break;
					system("pause");
					break;
				}
				case(2):
				{
					b1 = 0;
					cout << endl << "Elmentele se impart in doua categori cele de deasupra diagoanle (apasa 1) sau cele de sub diagonala (apasa 2): ";
					cin >> b1;
					if (b1 == 1)
					{
						cout << endl << "Elementele de deasupara diagonalei secundare sunt: ";
						susdiagsec(v0, v, x);
						for (int i = 1; i <= x; i++)
							cout << v0[i] << " ";
						cout << endl;
						stergevec(v0, x);
					}
					else if (b1 == 2)
					{
						cout << "Elementele de sub diagonala secundara sunt: ";
						subdiagsec(v0, v, x);
						for (int i = 1; i <= x; i++)
							cout << v0[i] << " ";
						cout << endl;
						stergevec(v0, x);
					}
					else
						break;
					system("pause");
					break;
				}
				default:
					cout << "Ai introdus o valoare gresita." << endl;
					break;
				}
				break;
			}
			case(5):
			{
				int b, v0[1000], x = 0, b1;
				cout << "Acesta este matricea din care o sa lucram: " << endl;
				scriematrice(v1, ok, maximul(v1),66);
				cout << endl << "In functie de ce diagonala doriti sa vedeti elementele (cea principala (apasa 1) sau cea secundara (apasa 2) ): ";
				cin >> b;
				switch (b)
				{
				case(1):
				{
					b1 = 0;
					cout << endl << "Elmentele se impart in doua categori cele de deasupra diagoanle (apasa 1) sau cele de sub diagonala (apasa 2): ";
					cin >> b1;
					if (b1== 1)
					{
						cout << endl << "Elementele de deasupara diagonalei princilpale sunt: ";
						susdiagprin(v0, v1, x);
						for (int i = 1; i <= x; i++)
							cout << v0[i] << " ";
						cout << endl;
						stergevec(v0, x);
					}
					else if (b1 == 2)
					{
						cout << endl << "Elementele de sub diagonala principala sunt: ";
						subdiagprin(v0, v1, x);
						for (int i = 1; i <= x; i++)
							cout << v0[i] << " ";
						cout << endl;
						stergevec(v0, x);
					}
					else
						break;
					system("pause");
					break;
				}
				case(2):
				{
					b1 = 0;
					cout << endl << "Elmentele se impart in doua categori cele de deasupra diagoanle (apasa 1) sau cele de sub diagonala (apasa 2): ";
					cin >> b1;
					if (b1 == 1)
					{
						cout << endl << "Elementele de deasupara diagonalei secundare sunt: ";
						susdiagsec(v0, v1, x);
						for (int i = 1; i <= x; i++)
							cout << v0[i] << " ";
						cout << endl;
						stergevec(v0, x);
					}
					else if (b1 == 2)
					{
						cout << "Elementele de sub diagonala secundara sunt: ";
						subdiagsec(v0, v1, x);
						for (int i = 1; i <= x; i++)
							cout << v0[i] << " ";
						cout << endl;
						stergevec(v0, x);
					}
					else
						break;
					system("pause");
					break;
				}
				default:
					cout << "Ai introdus o valoare gresita." << endl;
					break;
				}
				break;
			}
			case(6):
			{
				int b = 0, x = 0, v3[100], b1 = 0;
				char s[11];
				cout << endl << "Din care matrice doriti sa vedeti elemntele (pentru A(apasa 1), pentru B(apasa 2)): ";
				cin >> b;
				stergevec(v3, 100);
				switch (b)
				{
				case(1):
				{
					cout << endl;
					scriematrice(v, ok, maximul(v),65);
					cout << endl << "Scrie coordonata din care vrei sa apara elementele(Nord(in partea de sus), Sud(in partea de jos), Vest(in partea din stanga), Est(in partea din dreapta)): " << endl;
					cin >> s;
					coordonate(s, v, v3, x, b1);
					coordonatascrie(x);
					for (int i = 1; i <= b1; i++)
					{
						cout << v3[i] << " ";
					}
					cout << endl;
					system("pause");
					break;
				}
				case(2):
				{
					cout << endl;
					scriematrice(v1, ok, maximul(v1),66);
					cout << endl << "Scrie coordonata din care vrei sa apara elementele(Nord(in partea de sus), Sud(in partea de jos), Vest(in partea din stanga), Est(in partea din dreapta)): " << endl;
					cin >> s;
					coordonate(s, v1, v3, x, b1);
					coordonatascrie(x);
					for (int i = 1; i <= b1; i++)
					{
						cout << v3[i] << " ";
					}
					cout << endl;
					system("pause");
					break;
				}
				default:
					cout << "Ai introdus o valoare gresita." << endl;
					break;
				}
				break;
			}
			case(7):
			{
				int b = 0, v2[100][100];
				cout << "Din care matrice doriti sa vedeti transpusa(pentru A(apasa 1) si pentru B(apsa 2)): ";
				cin >> b;
				switch (b)
				{
				case(1):
				{
					cout << "Asa arata matricea: " << endl << endl;
					scriematrice(v, ok, maximul(v),65);
					cout << endl << "Iar aceasta este transpusa matrici A: " << endl << endl;
					transpusa(v, v2);
					scriematrice(v2, ok, maximul(v2),84);
					cout << endl;
					system("pause");
				}
				case(2):
				{
					cout << "Asa arata matricea: " << endl << endl;
					scriematrice(v1, ok, maximul(v1),65);
					cout << endl << "Iar aceasta este transpusa matrici B: " << endl << endl;
					transpusa(v1, v2);
					scriematrice(v2, ok, maximul(v2),84);
					cout << endl;
					system("pause");
				}
				default:
					cout << "Ai introdus o valoare gresita." << endl;
					break;
				}
				break;
			}
			case(8):
			{
				int b = 0, b1 = 0;
				int mv[100][100];
				cout << "La ce putere doriti sa fie matricea A sau B(dar nu mai mare de 10): ";
				cin >> b;
				if (b == 0)
				{
					cout << "Toate elemntele din matrice, orice matrice ar fi, sunt 0, iar matricea arata asa: " << endl;
					scriematrice(mv, ok, 2, 79);
				}
				else if ((b > 0) && (b <= 10))
				{
					cout << endl << "Alege care matrice doresti sa fie adusa la puterea " << b << " (pentru A(apasa 1), iar pentru B(apasa 2)): ";
					cin >> b1;
					cout << endl;
					switch (b1)
					{
					case(1):
					{
						inmultire(v, v, mv);
						for (int i = 2; i <= b; i++)
						{
							inmultire(mv, v, mv);
						}
						cout << "Aducerea la puterea " << b << " a fost executata cu succes. Aceasta este matricea: " << endl;
						scriematrice(mv, ok, maximul(mv), 65);
						break;
					}
					case(2):
					{
						inmultire(v1, v1, mv);
						for (int i = 2; i <= b; i++)
						{
							inmultire(mv, v1, mv);
						}
						cout << "Aducerea la puterea " << b << " a fost executata cu succes. Aceasta este matricea: " << endl;
						scriematrice(mv, ok, maximul(mv), 66);
						break;
					}
					default:
						cout << "Ai introdus o valoare gresita." << endl;
						break;
					}
				}
				else if ((b < 0) || (b > 10))
				{
					cout << "Ai introdus o valoare gresita." << endl;
				}
				system("pause");
				break;
			}
			case(9):
			{
				int b = 0;
				cout << "Pentru care matrice doriti sa vedeti determinantul(pentru A(apasa 1), iar pentru B(apasa 2)): ";
				cin >> b;
				switch (b)
				{
				case(1):
				{
					cout << endl << "Acesta este determinantul lui A: " << determinantNxN(v, n) << endl;
					break;
				}
				case(2):
				{
					cout << endl << "Acesta este determinantul lui B: " << determinantNxN(v1, n) << endl;
					break;
				}
				default:
					cout << endl << "Ai introdus o valoare gresita.";
					break;
				}
				system("pause");
				break;
			}
			case(10):
			{
				int b = 0, mat[100][100];
				double x1 = 0, temp[100][100];
				cout << "Inversul carei matrici doriti sa o vedeti(pentru A(apasa 1),iar pentru B(apasa 2)): ";
				cin >> b;
				switch (b)
				{
				case(1):
				{
					cout << "Aceasta este matricea: " << endl;
					scriematrice(v, ok, maximul(v), 'A');
					cout << endl << endl << "Acesta este inversa matrici A: " << endl;
					x1 = determinantNxN(v, n);
					if (x1 != 0)
					{
						x1 = 1 / x1;
						transpusa(v, mat);
						for (int i = 1; i <= n; i++)
						{
							for (int j = 1; j <= n; j++)
							{
								int temp1[100][100];
								matriceptnr(mat, temp1, i, j, n);
								temp[i][j] = pow(-1, (i + j + 1)) * determinantNxN(temp1, n - 1);
								temp[i][j] = x1 * temp[i][j];
							}
						}
						scriematriceV(temp, ok, 10, 'A');
					}
					else
					{
						cout << "Inversul matrici A nu se poate calcula deoarece A are determinantul egal cu 0."<<endl;
					}
					break;
				}
				case(2):
				{
					cout << "Aceasta este matricea: " << endl;
					scriematrice(v1, ok, maximul(v1), 'B');
					cout << endl << endl << "Acesta este inversa matrici B: " << endl;
					x1 = determinantNxN(v1, n);
					if (x1 != 0)
					{
						x1 = 1 / x1;
						transpusa(v1, mat);
						for (int i = 1; i <= n; i++)
						{
							for (int j = 1; j <= n; j++)
							{
								int temp1[100][100];
								matriceptnr(mat, temp1, i, j, n);
								temp[i][j] = pow(-1, (i + j + 1)) * determinantNxN(temp1, n - 1);
								temp[i][j] = x1 * temp[i][j];
							}
						}
						scriematriceV(temp, ok, 10, 'B');
					}
					else
					{
						cout << "Inversul matrici A nu se poate calcula deoarece A are determinantul egal cu 0." << endl;
					}
					break;
				}
				default:
					cout << endl << "Ai introdus o valoare gresita." << endl;
					break;
				}
				system("pause");
				break;
			}
			default:
				break;
			}
		} while (a != 11 && a != 12);
	} while (a != 12);
	system("cls");
	cout << "Ati iesit din aplicatie. Va multumesc pentru ca ati incercat-o." << endl;

	fin.close();
	return 0;
}
