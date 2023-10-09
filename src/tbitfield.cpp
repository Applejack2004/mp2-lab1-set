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
	TELEM m = GetMemMask(n);
	int ind = GetMemIndex(n);
	pMem[ind] = pMem[ind] | m;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n > BitLen-1 || n < 0)
	{
		throw " index out of range";
	}
	TELEM m = ~(GetMemMask(n));
	int ind = GetMemIndex(n);
	pMem[ind] = pMem[ind] & m;
    
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n > BitLen - 1 || n < 0)
	{
		throw " index out of range";
	}
	TELEM m = (GetMemMask(n));
	int ind = GetMemIndex(n);
	TELEM res = pMem[ind] & m;
	return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if ((bf.MemLen != MemLen))
	{
		delete[] pMem;
    }
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	//if (&bf == nullptr)
	//{
	//	throw "bf=null ptr";
	//}
	if (BitLen != bf.BitLen)
	{
		return false;

    }
	for (int i = 0; i< MemLen-1; i++)
	{
		if (pMem[i] != bf.pMem[i])
		{
			return false;
		}
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
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
	//int MEMmin = 0;
	//int MEMmax = 0;
	//if (BitLen != bf.BitLen)
	//{
	//	int max = bf.BitLen;
	//	int min = BitLen;
	//	if (BitLen > bf.BitLen)
	//	{
	//		max = BitLen;
	//		min = bf.BitLen;
	//	}
	//	if (min == BitLen)
	//	{
	//		MEMmin = MemLen;
	//	}
	//	else
	//	{
	//		MEMmin = bf.MemLen;
	//	}

	//	TBitField res(max);
	//	if (max == BitLen)
	//	{
	//		for (int i = 0; i < MemLen; i++)
	//		{
	//			res.pMem[i] = pMem[i];
	//		}
	//		for (int i = 0; i < MEMmin - 2; i++)
	//		{
	//			res.pMem[i] = (bf.pMem[i] | res.pMem[i]);
	//		}
	//		for (int k = (MEMmin - 1) * 32; k < min; k++)
	//		{
	//			if ((bf.GetBit(k) | res.GetBit(k)) == 0)
	//			{
	//				res.ClrBit(k);
	//			}
	//			else
	//			{
	//				res.SetBit(k);
	//			}


	//		}
	//		//TBitField help(bf);


	//		TBitField help(bf);

	//		for (int k = min; k < (MEMmin * 32) - 1; k++)
	//		{


	//			help.ClrBit(k);
	//			if (res.GetBit(k) | help.GetBit(k) == 0)
	//			{
	//				res.ClrBit(k);
	//			}
	//			else
	//			{
	//				res.SetBit(k);
	//			}

	//		}

	//	}
	//	else
	//	{
	//		for (int i = 0; i < bf.MemLen; i++)
	//		{
	//			res.pMem[i] = bf.pMem[i];
	//		}
	//		for (int i = 0; i < MEMmin - 2; i++)
	//		{
	//			res.pMem[i] = (this->pMem[i] | res.pMem[i]);
	//		}
	//		for (int k = (MEMmin - 1) * 32; k < min; k++)
	//		{
	//			if ((this->GetBit(k) | res.GetBit(k)) == 0)
	//			{
	//				res.ClrBit(k);
	//			}
	//			else
	//			{
	//				res.SetBit(k);
	//			}


	//		}
	//		//TBitField help(bf);




	//		for (int k = min; k < (MEMmin * 32) - 1; k++)
	//		{


	//			this->ClrBit(k);
	//			if (res.GetBit(k) | this->GetBit(k) == 0)
	//			{
	//				res.ClrBit(k);
	//			}
	//			else
	//			{
	//				res.SetBit(k);
	//			}

	//		}
	//	}
	//	return res;
	//}
	//else
	//{
	//	int maxl = BitLen;
	//	TBitField res(maxl);
	//	for (int i = 0; i < MemLen; i++)
	//	{
	//		res.pMem[i] = pMem[i];
	//	}
	//	for (int i = 0; i < bf.MemLen; i++)
	//	{
	//		res.pMem[i] = bf.pMem[i] | res.pMem[i];
	//	}
	//	return res;
 //   }

int min_len = bf.MemLen < this->MemLen ? bf.MemLen : this->MemLen;
int min_bit_len = bf.BitLen < this->BitLen ? bf.BitLen : this->BitLen;
int max_bit_len = bf.BitLen > this->BitLen ? bf.BitLen : this->BitLen;
TBitField res = TBitField(max_bit_len);
for (size_t i = 0; i < min_len; i++)
{
	res.pMem[i] = this->pMem[i] | bf.pMem[i];
}
return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	//int MEMmin = 0;
	//int MEMmax = 0;

	//int max = bf.BitLen;
	//int min = BitLen;
	//if (BitLen > bf.BitLen)
	//{
	//	max = BitLen;
	//	min = bf.BitLen;
	//}
	//if (min == BitLen)
	//{
	//	MEMmin = MemLen;
	//}
	//else
	//{
	//	MEMmin = bf.MemLen;
	//}

	//TBitField res(max);
	//for (int i = 0; i < MemLen; i++)
	//{
	//	res.pMem[i] = pMem[i];
	//}
	//for (int i = 0; i < MEMmin - 2; i++)
	//{
	//	res.pMem[i] = (bf.pMem[i] & res.pMem[i]);
	//}
	//for (int k = (MEMmin - 1) * 32; k < min; k++)
	//{
	//	if ((bf.GetBit(k) & res.GetBit(k)) == 0)
	//	{
	//		res.ClrBit(k);
	//	}
	//	else
	//	{
	//		res.SetBit(k);
	//	}


	//}
	//TBitField help(bf);
	//for (int k = min; k < (MEMmin * 32) - 1; k++)
	//{
	//	help.SetBit(k);
	//	if (res.GetBit(k) & help.GetBit(k) == 0)
	//	{
	//		res.ClrBit(k);
	//	}
	//	else
	//	{
	//		res.SetBit(k);
	//	}
	//}

	//return res
	int min_len = bf.MemLen < this->MemLen ? bf.MemLen : this->MemLen;
	int min_bit_len = bf.BitLen < this->BitLen ? bf.BitLen : this->BitLen;
	int max_bit_len = bf.BitLen > this->BitLen ? bf.BitLen : this->BitLen;
	TBitField res = TBitField(max_bit_len);
	for (int i = 0; i < min_len; i++)
	{
		res.pMem[i] = this->pMem[i] & bf.pMem[i];
	}
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++)
	{
		res.pMem[i] = ~pMem[i];
	}
	/*for (int i = 0; i < BitLen; i++)
{
	if ((GetBit(i))==0)
	{
	   res.SetBit(i);
	}
	else
	{
	  res.ClrBit(i);
	}


}*/
	return res;

}

// ввод/вывод

 istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	 char a;
	 for (int i = 0; i < bf.MemLen; i++)
	 {
		 bf.pMem[i] = 0;
	 }
	for (int i = 0; i < bf.BitLen; i++)
	{

		istr >> a;
		if (a == '1')
		{
			bf.SetBit(i);
		}
		else
		{
			if (a == '0')
			{
				bf.ClrBit(i);
			}
			else
			{
				break;
			}
		}
	}
	return istr;

}

  ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{

		if (bf.GetBit(i))
		{
			ostr << '1';

		}
		else
		{
			ostr << '0';
		}

	}
	return ostr;

}
