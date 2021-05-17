using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public interface IObject_Human
{
    Status_Human RecognizeSelfStatus();
    Inventory RecognizeSelfInventory();
    Equipment RecognizeSelfEquipment();
    IFieldObjectInfo RecognizeSelfPlace();
    Status_Item RecognizeItemStatus(Object_Item item);
    Observation_FieldInfo ObserveFieldOfView();
}

public interface IObject_Human_Behavior
{
    void Idle();
    void Eat(Item target);
    void Walk(Vector2 direction);
    void Run(Vector2 direction);
    void WorkField(FieldObject target);
}

public class Object_Human : MonoBehaviour, IObject_Human_Behavior, IObject_Human
{
    // status
    Health hp;
    Speed speed;
    Sight sight;
    List<Item> inventory = new List<Item>();

    event Func<EBehaviorResult> ProcessBehavior;

    public float Sight { get; }
    public Vector2 Position { get; }
    public Vector2 Direction { get; }
    public float MoveSpeed { get; }
    public EActionState ActionState { get; }

    private void Update()
    {
        if (ProcessBehavior == null)
        {
            Idle();
        }

        EBehaviorResult result = ProcessBehavior();
    }

    public void Idle()
    {
        throw new NotImplementedException();
    }

    public void Eat(Item target)
    {
        throw new NotImplementedException();
    }

    public void Run(Vector2 direction)
    {
        throw new NotImplementedException();
    }

    public void Walk(Vector2 direction)
    {
        throw new NotImplementedException();
    }

    public void WorkField(FieldObject target)
    {
        throw new NotImplementedException();
    }

    protected enum EBehaviorResult
    {
        Error,
        Start,
        Do,
        End,
    }

    protected EBehaviorResult Behavior_Idle()
    {
        return EBehaviorResult.Error;
    }

    protected EBehaviorResult Behavior_Eat()
    {
        return EBehaviorResult.Error;
    }

    public Status_Human RecognizeSelfStatus()
    {
        throw new NotImplementedException();
    }

    public Inventory RecognizeSelfInventory()
    {
        throw new NotImplementedException();
    }

    public Equipment RecognizeSelfEquipment()
    {
        throw new NotImplementedException();
    }

    public IFieldObjectInfo RecognizeSelfPlace()
    {
        throw new NotImplementedException();
    }

    public Status_Item RecognizeItemStatus(Object_Item item)
    {
        throw new NotImplementedException();
    }

    public Observation_FieldInfo ObserveFieldOfView()
    {
        throw new NotImplementedException();
    }
}
