using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Entity : MonoBehaviour
{
    public Rigidbody2D RD2D { get; set; }
    public int InstanceID { get; set; }
    public EActionState AS { get; set; } = EActionState.STOP;
    public ERace Race { get; set; } = ERace.UNDEFINED;

    public Vector2 Forward
    {
        get
        {
            return transform.rotation * Vector3.right;
        }
    }

    void Start()
    {
        InstanceID = GetInstanceID();
        RD2D = GetComponent<Rigidbody2D>();
    }
}
