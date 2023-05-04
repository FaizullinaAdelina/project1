using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace FineMethod
{
	class Program
	{
		static double fx(double x_1, double x_2)
		{
			return Math.Pow(x_1, 2) + 2 * Math.Pow(x_2, 2);
		}
		static double P(double x_1, double x_2, double r)
		{
			return r / 2 * Math.Pow((3 * x_1 + x_2 - 2), 2);
		}

		static double fn(double x_1, double x_2, double r)
		{
			return Math.Pow(x_1, 2) + 2 * Math.Pow(x_2, 2) + P(x_1,
				x_2, r);
		}
		static double dx(double x_1, double x_2, double r)
		{
			return 2 * x_1 + 3 * r * (3 * x_1 + x_2 - 2);
		}
		static double dy(double x_1, double x_2, double r)
		{
			return 4 * x_2 + r * (3 * x_1 + x_2 - 2);
		}
		static void Main(string[] args)
		{
			double eps_1 = 0.15, eps_2 = 0.2, eps = 0.05, rdf, x_o =
				0, y_o = 0, t = 1, dlx, dlf;
			double[] x = new double[10000];
			double[] y = new double[10000];
			double[] dfx = new double[10000];
			double[] dfy = new double[10000];
			double[] f = new double[10000];
			double[] dkx = new double[10000];
			double[] dky = new double[10000];
			double[] r = new double[1000000];
			int M = 100, k, flag, C = 5, ki = 0, key;
			double p;
			x[0] = 10; y[0] = 10; r[0] = 1;
			while (true)
			{
				k = 0; flag = 0; key = 0;
				if (ki >= 100)
				{
					x_o = x[k]; y_o = y[k];
					p = P(x_o, y_o, r[ki]);
					Console.WriteLine("---ОТВЕТ---");
					Console.WriteLine($"x_{ki} = ({x_o};{y_o})");
					Console.WriteLine($"P({ki}) = {p}");
					Console.WriteLine($"F({ki}) = {fx(x_o, y_o)}");
					Console.WriteLine($"ki = {ki}");
					Console.ReadLine();
					break;
				}

				while (true)
				{
					dfx[k] = dx(x[k], y[k], r[ki]);
					dfy[k] = dy(x[k], y[k], r[ki]);
					rdf = Math.Sqrt(Math.Pow(dfx[k], 2) +
						Math.Pow(dfy[k], 2));
					if (rdf < eps_1)
					{
						x_o = x[k];
						y_o = y[k];
						f[k] = fn(x[k], y[k], r[ki]);
						key = 1;
						break;
					}
					if (k >= M)
					{
						x_o = x[k];
						y_o = y[k];
						f[k] = fn(x[k], y[k], r[ki]);
						key = 2;
						break;
					}
					while (true)
					{
						x[k + 1] = x[k] - t * dfx[k];
						y[k + 1] = y[k] - t * dfy[k];
						f[k] = fn(x[ki], y[k], r[ki]);
						f[k + 1] = fn(x[k + 1], y[k + 1], r[ki]);
						if (f[k + 1] < f[k]) break;
						else
						{
							t /= 2;
						}
					}
					dlx = Math.Sqrt(Math.Pow(x[k + 1] - x[k], 2) +
						Math.Pow(y[k + 1] - y[k], 2));
					dlf = Math.Abs(f[k + 1] - f[k]);
					if (dlx < eps_2 && dlf < eps_2)
					{
						flag++;
					}
					else
					{
						flag = 0;
						k++;
						continue;
					}
					if (flag == 2)
					{
						x_o = x[k + 1];
						y_o = y[k + 1];
						f[k] = f[k + 1];
						k = k + 1;
						key = 3;
						break;
					}
				}
				Console.WriteLine($"x_{k} = ({x_o};{y_o})");
				Console.WriteLine($"k = {k}");
				Console.WriteLine($"Вышли на шаге № {key}");
				x_o = x[k]; y_o = y[k];
				p = P(x_o, y_o, r[ki]);
				if (p <= eps)
				{
					Console.WriteLine("---ОТВЕТ ХУЙНЯ---");
					ki++;
					Console.WriteLine($"x_{ki} = ({x_o};{y_o})");
					Console.WriteLine($"P({ki}) = {p}");
					Console.WriteLine($"F({ki}) = {fx(x_o, y_o)}");
					Console.WriteLine($"ki = {ki}");
					Console.ReadLine();
					break;
				}
				else
				{
					ki++; r[ki] = C * r[ki - 1];
					Console.WriteLine($"r[{ki}] = {r[ki]}");
					Console.WriteLine($"P({ki}) = {p}");
					x[0] = x_o; y[0] = y_o;
				}
			}
		}
	}
}