#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<math.h>

using namespace std;

int check(string *p_mnt, string *p_order, string  *p_ing)
{
	string mnt, order, ing;
	mnt = *p_mnt;
	order = *p_order;
	ing = *p_ing;
	int pnt = 0;
	for (int i = 0; i < mnt.length(); i++)
	{
		if ((mnt[i] <= '9') && (mnt[i] >= '0'))
			continue;
		else if (i == 0 && (mnt[i] == '-' || mnt[i] == '+'))
			continue;
		else if (mnt[i] == '.')
		{
			if (pnt == 0)
			{
				pnt = 1;
				continue;
			}
			else
			{
				cout << "Incorrect data entered in the first field (points)";
				cout << "\n";
				return -1;
			}
		}
		else
		{
			cout << "Incorrect data entered in the first field";
			cout << "\n";
			return -1;
		}
	}
	if (mnt.length() > 31 || mnt.length() == 0)
	{
		cout << "Invalid number of characters entered in the first field";
		cout << "\n";
		return -1;
	}

	for (int i = 0; i < order.length(); i++)
	{
		if ((order[i] <= '9') && (order[i] >= '0'))
			continue;
		else if (i == 0 && (order[i] == '-' || order[i] == '+'))
			continue;
		else
		{
			cout << "Incorrect data entered in the second field";
			cout << "\n";
			return -1;
		}
	}
	if (order.length() > 6 || order.length() == 0 || (order.length() > 6 && order[0] == '-'))
	{
		cout << "Invalid number of characters entered in the second field";
		cout << "\n";
		return -1;
	}

	for (int i = 0; i < ing.length(); i++)
	{
		if ((ing[i] <= '9') && (ing[i] >= '0'))
			continue;
		else if (i == 0 && (ing[i] == '-' || ing[i] == '+'))
			continue;
		else
		{
			cout << "Incorrect data entered in the third field";
			cout << "\n";
			return -5;
		}
	}
	if (ing.length() > 30 || ing.length() == 0)
	{
		cout << "Invalid number of characters entered in the third field";
		cout << "\n";
		return -1;
	}

	return 0;
}

int multiplication(string *p_mnt, string  *p_ing, int *p_diff, string *p_order, int *p_zn_m, int *p_zn_i)
{
	string mnt, ing, order;
	mnt = *p_mnt;
	ing = *p_ing;
	order = *p_order;
	int diff, zn_m, zn_i;
	diff = *p_diff;
	zn_m = *p_zn_m;
	zn_i = *p_zn_i;

	int *a = NULL;
	a = (int*)calloc(mnt.length(), sizeof(int));
	int *b = NULL;
	b = (int*)calloc(ing.length(), sizeof(int));

	// умножение
	int cnt = 0;
	for (int i = mnt.length() - 1; i >= 0; i--)
	{
		a[cnt] = mnt[i] - '0';
		cnt++;
	}
	cnt = 0;
	for (int i = ing.length() - 1; i >= 0; i--)
	{
		b[cnt] = ing[i] - '0';
		cnt++;
	}


	int l = mnt.length() + 1 + ing.length();
	int *c = NULL;
	c = (int*)calloc(l, sizeof(int));
	for (int i = 0; i < mnt.length(); i++)
	{
		for (int j = 0; j < ing.length(); j++)
		{
			c[i + j] += a[i] * b[j];
		}
	}

	for (int i = 0; i < l; i++)
	{
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}
	while (c[l - 1] == 0)
		l--;


	//высчитывание нового порядка и мантиссы
	int new_order = 0;
	int new_l = l;
	int start = 0;

	cout << '\n';
	for (int i = 0; i < l; i++)
	{
		if (c[i] == 0)
		{
			start++;
			new_order++;
		}
		else
			break;
	}
	cout << '\n' << new_order;
	new_order += (l - start);
	cout << '\n' << new_order;

	// вычисляем знак
	int flag = 0;
	if (zn_i == 1 || zn_m == 1)
	{
		if (zn_i == 1 && (zn_m == 2 || zn_m == 0))
			flag = 1;
		else if ((zn_i == 2 || zn_i == 0) && zn_m == 1)
			flag = 1;
		else if (zn_i == 1 && zn_m == 1)
			flag = 0;
	}

	//округление
	int dln = l - start;
	if (dln > 30)
	{
		for (int i = start; i < l; i++)
		{
			if (dln > 30)
			{
				if (c[i] >= 5)
					c[i + 1] += 1;
				start++;
				//new_order--; //???
			}
			dln--;
		}
	}
	if (c[start] == 10)
	{
		for (int i = start; i < l; i++)
		{
			if (c[i] == 10 || c[i] >= 5)
			{
				c[i + 1] += 1;
				start++;
			}
		}
	}

	if (diff < 0)
	{
		new_order += diff;
	}
	cout << '\n' << diff << ' ' << new_order;
	if (new_order > 99999 || new_order <= -99999)
	{
		cout << "Error! Order overflow!";
		return 0;
	}
	// вывод результатов
	cout << '\n' << "Result: ";
	if (flag == 1)
	{
		cout << "-";
	}
	cout << "0.";
	for (int i = l - 1; i >= start; i--)
	{
		cout << c[i];
	}
	cout << " E ";
	cout << new_order;
	cout << "\n";
	return 0;
}

int main()
{
	string mnt, order, ing;

	printf("You should enter the mantissa with point in the first field and enter the order in the second field.\n");
	printf("Next, you must enter an integer in the third field.\n\n");
	printf("                    1        10        20        31 \n");
	printf("                    |--------|---------|----------|\n");
	printf("Enter the mantissa: ");
	getline(cin, mnt, '\n');
	cout << "\n";
	printf("                    1   5\n");
	printf("                    |---|\n");
	printf("Enter the order:    ");
	getline(cin, order, '\n');
	cout << "\n";
	printf("                    1        10        20       30\n");
	printf("                    |--------|---------|---------|\n");
	printf("Enter an integer:   ");
	getline(cin, ing, '\n');

	string *p_mnt, *p_order, *p_ing;
	p_mnt = &mnt;
	p_order = &order;
	p_ing = &ing;
	int ch = check(p_mnt, p_order, p_ing);
	if (ch != 0)
		return 0;

	//узнаем знак
	int zn_m = 0, zn_i = 0, zn_ord = 0;
	if (mnt[0] == '-')
	{
		zn_m = 1;
		mnt[0] = '0';
		mnt.erase(0, 1);
	}
	else if (mnt[0] == '+')
	{
		zn_m = 2;
		mnt[0] = '0';
		mnt.erase(0, 1);
	}
	if (ing[0] == '-')
	{
		ing[0] = '0';
		zn_i = 1;
		ing.erase(0, 1);
	}
	else if (ing[0] == '+')
	{
		ing[0] = '0';
		zn_i = 2;
		ing.erase(0, 1);
	}
	if (order[0] == '-')
	{
		order[0] = '0';
		zn_ord = 1;
		order.erase(0, 1);
	}
	else if (order[0] == '+')
	{
		order[0] = '0';
		zn_ord = 2;
		order.erase(0, 1);
	}

	//преобразовываем порядок в число
	int order_i = 0, k = 1, diff = 0;
	for (int i = order.length() - 1; i >= 0; i--)
	{
		order_i += (order[i] - '0') * k;
		k *= 10;
	}
	// обнаруживаем точку в мантиссе
	int pnt_m = 0;
	for (int i = 0; i < mnt.length(); i++)
	{
		if (mnt[i] == '.')
			pnt_m = i;
	}
	
	if (zn_ord == 1)
	{
		order_i *= -1;
	}
	cout << order_i;

	for (int i = 0; i < mnt.length(); i++)
	{
		if (i < pnt_m  && mnt[0] != '0') // ???
		{
			order_i++;
		}
		if (i > pnt_m && mnt[i] == '0')
		{
			cout << '!';
			order_i--;
		}
	}

	mnt.erase(pnt_m, 1);

	int g = 0;
	while (mnt[g] == '0')
	{
		mnt.erase(g, 1);
	}

	cout << order_i << ' '<<mnt << ' ';


	// выясняем разницу между длиной мантиссы и порядком (чтобы узнать, сколько остается за точкой)

	if (mnt.length() < order_i)
	{
		diff = order_i - mnt.length();
		for (int i = 0; i < diff; i++)
		{
			mnt += '0';
		}
	}
	if (mnt.length() > order_i)
	{
		diff = order_i - mnt.length();
	}
	

	cout << diff;

	// отправляем данные в функцию вычисление
	int *p_diff;
	p_diff = &diff;
	int *p_zn_i, *p_zn_m;
	p_zn_m = &zn_m;
	p_zn_i = &zn_i;

	multiplication(p_mnt, p_ing, p_diff, p_order, p_zn_m, p_zn_i);

	return 0;
}
