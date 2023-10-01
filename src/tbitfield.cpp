// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
	{
		throw -1;

    }
	else
	{
		BitLen = len;
		MemLen = len / 32 + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen / 32 + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n > BitLen-1 || n < 0)
	{
		throw " index out of range";
	}
	return n / 32; //(sizeof(TELEM) * 8);//32
		
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM t = 1;
	int shift = n % 32;
	TELEM res = t << shift;
	return res;

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{

  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n > BitLen-1 || n < 0)
	{
		throw " index out of range";
	}
	pMem[n] = 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n > BitLen-1 || n < 0)
	{
		throw " index out of range";
	}
	pMem[n] = 0;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n > BitLen - 1 || n < 0)
	{
		throw " index out of range";
	}
  return pMem[n];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	delete[] pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[BitLen];
	for (int i = 0; i < BitLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return false;

    }
	for (int i = 0; i < BitLen; i++)
	{
		if (pMem[i] != bf.pMem[i])
		{
			return false;
		}
	}
	return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen != bf.BitLen)
	{
		throw "bifield sizes are not equal ";
	}
	TBitField res(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		res.pMem[i] = (pMem[i] | bf.pMem[i]);
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen != bf.BitLen)
	{
		throw "bifield sizes are not equal ";
	}
	TBitField res(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		res.pMem[i] = (pMem[i] & bf.pMem[i]);
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		res.pMem[i] = !(pMem[i]);
	}
	return res;

}

// ввод/вывод

 istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	for (int i = 0; i < bf.BitLen; i++)
	{

		cin >> bf.pMem[i];
	}
	return istr;

}

  ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{

		cout << bf.pMem[i];
	}
	return ostr;

}
