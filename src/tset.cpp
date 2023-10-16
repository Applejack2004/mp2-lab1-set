// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp),MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField),MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf),MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    int res = BitField.GetBit(Elem);
    return res;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (BitField==s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet Res(s);
    Res.BitField = Res.BitField | BitField;
    return Res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet Res(*this);
    Res.InsElem(Elem);
    return Res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet Res(*this);
    Res.DelElem(Elem);
    return Res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet Res(s);
    Res.BitField = Res.BitField & BitField;
    return Res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet Res(*this);
    Res.BitField = ~(Res.BitField);
    return Res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    int m;
    char d;
    istr >> d;
        while (d != ')')
        {
            istr >> m;
            s.InsElem(m);
            istr >> d;
        }


    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << '(';
    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMember(i))
        {
            ostr << i << ' ';

        }

    }
    ostr << ')';
    return ostr;
}
