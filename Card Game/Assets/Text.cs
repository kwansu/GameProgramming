using UnityEngine;
using System.Collections;

public class Text : MonoBehaviour
{
	TextMesh textMesh;

	void Awake()
	{
		textMesh = GetComponent<TextMesh>();
	}

	public void Reset()
	{
		textMesh.text = null;
	}

	public void SetText(Card card)
	{
		textMesh.text = card.Symbol.ToString2() + card.Value.ToString2();
	}
}
