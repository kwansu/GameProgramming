using System.Collections.Generic;
using UnityEngine;

using HashPrerequisiteYeomso = System.Collections.Generic.Dictionary<YeomsoTypeNumber, Prerequisite_Yeomso>;

public class Concept
{
    public string Name { get; set; }
    //private Ye_Entity Ye_entityObject { get; set; }
    public HashPrerequisiteYeomso HashPrerequisiteYeomsos { get; } = new HashPrerequisiteYeomso();
    public List<Prerequisite_Condition> ListPrerequisiteConditions { get; } = new List<Prerequisite_Condition>();

    public void SetupPrerequisiteYeomsos()
    {
        foreach (var prere_condition in ListPrerequisiteConditions)
        {
            prere_condition.SetupPrerequisiteYeomsos();

            int i = 0;

            foreach (var typeNumber in prere_condition.ListParameterYeomsoTypeNumber)
            {
                if (HashPrerequisiteYeomsos.ContainsKey(typeNumber) == false)
                {
                    Prerequisite_Yeomso prere_yeomso = new Prerequisite_Yeomso();
                    prere_yeomso.TypeNumber = typeNumber;

                    HashPrerequisiteYeomsos.Add(typeNumber, prere_yeomso);
                }

                prere_condition.ArrayYeomsos[i++] = HashPrerequisiteYeomsos[typeNumber];
            }
        }
    }

    public bool ImpliedYeomso(Ye_Entity ye_entityTarget, out Ye_Dependent ye_result)
    {
        ye_result = null;

        // 필요한 모든 염소가 존재하는지 확인하고 연결한다.
        foreach (var prere_ye in HashPrerequisiteYeomsos)
        {
            var yeomsosPerCurrent = ye_entityTarget.RecentYeomsos;

            if (yeomsosPerCurrent == null)
            {
                Debug.DebugBreak();
            }

            if (yeomsosPerCurrent.Hash_Yeomsos.ContainsKey(prere_ye.Key) == false)
            {
                return false;
            }

            Ye_Dependent ye_prere = yeomsosPerCurrent.Hash_Yeomsos[prere_ye.Value.TypeNumber];

            prere_ye.Value.Ye_object = ye_prere;
        }

        // 모든 조건들을 만족하는지 확인한다. 각 조건의 파라미터는 미리 연결되어있다고 가정한다.(SetupPrerequisiteYeomsos)
        foreach (var prere_condition in ListPrerequisiteConditions)
        {
            if (prere_condition.SatisfyCondition(ye_entityTarget) == false)
            {
                return false;
            }
        }

        ye_result = new Ye_Walk();
        ye_result.Owner = ye_entityTarget;

        return true;
    }
}