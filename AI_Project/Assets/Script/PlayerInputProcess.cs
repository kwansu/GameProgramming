using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerInputProcess : MonoBehaviour
{
	public CharacterController currentController;
	public CameraPickUp cameraPicking;

	void Update()
	{
		if (currentController != null)
		{
			if (Input.GetMouseButtonUp(1))
			{
				RaycastHit outHit;

				if (cameraPicking.PickingMousePointToWorld(out outHit))
				{
					if (outHit.collider.CompareTag("Ground"))
					{
						currentController.Move(outHit.point);
					}
				}
			}
		}
	}
}
