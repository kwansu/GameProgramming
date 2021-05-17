using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SituationGenerator : MonoBehaviour
{
    public GameObject unit_Rabbit = null;
    public Entity entity_Rabbit = null;

    float deltaTime = 0.0f;
    bool t2 = false, t3 = false;

    void Start()
    {
        if (unit_Rabbit != null)
        {
            entity_Rabbit = unit_Rabbit.GetComponent<Entity>();

            entity_Rabbit.AS = EActionState.WALK;

            Rigidbody2D rd2d = unit_Rabbit.GetComponent<Rigidbody2D>();
            rd2d.velocity = entity_Rabbit.Forward * 3.0f;
        }
    }

    void Update()
    {
        deltaTime += Time.deltaTime;

        //if (deltaTime > 3.0f && t2 == false)
        //{
        //    t2 = true;

        //    Rigidbody2D rd2d = unit_Rabbit.GetComponent<Rigidbody2D>();
        //    unit_Rabbit.transform.Rotate(0.0f, 0.0f, 90.0f);
        //    rd2d.velocity = entity_Rabbit.Forward * 2.0f;
        //}

        if (t2 == false && deltaTime > 3.0f)
        {
            t2 = true;

            entity_Rabbit.AS = EActionState.EAT;

            Rigidbody2D rd2d = unit_Rabbit.GetComponent<Rigidbody2D>();
            unit_Rabbit.transform.Rotate(0.0f, 0.0f, 20.0f);
            rd2d.velocity = Vector2.zero;
        }

        if (t3 == false && deltaTime > 4.0f)
        {
            t3 = true;

            entity_Rabbit.AS = EActionState.RUN;

            Rigidbody2D rd2d = unit_Rabbit.GetComponent<Rigidbody2D>();
            unit_Rabbit.transform.Rotate(0.0f, 0.0f, 40.0f);
            rd2d.velocity = entity_Rabbit.Forward * 6.0f;
        }
    }
}
