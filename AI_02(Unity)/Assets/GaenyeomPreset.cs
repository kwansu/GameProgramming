using System;
using System.Collections.Generic;
using UnityEngine;

public class GaenyeomPreset<T> : Gaenyeom where T : GaenyeomPreset<T>, new()
{
    static private Dictionary<Type, GaenyeomTypeNumber> registeredTypes = new Dictionary<Type, GaenyeomTypeNumber>();

    public GaenyeomPreset(EGaenyeomTypePreset typePreset)
    {
        if (registeredTypes.ContainsKey(typeof(T)))
        {
            Debug.LogError(1);
        }

        if (registeredTypes.ContainsValue(typePreset))
        {
            Debug.LogError(1);
        }

        registeredTypes.Add(typeof(T), typePreset);

        typeNumber = typePreset;
    }

    public override Gaenyeom CreateGaenyeom()
    {
        return new T();
    }
}

public class Gaenyeom_Object : GaenyeomPreset<Gaenyeom_Object>
{
    public Gaenyeom_Object() : base(EGaenyeomTypePreset.Object) { }
}

public class Gaenyeom_Field : GaenyeomPreset<Gaenyeom_Field>
{
    public Gaenyeom_Field() : base(EGaenyeomTypePreset.Field) { }
}

public class Gaenyeom_Eat : GaenyeomPreset<Gaenyeom_Eat>
{
    public Gaenyeom_Eat() : base(EGaenyeomTypePreset.Eat) { }


}