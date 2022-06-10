#include <iostream>
#include <cassert>
class MedalRow
{
	char country[4];
	int medals[3];
public:
	static const int GOLD{ 0 };
	static const int SILVER{ 1 };
	static const int BRONZE{ 2 };
	MedalRow(const char* countryP, const int* medalsP)
	{
		strcpy_s(country, 4, countryP ? countryP : "NON");
		for (int i{ 0 }; i < 3; ++i)
		{
			medals[i] = medalsP ? medalsP[i] : 0;
		}
	}
	MedalRow() : MedalRow(nullptr, nullptr) {};
	MedalRow& setCountry(const char* countryP)
	{
		if (countryP)
		{
			strcpy_s(country, 4, countryP);
		}
		return *this;
	}
	const char* getCountry()const { return country; }

		int& operator[](int idx)
	{
		assert((idx >= 0 and idx < 3) and "Index out "
			"of range!");
		return medals[idx];
	}
	int operator[](int idx)const
	{
		assert((idx >= 0 and idx < 3) and "Index out "
			"of range!");
		return medals[idx];
	}
	friend std::ostream& operator << (std::ostream& out, MedalRow& instance)
	{
		out << '[' << instance.country << "]-( ";
		for (int i{ 0 }; i < 3; ++i)
		{
			out << instance.medals[i];
			if (i < 2) { std::cout << '\t'; }
		}
		out << " )\n";
		return out;
	}
};
class MedalsTable
{
public:
	static const int maxSize{ 10 };
private:
	MedalRow* medalRows;
	int size;
	int findCountry(const char* country)const
	{
		for (int i{ 0 }; i < size; ++i)
		{

				if (strcmp(medalRows[i].getCountry(),
					country) == 0)
				{
					return i;
				}
		}
		return -1;
	}
	void addRow()
	{
		MedalRow* temp = new MedalRow[size];
		for (int i = 0; i < size - 1; i++)
		{
			temp[i] = medalRows[i];
		}
		delete[] medalRows;
		medalRows = new MedalRow[size];
		for (int i = 0; i < size - 1; i++)
		{
			medalRows[i] = temp[i];
		}
		delete[] temp;
	}
	
public:
	~MedalsTable()
	{
		delete[] medalRows;
		medalRows = nullptr;
	}
	MedalsTable() : size{ 0 } 
	{
		medalRows = new MedalRow[size];
	};
	 MedalsTable(MedalsTable& instance)
	{
		 this->size = instance.size;
		 this->medalRows = new MedalRow[size];
		 for (int i = 0; i < size; i++)
		 { 
			 this->medalRows[i] = instance.medalRows[i];
		 }
	}
	MedalRow& operator[](const char* country)
	{
		int idx{ findCountry(country) };
		if (idx == -1)
		{
			assert(size < MedalsTable::maxSize and
				"Table is FULL!");
			idx = size++;
			addRow();
			medalRows[idx].setCountry(country);
		}
		return medalRows[idx];
	}
	const MedalRow& operator[](const char* country)const
	{
		int idx{ findCountry(country) };
		assert(idx != -1 and "Country not found on const "
			"table");
		return medalRows[idx];
	}
	friend std::ostream& operator << (std::ostream& out, MedalsTable& instance)
	{

			for (int i{ 0 }; i < instance.size; ++i)
			{
				out << instance.medalRows[i];
			}
			return out;
	}
};
int main()
{
	MedalsTable mt1;
	std::cout << "Medals table #1:\n";
	mt1["UKR"][MedalRow::GOLD] = 14;
	mt1["UKR"][MedalRow::SILVER] = 5;
	mt1["HUN"][MedalRow::BRONZE] = 9;
	mt1["HUN"][MedalRow::GOLD] = 7;
	mt1["POL"][MedalRow::GOLD] = 4;
	mt1["POL"][MedalRow::SILVER] = 2;
	std::cout << mt1;
	std::cout << "\nMedals table #2:\n";
	MedalsTable mt2 = mt1;
	std::cout << mt2;
	mt1["POL"][MedalRow::BRONZE] = 2;
	std::cout << "\nMedals table mt1(pol bronze 2 added):\n";
	std::cout << mt1;
	std::cout << "\nMedals table mt2(nothing added):\n";
	std::cout << mt2;
	return 0;
}