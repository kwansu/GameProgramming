using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Camera))]
public class CameraPickUp : MonoBehaviour
{
	Camera thisCamera;

	public GameObject destination;

	void Awake()
	{
		thisCamera = GetComponentInChildren<Camera>();
	}

	public bool PickingMousePointToWorld(out RaycastHit outHit)
	{
		outHit = new RaycastHit();
		bool result = false;

		Ray pickingRay = thisCamera.ScreenPointToRay(Input.mousePosition);

		//Debug.Log(pickingRay.origin);
		//Debug.DrawRay(pickingRay.origin, pickingRay.direction * 10.0f, Color.red, 2.0f);

		if (Physics.Raycast(pickingRay, out outHit))
		{
			destination.transform.position = outHit.point;
			result = true;
		}

		return result;
	}
}
