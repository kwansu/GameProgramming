using System;
using System.Collections.Generic;
using UnityEngine;

using FieldCoordinate = UnityEngine.Vector3;

public interface ICreatureIteration
{
	void Move(FieldCoordinate destination);
	void Move(InteractiveObject target);
	void PickUp(AcquirableObject item);
	void Attack(InteractiveObject target);
}
