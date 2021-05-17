using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CreatureState : MonoBehaviour
{
	public float maxSP;
	public float maxHP;
	public float staminaPoint;
	public float healthPoint;
	
	void Init()
	{
		staminaPoint = maxSP;
		healthPoint = maxHP;
	}

	void Start()
	{
		Init();
	}

	void Update()
	{
		if (IsLive() == false)
		{
			ProcessDeath();
		}
	}

	bool IsLive()
	{
		return (healthPoint > 0.0f);
	}

	void ProcessDeath()
	{

	}
}
