using System.Collections;
using System.Collections.Generic;
using UnityEngine.AI;
using UnityEngine;

public enum CharacterAction
{
	IDLE, MOVE, ATTACK, FOLLOW
}

[RequireComponent(typeof(NavMeshAgent))]
public class CharacterController : MonoBehaviour, ICreatureIteration
{
	private NavMeshAgent agent;
	private CharacterAction currentAction;

	void Awake()
	{
		agent = GetComponentInChildren<NavMeshAgent>();
		currentAction = CharacterAction.IDLE;
	}

	// 0.5초마다 타켓을 따라간다.
	IEnumerator FollowTarget(InteractiveObject target)
	{
		if (currentAction == CharacterAction.FOLLOW)
		{
			agent.destination = target.transform.position;
			yield return new WaitForSeconds(0.5f);
		}

		yield return null;
	}

	public void Move(Vector3 position)
	{
		agent.destination = position;
		currentAction = CharacterAction.MOVE;
	}

	public void Move(InteractiveObject target)
	{
		//currentAction = CharacterAction.FOLLOW;
	}

	public void PickUp(AcquirableObject target)
	{

	}

	public void Attack(InteractiveObject target)
	{

	}
}
