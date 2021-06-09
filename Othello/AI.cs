using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public struct Aspect
{
	public int row, col;

	public Aspect(int row, int col)
	{
		this.row = row;
		this.col = col;
	}
}

public class AI : Player
{
	public AI(COLOR team, Game game) 
		: base(team, game)
	{
	}
}