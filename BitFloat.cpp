#pragma once
#include "BitFloat.h"

static BitFloat Zero() {
	return BitFloat(0);
}
static BitFloat One() {
	return BitFloat(1 << BIT);
}
static BitFloat Half() {
	return BitFloat(1 << BIT - 1);
}

BitFloat::BitFloat() {
	value = 0;
}
BitFloat::BitFloat(long v) {
	value = v;
}

long BitFloat::Value() {
	return value;
}
int BitFloat::IntValue() {
	return (int)(value >> BIT);
}
long BitFloat::LongValue() {
	return value >> BIT;
}
float BitFloat::FloatValue() {
	return (float)(value / (double)One().Value());
}
double BitFloat::DoubleValue() {
	return value / (double)One().Value();
}
template<typename object>
bool BitFloat::Equals(object obj) {
	if (typeid(obj).name() == typeid(this).name())
		return this == obj;
	else if (typeid(obj).name() == typeid(int).name())
		return this->IntValue() == obj;
	else if (typeid(obj).name() == typeid(long).name())
		return this->LongValue() == obj;
	else if (typeid(obj).name() == typeid(float).name())
		return this->FloatValue() == obj;
	else if (typeid(obj).name() == typeid(double).name())
		return this->DoubleValue() == obj;
	return false;
}
int BitFloat::GetHashCode() {
	return (int)value;
}
std::string BitFloat::ToString() {
	return std::to_string(DoubleValue());
}

BitFloat BitFloat::Create(int value) {
	return BitFloat((long)value << BIT);
}
BitFloat BitFloat::Create(long value) {
	return BitFloat(value << BIT);
}
BitFloat BitFloat::Create(float value) {
	return BitFloat((One() * value).Value());
}
BitFloat BitFloat::Create(double value) {
	return BitFloat((One() * value).Value());
}
BitFloat BitFloat::Create(BitFloat bitFloat) {
	return BitFloat(bitFloat.Value());
}
BitFloat BitFloat::CreateFromRaw(long value) {
	return BitFloat(value);
}

BitFloat BitFloat::Zero() {
	return BitFloat(0);
}
BitFloat BitFloat::One() {
	return BitFloat(1 << BIT);
}
BitFloat BitFloat::Half() {
	return BitFloat(1 << BIT - 1);
}

#pragma region ����������
//+
BitFloat BitFloat::operator +(const BitFloat& a) {
	return BitFloat(value + a.value);
}
BitFloat BitFloat::operator +(const int a) {
	return BitFloat(value + ((long)a << BIT));
}

BitFloat operator +(const int a, BitFloat b) {
	return b + a;
}
BitFloat BitFloat::operator +(const long a) {
	return BitFloat(value + (a << BIT));
}
BitFloat operator +(const long a, BitFloat b) {
	return b + a;
}
BitFloat BitFloat::operator +(const float a) {
	return BitFloat(value + (a * One()).value);
}

BitFloat operator +(const float a, BitFloat b) {
	return b + a;
}
BitFloat BitFloat::operator +(const double a) {
	return BitFloat(value + (a * One()).value);
}

BitFloat operator +(const double a, BitFloat b) {
	return b + a;
}

//-
BitFloat BitFloat::operator -() {
	return BitFloat(-value);
}
BitFloat BitFloat::operator -(const BitFloat& a) {
	return BitFloat(value - a.value);
}

BitFloat BitFloat::operator -(const int a) {
	return BitFloat(value - ((long)a << BIT));
}
BitFloat operator -(const int a, BitFloat b) {
	return BitFloat(((long)a << BIT) - b.value);
}
BitFloat BitFloat::operator -(const long a) {
	return BitFloat(value - (a << BIT));
}
BitFloat operator -(const long a, BitFloat b) {
	return BitFloat((a << BIT) - b.value);
}
BitFloat BitFloat::operator -(const float a) {
	return BitFloat(value - (a * One()).value);
}
BitFloat operator -(const float a, BitFloat b) {
	return BitFloat((a * One()).value - b.value);
}
BitFloat BitFloat::operator -(const double a) {
	return BitFloat(value - (a * One()).value);
}
BitFloat operator -(const double a, BitFloat b) {
	return BitFloat((a * One()).value - b.value);
}

//*
BitFloat BitFloat::operator *(const BitFloat& a) {
	return BitFloat((value * a.value) >> BIT);
}

BitFloat BitFloat::operator *(const int b) {
	return BitFloat(value * b);
}
BitFloat operator *(const int a, BitFloat b) {
	return b * a;
}
BitFloat BitFloat::operator *(const long a) {
	return BitFloat(value * a);
}
BitFloat operator *(const long a, BitFloat b) {
	return b * a;
}
BitFloat BitFloat::operator *(const float a) {
	return BitFloat((long)(value * a));
}
BitFloat operator *(const float a, BitFloat b) {
	return b * a;
}
BitFloat BitFloat::operator *(const double a) {
	return BitFloat((long)(value * a));
}
BitFloat operator *(const double a, BitFloat b) {
	return b * a;
}

///
BitFloat BitFloat::operator /(const BitFloat& a) {
	return BitFloat((value << BIT) / a.value);
}
BitFloat BitFloat::operator /(const int a) {
	return BitFloat(value / a);
}
BitFloat operator /(const int a, BitFloat b) {
	return BitFloat(((long)a << BIT << BIT) / b.value);
}
BitFloat BitFloat::operator /(const long a) {
	return BitFloat(value / a);
}
BitFloat operator /(const long a, BitFloat b) {
	return BitFloat((a << BIT << BIT) / b.value);
}
BitFloat BitFloat::operator /(const float a) {
	return BitFloat((value << BIT) / (((a * One()).value)));
}
BitFloat operator /(const float a, BitFloat b) {
	return BitFloat((long)(a * (One().value << BIT)) / b.value);
}
BitFloat BitFloat::operator /(const double b) {
	return BitFloat((value << BIT) / (((b * One()).value)));
}
BitFloat operator /(const double a, BitFloat b) {
	return BitFloat((long)(a * (One().value << BIT)) / b.value);
}

//%
BitFloat BitFloat::operator %(const BitFloat& a) {
	return BitFloat(value % a.value);
}

BitFloat BitFloat::operator %(const int a) {
	return BitFloat(value % ((long)a << BIT));
}
BitFloat operator %(const int a, BitFloat b) {
	return BitFloat(((long)a << BIT) % b.value);
}
BitFloat BitFloat::operator %(const long a) {
	return BitFloat(value % (a << BIT));
}
BitFloat operator %(const long a, BitFloat b) {
	return BitFloat((a << BIT) % b.value);
}
BitFloat BitFloat::operator %(const float a) {
	return BitFloat(value % (a * One()).value);
}
BitFloat operator %(const float a, BitFloat b) {
	return BitFloat((a * One()).value % b.value);
}
BitFloat BitFloat::operator %(const double b) {
	return BitFloat(value % (b * One()).value);
}
BitFloat operator %(const double a, BitFloat b) {
	return BitFloat((a * One()).value % b.value);
}

//==
bool BitFloat::operator ==(const BitFloat& a) {
	return value == a.value;
}

bool BitFloat::operator ==(const int b) {
	return value == ((long)b << BIT);
}
bool operator ==(const int a, BitFloat b) {
	return b == a;
}
bool BitFloat::operator ==(const long a) {
	return value == (a << BIT);
}
bool operator ==(const long a, BitFloat b) {
	return b == a;
}
bool BitFloat::operator ==(float a) {
	return value == (a * One()).value;
}
bool operator ==(const float a, BitFloat b) {
	return b == a;
}
bool BitFloat::operator ==(double a) {
	return value == (a * One()).value;
}
bool operator ==(const double a, BitFloat b) {
	return b == a;
}

//!=
bool BitFloat::operator !=(const BitFloat& a) {
	return value != a.value;
}

bool BitFloat::operator !=(const int b) {
	return value != ((long)b << BIT);
}
bool operator !=(const int a, BitFloat b) {
	return b != a;
}
bool BitFloat::operator !=(const long a) {
	return value != (a << BIT);
}
bool operator !=(const long a, BitFloat b) {
	return b != a;
}
bool BitFloat::operator !=(float a) {
	return value != (a * One()).value;
}
bool operator !=(const float a, BitFloat b) {
	return b != a;
}
bool BitFloat::operator !=(double a) {
	return value != (a * One()).value;
}
bool operator !=(const double a, BitFloat b) {
	return b != a;
}

//>
bool BitFloat::operator >(const BitFloat& a) {
	return value > a.value;
}

bool BitFloat::operator >(const int b) {
	return value > ((long)b << BIT);
}
bool operator >(const int a, BitFloat b) {
	return b > a;
}
bool BitFloat::operator >(const long a) {
	return value > (a << BIT);
}
bool operator >(const long a, BitFloat b) {
	return b > a;
}
bool BitFloat::operator >(float a) {
	return value > (a * One()).value;
}
bool operator >(const float a, BitFloat b) {
	return b > a;
}
bool BitFloat::operator >(double a) {
	return value > (a * One()).value;
}
bool operator >(const double a, BitFloat b) {
	return b > a;
}

//>=
bool BitFloat::operator >=(const BitFloat& a) {
	return value >= a.value;
}

bool BitFloat::operator >=(const int b) {
	return value >= ((long)b << BIT);
}
bool operator >=(const int a, BitFloat b) {
	return b >= a;
}
bool BitFloat::operator >=(const long a) {
	return value >= (a << BIT);
}
bool operator >=(const long a, BitFloat b) {
	return b >= a;
}
bool BitFloat::operator >=(float a) {
	return value >= (a * One()).value;
}
bool operator >=(const float a, BitFloat b) {
	return b >= a;
}
bool BitFloat::operator >=(double a) {
	return value >= (a * One()).value;
}
bool operator >=(const double a, BitFloat b) {
	return b >= a;
}

//<
bool BitFloat::operator <(const BitFloat& a) {
	return value < a.value;
}

bool BitFloat::operator <(const int b) {
	return value < ((long)b << BIT);
}
bool operator <(const int a, BitFloat b) {
	return b < a;
}
bool BitFloat::operator <(const long a) {
	return value < (a << BIT);
}
bool operator <(const long a, BitFloat b) {
	return b < a;
}
bool BitFloat::operator <(float a) {
	return value < (a* One()).value;
}
bool operator <(const float a, BitFloat b) {
	return b < a;
}
bool BitFloat::operator <(double a) {
	return value < (a* One()).value;
}
bool operator <(const double a, BitFloat b) {
	return b < a;
}

//<=
bool BitFloat::operator <=(const BitFloat& a) {
	return value <= a.value;
}

bool BitFloat::operator <=(const int b) {
	return value <= ((long)b << BIT);
}
bool operator <=(const int a, BitFloat b) {
	return b <= a;
}
bool BitFloat::operator <=(const long a) {
	return value <= (a << BIT);
}
bool operator <=(const long a, BitFloat b) {
	return b <= a;
}
bool BitFloat::operator <=(float a) {
	return value <= (a * One()).value;
}
bool operator <=(const float a, BitFloat b) {
	return b <= a;
}
bool BitFloat::operator <=(double a) {
	return value <= (a * One()).value;
}
bool operator <=(const double a, BitFloat b) {
	return b <= a;
}

//������
#pragma region ������
#pragma region ��ֵ����
BitFloat BitMathUtil::Sqrt(BitFloat number) {
	long value = number.Value();
	if (value == 0) {
		return BitFloat::Zero();
	}

	long n = (value >> 1) + 1;
	long m = (n + (value / n)) >> 1;
	while (m < n) {
		n = m;
		m = (n + (value / n)) >> 1;
	}
	return BitFloat::CreateFromRaw(n << BIT / 2);
}
//����ֵ
BitFloat BitMathUtil::Abs(BitFloat number) {
	return BitFloat::Create(number >= 0 ? number : -number);
}
//����ȡ��
BitFloat BitMathUtil::Floor(BitFloat number) {
	return BitFloat::CreateFromRaw((number.Value() >> BIT) << BIT);
}
//��������
BitFloat BitMathUtil::Round(BitFloat number) {
	return Floor(number + BitFloat::Half());
}
//����ȡ��
BitFloat BitMathUtil::Ceil(BitFloat number) {
	long value = number.Value() + BitFloat::One().Value() - 1;
	return BitFloat::CreateFromRaw((value >> BIT) << BIT);
}
BitFloat BitMathUtil::Min(BitFloat a, BitFloat b) {
	return a <= b ? a : b;
}
BitFloat BitMathUtil::Max(BitFloat a, BitFloat b) {
	return a >= b ? a : b;
}
//���Ȼ���Ƕ�
BitFloat BitMathUtil::Rad2Deg(BitFloat number) {
	return number * 180 / PI;
}
//�ǶȻ��㻡��
BitFloat BitMathUtil::Deg2Rad(BitFloat number) {
	return number * PI / 180;
}
#pragma endregion
#pragma region ���Ǻ���
//��ֵ��λΪ�Ƕ�
//̩�չ�ʽ sinx=x-x^3/3!+x^5/5!-x^7/7!+x^9/9!
BitFloat BitMathUtil::Sin(BitFloat angle) {
	BitFloat twicePI = PI * 2;
	BitFloat halfPI = PI / 2;
	BitFloat rad = Deg2Rad(angle) % twicePI;
	if (rad < 0) {
		rad = rad + twicePI;
	}
	int quadrant = (rad / halfPI).IntValue();
	bool mirror = quadrant == 1 || quadrant == 3;
	bool flip = quadrant == 2 || quadrant == 3;
	rad = rad % halfPI;
	if (mirror) {
		rad = halfPI - rad;
	}
	BitFloat square = rad * rad;
	BitFloat cube = square * rad;

	BitFloat result = rad - (cube / 6) + (cube * square / 120);
	if (flip) {
		result = -result;
	}
	return result;
}
//̩�չ�ʽ cos x = 1-x^2/2!+x^4/4!
BitFloat BitMathUtil::Cos(BitFloat angle) {
	BitFloat twicePI = PI * 2;
	BitFloat halfPI = PI / 2;
	BitFloat rad = Deg2Rad(angle) % twicePI;
	if (rad < 0) {
		rad = rad + twicePI;
	}

	int quadrant = (rad / halfPI).IntValue();
	bool mirror = quadrant == 1 || quadrant == 3;
	bool flip = quadrant == 1 || quadrant == 2;

	rad = rad % halfPI;
	if (mirror) {
		rad = halfPI - rad;
	}

	BitFloat square = rad * rad;
	BitFloat result = BitFloat::One() - (square / 2) + (square * square / 24);
	if (flip) {
		result = -result;
	}
	return result;
}
BitFloat BitMathUtil::Tan(BitFloat angle) {
	return Sin(angle) / Cos(angle);
}
#pragma endregion
#pragma endregion 
//��ά����
#pragma region ��ά����
	//��ά����

Vector2::Vector2() {
	x = 0;
	y = 0;
}
Vector2::Vector2(float x, float y) {
	Vector2::x = x;
	Vector2::y = y;
}
Vector2 Vector2::operator+(Vector2 a) {
	return Vector2(x + a.x, y + a.y);
}
Vector2 Vector2::operator-(Vector2 a) {
	return Vector2(x - a.x, y - a.y);
}
Vector2 Vector2::operator-() {
	return Vector2(-x, -y);
}
Vector2 Vector2::operator*(const float a) {
	return Vector2((float)x * a, (float)y * a);
}
Vector2 operator*(const float a, Vector2 v) {
	return v * a;
}
Vector2 Vector2::operator/(const float a) {
	return Vector2((float)x / a, (float)y / a);
}
#pragma endregion
//��������ά����
#pragma region ��������ά����
BitVector2::BitVector2(BitFloat x, BitFloat y) {
	BitVector2::x = x;
	BitVector2::y = y;
}
Vector2 BitVector2::GetVector2() {
	return Vector2(x.FloatValue(), y.FloatValue());
}
//�������������� ����ƽ����
BitFloat BitVector2::SqrMagnitude() {
	return x * x + y * y;
}
//��������
BitFloat BitVector2::Magnitude() {
	return BitMathUtil::Sqrt(SqrMagnitude());
}
template<typename object>
bool BitVector2::Equals(object obj) {
	if (typeid(obj).name() == typeid(BitVector2::One()).name())
		return obj == this;
	return false;
}
int BitVector2::GetHashCode() {
	//ûд
}
BitVector2 BitVector2::Create(Vector2 vect) {
	return BitVector2(BitFloat::Create(vect.x), BitFloat::Create(vect.y));
}
//�������
BitFloat BitVector2::Dot(BitVector2 a, BitVector2 b) {
	return a.x * b.x + a.y * b.y;
}
//���
BitFloat BitVector2::Distance(BitVector2 a, BitVector2 b) {
	BitFloat x = a.x - b.x;
	BitFloat y = a.y - b.y;
	return BitMathUtil::Sqrt(x * x + y * y);
}
std::string BitVector2::ToString() {
	return x.ToString() + " " + y.ToString();
}

#pragma region ���������
//+
BitVector2 BitVector2::operator +(BitVector2 a) {
	return BitVector2(x + a.x, y + a.y);
}

//-
BitVector2 BitVector2::operator -(BitVector2 a) {
	return BitVector2(x - a.x, y - a.y);
}

//*
BitVector2 BitVector2::operator *(const int a) {
	return BitVector2(x * a, y * a);
}
BitVector2 operator *(const int a, BitVector2 b) {
	return b * a;
}
BitVector2 BitVector2::operator *(const long a) {
	return BitVector2(x * a, y * a);
}
BitVector2 operator *(const long a, BitVector2 b) {
	return b * a;
}
BitVector2 BitVector2::operator *(const float a) {
	return  BitVector2(x * a, y * a);
}
BitVector2 operator *(const float a, BitVector2 b) {
	return b * a;
}
BitVector2 BitVector2::operator *(const double a) {
	return BitVector2(x * a, y * a);
}
BitVector2 operator *(const double a, BitVector2 b) {
	return b * a;
}

///
BitVector2 BitVector2::operator /(const int a) {
	return BitVector2(x / a, y / a);
}
BitVector2 BitVector2::operator /(const long a) {
	return BitVector2(x / a, y / a);
}
BitVector2 BitVector2::operator /(const float a) {
	return BitVector2(x / a, y / a);
}
BitVector2 BitVector2::operator /(double a) {
	return BitVector2(x / a, y / a);
}

//==
bool BitVector2::operator ==(BitVector2 a) {
	return x == a.x && y == a.y;
}
//!=
bool BitVector2::operator !=(BitVector2 a) {
	return x != a.x || y != a.y;
}

//=

//x��y�᷽����ͶӰ��Ϊ1������
BitVector2 BitVector2::One() {
	return BitVector2(BitFloat::One(), BitFloat::One());
}
//������
BitVector2 BitVector2::Zero() {
	return BitVector2(BitFloat::Zero(), BitFloat::Zero());
}
//x�Ḻ����
BitVector2 BitVector2::Left() {
	return BitVector2(BitFloat::Create(-1), BitFloat::Zero());
}
//x��������
BitVector2 BitVector2::Right() {
	return BitVector2(BitFloat::Create(1), BitFloat::Zero());
}
//y��������
BitVector2 BitVector2::Up() {
	return BitVector2(BitFloat::Zero(), BitFloat::Create(1));
}
//y�Ḻ����
BitVector2 BitVector2::Down() {
	return BitVector2(BitFloat::Zero(), BitFloat::Create(-1));
}
#pragma endregion
#pragma endregion

//��ά����
#pragma region ��ά����
Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}
Vector3::Vector3(float x, float y, float z) {
	Vector3::x = x;
	Vector3::y = y;
	Vector3::z = z;
}
Vector3 Vector3::operator+(Vector3 a) {
	return Vector3(x + a.x, y + a.y, z + a.z);
}
Vector3 Vector3::operator-(Vector3 a) {
	return Vector3(x - a.x, y - a.y, z - a.z);
}
Vector3 Vector3::operator-() {
	return Vector3(-x, -y, -z);
}
Vector3 Vector3::operator*(const float a) {
	return Vector3((float)x * a, (float)y * a, (float)z * a);
}
Vector3 operator*(const float a, Vector2 v) {
	return v * a;
}
Vector3 Vector3::operator/(const float a) {
	return Vector3((float)x / a, (float)y / a, (float)z / a);
}
#pragma endregion

//��������ά����
#pragma region ��������ά����
BitVector3::BitVector3() {
	this->x = BitFloat::Zero();
	this->y = BitFloat::Zero();
	this->z = BitFloat::Zero();
}

BitVector3::BitVector3(BitFloat x, BitFloat y, BitFloat z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3 BitVector3::ToVector3() {
	return Vector3(x.FloatValue(), y.FloatValue(), z.FloatValue());
}
//�������������� ����ƽ����
BitFloat BitVector3::SqrMagnitude() {
	return x * x + y * y + z * z;
}
//��������
BitFloat BitVector3::Magnitude() {
	return BitMathUtil::Sqrt(SqrMagnitude());
}
//��׼��
BitVector3 BitVector3::Normalized() {
	BitFloat xq = x * x;
	BitFloat yq = y * y;
	BitFloat zq = z * z;
	BitFloat total = xq + yq + zq;
	if (total == 0) {
		return BitVector3::Zero();
	}
	BitFloat newX = x > 0 ? BitMathUtil::Sqrt(xq / total) : -BitMathUtil::Sqrt(xq / total);
	BitFloat newY = y > 0 ? BitMathUtil::Sqrt(yq / total) : -BitMathUtil::Sqrt(yq / total);
	BitFloat newZ = z > 0 ? BitMathUtil::Sqrt(zq / total) : -BitMathUtil::Sqrt(zq / total);
	return BitVector3(newX, newY, newZ);
}

template<typename object>
bool BitVector3::Equals(object obj) {
	if (typeid(obj).name() == typeid(BitVector3::One()).name())
		return obj == this;
	return false;
}
int BitVector3::GetHashCode() {
	//ûд
}
BitVector3 BitVector3::Create(Vector3 vect) {
	return BitVector3(BitFloat::Create(vect.x), BitFloat::Create(vect.y), BitFloat::Create(vect.z));
}
//�������
BitFloat BitVector3::Dot(BitVector3 a, BitVector3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
//���
BitFloat BitVector3::Distance(BitVector3 a, BitVector3 b) {
	BitFloat x = a.x - b.x;
	BitFloat y = a.y - b.y;
	BitFloat y = a.z - b.z;
	return BitMathUtil::Sqrt(x * x + y * y + z * z);
}

#pragma region ���������
//+
BitVector3 BitVector3::operator +(BitVector3 a) {
	return BitVector3(x + a.x, y + a.y, z + a.z);
}

//-
BitVector3 BitVector3::operator -(BitVector3 a) {
	return BitVector3(x - a.x, y - a.y, z - a.z);
}

//*
BitVector3 BitVector3::operator *(const int a) {
	return BitVector3(x * a, y * a, z * a);
}
BitVector3 operator *(const int a, BitVector3 b) {
	return b * a;
}
BitVector3 BitVector3::operator *(const long a) {
	return BitVector3(x * a, y * a, z * a);
}
BitVector3 operator *(const long a, BitVector3 b) {
	return b * a;
}
BitVector3 BitVector3::operator *(const float a) {
	return  BitVector3(x * a, y * a, z * a);
}
BitVector3 operator *(const float a, BitVector3 b) {
	return b * a;
}
BitVector3 BitVector3::operator *(const double a) {
	return BitVector3(x * a, y * a, z * a);
}
BitVector3 operator *(const double a, BitVector3 b) {
	return b * a;
}

///
BitVector3 BitVector3::operator /(const int a) {
	return BitVector3(x / a, y / a, z / a);
}
BitVector3 BitVector3::operator /(const long a) {
	return BitVector3(x / a, y / a, z / a);
}
BitVector3 BitVector3::operator /(const float a) {
	return BitVector3(x / a, y / a, z / a);
}
BitVector3 BitVector3::operator /(double a) {
	return BitVector3(x / a, y / a, z / a);
}

//==
bool BitVector3::operator ==(BitVector3 a) {
	return x == a.x && y == a.y && z == a;
}
//!=
bool BitVector3::operator !=(BitVector3 a) {
	return x != a.x || y != a.y || z != a.z;
}

//=
//ͬ��ά����

//x��y�᷽����ͶӰ��Ϊ1������
BitVector3 BitVector3::One() {
	return BitVector3(BitFloat::One(), BitFloat::One(), BitFloat::One());
}
//������
BitVector3 BitVector3::Zero() {
	return BitVector3(BitFloat::Zero(), BitFloat::Zero(), BitFloat::Zero());
}
//x�Ḻ����
BitVector3 BitVector3::Left() {
	return BitVector3(BitFloat::Create(-1), BitFloat::Zero(), BitFloat::Zero());
}
//x��������
BitVector3 BitVector3::Right() {
	return BitVector3(BitFloat::Create(1), BitFloat::Zero(), BitFloat::Zero());
}
//y��������
BitVector3 BitVector3::Up() {
	return BitVector3(BitFloat::Zero(), BitFloat::Create(1), BitFloat::Zero());
}
//y�Ḻ����
BitVector3 BitVector3::Down() {
	return BitVector3(BitFloat::Zero(), BitFloat::Create(-1), BitFloat::Zero());
}
//z��������
BitVector3 BitVector3::Forward() {
	return BitVector3(BitFloat::Zero(), BitFloat::Zero(), BitFloat::Create(1));
}
//y�Ḻ����
BitVector3 BitVector3::Back() {
	return BitVector3(BitFloat::Zero(), BitFloat::Zero(), BitFloat::Create(-1));
}
#pragma endregion
#pragma endregion

