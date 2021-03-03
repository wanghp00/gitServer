#pragma once
#include <typeinfo>
#include <string>

//using namespace std;

//定点位数
static const int BIT = 16;
//定点数结构体
#pragma region BitFloat
struct BitFloat
{
private:
	long value;

public:
	BitFloat();
	BitFloat(long v);

	long Value();
	int IntValue();
	long LongValue();
	float FloatValue();
	double DoubleValue();
	template<typename object>
	bool Equals(object obj);
	int GetHashCode();
	std::string ToString();

	static BitFloat Create(int value);
	static BitFloat Create(long value);
	static BitFloat Create(float value);
	static BitFloat Create(double value);
	static BitFloat Create(BitFloat bitFloat);
	static BitFloat CreateFromRaw(long value);

	static BitFloat Zero();
	static BitFloat One();
	static BitFloat Half();

#pragma region 操作符重载
	//+
	BitFloat operator +(const BitFloat& a);
	BitFloat operator +(const int a);

	friend BitFloat operator +(const int a, BitFloat b);
	BitFloat operator +(const long a);
	friend BitFloat operator +(const long a, BitFloat b);
	BitFloat operator +(const float a);

	friend BitFloat operator +(const float a, BitFloat b);
	BitFloat operator +(const double a);

	friend BitFloat operator +(const double a, BitFloat b);

	//-
	BitFloat operator -();
	BitFloat operator -(const BitFloat& a);

	BitFloat operator -(const int a);
	friend BitFloat operator -(const int a, BitFloat b);
	BitFloat operator -(const long a);
	friend BitFloat operator -(const long a, BitFloat b);
	BitFloat operator -(const float a);
	friend BitFloat operator -(const float a, BitFloat b);
	BitFloat operator -(const double a);

	//*
	BitFloat operator *(const BitFloat& a);

	BitFloat operator *(const int b);
	friend BitFloat operator *(const int a, BitFloat b);
	BitFloat operator *(const long a);
	friend BitFloat operator *(const long a, BitFloat b);
	BitFloat operator *(const float a);
	friend BitFloat operator *(const float a, BitFloat b);
	BitFloat operator *(const double a);

	///
	BitFloat operator /(const BitFloat& a);
	BitFloat operator /(const int a);
	friend BitFloat operator /(const int a, BitFloat b);
	BitFloat operator /(const long a);
	friend BitFloat operator /(const long a, BitFloat b);
	BitFloat operator /(const float a);
	friend BitFloat operator /(const float a, BitFloat b);
	BitFloat operator /(const double b);
	friend BitFloat operator /(const double a, BitFloat b);

	//%
	BitFloat operator %(const BitFloat& a);

	BitFloat operator %(const int a);
	friend BitFloat operator %(const int a, BitFloat b);
	BitFloat operator %(const long a);
	friend BitFloat operator %(const long a, BitFloat b);
	BitFloat operator %(const float a);
	friend BitFloat operator %(const float a, BitFloat b);
	BitFloat operator %(const double b);
	friend BitFloat operator %(const double a, BitFloat b);

	//==
	bool operator ==(const BitFloat& a);

	bool operator ==(const int b);
	friend bool operator ==(const int a, BitFloat b);
	bool operator ==(const long a);
	friend bool operator ==(const long a, BitFloat b);
	bool operator ==(float a);
	friend bool operator ==(const float a, BitFloat b);
	bool operator ==(double a);
	friend bool operator ==(const double a, BitFloat b);

	//!=
	bool operator !=(const BitFloat& a);

	bool operator !=(const int b);
	friend bool operator !=(const int a, BitFloat b);
	bool operator !=(const long a);
	friend bool operator !=(const long a, BitFloat b);
	bool operator !=(float a);
	friend bool operator !=(const float a, BitFloat b);
	bool operator !=(double a);
	friend bool operator !=(const double a, BitFloat b);

	//>
	bool operator >(const BitFloat& a);

	bool operator >(const int b);
	friend bool operator >(const int a, BitFloat b);
	bool operator >(const long a);
	friend bool operator >(const long a, BitFloat b);
	bool operator >(float a);
	friend bool operator >(const float a, BitFloat b);
	bool operator >(double a);
	friend bool operator >(const double a, BitFloat b);

	//>=
	bool operator >=(const BitFloat& a);

	bool operator >=(const int b);
	friend bool operator >=(const int a, BitFloat b);
	bool operator >=(const long a);
	friend bool operator >=(const long a, BitFloat b);
	bool operator >=(float a);
	friend bool operator >=(const float a, BitFloat b);
	bool operator >=(double a);
	friend bool operator >=(const double a, BitFloat b);

	//<
	bool operator <(const BitFloat& a);

	bool operator <(const int b);
	friend bool operator <(const int a, BitFloat b);
	bool operator <(const long a);
	friend bool operator <(const long a, BitFloat b);
	bool operator <(float a);
	friend bool operator <(const float a, BitFloat b);
	bool operator <(double a);
	friend bool operator <(const double a, BitFloat b);

	//<=
	bool operator <=(const BitFloat& a);

	bool operator <=(const int b);
	friend bool operator <=(const int a, BitFloat b);
	bool operator <=(const long a);
	friend bool operator <=(const long a, BitFloat b);
	bool operator <=(float a);
	friend bool operator <=(const float a, BitFloat b);
	bool operator <=(double a);
	friend bool operator <=(const double a, BitFloat b);
#pragma endregion
};
#pragma endregion 

//圆周率
static BitFloat PI = BitFloat((BitFloat::One() * 355) / 113);

//定点数工具类
#pragma region 工具类
class BitMathUtil {
public:
#pragma region 数值计算
	//开方
	static BitFloat Sqrt(BitFloat number);
	//绝对值
	static BitFloat Abs(BitFloat number);
	//向下取整
	static BitFloat Floor(BitFloat number);
	//四舍五入
	static BitFloat Round(BitFloat number);
	//向上取整
	static BitFloat Ceil(BitFloat number);
	static BitFloat Min(BitFloat a, BitFloat b);
	static BitFloat Max(BitFloat a, BitFloat b);
	//弧度换算角度
	static BitFloat Rad2Deg(BitFloat number);
	//角度换算弧度
	static BitFloat Deg2Rad(BitFloat number);
#pragma endregion
#pragma region 三角函数
	//数值单位为角度
	//泰勒公式 sinx=x-x^3/3!+x^5/5!-x^7/7!+x^9/9!
	static BitFloat Sin(BitFloat angle);
	//泰勒公式 cos x = 1-x^2/2!+x^4/4!
	static BitFloat Cos(BitFloat angle);
	static BitFloat Tan(BitFloat angle);
#pragma endregion
};
#pragma endregion 
#pragma region 二维向量
//二维向量
struct Vector2 {
public:
	float x;
	float y;
	Vector2();
	Vector2(float x, float y);
	Vector2 operator+(Vector2 a);
	Vector2 operator-(Vector2 a);
	Vector2 operator-();
	Vector2 operator*(const float a);
	friend Vector2 operator*(const float a, Vector2 v);
	Vector2 operator/(const float a);
};
#pragma endregion
#pragma region 定点数二维向量
//定点数二维向量
struct BitVector2 {
public:
	BitFloat x;
	BitFloat y;
	BitVector2(BitFloat x, BitFloat y);
	Vector2 GetVector2();
	//计算向量长度用 坐标平方和
	BitFloat SqrMagnitude();
	//向量长度
	BitFloat Magnitude();
	template<typename object>
	bool Equals(object obj);
	int GetHashCode();
	static BitVector2 Create(Vector2 vect);
	//向量点乘
	static BitFloat Dot(BitVector2 a, BitVector2 b);
	//间距
	static BitFloat Distance(BitVector2 a, BitVector2 b);
	std::string ToString();

#pragma region 运算符重载
	//+
	BitVector2 operator +(BitVector2 a);

	//-
	BitVector2 operator -(BitVector2 a);

	//*
	BitVector2 operator *(const int a);
	friend BitVector2 operator *(const int a, BitVector2 b);
	BitVector2 operator *(const long a);
	friend BitVector2 operator *(const long a, BitVector2 b);
	BitVector2 operator *(const float a);
	friend BitVector2 operator *(const float a, BitVector2 b);
	BitVector2 operator *(const double a);
	friend BitVector2 operator *(const double a, BitVector2 b);

	///
	BitVector2 operator /(const int a);
	BitVector2 operator /(const long a);
	BitVector2 operator /(const float a);
	BitVector2 operator /(double a);

	//==
	bool operator ==(BitVector2 a);

	//!=
	bool operator !=(BitVector2 a);

	//=
	/*   这一段是小黄原代码 隐式转换的重载 我不知道怎么改。。
	#region =
		public static implicit operator BitVector3(BitVector2 v) {
		return new BitVector3(v.x, v.y, BitFloat.Zero);
	}

	public static implicit operator BitVector2(BitVector3 v) {
		return new BitVector2(v.x, v.y);
	}

	public static implicit operator BitVector2(Vector2 v) {
		return new BitVector2(v);
	}
	#endregion*/

	//x轴y轴方向上投影都为1的向量
	BitVector2 One();
	//零向量
	BitVector2 Zero();
	//x轴负方向
	BitVector2 Left();
	//x轴正方向
	BitVector2 Right();
	//y轴正方向
	BitVector2 Up();
	//y轴负方向
	BitVector2 Down();
#pragma endregion
};
#pragma endregion
#pragma region 三维向量
struct Vector3 {
public:
	float x;
	float y;
	float z;
	Vector3();
	Vector3(float x, float y, float z);
	Vector3 operator+(Vector3 a);
	Vector3 operator-(Vector3 a);
	Vector3 operator-();
	Vector3 operator*(const float a);
	friend Vector3 operator*(const float a, Vector3 v);
	Vector3 operator/(const float a);
};
#pragma endregion

#pragma region 定点数三维向量
struct BitVector3 {
public:
	BitVector3();
	BitFloat x;
	BitFloat y;
	BitFloat z;
	BitVector3(BitFloat x, BitFloat y, BitFloat z);
	BitVector3(BitFloat x, BitFloat y);
	BitVector3(Vector3 vect);
	Vector3 ToVector3();
	//计算向量长度用 坐标平方和
	BitFloat SqrMagnitude();
	//向量长度
	BitFloat Magnitude();
	BitVector3 Normalized();
	template<typename object>
	bool Equals(object obj);
	int GetHashCode();
	static BitVector3 Create(Vector3 vect);
	//向量点乘
	static BitFloat Dot(BitVector3 a, BitVector3 b);
	std::string ToString();
	static BitVector3 Cross(BitVector3 a, BitFloat b);
	static BitVector3 Project(BitVector3 vect, BitVector3 axis);
	//间距
	static BitFloat Distance(BitVector3 a, BitVector3 b);
#pragma region 运算符重载
	//+
	BitVector3 operator +(BitVector3 a);

	//-
	BitVector3 operator -(BitVector3 a);

	//*
	BitVector3 operator *(const int a);
	friend BitVector3 operator *(const int a, BitVector3 b);
	BitVector3 operator *(const long a);
	friend BitVector3 operator *(const long a, BitVector3 b);
	BitVector3 operator *(const float a);
	friend BitVector3 operator *(const float a, BitVector3 b);
	BitVector3 operator *(const double a);
	friend BitVector3 operator *(const double a, BitVector3 b);

	///
	BitVector2 operator /(const int a);
	BitVector2 operator /(const long a);
	BitVector2 operator /(const float a);
	BitVector2 operator /(double a);

	//==
	bool operator ==(BitVector3 a);

	//!=
	bool operator !=(BitVector3 a);

	//=

	//x轴y轴方向上投影都为1的向量
	static BitVector3 One();
	//零向量
	static BitVector3 Zero();
	//x轴负方向
	static BitVector3 Left();
	//x轴正方向
	static BitVector3 Right();
	//y轴正方向
	static BitVector3 Up();
	//y轴负方向
	static BitVector3 Down();
	//z轴正方向
	static BitVector3 Forward();
	//z轴负方向
	static BitVector3 Back();
#pragma endregion
};
#pragma endregion


static BitFloat Zero();
static BitFloat One();
static BitFloat Half();