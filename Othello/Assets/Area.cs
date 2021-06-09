using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public struct Aspect
{
	public int row, col;
}

public class Area
{
	readonly int[] totalNum;
	readonly int[] winNum;
	public readonly float[] winRate;

	int feature;

	public int FeatureNum
	{
		get
		{
			return feature;
		}

		set
		{
			feature = Mathf.Clamp(value, 0, 8);
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
			winRate[i] = (float)winNum[i] / totalNum[i];
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

