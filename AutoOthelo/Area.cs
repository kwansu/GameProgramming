using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class Area
{
	readonly int[] totalNum;
	readonly int[] winNum;
	readonly float[] winRate;

	int feature;

	public int FeatureNum
	{
		get
		{
			return feature;
		}

		set
		{
			if (value < 0) feature = 0;
			else if (value > 8) feature = 8;
			else feature = value;
		}
	}

	public float Interval
	{
		get
		{
			return winRate[feature + 1] - winRate[feature];
		}
	}

	public float this[int index]
	{
		get
		{
			return winRate[index];
		}
	}

	public int GetTotal(int index)
	{
		return totalNum[index];
	}

	public int GetWin(int index)
	{
		return winNum[index];
	}

	public Area(int[] total, int[] win)
	{
		feature = 0;
		totalNum = (int[])total.Clone();
		winNum = (int[])win.Clone();
		winRate = new float[winNum.Length];

		for (int i = 0; i < winRate.Length; ++i)
		{
			if (totalNum[i] == 0)
			{
				winRate[i] = -1;
			}
			else
			{
				winRate[i] = (float)winNum[i] / totalNum[i];
			}
		}
	}

	public void Calculate(bool isWin)
	{
		++totalNum[feature];

		if (isWin)
		{
			++winNum[feature];
		}

		winRate[feature] = (float)winNum[feature] / totalNum[feature];
	}
}

public struct Aspect
{
	public int row, col;

	public Aspect(int row, int col)
	{
		this.row = row;
		this.col = col;
	}
}
