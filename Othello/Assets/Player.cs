using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using TEAM = COLOR;

public class Player
{
	readonly Game game;
	readonly TEAM team;

	bool isTurn;

	public Player(TEAM team, Game game)
	{
		this.game = game;

		this.team = team;
	}

	public virtual void Update()
	{

	}
}