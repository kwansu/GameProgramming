using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/// <summary>
/// 월드상 관찰자가 다른 객체를 관찰할 경우 얻을 수 있는 겉보기 정보.
/// </summary>
public struct ObservedObject
{
    public int IdCode { get; set; }
    public Vector3 Pos { get; set; }
    public EActionState AS { get; set; }
}

public struct SituationFactor
{
    public float Time { get; set; }
    public Vector3 Pos { get; set; }
    public Vector2 Vel { get; set; }
    public EActionState AS { get; set; }
}

public class SituationObject
{
    public int InstanceID { get; set; }
    public List<SituationFactor> FactorList { get; set; } = new List<SituationFactor>();
    public SituationFactor RecentFactor
    {
        get
        {
            return FactorList[FactorList.Count - 1];
        }

        set
        {
            FactorList[FactorList.Count - 1] = value;
        }
    }

    public void AddFactor(Entity entity)
    {
        SituationFactor factor = new SituationFactor();

        factor.Time = Time.time;
        factor.Pos = entity.transform.position;
        factor.Vel = entity.RD2D.velocity;
        factor.AS = entity.AS;

        FactorList.Add(factor);
    }
}
