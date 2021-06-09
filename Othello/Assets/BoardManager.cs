using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;

public interface IBoardManager
{
	void Update();
	void AddAbleList(Cell cell, COLOR team);
	void RemoveAbleList(Cell cell, COLOR team);
	void RemoveAbleList(Cell cell);
}

public class BoardManager : IBoardManager
{
	public void Update()
	{

	}

	public void AddAbleList(Cell cell, COLOR team)
	{

	}

	public void RemoveAbleList(Cell cell, COLOR team)
	{

	}

	public void RemoveAbleList(Cell cell)
	{

	}
}