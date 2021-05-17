using System;
using System.Collections.Generic;
using UnityEngine;

//public abstract class Prerequisite_Yeomsos
//{
//    public Ye_Entity Ye_EntityOwner { get; set; }

//    public abstract bool SatisfyPrerequisite(BehaviourOverTime currentBehaviors);
//}

//public class Prerequisite_Compare<T> : Prerequisite_Yeomsos
//{
//    public Pr_Data<T> ComparedDataType { get; set; }
//    public Ye_Dependent Ye_AtPreviousTime { get; set; }
//    public Ye_Dependent Ye_AtFocusTime { get; set; }
//}

/// <summary>
/// '행동/사건/원인/입력'으로 인해 발생하는 '변화/결과/출력'을 나타낸다.
/// 여기서 조건이 있을 경우를 그대로 쓸지 아니면, 새로운 클래스를 만들지도 생각해보자.
/// </summary>
//public class Prerequisite_Event_Vary : Prerequisite_Yeomsos
//{
//    public Ye_Dependent Ye_Envet { get; protected set; }
//    public Ye_Dependent Ye_Vary { get; protected set; }

//    public List<Condition_Prerequisite> Conditions_event { get; } = new List<Condition_Prerequisite>();
//    public List<Condition_Prerequisite> Conditions_vary { get; } = new List<Condition_Prerequisite>();

//    public override bool SatisfyPrerequisite(BehaviourOverTime currentBehaviors)
//    {
//        Ye_Envet = null;
//        Ye_Vary = null;



//        return false;
//    }

//    private bool SatisfyEvent(Ye_Dependent ye_event)
//    {
//        foreach (var condition in Conditions_event)
//        {
//            if (condition.SatisfyCondition(ye_event) == false)
//            {
//                return false;
//            }
//        }

//        return true;
//    }

//    private bool SatisfyVary(Ye_Dependent ye_vary)
//    {
//        foreach (var condition in Conditions_vary)
//        {
//            if (condition.SatisfyCondition(ye_vary) == false)
//            {
//                return false;
//            }
//        }

//        return true;
//    }
//}

//public class Prerequisite_ActionWalk_Move : Prerequisite_Event_Vary
//{
//    public bool Setup(Ye_Dependent ye_envent, Ye_Dependent ye_vary)
//    {
//        Ye_Action ye_action = ye_envent as Ye_Action;
//        Ye_Move ye_move = ye_vary as Ye_Move;

//        if (ye_action == null || ye_move == null)
//        {
//            return false;
//        }

//        if (ye_action.ActionState != EActionState.WALK)
//        {
//            return false;
//        }

//        Ye_Envet = ye_action;
//        Ye_Vary = ye_move;

//        return true;
//    }
//}

public class Prerequisite_Yeomso
{
    public Ye_Dependent Ye_object { get; set; }

    public YeomsoTypeNumber TypeNumber { get; set; }

    private Type typeProperty = null;
    public Type TypeProperty
    {
        get { return typeProperty; }
        set
        {
            if (value.BaseType == typeof(Property_Base))
            {
                typeProperty = value;
            }
        }
    }

}

public class Prerequisite_Condition
{
    public List<YeomsoTypeNumber> ListParameterYeomsoTypeNumber { get; } = new List<YeomsoTypeNumber>();
    public Prerequisite_Yeomso[] ArrayYeomsos { get; private set; }

    //public delegate bool SatisfySelfCondition(Ye_Dependent[] ye_target);
    public Func<Ye_Entity, Prerequisite_Yeomso[], bool> ConditionFunc { get; set; }

    public void SetupPrerequisiteYeomsos()
    {
        int count = ListParameterYeomsoTypeNumber.Count;

        if (count <= 0)
        {
            Debug.LogError(count);
        }

        //Debug.Log(count);

        ArrayYeomsos = new Prerequisite_Yeomso[count];
    }

    public bool SatisfyCondition(Ye_Entity ye_entity)
    {
        return ConditionFunc(ye_entity, ArrayYeomsos);
    }
}