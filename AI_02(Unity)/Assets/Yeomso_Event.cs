using System;
using System.Collections.Generic;

public class Gwannyeom
{
    public enum EGwannyeomType
    {
        Behavior,
        Target,
        Change,
    }

    Yeomso yeomso;
    EGwannyeomType currentType;
    Dictionary<EGwannyeomType, Gwannyeom> gwannyeoms;
}

public class Yeomso_Event
{
    List<Gwannyeom> gwannyeoms;

    // 행동/과정/발단
    Yeomso process;

    // 변화/결과/결론
    Yeomso result;
}
