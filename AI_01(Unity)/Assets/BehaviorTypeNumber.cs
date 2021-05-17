
public struct BehaviorTypeNumber 
{
    private static int typeCount;
    private int typeNumber;

    static BehaviorTypeNumber()
    {
        typeCount = (int)EBehaviorType.LastType;
    }

    public static implicit operator int (BehaviorTypeNumber data)
    {
        return data.typeNumber;
    }

    public static implicit operator BehaviorTypeNumber(EBehaviorType eType)
    {
        BehaviorTypeNumber result;
        result.typeNumber = (int)eType;

        return result;
    }

    public override int GetHashCode()
    {
        return typeNumber;
    }

    public int AddBehaviorType()
    {
        return typeCount++;
    }

    public enum EBehaviorType
    {
        Error,

        LastType
    }
}
